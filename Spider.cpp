#include "Spider.h"
#include "GameObjectManager.h"
#include <stdlib.h>

namespace CentipedeGame
{
	Spider::Spider( float initX, float initY )
	:GameObject( initX, initY )
	,mMovingUp(true)
	,mMovingLeft(false)
	{
	}

	Spider::~Spider()
	{
	}

	void Spider::Update(float fTime)
	{
		if( mMovingUp )
		{
			mY += (fTime/10);
		}
		else
		{
			mY -= (fTime/10);
		}

		if( mMovingLeft )
		{
			mX -= fTime/10;
		}
		else
		{
			mX += fTime/10;
		}

		float distanceToSide;
		float gridWidth = GameObjectManager::getInstance()->getGrid().getWidth();

		// only change directions at the walls
		if( ( mX < 1 && mMovingLeft ) || ( mX - gridWidth < 1 && !mMovingLeft ) )
		{
			mMovingLeft = !mMovingLeft;
		}

		float gridHeight = GameObjectManager::getInstance()->getGrid().getHeight();

		//Change direction on random chance, or when near the walls
		int bounceChance = rand() % 100;
		if( rand() < 1 || mY < 1 || mY - gridHeight < 1 )
		{
			mMovingUp = !mMovingUp;
		}
	}

	void Spider::hit()
	{
		//GameObjectManager::getInstance()->destroySpider( this );
	}


}