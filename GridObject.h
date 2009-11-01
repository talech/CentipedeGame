#ifndef GridObject_H
#define GridObject_H

#include "GameObject.h"

namespace CentipedeGame
{
	class GridObject : public GameObject
	{
	public:

		// Constructor:
		// <param name = 'initX'> The x coordinate of the grid this object starts out in</param>
		// <param name = 'initY'> The y coordinate of the grid this object starts out in</param>
		GridObject( int initX, int initY );
		GridObject( );
		~GridObject();

		virtual void Update(float fTime);

		int getGridX() { return mX; }
		int getGridY() { return mY; }

	protected:
		// Called when the timer ticks
		virtual void timerUpdate() = 0;

	private:
		float mTimer;
		float mPeriod;
	};
}
#endif