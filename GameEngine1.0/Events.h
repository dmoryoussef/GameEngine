enum EVENT_TYPE
{
	CONSOLE_KEYBOARD_EVENT,
	CONSOLE_MOUSE_EVENT,
	GAMEPAD_EVENT,
	GUI_EVENT,
	NEW_BASENODE_EVENT,
	TRANSFORMUPDATE_EVENT,
	MOUSEWORLD_EVENT,
	SELECTIONSQUARE_EVENT,
	BASENODE_EVENT
};

enum GUI_EVENT
{
	BUTTON_EVENT,
	NEW_COMPONENT_EVENT,
	CAMERA_WINDOW_EVENT
};

class BaseNodeEvent :
	public _Event
{
private:
	BaseNode* m_pBaseNode;

public:
	BaseNodeEvent(BaseNode* pBaseNode) :
		m_pBaseNode(pBaseNode),
		_Event(BASENODE_EVENT) {};

	BaseNode *getBaseNode()
	{
		return m_pBaseNode;
	}

	template <typename T> T *getBaseNode()
	{
		/*if (typeid(*m_pBaseNode) == typeid(T))
			return static_cast<T*>(m_pBaseNode);
		
		return NULL;*/
		return dynamic_cast<T*>(m_pBaseNode);
	}
};

class GamePadEvent :
	public _Event
{
private:
	int m_nIndex;

	GamePad m_Controller;

public:
	GamePadEvent(GamePad controller) :
		m_Controller(controller),
		_Event(GAMEPAD_EVENT) {}

	GamePad getState()
	{
		return m_Controller;
	}
};

class KeyboardEvent : 
	public _Event
{
private:
	char m_chKey;
	bool m_bKeyDown;
public:
	KeyboardEvent(char chKey, bool bKeyDown) :
		m_chKey(chKey),
		m_bKeyDown(bKeyDown),
		_Event(CONSOLE_KEYBOARD_EVENT) {};

	bool isKeyDown()
	{
		return m_bKeyDown;
	}
	char getKey() { return m_chKey; }
};

class SelectionSquareEvent : public _Event
{
private:
	Vector2 Min;
	Vector2 Max;

public:
	SelectionSquareEvent(Vector2 min, Vector2 max) :
		Min(min),
		Max(max),
		_Event(SELECTIONSQUARE_EVENT) {};

	Vector2 getMin()
	{
		return Min;
	}

	Vector2 getMax()
	{
		return Max;
	}
};

class MouseWorldEvent : public _Event
{
private:
	Vector2 WorldPosition;
	MouseState State;

public:
	MouseWorldEvent(Vector2 position, MouseState state) :
		WorldPosition(position),
		State(state),
		_Event(MOUSEWORLD_EVENT) {};

	Vector2 getWorldPosition()
	{
		return WorldPosition;
	}

	MouseState getState()
	{
		return State;
	}
};

class MouseEvent : 
	public _Event
{
private:
	MouseState State;

public:
	MouseEvent(MouseState state) :
		State(state),
		_Event(CONSOLE_MOUSE_EVENT)
	{}

	MouseState getState()
	{
		return State;
	}
};

class _AGUIEvent : 
	public _Event
{
private:
	int m_nUIEventType;
	BaseNode *m_pComponent;
	bool m_bTopDown;

public:
	_AGUIEvent(int nUIEventType, BaseNode *pComponent, bool btopdown) :
		m_nUIEventType(nUIEventType),
		m_pComponent(pComponent),
		m_bTopDown(btopdown),
		_Event(GUI_EVENT) {};

	int getEventType()
	{
		return m_nUIEventType;
	}

	template <typename T> T *getComponent()
	{
		if (T *pComponent = dynamic_cast<T*>(m_pComponent))
			return pComponent;
		else
			return NULL;
	}

	BaseNode *getComponent()
	{
		return m_pComponent;
	}

	bool isTopDown()
	{
		return m_bTopDown;
	}
};


class NewBaseNodeEvent :
	public _Event
{
private:
	BaseNode *m_pNew;
	BaseNode *m_pParent;

public:
	NewBaseNodeEvent(BaseNode *pNew, BaseNode *pParent) :
		m_pNew(pNew),
		m_pParent(pParent),
		_Event(NEW_BASENODE_EVENT) {};

	BaseNode *getNew()
	{
		return m_pNew;
	}

	BaseNode *getParent()
	{
		return m_pParent;
	}
};

class TransformUpdateEvent :
	public _Event
{
private:
	BaseNode *m_pEntity;
	Vector3 m_Direction;
	Vector3 m_Rotation;
	Vector3 m_Translation;
	

public:
	TransformUpdateEvent(Vector3 direction, Vector3 rotation, BaseNode *pEntity) :
		m_Translation(direction),
		m_Direction(direction),
		m_Rotation(rotation),
		m_pEntity(pEntity),
		_Event(TRANSFORMUPDATE_EVENT) {};

	Vector3 getTranslation()
	{
		return m_Translation;
	}

	Vector3 getRotation()
	{
		return m_Rotation;
	}

	Vector3 getDirection()
	{
		// TODO: change to get ACTION type
		return m_Direction;
	}

	BaseNode *getEntity()
	{
		return m_pEntity;
	}

};