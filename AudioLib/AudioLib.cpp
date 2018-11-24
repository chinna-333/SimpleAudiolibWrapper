// AudioLib.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include <Windows.h>
#include <mmsystem.h>
#define AUD_LIB_DLL_EXPORT
#include "audiolib.h"

extern "C"
{
	DECLDIR void playSound(char* fileName){
		wchar_t wtext[256];
		MultiByteToWideChar(CP_ACP, 0, fileName, -1, wtext, 256);
		LPWSTR file = wtext;
		PlaySound(file, NULL, SND_SYNC);
	}
}
