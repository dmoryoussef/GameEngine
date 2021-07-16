class _ARenderer2D
{
private:
	float fTheta;

	Mesh3D *pCube1; 

	APixel getGreyscaleColor(float fValue)
	{
		int BG_Color = 0;
		int FG_Color = 0;
		char sym = 0;
		//	convert float range of { 0.0 , 1.0 }
		//	to int value of range { 1, 13 }
		int nValue = fValue * 12;

		switch (nValue)
		{
			case 0: BG_Color = BG_BLACK; FG_Color = FG_BLACK; sym = PIXEL_SOLID; 
				break;
			case 1: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_QUARTER; 
				break;
			case 2: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_HALF; 
				break;
			case 3: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_THREEQUARTER; 
				break;
			case 4: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_SOLID; 
				break;
			case 5: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_QUARTER; 
				break;
			case 6: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_HALF; 
				break;
			case 7: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_THREEQUARTER; 
				break;
			case 8: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_SOLID; 
				break;
			case 9:  BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_QUARTER; 
				break;
			case 10: BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_HALF; 
				break;
			case 11: BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_THREEQUARTER; 
				break;
			case 12: BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_SOLID;
				break;
		}
		
		return APixel(sym, BG_Color + FG_Color);
	}

	void MultiplyMatrixVector(Vector3 &i, Vector3 &o, mat4x4 &m)
	{
			o.X = i.X * m.m[0][0] + i.Y * m.m[1][0] + i.Z * m.m[2][0] + m.m[3][0];
			o.Y = i.X * m.m[0][1] + i.Y * m.m[1][1] + i.Z * m.m[2][1] + m.m[3][1];
			o.Z = i.X * m.m[0][2] + i.Y * m.m[1][2] + i.Z * m.m[2][2] + m.m[3][2];
		float w = i.X * m.m[0][3] + i.Y * m.m[1][3] + i.Z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.X /= w;
			o.Y /= w; 
			o.Z /= w;
		}
	}

	Polygon2D square;

public:
	_ARenderer2D() :
		fTheta(30)
	{
		pCube1 = new Mesh3D("cube.obj");
	};
	~_ARenderer2D()
	{
		delete pCube1;
	}


	void Render2D(BaseNode *pGameData, AFrame *pBuffer)
	{
		if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
		{
			while (pEntities->isIterating())
			{
				if (Transform3D *pTransform = pEntities->getCurrent()->getChild<Transform3D>())
					if (Mesh2D *pMesh = pEntities->getCurrent()->getChild<Mesh2D>())
					{
						Polygon2D Poly = pMesh->getPoly();
						Poly.scale({ pTransform->getScale().Y, pTransform->getScale().X });
						Poly.rotate({ pTransform->getRotation().X });
						Poly.translate({ pTransform->getPosition().Y, pTransform->getPosition().X });
						Poly.draw(pBuffer);
					}
			}
		}
		
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
};