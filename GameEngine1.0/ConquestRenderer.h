class GameRenderer : public ConsoleRender2D
{
public:
	GameRenderer() :
		ConsoleRender2D() {};

	void Render2D(BaseNode *pGameData, BaseNode *pCamera, Vector2 vWorldMin, Vector2 vWorldMax)
	{


		//if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
		//{
		//	while (pEntities->isIterating())
		//	{
		//		if (Transform3D *pTransform = pEntities->getCurrent()->getChild<Transform3D>())
		//		{
		//			if (Poly2D *pMesh = pEntities->getCurrent()->getChild<Poly2D>())
		//			{
		//				/*Polygon2D Poly = pMesh->getPoly();
		//				Poly.scale({ pTransform->getScale().Y, pTransform->getScale().X});
		//				Poly.rotate({ pTransform->getRotation().X });
		//				Poly.translate({ pTransform->getPosition().Y, pTransform->getPosition().X });
		//				Poly.translate(CameraPosition.toVec2());

		//				vector<Vector2> Verticies = Poly.Verticies;
		//				for (int nI = 0; nI < Verticies.size() - 1; nI++)
		//				{
		//					DrawLine(Verticies[nI], Verticies[nI + 1], getGreyscaleColor(1.0));
		//				}

		//				DrawLine(Verticies[Verticies.size() - 1], Verticies[0], getGreyscaleColor(1.0));*/

		//				Vector2 Min(vCameraPosition.X + pTransform->getPosition().X * vCameraPosition.Z, vCameraPosition.Y + pTransform->getPosition().Y * vCameraPosition.Z);
		//				Vector2 Max(vCameraPosition.X + pTransform->getPosition().X * vCameraPosition.Z + 1 * vCameraPosition.Z, vCameraPosition.Y + pTransform->getPosition().Y * vCameraPosition.Z + 1 * vCameraPosition.Z);
		//				DrawQuad(Min.X, Min.Y, Max.X, Max.Y, getGreyscaleColor(1.0));

		//			}
		//			if (ARender *pRender = pEntities->getCurrent()->getChild<ARender>())
		//			{
		//				Vector2 Min(vCameraPosition.X + pTransform->getPosition().X * vCameraPosition.Z, vCameraPosition.Y + pTransform->getPosition().Y * vCameraPosition.Z);
		//				pRender->drawToFrame(m_pTargetBuffer, Min);
		//				//m_pTargetBuffer->set('A', Min.Y, Min.X, FG_WHITE + BG_BLACK);
		//			}

		//		}
		//	}
		//}
	}

	void Render2D(BaseNode *pCamera, AFrame *pBuffer,
		BaseNode *pGameData)
	{
		//	row = dimenson1
		//	column = dimension2
		//	for dimension1 = column = Y, min to max (window 0 to height)
		//		for dimension2 = row = X, min to max (window 0 to width)
		//			camera position Y + local screen Y, camera position x + local screen x
		//				if any part of entity is in this y, x
		//					render it

		/*
		Front Facing =	from	Y.Min - Y.Max
								X.Min - X.Max

		Top Down Facing = from	Z.Max - Z.Min
								X.Min - X.Max

		Bottom Up Facing		Z.Min - Z.Max
								X.Min - X.Max

		Convert Vector3 position to Vector2 screen space
		*/

		/*while (!pGameData->endOfList())
		{
			Vector2 CameraMin = Vector2(pCamera->getChild<Transform3D>()->getPosition().Z, pCamera->getChild<Transform3D>()->getPosition().X);
			Vector2 CameraMax = CameraMin + pBuffer->getSize();

			if (Render *pRender = pGameData->getCurrent()->getChild<Render>())
				if (Transform3D *pTransform = pGameData->getCurrent()->getChild<Transform3D>())
				{
					Vector2 EntityMin = Vector2(pTransform->getPosition().Z, pTransform->getPosition().X);
					Vector2 EntityMax = EntityMin + pRender->getSprite()->getSize();
					if (EntityMax > CameraMin && EntityMin < CameraMax)
					{
						Vector2 RenderScreenPosition = EntityMin - CameraMin;
						pRender->drawToFrame(pBuffer, RenderScreenPosition, EntityMax);
					}
				}

		}*/

	}

	void draw(BaseNode* pGameData, BaseNode* pCamera)
	{
		//	need window size, camera position, camera zoom/scale
		//	in order to clip parts that are off screen 
		Vector3 vCameraPosition = pCamera->getChild<Transform3D>()->getPosition();
		Vector2 vWorldMin = pCamera->getChild<Camera>()->getWorldMin();
		Vector2 vWorldMax = pCamera->getChild<Camera>()->getWorldMax();

		// fix: when scale is small, only grab certain tiles
		//	scale / nX?
		//	scale / nY?
		//	avoids rendering tiles that are too small to see anyway

		if (TileMapManager* pTileMapManager = pGameData->getChild<TileMapManager>())
		{
			
				
				//if (HeightMap *pMap = pTileMapManager->getChild<HeightMap>())
				//{
				//	Vector2 mapSize = pMap->getSize();
				//	if (vWorldMin.Y < 0)
				//		vWorldMin.Y = 0;
				//	if (vWorldMin.X < 0)
				//		vWorldMin.X = 0;
				//	if (vWorldMax.Y > mapSize.Y)
				//		vWorldMax.Y = mapSize.Y;
				//	if (vWorldMax.X > mapSize.X)
				//		vWorldMax.X = mapSize.X;

				//	int TilesRendered = 0;

				//	for (int nY = vWorldMin.Y; nY < vWorldMax.Y; nY++)
				//		for (int nX = vWorldMin.X; nX < vWorldMax.X; nX++)
				//		{
				//			Vector2 Min(vCameraPosition.Y + nY * vCameraPosition.Z, vCameraPosition.X + nX * vCameraPosition.Z);
				//			Vector2 Max(vCameraPosition.Y + nY * vCameraPosition.Z + 1 * vCameraPosition.Z, vCameraPosition.X + nX * vCameraPosition.Z + 1 * vCameraPosition.Z);

				//			{
				//				DrawQuad(Min.Y,
				//					Min.X,
				//					Max.Y,
				//					Max.X,
				//					getGreyscaleColor(pMap->getTile(nY, nX)->getValue()));
				//			}

				//			TilesRendered++;

				//			//	move to bottom of render, to put on top
				//			if (pMap->getTile(nY, nX) == pMap->getMouseOverTile())
				//			{
				//				DrawQuad(Min.Y,
				//					Min.X,
				//					Max.Y,
				//					Max.X,
				//					getGreyscaleColor(100));

				//			}
				//		}

				//	// loop edges

				//	//for (int nI = 0; nI < pMap->getEdges().size(); nI++)
				//	//{
				//	//	Vector2 Start = pMap->getEdges()[nI].Start;
				//	//	Vector2 End = pMap->getEdges()[nI].End;
				//	//	Start = CameraPosition.toVec2() + (Start * CameraPosition.Z);
				//	//	End = CameraPosition.toVec2() + (End * CameraPosition.Z);
				//	//	DrawLine(Start, End, APixel('x', BG_BLACK + FG_LIGHTRED));
				//	//}

				//	//	debug info
				//	//m_pTargetBuffer->set("POLY EDGES: " + toString<int>(pMap->getEdges().size()), 1, 55, FG_WHITE + BG_BLACK);
				//	//m_pTargetBuffer->set("TILES RENDERED: " + toString<int>(TilesRendered), 1, 30, FG_WHITE + BG_BLACK);
				//	m_pTargetBuffer->set("WORLDMIN Y " + toString<float>(vWorldMin.Y), 2, 30, FG_WHITE + BG_BLACK);
				//	m_pTargetBuffer->set("WORLDMAX Y " + toString<float>(vWorldMax.Y), 3, 30, FG_WHITE + BG_BLACK);
				//	m_pTargetBuffer->set("WORLDMIN X " + toString<float>(vWorldMin.X), 4, 30, FG_WHITE + BG_BLACK);
				//	m_pTargetBuffer->set("WORLDMAX X " + toString<float>(vWorldMax.X), 5, 30, FG_WHITE + BG_BLACK);
				//}

				//if (WaterMap *pMap = pTileMapManager->getChild<WaterMap>())
				//{
				//	Vector2 mapSize = pMap->getSize();
				//	if (vWorldMin.Y < 0)
				//		vWorldMin.Y = 0;
				//	if (vWorldMin.X < 0)
				//		vWorldMin.X = 0;
				//	if (vWorldMax.Y > mapSize.Y)
				//		vWorldMax.Y = mapSize.Y;
				//	if (vWorldMax.X > mapSize.X)
				//		vWorldMax.X = mapSize.X;


				//	for (int nY = vWorldMin.Y; nY < vWorldMax.Y; nY++)
				//		for (int nX = vWorldMin.X; nX < vWorldMax.X; nX++)
				//		{
				//			float fValue = pMap->getTile(nY, nX)->getValue();
				//			if (fValue > 0.15)
				//			{
				//				Vector2 Min(vCameraPosition.Y + nY * vCameraPosition.Z, vCameraPosition.X + nX * vCameraPosition.Z);
				//				Vector2 Max(vCameraPosition.Y + nY * vCameraPosition.Z + 1 * vCameraPosition.Z, vCameraPosition.X + nX * vCameraPosition.Z + 1 * vCameraPosition.Z);

				//				//	if water velocity > some value
				//				//		use "flowing water" character "~"

				//				{
				//					DrawQuad(Min.Y,
				//						Min.X,
				//						Max.Y,
				//						Max.X,
				//						getColorscaleColor(fValue));
				//				}
				//			}
				//		}
				//}

				//if (BuildingMap *pMap = pTileMapManager->getChild<BuildingMap>())
				//{
				//	Vector2 mapSize = pMap->getSize();
				//	if (vWorldMin.Y < 0)
				//		vWorldMin.Y = 0;
				//	if (vWorldMin.X < 0)
				//		vWorldMin.X = 0;
				//	if (vWorldMax.Y > mapSize.Y)
				//		vWorldMax.Y = mapSize.Y;
				//	if (vWorldMax.X > mapSize.X)
				//		vWorldMax.X = mapSize.X;

				//	for (int nY = vWorldMin.Y; nY < vWorldMax.Y; nY++)
				//		for (int nX = vWorldMin.X; nX < vWorldMax.X; nX++)
				//		{
				//			float fValue = pMap->getTile(nY, nX)->getValue();
				//			if (fValue > 0)
				//			{
				//				Vector2 Min(vCameraPosition.Y + nY * vCameraPosition.Z, vCameraPosition.X + nX * vCameraPosition.Z);
				//				Vector2 Max(vCameraPosition.Y + nY * vCameraPosition.Z + 1 * vCameraPosition.Z, vCameraPosition.X + nX * vCameraPosition.Z + 1 * vCameraPosition.Z);
				//				{
				//					DrawQuad(Min.Y,
				//						Min.X,
				//						Max.Y,
				//						Max.X,
				//						getGreyscaleColor(100));
				//				}
				//			}

				//		}
				//}

				//if (PathingMap *pMap = pTileMapManager->getChild<PathingMap>())
				//{
				//	DrawQuad(0, 0, nHeight, nWidth, getGreyscaleColor(50));
				//	Vector2 mapSize = pMap->getSize();
				//	if (vWorldMin.Y < 0)
				//		vWorldMin.Y = 0;
				//	if (vWorldMin.X < 0)
				//		vWorldMin.X = 0;
				//	if (vWorldMax.Y > mapSize.Y)
				//		vWorldMax.Y = mapSize.Y;
				//	if (vWorldMax.X > mapSize.X)
				//		vWorldMax.X = mapSize.X;

				//	int TilesRendered = 0;

				//	float padding = 0.09;

				//	for (int nY = vWorldMin.Y; nY < vWorldMax.Y; nY++)
				//		for (int nX = vWorldMin.X; nX < vWorldMax.X; nX++)
				//		{
				//			Vector2 Min((vCameraPosition.Y + nY * vCameraPosition.Z) , (vCameraPosition.X + nX * vCameraPosition.Z) );
				//			Vector2 Max((vCameraPosition.Y + nY * vCameraPosition.Z + 1 * vCameraPosition.Z) , (vCameraPosition.X + nX * vCameraPosition.Z + 1 * vCameraPosition.Z) );

				//			{
				//				DrawQuad(	Min.Y + (padding * vCameraPosition.Z),
				//							Min.X + (padding * vCameraPosition.Z),
				//							Max.Y - (padding * vCameraPosition.Z),
				//							Max.X - (padding * vCameraPosition.Z),
				//							getGreyscaleColor(pMap->getTile(nY, nX)->getValue()));
				//			}

				//			TilesRendered++;

				//			//	move to bottom of render, to put on top
				//			if (pMap->getTile(nY, nX) == pMap->getMouseOverTile())
				//			{
				//				DrawQuad(	Min.Y + (padding * vCameraPosition.Z),
				//							Min.X + (padding * vCameraPosition.Z),
				//							Max.Y - (padding * vCameraPosition.Z),
				//							Max.X - (padding * vCameraPosition.Z),
				//							APixel(' ', FG_LIGHTGREEN + BG_LIGHTGREEN));
				//			}

				//			/*if (vCameraPosition.Z > 6.0)
				//				DrawNum<int>(pMap->getTile(nY, nX)->getValue(), Min.Y + (0.5 * vCameraPosition.Z), Min.X + (0.5 * vCameraPosition.Z), BG_BLACK + FG_YELLOW);*/
				//		}
				//}

			//}
		}
	}
};