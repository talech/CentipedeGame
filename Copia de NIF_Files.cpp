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

#include <NiMain.h>
#include <NiAnimation.h>
#include <NiParticle.h>
#include <NiLicense.h>

NiEmbedGamebryoLicenseCode;

#include "NIF_Files.h"



//---------------------------------------------------------------------------
NiApplication* NiApplication::Create()
{
    return NiNew NIF_Files;
}
//---------------------------------------------------------------------------
NIF_Files::NIF_Files() : NiSample("Tutorial: Loading And Rendering a NIF File",
    DEFAULT_WIDTH, DEFAULT_HEIGHT, true)
{
#if defined(_XENON)
    SetMediaPath("D:/DATA/");
#elif defined (WIN32)
    SetMediaPath("../../../DATA/");   
#elif defined (_PS3)
    SetMediaPath("../../../../Data/");  
#elif defined(_WII)
    SetMediaPath("/Tutorials/Graphics/Data/");

    m_uiMaxOutputLogLines = 4;
#endif

    m_bUseNavSystem = false;
}
//---------------------------------------------------------------------------
bool NIF_Files::CreateScene()
{
    // Because our scene will have some billboards with alpha, we use 
    // a NiAlphaAccumulator in order that our alpha gets sorted and drawn
    // correctly.
    NiAlphaAccumulator* pkAccum = NiNew NiAlphaAccumulator;
    m_spRenderer->SetSorter(pkAccum);
	
    // NiStreams are used to load a NIF file from disk. Once a stream is 
    // loaded, it will contain one or more "top-level" objects. These objects
    // could be NiNodes, NiTextures, or any other Gamebryo class. The Max and 
    // Maya exporters both place the scene graph as the first element in the
    // NIF file.

    NiStream kStream;

    // Load in the scenegraph for our world...
    bool bSuccess = kStream.Load(
        NiApplication::ConvertMediaFilename("GameScene.nif"));

    if (!bSuccess)
    {
        NiMessageBox("WORLD.NIF file could not be loaded!", "NIF Error");
        return false;
    }

    m_spScene = (NiNode*) kStream.GetObjectAt(0);
    NIASSERT(NiIsKindOf(NiNode, m_spScene));

    // We expect the world to have been exported with a camera, so we 
    // look for it here.
    // In order to render the scene graph, we need a camera. We're now going
    // to recurse the scene graph looking for a camera.
    if (!FindSceneCamera())
    {
        NiMessageBox("The NIF file has no camera!", "Camera Error");
        return false;
    }


	NiTObjectArray<NiCameraPtr> kCameras;
	NiTObjectArray<NiLightPtr> kLights;
	NiTObjectArray<NiNodePtr> kScenes;
	//NiStream kStream;
	//bool bSuccess = kStream.Load(
 //       NiApplication::ConvertMediaFilename("GameScene.nif"));

 //   if (!bSuccess)
 //   {
 //       NiMessageBox("WORLD.NIF file could not be loaded!", "NIF Error");
 //       return false;
 //   }

	for (unsigned int i = 0; i < kStream.GetObjectCount(); i++)
	{
		NiObject* pkObject = kStream.GetObjectAt(i);
		if (NiIsKindOf(NiCamera, pkObject))
			kCameras.Add((NiCamera*) pkObject);
		else if (NiIsKindOf(NiLight, pkObject))
			kLights.Add((NiLight*) pkObject);
		else if (NiIsKindOf(NiNode, pkObject))
			kScenes.Add((NiNode*) pkObject);
		else
		{
			// unknown object, handle it somehow
		}
	}

	//m_spScene = (NiNode*) kStream.GetObjectAt(0);
 //   NIASSERT(NiIsKindOf(NiNode, m_spScene));

    return bSuccess;
}
//---------------------------------------------------------------------------
bool NIF_Files::CreateUIElements()
{
    NiSample::CreateUIElements();

    // The Log is a text output used by all NiSample derived classes

    AddLogEntry("Press ESC or Start + Select to quit");

    return true;
}
//---------------------------------------------------------------------------
bool NIF_Files::FindSceneCamera()
{
    if (m_spScene)
    {
        m_spCamera = FindCamera(m_spScene);
    }

    return (m_spCamera != NULL);
}
//---------------------------------------------------------------------------
NiCamera* NIF_Files::FindCamera(NiAVObject* pkObject)
{
    // This function recursively walks the scenegraph until a camera
    // is found.

	if (NiIsKindOf(NiCamera, pkObject))
    {
        return (NiCamera*) pkObject;
    }
    else if (NiIsKindOf(NiNode, pkObject))
    {
        // NiNodes are the primary structural objects in Gamebryo. They 
        // group other Gamebryo scene objects together under a common parent
        // and coordinate system. NiNodes can have as many children as 
        // necessary, but those children are not guaranteed to be contiguous.

        NiNode* pkNode = (NiNode*) pkObject;
        for (unsigned int ui = 0; ui < pkNode->GetArrayCount(); ui++)
        {
            NiCamera* pkFoundCamera = FindCamera(pkNode->GetAt(ui));
            if (pkFoundCamera)
                return pkFoundCamera;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
