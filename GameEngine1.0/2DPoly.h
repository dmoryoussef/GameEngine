class Poly2D : 
	public _GComponent
{
private:
	Polygon2D m_Poly;

public:
	Poly2D() :
		_GComponent("2DPOLY") 
	{
		//	add list of triangles instead of verticies
		//	then can be filled polygons
		createCircle();
	}

	void createCircle()
	{
		int nVerticies = 10;
		m_Poly.Verticies.push_back({ 0.0, 0.0 });
		for (int nI = 0; nI < nVerticies; nI++)
		{
			m_Poly.Verticies.push_back({ cosf(nI / (float)(nVerticies - 1) * 2.0f * 3.14159f) , sinf(nI / (float)(nVerticies - 1) * 2.0f * 3.14159f) });
		}

		m_Poly.scale({ 8, 8 });
	}

	Polygon2D getPoly()
	{
		return m_Poly;
	}
};

