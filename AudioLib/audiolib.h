#ifndef AUDLIB_H
#define AUDLIB_H

#ifdef AUD_LIB_DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C"
{
	DECLDIR void playSound(char*);
	DECLDIR bool initPlayQueue();
	DECLDIR void addSoundToQueue(char *);
	DECLDIR void closePlayQueue();
	DECLDIR void stopPlayQueue();
	DECLDIR void playSoundLoop(char *);
	DECLDIR void stopSoundLoop();
	DECLDIR void playListInSequence(char **, int);
}

#endif