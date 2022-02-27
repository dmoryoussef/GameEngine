class HeightMap :
	public _TileMap<HeightTile>
{
private:
	HeightTile *m_pMouseOverTile;

	float getDiamondSample(int nX, int nY, int nSize)
	{
		int nHalfSize = nSize / 2;

		float fA = getTile(nX, nY - nHalfSize)->getValue();
		float fB = getTile(nX, nY + nHalfSize)->getValue();
		float fC = getTile(nX - nHalfSize, nY)->getValue();
		float fD = getTile(nX + nHalfSize, nY)->getValue();

		return (fA + fB + fC + fD) / 4.0;
	}
	float getSquareSample(int nY, int nX, int nSize)
	{
		int nHalfSize = nSize / 2;

		float fA = getTile(nX - nHalfSize, nY - nHalfSize)->getValue();
		float fB = getTile(nX - nHalfSize, nY + nHalfSize)->getValue();
		float fC = getTile(nX + nHalfSize, nY - nHalfSize)->getValue();
		float fD = getTile(nX + nHalfSize, nY + nHalfSize)->getValue();

		return (fA + fB + fC + fD) / 4.0;
	}
	void DiamondSquare(int nSampleSize, int nMaxRandom, float fRandomScale)
	{		
		while (nSampleSize > 1)
		{
			int nHalfStep = nSampleSize / 2;

			for (int nY = nHalfStep; nY < Size.Y + nHalfStep; nY += nSampleSize)
				for (int nX = nHalfStep; nX < Size.X + nHalfStep; nX += nSampleSize)
				{
					getTile(nX, nY)->setValue(getSquareSample(nX, nY, nSampleSize) + (rand() % nMaxRandom * fRandomScale));
					
					//pEvents->add(new Tile2dUpdatedEvent(m_pParentTileMap->getTile(nY, nX)));
				}

			for (int nY = 0; nY < Size.Y; nY += nSampleSize)
				for (int nX = 0; nX < Size.X; nX += nSampleSize)
				{
					getTile(nX, nY + nHalfStep)->setValue(getDiamondSample(nX, nY + nHalfStep, nSampleSize) + (rand() % nMaxRandom * fRandomScale));
					
					//pEvents->add(new Tile2dUpdatedEvent(m_pParentTileMap->getTile(nY, nX + nHalfStep)));

					getTile(nX + nHalfStep, nY)->setValue(getDiamondSample(nX + nHalfStep, nY, nSampleSize) + (rand() % nMaxRandom * fRandomScale));
					
					//pEvents->add(new Tile2dUpdatedEvent(m_pParentTileMap->getTile(nY + nHalfStep, nX)));

				}

			nSampleSize /= 2;
			fRandomScale /= 2.0;
		}
	}

	void onEvent(_Event *pEvent)
	{
		switch (pEvent->m_eType)
		{
			/*case MOUSEWORLD_EVENT:
			{
				Vector2 vWorldPosition = pEvent->get<MouseWorldEvent>()->getWorldPosition();
				m_pMouseOverTile = getTile(vWorldPosition);
			} break;*/
		}
	}

public:
	HeightMap(int nX, int nY) :
		_TileMap({ (float)nX, (float)nY }, "HEIGHTMAP") 
	{
		int nMaxHeight = 100;
		srand(0);

		for (int nY = 0; nY < Size.Y; nY++)
			for (int nX = 0; nX < Size.X; nX++)
			{
				HeightTile *pCurrent = getTile(nX, nY);

				pCurrent->setValue(float(rand() % nMaxHeight));
			}

		int nSampleSize = 32;		//	4, 16, 32, 64 ... size
		int nMaxRandom = 1;			// > 0
		float fRandomScale = 4.5;

		DiamondSquare(nSampleSize, nMaxRandom, fRandomScale);
	};

	HeightTile *getMouseOverTile()
	{
		return m_pMouseOverTile;
	}

};