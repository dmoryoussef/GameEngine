class Velocity3D
	: public _GComponent
{
private:
	Vector3 TranslationVelocity;
	Vector3 RotationVelocity;
	// momentum = velocity * mass

public:
	Velocity3D(Vector3 transl, Vector3 rot) :
		TranslationVelocity(transl),
		RotationVelocity(rot),
		_GComponent("Velocity3D") {}

	void update(int nDeltaTime)
	{
		// Vector3 DeltaVelocity = Velocity * nDeltaTime;
		// addEvent(new PhysicsEvent(DeltaVelocity));
	}

	Vector3 getRotation()
	{
		return RotationVelocity;
	}
	Vector3 getTranslation()
	{
		return TranslationVelocity;
	}

	void setRotVelocity(Vector3 velocity)
	{
		RotationVelocity = velocity;
	}

	void setTranslVelocity(Vector3 velocity)
	{
		TranslationVelocity = velocity;
	}
};