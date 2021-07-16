template <typename TileType> class TileMap : 
	public BaseNode
{
protected:
	Vector2 Size;
	TileType *m_pTileMap;
	int m_nTotalGroups;

	void initialize()
	{
		m_pTileMap = new TileType[Size.Y * Size.X];

		for (int nY = 0; nY < Size.Y; nY++)
			for (int nX = 0; nX < Size.X; nX++)
			{
				TileType *Current = getTile(nY, nX);

				Current->initTile(Vector2(nY, nX), getTile(nY - 1, nX), getTile(nY + 1, nX), getTile(nY, nX + 1), getTile(nY, nX - 1));
			}

	}



public:
	TileMap(Vector2 size, string strName) :
		m_pTileMap(NULL),
		Size(size),
		m_nTotalGroups(0),
		BaseNode(strName)
	{
		initialize();
	};
	~TileMap() 
	{
		delete m_pTileMap; 
	}

	TileType *getTile(int nY, int nX)
	{
		if (nY <= Size.Y && nX <= Size.X)
			return &m_pTileMap[(nX & int(Size.X) - 1) + int(Size.X) * (nY & int(Size.Y) - 1)];
		else
			return NULL;
	}

	template <typename T>
	T *getTile(int nY, int nX)
	{
		BaseNode *pParent = getParent();
		while (pParent->isIterating())
		{
			TileMap *pTileMap = pParent->getCurrent<TileMap>();
			BaseNode *pTile = pTileMap->getTile(nY, nX);
			if (typeid(*pTile) == typeid(T))
				return static_cast<T*>(pTile);
		}

		return NULL;
	}

	TileType *getTile(Vector2 position)
	{
		return &m_pTileMap[(int(position.X) & int(Size.X) - 1) + int(Size.X) * (int(position.Y) & int(Size.Y) - 1)];
	}

	Vector2 getSize() { return Size; }
};