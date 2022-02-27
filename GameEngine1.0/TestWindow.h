class TestWindow :
	public _AWindow
{
private:
	BaseNode *pData;

public:
	TestWindow() :
		_AWindow() 
	{
		m_bDraggable = true;

		UILayout *pLayout = new UILayout(2, 2, 1, 0);
		pLayout->setAlignment(ALIGN_LEFT);
		pLayout->addComponent(new _AButton("TEST 1", false), 0, 0);
		pLayout->addComponent(new _AButton("TEST 2", false), 1, 0);
		pLayout->addComponent(new _ATextLabel("LABEL 1"), 0, 1);
		pLayout->addComponent(new _ATextLabel("LABEL 2"), 1, 1);
		addComponent(pLayout);
	};
};