class ExplorerWindow :
	public _AWindow
{
	// on handling button event
	//	run onEvent
	//	handle base events
	//	check for gui_event
	//	check if event is button_event
	//	check button states
	class BaseNodeButton :
		public _AButton
	{
		private:
			BaseNode *m_pParentWindow;
			BaseNode *m_pBaseNode;
		public:
			BaseNodeButton(BaseNode *pBaseNode, BaseNode *pParentWindow) :
				m_pBaseNode(pBaseNode),
				m_pParentWindow(pParentWindow),
				_AButton(pBaseNode->getName()) {}

			BaseNode *getParentWindow()
			{
				return m_pParentWindow;
			}
			BaseNode *getBaseNode()
			{
				return m_pBaseNode;
			}
	};

	class BaseNodeComboButton :
		public _ASingleSelectComboButton
	{
	private:
		BaseNode *m_pBaseNode;
		BaseNode *m_pChildComboButton;
	public:
		BaseNodeComboButton(BaseNode *pBaseNode) :
			m_pBaseNode(pBaseNode),
			m_pChildComboButton(NULL),
			_ASingleSelectComboButton() 
		{
			
		}

		~BaseNodeComboButton()
		{
			delete m_pChildComboButton;
		}

		void setChildComponent(BaseNode *pChild)
		{
			m_pChildComboButton = pChild;
		}

		BaseNode *getBaseNode()
		{
			return m_pBaseNode;
		}
	};

private:
	BaseNode *m_pRootNode;
	BaseNodeComboButton *m_pComboButton;

	void onEvent(_Event *pEvent)
	{
		_AWindow::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case GUI_EVENT:
			{
				if (pEvent->get<_AGUIEvent>()->getComponent<_AComponent>()->getState() == DEFAULT)
				{
					if (BaseNodeButton *pButton = pEvent->get<_AGUIEvent>()->getComponent<BaseNodeButton>())
					{
						if (pButton->getParentWindow() == this)
						{
							//	clear any child windows, so it can only have the one
							while (isIterating())
							{
								if (ExplorerWindow *pWindow = getCurrent<ExplorerWindow>())
								{
									if (pWindow->getBaseNode() == pButton->getBaseNode())
									{
										removeCurrent();
									}
								}
							}
						}
					}
				}

				if (pEvent->get<_AGUIEvent>()->getComponent<_AComponent>()->getState() == LEFT_RELEASED)
				{
					if (BaseNodeButton *pButton = pEvent->get<_AGUIEvent>()->getComponent<BaseNodeButton>())
					{
						if (pButton->getParentWindow() == this)
						{
							// add new window
							ExplorerWindow *pWindow = new ExplorerWindow(pButton->getBaseNode(), ALIGN_OUTSIDE_LEFT);
							addComponent(pWindow);
						}
					}
				}
				
			}
			break;
		}
	}

	void constructComponent(BaseNode *pGameData)
	{
		//	get data from basenode to be placed in this frame
		m_pRootNode->toFrame(this);
	}


public:
	ExplorerWindow(BaseNode *pRootNode, int nAlignment) :
		m_pRootNode(pRootNode),
		_AWindow("EXPLORER", 20, 30, 1, 1) 
	{
		m_nAlignment = nAlignment;
		m_strText = m_pRootNode->getName();
		m_bDisplayTitle = true;
		//	create list of buttons for root note
		m_pComboButton = new BaseNodeComboButton(pRootNode);
		addComponent(m_pComboButton);
		while (m_pRootNode->isIterating())
		{
			m_pComboButton->addComponent(new BaseNodeButton(m_pRootNode->getCurrent(), this));
		}
		m_pComboButton->setAlignment(ALIGN_RIGHT);
		//	when button pressed
		//		create new list of buttons for that list
		//		offset position

		//	BASENODE SPECIFIC:
		//	add buttons?
		//	draw(data)

	}

	BaseNode *getBaseNode()
	{
		return m_pRootNode;
	}

	void update(int nDeltaTime)
	{
		BaseNode::update(nDeltaTime);

		if (m_pRootNode && m_pComboButton)
				if (m_pComboButton->getTotal() != m_pRootNode->getTotal())
				{
					// clear and reset all
					/*remove(m_pComboButton);
					m_pComboButton = new BaseNodeComboButton(m_pRootNode);
					addChild(m_pComboButton);
					while (m_pRootNode->isIterating())
						m_pComboButton->addComponent(new BaseNodeButton(m_pRootNode->getCurrent(), this));
					m_pComboButton->setAlignment(ALIGN_RIGHT);
					*/

					// just remove the button and resize component
					// find button that was removed and delete
					while (m_pComboButton->isIterating())
					{	
						// if button exists but node doesnt:
						if (!m_pRootNode->getChild(m_pComboButton->getCurrent<BaseNodeButton>()->getBaseNode()))
						{
							//	NULL was returned node is not there
							m_pComboButton->removeCurrent();
						}
					}

					// if node exists but button doesnt:
					while (m_pRootNode->isIterating())
					{
						bool bExists = false;
						while (m_pComboButton->isIterating())
						{
							BaseNode *pButtonNode = m_pComboButton->getCurrent<BaseNodeButton>()->getBaseNode();
							BaseNode *pBaseNode = m_pRootNode->getCurrent();
							if (pButtonNode == pBaseNode)
							{
								bExists = true;
							}
						}
						if (bExists == false)
						{
							// no button exists for this node
							//	add now
							m_pComboButton->addComponent(new BaseNodeButton(m_pRootNode->getCurrent(), this));
						}
					}
				}
	}

};