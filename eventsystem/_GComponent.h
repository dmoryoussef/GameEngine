class _GComponent :
	public BaseNode,
	public EventListener
{
private:
	string m_strDescription;		//	describes what this component does
									//	can be part of pop up window or detail window
public:
	_GComponent(string strName) :
		BaseNode(strName) {};

	void setDescription(string strDescription)
	{
		m_strDescription = strDescription;
	}

	string getDescription()
	{
		return m_strDescription;
	}

	virtual void addComponent(_GComponent *pComponent)
	{
		addChild(pComponent);
	}

	template <typename T>T *get()
	{
		return getChild<T>();
	}
};