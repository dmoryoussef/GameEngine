class CollisionTile :
	public Tile2D<CollisionTile>
{
private:
	bool m_bBlocking;

public:
	CollisionTile() :
		m_bBlocking(false),
		Tile2D() {};

	bool isBlocking()
	{
		return m_bBlocking;
	}

	void setBlocking(bool bBlocking)
	{
		m_bBlocking = bBlocking;
	}

};

class CollisionTileMap :
	public TileMap<CollisionTile>
{
private:
public:
	CollisionTileMap(Vector2 size) :
		TileMap(size, "CollisionMap") 
	{
		for (int nY = 0; nY < Size.Y; nY++)
			for (int nX = 0; nX < Size.X; nX++)
			{
				if (nY == 0 || nY == Size.Y || nX == Size.X || nX == 0)
					getTile(nY, nX)->setBlocking(true);
				else 
					getTile(nY, nX)->setBlocking(false);
			}
	};

	void render(AFrame *pFrame, Vector2 Min, Vector2 Max)
	{
	}
};