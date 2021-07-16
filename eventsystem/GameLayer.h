using namespace std;

#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <xinput.h>

//	CUSTOM DATA Structures
#include "Vector2.h"
#include "Vector3.h"

#include "_LinkedList.h"

//	PLATFORM LAYER STUFF
#include "_PlatformLayer.h"
#include "ConsolePlatform.h" 
//	WIN32 LAYER STUFF
#include "Win32Platform.h"

//	BASE GAME OBJECT
#include "BaseNode.h"

//	EVENT SYSTEM
#include "EventListener.h"
#include "Events.h"

//	AGUI OBJECTS
#include "_AComponent.h"
#include "_AWindow.h"
#include "_AButton.h"
#include "_AScrollBar.h"
#include "_ASingleSelectComboButton.h"
#include "_ATextBox.h"
#include "OtherComponents.h"


#include "Polygon.h"
#include "Core3D.h"

//	Managers
#include "EntityManager.h"
#include "TileMapManager.h"

// Entity Components
#include "_GComponent.h"
#include "Transform3D.h"
#include "Velocity3D.h"
#include "Render.h"
#include "UIState.h"
#include "3DMesh.h"
#include "2DMesh.h"

//	Rendering
#include "_ARenderer2D.h"
#include "_ARenderer3D.h"

//	Physics
#include "Physics.h"

class Game : public BaseNode,
			 public EventListener
{
protected:
	BaseNode *m_pGameData;
	bool m_bRunning;
	_AWindow *m_pGuiData;
	Physics *pPhysics;
	AFrame *m_pGameBuffer;

	_PlatformLayer *m_pBuffer;


	int nXOffset = 0;
	int nYOffset = 0;

	std::chrono::time_point<std::chrono::high_resolution_clock> tp1;
	std::chrono::time_point<std::chrono::high_resolution_clock> tp2;

	int getDeltaTime()
	{
		tp2 = std::chrono::high_resolution_clock::now();

		using ms = std::chrono::duration<float, std::milli>;
		float fDeltaTime = std::chrono::duration_cast<ms>(tp2 - tp1).count();

		tp1 = tp2;

		int nDeltaTime = fDeltaTime;
		return nDeltaTime;
	}

	void handlePlatformLayerEvents(ConsoleInputBuffer *pInputBuffer)
	{
		if (pInputBuffer->m_pInputBuffer)
			for (int nI = 0; nI < pInputBuffer->m_nTotalEvents; nI++)
			{
				switch (pInputBuffer->m_pInputBuffer[nI].EventType)
				{
					case WINDOW_BUFFER_SIZE_EVENT:
					{
						//	resize console dimensions to match new buffer size
						int nHeight = pInputBuffer->m_pInputBuffer[nI].Event.WindowBufferSizeEvent.dwSize.Y;
						int nWidth = pInputBuffer->m_pInputBuffer[nI].Event.WindowBufferSizeEvent.dwSize.X;


						// pOutputBuffer->resizeBuffer(nHeight, nWidth);


						break;
					}

					case KEY_EVENT:
					{
						char chKey = pInputBuffer->m_pInputBuffer[nI].Event.KeyEvent.uChar.AsciiChar;
						addEvent(new KeyboardEvent(chKey, pInputBuffer->m_pInputBuffer[nI].Event.KeyEvent.bKeyDown));
					}
					break;

					case MOUSE_EVENT:
					{
						bool bLeftPressed = false;
						bool bRightPressed = false;
						bool bShiftPressed = false;
						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
							bLeftPressed = true;
						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
							bRightPressed = true;
						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwControlKeyState == SHIFT_PRESSED)
							bShiftPressed = true;

						int nY = pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwMousePosition.Y;
						int nX = pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwMousePosition.X;
						addEvent(new MouseEvent(nY, nX, bLeftPressed));
					}
					break;
				}
			}
	}

	void update(int nDeltaTime)
	{
		m_pGuiData->update(nDeltaTime);
		pPhysics->update(m_pGameData, nDeltaTime);
		m_pGameData->update(nDeltaTime);
	}

	void render(ConsoleOutputBuffer *pConsoleBuffer)
	{
		m_pGuiData->render(m_pGameData, m_pGuiData);	// update-bucket of gui objects (not a window)
		pConsoleBuffer->renderToBuffer(m_pGuiData);
	}

	void onEvent(_Event *pEvent)
	{
		switch (pEvent->m_eType)
		{
			case CONSOLE_KEYBOARD_EVENT:
			{
				if (pEvent->get<KeyboardEvent>()->getKey() == 27)
					m_bRunning = false;
				break;
			}

			
		}
	}

public:
	Game(int nHeight, int nWidth) :
		m_pGameBuffer(NULL),
		m_pBuffer(NULL)
	{	
		pPhysics = new Physics();
		m_bRunning = true;
		// init game data
		m_pGameData = new BaseNode("GameData");
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		registerListener(this, NEW_BASENODE_EVENT);
		m_pGuiData = new _AWindow(nHeight, nWidth, 0, 0);
		m_pGuiData->setMouseOver(true);
		m_pGuiData->setDisplayPosition(false);
		m_pGuiData->setDisplayTitle(false);

		//m_pGameData->addChild(m_pGuiData);		// *sometimes* ends up clearing screen after loading gui, why?? TODO - fix
		m_pGameBuffer = new AFrame(nHeight, nWidth);

		OutputDebugString("Game Layer\n");
	}

	~Game()
	{
		delete m_pGameData;
		delete m_pGameBuffer;
		//	delete m_pGuiData; no need if part of gamedata 
	}

	void setBuffer(_PlatformLayer *pBuffer)
	{
		m_pBuffer = pBuffer;
	}

	bool isRunning()
	{
		return m_bRunning;
	}

	void Run()
	{
		float fSpeed = 1.0;

		int nDeltaTime = getDeltaTime() * fSpeed;

		if (true)
		{
			//	handlePlatformLayerEvents(pInputBuffer);
			nXOffset++;
			nYOffset++;
			dispatchEvents();
			update(nDeltaTime);
			m_pBuffer->RenderToBuffer();
		}
	}

	void run(ConsoleInputBuffer *pInputBuffer, ConsoleOutputBuffer *pConsoleBuffer)
	{
		float fSpeed = 1.0;

		int nDeltaTime = getDeltaTime() * fSpeed;

		if (true)
		{
			handlePlatformLayerEvents(pInputBuffer);
			dispatchEvents();
			update(nDeltaTime);
			render(pConsoleBuffer);
		}
	}

	// void run(input, output)
	//	set input;
	//		keyboard
	//		controller
	//		etc
	//	set output;
	//		audio
	//		video
	//	run loop
};