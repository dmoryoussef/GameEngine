class WaterMap :
	public _TileMap<WaterTile>
{
private:
	void onEvent(_Event *pEvent)
	{
		switch (pEvent->m_eType)
		{
			case MOUSEWORLD_EVENT:
			{
				MouseWorldEvent *pWorldEvent = pEvent->get<MouseWorldEvent>();
				if (pWorldEvent->getState().bLeftButtonDown)
				{
					Vector2 WorldPosition = pWorldEvent->getWorldPosition();
					WaterTile *pTile = getTile(WorldPosition);
					pTile->addValue(1.5);
				}
				break;
			}
		}
	}

public:
	WaterMap(int nX, int nY) :
		_TileMap({float(nX), float(nY) }, "WATERMAP")
	{
		registerListener(this, MOUSEWORLD_EVENT);
		rain(0, 0, Size.Y, Size.X);
	};

	void rain(int minY, int minX, int maxY, int maxX)
	{
		for (int nY = minY; nY < maxY; nY++)
			for (int nX = minX; nX < maxX; nX++)
			{
				getTile(nX, nY)->addValue(1.5);
			}
	}

	void addSpring(int nX, int nY)
	{
		//	add unlimited water source to specific tile location
	}


};