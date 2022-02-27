class Pathfinding : public _GComponent
{
private:
	//	Stack of Pathing nodes
	//	goal position

	void onEvent(_Event *pEvent)
	{
		//	case PATHINGCOMMENT_EVENT:
		{
			//	event.targetPosition
			//	setPath(doPathfinding(targetPosition));
		}
		//	break;
	}

public:
	Pathfinding() :
		_GComponent("PATHFINDING") {};

	void update(int nDeltaTime)
	{
		//	if position is != goal tile
		//		new movecommand(currentile.posiiton - nexttile.position)
		//	else
		//		pathList.pop()
	}

	void setPath()
	{

	}

};