class Camera : 
	public _GComponent
{
private:
	Vector3 vForward;
	Vector3 vUpDir;

	Vector2 vPrevMousePosition;
	Vector2 vDeltaPos;

	Vector2 vWorldMin;
	Vector2 vWorldMax;

	void onEvent(_Event* pEvent)
	{
		switch (pEvent->m_eType)
		{
			case CONSOLE_KEYBOARD_EVENT:
			{
				if (pEvent->get<KeyboardEvent>()->getKey() == 'a') // left
				{
					//	get negative right vector
					//	send position update event
					addEvent(new TransformUpdateEvent(-getRight() * 0.01, { 0, 0, 0 }, m_pParent));
				}

				if (pEvent->get<KeyboardEvent>()->getKey() == 'd') // right
				{
					//	get right vector
					//	send position update event
					addEvent(new TransformUpdateEvent(getRight() * 0.01, { 0, 0, 0 }, m_pParent));
				}

				if (pEvent->get<KeyboardEvent>()->getKey() == 'w') // forward
				{
					//	send position update event
					addEvent(new TransformUpdateEvent(vForward * 0.01, { 0, 0, 0 }, m_pParent));
				}

				if (pEvent->get<KeyboardEvent>()->getKey() == 's') // back
				{
					//	use negative forward vector
					//	send position update event
					addEvent(new TransformUpdateEvent(-vForward * 0.01, { 0, 0, 0 }, m_pParent));
				}

				if (pEvent->get<KeyboardEvent>()->getKey() == 32) // up
				{
					//	use negative forward vector
					//	send position update event
					addEvent(new TransformUpdateEvent(-vUpDir * 0.01, { 0, 0, 0 }, m_pParent));
				}

				if (pEvent->get<KeyboardEvent>()->getKey() == 'c') // down  
				{
					//	use negative forward vector
					//	send position update event
					addEvent(new TransformUpdateEvent(vUpDir * 0.01, { 0, 0, 0 }, m_pParent));
				}

				break;
			}

			case CONSOLE_MOUSE_EVENT:
			{
				Vector2 vCurrentMousePosition = pEvent->get<MouseEvent>()->getState().Position;
				
				if (pEvent->get<MouseEvent>()->getState().bLeftButtonDown)
				{
					
					vDeltaPos = vCurrentMousePosition - vPrevMousePosition;
					vDeltaPos = vDeltaPos * 0.005f;
					
				}
				vPrevMousePosition = vCurrentMousePosition;
				break;
			}
		}
	}


public:
	Camera(Vector3 forward, Vector3 up) :
		vForward(forward),
		vUpDir(up),
		vPrevMousePosition(),
		_GComponent("CAMERA") 
	{
		registerListener(this, CONSOLE_KEYBOARD_EVENT);
		registerListener(this, CONSOLE_MOUSE_EVENT);
	};

	void setView(Vector2 vMin, Vector2 vMax)
	{
		vWorldMin = vMin;
		vWorldMax = vMax;
	}

	Vector2 getWorldMin()
	{
		return vWorldMin;
	}
	Vector2 getWorldMax()
	{
		return vWorldMax;
	}

	void update(float fDeltaTime)
	{
		
		vDeltaPos = vDeltaPos * fDeltaTime;
		mat4x4 matRotateX = matRotateX.rotateX(-vDeltaPos.Y);
		mat4x4 matRotateY = matRotateY.rotateY(-vDeltaPos.X);
		mat4x4 matCameraRot = matCameraRot.Identity();
		matCameraRot = matCameraRot * matRotateX;
		matCameraRot = matCameraRot * matRotateY;
		vForward = matCameraRot * vForward;
		//	vUpDir = matCameraRot * vUpDir;// dont do this
		vDeltaPos = { 0, 0 };
	}

	Vector3 getRight()
	{
		return crossProduct(vUpDir, vForward);
	}

	Vector3 getForward() { return vForward; }
	Vector3 getUp() { return vUpDir; }
};