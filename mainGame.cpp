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

#include "mainGame.h"
#include "Player.h"

using namespace CentipedeGame;

//---------------------------------------------------------------------------
NiApplication* NiApplication::Create()
{
    return NiNew mainGame;
}
//---------------------------------------------------------------------------
mainGame::mainGame() : NiSample("3d Centipede",
    DEFAULT_WIDTH, DEFAULT_HEIGHT, true)
{
#if defined(_XENON)
    SetMediaPath("D:/DATA/");
#elif defined (WIN32)
    SetMediaPath("../../DATA/");   
#elif defined (_PS3)
    SetMediaPath("../../../../Data/");  
#elif defined(_WII)
    SetMediaPath("/Tutorials/Graphics/Data/");

    m_uiMaxOutputLogLines = 4;
#endif

    m_bUseNavSystem = false;
}
//---------------------------------------------------------------------------
void mainGame::UpdateFrame()
{
    NiSample::UpdateFrame();
	

    m_spScene->Update(m_fAccumTime);
}
//---------------------------------------------------------------------------
bool mainGame::CreateScene()
{
	//GameObjectManager::getInstance();
    
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
        NiMessageBox("Scene file could not be loaded!", "NIF Error");
        return false;
    }

    m_spScene = (NiNode*) kStream.GetObjectAt(0);

    NIASSERT(NiIsKindOf(NiNode, m_spScene));

    // We expect the world to have been exported with a camera, so we 
    // look for it here.
    // In order to render the scene graph, we need a camera. We're now going
    // to recurse the scene graph looking for a camera.
    
	m_spCamera1 = (NiCamera*)m_spScene->GetObjectByName("camera1");
	m_spCamera = (NiCamera*)m_spScene->GetObjectByName("camera1");
    if (!m_spCamera)
    {
        NiMessageBox("The NIF file has no camera!", "Camera Error");
        return false;
    }


	NiTObjectArray<NiCameraPtr> kCameras;
	NiTObjectArray<NiLightPtr> kLights;
	NiTObjectArray<NiNodePtr> kScenes;


	for (unsigned int i = 0; i < kStream.GetObjectCount(); i++)
	{
		NiObject* pkObject = kStream.GetObjectAt(i);
		if (NiIsKindOf(NiCamera, pkObject)){
			NiCamera* m_cam = (NiCamera*)pkObject;
			kCameras.Add((NiCamera*) pkObject);
			if(m_cam->GetName().EqualsNoCase("camera2")){
				m_spCamera2 = m_cam; 
				NIASSERT(m_spCamera2);
			}
		}
		
		else if (NiIsKindOf(NiLight, pkObject))
			kLights.Add((NiLight*) pkObject);
		else if (NiIsKindOf(NiNode, pkObject)){
			kScenes.Add((NiNode*) pkObject);
			
		}
		else
		{
			// unknown object, handle it somehow
		}
	}
	//GameObjectManager::addObjectScenes(kScenes);
	
	NiNode* pkGnome = (NiNode*)m_spScene->GetObjectByName("|gnome");

	Player* pkPlayer = NiNew Player();
	pkPlayer->SetTarget(pkGnome);
	pkPlayer->SetApplication(this);

    return bSuccess;
}
//---------------------------------------------------------------------------
bool mainGame::CreateUIElements()
{
    NiSample::CreateUIElements();

    // The Log is a text output used by all NiSample derived classes

    AddLogEntry("Press ESC or Start + Select to quit");

    return true;
}
//---------------------------------------------------------------------------


//Switch between cameras
void mainGame::SwitchCamera(){
	NiInputKeyboard* pkKeyboard = NULL;
        if (this->GetInputSystem()){
            pkKeyboard = this->GetInputSystem()->GetKeyboard();
        }

        if (pkKeyboard != NULL){
			if (pkKeyboard->KeyWasPressed(NiInputKeyboard::KEY_C)){
				if(m_spCamera == m_spCamera1)
					m_spCamera = m_spCamera2;
				else
					m_spCamera = m_spCamera1;
			}


        }
}