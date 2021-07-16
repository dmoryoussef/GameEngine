class EarthTile :
	public Tile2D<EarthTile>
{
private:
	float m_fElevation;

	//	ore deposit patterns
	//	deep earth	-	evenly distributed - all types
	//					becomes fractally less distributed on surface
	//					more common around volcanic activity
	//
	//	detailed:
	//	solid rock	-	erosion rate .00001
	//	gravel		-	erosion rate .0001
	//	sand		-	erosion rate .001
	//	silt		-	erosion rate .01
	//	clay		-	erosion rate .1 - soft plastic when containing water, hard brittle when dry
	//					usually deposited around stationary water
	//
	//	soil type	-	combination of sand, silt, clay, water
	//					determines growth rate of flora
	//
	//	erosion		-	convert high ranked content to lower
	//				-	needs to be moved to next tile by outside force - weathering/water
	//					erosion rate decreases by rank
	//					ex: rock on this tile -> % gravel to neighbor tile
	//					ex: sand on this tile -> sand and % silt to neighbor tile
	//					ex: silt on this tile -> silt and % clay to next tile

public:
	EarthTile() :
		m_fElevation(0.0) {};

	~EarthTile() {}

	float getElevation() { return m_fElevation; }
	
	void setAltitude(float fAlt)
	{
		m_fElevation = fAlt;
	}

	void erode(float fAmount)
	{
		m_fElevation = m_fElevation * fAmount;
	}

	EarthTile *getLowestAdjacentTile()
	{
		EarthTile *pLowestTile = this;

		if (getValue() > getNorth()->getValue())
			pLowestTile = getNorth();
		if (getValue() > getSouth()->getValue())
			pLowestTile = getSouth();
		if (getValue() > getWest()->getValue())
			pLowestTile = getWest();
		if (getValue() > getEast()->getValue())
			pLowestTile = getEast();

		if (pLowestTile != this)
			return pLowestTile;

		return NULL;
	}

};