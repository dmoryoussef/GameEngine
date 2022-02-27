//	class component child interface
//		close parent
//		scroll parent
//		drag parent
//		other function?

enum GUI_ALIGNMENT
{
	ALIGN_NONE,
	ALIGN_TOP,
	ALIGN_BOTTOM,
	ALIGN_LEFT,
	ALIGN_CENTERLEFT,
	ALIGN_RIGHT,
	ALIGN_CENTER,
	ALIGN_OUTSIDE_LEFT,
	ALIGN_OUTSIDE_RIGHT
};

enum GUI_STATE
{
	DEFAULT,
	MOUSE_OVER,
	LEFT_PRESSED,
	LEFT_RELEASED,
	RIGHT_PRESSED,
	RIGHT_RELEASED,
	LEFT_ACTIVE
};



class _AComponent :
	public BaseNode,
	public EventListener,
	public AFrame
{
protected:
	Vector2 MaxSize;			//	any size greater than this - add scroll bar
	Vector2 Position;
	Vector2 Border;
	string m_strText;			// window title, button name, textfield, etc
	bool m_bMouseOver;

	int m_nState;
	bool m_bActive;
	bool m_bToggle;
	int m_nAlignment;

	virtual void removeComponent(_AComponent *pComponent) {}
	virtual void constructComponent(BaseNode *pData) {}
	

	void onEvent(_Event *pEvent)
	{
		switch (pEvent->m_eType)
		{
			case CONSOLE_MOUSE_EVENT:
			{
				
				updateMouseOver(pEvent->get<MouseEvent>()->getState().Position);
					
					
				switch (m_nState)
				{
					case DEFAULT:
						if (m_bMouseOver)
							setState(MOUSE_OVER);
						break;

					case MOUSE_OVER:
						if (pEvent->get<MouseEvent>()->getState().bLeftButtonDown)
							setState(LEFT_PRESSED);
						if (!m_bMouseOver)
							setState(DEFAULT);
						break;

					case LEFT_PRESSED:		//	handle toggle between active/inactive
						if (!pEvent->get<MouseEvent>()->getState().bLeftButtonDown)
						{
							if (m_bMouseOver)
							{
								if (m_bActive == false)
								{
									setState(LEFT_RELEASED);
									m_bActive = true;

								}
								else
								{
									setState(DEFAULT);
									m_bActive = false;
								}
							}
							else							// if mouse is moved off, then button released - revert to previous state
							{
								if (m_bActive)
									setState(LEFT_RELEASED);
								else
									setState(DEFAULT);
							}
						}

						break;

					case LEFT_RELEASED:
						//	do something
						if (m_bToggle == false)
							if (m_bMouseOver)
								setState(MOUSE_OVER);
							else
								setState(DEFAULT);
						if (m_bMouseOver)
							if (pEvent->get<MouseEvent>()->getState().bLeftButtonDown)
								setState(LEFT_PRESSED);
						break;

					case RIGHT_RELEASED:
						//	do something
						if (m_bMouseOver)
							setState(MOUSE_OVER);
						else
							setState(DEFAULT);
						break;

				}
				break;
			}
		}
	}

	void drawBorder(int nFinalColor)
	{
		for (int nY = 0; nY < Size.Y; nY++)
			for (int nX = 0; nX < Size.X; nX++)
			{
				if (nY == 0 || nY == m_nHeight - 1)					//	top or bottom sides
					set(205, nX, nY, nFinalColor);
				if (nX == 0 || nX == m_nWidth - 1)					//	left or right sides
					set(186, nX, nY, nFinalColor);

				if (nY == 0 && nX == 0)								//	top left corner
					set(201, nX, nY, nFinalColor);
				if (nY == 0 && nX == m_nWidth - 1)					//	top right corner
					set(187, nX, nY, nFinalColor);
				if (nY == m_nHeight - 1 && nX == m_nWidth - 1)		//	bottom right corner
					set(188, nX, nY, nFinalColor);
				if (nY == m_nHeight - 1 && nX == 0)					//	bottom left corner
					set(200, nX, nY, nFinalColor);
			}
	}

	void drawThinBorder(int nFinalColor)
	{
		for (int nY = 0; nY < Size.Y; nY++)
			for (int nX = 0; nX < Size.X; nX++)
			{
				if (nY == 0 || nY == Size.Y - 1)					//	top or bottom sides
					set(196, nX, nY, nFinalColor);
				if (nX == 0 || nX == Size.X - 1)					//	left or right sides
					set(179, nX, nY, nFinalColor);

				if (nY == 0 && nX == 0)								//	top left corner
					set(218, nX, nY, nFinalColor);
				if (nY == 0 && nX == Size.X - 1)					//	top right corner
					set(191, nX, nY, nFinalColor);
				if (nY == Size.Y - 1 && nX == Size.X - 1)			//	bottom right corner
					set(217, nX, nY, nFinalColor);
				if (nY == Size.Y - 1 && nX == 0)					//	bottom left corner
					set(192, nX, nY, nFinalColor);
			}
	}

	
public:
	_AComponent(int nWidth, int nHeight, int nPosX, int nPosY) :
		m_nState(DEFAULT),
		Position(nPosX, nPosY),
		MaxSize(nWidth, nHeight),
		Border(1, 0),
		m_bMouseOver(false),
		m_bActive(false),
		m_nAlignment(ALIGN_NONE),
		m_bToggle(true),
		AFrame(nWidth, nHeight, BG_BLACK, FG_WHITE) 
	{
		setName("COMPONENT");
		registerListener(this, CONSOLE_MOUSE_EVENT);
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		//addCallbackListener(this, CONSOLE_MOUSE_EVENT, &onMouseOver);
		
		registerListener(this, GUI_EVENT);
	};

	_AComponent(int nWidth, int nHeight) :
		m_nState(DEFAULT),
		Position(0, 0),
		MaxSize(0, 0),
		Border(0, 0),
		m_bMouseOver(false),
		m_bActive(false),
		m_bToggle(true),
		AFrame(nWidth, nHeight, BG_BLACK, FG_WHITE)
	{
		registerListener(this, CONSOLE_MOUSE_EVENT);
		registerListener(this, GUI_EVENT);
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
	};

	_AComponent(string strText) :
		m_nState(DEFAULT),
		Position(0, 0),
		MaxSize(0, 0),
		Border(0, 0),
		m_bMouseOver(false),
		m_bActive(false),
		m_bToggle(true),
		AFrame(0, 0, BG_BLACK, FG_WHITE)
	{
		setText(strText);
		registerListener(this, CONSOLE_MOUSE_EVENT);
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		registerListener(this, GUI_EVENT);

		//	set position based on other
		//	components in list
	};

	_AComponent() :
		m_nState(DEFAULT),
		Position(0, 0),
		MaxSize(0, 0),
		Border(0, 0),
		m_bMouseOver(false),
		m_bActive(false),
		m_bToggle(true),
		AFrame(0, 0, BG_BLACK, FG_WHITE)
	{
		setName("COMPONENT");
		registerListener(this, CONSOLE_MOUSE_EVENT);
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		registerListener(this, GUI_EVENT);

		//	set position based on other
		//	components in list
	};

	~_AComponent()
	{
		//	unregisterAll(this);
	}

	int DefaultColor()
	{
		return m_nBGColor + m_nFGColor;
	}

	int getAlignment()
	{
		return m_nAlignment;
	}
	int getState()
	{
		return m_nState;
	}

	void setAlignment(int nAlignment)
	{
		m_nAlignment = nAlignment;
		int nAlignY = 1; //	adjust for border
		int nAlignX = 0;
		if (m_pParent)
		{
			while (m_pParent->isIterating())
			{
				//	if current's alignment == this alignment
				_AComponent *pCurrent = m_pParent->getCurrent<_AComponent>();
				if (pCurrent != this)
					if (pCurrent->getAlignment() == nAlignment)
					{
						nAlignY = nAlignY + pCurrent->getSize().Y;
					}
			}

			switch (nAlignment)
			{
				case ALIGN_TOP:
					break;
				case ALIGN_BOTTOM:
					/*int nX = 1;
					int nY = getParent<_AComponent>()->getSize().Y;
					Position = Vector2(nY - Size.Y, nX);*/
					break;
				case ALIGN_LEFT:
				{
					//	check other previous siblings for align left?
					int nX = 1;
					int nY = nAlignY;
					Position = Vector2(nX, nY);
				} break;
				case ALIGN_CENTERLEFT:
				{
					int nX = 1;
					int nY = nAlignY;
					nY = getParent<_AComponent>()->getSize().Y;
					Position = Vector2(nX / 2 - Size.X, nY);
				} break;
				case ALIGN_RIGHT:
				{
					int nX = getParent<_AComponent>()->getSize().X;
					int nY = nAlignY;
					Position = Vector2(nX - Size.X - 1, nY);
				} break;
				case ALIGN_CENTER:
				{
					
				} break;
				case ALIGN_OUTSIDE_LEFT:
				{
					int nPosY = 0;
					int nPosX = 0;
					nPosX = nPosX - Size.X + 1;
					Vector2 NewPos(nPosX, nPosY);
					Position = NewPos;
				} break;
				case ALIGN_OUTSIDE_RIGHT:
				break;
			}
		}
	}
	void setPosition(int nX, int nY)
	{
		Position.X = nX;
		Position.Y = nY;
	}
	void setState(int nState)
	{
		m_nState = nState;
		if (m_nState == DEFAULT)
			m_bActive = false;
		addEvent(new _AGUIEvent(BUTTON_EVENT, this, NULL));
	}

	//	REFACTOR TO BASE_COMPONENT WITH ASCII AND WIN32 AS DERIVED
	//virtual void Win32Draw(BaseNode *pData) {}
	//virtual void Win32ConstructBase() {}
	//void Win32Render(BaseNode *pData)
	//{
	//	//	handle self
	//	//Win32Draw(pData);
	//	//Win32ConstructBase();
	//	//	handle children
	//	for (_AComponent *pChild = getStart<_AComponent>(); pChild != NULL; pChild = pChild->getNext<_AComponent>())
	//		pChild->Win32Render(pData);
	//}

	void render(BaseNode *pData, AFrame *pFrame)
	{
		clear(m_nBGColor);

		// specific to each component (game data to be diplayed)
		constructComponent(pData);

		//	layer base on top (title, boarder, etc)
		constructBase();

		//	set final look to main frame
		pFrame->setFrame(this, getMin().X, getMin().Y);
		
		// Now do the same for each child component
		for (_AComponent *pChild = getStart<_AComponent>(); pChild != NULL; pChild = pChild->getNext<_AComponent>())
		{
			pChild->render(pData, pFrame);
		}
	}
	void update(int nDeltaTime)
	{
		while (isIterating())
			getCurrent()->update(nDeltaTime);
	}

	//template <typename T> string toString(T data)
	//{
	//	stringstream str;
	//	str << data;
	//	return str.str();
	//}

	template <typename T> T *getComponent()
	{
		return getChild<T>();
	}

	string getText()
	{
		return m_strText;
	}

	Vector2 getPosition()
	{
		return Position;
	}
	Vector2 getConsoleWindowPosition()
	{
		Vector2 RelPosition = Position;
		for (_AComponent *pParent = getParent<_AComponent>(); pParent != NULL; pParent = pParent->getParent<_AComponent>())
		{
			Vector2 ParentPos = pParent->getPosition();
			RelPosition = RelPosition + ParentPos;
		}
		return RelPosition;
	}
	Vector2 getMin()
	{
		Vector2 Pos = getConsoleWindowPosition();
		return Pos;
	}
	Vector2 getMax()
	{
		Vector2 Position = getConsoleWindowPosition();
		Vector2 FinalMax = Position + Size;
		return  FinalMax;
	}

	void setToggle(bool bToggle)
	{
		m_bToggle = bToggle;
	}

	bool isMouseOver()
	{
		return m_bMouseOver;
	}

	virtual void updateMouseOver(Vector2 MousePosition)
	{
		if (getParent())									// MOVED THIS TO COMPONENT SPECIFIC 
			if (getParent<_AComponent>()->isMouseOver())	//	only handle if the parent component is already mouseover
			{
				if (MousePosition.X >= getMin().X &&
					MousePosition.Y >= getMin().Y &&
					MousePosition.X < getMax().X &&
					MousePosition.Y < getMax().Y)
				{
					setMouseOver(true);
				}
				else
					setMouseOver(false);
			}
			else
			{
				setMouseOver(false);						//	Parent is not MouseOver so child should not be - needs to be explicitly set or there are bugs
			}
	}

	virtual void setText(string strText)
	{
		m_strText = strText;
	}
	virtual void setMouseOver(bool bMouseOver)
	{
		m_bMouseOver = bMouseOver;
	}
	virtual void addComponent(_AComponent *pComponent) 
	{
		addChild(pComponent);
		pComponent->setAlignment(pComponent->getAlignment());
	}
	virtual void constructBase() {}
};

class UILayout :
	public _AComponent
{
private:
	int *m_nLayout;

	int m_nHeight;
	int m_nWidth;
	int m_nCellWidth;
	int m_nCellHeight;

	int m_nCellWidthBuffer;
	int m_nCellHeightBuffer;

public:
	UILayout(int nWidth, int nHeight, int nCellWidthBuffer, int nCellHeightBuffer) :
		m_nLayout(new int[nHeight * nWidth]),
		m_nHeight(nHeight),
		m_nWidth(nWidth),
		m_nCellHeightBuffer(nCellHeightBuffer),
		m_nCellWidthBuffer(nCellWidthBuffer),
		_AComponent()
	{
		clearLayout();
	};

	void clearLayout()
	{
		for (int nY = 0; nY < m_nHeight; nY++)
			for (int nX = 0; nX < m_nWidth; nX++)
			{
				m_nLayout[nX + m_nWidth * nY] = 0;
			}

		clearList(); 
	}

	void updateLayout()
	{
		//	reset position
		//	get max cell size
		//	set new position


		/*
	
		while (isIterating())
		{
			int nY = Position.Y;
			itn nX = Position.X;
			_AComponent *pComponent = getCurrent<_AComponent>();

			pComponent->setPosition(nY / m_nCellHeight, nX / m_nCellWidth);

		}

		while (isIterating())
		{
			_AComponent *pComponent = getCurrent<_AComponent>();

			if (pComponent->getSize().X > m_nCellWidth)
				m_nCellWidth = pComponent->getSize().X;
			if (pComponent->getSize().Y > m_nCellHeight)
				m_nCellHeight = pComponent->getSize().Y;

		}
		int nY = 0;
		int nX = 0;
		while (isIterating())
		{
			_AComponent *pComponent = getCurrent<_AComponent>();

			int nY = pComponent->getPosition().Y / m_nCellHeight;
			int nX = pComponent->getPosition().X / m_nCellWidth;

			pComponent->setPosition(nY * m_nCellHeight, nX * m_nCellWidth);
		}*/
	}

	void addComponent(_AComponent *pComponent, int nX, int nY)
	{
		if (nY < m_nHeight && nX < m_nWidth)
			if (m_nLayout[nX + m_nWidth * nY] == 0)
			{
				if (pComponent->getSize().X > m_nCellWidth)
					m_nCellWidth = m_nCellWidthBuffer + pComponent->getSize().X;
				if (pComponent->getSize().Y > m_nCellHeight)
					m_nCellHeight = m_nCellHeightBuffer + pComponent->getSize().Y;

				pComponent->setPosition(nY * m_nCellHeight, nX * m_nCellWidth);

				m_nLayout[nX + m_nWidth * nY] == 1;
		
				addChild(pComponent);
			}

		setSize(m_nWidth * m_nCellWidth, m_nHeight * m_nCellHeight);
	}
};