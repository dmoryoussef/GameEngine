class TileMapManager :
	public BaseNode,
	public EventListener
{
private:
	//float getTotal(HeightTile *pHeight, WaterTile *pWater)
	//{
	//	float fHeight = pHeight->getValue();
	//	float fWater = pWater->getValue();
	//	return fHeight + fWater;
	//}

public:
	TileMapManager() :
		BaseNode("TileMapManager") {};

	void update(int nDeltaTime)
	{
		//	 for now, handle map physics here
		//	water flowing
		/*

		variant one - only flow to lowest tile of all neighbors
		if (heightmap.value + watermap.value > neighbor)
			flow down

		variant two - flow to all lower neighbors

		*/

		//if (HeightMap *pHeightMap = getChild<HeightMap>())
		//	if (WaterMap *pWaterMap = getChild<WaterMap>())
		//	{
		//		Vector2 mapSize = pWaterMap->getSize();
		//		for (int nY = 0; nY < mapSize.Y; nY++)
		//			for (int nX = 0; nX < mapSize.X; nX++)
		//			{
		//				WaterTile *pWaterTile = pWaterMap->getTile(nY, nX);
		//				HeightTile *pHeightTile = pHeightMap->getTile(nY, nX);
		//				if (pWaterTile->getValue() > 0.15)
		//				{
		//					//	handle water movement 
		//					//	current velocity and mass
		//					//	check neighbors for height difference

		//					float fLowest = pWaterTile->getValue() + pHeightTile->getValue();
		//					WaterTile *pLowestTile = pWaterTile;
		//					//	check north
		//					float fCurrentTotal = getTotal(pHeightTile->getNorth(), pWaterTile->getNorth());
		//					if (fCurrentTotal < fLowest)
		//					{
		//						pLowestTile = pWaterTile->getNorth();
		//						fLowest = fCurrentTotal;
		//					}
		//					
		//					//	check south
		//					fCurrentTotal = getTotal(pHeightTile->getSouth(), pWaterTile->getSouth());
		//					if (fCurrentTotal < fLowest)
		//					{
		//						pLowestTile = pWaterTile->getSouth();
		//						fLowest = fCurrentTotal;
		//					}
		//					
		//					//	check east
		//					fCurrentTotal = getTotal(pHeightTile->getEast(), pWaterTile->getEast());
		//					if (fCurrentTotal < fLowest)
		//					{
		//						pLowestTile = pWaterTile->getEast();
		//						fLowest = fCurrentTotal;
		//					}
		//					
		//					//	check west
		//					fCurrentTotal = getTotal(pHeightTile->getWest(), pWaterTile->getWest());
		//					if (fCurrentTotal < fLowest)
		//					{
		//						pLowestTile = pWaterTile->getWest();
		//						fLowest = fCurrentTotal;
		//					}

		//					if (pWaterTile != pLowestTile)
		//					{
		//						float fDiff = (pWaterTile->getValue() + pHeightTile->getValue()) - fLowest;

		//						if (fDiff > 1)
		//						{
		//							if (fDiff > pWaterTile->getValue())
		//								fDiff = pWaterTile->getValue();
		//						
		//							float fFlow = fDiff * 0.9;

		//							pLowestTile->addValue(fFlow);
		//							pWaterTile->subValue(fFlow);
		//						}

		//						
		//					}
		//					
		//					
		//				}
		//			}
		//	}

	}

};