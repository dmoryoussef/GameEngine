enum EVENT_TYPE
{
	CONSOLE_KEYBOARD_EVENT,
	CONSOLE_MOUSE_EVENT,
	GUI_EVENT,
	NEW_BASENODE_EVENT,
};

enum GUI_EVENT
{
	BUTTON_EVENT,
	NEW_COMPONENT_EVENT,
	CAMERA_WINDOW_EVENT
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

class MouseEvent : 
	public _Event
{
private:
	int m_nX;
	int m_nY;
	Vector2 Position;
	bool m_bLeftButtonDown;

public:
	MouseEvent(int nY, int nX, bool bLeftButtonDown) :
		m_nY(nY),
		m_nX(nX),
		m_bLeftButtonDown(bLeftButtonDown),
		Position(nY, nX),
		_Event(CONSOLE_MOUSE_EVENT) {}


	bool isLeftButtonDown()
	{
		return m_bLeftButtonDown;
	}

	int getX() { return m_nX; }
	int getY() { return m_nY; }
	Vector2 getPosition()
	{
		return Position;
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