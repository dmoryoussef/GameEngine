class _AButton :
	public _AComponent
{
protected:
	void constructBase()
	{
		int nCenterX = (Size.X / 2) - (m_strText.size() / 2);
		int nCenterY = Size.Y / 2;

		switch (m_nState)
		{
			case DEFAULT:
				//setForegroundColor(FOREGROUND_DARKGREY);
				//	setBackgroundColor(BACKGROUND_BLACK);
				set(m_strText, nCenterY, nCenterX, m_nBGColor + FG_DARKGREY);
				break;
			case MOUSE_OVER:
				//	setForegroundColor(FOREGROUND_BLACK);
				//	setBackgroundColor(BACKGROUND_WHITE);
				set(m_strText, nCenterY, nCenterX, BG_LIGHTGREY + FG_BLACK);
				break;
			case LEFT_PRESSED:
				//	setForegroundColor(FOREGROUND_WHITE);
				//	setBackgroundColor(BACKGROUND_BLACK);
				set(m_strText, nCenterY, nCenterX, m_nBGColor + FG_WHITE);
				break;
			case LEFT_RELEASED:
				//	setForegroundColor(FOREGROUND_BLACK);
				//	setBackgroundColor(BACKGROUND_WHITE);
				set(m_strText, nCenterY, nCenterX, BG_WHITE + FG_BLACK);
				break;
		}
	}

public:
	_AButton(string strText, int nY, int nX) :
		_AComponent(1, strText.size(), nY, nX) 
	{
		setText(strText);
	};

	_AButton(int nHeight, int nWidth, int nPosY, int nPosX) :
		_AComponent(nHeight, nWidth, nPosY, nPosX) 
	{
	};

	_AButton(string strText) :
		_AComponent(1, strText.size(), 0, 0)
	{
		setText(strText);
	};

	void setToggle(bool bToggle)
	{
		m_bToggle = bToggle;
	}

	
};

