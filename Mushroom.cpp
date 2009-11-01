#include "Mushroom.h"
#include "GameObjectManager.h"

namespace CentipedeGame
{
	Mushroom::Mushroom( int x, int y )
	:GridObject( x, y )
	,mPoisoned(false)
	,mHP(4)
	{
	}

	Mushroom::~Mushroom()
	{
	}

	bool Mushroom::isPoisoned()
	{
		return mPoisoned;
	}

	void Mushroom::poison()
	{
		mPoisoned = true;
	}

	void Mushroom::hit()
	{
		mHP--;

		switch( mHP )
		{
		case 4:
		case 3:
		case 2:
		case 1:
			// Just reserving space for updating graphics
			break;

		case 0:
			GameObjectManager::getInstance()->destroyMushroom(this);
			// Update graphics?
			break;
		}
	}

	void Mushroom::timerUpdate()
	{
	}
}