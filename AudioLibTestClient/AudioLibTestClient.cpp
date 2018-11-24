#include "stdafx.h"
#include "audiolib.h"
#include <Windows.h>
#include <stdio.h>

// sound assets are placed under "AudioLib/sound assets" and defined in audiolib.h

// currently three sound assets are defined in dll -- (audiolib.h) -- SOUND_ONE, SOUND_TWO, SOUND_THREE
// To add different sounds place the new sounds in above mentioned folder and define them in audiolib.h

// you can use playSound function to play sound files not in assets also. 
// simply pass the path (remember to escape every "\") to the sound file in the funtion argument.
// note that the path must be atmost 256 characters long including null character.

// only .wav files are currently supported.

// always terminate the program with exit(0) if addSoundToQueue() or playSoundLoop() is used. 
// because they are asynchronous methods and are not terminated implicitly by underlying api.

int main(){

	// play one file synchronously. uncomment any of the 3 line below.
	//playSound(SOUND_ONE);
	//playSound(SOUND_TWO);
	//playSound(SOUND_THREE);


	// play a sound in a loop until stopSoundLoop is called. Sleep() is defined in Windows.h
	// below block plays a sound in loop for 5 seconds.
	/*
	playSoundLoop(SOUND_ONE);
	for (int i = 0; i < 10000; i++)
		printf("playing..\n");		// you can see that the playSoundLoop is asynchronous -- non blocking.
	Sleep(5000);		// plays the loop for 5 secounds
	playSound(SOUND_THREE);
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
	// also note that if main thread is terminated then the play queue stops immediatedly.
	/*
	initPlayQueue();
	addSoundToQueue(SOUND_ONE);
	addSoundToQueue(SOUND_TWO);
	addSoundToQueue(SOUND_THREE);
	*/

	// there is stopPlayQueue() method which stops the queue immediately. it must be used carefully.
	// if we add that method at the end of above block no sound will be played as it stops the queue immediately--asynchronously.

	// TODO implement a delayed stop queue method which stops the queue from accepting new sounds to queue and teminates once all sounds currently in queue are played.
	system("pause");
	exit(0);
}
