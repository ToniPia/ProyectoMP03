#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <vector>

#include "../SDL/include/SDL.h"
#include "../SDL/SDLMixer/include/SDL_mixer.h"


//! ResourceManager class
/*
	Handles the management of the game.
*/
class ResourceManager
{
public:
	//! Destructor.
	~ResourceManager(void);

	//---Textures:

	//! Gets the texture ID from file name. Use AddTexture if the image needs to be loaded from disc.
	/*
		\param1: Filepath to the texture
		\return: ID of the texture
	*/
	Sint32 LoadAndGetTextureID(const char* _file);

	//! Returns the SDL_Texture of the graphic. Only for render methods.
	/*
		\param1: ID of the texture
		\return: SDL_Texture of the graphic
	*/
	SDL_Texture* GetTextureByID(Sint32 _id);

	//! Gets the texture path given an ID texture.
	/*
		\param1: ID of the texture
		\return: Filepath to the texture
	*/
	std::string GetTexturePathByID(Sint32 _id);

	//! Loads a texture from disc and adds it to the ResourceManager.
	/*
		\param1: Filepath to the texture
		\return: Index of the new texture
	*/
	Sint32 AddTexture(const char* _file);

	//! Deletes a texture from the ResourceManager texture map.
	/*
		\param1: Filepath to the texture
	*/
	void RemoveTexture(const char* _file);

	//! Returns Width and Height of the texture.
	/*
		\param1: Img ID texture
		\param2: Width value of the texture
		\param3: Height value of the texture
	*/
	void GetTextureSize(Sint32 _img, int& _width, int& _height);

	//! Returns Width of a surface.
	/*
		\param1: Img ID texture
		\return: Width of the texture
	*/
	Uint16 GetTextureWidth(Sint32 _img);

	//! Returns Height of a surface.
	/*
		\param1: Img ID texture
		\return: Height of the texture
	*/
	Uint16 GetTextureHeight(Sint32 _img);

	//---Sounds:

	//! Gets the sound ID from file name. Use AddTexture if the image needs to be loaded from disc.
	/*
		\param1: Filepath to the sound
		\return: ID of the sound
	*/
	Sint32 LoadAndGetSoundID(const char* _file);

	//! Returns the Mix_Chunk of the sound.
	/*
		\param1: ID of the sound
		\return: Mix_Chunk of the sound
	*/
	Mix_Chunk* GetSoundByID(Sint32 _id);

	//! Gets the texture path given an ID texture.
	/*
		\param1: ID of the texture
		\return: Filepath to the texture
	*/
	std::string GetSoundPathByID(Sint32 _id);

	//! Loads a texture from disc and adds it to the ResourceManager.
	/*
		\param1: Filepath to the texture
		\return: Index of the new texture
	*/
	Sint32 AddSound(const char* _file);

	//! Deletes a texture from the ResourceManager texture map.
	/*
		\param1: Filepath to the texture
	*/
	void RemoveSound(const char* _file);

	//! Searches the first NULL in _mTexturesVector and updates _mFirstFreeSlotTexture to store its position.
	/*
		\return: Index of the first NULL in _mTexturesVector
	*/
	Uint32 UpdateFirstFreeSlotTexture();

	//! Searches the first NULL in _mSoundsVector and updates _mFirstFreeSlotSound to store its position.
	/*
		\return: Index of the first NULL in _mSoundsVector
	*/
	Uint32 UpdateFirstFreeSlotSound();

	//! Gets _mTexturesVector
	std::vector<SDL_Texture*> GetTexturesVector() { return _mTexturesVector; };
	//! Gets _mSoundsVector
	std::vector<Mix_Chunk*> GetSoundsVector() { return _mSoundsVector; };

	//! Gets Singleton instance.
	/*
		\return: Instance of ResourceManager (Singleton pattern)
	*/
	static ResourceManager* GetInstance();

protected:
	//! Constructor of an empty ResourceManager.
	ResourceManager(void);

private:
	std::vector<SDL_Texture*>			_mTexturesVector;			/*< Vector that stores Textures. Useful in render methods and sequential access */
	std::vector<Mix_Chunk*>				_mSoundsVector;				/*< Vector that stores Sounds. Useful in render methods and sequential access */
	std::map<std::string, Sint32>		_mIDTextureMap;				/*< Map that stores ID. Links string to ID, useful to check if the graphic has been loaded previously */
	std::map<std::string, Sint32>		_mIDSoundMap;				/*< Map that stores ID. Links string to ID, useful to check if the sound has been loaded previously */
	Uint32								_mFirstFreeSlotTexture;		/*< First free slot in the mTexturesVector */
	Uint32								_mFirstFreeSlotSound;		/*< First free slot in the mSoundsVector */
	static ResourceManager*				_pInstance;					/*< Singleton instance */
};

#endif

