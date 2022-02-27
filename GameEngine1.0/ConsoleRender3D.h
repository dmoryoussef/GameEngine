class ConsoleRender3D : public ConsoleRender2D
{
private:
	float *m_pDepthBuffer; 
	float m_fAmbientLight;

	Vector3 Vector_IntersectPlane(Vector3 &plane_p, Vector3 &plane_n, Vector3 &lineStart, Vector3 &lineEnd, float &t)
	{
		plane_n = plane_n.normalized();
		float plane_d = -dotProduct(plane_n, plane_p);
		float ad = dotProduct(lineStart, plane_n);
		float bd = dotProduct(lineEnd, plane_n);
		t = (-plane_d - ad) / (bd - ad);
		Vector3 lineStartToEnd = (lineEnd - lineStart);
		Vector3 lineToIntersect = (lineStartToEnd * t);
		return (lineStart + lineToIntersect);
	}

	int Triangle_ClipAgainstPlane(Vector3 plane_p, Vector3 plane_n, Triangle& in_tri, Triangle& out_tri1, Triangle& out_tri2)
	{
		// Make sure plane normal is indeed normal
		plane_n = plane_n.normalized();

		// Return signed shortest distance from point to plane, plane normal must be normalised
		auto dist = [&](Vector3 &p)
		{
			Vector3 a = p;
			Vector3 n = a.normalized();
			return ((plane_n.X * p.X + plane_n.Y * p.Y + plane_n.Z * p.Z) - dotProduct(plane_n, plane_p));
		};

		// Create two temporary storage arrays to classify points either side of plane
		// If distance sign is positive, point lies on "inside" of plane
		Vector3* inside_points[3];
		int nInsidePointCount = 0;
		Vector3* outside_points[3];
		int nOutsidePointCount = 0;

		// Get signed distance of each point in triangle to plane
		float d0 = dist(in_tri.A);
		float d1 = dist(in_tri.B);
		float d2 = dist(in_tri.C);

		if (d0 >= 0)
		{
			inside_points[nInsidePointCount++] = &in_tri.A;
		}
		else
		{
			outside_points[nOutsidePointCount++] = &in_tri.A;
		}

		if (d1 >= 0)
		{
			inside_points[nInsidePointCount++] = &in_tri.B;
		}
		else
		{
			outside_points[nOutsidePointCount++] = &in_tri.B;
		}

		if (d2 >= 0)
		{
			inside_points[nInsidePointCount++] = &in_tri.C;
		}
		else
		{
			outside_points[nOutsidePointCount++] = &in_tri.C;
		}

		// Now classify triangle points, and break the input triangle into 
		// smaller output triangles if required. There are four possible
		// outcomes...

		if (nInsidePointCount == 0)
		{
			// All points lie on the outside of plane, so clip whole triangle
			// It ceases to exist

			return 0; // No returned triangles are valid
		}

		if (nInsidePointCount == 3)
		{
			// All points lie on the inside of plane, so do nothing
			// and allow the triangle to simply pass through
			out_tri1 = in_tri;

			return 1; // Just the one returned original triangle is valid
		}

		if (nInsidePointCount == 1 && nOutsidePointCount == 2)
		{
			// Triangle should be clipped. As two points lie outside
			// the plane, the triangle simply becomes a smaller triangle

			// Copy appearance info to new triangle
			//	out_tri1.Color = FG_LIGHTRED; // in_tri.Color;
			out_tri1.Pixel.m_chChar = in_tri.Pixel.m_chChar;
			out_tri1.Pixel.m_nColor = in_tri.Pixel.m_nColor;;

			// The inside point is valid, so keep that...
			out_tri1.A = *inside_points[0];

			// but the two new points are at the locations where the 
			// original sides of the triangle (lines) intersect with the plane
			float t;
			out_tri1.B = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
			out_tri1.C = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1], t);

			return 1; // Return the newly formed single triangle
		}

		if (nInsidePointCount == 2 && nOutsidePointCount == 1)
		{
			// Triangle should be clipped. As two points lie inside the plane,
			// the clipped triangle becomes a "quad". Fortunately, we can
			// represent a quad with two new triangles

			// Copy appearance info to new triangles
			//	out_tri1.Color = FG_LIGHTBLUE;
			out_tri1.Pixel.m_chChar = in_tri.Pixel.m_chChar;
			out_tri1.Pixel.m_nColor = in_tri.Pixel.m_nColor;

			//	out_tri2.Color = FG_LIGHTBLUE;
			out_tri2.Pixel.m_chChar = in_tri.Pixel.m_chChar;
			out_tri2.Pixel.m_nColor = in_tri.Pixel.m_nColor;

			// The first triangle consists of the two inside points and a new
			// point determined by the location where one side of the triangle
			// intersects with the plane
			float t;
			out_tri1.A = *inside_points[0];
			out_tri1.B = *inside_points[1];
			out_tri1.C = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);


			// The second triangle is composed of one of he inside points, a
			// new point determined by the intersection of the other side of the 
			// triangle and the plane, and the newly created point above
			out_tri2.A = *inside_points[1];
			out_tri2.B = out_tri1.C;
			out_tri2.C = Vector_IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0], t);
			return 2; // Return two newly formed triangles which form a quad
		}
	}

	mat4x4 worldTransform(Transform3D *pTransform)
	{
		Vector3 Position = pTransform->getPosition();
		Vector3 Rotation = pTransform->getRotation();
		Vector3 Scale = pTransform->getScale();

		mat4x4 matTrans = matTrans.Translation(Position.X, Position.Y, Position.Z);
		mat4x4 matRotateX = matRotateX.rotateX(Rotation.X);
		mat4x4 matRotateY = matRotateY.rotateY(Rotation.Y);
		mat4x4 matRotateZ = matRotateZ.rotateZ(Rotation.Z);
		mat4x4 matScale = matScale.Scale(Scale.X, Scale.Y, Scale.Z);
		mat4x4 matWorld = matWorld.Identity();

		matWorld = matWorld * matScale;
		matWorld = matWorld * matRotateX;
		matWorld = matWorld * matRotateY;
		matWorld = matWorld * matRotateZ;
		matWorld = matWorld * matTrans;
		
		
		return matWorld;
	}

	vector<Triangle> ProjectTriangles(vector<Triangle> vecTris, mat4x4 matProj)
	{
		vector<Triangle> vecProjectedTris;

		for (auto tri : vecTris)
		{
			Triangle triProjected = tri;
			triProjected = matProj * triProjected;
			triProjected.A = triProjected.A / triProjected.A.W;
			triProjected.B = triProjected.B / triProjected.B.W;
			triProjected.C = triProjected.C / triProjected.C.W;

			vecProjectedTris.push_back(triProjected);
		}

		return vecProjectedTris;
	}

	vector<Triangle> TransformTriangles(vector<Triangle> vecTris, mat4x4 matWorld)
	{
		vector<Triangle> vecTransformedTris;
		//	transform mesh of triangles
		for (auto tri : vecTris)
		{
			Triangle triTransformed = matWorld * tri;
			vecTransformedTris.push_back(triTransformed);
		}

		return vecTransformedTris;
	}

	vector<Triangle> ScaleToScreen(vector<Triangle> vecTris, float fHeight, float fWidth)
	{
		Vector3 vOffsetView = { 1, 1, 0 };
		vector<Triangle> vecScalesTris;
		for (auto tri : vecTris)
		{
			Triangle scaledTri = tri + vOffsetView;

			scaledTri.A.X *= 0.5f * fWidth;
			scaledTri.A.Y *= 0.5f * fHeight;
			scaledTri.B.X *= 0.5f * fWidth;
			scaledTri.B.Y *= 0.5f * fHeight;
			scaledTri.C.X *= 0.5f * fWidth;
			scaledTri.C.Y *= 0.5f * fHeight;
			vecScalesTris.push_back(scaledTri);
		}
		return vecScalesTris;
	}


	void SortAndRasterTriangles(vector<Triangle> vecTrisToRaster)
	{
		//	for (int i = 0; i < nHeight * nWidth; i++)	m_pDepthBuffer[i] = 0.0f;

		DrawNum(vecTrisToRaster.size(), 2, 2, FG_WHITE + BG_BLACK);
		sort(vecTrisToRaster.begin(), vecTrisToRaster.end(), [](Triangle &t1, Triangle &t2)
		{
			float z1 = (t1.A.Z + t1.B.Z + t1.C.Z) / 3;
			float z2 = (t2.A.Z + t2.B.Z + t2.C.Z) / 3;
			return z1 > z2;
		});

		for (auto tri : vecTrisToRaster)
		{
			FillTriangle(tri, tri.Pixel);
			//DrawTriangle(tri, getGreyscaleColor(0.5));
		}
 	}

	vector<Triangle> BackfaceCulling(vector<Triangle> vecTris, Vector3 vCameraPos)
	{
		vector<Triangle> vecRemainingTris;
		for (auto tri : vecTris)
		{
			Triangle keptTri = tri;
			Vector3 triNormal = keptTri.normal().normalized();
			Vector3 vCameraRay = keptTri.A - vCameraPos;

			if (dotProduct(triNormal, vCameraRay) > 0.0f)	
			{
				vecRemainingTris.push_back(keptTri);
			}
		}
		return vecRemainingTris;
	}

	vector<Triangle> ProcessLambertLighting(vector<Triangle> vecTris, vector<Vector3> vecLights)
	{
		vector<Triangle> vecLightedTris;
		for (auto tri : vecTris)
		{
			Triangle triLighted = tri;
			float totalLightValue = 0;
			for (auto vLight : vecLights)
			{
				float fLightLevel = dotProduct(vLight.normalized(), tri.normal().normalized());	// OBJ files have reversed normals? fix? - reading y than x seems to have fixed it
				if (fLightLevel > 0)
					totalLightValue += fLightLevel;
			}

			totalLightValue += m_fAmbientLight;
			if (totalLightValue > 1.0f)
				totalLightValue = 1.0f;
			triLighted.Pixel = getGreyscaleColor(totalLightValue);
			vecLightedTris.push_back(triLighted);
		}
		return vecLightedTris;
	}

	vector<Triangle> ViewTriangles(vector<Triangle> vecTris, mat4x4 matView)
	{
		vector<Triangle> vecViewTriangles;

		for (auto tri : vecTris)
		{
			Triangle triView = matView * tri;
			vecViewTriangles.push_back(triView);
		}

		return vecViewTriangles;
	}

	vector<Triangle> ClipTriangles(vector<Triangle> vecTris, Vector3 planePoint, Vector3 planeNormal)
	{
		vector<Triangle> vecClippedTriangles;
		for (auto tri : vecTris)
		{
			int nClippedTriangles = 0;
			Triangle clipped[2];
			nClippedTriangles = Triangle_ClipAgainstPlane(planePoint, planeNormal, tri, clipped[0], clipped[1]);
			for (int n = 0; n < nClippedTriangles; n++)
			{
				vecClippedTriangles.push_back(clipped[n]);
			}
		}

		return vecClippedTriangles;
	}

	vector<Triangle> ClipEdges(vector<Triangle> vecTris)
	{
		vector<Triangle> vecClippedTris;
		// Loop through all transformed, viewed, projected, and sorted triangles
		for (auto& triToRaster : vecTris)
		{
			// Clip triangles against all four screen edges, this could yield
			// a bunch of triangles, so create a queue that we traverse to 
			//  ensure we only test new triangles generated against planes
			Triangle clipped[2];
			list<Triangle> listTriangles;

			// Add initial triangle
			listTriangles.push_back(triToRaster);
			int nNewTriangles = 1;

			for (int p = 0; p < 4; p++)
			{
				int nTrisToAdd = 0;
				while (nNewTriangles > 0)
				{
					// Take triangle from front of queue
					Triangle test = listTriangles.front();
					listTriangles.pop_front();
					nNewTriangles--;

					// Clip it against a plane. We only need to test each 
					// subsequent plane, against subsequent new triangles
					// as all triangles after a plane clip are guaranteed
					// to lie on the inside of the plane. I like how this
					// comment is almost completely and utterly justified
					switch (p)
					{
						case 0:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
						case 1:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, (float)nHeight - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
						case 2:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
						case 3:	nTrisToAdd = Triangle_ClipAgainstPlane({ (float)nWidth - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
					}

					// Clipping may yield a variable number of triangles, so
					// add these new ones to the back of the queue for subsequent
					// clipping against next planes
					for (int w = 0; w < nTrisToAdd; w++)
						listTriangles.push_back(clipped[w]);
				}

				nNewTriangles = listTriangles.size();
			}

			for (auto &tri : listTriangles)
			{
				vecClippedTris.push_back(tri);
			}
			
		}

		return vecClippedTris;
	}



	void draw(BaseNode *pGameData, BaseNode *pCamera)
	{
		//	camera 
		Vector3 vCameraPos = pCamera->getChild<Transform3D>()->getPosition();
		Vector3 vTarget = pCamera->getChild<Camera>()->getForward();
		vTarget = vTarget + vCameraPos;
		Vector3 vUp = pCamera->getChild<Camera>()->getUp();
		mat4x4 matCamera = matCamera.PointAt(vCameraPos, vTarget, vUp);
		mat4x4 matView = Inverse(matCamera);

		vector<Triangle> vecSceneTriangles;

		while (pGameData->isIterating())
		{
			if (Mesh3D* pMesh = pGameData->getCurrent()->getChild<Mesh3D>())
			{
				if (Transform3D* pTransform = pGameData->getCurrent()->getChild<Transform3D>())
				{
					vector<Triangle> vecTriangles = pMesh->getMesh();

					//	world matrix
					mat4x4 matWorld = worldTransform(pTransform);
					vector<Triangle> vecTransformedTriangles = TransformTriangles(vecTriangles, matWorld);
		
					//	triangles facing away from camera are removed
					vector<Triangle> vecForwardFacingTriangles = BackfaceCulling(vecTransformedTriangles, vCameraPos);
		
					//	handle basic lighting
					vector<Vector3> vecDirectionalLights;
					vecDirectionalLights.push_back(Vector3(0.0f, 0.0f, 1.0f));
					//	vecDirectionalLights.push_back(Vector3(1.0f, 0.0f, 0.0f));
					vector<Triangle> vecLitTris = ProcessLambertLighting(vecForwardFacingTriangles, vecDirectionalLights);
		
					//	view matrix
					vector<Triangle> vecViewTriangles = ViewTriangles(vecLitTris, matView);

					//	clip against near plane
					vector<Triangle> vecZClippedTriangles = ClipTriangles(vecViewTriangles, { 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f });

					//	projection matrix 
					mat4x4 matProjection = matProjection.Projection(90.0f, (float)nHeight / (float)nWidth, 0.1f, 1000.0f);
					vector<Triangle> vecProjectedTriangles = ProjectTriangles(vecZClippedTriangles, matProjection);

					vector<Triangle> vecScaledToScreen = ScaleToScreen(vecProjectedTriangles, nHeight, nWidth);


					vector<Triangle> vecEdgesClippedTriangles = ClipEdges(vecScaledToScreen);

					vecSceneTriangles.insert(vecSceneTriangles.end(), vecEdgesClippedTriangles.begin(), vecEdgesClippedTriangles.end());
				}
			}
		}

		SortAndRasterTriangles(vecSceneTriangles);
	}

public:
	ConsoleRender3D() :
		m_pDepthBuffer(NULL),
		m_fAmbientLight(0.1f),
		ConsoleRender2D()
	{};

	~ConsoleRender3D()
	{
		delete m_pDepthBuffer;
	}

	void init(AFrame* pBuffer) 
	{
		m_pTargetBuffer = pBuffer;
		nHeight = pBuffer->getHeight();
		nWidth = pBuffer->getWidth();
		m_pDepthBuffer = new float[nHeight * nWidth];
	}
};