#ifndef GameObjectManager_H
#define GameObjectManager_H

#include <vector>
#include <NiApplication.h>

#include "GameObject.h"
#include "Mushroom.h"
#include "GameGrid.h"
#include "CentipedeSegment.h"

namespace CentipedeGame
{
	class GameObjectManager
	{
	public:

		~GameObjectManager();

		// Spawn a number of mushrooms in random locations
		void spawnRandomMushrooms( int numMushrooms );

		void destroyMushroom( Mushroom* msh );

		void destroyCentipedeSegment( CentipedeSegment* seg );

		void updateAllObjects( float fTime );

		//void addObjectScenes(NiTObjectArray<NiNodePtr> kObjects){mObjectScenes = kObjects;}

		GameGrid& getGrid();

		static GameObjectManager* getInstance() { return &mInst; }

	protected:
		GameObjectManager();

	private:
		// Stuff to make this a singleton
		static GameObjectManager mInst;

		std::vector<GameObject*> mObjects;

		GameGrid mGameGrid;
		//NiTObjectArray<NiNodePtr> mObjectScenes;
	};
}
#endif