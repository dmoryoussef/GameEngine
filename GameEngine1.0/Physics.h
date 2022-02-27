class Physics :
	public _GComponent
{
private:
	float m_fDeltaTime;
	
	Vector3 Gravity;


	void updateAcceleration(Velocity3D *pVelocity, Acceleration3D *pAcceleration, float fDeltaTime)
	{
		Vector3 PosVel = pVelocity->getTranslation();
		Vector3 RotVel = pVelocity->getRotation();

		Vector3 TransAccel= pAcceleration->getTranslation();
		Vector3 RotAccel = pAcceleration->getRotation();

		Vector3 DeltaRot = RotAccel * fDeltaTime;
		Vector3 DeltaTransl = TransAccel* fDeltaTime;

		Vector3 newPos = PosVel + DeltaTransl;
		Vector3 newRot = RotVel + DeltaRot;

		pVelocity->setTranslVelocity(newPos);
		pVelocity->setRotVelocity(newRot);
	}

	void updateVelocity(Transform3D *pTransform, Velocity3D *pVelocity, float fDeltaTime)
	{
		Vector3 Pos = pTransform->getPosition();
		Vector3 Rot = pTransform->getRotation();
		Vector3 TransVel = pVelocity->getTranslation();
		Vector3 RotVel = pVelocity->getRotation();


		Vector3 DeltaRot = RotVel * fDeltaTime;
		Vector3 DeltaTransl = TransVel * fDeltaTime;

		Vector3 newPos = Pos + DeltaTransl;
		Vector3 newRot = Rot + DeltaRot;

		
		pTransform->setPosition(newPos);
		pTransform->setRotation(newRot);
	}

	void onEvent(_Event* pEvent)
	{
		switch (pEvent->m_eType)
		{

		}
	}


public:
	Physics() :
		m_fDeltaTime(0.0),
		Gravity(0.0001, 0.0, 0.0),
		_GComponent("PHYSICS_ENGINE") {};

	void update(BaseNode *pGameData, float fDeltaTime)
	{
		BaseNode *pEntities = pGameData->getChild<EntityManager>();

		while (pEntities->isIterating())
		{
			//	Handle Velocity
			if (Transform3D *pTransform = pEntities->getCurrent()->getChild<Transform3D>())
			{
				if (Velocity3D *pVelocity = pEntities->getCurrent()->getChild<Velocity3D>())
				{
					// handleAcceleration(fDeltaTime);
					updateVelocity(pTransform, pVelocity, fDeltaTime);

					//Vector3 Velocity = pVelocity->getVelocity();
					//Vector3 DeltaGravity = Gravity * nDeltaTime;
					//Vector3 DeltaVelocity = Velocity * nDeltaTime;
					//
					//pTransform->setPosition(pTransform->getPosition() + DeltaVelocity);

					//if (pTransform->getPosition().Y < 35)
					//	pVelocity->setVelocity(pVelocity->getVelocity() + DeltaGravity);

					//if (pTransform->getPosition().Y >= 35)
					////	bounce off "ground"
					//{
					//	float fY = pVelocity->getVelocity().Y - 0.01;
					//	float fX = pVelocity->getVelocity().X;
					//	float fZ = pVelocity->getVelocity().Z;
					//	pVelocity->setVelocity({ -fY, fX, fZ });
					//}

				}
			}

			// Handle static collision detection

		}
	}
};
