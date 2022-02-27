class Demo3d : public Game
{
private:
	void onEvent(_Event* pEvent)
	{
		Game::onEvent(pEvent);
	}

	BaseNode* addPrimitiveCube(Transform3D *pTransform)
	{
		BaseNode* pEntity = new BaseNode("Cube");
		pEntity->addChild(pTransform);
		pEntity->addChild(new Mesh3D("cube.obj"));
		return pEntity;
	}

	BaseNode *demoEntity()
	{
		BaseNode* pEntity = new BaseNode("Cube");
		pEntity->addChild(new Transform3D({ 0.0, 0.0, 5.0 }, { 0.0, 0.0, 0 }, { 1.0, 1.0, 1.0 }));
		pEntity->addChild(new Velocity3D({ 0.0, 0, 0 }, { 0.00, 0.00, 0.0 }));
		pEntity->addChild(new Mesh3D("cube.obj"));
		return pEntity;
	}

	BaseNode *camera()
	{
		// move this into the game later
		BaseNode* pCamera = new BaseNode("Camera");
		pCamera->addChild(new Transform3D({ 0.0, 0.0, -10.0 }, { 0, 0, 0 }, { 0, 0, 0 }));
		pCamera->addChild(new Camera({ 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 }));
		//pCamera->addChild(new UserController(4));	// 0 = gamepad 1, 4 = keyboard/mouse
		m_pGameData->getChild<EntityManager>()->addChild(pCamera);
		return pCamera;
	}

public:
	Demo3d(int nWidth, int nHeight) :
		Game(nWidth, nHeight)
	{
		registerListener(this, GUI_EVENT);

		m_pGameData->add(new EntityManager());
		//m_pGameData->getChild<EntityManager>()->addChild(addPrimitiveCube(new Transform3D({ 0, 0, 0 }, { 0, 0, 0 }, { .1, 2, 2 })));
		m_pGameData->getChild<EntityManager>()->addChild(demoEntity());
		m_pGuiData->addComponent(new CameraWindow(new ConsoleRender3D(), camera(), ALIGN_LEFT));
		m_pGuiData->addComponent(new DiagWindow(ALIGN_RIGHT));
	}
};