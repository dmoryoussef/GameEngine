
class _AMultiSelectComboButton :
	public _AComponent
{
protected:
	void constructBase()
	{
	}

	void onEvent(_Event *pEvent)
	{
		_AComponent::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
		}
	}

public:
	_AMultiSelectComboButton(int nPosX, int nPosY) :
		_AComponent(0, 0, nPosX, nPosY){};

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
		setSize(nNewWidth, getSize().trunc().Y + pComponent->getSize().trunc().Y);
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

class _ABar :
	public _AComponent
{
	//	gives graphic output of a bar from 1-100%
	//	uneditable
};

class _ATextLabel :
	public _AComponent
{
private:

	void constructBase()
	{
		
			set(m_strText, 0, 0, BG_BLACK + FG_WHITE);
	}

public:
	_ATextLabel(string strText) :
		_AComponent(1, strText.size(), 0, 0)
	{
		setText(strText);
	};


};