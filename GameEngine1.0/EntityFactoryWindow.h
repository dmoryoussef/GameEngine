class EntityFactoryWindow : 
	public _AWindow
{
private:
	_AButton *m_pButton;
	_AMultiSelectComboButton *m_pMultiButton;

	void defaultAll()
	{
		while (m_pMultiButton->isIterating())
		{
			m_pMultiButton->getCurrent<_AButton>()->setState(DEFAULT);
		}
	}

	void onEvent(_Event *pEvent)
	{
		_AWindow::onEvent(pEvent);

		if (pEvent->m_eType == GUI_EVENT)
		{
			if (pEvent->get<_AGUIEvent>()->getComponent() == m_pButton)
			{
				if (m_pButton->getState() == LEFT_RELEASED)
				{
					BaseNode *pNewEntity = new BaseNode("ENTITY");
					while (m_pMultiButton->isIterating())
					{
						if (m_pMultiButton->getCurrent<_AButton>()->getText() == "TRANSFORM" &&
							m_pMultiButton->getCurrent<_AButton>()->getState() == LEFT_RELEASED)
							pNewEntity->addChild(new Transform3D({ 5.5, 5.5, 5 }, { 0, 0, 0 }, { 0, 0, 0 }));
						
						if (m_pMultiButton->getCurrent<_AButton>()->getText() == "ARENDER" &&
							m_pMultiButton->getCurrent<_AButton>()->getState() == LEFT_RELEASED)
							pNewEntity->addChild(new ARender());
						
						if (m_pMultiButton->getCurrent<_AButton>()->getText() == "VELOCITY" &&
							m_pMultiButton->getCurrent<_AButton>()->getState() == LEFT_RELEASED)
							pNewEntity->addChild(new Velocity3D({ 0, 0, 0 }, { 0, 0, 0 }));
					}

					defaultAll();
					
					addEvent(new NewBaseNodeEvent(pNewEntity, NULL));
				}
			}
		}
	}

public:
	EntityFactoryWindow() :
		_AWindow(45, 30, 5, 165) 
	{
		m_bDraggable = true;
		setBGColor(BG_DARKRED);
		setText("ENTITY_FACTORY");

		//	multiselect combo button
		m_pMultiButton = new _AMultiSelectComboButton(3, 3);
		m_pMultiButton->setBGColor(BG_DARKBLUE);
		m_pMultiButton->addComponent(new _AButton("TRANSFORM"));
		m_pMultiButton->addComponent(new _AButton("ARENDER"));
		m_pMultiButton->addComponent(new _AButton("VELOCITY"));

		addComponent(m_pMultiButton);
		//		button for each available component
		//	enter button
		//		create entity
		string text = "EXECUTE";
		_AButton *pButton = new _AButton(3, text.size() + 2, m_pMultiButton->getSize().Y + 1 + m_pMultiButton->getPosition().Y, m_pMultiButton->getPosition().X);
		pButton->setToggle(false);
		pButton->setText(text);
		addComponent(pButton);
		m_pButton = pButton;
	};
};