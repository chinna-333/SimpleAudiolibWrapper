// AudioLib.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include <Windows.h>
#include <mmsystem.h>
#define AUD_LIB_DLL_EXPORT
#include "audiolib.h"

wchar_t *convertStringToLiteral(char *string){
	wchar_t wtext[256];
	MultiByteToWideChar(CP_ACP, 0, string, -1, wtext, 256);
	LPWSTR literal = wtext;
	return literal;
}

extern "C"
{
	// plays a sound. function returns only after the sound is completly played. cannot be stopped intermediately.
	DECLDIR void playSound(char* fileName){
		PlaySound(convertStringToLiteral(fileName), NULL, SND_SYNC);
	}

	// queue terminates only after stopQueue() is called.
	DECLDIR void addSoundToQueue(char *fileName){
		// SND_ASYNC returns immediately after adding sound to windows sound queue. 
		PlaySound(convertStringToLiteral(fileName), NULL, SND_ASYNC);
	}

	// stops the windows sound queue.
	DECLDIR void stopQueue(){
		PlaySound(NULL, 0, 0);
	}

	// plays a sound in a Loop until stopQueue() or playSound() is called.
	DECLDIR void playSoundLoop(char *fileName){
		PlaySound(convertStringToLiteral(fileName), NULL, SND_LOOP|SND_ASYNC);
	}
}
