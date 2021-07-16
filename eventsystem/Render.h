class Render :
	public _GComponent
{
private:
	AFrame *Sprite;

public:
	Render() :
		Sprite(new AFrame(3, 3, BG_BLACK, FG_WHITE)),
		_GComponent("Render")
	{

	}
	AFrame *getSprite()
	{
		return Sprite;
	}

	void drawToFrame(AFrame *pFrame, Vector2 Min, Vector2 Max)
	{
		pFrame->setFrame(Sprite, Min.Y, Min.X);
	}
};