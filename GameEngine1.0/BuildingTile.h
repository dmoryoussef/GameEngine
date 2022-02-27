class BuildingTile :
	public _Tile2D<BuildingTile>
{
private:
	int m_nBuildingType;

public:
	BuildingTile() :
		m_nBuildingType(1),
		_Tile2D("BUILDING_TILE") {};

	void setBuildingType(int nType)
	{
		m_nBuildingType = nType;
	}

	int getType()
	{
		return m_nBuildingType;
	}
};