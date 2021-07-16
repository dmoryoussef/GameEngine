class Transform3D :
	public _GComponent
{
private:
	Vector3 Position;
	Vector3 Scale;
	Vector3 Rotation;

public:
	Transform3D(Vector3 P, Vector3 R, Vector3 S) :
		Position(P),
		Scale(S),
		Rotation(R),
		_GComponent("Transform3D") {};

	/*
	bool isMouseOver(Vector2 MouseWorldPosition)
	{
		//	convert transform to int from float to correct 
		//	for console resolution

		//	do test:
		if (MouseWorldPosition.Y >= Position.trunc().Y &&
			MouseWorldPosition.Y < Position.trunc().Y + Scale.Y &&
			MouseWorldPosition.X >= Position.trunc().X &&
			MouseWorldPosition.X < Position.trunc().X + Scale.X)
			return true;
		else
			return false;
	}
	*/

	void translate(Vector3 translate)
	{
		Position = Position + translate;
	}

	void setPosition(Vector3 position) { Position = position; }
	void setRotation(Vector3 rotation) { Rotation = rotation; }
	void setScale(Vector3 scale) { Scale = scale; }

	Vector3 getPosition() { return Position; }
	Vector3 getRotation() { return Rotation; }
	Vector3 getScale() { return Scale; }

};