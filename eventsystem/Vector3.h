#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3
{
	float X;
	float Y;
	float Z;
	float W;;

	Vector3() :
		X(0.0),
		Y(0.0),
		Z(0.0),
		W(1.0){};

	Vector3(float x, float y, float z) :
		X(x),
		Y(y),
		Z(z),
		W(1.0) {};

	float magnitude()
	{
		return sqrt((Y * Y) + (X * X) + (Z * Z));
	}

	Vector3 toInt()
	{
		int nY = int(Y);
		int nX = int(X);
		int nZ = int(Z);
		Vector3 Int(nX, nY, nZ);
		return Int;
	}

	Vector3 normalized()
	{
		float l = magnitude();
		return Vector3(X /= l, Y /= l, Z /= l);
	}
};

Vector3 operator*(Vector3 A, int nScaler)
{
	Vector3 operation(A.X * nScaler, A.Y * nScaler, A.Z * nScaler);
	return operation;
}

Vector3 operator+(Vector3 A, Vector3 B)
{
	Vector3 operation(A.X + B.X, A.Y + B.Y, A.Z + B.Z);
	return operation;
}

Vector3 operator-(Vector3 A, Vector3 B)
{
	return Vector3 (A.X - B.X, A.Y - B.Y, A.Z - B.Z);
}

Vector3 crossProduct(Vector3 line1, Vector3 line2)
{
	return Vector3(line1.Y * line2.Z - line1.Z * line2.Y, 
				   line1.Z * line2.X - line1.X * line2.Z, 
				   line1.X * line2.Y - line1.Y * line2.X);
}

float dotProduct(Vector3 A, Vector3 B)
{
	return (A.X * B.X) + (A.Y * B.Y) + (A.Z * B.Z);
}


#endif