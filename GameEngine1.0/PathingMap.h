#include <queue>


class PathingMap :
	public _TileMap<PathingTile>
{
private:

	struct node
	{
		PathingTile *pTile;
		PathingTile *pParent;
		float gCost;
		float hCost;
		float fCost;

		node(PathingTile *tile, PathingTile *parent)
		{
			pTile = tile;
			pParent = parent;
		}
	};

	void BreadthFirstSearch(PathingTile *pStart, PathingTile *pEnd)
	{
		node *start = new node(pStart, NULL);
		//frontier = Queue()
		queue<node*> frontier;
		//	frontier.put(start)
		frontier.push(start);
		//	reached = set()
		vector<node*> reached;
		//	reached.add(start)
		reached.push_back(start);

		//	while not frontier.empty() :
		while (frontier.size() > 0)
		{
			//		current = frontier.get()
			node *current = frontier.front();
			frontier.pop();
			//		for next in graph.neighbors(current) :
			if (current->pTile->getNorth() != NULL)
			{
				/*node *north = new node(current->pTile->getNorth(), current->pTile);
				if (north->pTile)
					reached.*/
			}
				
			if (current->pTile->getSouth() != NULL)
				node *north = new node(current->pTile->getSouth(), current->pTile);
			if (current->pTile->getEast() != NULL)
				node *north = new node(current->pTile->getEast(), current->pTile);
			if (current->pTile->getWest() != NULL)
				node *north = new node(current->pTile->getWest(), current->pTile);
			
			//			if next not in reached :
			//frontier.put(next)
			//	reached.add(next)
		}
		
	}

	void AStar(PathingTile *pStart, PathingTile *pEnd)
	{
		/*
		frontier = PriorityQueue()
		frontier.put(start, 0)
		came_from = dict()
		cost_so_far = dict()
		came_from[start] = None
		cost_so_far[start] = 0

		while not frontier.empty():
		   current = frontier.get()

		   if current == goal:
			  break
   
		   for next in graph.neighbors(current):
			  new_cost = cost_so_far[current] + graph.cost(current, next)
			  if next not in cost_so_far or new_cost < cost_so_far[next]:
				 cost_so_far[next] = new_cost
				 priority = new_cost + heuristic(goal, next)
				 frontier.put(next, priority)
				 came_from[next] = current
		*/


	}



	void onEvent(_Event *pEvent)
	{
		_TileMap::onEvent(pEvent);

		switch (pEvent->m_eType)
		{
			case MOUSEWORLD_EVENT:
			{
				MouseState state = pEvent->get<MouseWorldEvent>()->getState();
				Vector2 pos = pEvent->get<MouseWorldEvent>()->getWorldPosition();
				
				if (PathingTile *pTile = getTile(pos))
				{
					if (state.bLeftButtonDown)
					{
						pTile->setValue(100);
						//	add start position
						//	add end position
					}

					if (state.bRightButtonDown)
					{
						//	add blocking tile
						pTile->setValue(0);
					}
				}
				break;
			}
		}
	}

public:
	PathingMap(int nX, int nY) : 
		_TileMap({float(nX), float(nY)}, "PATHINGMAP") 
	{
		for (int nY = 0; nY < Size.Y; nY++)
			for (int nX = 0; nX < Size.X; nX++)
			{
				if (PathingTile *pTile = getTile(nX, nY))
					pTile->setValue(100);
			}
	}

	void render(ConsoleRender2D *pRenderer, Vector3 vCameraPosition, Vector2 vWorldMin, Vector2 vWorldMax)
	{
		pRenderer->DrawQuad(0, 0, pRenderer->nHeight, pRenderer->nWidth, pRenderer->getGreyscaleColor(50));
		Vector2 mapSize = getSize();
		if (vWorldMin.Y < 0)
			vWorldMin.Y = 0;
		if (vWorldMin.X < 0)
			vWorldMin.X = 0;
		if (vWorldMax.Y > mapSize.Y)
			vWorldMax.Y = mapSize.Y;
		if (vWorldMax.X > mapSize.X)
			vWorldMax.X = mapSize.X;

		int TilesRendered = 0;

		float padding = 0.09;

		for (int nY = vWorldMin.Y; nY < vWorldMax.Y; nY++)
			for (int nX = vWorldMin.X; nX < vWorldMax.X; nX++)
			{
				Vector2 Min((vCameraPosition.X + nX * vCameraPosition.Z), (vCameraPosition.Y + nY * vCameraPosition.Z));
				Vector2 Max((vCameraPosition.X + nX * vCameraPosition.Z + 1 * vCameraPosition.Z), (vCameraPosition.Y + nY * vCameraPosition.Z + 1 * vCameraPosition.Z));

				{
					pRenderer->DrawQuad(Min.X + (padding * vCameraPosition.Z),
						Min.Y + (padding * vCameraPosition.Z),
						Max.X - (padding * vCameraPosition.Z),
						Max.Y - (padding * vCameraPosition.Z),
						pRenderer->getGreyscaleColor(getTile(nX, nY)->getValue()));
				}

				TilesRendered++;

				//	move to bottom of render, to put on top
				if (getTile(nX, nY) == getMouseOverTile())
				{
					pRenderer->DrawQuad(Min.X + (padding * vCameraPosition.Z),
						Min.Y + (padding * vCameraPosition.Z),
						Max.X - (padding * vCameraPosition.Z),
						Max.Y - (padding * vCameraPosition.Z),
						APixel(' ', FG_LIGHTGREEN + BG_LIGHTGREEN));
				}
			}
	}
};