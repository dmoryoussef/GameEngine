class DiagWindow :
	public _AWindow
{
private:
	Vector2 MousePosition;
	float m_fDeltaTime;

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;

	void onEvent(_Event *pEvent)
	{
		_AWindow::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case GAMEPAD_EVENT:
			{
				GamePad Controller = pEvent->get<GamePadEvent>()->getState();
				leftStickX = Controller.clearDeadzone(Controller.LeftStickX);
				leftStickY = Controller.clearDeadzone(Controller.LeftStickY);
				rightStickX = Controller.clearDeadzone(Controller.RightStickX);
				rightStickY = Controller.clearDeadzone(Controller.RightStickY);
				break;
			}

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
				MousePosition = pEvent->get<MouseEvent>()->getState().Position;
				break;
			}
		}
	}

	string formatMousePosition(Vector2 Position)
	{
		string strPos = toString<int>(Position.trunc().X) + "x" + toString<int>(Position.trunc().Y);
		string strFinal = "";
		strFinal.insert(0, 1, '[');
		strFinal.insert(strFinal.end(), 1, ']');

		strFinal.insert(1, strPos);
		return strFinal;
	}

public:
	DiagWindow(int nAlignment) :
	MousePosition(),
	leftStickX(0),
	leftStickY(0),
	rightStickX(0),
	rightStickY(0),
	_AWindow("DIAGNOSTICS", 25, 15, 15, 15)		
	{
		m_bDraggable = true;
		m_bDisplayTitle = true;
		setBGColor(BG_DARKTEAL);
		m_nAlignment = nAlignment;
		registerListener(this, GAMEPAD_EVENT);
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


	void update(float fDeltaTime)
	{
		m_fDeltaTime = fDeltaTime;
	}

	void constructComponent(BaseNode *pBaseNode)
	{
		set("FPS", 2, 2, m_nBGColor + m_nFGColor);
		set(toString<int>(1000 / m_fDeltaTime), 6, 2, m_nBGColor + m_nFGColor);

		set("DT", 2, 3, m_nBGColor + m_nFGColor);
		set(toString<float>(m_fDeltaTime), 6, 3, m_nBGColor + m_nFGColor);

		set(formatMousePosition(MousePosition), 2, 4, m_nBGColor + m_nFGColor);

		set("LEFT STICK  [" + toString<float>(leftStickX) + "x" + toString<float>(leftStickY) + "]", 2, 6, m_nBGColor + m_nFGColor);
		set("RIGHT STICK [" + toString<float>(rightStickX) + "x" + toString<float>(rightStickY) + "]", 2, 7, m_nBGColor + m_nFGColor);
	}

};