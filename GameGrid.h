#ifndef GameGrid_H
#define GameGrid_H

#include "GridObject.h"
#include <vector>

namespace CentipedeGame
{
	class GameGrid
	{
	public:

		GameGrid( int x, int y );

		~GameGrid();

		// Returns a pointer to the GridObject at (x, y).
		GridObject* getObjectAt( int x, int y );

		// Attempts to insert obj into cell (x, y).
		// Returns false if (x, y) is already occupied, or if (x, y) 
		// is not in the grid.
		bool insertObjectAt( GridObject* obj, int x, int y );

		// Attempts to remove the object from (x, y)
		// Returns the pointer to the object at (x, y) or a null pointer
		// if (x, y) is empty or not on the grid.
		// This does not call the GridObject's destructor.
		GridObject* removeObjectFrom( int x, int y );

		// Attempts to remove object from (xFrom, yFrom) and move it to 
		// (xTo, yTo).
		// Returns false if (xFrom, yFrom) is empty or if (xTo, yTo) is
		// already occupied or if either (xFrom, yFrom) or (xTo, yTo is
		// not in the grid.
		// Otherwise returns true
		bool moveObject( int xFrom, int yFrom, int xTo, int yTo );

		int getWidth();
		int getHeight();

	private:

		std::vector<std::vector<GridObject*>> mGrid;
	};
}

#endif