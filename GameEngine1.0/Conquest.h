#include "HeightTile.h"
#include "WaterTile.h"
#include "BuildingTile.h"
#include "PathingTile.h"

#include "HeightMap.h"
#include "WaterMap.h"
#include "BuildingMap.h"
#include "PathingMap.h"

#include "ConquestRenderer.h"

#include "TileMapWindow.h"
#include "CameraWindow.h"
#include "DiagWindow.h"
#include "BaseNodeSelectionButton.h"
#include "EntityFactoryWindow.h"
#include "ExplorerWindow.h"
#include "TestWindow.h"


class Conquest :
	public Game
{
private:

	BaseNode *camera()
	{
		// move this into the game later
		BaseNode *pCamera = new BaseNode("Camera");
		pCamera->addChild(new Transform3D({ 2.0, 2.0, 9.0 }, { 0, 0, 0 }, { 0, 0, 0 }));
		pCamera->addChild(new Camera({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }));
		//pCamera->addChild(new UserController(0));	// controller
		m_pGameData->getChild<EntityManager>()->addChild(pCamera);
		return pCamera;
	}

	void onEvent(_Event *pEvent)
	{
		Game::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case GUI_EVENT:
			{
				if (pEvent->get<_AGUIEvent>()->getEventType() == CAMERA_WINDOW_EVENT)
				{
					m_pGuiData->addComponent(new CameraWindow(new ConsoleRender2D(), camera(), ALIGN_LEFT));
				}
			}
			break;

			case NEW_BASENODE_EVENT:
			{
				if (pEvent->get<NewBaseNodeEvent>()->getParent())
				{

				}
				else
				{
					BaseNode *pNew = pEvent->get<NewBaseNodeEvent>()->getNew();
					m_pGameData->getChild<EntityManager>()->addChild(pNew);
				}
				break;
			}
		}
	}

public:
	Conquest(int nHeight, int nWidth) :
		Game(nHeight, nWidth)
	{
		registerListener(this, GUI_EVENT);
		
		
		TileMapManager *pMapManager = new TileMapManager();
		pMapManager->addChild(new DefaultTileMap(128, 128));

		m_pGameData->add(pMapManager);
		m_pGameData->add(new EntityManager());

		m_pGuiData->addComponent(new DiagWindow(ALIGN_RIGHT));		
		m_pGuiData->addComponent(new CameraWindow(new GameRenderer(), 2, 2, camera(), ALIGN_LEFT));
		m_pGuiData->addComponent(new ExplorerWindow(m_pGameData, ALIGN_RIGHT));
		
		
		m_pGuiData->addComponent(new TileMapWindow(pMapManager));
		

		
		
		/*
		EntityFactoryWindow *pFactory = new EntityFactoryWindow();
		m_pGuiData->addChild(pFactory);
		pFactory->setAlignment(ALIGN_RIGHT);
		BaseNode *pEntity = new BaseNode("ENTITY");
		pEntity->addChild(new Transform3D({ 15.5, 15.5, 0.0 }, { 0.0, 0.0, 0.0 }, { 1.0, 1.0, 1.0 }));
		pEntity->addChild(new ARender('A'));
		pEntity->addChild(new UIInterface());
		m_pGameData->getChild<EntityManager>()->addChild(pEntity);
		/*BaseNode *pEntity1 = new BaseNode("Entity1");
		pEntity1->addChild(new Mesh3D("sphere.obj"));
		pEntity1->addChild(new Transform3D({ 2.0, 2.0, 10.0 }, { 0.0, 0.0, 0.0 }, { 100, 100, 100 }));
		pEntity1->addChild(new Velocity3D({ 0.0, 0.0, 0.0 }, { 0.0002, 0.0001, 0.0 }));
		m_pGameData->getChild<EntityManager>()->addChild(pEntity1);

		BaseNode *pEntity2 = new BaseNode("Entity2");
		pEntity2->addChild(new Mesh3D("shipv02.obj"));
		pEntity2->addChild(new Transform3D({ 0.0, 0.0, 15.0 }, { 0.0, 0.0, 0.0 }, { 100, 100, 100 }));
		pEntity2->addChild(new Velocity3D({ 0.0, 0.0, 0.0 }, { 0.001, 0.002, 0.0 }));
		m_pGameData->getChild<EntityManager>()->addChild(pEntity2);*/

		//BaseNode *pEntity3 = new BaseNode("Entity3D");
		//pEntity3->addChild(new Mesh3D("sphere.obj"));
		//pEntity3->addChild(new Transform3D({ 0.0, 0.0, 10.0 }, { 0.0, 0.0, 0.0 }, { 100, 100, 100 }));
		//pEntity3->addChild(new Velocity3D({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }));
		//pEntity3->addChild(new UserController(0));	// keyboard
		//m_pGameData->getChild<EntityManager>()->addChild(pEntity3);

		/*BaseNode *pNewEntity = m_pGameData->getChild<EntityManager>()->createEntity("Tester");
		pNewEntity->addChild(new Transform3D({1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.05, 0.05, 0.05}));
		pNewEntity->addChild(new Poly2D());
		pNewEntity->addChild(new UserController(0));*/

		OutputDebugString("Derived Game Layer\n");
	};
};