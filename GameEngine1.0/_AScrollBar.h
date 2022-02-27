class _AScrollBar :
	public _AComponent
{
private:
	_AButton *m_pButton;
	bool m_bDragActive;


	void onEvent(_Event *pEvent)
	{
		_AComponent::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
		case CONSOLE_MOUSE_EVENT:
		{
			MouseEvent *pMouseEvent = pEvent->get<MouseEvent>();
			switch (m_pButton->getState())
			{
			case LEFT_PRESSED:
				if (!m_bDragActive)
				{
					m_bDragActive = true;
				}
				else
				{
					Vector2 CurrentMousePosition = pMouseEvent->getState().Position;
					if (CurrentMousePosition.Y >= getMin().Y
						&& CurrentMousePosition.Y <= getMax().Y - 1)
					{
						m_pButton->setPosition(CurrentMousePosition.Y - getMin().Y, m_pButton->getPosition().X);
					}
					if (!pMouseEvent->getState().bLeftButtonDown)
						m_bDragActive = false;

					//	getParent<_AComponent>()->constructBase(pBuffer);

				}
				break;
			}
			break;
		}
		}
	}
	//	position based on size of bar Y = 0 - maxSize
	//		mouseover
	//		mousepressed
	//			drag on move - along axis
	//	
	//	
	//	onEvent()
	//		new position as percent
	//
	//		parent handles
	//			renders current window based on position	
	//	
public:
	_AScrollBar(int nWidth, int nHeight, int nPosX, int nPosY) :
		m_bDragActive(false),
		_AComponent(nWidth, nHeight, nPosX, nPosY)
	{
		m_pButton = new _AButton("X");
		m_pButton->setPosition(1, 0);
		m_pButton->setToggle(false);
		addComponent(m_pButton);
		registerListener(this, CONSOLE_MOUSE_EVENT);
		registerListener(this, GUI_EVENT);
		setBGColor(BG_DARKGREY);
	}

	_AScrollBar() :
		m_bDragActive(false),
		_AComponent()
	{
		m_pButton = new _AButton("X");
		m_pButton->setPosition(1, 0);
		m_pButton->setToggle(false);
		addComponent(m_pButton);
		registerListener(this, CONSOLE_MOUSE_EVENT);
		registerListener(this, GUI_EVENT);
		setBGColor(BG_LIGHTGREY);
	}

	void init()
	{
		setSize(getParent<_AComponent>()->getSize().Y - 2, 1 );
		setPosition(1, getParent<_AComponent>()->getSize().X - 1);
	}

	float getScrollPosition()
	{
		return (m_pButton->getPosition().Y - Position.Y) / getSize().Y;
	}
};
