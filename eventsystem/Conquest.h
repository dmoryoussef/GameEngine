#include "_Tile2d.h"
#include "_TileMap.h"
#include "EarthTile.h"
#include "EarthTileMap.h"
#include "CollisionTileMap.h"

#include "CameraWindow.h"
#include "DiagWindow.h"
#include "BaseNodeSelectionButton.h"
#include "EntityFactoryWindow.h"
#include "ExplorerWindow.h"


class Conquest :
	public Game
{
private:

	BaseNode *camera()
	{
		// move this into the game later
		BaseNode *pCamera = new BaseNode("Camera");
		pCamera->addChild(new Transform3D({ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }));
		// add cameraComponent()
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
					m_pGuiData->addComponent(new CameraWindow(camera(), pEvent->get<_AGUIEvent>()->isTopDown()));
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

	//void render(ConsoleOutputBuffer *pConsoleBuffer)
	//{
	//	m_pGameBuffer->set("test", 15, 15, FG_WHITE + BG_BLACK);
	//	pConsoleBuffer->renderToBackBuffer(m_pGameBuffer);
	//}

public:
	Conquest(int nHeight, int nWidth) :
		Game(nHeight, nWidth)
	{
		registerListener(this, GUI_EVENT);
		
		m_pGameData->add(new EntityManager());

		DiagWindow *pWindow1 = new DiagWindow();
		m_pGuiData->addChild(pWindow1);
		pWindow1->setAlignment(ALIGN_RIGHT);
		
		EntityFactoryWindow *pFactory = new EntityFactoryWindow();
		m_pGuiData->addChild(pFactory);
		pFactory->setAlignment(ALIGN_RIGHT);

		CameraWindow *cameraWindow = new CameraWindow(2, 2, camera(), true);
		m_pGuiData->addComponent(cameraWindow);
		cameraWindow->setAlignment(ALIGN_LEFT);

		ExplorerWindow *pExplorer = new ExplorerWindow(m_pGameData);
		m_pGuiData->addChild(pExplorer);
		pExplorer->setAlignment(ALIGN_RIGHT);	// need an "on add" to parent or "on start" to set alignment when it has a parent set

		BaseNode *pEntity = new BaseNode("Entity");
		pEntity->addChild(new Mesh2D());
		pEntity->addChild(new Transform3D({ 25.0, 35.0, 0.0 }, { 0, 0, 0 }, { 2.0, 2.0, 0.0 }));
		pEntity->addChild(new Velocity3D({ 0.0, 0.0, 0.0 }, { 0.005, 0.0, 0.0 }));
		m_pGameData->getChild<EntityManager>()->addChild(pEntity);

		OutputDebugString("Derived Game Layer\n");
	};
};