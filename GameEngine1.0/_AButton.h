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

	void onEvent(_Event *pEvent)
	{
		_AComponent::onEvent(pEvent);

	}

public:
	_AButton(string strText, int nX, int nY) :
		_AComponent(1, strText.size(), nX, nY) 
	{
		setText(strText);
	};

	_AButton(int nWidth, int nHeight, int nPosX, int nPosY) :
		_AComponent(nWidth, nHeight, nPosX, nPosY) 
	{
	};

	_AButton(string strText, bool bToggle) :
		_AComponent(strText.size(), 1, 0, 0)
	{
		m_bToggle = bToggle;
		setText(strText);
	};

	_AButton(string strText) :
		_AComponent(strText.size(), 1, 0, 0)
	{
		setText(strText);
	};


	
};

