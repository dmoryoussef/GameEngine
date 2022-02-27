class Transform3D :
	public _GComponent
{
private:
	Vector3 vPosition;
	Vector3 vScale;
	Vector3 vRotation;

	Vector3 vDeltaTranslate;
	Vector3 vDeltaRotate;

	void onEvent(_Event *pEvent)
	{
		switch (pEvent->m_eType)
		{
			case TRANSFORMUPDATE_EVENT:
			{
				BaseNode *pParent = pEvent->get<TransformUpdateEvent>()->getEntity();

				if (getParent() == pParent)
				{
					////Position.X = Position.X + pEvent->get<ControllerEvent>()->getDirection().X;
					//Vector3 Radians = pEvent->get<TransformUpdateEvent>()->getRotation();
					//Rotation = Rotation + Radians;
					//
					//float fForwardSpeed = pEvent->get<TransformUpdateEvent>()->getDirection().Y;

					//Vector3 Direction = pEvent->get<TransformUpdateEvent>()->getDirection();
					//Position = Position + (getForward() * fForwardSpeed);

					Vector3 trans = pEvent->get<TransformUpdateEvent>()->getTranslation();
					vDeltaTranslate = vDeltaTranslate + trans;
					
					Vector3 rot = pEvent->get<TransformUpdateEvent>()->getRotation();
					vDeltaRotate = vDeltaRotate + rot;

				}
			}
			break;
		}
	}

public:
	Transform3D(Vector3 P, Vector3 R, Vector3 S) :
		vPosition(P),
		vScale(S),
		vRotation(R),
		_GComponent("Transform3D") 
	{
		registerListener(this, TRANSFORMUPDATE_EVENT);
	};

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

	void update(float fDeltaTime)
	{
		if (vDeltaTranslate.magnitude() != 0)
		{
			vDeltaTranslate = vDeltaTranslate * fDeltaTime;
			translate(vDeltaTranslate);
			vDeltaTranslate = { 0, 0, 0 };
		}
		
		if (vDeltaRotate.magnitude() != 0)
		{
			vDeltaRotate = vDeltaRotate * fDeltaTime;
			vRotation = vRotation + vDeltaRotate;
			vDeltaRotate = { 0, 0, 0 };
		}

	}

	void draw(AFrame *pFrame)
	{
		pFrame->set("TRANSLATION [" + toString<float>(vPosition.X) + "x" + toString<float>(vPosition.Y) + "x" + toString<float>(vPosition.Z) + "]", 2, 2, FG_WHITE + BG_BLACK);
		pFrame->set("ROTATION    [" + toString<float>(vRotation.X) + "x" + toString<float>(vRotation.Y) + "x" + toString<float>(vRotation.Z) + "]", 3, 2, FG_WHITE + BG_BLACK);
	}

	void translate(Vector3 translate)
	{
		vPosition = vPosition + translate;
	}

	void setPosition(Vector3 position) { vPosition = position; }
	void setRotation(Vector3 rotation) { vRotation = rotation; }
	void setScale(Vector3 scale) { vScale = scale; }

	Vector3 getForward()
	{
		Vector3 Forward(0, 0, 1);

		mat4x4 matRotateX = matRotateX.rotateX(vRotation.X);
		mat4x4 matRotateY = matRotateY.rotateY(vRotation.Y);
		mat4x4 matRotateZ = matRotateZ.rotateZ(vRotation.Z);

		Forward = matRotateX * Forward;
		Forward = matRotateY * Forward;
		Forward = matRotateZ * Forward;
		
		return Forward;
	}


	Vector3 getPosition() { return vPosition; }
	Vector3 getRotation() { return vRotation; }
	Vector3 getScale() { return vScale; }

};