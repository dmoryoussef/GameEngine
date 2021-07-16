
class _AWindow : 
	public _AComponent
{
protected:
	bool m_bDraggable;
	bool m_bDragActive;
	bool m_bDisplayPosition;
	bool m_bDisplayTitle;
	Vector2 StartMousePosition;

	string formatTitle(string strName)
	{
		string strFinal = "";
		strFinal.insert(0, 1, 181);
		strFinal.insert(strFinal.end(), 1, 198);

		strFinal.insert(1, strName);

		return strFinal;
	}

	string formatPosition()
	{
		string strPos = toString<int>(getMin().Y) + "x" + toString<int>(getMin().X);
		string strFinal = "";
		strFinal.insert(0, 1, 181);
		strFinal.insert(strFinal.end(), 1, 198);

		strFinal.insert(1, strPos);

		return strFinal;
	}

	void drag(MouseEvent *pMouseEvent)
	{
		if (!m_bDragActive)
		{
			if (m_bMouseOver)	//	or window underneith will be grabbed too
				if (pMouseEvent->getY() == getMin().Y
					&& pMouseEvent->getX() > getMin().X
					&& pMouseEvent->getX() < getMax().X
					&& pMouseEvent->isLeftButtonDown())
					{
						StartMousePosition = pMouseEvent->getPosition();
						StartMousePosition = StartMousePosition - Position;
						m_bDragActive = true;
					}
		}
		else
		{
			Vector2 CurrentMousePosition = pMouseEvent->getPosition();
			Position = CurrentMousePosition - StartMousePosition;
			if (!pMouseEvent->isLeftButtonDown())
				m_bDragActive = false;
		}
	}


	void onEvent(_Event *pEvent)
	{
		_AComponent::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case CONSOLE_MOUSE_EVENT:
			{
				// convert to component
				//	drag: area, event listener
				//	close: area, event listener, 'x'
				//	resize window, etc
				
				if (m_bDraggable)
					drag(pEvent->get<MouseEvent>());
				
				if (m_bMouseOver && pEvent->get<MouseEvent>()->isLeftButtonDown())
					moveToTop();
				
				break;
			}
		}
	}

	void constructBase()
	{
		int nForgroundColor = FG_DARKGREY;
		if (m_bMouseOver)
			nForgroundColor = FG_WHITE;
		
		int nFinalColor = m_nBGColor + nForgroundColor;
		
		drawBorder(nFinalColor);

		string strPosition = formatPosition();

		if (m_bDisplayPosition)
			set(strPosition, 0, Size.X - (strPosition.size() + 1), nFinalColor);

		if (m_bDisplayTitle)
			set(formatTitle(m_strText), 0, 1, nFinalColor);
	}
	
public:
	_AWindow(int nHeight, int nWidth, int nPosY, int nPosX) :
		m_bDragActive(false),
		m_bDisplayPosition(true),
		m_bDisplayTitle(true),
		m_bDraggable(false),
		_AComponent(nHeight, nWidth, nPosY, nPosX)
	{
		setName("DEFAULT_WINDOW");
		setText("DEFAULT_WINDOW");
	};

	_AWindow(string strTitle, int nHeight, int nWidth, int nPosY, int nPosX) :
		m_bDragActive(false),
		m_bDisplayPosition(true),
		_AComponent(nHeight, nWidth, nPosY, nPosX) 
	{
		setName(strTitle);
		setText(strTitle);
	};

	void setDraggable(bool bDraggable)
	{
		m_bDraggable = bDraggable;
	}
	void setTitle(string strTitle)
	{
		m_strText = strTitle;
	}
	void setDisplayTitle(bool bDisplay)
	{
		m_bDisplayTitle = bDisplay;
	}
	void setDisplayPosition(bool bDisplay)
	{
		m_bDisplayPosition = bDisplay;
	}

	void moveToTop()
	{
		if (getParent())	// makes sure its not the base window, may get rid of this and draw directly to buffer
			{
			//	while not parent != null
			//	get parent
			//	 then move to top
				BaseNode *pParent = getParent();
				pop();
				pParent->addAtEnd(this);
				setParent(pParent);
			}
	}
	void updateMouseOver(Vector2 MousePosition)
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

	void resetMouseOver(_AComponent *pComponent) 
	{
		if (pComponent->isMouseOver())
			m_bMouseOver = false;

		for (_AComponent *pCurrent = pComponent->getStart<_AComponent>();		//	if any (window component) on top is mouse over - reset this 
			pCurrent != NULL;
			pCurrent = pCurrent->getNext<_AComponent>())

			resetMouseOver(pCurrent);
	}

	void setMouseOver(bool bNewMouseOverState)
	{
		if (!m_bDragActive)												//	if not already dragging this window, update mouseover state
		{
			m_bMouseOver = bNewMouseOverState;

			//	if any (window component) on top is mouse over - reset this 
			
			// if top window - reset any other underneith that are mouseover
			
			if (m_bMouseOver == true)
			{
				// reset anything up and under
				//
			}
				/*	for (_AComponent *pCurrent = getPrevious<_AComponent>();		
						pCurrent != NULL;
						pCurrent = pCurrent->getPrevious<_AComponent>())
							resetMouseOver(pCurrent);*/
				
			for (_AComponent *pCurrent = getNext<_AComponent>();		
				pCurrent != NULL;
				pCurrent = pCurrent->getNext<_AComponent>())
					resetMouseOver(pCurrent);

			
		}
	}

	void addComponent(_AComponent *pComponent)
	{
		addChild(pComponent);
	}

};

