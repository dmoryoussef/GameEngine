class ARender :
	public _GComponent
{
private:
	AFrame *Sprite;
	char m_chAscii;

public:
	ARender(char chA) :
		Sprite(new AFrame(1, 1, BG_BLACK, FG_WHITE)),
		_GComponent("Render")
	{
		APixel pix(chA, BG_BLACK + FG_WHITE);
		Sprite->set(pix, 0, 0);
	}

	ARender() :
		Sprite(new AFrame(3, 3, BG_BLACK, FG_WHITE)),
		_GComponent("Render")
	{

	}
	AFrame *getSprite()
	{
		return Sprite;
	}

	void drawToFrame(AFrame *pFrame, Vector2 Min)
	{
		// handle clipping??
		pFrame->setFrame(Sprite, Min.X, Min.Y);
	}
};