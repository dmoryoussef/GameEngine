
struct mat4x4
{
	float m[4][4] = { 0 };

	void RotateX(float fAngleRad)
	{
		m[0][0] = 1;
		m[1][1] = cosf(fAngleRad);
		m[1][2] = sinf(fAngleRad);
		m[2][1] = -sinf(fAngleRad);
		m[2][2] = cosf(fAngleRad);
		m[3][3] = 1;
	}

	void RotateY(float fAngleRad)
	{
		m[0][0] = cosf(fAngleRad);
		m[0][2] = sinf(fAngleRad);
		m[2][0] = -sinf(fAngleRad);
		m[1][1] = 1.0f;
		m[2][2] = cosf(fAngleRad);
		m[3][3] = 1.0f;
	}

	void RotateZ(float fAngleRad)
	{
		m[0][0] = cosf(fAngleRad);
		m[0][1] = sinf(fAngleRad);
		m[1][0] = -sinf(fAngleRad);
		m[1][1] = cosf(fAngleRad);
		m[2][2] = 1.0f;
		m[3][3] = 1.0f;
	}

	void Translate(float x, float y, float z)
	{
		m[0][0] = 1.0f;
		m[1][1] = 1.0f;
		m[2][2] = 1.0f;
		m[3][3] = 1.0f;
		m[3][0] = x;
		m[3][1] = y;
		m[3][2] = z;
	}

	mat4x4 Identity()
	{
		mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;

		return matrix;
	}

	mat4x4 Scale(float x, float y, float z)
	{
		mat4x4 matScale;
		matScale.m[0][0] = x;
		matScale.m[1][1] = y;
		matScale.m[2][2] = z;
		matScale.m[3][3] = 1;
		return matScale;
	}

	mat4x4 rotateX(float fAngleRad)
	{
		mat4x4 matRotX;
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fAngleRad);
		matRotX.m[1][2] = sinf(fAngleRad);
		matRotX.m[2][1] = -sinf(fAngleRad);
		matRotX.m[2][2] = cosf(fAngleRad);
		matRotX.m[3][3] = 1;
		return matRotX;
	}

	mat4x4 rotateY(float fAngleRad)
	{
		mat4x4 matRotY;
		matRotY.m[0][0] = cosf(fAngleRad);
		matRotY.m[0][2] = sinf(fAngleRad);
		matRotY.m[2][0] = -sinf(fAngleRad);
		matRotY.m[1][1] = 1.0f;
		matRotY.m[2][2] = cosf(fAngleRad);
		matRotY.m[3][3] = 1.0f;
		return matRotY;
	}

	mat4x4 rotateZ(float fAngleRad)
	{
		mat4x4 matRotZ;
		matRotZ.m[0][0] = cosf(fAngleRad);
		matRotZ.m[0][1] = sinf(fAngleRad);
		matRotZ.m[1][0] = -sinf(fAngleRad);
		matRotZ.m[1][1] = cosf(fAngleRad);
		matRotZ.m[2][2] = 1.0f;
		matRotZ.m[3][3] = 1.0f;
		return matRotZ;
	}

	mat4x4 Translation(float x, float y, float z)
	{
		mat4x4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		matrix.m[3][0] = x;
		matrix.m[3][1] = y;
		matrix.m[3][2] = z;
		return matrix;
	}

	mat4x4 Projection(float fFovDegrees, float fAspectRatio, float fNear, float fFar)
	{
		float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
		mat4x4 matrix;
		matrix.m[0][0] = fAspectRatio * fFovRad;
		matrix.m[1][1] = fFovRad;
		matrix.m[2][2] = fFar / (fFar - fNear);
		matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matrix.m[2][3] = 1.0f;
		matrix.m[3][3] = 0.0f;
		return matrix;
	}

	mat4x4 PointAt(Vector3 &pos, Vector3 &target, Vector3 &up)
	{
		// Calculate new forward direction
		Vector3 Forward = target - pos;
		Forward = Forward.normalized();

		// Calculate new Up direction
		Vector3 a = Forward * dotProduct(up, Forward);
		Vector3 Up = up - a;
		Up = Up.normalized();

		// New Right direction is easy, its just cross product
		Vector3 Right = crossProduct(Up, Forward);

		// Construct Dimensioning and Translation Matrix
		mat4x4 matrix;

		matrix.m[0][0] = Right.X;	matrix.m[0][1] = Right.Y;	matrix.m[0][2] = Right.Z;	matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = Up.X;		matrix.m[1][1] = Up.Y;		matrix.m[1][2] = Up.Z;		matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = Forward.X;	matrix.m[2][1] = Forward.Y;	matrix.m[2][2] = Forward.Z;	matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = pos.X;		matrix.m[3][1] = pos.Y;		matrix.m[3][2] = pos.Z;		matrix.m[3][3] = 1.0f;

		return matrix;
	}
};

mat4x4 Inverse(mat4x4 &m) // Only for Rotation/Translation Matrices
	{
		mat4x4 matrix;

		matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
		matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
		matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
		matrix.m[3][3] = 1.0f;

		return matrix;
	}

Vector3 operator*(mat4x4 &m, Vector3 &vec)
{
	Vector3 v;

	v.X = vec.X * m.m[0][0] + vec.Y * m.m[1][0] + vec.Z * m.m[2][0] + vec.W * m.m[3][0];
	v.Y = vec.X * m.m[0][1] + vec.Y * m.m[1][1] + vec.Z * m.m[2][1] + vec.W * m.m[3][1];
	v.Z = vec.X * m.m[0][2] + vec.Y * m.m[1][2] + vec.Z * m.m[2][2] + vec.W * m.m[3][2];
	v.W = vec.X * m.m[0][3] + vec.Y * m.m[1][3] + vec.Z * m.m[2][3] + vec.W * m.m[3][3];

	return v;
}

mat4x4 operator*(mat4x4 &m1, mat4x4 &m2)
{
	mat4x4 matrix;

	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + 
							 m1.m[r][1] * m2.m[1][c] + 
							 m1.m[r][2] * m2.m[2][c] + 
							 m1.m[r][3] * m2.m[3][c];

	return matrix;
}

Triangle operator*(mat4x4 &m, Triangle &t)
{
	Triangle out = t;
	out.A = m * t.A;
	out.B = m * t.B;
	out.C = m * t.C;
	return out;
}

Triangle operator+(Triangle &tri, Vector3 &vec)
{
	Triangle out = tri;
	out.A = tri.A + vec;
	out.B = tri.B + vec;
	out.C = tri.C + vec;
	return out;
}
