#include "stdafx.h"
#include "audiolib.h"


// sound assets are placed under "AudioLib/sound assets"
// currently three sound assets are defined in dll (audiolib.h) -- SOUND_ONE, SOUND_TWO, SOUND_THREE
// To add different sounds place the new sounds in above mentioned folder and define in audiolib.h
// you can use playSound function to play sound files not in assets also. simply pass the path to the sound file in the funtion argument.
// note that only .wav files are currently supported.

int main(){
	playSound(SOUND_THREE);
	return 0;
}
