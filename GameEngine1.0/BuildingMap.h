class BuildingMap :
	public _TileMap<BuildingTile>
{
private:
	void onEvent(_Event *pEvent)
	{
		switch (pEvent->m_eType)
		{
			case SELECTIONSQUARE_EVENT:
			{
				Vector2 Min = pEvent->get<SelectionSquareEvent>()->getMin();
				Vector2 Max = pEvent->get<SelectionSquareEvent>()->getMax();
					
				for (int nY = Min.Y; nY <= Max.Y; nY++)
					for (int nX = Min.X; nX <= Max.X; nX++)
					{
						if (nY == (int)Min.Y || nY == (int)Max.Y || nX == (int)Min.X || nX == (int)Max.X)
							getTile( nX, nY )->setValue(1);
					}

				break;
			}

			case MOUSEWORLD_EVENT:
			{
				MouseWorldEvent *pWorldEvent = pEvent->get<MouseWorldEvent>();
				if (pWorldEvent->getState().bLeftButtonDown)
				{
					
				}
				break;
			}
		}
	}

public:
	BuildingMap(int nX, int nY) :
		_TileMap({ float(nX), float(nY) }, "WATERMAP")
	{
		registerListener(this, MOUSEWORLD_EVENT);
		registerListener(this, SELECTIONSQUARE_EVENT);
	};


};