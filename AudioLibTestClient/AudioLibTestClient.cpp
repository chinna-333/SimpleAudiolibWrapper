#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>

#include "audiolib.h"

#define SOUND_ONE "..\\audio assets\\sound1.wav"
#define SOUND_TWO "..\\audio assets\\sound2.wav"
#define SOUND_THREE "..\\audio assets\\sound3.wav"

// sound files are placed under audio assets folder

// currently three sound assets are defined from ..\\audio assets -- SOUND_ONE, SOUND_TWO, SOUND_THREE
// To add different sounds place the new sounds in above mentioned folder and define them

// you can use playSound function to play sound files not in assets also. 
// simply pass the path (remember to escape every "\") to the sound file in the funtion argument -- absolute path also accepted.
// note that the path must be atmost 256 characters long including null character.

// only .wav files are currently supported.

// always terminate the program with exit(0) if playSoundLoop() is used. 
// because ii is an asynchronous method that is not terminated implicitly by underlying windows api.

int main(){

	// play one file synchronously. uncomment any of the 3 lines below.
	//playSound(SOUND_ONE);
	//playSound(SOUND_TWO);
	//playSound(SOUND_THREE);


	// play a sound in a loop until stopSoundLoop is called. Sleep() is defined in Windows.h
	// below block plays a sound in loop for 5 seconds.
	/*
	playSoundLoop(SOUND_ONE);
	for (int i = 0; i < 10000; i++)
		printf("playing..\n");		// you can see that the playSoundLoop is asynchronous -- non blocking.
	Sleep(2000);		// waits for 5 secounds
	stopSoundLoop();	// stops the loop after 5 seconds
	printf("finished\n");
	*/


	// play a list of sounds in sequence. uncomment the below block to check it. 
	/*
	char *list[256] = { SOUND_ONE, SOUND_TWO, SOUND_THREE };
	playListInSequence(list, 3);
	*/


	// the below is asynchronous playing queue. the above mentioned playListInSequence is blocking method.
	// play queue provides a non blocking approach. ie sound plays in the background. while execution continues.
	// always call initPlayQueue() before adding to queue. sound is not played until queue is initialized.
	// call closePlayQueue() to close the queue. 
	// after closePlayQueue() new sounds cannot be added to the queue, any remaining sounds in the queue are played.
	// also note that if main thread is terminated then the play queue stops immediatedly.
	/*
	initPlayQueue();
	addSoundToQueue(SOUND_ONE);
	addSoundToQueue(SOUND_TWO);
	addSoundToQueue(SOUND_THREE);
	closePlayQueue();
	*/

	// there is stopPlayQueue() method which stops the queue immediately. it must be used carefully as it may terminate the queue without playing any sound.
	// if we add stopPlayQueue() method instead of closePlayQueue() in above block no sound will be played as it stops the queue immediately--asynchronously.

	system("pause");
}
