#include "stdafx.h"
#include "audiolib.h"
#include <Windows.h>
#include <stdio.h>

// sound assets are placed under "AudioLib/sound assets" and defined in audiolib.h

// currently three sound assets are defined in dll (audiolib.h) -- SOUND_ONE, SOUND_TWO, SOUND_THREE
// To add different sounds place the new sounds in above mentioned folder and define in audiolib.h

// you can use playSound function to play sound files not in assets also. 
// simply pass the path (remember to escape every "\") to the sound file in the funtion argument.

// note that only .wav files are currently supported.

// always terminate the program with exit(0) if addSoundToQueue() or playSoundLoop() is used. 
// because they are async methods and are not terminated implicitly by underlying windows api.

int main(){
	playSoundLoop(SOUND_ONE);
	Sleep(5000);
	playSound(SOUND_THREE);
	printf("test\n");
	system("pause");
	exit(0);
}
