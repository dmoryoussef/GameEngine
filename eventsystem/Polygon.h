struct Triangle
{
	Vector3 A;
	Vector3 B;
	Vector3 C;

	APixel Pixel;

	Triangle() :
		A({ 0.0, 0.0, 0.0 }),
		B({ 0.0, 0.0, 0.0 }),
		C({ 0.0, 0.0, 0.0 }) {};

	Triangle(Vector3 a, Vector3 b, Vector3 c) :
		A(a),
		B(b),
		C(c) {};

	Vector3 normal()
	{
		Vector3 lineA = B - A;
		Vector3 lineB = C - A;

		return crossProduct(lineA, lineB);
	}

};

struct mat2x2
{
	float m[2][2] = { 0 };

	mat2x2 Rotate(float fAngleRad)
	{
		mat2x2 matRotate;
		matRotate.m[0][0] = cosf(fAngleRad);
		matRotate.m[0][1] = sinf(fAngleRad);
		matRotate.m[1][0] = -sinf(fAngleRad);
		matRotate.m[1][1] = cosf(fAngleRad);
		return matRotate;
	}

	mat2x2 Scale(Vector2 scale)
	{
		mat2x2 matScale;
		matScale.m[0][0] = scale.X;
		matScale.m[1][1] = scale.Y;
		return matScale;
	}

	mat2x2 Translate(Vector2 transl)
	{
		mat2x2 matRotate;
		matRotate.m[0][0] = transl.X;
		matRotate.m[0][1] = transl.Y;
		return matRotate;
	}

};

Vector2 operator*(Vector2 &vec, mat2x2 &mat)
{
	Vector2 out;
	out.X = vec.X * mat.m[0][0] + vec.Y * mat.m[1][0];
	out.Y = vec.X * mat.m[0][1] + vec.Y * mat.m[1][1];
	
	return out;
}

class Polygon2D
{
public:
	vector<Vector2> Verticies;

	void draw(AFrame *pBuffer)
	{
		for (int nI = 0; nI < Verticies.size() - 1; nI++)
		{
			pBuffer->drawLine(Verticies[nI], Verticies[nI + 1], BG_BLACK + FG_WHITE);
		}

		pBuffer->drawLine(Verticies[Verticies.size() - 1], Verticies[0], BG_BLACK + FG_WHITE);
	}

	void scale(Vector2 scale)
	{
		mat2x2 matScale = matScale.Scale(scale);
		for (auto &vert : Verticies)
		{
			vert = vert * matScale;
		}
	}

	void translate(Vector2 transl)
	{
		for (auto &vert : Verticies)
		{
			vert = vert + transl;
		}
	}

	void rotate(float fRad)
	{
		mat2x2 matRot = matRot.Rotate(fRad);
		for (auto &vert : Verticies)
		{
			vert = vert * matRot;
		}
	}

};

