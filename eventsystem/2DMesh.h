class Mesh2D : 
	public _GComponent
{
private:
	Polygon2D m_Poly;

public:
	Mesh2D() :
		_GComponent("2DMesh") 
	{
		//	// unit square w/ 0, 0 origin
		m_Poly.Verticies =
		{
			{5,0},
		{4,-4},
		{0,-5},
		{-4,-4},
		{-5,0},
		{-4,4},
		{0,5},
		{4,4}
		};
	}

	Polygon2D getPoly()
	{
		return m_Poly;
	}
};