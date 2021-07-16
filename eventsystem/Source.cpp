#include "GameLayer.h"
#include "Conquest.h"

LPTSTR dbs(string str)
{
	LPTSTR long_string = new TCHAR[str.size() + 1];
	strcpy(long_string, str.c_str());
	return long_string;
}

#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub)
{
	return(0);
}
x_input_set_state *_XInputSetState = XInputSetStateStub;
#define XInputSetState _XInputSetState

#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
	return(0);
}
x_input_get_state *_XInputGetState = XInputGetStateStub;
#define XInputGetState _XInputGetState

void loadXInput()
{
	HMODULE XInputLibrary = LoadLibrary("xinput1_3.dll");
	if (XInputLibrary)
	{
		XInputGetState = (x_input_get_state *)GetProcAddress(XInputLibrary, "XInputGetState");
		XInputSetState = (x_input_set_state *)GetProcAddress(XInputLibrary, "XInputSetState");
	}
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = _XInputGetState(i, &state);
		
		if (dwResult == ERROR_SUCCESS)
		{
			OutputDebugString(dbs("Controller is connected"));
		}
		else
		{
			OutputDebugString("Controller is not connected\n");
		}
	}

}

#define GAME_HEIGHT 100
#define GAME_WIDTH 150

int main()
{
	Conquest *pGame = new Conquest(GAME_HEIGHT, GAME_WIDTH);	
	
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

	//createWin32Window();
	//Win32BackBuffer *pWin32Buffer = new Win32BackBuffer(720, 1280);
	ConsoleOutputBuffer *pConsoleBuffer = new ConsoleOutputBuffer();
	pConsoleBuffer->initConsoleWindow(GAME_HEIGHT, GAME_WIDTH, 8, 8);
/*
	ConsoleInputBuffer *pInputBuffer = new ConsoleInputBuffer();
	loadXInput();	*/

	//	create platform layer object
	//	PlatformLayer = new ConsoleLayer();
	//	pass to game
	//	pGame->setPlatformLayer(PlatformLayer)
	// move loop to game layer
	// game->run();
	// should be the only command needed
	pGame->setBuffer(pConsoleBuffer);
	while (pGame->isRunning())
	{
		//pInputBuffer->getConsoleInput();
		handleWin32Events();
		pGame->Run();			//	This creates an independant layer between the console platform layer and game layer
		pConsoleBuffer->outputToConsole();
		//Win32RenderBufferToWindow(pBuffer);
	}

	/*delete pOutputBuffer;
	delete pInputBuffer;*/
	delete pConsoleBuffer;
	//delete pWin32Buffer;
	delete pGame;
	return 0;
}