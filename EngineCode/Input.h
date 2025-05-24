#ifndef INPUT_H
#define INPUT_H

#include "../SDL/include/SDL.h"

enum EKeyState {
	OFF, Released, Pressed, Hold
};


//! Video class
/*
	Handles the management of the inputs in the game.
*/
class Input
{
public:
	//! Destructor.
	~Input(void);

	//! Reset all pressed keys to false.
	void ResetKeys();

	//! Saves pressed keys in an EKeyState's array.
	void SetPressedKeys(int _keyState);

	//! Gets pressed keys from the EKeyState's array.
	bool GetPressedKeys(int _keyState);

	//! Saves released keys in an EKeyState's array.
	void SetReleasedKeys(int _keyState);

	//! Gets ON keys from the EKeyState's array.
	bool GetHoldKeys(int _keyState);

	//! Searches for a controller that has been connected to the system.
	SDL_GameController* FindController();

	//! Closes the current SDL_GameController controller.
	/*
		\param1: SDL_GameController game controller
	*/
	void CloseController(SDL_GameController* _gameController);

	//! Initializes an input controller.
	void InitInput();

	//! Updates the input events in the game.
	void UpdateInput();

	//! Set for _mGameController
	void SetGameController(SDL_GameController* _gameController) { _mGameController = _gameController; };
	//! Get for _mGameController
	SDL_GameController* GetGameController() { return _mGameController; };

	//! Gets Singleton instance.
	/*
		\return: Instance of Input (Singleton pattern)
	*/
	static Input* GetInstance();

protected:
	//! Constructor of an empty Input manager.
	Input(void);

private:	
	bool							_mIsInitialized;	/*< Bool variable. Used to check if SDL_GameController has been initialized */
	EKeyState*						_mKeysStates;		/*< Keys' values array */
	SDL_GameController*				_mGameController;	/*< SDL_GameController object */
	static Input*					_pInstance;			/*< Singleton instance */
};

#endif

