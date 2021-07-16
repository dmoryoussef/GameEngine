class _ASingleSelectComboButton :
	public _AComponent
{
	//	list of buttons - only one of the set can be selected/activated a time
	//	container of buttons
	//	active button
protected:
	_AButton *m_pActiveButton;

	void onEvent(_Event *pEvent)
	{
		_AComponent::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case GUI_EVENT:
			{
				if (pEvent->get<_AGUIEvent>()->getEventType() == BUTTON_EVENT)
				{
					if (_AButton *pButton = pEvent->get<_AGUIEvent>()->getComponent<_AButton>())
					{
						string str = pButton->getText();
						if (pButton->getParent() == this)									//	if this button is a descendant of this window
						{
							switch (pButton->getState())
							{
							case LEFT_RELEASED:
								if (m_pActiveButton != pButton
									&& m_pActiveButton != NULL)
									m_pActiveButton->setState(DEFAULT);
								m_pActiveButton = pButton;
								break;
							}
						}
					}
				}
			}
			break;
		}
	}

public:
	_ASingleSelectComboButton() :
		m_pActiveButton(NULL),
		_AComponent(0, 0, 1, 1) 
	{
	};

	_ASingleSelectComboButton(int nPosY, int nPosX) :
		m_pActiveButton(NULL),
		_AComponent(0, 0, nPosY, nPosX)  {};


	void deleteComponent(_AComponent *pComponent)
	{
		for (_AComponent *pCurrent = getStart<_AComponent>(); pCurrent != NULL; pCurrent = pCurrent->getNext<_AComponent>())
		{
			if (pCurrent->getPosition().Y > pComponent->getPosition().Y)
				pCurrent->setPosition(pCurrent->getPosition().Y - pComponent->getSize().Y, pCurrent->getPosition().X);
		}

		remove(pComponent);
	}

	void deleteComponents()
	{
		clearList();
		setSize( 0, 0 );
	}

	void addComponent(_AComponent *pComponent)
	{
		//	add button
		//static_cast<_AButton*>(pComponent);
		//		nPosY = size list(total current buttons)
		//		nPosX = this pos x
		pComponent->setPosition(getTotal(), 0);
		int nNewWidth = Size.X;
		if (Size.X < pComponent->getSize().X)
			nNewWidth = pComponent->getSize().X;
		setSize(getSize().Y + pComponent->getSize().Y, nNewWidth );
		//		height = 1
		//			maybe: other size for special formatting
		//			maybe:	resize this height to match total button height
		//				void getTotalButtonHeight()
		//		width = button text width
		//			maybe: force all buttons to this width
		//				predetermined width or max button width
		//				getMaxButtonWidth
		//			maybe: if button width > this width, resize this component width to button width
		addChild(pComponent);
	}

	void setComponentBackgroundColor(int nColor)
	{
		while (isIterating())
		{
			getCurrent<_AComponent>()->setBGColor(nColor);
		}
	}
};	