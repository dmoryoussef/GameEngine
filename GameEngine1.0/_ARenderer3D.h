#include <list>

//class _ARenderer3D
//{
//private:
//	void drawLine(Vector2 Start, Vector2 End, int nColor, AFrame *pBuffer)
//	{
//		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
//		dx = End.X - Start.X;
//		dy = End.Y - Start.Y;
//		dx1 = abs(dx);
//		dy1 = abs(dy);
//		px = 2 * dy1 - dx1;
//		py = 2 * dx1 - dy1;
//
//		if (dy1 <= dx1)
//		{
//			if (dx >= 0)
//			{
//				x = Start.X;
//				y = Start.Y;
//				xe = End.X;
//			}
//			else
//			{
//				x = End.X;
//				y = End.Y;
//				xe = Start.X;
//			}
//			pBuffer->set(219, x, y, nColor);
//
//			for (i = 0; x < xe; i++)
//			{
//				x = x + 1;
//				if (px < 0)
//					px = px + 2 * dy1;
//
//				else
//				{
//					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
//					px = px + 2 * (dy1 - dx1);
//				}
//				pBuffer->set(219, x, y, nColor);
//			}
//		}
//
//		else
//		{
//			if (dy >= 0)
//			{
//				x = Start.X;
//				y = Start.Y;
//				ye = End.Y;
//			}
//			else
//			{
//				x = End.X;
//				y = End.Y;
//				ye = Start.Y;
//			}
//			pBuffer->set(219, x, y, nColor);
//
//			for (i = 0; y < ye; i++)
//			{
//				y = y + 1;
//				if (py <= 0)
//					py = py + 2 * dx1;
//				else
//				{
//					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
//					py = py + 2 * (dx1 - dy1);
//
//				}
//				pBuffer->set(219, x, y, nColor);
//			}
//		}
//
//	}
//	void drawTriangle(Vector2 a, Vector2 b, Vector2 c, int nColor, AFrame *pBuffer)
//	{
//		drawLine(a, b, nColor, pBuffer);
//		drawLine(b, c, nColor, pBuffer);
//		drawLine(c, a, nColor, pBuffer);
//	}
//	void fillTriangle(Triangle triangle, APixel pixel, AFrame *pBuffer)
//
//	{
//		int x1 = triangle.A.X;
//		int y1 = triangle.A.Y;
//
//		int x2 = triangle.B.X;
//		int y2 = triangle.B.Y;
//
//		int x3 = triangle.C.X;
//		int y3 = triangle.C.Y;
//
//		auto SWAP = [](int &x, int &y) { int t = x; x = y; y = t; };
//
//		auto drawline = [&](int sx, int ex, int ny)
//		{
//			for (int i = sx; i <= ex; i++)
//				pBuffer->set(pixel.m_chChar, ny, i, pixel.m_nColor);
//		};
//
//
//
//		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
//
//		bool changed1 = false;
//
//		bool changed2 = false;
//
//		int signx1, signx2, dx1, dy1, dx2, dy2;
//
//		int e1, e2;
//
//		// Sort vertices
//
//		if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
//
//		if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }
//
//		if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }
//
//
//
//		t1x = t2x = x1; y = y1;   // Starting points
//
//		dx1 = (int)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
//
//		else signx1 = 1;
//
//		dy1 = (int)(y2 - y1);
//
//
//
//		dx2 = (int)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
//
//		else signx2 = 1;
//
//		dy2 = (int)(y3 - y1);
//
//
//
//		if (dy1 > dx1) {   // swap values
//
//			SWAP(dx1, dy1);
//
//			changed1 = true;
//
//		}
//
//		if (dy2 > dx2) {   // swap values
//
//			SWAP(dy2, dx2);
//
//			changed2 = true;
//
//		}
//
//
//
//		e2 = (int)(dx2 >> 1);
//
//		// Flat top, just process the second half
//
//		if (y1 == y2) goto next;
//
//		e1 = (int)(dx1 >> 1);
//
//
//
//		for (int i = 0; i < dx1;) {
//
//			t1xp = 0; t2xp = 0;
//
//			if (t1x < t2x) { minx = t1x; maxx = t2x; }
//
//			else { minx = t2x; maxx = t1x; }
//
//			// process first line until y value is about to change
//
//			while (i < dx1) {
//
//				i++;
//
//				e1 += dy1;
//
//				while (e1 >= dx1) {
//
//					e1 -= dx1;
//
//					if (changed1) t1xp = signx1;//t1x += signx1;
//
//					else          goto next1;
//
//				}
//
//				if (changed1) break;
//
//				else t1x += signx1;
//
//			}
//
//			// Move line
//
//		next1:
//
//			// process second line until y value is about to change
//
//			while (1) {
//
//				e2 += dy2;
//
//				while (e2 >= dx2) {
//
//					e2 -= dx2;
//
//					if (changed2) t2xp = signx2;//t2x += signx2;
//
//					else          goto next2;
//
//				}
//
//				if (changed2)     break;
//
//				else              t2x += signx2;
//
//			}
//
//		next2:
//
//			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
//
//			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
//
//			drawline(minx, maxx, y);    // Draw line from min to max points found on the y
//
//										 // Now increase y
//
//			if (!changed1) t1x += signx1;
//
//			t1x += t1xp;
//
//			if (!changed2) t2x += signx2;
//
//			t2x += t2xp;
//
//			y += 1;
//
//			if (y == y2) break;
//
//
//
//		}
//
//	next:
//
//		// Second half
//
//		dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
//
//		else signx1 = 1;
//
//		dy1 = (int)(y3 - y2);
//
//		t1x = x2;
//
//
//
//		if (dy1 > dx1) {   // swap values
//
//			SWAP(dy1, dx1);
//
//			changed1 = true;
//
//		}
//
//		else changed1 = false;
//
//
//
//		e1 = (int)(dx1 >> 1);
//
//
//
//		for (int i = 0; i <= dx1; i++) {
//
//			t1xp = 0; t2xp = 0;
//
//			if (t1x < t2x) { minx = t1x; maxx = t2x; }
//
//			else { minx = t2x; maxx = t1x; }
//
//			// process first line until y value is about to change
//
//			while (i < dx1) {
//
//				e1 += dy1;
//
//				while (e1 >= dx1) {
//
//					e1 -= dx1;
//
//					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
//
//					else          goto next3;
//
//				}
//
//				if (changed1) break;
//
//				else   	   	  t1x += signx1;
//
//				if (i < dx1) i++;
//
//			}
//
//		next3:
//
//			// process second line until y value is about to change
//
//			while (t2x != x3) {
//
//				e2 += dy2;
//
//				while (e2 >= dx2) {
//
//					e2 -= dx2;
//
//					if (changed2) t2xp = signx2;
//
//					else          goto next4;
//
//				}
//
//				if (changed2)     break;
//
//				else              t2x += signx2;
//
//			}
//
//		next4:
//
//
//
//			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
//
//			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
//
//			drawline(minx, maxx, y);
//
//			if (!changed1) t1x += signx1;
//
//			t1x += t1xp;
//
//			if (!changed2) t2x += signx2;
//
//			t2x += t2xp;
//
//			y += 1;
//
//			if (y > y3) return;
//
//		}
//
//	}
//	
//	
//	
//	APixel getGreyscaleColor(float fValue)
//	{
//		int BG_Color = 0;
//		int FG_Color = 0;
//		char sym = 0;
//		//	convert float range of { 0.0 , 1.0 }
//		//	to int value of range { 1, 13 }
//		int nValue = fValue * 12;
//
//		switch (nValue)
//		{
//		case 0: BG_Color = BG_BLACK; FG_Color = FG_BLACK; sym = PIXEL_SOLID;
//			break;
//		case 1: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_QUARTER;
//			break;
//		case 2: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_HALF;
//			break;
//		case 3: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_THREEQUARTER;
//			break;
//		case 4: BG_Color = BG_BLACK; FG_Color = FG_DARKGREY; sym = PIXEL_SOLID;
//			break;
//		case 5: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_QUARTER;
//			break;
//		case 6: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_HALF;
//			break;
//		case 7: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_THREEQUARTER;
//			break;
//		case 8: BG_Color = BG_DARKGREY; FG_Color = FG_LIGHTGREY; sym = PIXEL_SOLID;
//			break;
//		case 9:  BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_QUARTER;
//			break;
//		case 10: BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_HALF;
//			break;
//		case 11: BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_THREEQUARTER;
//			break;
//		case 12: BG_Color = BG_LIGHTGREY; FG_Color = FG_WHITE; sym = PIXEL_SOLID;
//			break;
//		}
//
//		return APixel(sym, BG_Color + FG_Color);
//	}
//
//	void SortAndRasterTriangles(vector<Triangle> vecTrianglesToRaster, AFrame *pBuffer)
//	{
//		sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](Triangle &t1, Triangle &t2)
//		{
//			float z1 = (t1.A.Z + t1.B.Z + t1.C.Z) / 3;
//			float z2 = (t2.A.Z + t2.B.Z + t2.C.Z) / 3;
//			return z1 > z2;
//		});
//
//		for (auto tri : vecTrianglesToRaster)
//		{
//			fillTriangle(tri, tri.Pixel, pBuffer);
//			//	DrawTriangle(tri, Color(0, 0, 0, 0));
//		}
//	}
//
//	mat4x4 worldTransform(Transform3D *pTransform)
//	{
//		Vector3 Position = pTransform->getPosition();
//		Vector3 Rotation = pTransform->getRotation();
//
//		mat4x4 matTrans = matTrans.Translation(Position.Y, Position.X, Position.Z);
//		mat4x4 matRotateX = matRotateX.rotateX(Rotation.X);
//		mat4x4 matRotateY = matRotateY.rotateY(Rotation.Y);
//		mat4x4 matRotateZ = matRotateZ.rotateZ(Rotation.Z);
//		mat4x4 matWorld = matWorld.Identity();
//
//		matWorld = matWorld * matRotateX;
//		matWorld = matWorld * matRotateY;
//		matWorld = matWorld * matRotateZ;
//		matWorld = matWorld * matTrans;
//		return matWorld;
//	}
//
//	mat4x4 cameraView(BaseNode *pCamera)
//	{
//
//	}
//
//	void setTriangleLight(Vector3 lightDirection, Vector3 transformedNormal, Triangle &tri)
//	{
//		float fLightLevel = dotProduct(lightDirection, transformedNormal);
//		if (fLightLevel >= 0)
//		{
//			APixel pixel = getGreyscaleColor(dotProduct(transformedNormal, lightDirection));
//			tri.Pixel = pixel;
//		}
//	}
//
//
//	list<Triangle> ClipTriangles(vector<Triangle> trisToRaster, float fHeight, float fWidth)
//	{
//		list<Triangle> listTriangles;
//		// Loop through all transformed, viewed, projected, and sorted triangles
//		for (auto &triToRaster : trisToRaster)
//		{
//			// Clip triangles against all four screen edges, this could yield
//			// a bunch of triangles, so create a queue that we traverse to 
//			//  ensure we only test new triangles generated against planes
//			Triangle clipped[2];
//			
//
//			// Add initial triangle
//			listTriangles.push_back(triToRaster);
//			int nNewTriangles = 1;
//
//			for (int p = 0; p < 4; p++)
//			{
//				int nTrisToAdd = 0;
//				while (nNewTriangles > 0)
//				{
//					// Take triangle from front of queue
//					Triangle test = listTriangles.front();
//					listTriangles.pop_front();
//					nNewTriangles--;
//
//					// Clip it against a plane. We only need to test each 
//					// subsequent plane, against subsequent new triangles
//					// as all triangles after a plane clip are guaranteed
//					// to lie on the inside of the plane. I like how this
//					// comment is almost completely and utterly justified
//					switch (p)
//					{
//						case 0:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
//						case 1:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, fHeight - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
//						case 2:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
//						case 3:	nTrisToAdd = Triangle_ClipAgainstPlane({ fWidth - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
//					}
//
//					// Clipping may yield a variable number of triangles, so
//					// add these new ones to the back of the queue for subsequent
//					// clipping against next planes
//					for (int w = 0; w < nTrisToAdd; w++)
//						listTriangles.push_back(clipped[w]);
//				}
//				nNewTriangles = listTriangles.size();
//			}
//		}
//
//		return listTriangles;
//	}
//	
//public:
//	_ARenderer3D() {};
//	~_ARenderer3D() {}
//	
//	void Render3DNoClipping(BaseNode *pGameData, AFrame *pBuffer, BaseNode *pCamera)
//	{
//		float fHeight = pBuffer->getHeight();
//		float fWidth = pBuffer->getWidth();
//		mat4x4 matProj = matProj.Projection(90.0, fHeight / fWidth, 0.1, 1000.0);
//		// Illumination
//		Vector3 vLightDir(0.0, 0.0, -1.0);
//		vLightDir = vLightDir.normalized();
//		// Camera
//		Vector3 cameraPos(0, 0, 0);
//		Vector3 upDir(1, 0, 0);
//		Vector3 forwardDir(0, 0, 1);
//		
//		if (pCamera)
//		{
//			if (Camera *pCameraComponent = pCamera->getChild<Camera>())
//			{
//				if (Transform3D *pTransform = pCamera->getChild<Transform3D>())
//				{
//					upDir = pCameraComponent->getUpDir();
//					forwardDir = pTransform->getForward();
//
//					Vector3 Position = pTransform->getPosition();
//					mat4x4 matTrans = matTrans.Translation(Position.Y, Position.X, Position.Z);
//					
//					cameraPos = matTrans * cameraPos;
//				}
//			}
//		}
//		
//		Vector3 target = cameraPos + forwardDir;
//		mat4x4 matCamera = matCamera.PointAt(cameraPos, target, upDir);
//		mat4x4 matView = Inverse(matCamera);
//
//		vector<Triangle> vecTrianglesToRaster;
//
//		while (pGameData->isIterating())
//		{
//			BaseNode *pCurrent = pGameData->getCurrent();
//			if (Transform3D *pTransform = pCurrent->getChild<Transform3D>())
//				if (Mesh3D *pMesh = pCurrent->getChild<Mesh3D>())
//				{
//					mat4x4 matWorld = worldTransform(pTransform);
//
//					for (auto tri : pMesh->getMesh())
//					{
//						Triangle triTransformed = matWorld * tri;
//
//						Vector3 triNormal = triTransformed.normal().normalized();
//						Vector3 cameraRay = triTransformed.A - cameraPos;
//
//						if (dotProduct(triNormal, cameraRay) < 0)
//						{
//							Triangle triViewed = matView * triTransformed;
//							
//							{
//								Triangle triProjected = matProj * triViewed;
//								triProjected.A = triProjected.A / triProjected.A.W;
//								triProjected.B = triProjected.B / triProjected.B.W;
//								triProjected.C = triProjected.C / triProjected.C.W;
//
//								Vector3 vOffsetView = { 1, 1, 0 };
//								triProjected = triProjected + vOffsetView;
//														
//								triProjected.A.X *= 0.5f * fWidth;
//								triProjected.A.Y *= 0.5f * fHeight;
//								triProjected.B.X *= 0.5f * fWidth;
//								triProjected.B.Y *= 0.5f * fHeight;
//								triProjected.C.X *= 0.5f * fWidth;
//								triProjected.C.Y *= 0.5f * fHeight;
//
//								setTriangleLight(vLightDir, triNormal, triProjected);
//
//								vecTrianglesToRaster.push_back(triProjected);
//							}
//						}
//					}
//				}
//		}
//		
//
//		SortAndRasterTriangles(vecTrianglesToRaster, pBuffer);
//	}
//
//	void Render3DWithClipping(BaseNode *pEntities, AFrame *pBuffer, BaseNode *pCamera)
//	{
//		// basic 3d render with no camera
//		float fHeight = pBuffer->getHeight();
//		float fWidth = pBuffer->getWidth();
//
//		mat4x4 matProj = matProj.Projection(90.0, fHeight / fWidth, 0.1, 1000.0);
//		Vector3 vCamera(0, 0, 0);
//		Vector3 vLightDir(0.0, 0.0, -1.0);
//		vLightDir = vLightDir.normalized();
//
//		// iterate entities, project triangles and add triangles to raster list
//		vector<Triangle> trisToRaster;
//		while (pEntities->isIterating())
//		{
//			BaseNode *pCurrent = pEntities->getCurrent();
//			if (Transform3D *pTransform = pCurrent->getChild<Transform3D>())
//				if (Mesh3D *pMesh = pCurrent->getChild<Mesh3D>())
//				{
//					mat4x4 matWorld = worldTransform(pTransform);
//
//					for (auto tri : pMesh->getMesh())
//					{
//						Triangle triTransformed = matWorld * tri;
//						Vector3 triNormal = triTransformed.normal().normalized();
//
//						if (dotProduct(triNormal, (triTransformed.A - vCamera)) < 0)
//						{
//							
//							int nClippedTriangles = 0;
//							Triangle clipped[2];
//							nClippedTriangles = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, triTransformed, clipped[0], clipped[1]);
//							
//							// We may end up with multiple triangles form the clip, so project as
//							// required
//							for (int n = 0; n < nClippedTriangles; n++)
//							{
//
//								Triangle triProjected = matProj * clipped[n];
//								triProjected.A = triProjected.A / triProjected.A.W;
//								triProjected.B = triProjected.B / triProjected.B.W;
//								triProjected.C = triProjected.C / triProjected.C.W;
//
//								//	offset - why? i dont know, figure this out later
//								Vector3 vOffsetView = { 1, 1, 0 };
//								triProjected = triProjected + vOffsetView;
//
//								//	scale to window
//								triProjected.A.X *= 0.5f * fWidth;
//								triProjected.A.Y *= 0.5f * fHeight;
//								triProjected.B.X *= 0.5f * fWidth;
//								triProjected.B.Y *= 0.5f * fHeight;
//								triProjected.C.X *= 0.5f * fWidth;
//								triProjected.C.Y *= 0.5f * fHeight;
//
//								//	set triangle color
//								setTriangleLight(vLightDir, triNormal, triProjected);
//
//								trisToRaster.push_back(triProjected);
//							}
//						}
//					}
//
//					sort(trisToRaster.begin(), trisToRaster.end(), [](Triangle &t1, Triangle &t2)
//					{
//						float z1 = (t1.A.Z + t1.B.Z + t1.C.Z) / 3.0f;
//						float z2 = (t2.A.Z + t2.B.Z + t2.C.Z) / 3.0f;
//						return z1 > z2;
//					});
//
//					
//					list<Triangle> TrisToRaster = ClipTriangles(trisToRaster, fHeight, fWidth);
//
//					// Draw the transformed, viewed, clipped, projected, sorted, clipped triangles
//					for (auto &tri : TrisToRaster)
//					{
//						fillTriangle(tri, tri.Pixel, pBuffer);
//					}
//					
//				}
//		}
//
//
//
//		//SortAndRasterTriangles(trisToRaster, pBuffer);
//	}
//
//
//	void Render3D(BaseNode *pEntities, AFrame *pBuffer)
//	{
//		// basic 3d render with no camera
//		int nHeight = pBuffer->getHeight();
//		int nWidth = pBuffer->getWidth();
//
//		mat4x4 matProj = matProj.Projection(90.0, (float)nHeight / (float)nWidth, 0.1, 1000.0);
//		Vector3 vCamera(0, 0, 0);
//		Vector3 vLightDir(0.0, 0.0, -1.0);
//		vLightDir = vLightDir.normalized();
//
//		// iterate entities, project triangles and add triangles to raster list
//		vector<Triangle> trisToRaster;
//		while (pEntities->isIterating())
//		{
//			BaseNode *pCurrent = pEntities->getCurrent();
//			if (Transform3D *pTransform = pCurrent->getChild<Transform3D>())
//				if (Mesh3D *pMesh = pCurrent->getChild<Mesh3D>())
//				{
//					mat4x4 matWorld = worldTransform(pTransform);
//
//					for (auto tri : pMesh->getMesh())
//					{
//						Triangle triTransformed = matWorld * tri;
//						Vector3 triNormal = triTransformed.normal().normalized();
//
//						if (dotProduct(triNormal, (triTransformed.A - vCamera)) < 0)
//						{
//							Triangle triProjected = matProj * triTransformed;
//							triProjected.A = triProjected.A / triProjected.A.W;
//							triProjected.B = triProjected.B / triProjected.B.W;
//							triProjected.C = triProjected.C / triProjected.C.W;
//
//							//	offset - why? i dont know, figure this out later
//							Vector3 vOffsetView = { 1, 1, 0 };
//							triProjected = triProjected + vOffsetView;
//
//							//	scale to window
//							triProjected.A.X *= 0.5f * (float)nWidth;
//							triProjected.A.Y *= 0.5f * (float)nHeight;
//							triProjected.B.X *= 0.5f * (float)nWidth;
//							triProjected.B.Y *= 0.5f * (float)nHeight;
//							triProjected.C.X *= 0.5f * (float)nWidth;
//							triProjected.C.Y *= 0.5f * (float)nHeight;
//
//							//	set triangle color
//							setTriangleLight(vLightDir, triNormal, triProjected);
//
//							trisToRaster.push_back(triProjected);
//						}
//					}
//				}
//		}
//
//		SortAndRasterTriangles(trisToRaster, pBuffer);
//	}
//
//};