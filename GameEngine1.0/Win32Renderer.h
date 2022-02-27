class Win32Renderer
{
private:
	Win32BackBuffer *m_pTargetBuffer;
	int nWidth;
	int nHeight;
	int nBytesPerPixel;

	inline uint32_t Color(float fBlue, float fGreen, float fRed, float fAlpha)
	{

		uint32_t color = ((int)(fBlue * 255) << 0) |
						 ((int)(fGreen * 255) << 8) |
						 ((int)(fRed * 255) << 16) |
						 ((int)(fAlpha * 255) << 24);

			return color;
	}

	void DrawPoint(int nY, int nX, uint32_t Color)
	{
		if (nX > 0 && nX < nWidth && nY > 0 && nY < nHeight)
		{
			uint8_t *pPixel = (uint8_t*)m_pTargetBuffer->pBuffer +
				nX * nBytesPerPixel +
				nY * nWidth * nBytesPerPixel;

			*(uint32_t*)pPixel = Color;
		}
	}
	void DrawLine(Vector2 Start, Vector2 End, uint32_t nColor)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = End.X - Start.X;
		dy = End.Y - Start.Y;
		dx1 = abs(dx);
		dy1 = abs(dy);
		px = 2 * dy1 - dx1;
		py = 2 * dx1 - dy1;

		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = Start.X;
				y = Start.Y;
				xe = End.X;
			}
			else
			{
				x = End.X;
				y = End.Y;
				xe = Start.X;
			}
			DrawPoint(y, x, nColor);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;

				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				DrawPoint(y, x, nColor);
			}
		}

		else
		{
			if (dy >= 0)
			{
				x = Start.X;
				y = Start.Y;
				ye = End.Y;
			}
			else
			{
				x = End.X;
				y = End.Y;
				ye = Start.Y;
			}
			DrawPoint(y, x, nColor);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);

				}
				DrawPoint(y, x, nColor);
			}
		}

	}
	void DrawTriangle(Triangle Tri, uint32_t nColor)
	{
		DrawLine({ Tri.A.Y, Tri.A.X }, { Tri.B.Y, Tri.B.X }, nColor);
		DrawLine({ Tri.B.Y, Tri.B.X }, { Tri.C.Y, Tri.C.X }, nColor);
		DrawLine({ Tri.C.Y, Tri.C.X }, { Tri.A.Y, Tri.A.X }, nColor);
	}
	void DrawTriangle(Vector3 a, Vector3 b, Vector3 c, uint32_t nColor)
	{
		DrawLine({ a.Y, a.X }, { b.Y, b.X }, nColor);
		DrawLine({ b.Y, b.X }, { c.Y, c.X }, nColor);
		DrawLine({ c.Y, c.X }, { a.Y, a.X }, nColor);
	}
	void FillTriangle(Triangle triangle, uint32_t Color)
	{
		int x1 = triangle.A.X;
		int y1 = triangle.A.Y;
			
		int x2 = triangle.B.X;
		int y2 = triangle.B.Y;
		
		int x3 = triangle.C.X;
		int y3 = triangle.C.Y;
		
		auto SWAP = [](int &x, int &y) { int t = x; x = y; y = t; };

		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				DrawPoint(ny, i, Color);
		};



		int t1x, t2x, y, minx, maxx, t1xp, t2xp;

		bool changed1 = false;

		bool changed2 = false;

		int signx1, signx2, dx1, dy1, dx2, dy2;

		int e1, e2;

		// Sort vertices

		if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }

		if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }

		if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }



		t1x = t2x = x1; y = y1;   // Starting points

		dx1 = (int)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }

		else signx1 = 1;

		dy1 = (int)(y2 - y1);



		dx2 = (int)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }

		else signx2 = 1;

		dy2 = (int)(y3 - y1);



		if (dy1 > dx1) {   // swap values

			SWAP(dx1, dy1);

			changed1 = true;

		}

		if (dy2 > dx2) {   // swap values

			SWAP(dy2, dx2);

			changed2 = true;

		}



		e2 = (int)(dx2 >> 1);

		// Flat top, just process the second half

		if (y1 == y2) goto next;

		e1 = (int)(dx1 >> 1);



		for (int i = 0; i < dx1;) {

			t1xp = 0; t2xp = 0;

			if (t1x < t2x) { minx = t1x; maxx = t2x; }

			else { minx = t2x; maxx = t1x; }

			// process first line until y value is about to change

			while (i < dx1) {

				i++;

				e1 += dy1;

				while (e1 >= dx1) {

					e1 -= dx1;

					if (changed1) t1xp = signx1;//t1x += signx1;

					else          goto next1;

				}

				if (changed1) break;

				else t1x += signx1;

			}

			// Move line

		next1:

			// process second line until y value is about to change

			while (1) {

				e2 += dy2;

				while (e2 >= dx2) {

					e2 -= dx2;

					if (changed2) t2xp = signx2;//t2x += signx2;

					else          goto next2;

				}

				if (changed2)     break;

				else              t2x += signx2;

			}

		next2:

			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;

			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;

			drawline(minx, maxx, y);    // Draw line from min to max points found on the y

										 // Now increase y

			if (!changed1) t1x += signx1;

			t1x += t1xp;

			if (!changed2) t2x += signx2;

			t2x += t2xp;

			y += 1;

			if (y == y2) break;



		}

	next:

		// Second half

		dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }

		else signx1 = 1;

		dy1 = (int)(y3 - y2);

		t1x = x2;



		if (dy1 > dx1) {   // swap values

			SWAP(dy1, dx1);

			changed1 = true;

		}

		else changed1 = false;



		e1 = (int)(dx1 >> 1);



		for (int i = 0; i <= dx1; i++) {

			t1xp = 0; t2xp = 0;

			if (t1x < t2x) { minx = t1x; maxx = t2x; }

			else { minx = t2x; maxx = t1x; }

			// process first line until y value is about to change

			while (i < dx1) {

				e1 += dy1;

				while (e1 >= dx1) {

					e1 -= dx1;

					if (changed1) { t1xp = signx1; break; }//t1x += signx1;

					else          goto next3;

				}

				if (changed1) break;

				else   	   	  t1x += signx1;

				if (i < dx1) i++;

			}

		next3:

			// process second line until y value is about to change

			while (t2x != x3) {

				e2 += dy2;

				while (e2 >= dx2) {

					e2 -= dx2;

					if (changed2) t2xp = signx2;

					else          goto next4;

				}

				if (changed2)     break;

				else              t2x += signx2;

			}

		next4:



			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;

			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;

			drawline(minx, maxx, y);

			if (!changed1) t1x += signx1;

			t1x += t1xp;

			if (!changed2) t2x += signx2;

			t2x += t2xp;

			y += 1;

			if (y > y3) return;

		}

	}
	
	void DrawQuad(int nMinY, int nMinX, int nMaxY, int nMaxX, uint32_t Color)
	{
		int nPitch = nWidth * nBytesPerPixel;		// full width of the row

		uint8_t *pRow = (uint8_t*)m_pTargetBuffer->pBuffer +
			nMinX * nBytesPerPixel +
			nMinY * nPitch;

		if (nMinY < 0)
			nMinY = 0;
		if (nMinX < 0)
			nMinX = 0;
		if (nMaxX > nWidth)
			nMaxX = nWidth;
		if (nMaxY > nHeight)
			nMaxY = nHeight;

		for (int nY = nMinY; nY < nMaxY; ++nY)
		{

			uint32_t *pPixel = (uint32_t*)pRow;
			for (int nX = nMinX; nX < nMaxX; ++nX)
			{
				*(uint32_t*)pPixel++ = Color;
			}
			pRow += nPitch;
		}
	}

public:
	Win32Renderer() {};
	Win32Renderer(Win32BackBuffer *pTargetBuffer) :
		nWidth(pTargetBuffer->nWidth),
		nHeight(pTargetBuffer->nHeight),
		nBytesPerPixel(pTargetBuffer->nBytesPerPixel),
		m_pTargetBuffer(pTargetBuffer){};

	void setBuffer(Win32BackBuffer *pTargetBuffer) 
	{
		nWidth = pTargetBuffer->nWidth;
		nHeight = pTargetBuffer->nHeight;
		nBytesPerPixel = pTargetBuffer->nBytesPerPixel;
		m_pTargetBuffer = pTargetBuffer;
	}

	//void Draw(Polygon2D &Poly)
	//{
	//	uint32_t nColor = Color(0, 255, 0, 0);

	//	vector<Vector2> Verticies = Poly.Verticies;
	//	for (int nI = 0; nI < Verticies.size() - 1; nI++)
	//	{
	//		DrawLine(Verticies[nI], Verticies[nI + 1], nColor);
	//	}

	//	DrawLine(Verticies[Verticies.size() - 1], Verticies[0], nColor);
	//}

	//void SortAndRasterTriangles(vector<Triangle> vecTrianglesToRaster)
	//{
	//	sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](Triangle &t1, Triangle &t2)
	//	{
	//		float z1 = (t1.A.Z + t1.B.Z + t1.C.Z) / 3;
	//		float z2 = (t2.A.Z + t2.B.Z + t2.C.Z) / 3;
	//		return z1 > z2;
	//	});

	//	for (auto tri : vecTrianglesToRaster)
	//	{
	//		FillTriangle(tri, tri.Color);
	//		//	DrawTriangle(tri, Color(0, 0, 0, 0));
	//	}
	//}

	//void Render3DTestA(BaseNode *pGameData)
	//{
	//	m_pTargetBuffer->fill(Color(0, 0, 0, 0));
	//	mat4x4 matProj = matProj.Projection(90.0, (float)nHeight/(float)nWidth, 0.1, 1000.0);

	//	Vector3 vCamera(0, 0, 0);
	//	
	//	// Illumination
	//	Vector3 vLightDir(0.0, 0.0, -1.0);
	//	vLightDir = vLightDir.normalized();

	//	vector<Triangle> vecTrianglesToRaster;
	//	
	//	if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
	//	{
	//		while (pEntities->isIterating())
	//		{
	//			BaseNode *pCurrent = pEntities->getCurrent();
	//			if (Transform3D *pTransform = pCurrent->getChild<Transform3D>())
	//				if (Mesh3D *pMesh = pCurrent->getChild<Mesh3D>())
	//				{
	//					Vector3 Position = pTransform->getPosition();
	//					Vector3 Rotation = pTransform->getRotation();
	//					Vector3 Scale = pTransform->getScale();

	//					mat4x4 matTrans = matTrans.Translation(Position.Y, Position.X, Position.Z);
	//					mat4x4 matRotateX = matRotateX.rotateX(Rotation.X);
	//					mat4x4 matRotateY = matRotateY.rotateY(Rotation.Y);
	//					mat4x4 matRotateZ = matRotateZ.rotateZ(Rotation.Z);
	//					mat4x4 matWorld = matWorld.Identity();
	//				
	//					matWorld = matWorld * matRotateX;
	//					matWorld = matWorld * matRotateY;
	//					matWorld = matWorld * matRotateZ;
	//					matWorld = matWorld * matTrans;
	//					
	//					for (auto tri : pMesh->getMesh())
	//					{
	//						Triangle triTransformed = matWorld * tri;
	//						Vector3 triNormal = triTransformed.normal().normalized();

	//						if (dotProduct(triNormal, (triTransformed.A - vCamera)) < 0)
	//						{
	//							Triangle triProjected = matProj * triTransformed;
	//								
	//							triProjected.A = triProjected.A / triProjected.A.W;
	//							triProjected.B = triProjected.B / triProjected.B.W;
	//							triProjected.C = triProjected.C / triProjected.C.W;

	//							Vector3 vOffsetView = { 1,1,0 };
	//							triProjected.A = triProjected.A + vOffsetView;
	//							triProjected.B = triProjected.B + vOffsetView;
	//							triProjected.C = triProjected.C + vOffsetView;
	//							triProjected.A.X *= 0.5f * (float)nWidth;
	//							triProjected.A.Y *= 0.5f * (float)nHeight;
	//							triProjected.B.X *= 0.5f * (float)nWidth;
	//							triProjected.B.Y *= 0.5f * (float)nHeight;
	//							triProjected.C.X *= 0.5f * (float)nWidth;
	//							triProjected.C.Y *= 0.5f * (float)nHeight;

	//							float fLightLevel = dotProduct(vLightDir, triNormal);
	//							int color = Color(0, 0, 0, 0);
	//							if (fLightLevel >= 0)
	//							{
	//								color = Color(1 * fLightLevel, 1 * fLightLevel, 1 * fLightLevel, 0);
	//							}
	//															
	//							triProjected.Color = color;
	//							vecTrianglesToRaster.push_back(triProjected);
	//						}
	//					}
	//				}
	//		}
	//	}
	//	
	//	SortAndRasterTriangles(vecTrianglesToRaster);
	//}

	//void Render3DTestC(BaseNode *pGameData, int nY, int nX)
	//{
	//	vector<Triangle> vecTrianglesToRaster;
	//	m_pTargetBuffer->fill(Color(0, 0, 0, 0));
	//	mat4x4 matProj = matProj.Projection(90.0, (float)nHeight / (float)nWidth, 0.1, 1000.0);

	//	// Illumination
	//	Vector3 vLightDir(0.0, 0.0, -1.0);
	//	vLightDir = vLightDir.normalized();

	//	// Make view matrix from camera
	//	//	mat4x4 matCameraRot = matCameraRot.rotateY(0.0);
	//	// Create "Point At" Matrix for camera
	//	
	//	Vector3 cameraPos(0, 0, 0);
	//	Vector3 upDir( 1, 0, 0 );
	//	Vector3 forwardDir( 0, 0, 1 );

	//	if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
	//	{
	//		while (pEntities->isIterating())
	//		{
	//			if (Camera *pCamera = pEntities->getCurrent()->getChild<Camera>())
	//			{
	//				upDir = pCamera->getUpDir();
	//				forwardDir = pCamera->getForward();
	//				
	//				if (Transform3D *pTransform = pEntities->getCurrent()->getChild<Transform3D>())
	//				{
	//					Vector3 Position = pTransform->getPosition();
	//					Vector3 Rotation = pTransform->getRotation();

	//					mat4x4 matTrans = matTrans.Translation(Position.Y, Position.X, Position.Z);
	//					mat4x4 matRotateX = matRotateX.rotateX(Rotation.X);
	//					mat4x4 matRotateY = matRotateY.rotateY(Rotation.Y);
	//					mat4x4 matRotateZ = matRotateZ.rotateZ(Rotation.Z);

	//					cameraPos = matTrans * cameraPos;
	//					forwardDir = matRotateX * forwardDir;
	//					forwardDir = matRotateY * forwardDir;
	//					forwardDir = matRotateZ * forwardDir;
	//				}
	//			}
	//		}
	//	}
	//	
	//	//	Vector3 vLookDir = matCameraRot * vTarget;
	//	//	vTarget = vCamera + vLookDir;
	//	mat4x4 matCamera = matCamera.PointAt(cameraPos, forwardDir, upDir);
	//	mat4x4 matView = Inverse(matCamera);

	//	if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
	//	{
	//		while (pEntities->isIterating())
	//		{
	//			BaseNode *pCurrent = pEntities->getCurrent();
	//			if (Transform3D *pTransform = pCurrent->getChild<Transform3D>())
	//				if (Mesh3D *pMesh = pCurrent->getChild<Mesh3D>())
	//				{
	//					Vector3 Position = pTransform->getPosition();
	//					Vector3 Rotation = pTransform->getRotation();
	//					Vector3 Scale = pTransform->getScale();

	//					mat4x4 matTrans = matTrans.Translation(Position.Y, Position.X, Position.Z);
	//					mat4x4 matRotateX = matRotateX.rotateX(Rotation.X);
	//					mat4x4 matRotateY = matRotateY.rotateY(Rotation.Y);
	//					mat4x4 matRotateZ = matRotateZ.rotateZ(Rotation.Z);
	//					mat4x4 matWorld = matWorld.Identity();

	//					matWorld = matWorld * matRotateX;
	//					matWorld = matWorld * matRotateY;
	//					matWorld = matWorld * matRotateZ;
	//					matWorld = matWorld * matTrans;

	//					for (auto tri : pMesh->getMesh())
	//					{
	//						Triangle triTransformed = matWorld * tri;

	//						Vector3 triTransformedNormal = triTransformed.normal().normalized();
	//						Vector3 cameraRay = triTransformed.A - cameraPos;

	//						if (dotProduct(triTransformedNormal, cameraRay) < 0.0)
	//						{
	//							Triangle triViewed = matView * triTransformed;

	//							// Clip Viewed Triangle against near plane, this could form two additional
	//							// additional triangles. 
	//							/*int nClippedTriangles = 0;
	//							Triangle triClipped[2];
	//							nClippedTriangles = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, triViewed, triClipped[0], triClipped[1]);

	//							for (int n = 0; n < nClippedTriangles; n++)
	//							*/{
	//								Triangle triProjected = matProj *triViewed;
	//								triProjected.A = triProjected.A / triProjected.A.W;
	//								triProjected.B = triProjected.B / triProjected.B.W;
	//								triProjected.C = triProjected.C / triProjected.C.W;
	//							
	//								Vector3 vOffsetView = { 1,1,0 };
	//								triProjected.A = triProjected.A + vOffsetView;
	//								triProjected.B = triProjected.B + vOffsetView;
	//								triProjected.C = triProjected.C + vOffsetView;
	//								triProjected.A.X *= 0.5f * (float)nWidth;
	//								triProjected.A.Y *= 0.5f * (float)nHeight;
	//								triProjected.B.X *= 0.5f * (float)nWidth;
	//								triProjected.B.Y *= 0.5f * (float)nHeight;
	//								triProjected.C.X *= 0.5f * (float)nWidth;
	//								triProjected.C.Y *= 0.5f * (float)nHeight;


	//								float fLightLevel = dotProduct(vLightDir, triTransformedNormal);
	//								int color = Color(0, 0, 0, 0);
	//								if (fLightLevel >= 0)
	//								{
	//									color = Color(1 * fLightLevel, 1 * fLightLevel, 1 * fLightLevel, 0);
	//								}
	//								triProjected.Color = color;

	//								vecTrianglesToRaster.push_back(triProjected);
	//							}
	//						}
	//					}
	//				}
	//		}
	//	}

	//	SortAndRasterTriangles(vecTrianglesToRaster);

	//	DrawQuad(nY, nX, nY + 10, nX + 10, Color(255, 0, 0, 0));
	//}

	//void Render3DTestB(BaseNode *pGameData)
	//{
	//	m_pTargetBuffer->fill(Color(0, 0, 0, 0));

	//	Vector3 vLightDir(0.0, 0.0, -1.0);
	//	vLightDir = vLightDir.normalized();
	//	Vector3 vCamera;	// Location of camera in world space
	//	Vector3 vLookDir;	// Direction vector along the direction camera points
	//	
	//	int color = Color(1, 1, 1, 0);

	//	mat4x4 matProj = matProj.Projection(90.0f, 
	//										(float)nHeight / (float)nWidth,
	//										0.1f, 
	//										1000.0f);

	//	

	//	vector<Triangle> vecTrianglesToRaster;
	//	if (pGameData)
	//	{
	//		if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
	//		{
	//			while (pEntities->isIterating())
	//			{
	//				if (Transform3D *pTransform = pEntities->getCurrent()->getChild<Transform3D>())
	//					if (Mesh3D *pMesh = pEntities->getCurrent()->getChild<Mesh3D>())
	//					{
	//						Vector3 Position = pTransform->getPosition();
	//						Vector3 Rotation = pTransform->getRotation();
	//						Vector3 Scale = pTransform->getScale();

	//						mat4x4 matTrans = matTrans.Translation(Position.Y, Position.X, Position.Z);
	//						mat4x4 matRotateX = matRotateX.rotateX(Rotation.X);
	//						mat4x4 matRotateY = matRotateY.rotateY(Rotation.Y);
	//						mat4x4 matRotateZ = matRotateZ.rotateZ(Rotation.Z);
	//						mat4x4 matWorld = matWorld.Identity();

	//						matWorld = matWorld * matRotateX;
	//						matWorld = matWorld * matRotateY;
	//						matWorld = matWorld * matRotateZ;
	//						matWorld = matWorld * matTrans;

	//						// Make view matrix from camera
	//						// Create "Point At" Matrix for camera
	//						Vector3 vUp = { 0, 1, 0 };
	//						Vector3 vTarget = { 0, 0, 1 };
	//						mat4x4 matCameraRot = matCameraRot.rotateY(0.0);
	//						vLookDir = matCameraRot * vTarget;
	//						vTarget = vCamera + vLookDir;
	//						mat4x4 matCamera = matCamera.PointAt(vCamera, vTarget, vUp);
	//						mat4x4 matView = Inverse(matCamera);

	//						for (auto tri : pMesh->getMesh())
	//						{
	//							Triangle triTransformed = matWorld * tri;

	//							Vector3 triNormal = triTransformed.normal().normalized();

	//							if (dotProduct(triNormal, triTransformed.A) < 0)
	//							{
	//								Triangle triViewed = matView * triTransformed;

	//								Triangle triProjected;

	//								triProjected = matProj * triTransformed;

	//								triProjected.A = triProjected.A / triProjected.A.W;
	//								triProjected.B = triProjected.B / triProjected.B.W;
	//								triProjected.C = triProjected.C / triProjected.C.W;

	//								Vector3 vOffsetView = { 1,1,0 };
	//								triProjected.A = triProjected.A + vOffsetView;
	//								triProjected.B = triProjected.B + vOffsetView;
	//								triProjected.C = triProjected.C + vOffsetView;
	//								triProjected.A.X *= 0.5f * (float)nWidth;
	//								triProjected.A.Y *= 0.5f * (float)nHeight;
	//								triProjected.B.X *= 0.5f * (float)nWidth;
	//								triProjected.B.Y *= 0.5f * (float)nHeight;
	//								triProjected.C.X *= 0.5f * (float)nWidth;
	//								triProjected.C.Y *= 0.5f * (float)nHeight;


	//								float fLightLevel = -dotProduct(vLightDir, triNormal);
	//								if (fLightLevel > 0)
	//								{
	//									//	color = Color(1 * fLightLevel, 1 * fLightLevel, 1 * fLightLevel, 0);
	//								}

	//								triProjected.Color = color;
	//								vecTrianglesToRaster.push_back(triProjected);
	//							}
	//						}

	//					}
	//			}
	//		}
	//	}

	//	SortAndRasterTriangles(vecTrianglesToRaster);
	//}
	//void Render3D(BaseNode *pGameData)
	//{
	//	//	set up scene
	//	//		camera
	//	//		camera matrix
	//	//		light
	//	//		projection matrix
	//	//		etc
	//	
	//	//	for each mesh
	//	//	transform mesh
	//	//	mesh * world matrix

	//	//	convert to 2d
	//	//	mesh * projection matrix

	//	//	scale into view?
	//	//	color triangle

	//	//	sort triangles
	//	//	clip against near plane
	//	//	clip against side planes
	//	//	raster triangles

	//}

	//void Render2D(BaseNode *pGameData)
	//{
	//	//	clear background
	//	m_pTargetBuffer->fill(Color(0, 0, 0, 0));

	//	uint32_t nColor = Color(1, 1, 1, 0);	// entity colors will be moved inside entities
	//	if (TileMapManager *pTileMap = pGameData->getChild<TileMapManager>())
	//	{
	//		for (int nY = 0; nY < 10; nY++)
	//			for (int nX = 0; nX < 10; nX++)
	//			{
	//				/*if (pTileMap->_TileMap[nY][nX] == 1)
	//				{
	//					DrawQuad(nY * pTileMap->nTileHeight, nX * pTileMap->nTileWidth, nY * pTileMap->nTileHeight + pTileMap->nTileHeight, nX * pTileMap->nTileWidth + pTileMap->nTileWidth, Color(.5, .5, .5, 0));
	//				}*/
	//			}
	//	}

	//	if (EntityManager *pEntities = pGameData->getChild<EntityManager>())
	//	{
	//		while (pEntities->isIterating())
	//		{
	//			if (Transform3D *pTransform = pEntities->getCurrent()->getChild<Transform3D>())
	//				if (Poly2D *pMesh = pEntities->getCurrent()->getChild<Poly2D>())
	//				{
	//					Polygon2D Poly = pMesh->getPoly();
	//					Poly.scale({ pTransform->getScale().Y, pTransform->getScale().X});
	//					Poly.rotate({ pTransform->getRotation().X });
	//					Poly.translate({ pTransform->getPosition().Y, pTransform->getPosition().X});


	//					vector<Vector2> Verticies = Poly.Verticies;
	//					for (int nI = 0; nI < Verticies.size() - 1; nI++)
	//					{
	//						DrawLine(Verticies[nI], Verticies[nI + 1], nColor);
	//					}

	//					DrawLine(Verticies[Verticies.size() - 1], Verticies[0], nColor);
	//					Vector2 Min(pTransform->getPosition().Y, pTransform->getPosition().X);
	//					Vector2 Max(pTransform->getScale().Y + pTransform->getPosition().Y, pTransform->getScale().X + pTransform->getPosition().X);
	//					DrawQuad(Min.Y, Min.X, Max.Y, Max.X, nColor);
	//				}
	//		}
	//	}



	//}

	//void RenderGUI(BaseNode *pData)
	//{
	//	
	//}
};