#ifndef CentipedeSegment_H
#define CentipedeSegment_H

#include "GridObject.h"
namespace CentipedeGame
{

	enum Direction
	{
		Left,
		Down,
		Right,
		Up
	};

	class CentipedeSegment : public GridObject
	{
	public:

		CentipedeSegment( int initialX, int initialY );

		~CentipedeSegment();

		// Sets this segment as the head of the centipede.
		void makeHead();

		// Is this segment the head?
		bool isHead();

		// Makes the previous segment a head, updates the adjacent pointers,
		// updates the graphics, and notifies the GameObjectManager
		void hit();

		// Sets the next and previous pointers for this segment.
		void setNext( CentipedeSegment* next );
		void setPrevious( CentipedeSegment* previous );

	protected:

		void timerUpdate();

	private:

		void _moveRight();
		void _moveLeft();
		void _moveDown();
		void _moveUp();

		// The current direction this segment is facing
		// Only useful for heads
		Direction mCurrentDirection;

		// After moving down or up, will the centipede move left?
		bool mGoingLeft;

		// Is this centipede segment going down or up?
		bool mGoingDown;

		// If the centipede hits a poison mushroom, it dives to the bottom.
		bool mDiveBomb;

		// Is this segment the head?
		bool mHead;

		// The Segment's coordinates the last time timerUpdate() was called
		int mPreviousX;
		int mPreviousY;

		// The centipede segment in front of this one
		CentipedeSegment* mNext;

		// The segment behind this one
		CentipedeSegment* mPrevious;

		friend class CentipedeSegment;
	};
}
#endif