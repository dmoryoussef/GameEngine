#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub) { return(0); }
x_input_set_state *_XInputSetState = XInputSetStateStub;
#define XInputSetState _XInputSetState

#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub) { return(0); }
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
			OutputDebugString("Controller is connected\n");
		}
		else
		{
			OutputDebugString("Controller is not connected\n");
		}
	}

}

struct MouseState
{
	int nX;
	int nY;
	Vector2 Position;
	bool bLeftButtonDown = false;
	bool bRightButtonDown = false;
	bool bWheeledUp = false;
	bool bWheeledDown = false;
	bool bWheelButtonDown = false;
	bool bShiftDown = false;
};

struct GamePad
{
	int nIndex;
	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Start;
	bool Back;
	bool LeftShoulder;
	bool RightShoulder;
	bool AButton;
	bool BButton;
	bool XButton;
	bool YButton;

	float LeftStickX;
	float LeftStickY;

	float RightStickX;
	float RightStickY;

	float clearDeadzone(float val)
	{
		if (val > 0)
			if (val < .2)
				val = 0;
		if (val < 0)
			if (val > -0.2)
				val = 0;
		
		return val;
	}
};

class _PlatformLayer
{
private:

public:
	_PlatformLayer() 
	{
		loadXInput();
	};

	virtual void RenderToBuffer() {};
	virtual void CopyBufferToWindow() {};
	virtual void ResizeBuffer() {};
};