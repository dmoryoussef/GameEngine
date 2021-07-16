class _ARenderer3D
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

public:
	_ARenderer3D() :
		fTheta(30)
	{
		pCube1 = new Mesh3D("cube.obj");
	};
	~_ARenderer3D()
	{
		delete pCube1;
	}

	void Render3DTest(AFrame *pBuffer, int x, int z)
	{
		fTheta += .02;

		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = pBuffer->getSize().Y / pBuffer->getSize().X;
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
		mat4x4 matProj;
		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;

		mat4x4 matRotX;
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta);
		matRotX.m[1][2] = sinf(fTheta);
		matRotX.m[2][1] = -sinf(fTheta);
		matRotX.m[2][2] = cosf(fTheta);
		matRotX.m[3][3] = 1;

		mat4x4 matRotZ;
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		mat4x4 matRotY;
		matRotY.m[0][0] = cosf(fTheta);
		matRotY.m[0][2] = sinf(fTheta);
		matRotY.m[2][0] = -sinf(fTheta);
		matRotY.m[1][1] = 1.0f;
		matRotY.m[2][2] = cosf(fTheta);
		matRotY.m[3][3] = 1.0f;

		mat4x4 matTransl;
		matTransl.m[0][0] = 1.0f;
		matTransl.m[1][1] = 1.0f;
		matTransl.m[2][2] = 1.0f;
		matTransl.m[3][3] = 1.0f;
		matTransl.m[3][0] = x;
		matTransl.m[3][1] = 55;
		matTransl.m[3][2] = z;


		mat4x4 matScale;
		matScale.m[0][0] = 5; //x 
		matScale.m[1][1] = 5; //y
		matScale.m[2][2] = 5; //z
		matScale.m[3][3] = 1;

		Vector3 Camera;

		mat4x4 matWorld;
		matWorld = matWorld.Identity();
		matWorld = matWorld * matScale;
		matWorld = matWorld * matRotX;
		matWorld = matWorld * matRotY;
		matWorld = matWorld * matRotZ;
		matWorld = matWorld * matTransl;

		for (auto Tri : pCube1->getMesh())
		{
			Tri = matWorld * Tri;
			/*Tri = matRotX * Tri;
			Tri = matRotZ * Tri;
			Tri = matRotY * Tri;
			Tri = matScale * Tri;
			Tri = matTransl * Tri;*/

			/*MultiplyMatrixVector(Tri.A, Tri.A, matRotX);
			MultiplyMatrixVector(Tri.B, Tri.B, matRotX);
			MultiplyMatrixVector(Tri.C, Tri.C, matRotX);

			MultiplyMatrixVector(Tri.A, Tri.A, matScale);
			MultiplyMatrixVector(Tri.B, Tri.B, matScale);
			MultiplyMatrixVector(Tri.C, Tri.C, matScale);

			MultiplyMatrixVector(Tri.A, Tri.A, matTransl);
			MultiplyMatrixVector(Tri.B, Tri.B, matTransl);
			MultiplyMatrixVector(Tri.C, Tri.C, matTransl);
*/

/*Vector3 TriLineA;
TriLineA.X = Tri.B.X - Tri.A.X;
TriLineA.Y = Tri.B.Y - Tri.A.Y;
TriLineA.Z = Tri.B.Z - Tri.A.Z;

Vector3 TriLineB;
TriLineB.X = Tri.C.X - Tri.A.X;
TriLineB.Y = Tri.C.Y - Tri.A.Y;
TriLineB.Z = Tri.C.Z - Tri.A.Z;

Vector3 TriNormal;
TriNormal.X = TriLineA.Y * TriLineB.Z - TriLineA.Z * TriLineB.Y;
TriNormal.Y = TriLineA.Z * TriLineB.X - TriLineA.X * TriLineB.Z;
TriNormal.Z = TriLineA.X * TriLineB.Y - TriLineA.Y * TriLineB.X;

float L = sqrtf((TriNormal.X*TriNormal.X) + (TriNormal.Y*TriNormal.Y) + (TriNormal.Z*TriNormal.Z));
TriNormal.X /= L;
TriNormal.Y /= L;
TriNormal.Z /= L;*/

//	if (TriNormal.Z < 0.0)
/*	if ((TriNormal.X * (Tri.C.X - Camera.X)) +
		(TriNormal.Y * (Tri.C.Y - Camera.Y)) +
		(TriNormal.Z * (Tri.C.Z - Camera.Z)) < 0.0)*/
			{
				/*Tri = matProj * Tri;*/
				MultiplyMatrixVector(Tri.A, Tri.A, matProj);
				MultiplyMatrixVector(Tri.B, Tri.B, matProj);
				MultiplyMatrixVector(Tri.C, Tri.C, matProj);

				pBuffer->drawTriangle({ Tri.A.X, Tri.A.Y }, { Tri.B.X, Tri.B.Y }, { Tri.C.X, Tri.C.Y }, BG_BLACK + FG_WHITE);
			}
		}


	}

	void Render3D(BaseNode *pGameData, AFrame *pBuffer, BaseNode *pCamera)
	{
		while (pGameData->isIterating())
		{
			if (Transform3D *pTransform = pGameData->getCurrent<_GComponent>()->get<Transform3D>())
				if (Mesh3D *pMesh = pGameData->getCurrent<_GComponent>()->get<Mesh3D>())
				{
					Vector3 Position = pTransform->getPosition();
					Vector3 Rotation = pTransform->getRotation();
					Vector3 Scale = pTransform->getScale();
					//	projection matrix
					float fNear = 0.1;
					float fFar = 1000.0;
					float fFov = 90.0;
					float fAspectRatio = pBuffer->getSize().Y / pBuffer->getSize().X;
					fTheta += .05;

					mat4x4 matProj = matProj.Projection(fFov, fAspectRatio, fNear, fFar);
					mat4x4 matRotZ = matRotZ.rotateZ(Rotation.Z);
					mat4x4 matRotX = matRotX.rotateX(Rotation.X);
					mat4x4 matRotY = matRotY.rotateY(Rotation.Y);
					mat4x4 matTranslate = matTranslate.Translation(Position.X, Position.Y, Position.Z);
					mat4x4 matScale = matScale.Scale(Scale.X, Scale.Y, Scale.Z);

					Vector3 lookDir(0.0, 0.0, 1.0);
					Vector3 cameraPos = pCamera->getChild<Transform3D>()->getPosition();
					Vector3 up(0.0, 1.0, 0.0);
					Vector3 target = cameraPos + lookDir;
					mat4x4 matCamera = matCamera.PointAt(cameraPos, target, up);
					matCamera = matCamera.Inverse(matCamera);

					// Illumination
					Vector3 lightDir(1.0, 1.0, 1.0);
					lightDir = lightDir.normalized();

					vector<Triangle> trisToRaster;
					vector<Triangle> mesh = pMesh->getMesh();
					for (auto tri : mesh)
					{
						Triangle Transformed = tri;
						Transformed = matRotX * tri;
						Transformed = matRotZ * Transformed;
						Transformed = matRotY * Transformed;
						Transformed = matScale * Transformed;
						Transformed = matTranslate * Transformed;

						Transformed = matCamera * Transformed;

						Vector3 TriNormal = Transformed.normal();
						TriNormal = TriNormal.normalized();

						Vector3 cameraRay = Transformed.A - cameraPos;

						//if (dotProduct(TriNormal, cameraRay) < 0.0)
						{
							Triangle triProjected = matProj * Transformed;

							// How similar is normal to light direction
							APixel pixel = getGreyscaleColor(dotProduct(TriNormal, lightDir));
							triProjected.Pixel = pixel;

							trisToRaster.push_back(triProjected);
						}

						sort(trisToRaster.begin(), trisToRaster.end(),
							[](Triangle &t1, Triangle &t2)	// this is a lambda function! (*learn about this later*)
						{
							// average triangle points on z axis
							float z1 = (t1.A.Z + t1.B.Z + t1.C.Z) / 3;
							float z2 = (t2.A.Z + t2.B.Z + t2.C.Z) / 3;
							return z1 > z2;
						});

						for (auto &Tri : trisToRaster)
						{
							/*pBuffer->fillTriangle(Tri.A.X, Tri.A.Y,
												  Tri.B.X, Tri.B.Y,
												  Tri.C.X, Tri.C.Y,
												  Tri.Pixel);*/

							pBuffer->drawTriangle({ Tri.A.X, Tri.A.Y }, { Tri.B.X, Tri.B.Y }, { Tri.C.X, Tri.C.Y }, BG_BLACK + FG_WHITE);

						}
					}
				}
		}
	}

};