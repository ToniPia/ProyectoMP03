#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include <vector>

#include "Scene.h"


//! SceneMain class
/*!
	Handles the Main Scene for the game.
*/
class SceneMain : public Scene
{
public:
	SceneMain(void);
	~SceneMain(void);

	void	Init() override;
	void	Update() override;
	void	Render() override;
	void	UnloadResources() override;

private:
	std::vector<int>		_mIdsTexturesVector;
	bool					_mAllTexturesLoaded;
	int						_mArrowPosY;
};

#endif

