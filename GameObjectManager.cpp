#include "GameObjectManager.h"

namespace CentipedeGame
{
	GameObjectManager GameObjectManager::mInst;

	GameObjectManager::GameObjectManager()
	:mGameGrid(31, 34)
	,mObjects()
	{
	}

	GameObjectManager::~GameObjectManager()
	{
	}

	void GameObjectManager::destroyCentipedeSegment(CentipedeSegment *seg)
	{
	}

	void GameObjectManager::destroyMushroom( Mushroom* msh )
	{
	}

	void GameObjectManager::updateAllObjects(float fTime)
	{
	}

	GameGrid& GameObjectManager::getGrid()
	{
		return mGameGrid;
	}

}