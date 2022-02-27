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
	/*case WM_CLOSE:
	{
		OutputDebugString("WM_CLOSE \n");
	}
	break;*/
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

class Win32BackBuffer : 
	public _PlatformLayer
{
private:
	void createWin32Window()
	{
		//	https://docs.microsoft.com/en-us/windows/win32/learnwin32/creating-a-window
		HINSTANCE hInstance = GetModuleHandle(0);
		WNDCLASS WindowClass = {};

		WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
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
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
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


public:
	HWND WindowHandle;
	BITMAPINFO Info;
	void *pBuffer;
	int nWidth;
	int nHeight;
	int nBytesPerPixel = 4;
	HDC DeviceContext;
	RECT WindowSize;

	Win32BackBuffer(int Height, int Width) :
		_PlatformLayer()
	{
		createWin32Window();
		ResizeBuffer(Height, Width);
		DeviceContext = GetDC(WindowHandle);
		GetClientRect(WindowHandle, &WindowSize);
	}

	void GetWindowSize()
	{
		GetClientRect(WindowHandle, &WindowSize);
	}

	void ResizeBuffer(int Height, int Width)
	{
		//	https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createdibsection
		if (pBuffer)
		{
			VirtualFree(pBuffer, 0, MEM_RELEASE);
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
		pBuffer = VirtualAlloc(0, nBitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
	}

	//void DrawPoint(int nX, int nY, uint32_t Color)
	//{ 
	//	if (nX > 0 && nX < nWidth && nY > 0 && nY < nHeight)
	//	{
	//		uint8_t *pPixel = (uint8_t*)pBuffer +
	//			nX * nBytesPerPixel +
	//			nY * nWidth * nBytesPerPixel;

	//		*(uint32_t*)pPixel = Color;
	//	}
	//}
	//void DrawLine(Vector2 Start, Vector2 End, uint32_t nColor)
	//{
	//	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	//	dx = End.X - Start.X;
	//	dy = End.Y - Start.Y;
	//	dx1 = abs(dx);
	//	dy1 = abs(dy);
	//	px = 2 * dy1 - dx1;
	//	py = 2 * dx1 - dy1;

	//	if (dy1 <= dx1)
	//	{
	//		if (dx >= 0)
	//		{
	//			x = Start.X;
	//			y = Start.Y;
	//			xe = End.X;
	//		}
	//		else
	//		{
	//			x = End.X;
	//			y = End.Y;
	//			xe = Start.X;
	//		}
	//		DrawPoint(x, y, nColor);

	//		for (i = 0; x < xe; i++)
	//		{
	//			x = x + 1;
	//			if (px < 0)
	//				px = px + 2 * dy1;

	//			else
	//			{
	//				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
	//				px = px + 2 * (dy1 - dx1);
	//			}
	//			DrawPoint(x, y, nColor);
	//		}
	//	}

	//	else
	//	{
	//		if (dy >= 0)
	//		{
	//			x = Start.X;
	//			y = Start.Y;
	//			ye = End.Y;
	//		}
	//		else
	//		{
	//			x = End.X;
	//			y = End.Y;
	//			ye = Start.Y;
	//		}
	//		DrawPoint(x, y, nColor);

	//		for (i = 0; y < ye; i++)
	//		{
	//			y = y + 1;
	//			if (py <= 0)
	//				py = py + 2 * dx1;
	//			else
	//			{
	//				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
	//				py = py + 2 * (dx1 - dy1);

	//			}
	//			DrawPoint(x, y, nColor);
	//		}
	//	}

	//}
	//void DrawTriangle(Vector2 a, Vector2 b, Vector2 c, int nColor)
	//{
	//	DrawLine(a, b, nColor);
	//	DrawLine(b, c, nColor);
	//	DrawLine(c, a, nColor);
	//}
	//void DrawQuad(int nMinX, int nMinY, int nMaxX, int nMaxY, uint32_t Color)
	//{
	//	int nPitch = nWidth * nBytesPerPixel;		// full width of the row

	//	uint8_t *pRow = (uint8_t*)pBuffer +
	//		nMinX * nBytesPerPixel +
	//		nMinY * nPitch;

	//	if (nMinY < 0)
	//		nMinY = 0;
	//	if (nMinX < 0)
	//		nMinX = 0;
	//	if (nMaxX > nWidth)
	//		nMaxX = nWidth;
	//	if (nMaxY > nHeight)
	//		nMaxY = nHeight;

	//	for (int nY = nMinY; nY < nMaxY; ++nY)
	//	{

	//		uint32_t *pPixel = (uint32_t*)pRow;
	//		for (int nX = nMinX; nX < nMaxX; ++nX)
	//		{
	//			*(uint32_t*)pPixel++ = Color;
	//		}
	//		pRow += nPitch;
	//	}
	//}
	//inline uint32_t Color(uint8_t nBlue, uint8_t nGreen, uint8_t nRed, uint8_t nAlpha)
	//{
	//	return ((nBlue << 0) | (nGreen << 8) | (nRed << 16) | (nAlpha << 24));
	//}

	void fill(int Color)
	{
		int nPitch = nWidth * nBytesPerPixel;		// full width of the row in bytes (720 * 4)
		uint8_t *pRow = (uint8_t*)pBuffer;
		for (int nY = 0; nY < nHeight; ++nY)
		{
			uint32_t *pPixel = (uint32_t*)pRow;
			for (int nX = 0; nX < nWidth; ++nX)
			{
				*pPixel++ = Color;
			}
			pRow += nPitch;
		}
	}

	void Win32RenderBufferToWindow()
	{
		//	https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-stretchdibits
		GetWindowSize();
		int nWindowHeight = WindowSize.bottom - WindowSize.top;
		int nWindowWidth = WindowSize.right - WindowSize.left;
		StretchDIBits(DeviceContext,
			0, 0, nWindowWidth, nWindowHeight,
			0, 0, nWidth, nHeight,
			pBuffer,
			&Info,
			DIB_RGB_COLORS, SRCCOPY);
	}

	
};



