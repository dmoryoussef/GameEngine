class Physics :
	public _GComponent
{
private:
	Vector3 Gravity;

public:
	Physics() :
		Gravity(0.0001, 0.0, 0.0),
		_GComponent("PHYSICS_ENGINE") {};

	void update(BaseNode *pGameData, int nDeltaTime)
	{
		BaseNode *pEntities = pGameData->getChild<EntityManager>();

		while (pEntities->isIterating())
		{
			if (Transform3D *pTransform = pEntities->getCurrent()->getChild<Transform3D>())
			{
				if (Velocity3D *pVelocity = pEntities->getCurrent()->getChild<Velocity3D>())
				{
					Vector3 Pos = pTransform->getPosition();
					Vector3 Rot = pTransform->getRotation();

					Vector3 TransVel = pVelocity->getTranslation();
					Vector3 RotVel = pVelocity->getRotation();

					Vector3 DeltaRot = RotVel  * nDeltaTime;
					Vector3 DeltaTransl = TransVel * nDeltaTime;
					
					Vector3 newPos = Pos + DeltaTransl;
					Vector3 newRot = Rot + DeltaRot;

					pTransform->setPosition(newPos);
					pTransform->setRotation(newRot);

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
		}
	}
};
