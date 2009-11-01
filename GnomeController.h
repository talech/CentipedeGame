#ifndef GNOMECONTROLLER_H
#define GNOMECONTROLLER_H

#include <NiTimeController.h>

class NiApplication;

class GnomeController : public NiTimeController
{
    NiDeclareRTTI;

public:
    GnomeController();

    virtual void Update(float fTime);

    void SetApplication(NiApplication *pkApp);

protected:
    virtual bool TargetIsRequiredType () const;

    void UpdatePosition(NiAVObject* pkObject, NiPoint3& kTrans, float fDeltaTime);
    
    
    float m_fLastUpdateTime;

	float m_xBoundNeg;
	float m_xBoundPos;
	float m_zBoundNeg;
	float m_zBoundPos;

    NiApplication* m_pkGameApp;
};


NiSmartPointer(GnomeController);


#endif
