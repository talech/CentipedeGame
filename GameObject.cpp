#include <NiApplication.h>

#include "GameObject.h"

namespace CentipedeGame
{

NiImplementRTTI(GameObject, NiTimeController);

//---------------------------------------------------------------------------
	GameObject::GameObject(){}	

	GameObject::GameObject( float initX, float initY )
	:mX( initX )
	,mY( initY )
	{
	}

	

	GameObject::~GameObject()
	{
	}

//---------------------------------------------------------------------------
void GameObject::SetApplication(NiApplication *pkApp)
{
    m_pkGameApp = pkApp;
}
//---------------------------------------------------------------------------
bool GameObject::TargetIsRequiredType() const
{
    return NiIsKindOf(NiAVObject, m_pkTarget);
}


}