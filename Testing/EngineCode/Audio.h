#ifndef AUDIO_H
#define AUDIO_H

#include "../SDL/SDLMixer/include/SDL_mixer.h"


//! Audio class
/*
	Handles the management of the audio section in the game.
*/
class Audio
{
public:
	//! Destructor.
	~Audio(void);

	//! Loads a sound of the game.
	/*
		\param1: Filepath to the texture
	*/
	Mix_Chunk* LoadSound(const char* _file);

	//! Plays a sound of the game.
	/*
		\param1: ID of the sound
		\param2: Number of loops to play the sound
	*/
	void PlaySound(int _id, int _loops);

	//! Stop playing a sound of the game.
	/*
		\param1: Number of channel
	*/
	void StopSound(int _channel);

	//! Set volume of a sound.
	/*
		\param1: ID of the sound
		\param2: Volume sound
	*/
	void SetVolumeSound(int _id, int _volume);

	//! Free a sound of the game.
	/*
		\param1: ID of the sound
	*/
	void FreeSound(int _id);

	//! Free all sounds of the game.
	void FreeAllSounds();

	//! Closes current audio mixer.
	void CloseMixer();

	//! Initializes an audio mixer.
	void InitMixer();

	//! Gets Singleton instance.
	/*
		\return: Instance of Audio (Singleton pattern)
	*/
	static Audio* GetInstance();

protected:
	//! Constructor of an empty Audio manager.
	Audio(void);

private:
	bool			_mIsInitialized;	/*< Bool variable. Used to check if SDL_Mixer has been initialized */
	static Audio*	_pInstance;			/*< Singleton instance */
};

#endif

