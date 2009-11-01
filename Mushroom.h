#ifndef Mushroom_H
#define Mushroom_H

#include "GridObject.h"

namespace CentipedeGame
{
	class Mushroom : public GridObject
	{
	public:
		
		// Create a Mushroom at cell (x, y) in a GameGrid
		Mushroom( int x, int y );

		~Mushroom();

		// Checks if the Mushroom is poisoned.
		bool isPoisoned();

		// Turns on the poisoned attribute.  Updates graphics.
		void poison();

		// Damages the mushroom
		// Reduces HP, updates graphics, and notifies the GameObjectManager 
		// if it dies.
		void hit();
	protected:

		void timerUpdate();

	private:

		// Whether or not this mushroom is poisoned.
		bool mPoisoned;

		// The remaining hitpoints of this Mushroom.  Max 4.  Min 0.
		int mHP;
	};
}
#endif