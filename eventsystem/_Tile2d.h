template <typename TileType>
class Tile2D 
{
private:
	Vector2 m_Position;
	Tile2D *m_pNorth;
	Tile2D *m_pSouth;
	Tile2D *m_pEast;
	Tile2D *m_pWest;

	float m_fValue;
	int m_nTileGroup;

public:
	Tile2D() :
		m_fValue(0.0),
		m_pNorth(NULL),
		m_pSouth(NULL),
		m_pEast(NULL),
		m_pWest(NULL),
		m_nTileGroup(0) {};

	void initTile(Vector2 Position, Tile2D *pNorth, Tile2D *pSouth, Tile2D *pEast, Tile2D *pWest)
	{
		m_Position = Position;
		m_pNorth = pNorth;
		m_pSouth = pSouth;
		m_pEast = pEast;
		m_pWest = pWest;
	}

	float getValue()
	{
		return m_fValue;
	}

	void setValue(float fValue)
	{
		m_fValue = fValue;
	}

	void setGroup(int nGroupNumber)
	{
		m_nTileGroup = nGroupNumber;
	}
	int getGroup() { return m_nTileGroup; }

	TileType *getNorth() { return static_cast<TileType*>(m_pNorth); }
	TileType *getSouth() { return static_cast<TileType*>(m_pSouth); }
	TileType *getEast() { return static_cast<TileType*>(m_pEast); }
	TileType *getWest() { return static_cast<TileType*>(m_pWest); }

	Vector2 getPosition() { return m_Position; }


};
