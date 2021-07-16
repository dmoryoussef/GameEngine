HWND WindowHandle;

class Win32BackBuffer : 
	public _PlatformLayer
{
public:
	BITMAPINFO Info;
	void *pMemory;
	int nWidth;
	int nHeight;
	int nBytesPerPixel = 4;

	Win32BackBuffer(int Height, int Width) :
		_PlatformLayer()
	{
		ResizeBuffer(Height, Width);
	}

	void ResizeBuffer(int Height, int Width)
	{
		//	https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createdibsection
		if (pMemory)
		{
			VirtualFree(pMemory, 0, MEM_RELEASE);
		}

		nWidth = Width;
		nHeight = Height;

		Info.bmiHeader.biSize = sizeof(Info.bmiHeader);
		Info.bmiHeader.biWidth = nWidth;
		Info.bmiHeader.biHeight = -nHeight;
		Info.bmiHeader.biPlanes = 1;
		Info.bmiHeader.biBitCount = 32;
		Info.bmiHeader.biCompression = BI_RGB;

		int nBitmapMemorySize = (nWidth * nHeight) * nBytesPerPixel;
		pMemory = VirtualAlloc(0, nBitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
	}

	void RenderToBuffer()
	{
		int nPitch = nWidth * nBytesPerPixel;		// full width of the row
		uint8_t *pRow = (uint8_t*)pMemory;
		for (int nY = 0; nY < nHeight; ++nY)
		{
			uint32_t *pPixel = (uint32_t*)pRow;
			for (int nX = 0; nX < nWidth; ++nX)
			{
				uint8_t Blue = nX; //+nXOffset;
				uint8_t Green = nY;// +nYOffset;
				uint8_t Red = 0;
				uint8_t Alpha = 0;
				*pPixel++ = ((Green << 8) | Blue);
			}
			pRow += nPitch;
		}
	}
};


void Win32RenderBufferToWindow(Win32BackBuffer *pBuffer)
{
	//	https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-stretchdibits
	RECT rec;
	HDC DeviceContext = GetDC(WindowHandle);
	GetClientRect(WindowHandle, &rec);
	
	int nWindowHeight = rec.bottom - rec.top;
	int nWindowWidth = rec.right - rec.left;
	StretchDIBits(DeviceContext,
		0, 0, nWindowWidth, nWindowHeight,
		0, 0, pBuffer->nWidth, pBuffer->nHeight,
		pBuffer->pMemory,
		&pBuffer->Info,
		DIB_RGB_COLORS, SRCCOPY);


	ReleaseDC(WindowHandle, DeviceContext);
}

LRESULT CALLBACK
MainWindowCallback(HWND Window,
				   UINT Message,
				   WPARAM WParam,
				   LPARAM LParam)
{
	LRESULT Result = 0;
	switch (Message)
	{
		case WM_SIZE:
		{
			//	resizes buffer to match window size
			//	RECT rec;
			//	GetClientRect(Window, &rec);
			//	int nWidth = rec.right - rec.left;
			//	int nHeight = rec.bottom - rec.top;
			//	ResizeBuffer(nHeight, nWidth);
		}
		break;
		/*case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Width = Paint.rcPaint.right - Paint.rcPaint.left;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;

			RECT rec;
			GetClientRect(Window, &rec);
			UpdateWindow(DeviceContext, rec);
			EndPaint(Window, &Paint);
		}
		break;*/
		case WM_DESTROY:
		{
			OutputDebugString("WM_DESTROY \n");
		}
		break;
		case WM_CLOSE:
		{
			OutputDebugString("WM_CLOSE \n");
		}
		break;
		case WM_ACTIVATEAPP:
		{
			OutputDebugString("WM_ACTIVATEAPP \n");
		}
		break;
		default:
		{
			Result = DefWindowProc(Window, Message, WParam, LParam);
		}
		break;
	}

	return Result;
}

void createWin32Window()
{
	//	https://docs.microsoft.com/en-us/windows/win32/learnwin32/creating-a-window
	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASS WindowClass = {};

	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = "Win32 Window Class";

	if (!RegisterClass(&WindowClass))
	{
		OutputDebugString("RegisterClass error");
	}
	//	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
	WindowHandle = 
			CreateWindowEx(
				0,
				WindowClass.lpszClassName,
				"Win32 Window",
				WS_OVERLAPPEDWINDOW|WS_VISIBLE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				0,
				0,
				hInstance,
				0);

	if (!WindowHandle)
	{
		OutputDebugString("Window not created");
	}
		

}

void handleWin32Events()
{
	//	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
	MSG Message;
	while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

}