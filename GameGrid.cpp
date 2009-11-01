#include "GameGrid.h"

namespace CentipedeGame
{
	GameGrid::GameGrid( int x, int y )
	{
		mGrid = std::vector<std::vector<GridObject*>>(x);

		for( int i = 0; i < x; i++ )
		{
			mGrid[i] = std::vector<GridObject*>(y);
		}
	}

	GameGrid::~GameGrid()
	{
	}

	GridObject* GameGrid::getObjectAt( int x, int y )
	{
		return mGrid[x][y];
	}

	bool GameGrid::insertObjectAt( GridObject* obj, int x, int y )
	{
		// don't let them insert objects outside the grid
		if( x < 0 || x >= mGrid.size() || y < 0 || y >= mGrid[x].size() )
			return false;

		// don't let them insert null objects
		if( !obj )
			return false;

		if( ! mGrid[x][y] )
		{
			mGrid[x][y] = obj;
			return true;
		}

		return false;
	}

	GridObject* GameGrid::removeObjectFrom(int x, int y)
	{
		if( x < 0 || x >= mGrid.size() || y < 0 || y >= mGrid[x].size() )
			return 0;

		GridObject* tempStorage = mGrid[x][y];

		mGrid[x][y] = 0;

		return tempStorage;
	}

	bool GameGrid::moveObject(int xFrom, int yFrom, int xTo, int yTo)
	{
		GridObject* temp = removeObjectFrom( xFrom, yFrom );
		
		if( insertObjectAt( temp, xTo, yTo ) )
			return true;

		insertObjectAt( temp, xFrom, yFrom );

		return false;
	}

	int GameGrid::getHeight()
	{
		return mGrid[0].size();
	}

	int GameGrid::getWidth()
	{
		return mGrid.size();
	}
}