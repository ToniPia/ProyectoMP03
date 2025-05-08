#ifndef VIDEO_H
#define VIDEO_H

#include "../SDL/include/SDL.h"


//! Video class
/*
	Handles the management of the video section in the game.
*/
class Video
{
public:
	//! Destructor.
	~Video(void);

	//! Renders textures of the game.
	/*
		\param1: ID of the image
		\param2: rect to paint, taking the texture dimensions into account
		\param3: rect to paint, taking the world dimensions into account
	*/
	void RenderTexture(int _id, SDL_Rect _rect, SDL_Rect _rectAux);

	//! Destroy textures of the game.
	/*
		\param1: SDL_Texture pointer to the texture
	*/
	void DestroyTexture(SDL_Texture* _texture);

	//! Clears current screen.
	void ClearScreen();

	//! Updates current screen.
	void UpdateScreen();

	//! Closes the current SDL_Window window.
	void CloseWindow();

	//! Initializes a video manager.
	void InitVideo();

	//! Get for _mWindow
	SDL_Window* GetWindow() { return _mWindow; };
	//! Get for _mScreenRenderer
	SDL_Renderer* GetScreenRenderer() { return _mScreenRenderer; };

	//! Gets Singleton instance.
	/*
		\return: Instance of Video (Singleton pattern)
	*/
	static Video* GetInstance();

protected:
	//! Constructor of an empty Video manager.
	Video(void);

private:
	bool			_mIsInitialized;	/*< Bool variable. Used to check if SDL_Video and SDL_Image have been initialized */
	SDL_Window*		_mWindow;			/*< SDL_Window object */
	SDL_Renderer*	_mScreenRenderer;	/*< SDL_Renderer object */
	static Video*	_pInstance;			/*< Singleton instance */
};

#endif

