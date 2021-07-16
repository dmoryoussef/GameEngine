class CameraWindow :
	public _AWindow
{
private:
	BaseNode *m_pCamera;
	Vector2 PreviousMousePosition;
	bool m_bDrag;
	bool topdown;
	_ARenderer2D renderer;

	int z, x;

	//	camera angle/direction facing
	//		top down = convert z -> y
	//		side = y -> y
	//			left to right = no x coversion
	//			right to left = x -> -x

	string getViewType()
	{
		if (topdown)
			return "TOP_DOWN";
		
		return "SIDE";
	}
	
	void drawCoordinates()
	{
		Vector3 Position3 = m_pCamera->getChild<Transform3D>()->getPosition();
		Vector2 Size2 = getSize();
		Vector2 Position2(Position3.Y, Position3.X);	// for size view
		if (topdown)
		{
			//	use z as y, x
			Position2.Y = Position3.Z;
		}

		// for position to window width
		for (int nX = 1; nX < Size.X - 1; nX++)
			set(" ", 1, nX, BG_DARKGREY);
		
		for (int nX = 1; nX < Size.X - 1; nX++)
			if ((int(Position2.X + nX)) % 5 == 0)
				set(toString<int>(Position2.X + nX), 1, nX, BG_DARKGREY + FG_WHITE);

		for (int nY = 1; nY < Size.Y - 1; nY++)
			set(" ", nY, 1, BG_DARKGREY);
		
		for (int nY = 1; nY < Size.Y - 1; nY++)
			if (int((Position2.Y + nY)) % 5 == 0)
				set(toString<int>(Position2.Y + nY), nY, 1, BG_DARKGREY + FG_WHITE);
		
	}

	void renderEntities(BaseNode *pGameData)
	{
		
		renderer.Render2D(pGameData, this);

			/*if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
				renderer.Render3D(pEntities, this, m_pCamera);*/

			/*
			if (Transform3D *pTransform = pGameData->getCurrent()->getChild<Transform3D>())
				if (Render *pRender = pGameData->getCurrent()->getChild<Render>())
					if (topdown)
					{
						// convert entity 3d position into 2d for top down render
						Vector2 EntityPosition = Vector2(pTransform->getPosition().Z, pTransform->getPosition().X);
						Vector2 CameraMin = Vector2(m_pCamera->getChild<Transform3D>()->getPosition().Z, m_pCamera->getChild<Transform3D>()->getPosition().X);
						Vector2 CameraMax = CameraMin + Size; // window size
						
						if (EntityPosition > CameraMin && EntityPosition < CameraMin)

							if (EntityPosition > CameraMin
								&& EntityPosition < CameraMax)
							{
								set('@', EntityPosition.Y, EntityPosition.X);    //	render at position + camera position
							}
					}
					else
					{
						// convert entity 3d position into 2d for top down render
						Vector2 EntityPosition = Vector2(pTransform->getPosition().Y, pTransform->getPosition().X);
						Vector2 CameraMin = Vector2(m_pCamera->getChild<Transform3D>()->getPosition().Y, m_pCamera->getChild<Transform3D>()->getPosition().X);
						Vector2 CameraMax = CameraMin + Size; // window size

						//if (entity is inside min max of window)

							if (EntityPosition > CameraMin
								&& EntityPosition < CameraMax)
							{
								set('@', EntityPosition.Y, EntityPosition.X);    //	render at position + camera position
							}
							}
				}
			*/
	}

	void draw(BaseNode *pGameData)
	{
		renderEntities(pGameData);
		//	drawCoordinates();
	}

	void startDrag(Vector2 Current)
	{
		if (m_bMouseOver)
		{
			m_bDrag = true;
			PreviousMousePosition = Current;
		}
	}

	void updateDrag(Vector2 Current)
	{
		Vector2 DeltaPos = PreviousMousePosition - Current;
		Vector3 CPosition = m_pCamera->getChild<Transform3D>()->getPosition();
		PreviousMousePosition = Current;
		//	based on camera rotation
		//	convert back to vect3
		if (topdown)	// camera specific
		{
			Vector3 NewPosition = Vector3(CPosition.X + DeltaPos.X, 
										  DeltaPos.Y + CPosition.Y, 
										  CPosition.Z);
			m_pCamera->getChild<Transform3D>()->setPosition(NewPosition);
		}
		//	side
		else
		{
			Vector3 NewPosition = Vector3(CPosition.X + DeltaPos.X, DeltaPos.Y + CPosition.Y, CPosition.Z);
			m_pCamera->getChild<Transform3D>()->setPosition(NewPosition);
		}
	}

	void onEvent(_Event *pEvent)
	{
		_AWindow::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case CONSOLE_KEYBOARD_EVENT:
				if ((pEvent->get<KeyboardEvent>()->getKey() == 'a') && (pEvent->get<KeyboardEvent>()->isKeyDown()))
				{
					x = x - 1;
				}
				if ((pEvent->get<KeyboardEvent>()->getKey() == 'd') && (pEvent->get<KeyboardEvent>()->isKeyDown()))
				{
					x = x + 1;
				}
				if ((pEvent->get<KeyboardEvent>()->getKey() == 's') && (pEvent->get<KeyboardEvent>()->isKeyDown()))
				{
					z = z - 1;
				}
				if ((pEvent->get<KeyboardEvent>()->getKey() == 'w') && (pEvent->get<KeyboardEvent>()->isKeyDown()))
				{
					z = z + 1;
				}
				break;
			case CONSOLE_MOUSE_EVENT:
			{
				if (!m_bDragActive)
				{
					Vector2 Current = pEvent->get<MouseEvent>()->getPosition();
					{
						bool bMouseDown = pEvent->get<MouseEvent>()->isLeftButtonDown();
						if (!m_bDrag)
						{
							if (bMouseDown)
								startDrag(Current);
						}
						else
						{
							if (bMouseDown)
								updateDrag(Current);
							else
								m_bDrag = false;
						}
					}
				}
		
				break;
			}
		}
	}
		

public:
	CameraWindow(BaseNode *pCamera, bool top) :
		topdown(top),
		PreviousMousePosition(),
		m_bDrag(false),
		z(1),
		x(25),
		_AWindow(50, 100, 2, 2) 
	{
		m_bDraggable = true;
		m_pCamera = pCamera;
		setTitle(pCamera->getName() + " " + getViewType());
	}

	CameraWindow(int nPosY, int nPosX, BaseNode *pCamera, bool top) :
		topdown(top),
		z(5),
		x(55),
		_AWindow(50, 100, nPosY, nPosX)
	{
		m_bDraggable = true;
		m_pCamera = pCamera;
		setTitle(pCamera->getName() + " " + getViewType());
	}
};