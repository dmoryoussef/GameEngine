class TileMapWindow :
	public _AWindow
{
private:
	BaseNode *m_pTileMaps;
	Vector2 MousePosition;
	BaseTile *pCurrentTile;

	void constructComponent(BaseNode *pGameData)
	{
		if (pCurrentTile)
		{
			set(pCurrentTile->getPosition().formatted(), 2, 2, currentColor());
			set(pCurrentTile->getType(), 10, 2, currentColor());
		}

			
		/*while (m_pTileMaps->isIterating())
		{

			float fTotal = 0;

			if (HeightMap *pCurrent = m_pTileMaps->getChild<HeightMap>())
			{
				if (MousePosition.X < pCurrent->getSize().X && MousePosition.Y < pCurrent->getSize().Y)
				{
					fTotal = fTotal + pCurrent->getTile(MousePosition)->getValue();
					set("HEIGHT: " + toString<float>(pCurrent->getTile(MousePosition)->getValue()), 2, 2, DefaultColor());
				}
			}

			if (WaterMap *pCurrent = m_pTileMaps->getChild<WaterMap>())
			{
				if (MousePosition.X < pCurrent->getSize().X && MousePosition.Y < pCurrent->getSize().Y)
				{
					fTotal = fTotal + pCurrent->getTile(MousePosition)->getValue();
					set("WATER: " + toString<float>(pCurrent->getTile(MousePosition)->getValue()), 3, 2, DefaultColor());
				}

			}

			set("TOTAL: " + toString<float>(fTotal), 4, 2, DefaultColor());
		}*/
	}

	void onEvent(_Event *pEvent)
	{
		_AWindow::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			/*case MOUSEWORLD_EVENT:
			{
				MousePosition = pEvent->get<MouseWorldEvent>()->getWorldPosition();
				if (MousePosition.Y < 0)
					MousePosition.Y = 0;
				if (MousePosition.X < 0)
					MousePosition.X = 0;

			} break;*/

			case BASENODE_EVENT:
			{
				//	TODO:  change this to a vector of potential BaseTiles
				//	add tiles to vector
				//	to be handled in constructComponent later
				BaseTile* pTile = pEvent->get<BaseNodeEvent>()->getBaseNode<BaseTile>();
				if (pTile)
				{
					if (pTile->isMouseOver())
						pCurrentTile = pTile;
					else
						pCurrentTile = NULL;
				}
			}
		}
	}

public:
	TileMapWindow(BaseNode *pTileMaps) :
		m_pTileMaps(pTileMaps),
		_AWindow() 
	{
		m_nAlignment = ALIGN_RIGHT;
		registerListener(this, MOUSEWORLD_EVENT);
		registerListener(this, BASENODE_EVENT);
		setSize(25, 30);
		setText("TILE DETAILS");
	}
};