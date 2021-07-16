class BaseNodeSelectionComboButton :
	public _ASingleSelectComboButton
{
private:
	BaseNode *m_pBaseNode;
	int m_nCurrentTotal;

	void onEvent(_Event *pEvent)
	{
		_ASingleSelectComboButton::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case GUI_EVENT:
			{
				BaseNode *pBase = dynamic_cast<BaseNode*>(pEvent->get<_AGUIEvent>()->getComponent());
				{
				}
			}
			break;
		}
		// when button clicked, open new window with link to the next node in tree
	}

	void update(int nDeltaTime)
	{
		if (m_nCurrentTotal != m_pBaseNode->getTotal())
			refreshList();
	}

	void refreshList()
	{
		deleteComponents();

		while (m_pBaseNode->isIterating())
			addComponent(new _AButton(m_pBaseNode->getCurrent()->getName()));
	
		m_nCurrentTotal = m_pBaseNode->getTotal();
	}

public:
	BaseNodeSelectionComboButton(BaseNode *pBaseNode, int nY, int nX) :
		m_pBaseNode(pBaseNode),
		m_nCurrentTotal(0),
		_ASingleSelectComboButton(nY, nX) {};

};
