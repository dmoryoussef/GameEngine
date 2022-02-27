using namespace std;

#include <stdio.h>
#include <Windows.h>
#include <WindowsX.h>
#include <string.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <xinput.h>

class _InputDevice
{
	//	keyboard input x 1
	//	mouse input x 1
	//	game pad input x 4
};

class Keyboard :
	public _InputDevice
{
	//	keys[256]
	//	up/down
};

class Gamepad :
	public _InputDevice
{
	bool bUp;
	bool bDown;
	bool bLeft;
	bool bRight;
	bool bStart;
	bool bBack;
	bool bLeftShoulder;
	bool bRightShoulder;
	bool bAButton;
	bool bBButton;
	bool bXButton;
	bool bYButton;

	int bLeftStickX;
	int bLeftStickY;

	int bRightStickX;
	int bRightStickY;

	bool bConnected;
};

class Mouse :
	public _InputDevice
{
	int nX;
	int nY;

	// button 1
	// button 2
	// button 3
	// button 4
	// button 5

	// wheel up
	// wheel down
};

_InputDevice InputDevices[6];

void Debug(string str)
{
	LPTSTR long_string = new TCHAR[str.size() + 1];
	strcpy(long_string, str.c_str());
	OutputDebugStringA(long_string);
}

#define GAME_HEIGHT 100
#define GAME_WIDTH 150

template <typename T> string toString(T data)
{
	stringstream str;
	str << data;
	return str.str();
}

template <typename T> string toString(T *data)
{
	stringstream str;
	str << data;
	return str.str();
}

//	CUSTOM DATA Structures
#include "Vector2.h"
#include "Vector3.h"
#include "_LinkedList.h"

//	PLATFORM LAYER STUFF
#include "_PlatformLayer.h"
#include "ConsolePlatform.h" 
//	WIN32 LAYER STUFF
#include "Win32Platform.h"

#include "Polygon.h"
#include "Core3D.h"
//	Rendering
#include "Win32Renderer.h"
#include "_ARenderer3D.h"
#include "ConsoleRender2D.h"

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
#include "SelectionSquare.h"

// Entity Components
#include "_GComponent.h"
#include "Camera.h"
#include "UserController.h"
#include "Transform3D.h"
#include "Velocity3D.h"
#include "ARender.h"
#include "UIInterface.h"
#include "3DMesh.h"
#include "2DPoly.h"
#include "Pathfinding.h"
//	TileMaps
#include "_Tile2d.h"
#include "_TileMap.h"

//	Managers
#include "EntityManager.h"
#include "TileMapManager.h"
//	Systems
#include "Physics.h"
#include "PathfindingSystem.h"
//	GRAPHICS RENDERERS
#include "ConsoleRender3D.h"


class Game : public BaseNode,
			 public EventListener
{
protected:
	BaseNode *m_pGameData;
	bool m_bRunning;

	_AWindow *m_pGuiData;	// move to system?
	Physics *m_pPhysics;	// move to system?
	
	uint64_t nCountFreq;	
	LARGE_INTEGER PrevCounter;

	int m_nPosY;
	int m_nPosX;

	float getDeltaTime()
	{
		//	convert to a class, to be able to handle multiple timers for testing
		LARGE_INTEGER CurrCounter;
		QueryPerformanceCounter(&CurrCounter);

		uint64_t nDeltaCounter = CurrCounter.QuadPart - PrevCounter.QuadPart;

		float fDelta = (1000 * nDeltaCounter) / nCountFreq;	
		PrevCounter = CurrCounter;

		return fDelta;
	}

	void handleConsoleEvents(ConsoleInputBuffer *pInputBuffer)
	{
		DWORD dwResult;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			for (DWORD ControllerIndex = 0;
				ControllerIndex < XUSER_MAX_COUNT;
				++ControllerIndex)
			{
				XINPUT_STATE ControllerState;
				if (XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS)
				{
					XINPUT_GAMEPAD *pGamePad = &ControllerState.Gamepad;

					GamePad Controller;
					Controller.nIndex =			ControllerIndex;
					Controller.Up =				(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
					Controller.Down =			(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
					Controller.Left =			(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
					Controller.Right =			(pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
					Controller.Start =			(pGamePad->wButtons & XINPUT_GAMEPAD_START);
					Controller.Back =			(pGamePad->wButtons & XINPUT_GAMEPAD_BACK);
					Controller.LeftShoulder =	(pGamePad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
					Controller.RightShoulder =	(pGamePad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
					Controller.AButton =		(pGamePad->wButtons & XINPUT_GAMEPAD_A);
					Controller.BButton =		(pGamePad->wButtons & XINPUT_GAMEPAD_B);
					Controller.XButton =		(pGamePad->wButtons & XINPUT_GAMEPAD_X);
					Controller.YButton =		(pGamePad->wButtons & XINPUT_GAMEPAD_Y);

					//	stick range is between -32768 and 32767
					//	normalize first
					Controller.LeftStickX =		(float)pGamePad->sThumbLX / 32768.0;
					Controller.LeftStickY =		(float)pGamePad->sThumbLY / 32768.0;
					Controller.RightStickX =	(float)pGamePad->sThumbRX / 32768.0;
					Controller.RightStickY =	(float)pGamePad->sThumbRY / 32768.0;
					// clear deadzone range
					


					addEvent(new GamePadEvent(Controller));
				}
			}
			
		}

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
						MouseState State;

						int value = 0;
						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwEventFlags == MOUSE_WHEELED)
						{	
							value = pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwButtonState;
							if (value > 0)
								State.bWheeledUp = true;
							else
								State.bWheeledDown = true;
						}

						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
							State.bLeftButtonDown = true;
						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
							State.bRightButtonDown = true;
						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwControlKeyState == SHIFT_PRESSED)
							State.bShiftDown = true;
						if (pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
							State.bWheelButtonDown = true;
						

						State.Position.Y = pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwMousePosition.Y;
						State.Position.X = pInputBuffer->m_pInputBuffer[nI].Event.MouseEvent.dwMousePosition.X;

						addEvent(new MouseEvent(State));
					}
					break;
				}
			}
	}

	void handleWin32Events(Win32BackBuffer *pBuffer)
	{
		//	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
		MSG Message;
		LRESULT Result = 0;
		while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			switch (Message.message)
			{
				case WM_SETCURSOR:
				{
					//Result = DefWindowProcA(Window, Message, WParam, LParam);
				} break;
				case WM_CLOSE:
				{
					m_bRunning = false;
				} break;
				case WM_KEYDOWN:
				{
					if (Message.wParam == VK_ESCAPE)
						m_bRunning = false;

					char chKey = Message.wParam;

					addEvent(new KeyboardEvent(chKey, true));
				} break;
				case WM_KEYUP:
				{
					addEvent(new KeyboardEvent(Message.wParam, false));
				} break;

				case WM_CHAR:
				{
					char chKey = Message.wParam;
					addEvent(new KeyboardEvent(chKey, true));
				} break;

				case WM_MOUSEMOVE:
				{
					int xPos = GET_X_LPARAM(Message.lParam);
					int yPos = GET_Y_LPARAM(Message.lParam);
					//addEvent(new MouseEvent(yPos, xPos, false));
					
					//	get ratio of window size to buffer size
					//	convert mouse position
					pBuffer->GetWindowSize();
					float nWindowHeight = pBuffer->WindowSize.bottom - pBuffer->WindowSize.top;
					float nWindowWidth = pBuffer->WindowSize.right - pBuffer->WindowSize.left;
					float nBufferHeight = pBuffer->nHeight;
					float nBufferWidth = pBuffer->nWidth;
					
					float fHeightRatio = nWindowHeight / nBufferHeight;
					float fWidthRatio = nWindowWidth / nBufferWidth;

					m_nPosY = yPos / fHeightRatio;
					m_nPosX = xPos / fWidthRatio;
				} break;

			}

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		DWORD dwResult;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			// Simply get the state of the controller from XInput.
			dwResult = _XInputGetState(i, &state);

		}
	}

	void update(float fDeltaTime)
	{
		m_pGuiData->rootUpdate(fDeltaTime);
		m_pPhysics->update(m_pGameData, fDeltaTime);
		m_pGameData->rootUpdate(fDeltaTime);
	}

	void render(Win32BackBuffer *pWin32Buffer)
	{
		/*Win32Renderer Renderer(pWin32Buffer);
		Renderer.Render2D(m_pGameData);
		m_pGuiData->Win32Render(m_pGameData);*/
	}

	void render(ConsoleOutputBuffer *pConsoleBuffer)
	{
		//	Render gamedata to the gui from here
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

			case CONSOLE_MOUSE_EVENT:
			{
				m_nPosY = pEvent->get<MouseEvent>()->getState().Position.Y;
				m_nPosX = pEvent->get<MouseEvent>()->getState().Position.X;
				break;
			}
		}
	}
	

public:
	Game(int nWidth, int nHeight)
	{	
		m_nPosY = 0;
		m_nPosX = 0;
		m_pPhysics = new Physics();
		m_bRunning = true;
		// init game data
		m_pGameData = new BaseNode("GameData");
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		registerListener(this, NEW_BASENODE_EVENT);
		m_pGuiData = new _AWindow(nWidth, nHeight, 0, 0);
		m_pGuiData->setMouseOver(true);
		m_pGuiData->setDisplayPosition(false);
		m_pGuiData->setDisplayTitle(false);

		//m_pGameData->addChild(m_pGuiData);		// *sometimes* ends up clearing screen after loading gui, why?? TODO - fix

		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		nCountFreq = Frequency.QuadPart;
		
		OutputDebugString("Game Layer\n");
	}

	~Game()
	{
		delete m_pGameData;
		delete m_pGuiData; //	no need if part of gamedata 
	}

	bool isRunning()
	{
		return m_bRunning;
	}

	void Win32Run(Win32BackBuffer *pBuffer)
	{
		float fSpeed = 0.001;

		//	int nDeltaTime = getDeltaTime() * fSpeed;

		if (true)
		{
			handleWin32Events(pBuffer);
			//update(nDeltaTime);	// dont run twice
			render(pBuffer);
		}
	}

	void setup()
	{
		//	Win32PlatformLayer PlatformLayer = new Win32PlatformLayer(720, 1280);
		//		create outputbuffer
		//		create inputbuffer
		//		create soundbuffer
		//		etc
		//	pGame->init(PlatformLayer);
		//	pGame->run();
		//		update
		//		shutdown
		//			delete platformlayer

		// Win32BackBuffer *pWin32Buffer = new Win32BackBuffer(720, 1280);
		
		/*	loadXInput();	*/

			//	create platform layer object
			//	PlatformLayer = new ConsoleLayer();
			//	pass to game
			//	pGame->setPlatformLayer(PlatformLayer)
			// move loop to game layer
			// game->run();
			// should be the only command needed
	}

	void ConsoleRun()
	{
		ConsoleOutputBuffer *pConsoleBuffer = new ConsoleOutputBuffer();
		pConsoleBuffer->initConsoleWindow(GAME_WIDTH, GAME_HEIGHT, 8, 8);

		ConsoleInputBuffer *pInputBuffer = new ConsoleInputBuffer();

		float fSpeed = 1.0f;

		

		while (isRunning())
		{
			float fDeltaTime = getDeltaTime() * fSpeed;
			pInputBuffer->getConsoleInput();
			handleConsoleEvents(pInputBuffer);
			dispatchEvents();
			//	m_pPhysics->update(m_pGameData, fDeltaTime);
			update(fDeltaTime);
			
			render(pConsoleBuffer);
			pConsoleBuffer->outputToConsole();
		}

		delete pInputBuffer;
		delete pConsoleBuffer;
	}
};