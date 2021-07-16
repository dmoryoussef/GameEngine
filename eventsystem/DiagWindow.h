class DiagWindow :
	public _AWindow
{
private:
	Vector2 MousePosition;
	int m_nDeltaTime;

	void onEvent(_Event *pEvent)
	{
		_AWindow::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case GUI_EVENT:
			{
				if (pEvent->get<_AGUIEvent>()->getEventType() == BUTTON_EVENT)
				{
					if (_AButton *pButton = pEvent->get<_AGUIEvent>()->getComponent<_AButton>())
					{
						string str = pButton->getText();
						if (str == "TOP_DOWN CAMERA")
						{
							if (pButton->getState() == LEFT_RELEASED)
							{
								addEvent(new _AGUIEvent(CAMERA_WINDOW_EVENT, NULL, true));
							}
						}
						if (str == "SIDE CAMERA")
						{
							if (pButton->getState() == LEFT_RELEASED)
							{
								addEvent(new _AGUIEvent(CAMERA_WINDOW_EVENT, NULL, false));
							}
						}
					}
				}
			}
			break;

			case CONSOLE_MOUSE_EVENT:
			{
				MousePosition = pEvent->get<MouseEvent>()->getPosition();
				break;
			}
		}
	}

	string formatMousePosition(Vector2 Position)
	{
		string strPos = toString<int>(Position.trunc().Y) + "x" + toString<int>(Position.trunc().X);
		string strFinal = "";
		strFinal.insert(0, 1, '[');
		strFinal.insert(strFinal.end(), 1, ']');

		strFinal.insert(1, strPos);
		return strFinal;
	}

public:
	DiagWindow() :
	MousePosition(),
	_AWindow("DIAGNOSTICS", 15, 35, 15, 15)		
	{
		m_bDraggable = true;
		m_bDisplayTitle = true;
		setBGColor(BG_DARKTEAL);

		//_AButton *pButton1 = new _AButton("TOP_DOWN CAMERA", 6, 2);
		//pButton1->setToggle(false);
		//addComponent(pButton1);

		//_AButton *pButton2 = new _AButton("SIDE CAMERA", 7, 2);
		//pButton2->setToggle(false);
		//addComponent(pButton2);

		//_ATextBox *pTextBox = new _ATextBox(20, 20, 5, 18);
		//_AScrollBar *pBar = new _AScrollBar(pTextBox->getSize().Y - 2, 1, 1, pTextBox->getSize().X- 1);
		//pTextBox->setText("Pathfinding and Movement are used to move an agent in a game world. Pathfinding algorithms are used for the high level planning; reactive movement algorithms are used between the waypoints marked by the pathfinding algorithm.");
		//pTextBox->addComponent(pBar);
		//pTextBox->setEditable(true);
		//addComponent(pTextBox);
	};


	void update(int nDeltaTime)
	{
		m_nDeltaTime = nDeltaTime;
	}

	void draw(BaseNode *pBaseNode)
	{
		set("FPS", 2, 2, m_nBGColor + m_nFGColor);
		set(toString<int>(1000 / m_nDeltaTime), 2, 6, m_nBGColor + m_nFGColor);

		set("DT", 3, 2, m_nBGColor + m_nFGColor);
		set(toString<int>(m_nDeltaTime), 3, 6, m_nBGColor + m_nFGColor);

		set(formatMousePosition(MousePosition), 4, 2, m_nBGColor + m_nFGColor);
	}

};