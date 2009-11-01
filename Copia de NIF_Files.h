// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NIF_FILES_H
#define NIF_FILES_H

#include <NiSample.h>


class NIF_Files : public NiSample
{
public:
    NIF_Files();

    virtual bool CreateScene();
    virtual bool CreateUIElements();
    virtual bool FindSceneCamera();

protected:
    NiCamera* FindCamera(NiAVObject* pkObject);
};

#endif
