const int BG_BLACK = 0;
const int BG_DARKBLUE = 16;
const int BG_DARKGREEN = 32;
const int BG_DARKTEAL = 48;
const int BG_DARKRED = 64;
const int BG_PURPLE = 80;
const int BG_DARKYELLOW = 96;
const int BG_LIGHTGREY = 112;
const int BG_DARKGREY = 128;
const int BG_LIGHTBLUE = 144;
const int BG_LIGHTGREEN = 160;
const int BG_LIGHTTEAL = 176;
const int BG_LIGHTRED = 192;
const int BG_PINK = 208;
const int BG_YELLOW = 224;
const int BG_WHITE = 240;

const int FG_BLACK = 0;
const int FG_DARKBLUE = 1;
const int FG_DARKGREEN = 2;
const int FG_DARKTEAL = 3;
const int FG_DARKRED = 4;
const int FG_PURPLE = 5;
const int FG_DARKYELLOW = 6;
const int FG_LIGHTGREY = 7;
const int FG_DARKGREY = 8;
const int FG_LIGHTBLUE = 9;
const int FG_LIGHTGREEN = 10;
const int FG_LIGHTTEAL = 11;
const int FG_LIGHTRED = 12;
const int FG_PINK = 13;
const int FG_YELLOW = 14;
const int FG_WHITE = 15;

const int PIXEL_QUARTER = 176;
const int PIXEL_HALF = 177;
const int PIXEL_THREEQUARTER = 178;
const int PIXEL_SOLID = 219;

struct APixel						// Ascii Element
{
	struct PIXEL_COL
	{

	};

	struct PIXEL_TYPE
	{

	};

	int m_nColor;
	int m_chChar;

	APixel() :
		m_chChar(0),
		m_nColor(0) {}

	APixel(int nChar, int nColor) :
		m_chChar(nChar),
		m_nColor(nColor) {}

	void set(APixel asxel)
	{
		m_nColor = asxel.m_nColor;
		m_chChar = asxel.m_chChar;
	}

	void set(int chChar, int nColor)
	{
		m_nColor = nColor;
		m_chChar = chChar;
	}
};

class AFrame
{
protected:
	APixel *m_pAFrame;
	int m_nHeight;
	int m_nWidth;
	Vector2 Size;
	int m_nBGColor;
	int m_nFGColor;

public:
	AFrame()
	{
		//	default constructor
	}

	AFrame(int nWidth, int nHeight, int nBGColor, int nFGColor) :
		m_pAFrame(new APixel[nHeight * nWidth]),
		m_nHeight(nHeight),
		m_nWidth(nWidth),
		Size(nWidth, nHeight),
		m_nBGColor(nBGColor),
		m_nFGColor(nFGColor)
	{
		clear(nBGColor);
	}
	AFrame(int nWidth, int nHeight) :
		m_pAFrame(new APixel[nHeight * nWidth]),
		m_nHeight(nHeight),
		m_nWidth(nWidth),
		Size(nWidth, nHeight)
	{
		clear(BG_BLACK);
	}


	~AFrame()
	{
		delete m_pAFrame;
	}

	int getHeight()
	{
		return m_nHeight;
	}

	int getWidth()
	{
		return m_nWidth;
	}

	void setSize(int nWidth, int nHeight)
	{
		m_nHeight = nHeight;
		m_nWidth = nWidth;
		Size.Y = nHeight;
		Size.X = nWidth;
		delete m_pAFrame;
		m_pAFrame = new APixel[m_nHeight * m_nWidth];
	}

	Vector2 getSize()
	{
		return Size;
	}

	APixel getAPixel(int nX, int nY)
	{
		return m_pAFrame[nX + m_nWidth * nY];
	}

	void DrawPoint(int nX, int nY, APixel apixel)
	{
		m_pAFrame[nX + m_nWidth * nY].set(apixel);
	}

	void set(APixel asxel, int nX, int nY)
	{
		m_pAFrame[nX + m_nWidth * nY].set(asxel);
	}

	void clear(int nBGColor)
	{
		for (int nY = 0; nY < m_nHeight; ++nY)
			for (int nX = 0; nX < m_nWidth; ++nX)
			{
				m_pAFrame[nX + m_nWidth * nY].set(' ', nBGColor);
			}
	}

	void setFrame(AFrame *pAFrame, int nPosX, int nPosY)
	{
		for (int nY = 0; nY < pAFrame->getHeight(); nY++)
			for (int nX = 0; nX < pAFrame->getWidth(); nX++)
			{
				int nTotalY = nY + nPosY;
				int nTotalX = nX + nPosX;
				if ((nTotalY < m_nHeight && nTotalX < m_nWidth) &&			//	Protects from setting data outside the range of the frame
					(nTotalY >= 0 && nTotalX >= 0))
				{
					set(pAFrame->getAPixel(nX, nY), nTotalX, nTotalY);
				}
			}
	}

	void set(char chChar, int nX, int nY, int nBGColor, int nFGColor)
	{
		if (nX + m_nWidth * nY < m_nWidth * m_nHeight)
			m_pAFrame[nX + m_nWidth * nY].set(chChar, nBGColor + nFGColor);
	}

	void set(char chChar, int nX, int nY, int nColor)
	{
		if (nX + m_nWidth * nY < m_nWidth * m_nHeight)
			m_pAFrame[nX + m_nWidth * nY].set(chChar, nColor);
	}

	void set(string sString, int nX, int nY, int nColor)
	{
		for (int nI = 0; nI < sString.length(); nI++)
		{
			set(sString[nI], nX + nI, nY , nColor);
		}
	}

	void set(string sString, int nX, int nY, int nBGColor, int nFGColor)
	{
		for (int nI = 0; nI < sString.length(); nI++)
		{
			set(sString[nI], nX, nY + nI, nBGColor, nFGColor);
		}
	}

	void setVertical(string sString, int nX, int nY, int nBGColor, int nFGColor)
	{
		for (int nI = 0; nI < sString.length(); nI++)
		{
			set(sString[nI], nX , nY + nI, nBGColor, nFGColor);
		}
	}

	void setBGColor(int nBGColor)
	{
		m_nBGColor = nBGColor;
	}
	void setFGColor(int nFGColor)
	{
		m_nFGColor = nFGColor;
	}
	int currentColor()
	{
		return m_nBGColor + m_nFGColor;
	}
};

class ConsoleOutputBuffer :
	public _PlatformLayer
{
private:
	HANDLE m_hOutputHandle;
	CHAR_INFO *m_pBuffer;
	int m_nHeight;
	int m_nWidth;

public:
	ConsoleOutputBuffer(int nWidth, int nHeight) :
		m_pBuffer(NULL),
		m_nHeight(nHeight),
		m_nWidth(nWidth) ,
		_PlatformLayer()
	{
		m_hOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	};
	ConsoleOutputBuffer() :
		m_pBuffer(NULL),
		m_nHeight(0),
		m_nWidth(0) 
	{
		m_hOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	};
	~ConsoleOutputBuffer()
	{
		delete[] m_pBuffer;
	}

	void resizeBuffer(int nWidth, int nHeight)
	{
		m_nHeight = nHeight;
		m_nWidth = nWidth;
		delete m_pBuffer;
		m_pBuffer = new CHAR_INFO[nHeight * nWidth];
	}

	CHAR_INFO *getBuffer()
	{
		return m_pBuffer;
	}

	int getHeight() { return m_nHeight; }
	int getWidth() { return m_nWidth; }

	void RenderToBuffer()
	{
		for (int nY = 0; nY < m_nHeight; ++nY)
			for (int nX = 0; nX < m_nWidth; ++nX)
				{
					m_pBuffer[nX + m_nWidth * nY].Char.AsciiChar = 198;
					m_pBuffer[nX + m_nWidth * nY].Attributes = FG_DARKBLUE + BG_BLACK;
				}
	}


	void renderToBuffer(AFrame *pFrame)
	{
		for (int nY = 0; nY < pFrame->getSize().Y; ++nY)
			for (int nX = 0; nX < pFrame->getSize().X; ++nX)
				if ((nY < m_nHeight && nX < m_nWidth) &&			//	Protects from setting data outside the range of the frame
					(nY >= 0 && nX >= 0))
				{
					m_pBuffer[nX + m_nWidth * nY].Char.AsciiChar = pFrame->getAPixel(nX, nY).m_chChar;
					m_pBuffer[nX + m_nWidth * nY].Attributes = pFrame->getAPixel(nX, nY).m_nColor;
				}
	}

	void SetConsoleWindowSize(int x, int y)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		if (h == INVALID_HANDLE_VALUE)
			throw std::runtime_error("Unable to get stdout handle. \n");

		// If either dimension is greater than the largest console window we can have,
		// there is no point in attempting the change.
		{
			COORD largestSize = GetLargestConsoleWindowSize(h);
			if (x > largestSize.X)
				throw std::invalid_argument("The x dimension is too large. \n");
			if (y > largestSize.Y)
				throw std::invalid_argument("The y dimension is too large. \n");
		}


		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		if (!GetConsoleScreenBufferInfo(h, &bufferInfo))
			throw std::runtime_error("Unable to retrieve screen buffer info. \n");

		SMALL_RECT& winInfo = bufferInfo.srWindow;
		COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

		if (windowSize.X > x || windowSize.Y > y)
		{
			// window size needs to be adjusted before the buffer size can be reduced.
			SMALL_RECT info =
			{
				0,
				0,
				x < windowSize.X ? x - 1 : windowSize.X - 1,
				y < windowSize.Y ? y - 1 : windowSize.Y - 1
			};

			if (!SetConsoleWindowInfo(h, TRUE, &info))
				throw std::runtime_error("Unable to resize window before resizing buffer. \n");
		}

		COORD size = { x, y };
		if (!SetConsoleScreenBufferSize(h, size))
			throw std::runtime_error("Unable to resize screen buffer. \n");


		SMALL_RECT info = { 0, 0, x - 1, y - 1 };
		if (!SetConsoleWindowInfo(h, TRUE, &info))
			throw std::runtime_error("Unable to resize window after resizing buffer. \n");

			
		resizeBuffer(x, y);
	}

	void initConsoleWindow(int nWindowWidth, int nWindowHeight, int nPixelWidth, int nPixelHeight)
	{
		//	set size of buffer position and size
		//	https://docs.microsoft.com/en-us/windows/console/setconsolewindowinfo
		SMALL_RECT m_rectWindow = { 0, 0, 1, 1 };
		SetConsoleWindowInfo(m_hOutputHandle, TRUE, &m_rectWindow);

		// set screen buffer size
		//	https://docs.microsoft.com/en-us/windows/console/setconsolescreenbuffersize
		COORD coord = { (short)nWindowWidth, (short)nWindowHeight };
		if (!SetConsoleScreenBufferSize(m_hOutputHandle, coord))
		{
			OutputDebugStringA("SetConsoleScreenBufferSize \n");
		}

		// Assign screen buffer to the console
		//	https://docs.microsoft.com/en-us/windows/console/setconsoleactivescreenbuffer
		if (!SetConsoleActiveScreenBuffer(m_hOutputHandle))
		{
			OutputDebugStringA("SetConsoleActiveScreenBuffer \n");
		}

		// Set the font size now that the screen buffer has been assigned to the console
		//	https://docs.microsoft.com/en-us/windows/console/console-font-infoex
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = nPixelWidth;
		cfi.dwFontSize.Y = nPixelHeight;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;

		//	https://docs.microsoft.com/en-us/windows/console/setcurrentconsolefontex
		wcscpy_s(cfi.FaceName, L"Consolas");
		//if (!SetCurrentConsoleFontEx(m_hOutputHandle, false, &cfi))
		{
			OutputDebugStringA("SetCurrentConsoleFontEx \n");
		}

		// Get screen buffer info and check the maximum allowed window size. Return
		// error if exceeded, so user knows their dimensions/fontsize are too large
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		//	https://docs.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo
		if (!GetConsoleScreenBufferInfo(m_hOutputHandle, &csbi))
		{
			OutputDebugStringA("GetConsoleScreenBufferInfo \n");
		}

		if (nWindowHeight > csbi.dwMaximumWindowSize.Y)
		{
			OutputDebugStringA("Screen Height / Font Height Too Big \n");
		}

		if (nWindowWidth > csbi.dwMaximumWindowSize.X)
		{
			OutputDebugStringA("Screen Width / Font Width Too Big \n");
		}

		// Set Physical Console Window Size
		m_rectWindow = { 0, 0, (short)nWindowWidth - 1, (short)nWindowHeight - 1 };
		if (!SetConsoleWindowInfo(m_hOutputHandle, TRUE, &m_rectWindow))
		{
			OutputDebugStringA("SetConsoleWindowInfo \n");
		}

		// Set flags to allow mouse input		
		//	https://docs.microsoft.com/en-us/windows/console/setconsolemode
		if (!SetConsoleMode(m_hOutputHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		{
			OutputDebugStringA("SetConsoleMode \n");
		}

		// Allocate memory for screen buffer
		//	m_pBuffer = new CHAR_INFO[nWindowWidth * nWindowHeight];
		resizeBuffer(nWindowWidth, nWindowHeight);
		//	memset(m_pBuffer, 0, sizeof(CHAR_INFO) * nWindowWidth * nWindowHeight);

		//	https://docs.microsoft.com/en-us/windows/console/setconsolectrlhandler
		//	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);

	}

	void getConsoleBufferSize()
	{
		CONSOLE_SCREEN_BUFFER_INFO sbInfo;
		GetConsoleScreenBufferInfo(m_hOutputHandle, &sbInfo);
		int availableColumns = sbInfo.dwSize.X;
		int availableRows = sbInfo.dwSize.Y;
	}

	void outputToConsole()
	{
		COORD charBufSize = { m_nWidth, m_nHeight };
		COORD characterPos = { 0, 0 };
		SMALL_RECT writeArea = { 0, 0, m_nWidth - 1, m_nHeight - 1 };

		WriteConsoleOutput(m_hOutputHandle, m_pBuffer, charBufSize, characterPos, &writeArea);
	}
};

class ConsoleInputBuffer
{

public:
	HANDLE m_hInputHandle;
	INPUT_RECORD *m_pInputBuffer;
	int m_nTotalEvents;

	ConsoleInputBuffer() :
		m_pInputBuffer(NULL),
		m_nTotalEvents(0) 
	{
		m_hInputHandle = GetStdHandle(STD_INPUT_HANDLE);
	};

	INPUT_RECORD *getInput()
	{
		return m_pInputBuffer;
	}

	void getConsoleInput()
	{
		delete[] m_pInputBuffer;
		m_pInputBuffer = NULL;

		DWORD wTotalEvents = 0;
		DWORD wEventsRead = 0;

		GetNumberOfConsoleInputEvents(m_hInputHandle, &wTotalEvents);

		if (wTotalEvents != 0)
		{
			m_pInputBuffer = new INPUT_RECORD[wTotalEvents];
			ReadConsoleInput(m_hInputHandle, m_pInputBuffer, wTotalEvents, &wEventsRead);
			m_nTotalEvents = wTotalEvents;
		}
	}

};

