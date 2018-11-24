// AudioLib.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include <Windows.h>
#include <mmsystem.h>

#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

#define AUD_LIB_DLL_EXPORT
#include "audiolib.h"


queue <std::string> playQueue;
bool isQueueInitiated = false;
bool queueTerminateCalled = false;
std::mutex queuemtx, terminatemtx;

wchar_t *convertStringToLiteral(char *string){
	wchar_t wtext[256];
	MultiByteToWideChar(CP_ACP, 0, string, -1, wtext, 256);
	LPWSTR literal = wtext;
	return literal;
}

void convertTochar256(std::string source, char destination[256]){
	int i;
	for (i = 0; i < 255 && i<source.length(); i++)
		destination[i] = source[i];
	destination[i] = '\0';
}

// deamon play queue thread. checks for files to play in queue.
void queueDeamonThread(){
	std::string queuefront;
	char file[256];
	while (true){
		terminatemtx.lock();
		if (queueTerminateCalled){
			terminatemtx.unlock();
			break;
		}
		terminatemtx.unlock();
		queuemtx.lock();
		if (!playQueue.empty()){
			queuefront = playQueue.front();
			playQueue.pop();
		}
		else
			queuefront = "";
		queuemtx.unlock();
		if (queuefront != ""){
			convertTochar256(queuefront, file);
			PlaySound(convertStringToLiteral(file), NULL, SND_SYNC);
		}
		else
			this_thread::sleep_for(std::chrono::milliseconds(400));
	}
}

extern "C"
{
	// plays a sound. function returns only after the sound is completly played. cannot be stopped intermediately.
	DECLDIR void playSound(char* fileName){
		PlaySound(convertStringToLiteral(fileName), NULL, SND_SYNC);
	}

	// initialize play queue. only initialize this once.
	DECLDIR bool initPlayQueue(){
		if (isQueueInitiated)
			return false;
		isQueueInitiated = true;
		std::thread t(queueDeamonThread);
		t.detach();
	}

	// adds sound to playing queue.
	DECLDIR void addSoundToQueue(char *fileName){
		char file[256];
		convertTochar256(fileName, file);
		queuemtx.lock();
		playQueue.push(file);
		queuemtx.unlock();
	}

	// stops the windows sound queue.
	DECLDIR void stopPlayQueue(){
		terminatemtx.lock();
		if (!queueTerminateCalled){
			queueTerminateCalled = true;
		}
		terminatemtx.unlock();
	}

	// plays a sound in a Loop until stopQueue() or playSound() is called.
	DECLDIR void playSoundLoop(char *fileName){
		PlaySound(convertStringToLiteral(fileName), NULL, SND_LOOP|SND_ASYNC);
	}

	// stops the currently playing sound loop;
	DECLDIR void stopSoundLoop(){
		PlaySound(NULL, 0, 0);
		return;
	}

	// plays a list of sounds sequentially. 
	DECLDIR void playListInSequence(char **fileNamesList, int soundsCount){
		for (int i = 0; i < soundsCount; i++)
			playSound(fileNamesList[i]);
	}
}
