class Mesh3D :
	public _GComponent
{
private:
	vector<Triangle> Tris;

	void loadFromFile(string sFile)
	{
		ifstream file(sFile);
		if (file.is_open())
		{
			vector<Vector3> verts;

			while (!file.eof())
			{
				char line[128];
				file.getline(line, 128);

				stringstream string;
				string << line;
				char junk;

				if (line[0] == 'v')
				{
					Vector3 vec;
					string >> junk >> vec.X >> vec.Y >> vec.Z;
					verts.push_back(vec);
				}

				if (line[0] == 'f')
				{
					int f[3];
					string >> junk >> f[0] >> f[1] >> f[2];
					Tris.push_back({	verts[f[0] - 1],
										verts[f[1] - 1],
										verts[f[2] - 1]	});

				}
					

			}
		}
	}

public:
	Mesh3D() :
		_GComponent("3DMesh") 
	{
		Tris = 
		{
			{ { 0.0, 0.0, 0.0 },	{ 0.0, 1.0, 0.0 },	{ 1.0, 1.0, 0.0 } },
			{ { 0.0, 0.0, 0.0 },	{ 1.0, 1.0, 0.0 },	{ 1.0, 0.0, 0.0 } },

			{ { 1.0, 0.0, 0.0 },	{ 1.0, 1.0, 0.0 },	{ 1.0, 1.0, 1.0 } },
			{ { 1.0, 0.0, 0.0 },	{ 1.0, 1.0, 1.0 },	{ 1.0, 0.0, 1.0 } },

			{ { 1.0, 0.0, 1.0 },	{ 1.0, 1.0, 1.0 },	{ 0.0, 1.0, 1.0 } },
			{ { 1.0, 0.0, 1.0 },	{ 0.0, 1.0, 1.0 },	{ 0.0, 0.0, 1.0 } },

			{ { 0.0, 0.0, 1.0 },	{ 0.0, 1.0, 1.0 },	{ 0.0, 1.0, 0.0 } },
			{ { 0.0, 0.0, 1.0 },	{ 0.0, 1.0, 0.0 },	{ 0.0, 0.0, 0.0 } },

			{ { 0.0, 1.0, 0.0 },	{ 0.0, 1.0, 1.0 },	{ 1.0, 1.0, 1.0 } },
			{ { 0.0, 1.0, 0.0 },	{ 1.0, 1.0, 1.0 },	{ 1.0, 1.0, 0.0 } },

			{ { 1.0, 0.0, 1.0 },	{ 0.0, 0.0, 1.0 },	{ 0.0, 0.0, 0.0 } },
			{ { 1.0, 0.0, 1.0 },	{ 0.0, 0.0, 0.0 },	{ 1.0, 0.0, 0.0 } }
		};
	};

	Mesh3D(string sFileName) :
		_GComponent("3DMesh")
	{
		loadFromFile(sFileName);
	};

	vector<Triangle> getMesh()
	{
		return Tris;
	}

	void centerOrigin()
	{
		// avarage points, find center of object and offset points
	}



};