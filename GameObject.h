#ifndef GameObject_H
#define GameObject_H

#include <NiTimeController.h>

class NiApplication; 

namespace CentipedeGame
{
	class GameObject : public NiTimeController
	{
		NiDeclareRTTI;

	public:
		GameObject();
		GameObject( float initX, float initY );
		~GameObject();

		virtual void Update( float fTime ) = 0;

		virtual void hit() = 0;

		void SetApplication(NiApplication *pkApp);


		float getX() { return mX; }
		float getY() { return mY; }

	protected:
		float mX;
		float mY;

		virtual bool TargetIsRequiredType () const;	    
	    

		NiApplication* m_pkGameApp;
	private:
	};

NiSmartPointer(GameObject);

}
#endif