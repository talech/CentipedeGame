#ifndef Player_H
#define Player_H

#include "GameObject.h"

namespace CentipedeGame
{
	class Player : public GameObject
	{
	public:
		
		Player();
		~Player();

		// Read from the buffered input
		virtual void Update( float fTime );

		void hit();

	protected:
		float m_fLastUpdateTime;

		float m_xBoundNeg;
		float m_xBoundPos;
		float m_zBoundNeg;
		float m_zBoundPos;

	};
}

#endif