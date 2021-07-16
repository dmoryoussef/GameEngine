#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
	float Y;
	float X;

	Vector2() :
		Y(0.0),
		X(0.0) {};

	Vector2(float y, float x) :
		Y(y),
		X(x) {};


	float magnitude()
	{
		return sqrt((Y * Y) + (X * X));
	}

	Vector2 normalize()
	{
		float fMagnitude = magnitude();
		return Vector2((Y / fMagnitude), (X / fMagnitude));
	}

	Vector2 trunc()
	{
		int nY = int(Y);
		int nX = int(X);
		return Vector2(nY, nX);
	}

};

bool operator !=(Vector2 A, Vector2 B)
{
	if (A.X != B.X)
		return true;

	if (A.Y != B.Y)
		return true;

	return false;
}

bool operator ==(Vector2 A, Vector2 B)
{
	if (A.X == B.X && A.Y == B.Y)
		return true;
	else
		return false;
}

Vector2 operator+(Vector2 A, Vector2 B)
{
	Vector2 Add(A.Y + B.Y, B.X + A.X);
	return Add;
}

Vector2 operator-(Vector2 A, Vector2 B)
{
	Vector2 Subtract(A.Y - B.Y, A.X - B.X);
	return Subtract;
}

Vector2 operator*(Vector2 A, int nMultiplier)
{
	Vector2 Multiply(A.Y * nMultiplier, A.X * nMultiplier);
	return Multiply;
}

Vector2 operator*(Vector2 A, float fMultiplier)
{
	Vector2 Multiply(A.Y * fMultiplier, A.X * fMultiplier);
	return Multiply;
}

bool operator>(Vector2 A, Vector2 B)
{
	if (A.Y > B.Y &&
		A.X > B.X)
		return true;
	else return false;
}

bool operator<(Vector2 A, Vector2 B)
{
	if (A.Y < B.Y &&
		A.X < B.X)
		return true;
	else return false;
}

Vector2 getMax(Vector2 A, Vector2 B)
{
	if (A.Y > B.Y)
	{
		if (A.X > B.X)
			return A;
		else
			return B;
	}
	else
	{
		if (A.X > B.X)
			return A;
		else
			return B;
	}

}

Vector2 getMin(Vector2 A, Vector2 B)
{
	if (A.Y < B.Y)
	{
		if (A.X < B.X)
			return A;
		else
			return B;
	}
	else
	{
		if (A.X < B.X)
			return A;
		else
			return B;
	}

}

float dotProduct(Vector2 A, Vector2 B)
{
	return (A.Y * B.Y) + (A.X * B.X);
}

float hypotenuse(Vector2 &A, Vector2 &B)
{
	float hypo = sqrt((abs(A.X - B.X) * abs(A.X - B.X)) + (abs(A.Y - B.Y) * abs(A.Y - B.Y)));
	return hypo;
}

#endif