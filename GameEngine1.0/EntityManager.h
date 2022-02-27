class EntityManager :
	public BaseNode
{
private:

public:
	EntityManager() :
		BaseNode("EntityManager") {};

	BaseNode *createEntity(string sName)
	{
		//	add empty entity to list
		BaseNode *pEntity = new BaseNode(sName);
		addChild(pEntity);
		return pEntity;
	}
};