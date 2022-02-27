class SelectionSquare : public _AComponent
{
private:
	Vector2 Start;
	Vector2 End;

	bool m_bMouseButtonPressed;
	bool m_bKeyboardButtonPressed;

	void updateSquare(Vector2 Max)
	{
		End = Max;
	}

	void draw(BaseNode *pGameData)
	{
		Vector2 min = Start;
		Vector2 max = End;


		
		set("TEST", 15, 15, FG_WHITE + BG_BLACK);

		for (int nY = min.Y; nY < max.Y + 1; nY++)
			for (int nX = min.X; nX < max.X + 1; nX++)
			{
				if (nY == min.Y || nY == max.Y - 1 || nX == min.X || nX == max.X - 1)
				{
					set("x", nX, nY, DefaultColor());
				}
			}
	}


public:
	SelectionSquare(Vector2 start, Vector2 position, Vector2 size) :
		m_bKeyboardButtonPressed(false),
		m_bMouseButtonPressed(false),
		Start(start),
		End(start) ,
		_AComponent(position.X, position.Y, size.X, size.Y)
	{
		registerListener(this, MOUSEWORLD_EVENT);
	};

	void onEvent(_Event*pEvent)
	{
		_AComponent::onEvent(pEvent);
		switch (pEvent->m_eType)
		{
			case CONSOLE_KEYBOARD_EVENT:
			{
					
				break;
			}

			case MOUSEWORLD_EVENT:
			{
				MouseState mouseState = pEvent->get<MouseWorldEvent>()->getState();
				if (mouseState.bRightButtonDown)
				{
					End = mouseState.Position;
					Vector2 min = Start;
					if (End > Start)
						min = End;

					Vector2 max = End;
					if (Start > End)
						max = Start;

					Position = min;
					Size = max;
				}
					
				if (!mouseState.bRightButtonDown)
				{
					//	addEvent(Min(Start, End), Max(Start, End));
					End = mouseState.Position;
				}

				break;
			}
		}

		

	}

	//void render(Frame *pFrame)
	//{
	//	if (m_bActive)
	//	{
	//		//	Render Square
	//		for (int nY = Min().Y; nY <= Max().Y && nY < pFrame->getHeight(); nY++)
	//			for (int nX = Min().X; nX <= Max().X && nX < pFrame->getWidth(); nX++)
	//				if (nY == Min().Y || nY == Max().Y || nX == Min().X || nX == Max().X)
	//				{
	//					//	outlined square:
	//					pFrame->insertChar('.', nY, nX, FOREGROUND_WHITE + BACKGROUND_BLACK);
};