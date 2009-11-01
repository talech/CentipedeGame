#ifndef Spider_H
#define Spider_H

#include "GameObject.h"

namespace CentipedeGame
{
	class Spider : public GameObject
	{
	public:

		Spider( float initX, float initY );

		~Spider();

		// Move the spider diagonally, eat a mushroom, maybe?
		virtual void Update( float fTime );

		void hit();

	private:

		bool mMovingUp;
		
		bool mMovingLeft;
	};
}
#endif