class UIInterface :
	public _GComponent
{
public:
	UIInterface() :
		_GComponent("UIState")
	{
		registerListener(this, CONSOLE_MOUSE_EVENT);
	};

	//	Mouse state
	//		selected
	//		mouseover
	//	popup window
	//	events
};