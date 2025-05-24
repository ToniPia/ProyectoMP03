#include "Scene.h"

Scene::Scene()
{
	_mReInit = true;
}

Scene::~Scene()
{

}

void Scene::Init()
{
	_mReInit = false;
}

void Scene::ReInit()
{
	_mReInit = true;
}
