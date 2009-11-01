#include <NiMain.h>
#include <NiAnimation.h>
#include <NiParticle.h>
#include <NiLicense.h>

NiEmbedGamebryoLicenseCode;

#include "CentipedeGame.h"

//---------------------------------------------------------------------------
NiApplication* NiApplication::Create()
{
    return NiNew CentipedeGame;
}
//---------------------------------------------------------------------------
CentipedeGame::CentipedeGame() : NiSample("3d Centipede",
    DEFAULT_WIDTH, DEFAULT_HEIGHT, true)
{
#if defined (WIN32)
    SetMediaPath("DATA/");   

    m_uiMaxOutputLogLines = 4;
#endif

    m_bUseNavSystem = false;
}
//---------------------------------------------------------------------------
bool CentipedeGame::CreateScene()
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
	m_spCamera = FindFirstCamera(m_spScene);
    if (!m_spCamera)
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



    return bSuccess;
}
//---------------------------------------------------------------------------
bool CentipedeGame::CreateUIElements()
{
    NiSample::CreateUIElements();

    // The Log is a text output used by all NiSample derived classes

    AddLogEntry("Press ESC or Start + Select to quit");

    return true;
}
//---------------------------------------------------------------------------
