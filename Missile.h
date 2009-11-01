#ifndef Missile_H
#define Missile_H

#include "GameObject.h"

namespace CentipedeGame
{
	class Missile : public GameObject
	{
	public:
		Missile();
		~Missile();

		virtual void Update( float fTime );

		void hit();
	}
}

#endif