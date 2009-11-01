#include "GridObject.h"
#include "Defines.h"

namespace CentipedeGame
{
	GridObject::GridObject( int initX, int initY )
	:GameObject( initX, initY )
	,mTimer(0)
	,mPeriod( GRID_PERIOD )
	{
	}

	GridObject::~GridObject()
	{
	}

	void GridObject::Update(float fTime)
	{
		mTimer += fTime;

		// the period has passed.  Fire the timer!
		if( mPeriod <= mTimer )
		{
			timerUpdate();

			// reset the timer
			mTimer -= mPeriod;
		}
	}
}