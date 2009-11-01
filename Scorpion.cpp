#include "Scorpion.h"
#include "GameObjectManager.h"
#include "Mushroom.h"

namespace CentipedeGame
{

	Scorpion::Scorpion( float initY )
	:GameObject( 0, initY )
	{
	}

	Scorpion::~Scorpion()
	{
	}

	void Scorpion::Update(float fTime)
	{
		mX += fTime/8;

		// Did I walk over a mushroom?
		Mushroom* mush = dynamic_cast<Mushroom*>(GameObjectManager::getInstance()->getGrid().getObjectAt( mX, mY ));

		if( mush )
		{
			mush->poison();
		}
	}

	void Scorpion::hit()
	{
		//GameObjectManager::getInstance()->killScorpion();
	}
}