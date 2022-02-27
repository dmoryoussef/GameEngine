class WaterTile :
	public _Tile2D<WaterTile>
{
private:
	bool m_bFlowing;
	
public:
	WaterTile() :
		m_bFlowing(false),
		_Tile2D("WATER_TILE")
	{};
	
	void addValue(float fValue)
	{
		m_fValue = m_fValue + fValue;
	}

	void subValue(float fValue)
	{
		m_fValue = m_fValue - fValue;
		if (m_fValue < 0)
			m_fValue = 0;
	}

};