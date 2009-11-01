#ifndef Bomb_H
#define Bomb_H

#include "GameObject.h"

namespace CentipedeGame
{
	class Bomb : public GameObject
	{
	public:
		Bomb( float initialXVel, float initialZVel );
		~Bomb();
		
		virtual void Update( float fTime );

		void hit();

	private:

		float mZ;
	};
}

#endif
