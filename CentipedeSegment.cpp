#include "CentipedeSegment.h"
#include "GameObjectManager.h"

namespace CentipedeGame
{

	CentipedeSegment::CentipedeSegment( int initialX, int initialY )
	:GridObject( initialX, initialY )
	,mGoingLeft(false)
	,mHead(false)
	,mNext(0)
	,mPrevious(0)
	,mCurrentDirection(Direction::Left)
	{
	}

	CentipedeSegment::~CentipedeSegment()
	{
	}

	void CentipedeSegment::makeHead()
	{
		mHead = true;
	}

	bool CentipedeSegment::isHead()
	{
		return mHead;
	}

	void CentipedeSegment::hit()
	{
		if( mPrevious )
		{
			mPrevious->setNext(0);
			mPrevious->makeHead();
		}
		if( mNext )
		{
			mNext->setPrevious(0);
		}

		GameObjectManager::getInstance()->destroyCentipedeSegment(this);
	}

	void CentipedeSegment::setNext(CentipedeSegment *next)
	{
		mNext = next;
	}

	void CentipedeSegment::setPrevious(CentipedeSegment *previous)
	{
		mPrevious = previous;
	}

	void CentipedeSegment::timerUpdate()
	{
		int tempX = mX;
		int tempY = mY;

		if( !mHead )
		{
			mX = mNext->mPreviousX;
			mY = mNext->mPreviousY;
		}
		else
		{
			switch( mCurrentDirection )
			{
			case Direction::Up:
				_moveUp();
				// if I'm at the top
				if( mY >= GameObjectManager::getInstance()->getGrid().getHeight() - 1 )
				{
					// start going down
					mGoingDown = true;
				}
				break;
				
			case Direction::Down:
				_moveDown();
				//if I'm at the bottom
				if( mY <= 0 )
				{
					mGoingDown = false;
					mDiveBomb = false;
				}
				break;

			case Direction::Left:
				_moveLeft();
				break;

			case Direction::Right:
				_moveRight();
				
				break;
			}
		}

		mPreviousX = tempX;
		mPreviousY = tempY;
	}

	void CentipedeSegment::_moveDown()
	{
		mY--;
		if( mGoingLeft && !mDiveBomb )
		{
			mCurrentDirection = Direction::Left;
		}
		else
		{
			mCurrentDirection = Direction::Right;
		}
	}

	void CentipedeSegment::_moveLeft()
	{
		mX--;
		// if at the left edge of the grid
		if( mX <= 0 )
		{
			// turn up or down
			if( mGoingDown )
				mCurrentDirection = Direction::Down;
			else
				mCurrentDirection = Direction::Up;
		}

		// is there a mushroom in the next space?
		Mushroom* mush = dynamic_cast<Mushroom*>(GameObjectManager::getInstance()->getGrid().getObjectAt( mX - 1, mY ));
		
		// if there is a mushroom there
		if( mush )
		{
			// turn up or down
			if( mGoingDown )
				mCurrentDirection = Direction::Down;
			else
				mCurrentDirection = Direction::Up;

			if( mush->isPoisoned() )
				mDiveBomb = true;
		}
	}

	void CentipedeSegment::_moveRight()
	{
		mX++;

		// if at the left edge of the grid
		if( mX >= GameObjectManager::getInstance()->getGrid().getWidth() - 1 )
		{
			// turn up or down
			if( mGoingDown )
				mCurrentDirection = Direction::Down;
			else
				mCurrentDirection = Direction::Up;
		}

		// is there a mushroom in the next space?
		Mushroom* mush = dynamic_cast<Mushroom*>(GameObjectManager::getInstance()->getGrid().getObjectAt( mX + 1, mY ));
		
		// if there is a mushroom there
		if( mush )
		{
			// turn up or down
			if( mGoingDown )
				mCurrentDirection = Direction::Down;
			else
				mCurrentDirection = Direction::Up;

			if( mush->isPoisoned() )
				mDiveBomb = true;
		}
	}

	void CentipedeSegment::_moveUp()
	{
		mY++;
		if( mGoingLeft )
		{
			mCurrentDirection = Direction::Left;
		}
		else
		{
			mCurrentDirection = Direction::Right;
		}
	}


}