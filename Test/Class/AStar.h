#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

const int gc_WidthOfMap = 10;
const int gc_HighOfMap = 10;


int g_Map[gc_WidthOfMap][gc_HighOfMap] = {
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//0
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//1
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//2
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//3
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//4
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//5
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//6
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//7
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//8
	0, 0, 0, 0, 0,   0, 0, 0, 0, 0,//9
};

class SearchNode;

vector <SearchNode*> g_OpenList;
vector <SearchNode*> g_CloseList;
struct Pos
{
	Pos(const float& _x, const float& _y)
	{ 
		x = _x;
		y = _y; 
	}
	float x;
	float y;
};

const Pos gc_startPos = Pos(0,0);
const Pos gc_endPos = Pos(9, 9);

class SearchNode
{
public:
	SearchNode(const Pos& pos);
	~SearchNode();
	SearchNode(const SearchNode& node);
	SearchNode& operator=(const SearchNode& node);
	bool operator==(const SearchNode& node);
	void EasyCopy(const SearchNode& node);
	void EasyPush(const float& x, const float& y, const int& d);
	vector<SearchNode*>& getNearNodes();
	inline Pos* getPos(){ return m_pos; }
	inline void setG(const float& g){ m_g = g; }
	inline void setH(const float& h){ m_h = h; }
	inline void setF(const float& f){ m_f = f; }
	inline const float& getG(){ return m_g; }
	inline const float& getH(){ return m_h; }
	inline const float& getF(){ return m_g+m_h; }
	inline void setIdOfPosToParent(const int& id){ m_IdOfPosToParent = id; }
	const int& getDistanceToCurrentNodeByIdOfPosToParent(const int& id);
	inline const int& getIdOfPosToParent(){ return m_IdOfPosToParent; }
	inline void setParent(SearchNode* parent){ m_parent = parent; }
	inline SearchNode* getParent(){ return m_parent; }
private:
	float m_g;/*costFromStart*/
	float m_h;/*costToGoal*/
	float m_f;/*m_g + m_h*/
	SearchNode* m_parent;
	Pos* m_pos;/*自己的位置*/
	int m_IdOfPosToParent;
	vector<SearchNode*> m_nearNodes;
	enum EDGE
	{
		EDGE_LEFT = -1,
		EDGE_RIGHT = 10,
		EDGE_TOP = 10,
		EDGE_BOTTOM = -1,
	};
	enum DIRECTION
	{
		DIRECTION_INVALID = 1000,
		DIRECTION_LT,//left top
		DIRECTION_T,//top
		DIRECTION_RT,//right top
		DIRECTION_R,//right
		DIRECTION_RB,//right bottom
		DIRECTION_B,//bottom
		DIRECTION_LB,//left bottom
		DIRECTION_L,//left 
	};
	
	const float DISTANCE_NORMAL = 1;
	const float DISTANCE_SLANT = 1.4;
};
void SearchNode::EasyCopy(const SearchNode& node)
{
	this->m_g = node.m_g;
	this->m_h = node.m_h;
	this->m_f = node.m_f;
	this->m_parent = node.m_parent;
	this->m_pos = node.m_pos;
	this->m_nearNodes = node.m_nearNodes;
	this->m_IdOfPosToParent = node.m_IdOfPosToParent;
}
const int& SearchNode::getDistanceToCurrentNodeByIdOfPosToParent(const int& id)
{
	int distance = 0;
	switch (id)
	{
	case DIRECTION_INVALID:
	{
	}break;
	case DIRECTION_LT:
	case DIRECTION_RT:
	case DIRECTION_RB:
	case DIRECTION_LB:
	{
		distance = DISTANCE_SLANT;
	}break;
	case DIRECTION_T:
	case DIRECTION_R:
	case DIRECTION_B:
	case DIRECTION_L:
	{
		distance = DISTANCE_NORMAL;
	}break;
	default:
		break;
	}
	return distance;
}
void SearchNode::EasyPush(const float& x, const float& y, const int& d)
{
	Pos pos = Pos(x, y);
	SearchNode* node = new SearchNode(pos);
	node->setParent(this);
	node->setIdOfPosToParent(d);
	switch (d)
	{
	case DIRECTION_INVALID:
	{
		
	}break;
	case DIRECTION_LT:
	{
		node->m_g = m_g + DISTANCE_SLANT;
	}break;
	case DIRECTION_T:
	{
		node->m_g = m_g + DISTANCE_NORMAL;
	}break;
	case DIRECTION_RT:
	{
		node->m_g = m_g + DISTANCE_SLANT;
	}break;
	case DIRECTION_R:
	{
		node->m_g = m_g + DISTANCE_NORMAL;
	}break;
	case DIRECTION_RB:
	{
		node->m_g = m_g + DISTANCE_SLANT;
	}break;
	case DIRECTION_B:
	{
		node->m_g = m_g + DISTANCE_NORMAL;
	}break;
	case DIRECTION_LB:
	{
		node->m_g = m_g + DISTANCE_SLANT;
	}break;
	case DIRECTION_L:
	{
		node->m_g = m_g + DISTANCE_NORMAL;
	}break;
	default:
		break;
	}

	m_nearNodes.push_back(node);
}
SearchNode::SearchNode(const Pos& pos)
:m_IdOfPosToParent(DIRECTION_INVALID),
m_g(0.0f),
m_h(0.0f),
m_f(0.0f),
m_parent(nullptr)
{
	m_pos = new Pos(pos.x, pos.y);
}
SearchNode::~SearchNode()
{
	if (m_pos != nullptr)
	{
		delete m_pos;
		m_pos = nullptr;
	}
	if (m_parent != nullptr)
	{
		//delete m_parent;
		//m_parent = nullptr;
	}
	if (!m_nearNodes.empty())
	{
		vector<SearchNode*>::iterator begin = m_nearNodes.begin();
		for (; begin != m_nearNodes.end(); begin++)
		{
			//delete(*begin);
			//*begin = nullptr;
		}
		m_nearNodes.clear();
	}
}
SearchNode::SearchNode(const SearchNode& node)
{
	EasyCopy(node);
}
SearchNode& SearchNode::operator=(const SearchNode& node)
{
	if (&node == this)
		return *this;
	EasyCopy(node);
	return *this;
}

bool SearchNode::operator==(const SearchNode& node)
{
	if (this->m_pos->x == node.m_pos->x && this->m_pos->y == node.m_pos->y)
		return true;
	return false;
}
vector<SearchNode*>& SearchNode::getNearNodes()
{
	if (m_pos->x - 1 > EDGE_LEFT && m_pos->y + 1 < EDGE_TOP)
	{//left top
		EasyPush(m_pos->x - 1, m_pos->y + 1, DIRECTION_LT);
	}
	if (m_pos->y + 1 < EDGE_TOP)
	{//top
		EasyPush(m_pos->x, m_pos->y + 1, DIRECTION_T);
	}
	if (m_pos->x + 1 < EDGE_RIGHT && m_pos->y + 1 < EDGE_TOP)
	{//right top
		EasyPush(m_pos->x + 1, m_pos->y +1,DIRECTION_RT);
	}
	if (m_pos->x + 1 < EDGE_RIGHT)
	{//right
		EasyPush(m_pos->x+1, m_pos->y, DIRECTION_R);
	}
	if (m_pos->x + 1 < EDGE_RIGHT && m_pos->y-1 > EDGE_BOTTOM)
	{//right bottom
		EasyPush(m_pos->x + 1, m_pos->y-1, DIRECTION_RB);
	}
	if ( m_pos->y - 1 > EDGE_BOTTOM )
	{//bottom
		EasyPush(m_pos->x, m_pos->y - 1, DIRECTION_B);
	}
	if (m_pos->x - 1 > EDGE_LEFT && m_pos->y - 1 > EDGE_BOTTOM)
	{//left bottom
		EasyPush(m_pos->x - 1, m_pos->y - 1, DIRECTION_LB);
	}
	if (m_pos->x - 1 > EDGE_LEFT)
	{//left
		EasyPush(m_pos->x - 1, m_pos->y, DIRECTION_L);
	}
	return m_nearNodes;
}
bool FindFromOpenList( SearchNode* node)
{
	vector<SearchNode*>::iterator begin = g_OpenList.begin();
	for (; begin != g_OpenList.end(); begin++)
	{
		if (node->getPos()->x == (*begin)->getPos()->x && node->getPos()->y == (*begin)->getPos()->y)
		{
			return true;
		}
	}//end for
	return false;
}
bool FindFromCloseList(SearchNode* node)
{
	vector<SearchNode*>::iterator begin = g_CloseList.begin();
	for (; begin != g_CloseList.end(); begin++)
	{
		if (node->getPos()->x == (*begin)->getPos()->x && node->getPos()->y == (*begin)->getPos()->y)
		{
			return true;
		}
	}//end for
	return false;
}

bool compare(SearchNode*a, SearchNode*b)
{
	if (a->getF() < b->getF())
		return true;
	else
		return false;
}
void CleanOpenlistAndCloseList()
{
	vector<SearchNode*>::iterator begin = g_OpenList.begin();
	for (; begin != g_OpenList.end(); )
	{
		delete *begin;
		*begin = nullptr;
		begin = g_OpenList.erase(begin);
	}
	begin = g_CloseList.begin();
	for (; begin != g_CloseList.end(); )
	{
		delete *begin;
		*begin = nullptr;
		begin = g_CloseList.erase(begin);
	}

}
void SortOpenlist()
{
	sort(g_OpenList.begin(), g_OpenList.end(), compare);
}
void SortCloselist()
{
	sort(g_CloseList.begin(), g_CloseList.end(), compare);
}
void testSort()
{
	float a[10] = {2,1,4,5,3,6,7,8,9,10};
	for (int i = 0; i < 9; i++)
	{
		SearchNode *node = new SearchNode(Pos(0, 0));
		node->setF(a[i]);
		g_OpenList.push_back(node);
	}
	SortOpenlist();
	g_OpenList.erase(g_OpenList.begin());
}
bool AStarSearch(const Pos& startPos, const Pos& endPos)
{

	SearchNode *startNode = new SearchNode(startPos);
	SearchNode *endNode = new SearchNode(endPos);

	g_OpenList.push_back(startNode);
	while (!g_OpenList.empty())
	{
		SearchNode *node = g_OpenList[0];
		if (*node == *endNode)
		{
			SearchNode*parent = node->getParent();
			while (parent != nullptr)
			{
				cout << "posXY:" << parent->getPos()->x << parent->getPos()->y  << endl;
				parent = parent->getParent();
			}
			CleanOpenlistAndCloseList();
			return true;
		}
		else
		{
			vector<SearchNode*> nearNodes = node->getNearNodes();
			vector<SearchNode*>::iterator begin = nearNodes.begin();
			for (; begin != nearNodes.end(); begin++)
			{
				bool fOpen = FindFromOpenList(*begin);//find openlist
				bool fClose = FindFromCloseList(*begin);//find closelist
				if (!fOpen && !fClose)
				{
					g_OpenList.push_back(*begin);
				}
				else if (fOpen)
				{
					int distanceG = node->getDistanceToCurrentNodeByIdOfPosToParent((*begin)->getIdOfPosToParent()) + node->getG();
					if ( distanceG < (*begin)->getG())
					{
						(*begin)->setParent(node);
						(*begin)->setG(distanceG);
					}
				}
			}/*end for*/
			g_OpenList.erase(g_OpenList.begin());
			///g_OpenList.
			g_CloseList.push_back(node);
			SortOpenlist();
			SortCloselist();
		}
	}/*end while*/
	delete(startNode);
	delete(endNode);
	startNode = nullptr;
	endNode = nullptr;
	return false;
}