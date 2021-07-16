class EarthTileMap :
	public TileMap<EarthTile>
{
private:
	int m_nAsciiCode[9] = { 32, 176, 177, 178, 32, 176, 177, 178, 219 };
	int m_nRenderColor[9] =
	{
		BG_BLACK,
		BG_BLACK + FG_DARKGREY,
		BG_BLACK + FG_DARKGREY,
		BG_BLACK + FG_DARKGREY,
		BG_DARKGREY,
		BG_DARKGREY + FG_WHITE,
		BG_DARKGREY + FG_WHITE,
		BG_DARKGREY + FG_WHITE,
		FG_WHITE
	};

	int m_nStartSampleSize;			// feature size randomness of map, decreases with each algorithm pass
	int m_nCurrentSampleSize;
	int m_nMaxRandomAltitude;
	float m_fRandomScale;
	bool m_bComplete;
	bool m_bGroupsAssigned;
	int m_nTicks;

public:
	EarthTileMap(Vector2 size) :
		m_bComplete(false),
		m_bGroupsAssigned(false),
		m_nTicks(1),
		TileMap(size, "EARTH_MAP")
	{
		//	when generating random earth type amounts per tile, the higher the altitude, the greater the amount of bedrock vs other i.e. soil
		//	to simulate preexisting erosion.
		//	load algorythm parameters from file and run
		//	srand(0);

		//	load(ifDataFile);

		// set starting values:
		// this example sets the corners low and a highpoint in the center 
		// assuming samplesize = 32 and size = 128

		initialize();

	};

	void update(int nDeltaTime) {}
};
