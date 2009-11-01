#include <NiApplication.h>

#include "Player.h"

//---------------------------------------------------------------------------
namespace CentipedeGame
{
	Player::Player()
	{
	    
		m_fLastUpdateTime = 0.0f;
		
		m_xBoundNeg = -7.7;
		m_xBoundPos = 7.7;
		m_zBoundNeg = 4;
		m_zBoundPos = 8.9;
	   
	}

	Player::~Player(){}

	//---------------------------------------------------------------------------
	void Player::Update(float fTime)
	{
		float fDeltaTime = NiAbs(fTime - m_fLastUpdateTime);

		if (fDeltaTime > 1.0f)
		{
			m_fLastUpdateTime = fTime;
			return;
		}

		if (m_pkTarget)    // if there is an object, move it
		{
			NiAVObject* pkObject = (NiAVObject*)m_pkTarget;
			NIASSERT(NiIsKindOf(NiAVObject, pkObject));

			// Check the Keyboard exists
			NiInputKeyboard* pkKeyboard = NULL;
			if (m_pkGameApp->GetInputSystem())
			{
	           
				pkKeyboard = m_pkGameApp->GetInputSystem()->GetKeyboard();
			}

			int iHorz = 0;
			int iVert = 0;

	       

			if (pkKeyboard != NULL)
			{
				if (pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_LEFT) || pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_A))
					iHorz = -127;

				if (pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_RIGHT)|| pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_D))
					iHorz = 127;

				if (pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_DOWN)|| pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_S))
					iVert = 127;

				if (pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_UP)|| pkKeyboard->KeyIsDown(NiInputKeyboard::KEY_W))
					iVert = -127;
			}

			if (iHorz)
			{
				float fZ = iHorz * (1.0f / 127.0f);
				NiPoint3 kTrans(.1*fZ,0,0);
				kTrans = kTrans + pkObject->GetTranslate();
				if(kTrans.x > m_xBoundNeg && kTrans.x <m_xBoundPos)
					pkObject->SetTranslate(kTrans);
			}

			 if (iVert)
			{
				float fZ = iVert * (1.0f / 127.0f);
				NiPoint3 kTrans(0,0,.1*fZ);
				kTrans = kTrans + pkObject->GetTranslate();
				if(kTrans.z > m_zBoundNeg && kTrans.z <m_zBoundPos)
					pkObject->SetTranslate(kTrans);
			}
			 
	        
		}

		m_fLastUpdateTime = fTime;
	}
	//---------------------------------------------------------------------------

	void Player::hit(){}

}