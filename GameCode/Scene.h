#ifndef SCENE_H
#define SCENE_H


//! Scene class
/*!
	Handles the Scenes for all the game.
*/
class Scene
{
public:
	//! Constructor of an empty Scene.
	Scene();

	//! Destructor.
	virtual ~Scene();

	//! Initializes the Scene.
	virtual void Init();

	//! Function to withdraw anything owned by the class and to call Init function.
	virtual void ReInit();

	//! Handles the updating of the Scene.
	virtual void Update() = 0;

	//! Handles the drawing of the Scene.
	virtual void Render() = 0;

	//! Unload resources from the current Scene.
	virtual void UnloadResources() = 0;

	void setReInit(bool loaded = true) { _mReInit = loaded; };
	bool mustReInit() { return _mReInit; };

protected:
	bool	_mReInit;	/*<  Variable reloaded when returning to Scene */
};

#endif

