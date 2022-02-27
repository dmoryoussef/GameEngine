class UserController :
	public _GComponent
{
private:
	//	map this controller component to physical controller: gamepad 0 - 3, and or keyboard = 4?, mouse?
	int m_nControllerId;

	void onEvent(_Event *pEvent)
	{
		_GComponent::onEvent(pEvent);
		//	check for events
		//	create action events
		switch (pEvent->m_eType)
		{
			//	controller event
			//	get controller id
			//	if controller id === this.id
			//		handle event
			case GAMEPAD_EVENT:
			{
				if (pEvent->get<GamePadEvent>()->getState().nIndex == m_nControllerId)
				{
					GamePad Controller = pEvent->get<GamePadEvent>()->getState();
					float LeftStickX = Controller.clearDeadzone(Controller.LeftStickX);
					float LeftStickY = Controller.clearDeadzone(Controller.LeftStickY);
					float RightStickX = Controller.clearDeadzone(Controller.RightStickX);
					float RightStickY = Controller.clearDeadzone(Controller.RightStickY);
					//if (controller.Up)
					//{
					//	//	move up
					//	addEvent(new ControllerEvent({ -.010, 0, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//}
					//if (controller.Down)
					//{
					//	//	move down
					//	addEvent(new ControllerEvent({ .010, 0, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//}
					//if (controller.Left)
					//{
					//	// move left
					//	addEvent(new ControllerEvent({ 0, -.010, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//}
					//if (controller.Right)
					//{
					//	// move right
					//	addEvent(new ControllerEvent({ 0, .010, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//}

					//if (LeftStickX != 0 || LeftStickY != 0 || RightStickX != 0 || RightStickY != 0)
					{
						float fMoveSpeed = 0.10;
						float fRotateSpeed = 0.04;
						Vector3 translate(LeftStickY * fMoveSpeed, LeftStickX * fMoveSpeed, 0.0);
						Vector3 rotate(RightStickX * fRotateSpeed, RightStickY * fRotateSpeed, 0.0);
						addEvent(new TransformUpdateEvent(translate, rotate, m_pParent));
					}
				}
			}
			break;

			case MOUSEWORLD_EVENT:
			{
				//	if right button pressed
				//		entity is selected
				//			entity has pathing behavior/component
				
				//		addEvent(new PathingCommandEvent(MouseWOrldPosition));
			}
			break;

			case CONSOLE_KEYBOARD_EVENT: 
			{
				if (m_nControllerId == 4)
				{
					//if (pEvent->get<KeyboardEvent>()->isKeyDown())
					//{
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'w' || pEvent->get<KeyboardEvent>()->getKey() == 'W')
					//	{
					//		//	move up
					//		addEvent(new ControllerEvent({ -.10, 0, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//	}
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 's'|| pEvent->get<KeyboardEvent>()->getKey() == 'S')
					//	{
					//		//	move down
					//		addEvent(new ControllerEvent({ .10, 0, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//	}
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'a' || pEvent->get<KeyboardEvent>()->getKey() == 'A')
					//	{
					//		// move left
					//		addEvent(new ControllerEvent({ 0, -.10, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//	}
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'd' || pEvent->get<KeyboardEvent>()->getKey() == 'D')
					//	{
					//		// move right
					//		addEvent(new ControllerEvent({ 0, .10, 0 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//	}

					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'r' || pEvent->get<KeyboardEvent>()->getKey() == 'R')
					//	{
					//		//	move away
					//		addEvent(new ControllerEvent({ 0, 0, .10 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//	}
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'f' || pEvent->get<KeyboardEvent>()->getKey() == 'F')
					//	{
					//		//	move closer
					//		addEvent(new ControllerEvent({ 0, 0, -.10 }, { 0.0, 0.0, 0.0 }, m_pParent));
					//	}

					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'i')
					//	{
					//		//	key up
					//		addEvent(new ControllerEvent({ 0.0, 0.0, 0.0 }, { 0.0, 0.1, 0.0 }, m_pParent));
					//	}
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'k')
					//	{
					//		//	key down
					//		addEvent(new ControllerEvent({ 0.0, 0.0, 0.0 }, { 0.0, -0.1, 0.0 }, m_pParent));
					//	}
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'j')
					//	{
					//		//	key left
					//		addEvent(new ControllerEvent({ 0.0, 0.0, 0.0 }, { 0.1, 0.0, 0.0 }, m_pParent));
					//	}
					//	if (pEvent->get<KeyboardEvent>()->getKey() == 'l')
					//	{
					//		//	key right
					//		addEvent(new ControllerEvent({ 0.0, 0.0, 0.0 }, { -0.1, 0.0, 0.0 }, m_pParent));
					//	}
					//}
				}
					
			}
			break;
		}
	}

	void draw(AFrame *pFrame)
	{
		pFrame->set("Controller ID: " + toString<int>(m_nControllerId), 2, 2, FG_WHITE + BG_BLACK);
	}
	 

public:
	UserController(int Id) :
		m_nControllerId(Id),
		_GComponent("UserController")
	{
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		registerListener(this, GAMEPAD_EVENT);
	};

	void update(float fDeltaTime)
	{
		m_nControllerId = m_nControllerId;
	}

};