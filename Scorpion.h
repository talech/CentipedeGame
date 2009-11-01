#ifndef Scorpion_H
#define Scorpion_H

#include "GameObject.h"

namespace CentipedeGame
{
	class Scorpion : public GameObject
	{
	public:
		Scorpion( float initY );
		~Scorpion();

		virtual void Update( float fTime );

		void hit();
	};
}
#endif