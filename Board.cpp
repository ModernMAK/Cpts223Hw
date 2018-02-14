#include "Board.h"
#define LONG_TO_INT_BITS 32;
Board::Board()
{
	init(1);
}


Board::Board(int m)
{
	init(m);
}



Board::~Board()
{
}

bool Board::occupied(XY_T x, XY_T y)
{
	return boardLookup.find(toPos(x, y)) != boardLookup.end();
}

bool Board::insert(int id, XY_T x, XY_T y)
{
	string context = "Failed to insert";
	if(find(id))
	{
		string msg = "Player " + to_string(id) + " already exists!";
		printError(context,msg);
		return false;
	}
	else if(!inBound(x,y))
	{
		string msg = to_string(x) + "," + to_string(y) + " is out of bounds!";
		printError(context,msg);
		return false;
	}
	else if(getPlayerCount() >=  bound)
	{
		printError(context,"Cannot add anymore players!");
		return false;
	}
	else if (occupied(x, y))
	{
		string msg = to_string(x) + "," + to_string(y) + " is occupied!";
		printError(context,msg);
		return false;
	}
	//Blindly inserts into the board
	pureInsert(id, x, y);
	return true;
}

bool Board::remove(int id)
{
	if(!find(id))
	{	
		string msg = "Player " + to_string(id) + " could not be found!";
		printError("Failed to remove",msg);
		return false;
	}
	pureRemove(id);
	return true;
}

bool Board::find(int id)
{
	return playerLookup.find(id) != playerLookup.end();
}

bool Board::moveTo(int id, int nX, int nY)
{
	string context = "Failed to move";
	if (!inBound(nX, nY))
	{
		string msg = to_string(nX) + "," + to_string(nY) + " is out of bounds!";
		printError(context,msg);
		return false;
	}

	map<int, POS_T>::iterator temp = playerLookup.find(id);
	if(temp == playerLookup.end())
	{
		string msg = "Player " + to_string(id) + " could not be found!";
		printError(context,msg);
		return false;
	}

	POS_T pos = temp->second;
	XY_T x = toX(pos);
	XY_T y = toY(pos);
	if (nX == x && nY == y)
		return true;//Assume moving to the tile we are at is valid

	if(!validMove(x,y,nX,nY))
	{
		string msg = "Can't move from " + to_string(x) + "," + to_string(y) + " to " + to_string(nX) + "," + to_string(nY) + "!";
		printError(context,msg);
		return false;
	}
	int removed = pureMove(toPos(x, y), toPos(nX, nY));
	if(removed != -1)
	{
		cout << endl << "Player " << removed << " was defeated in battle." << endl;
	}
	return true;
}

void Board::printById()
{

	cout << endl << "All Players" << endl << "- - - - - -" << endl;
	for(map<int,POS_T>::iterator i = playerLookup.begin(); i != playerLookup.end(); ++i)
	{
		int32_t x = toX(i->second);
		int32_t y = toY(i->second);
		cout << "\t" << "Player " << i->first << " : " << x << "," << y << endl;
	}
	cout << endl;
}


void Board::init(int m)
{
	boardLookup = map<POS_T, XY_T>();
	playerLookup = map<XY_T, POS_T>();
	bound = m;
}

bool Board::inBound(XY_T x, XY_T y)
{
	return (x < bound && y < bound);
}

bool Board::validMove(XY_T x, XY_T y, XY_T x2, XY_T y2)
{


	int dX = (x2 - x);
	int dY = (y2 - y);
	dX = (dX < 0 ? -dX : dX);
	dY = (dY < 0 ? -dY : dY);

	return (dX == dY || dX == 0 || dY == 0);

}

int Board::getPlayerCount()
{
	return playerLookup.size();
}

void Board::printError(string context, string msg)
{
	cout << endl << "!!! ERROR !!!" << endl << context << endl << msg << endl;
}

POS_T Board::toPos(XY_T x, XY_T y)
{
	POS_T xl = (POS_T)x;
	POS_T yl = (POS_T)y;
	xl = xl << LONG_TO_INT_BITS;//Returns number of bytes in int, multiply by bits, then shift
	return xl + yl;
}

XY_T Board::toX(POS_T pos)
{
	pos = pos >> LONG_TO_INT_BITS;
	return (int)pos;
}
XY_T Board::toY(POS_T pos)
{
	return (XY_T)pos;//Truncate
}

void Board::pureInsert(int id, int32_t x, int32_t y)
{
	pureInsert(id,toPos(x, y));
}
void Board::pureInsert(int id, POS_T pos)
{
	boardLookup[pos] = id;
	playerLookup[id] = pos;
}

//Assumes there exists a player with id
void Board::pureRemove(int id)
{
	POS_T pos = playerLookup[id];
	boardLookup.erase(boardLookup.find(pos));
	playerLookup.erase(playerLookup.find(id));
}

//Assumes pos contains a player
void Board::pureRemove(POS_T pos)
{
	int id = boardLookup[pos];
	boardLookup.erase(boardLookup.find(pos));
	playerLookup.erase(playerLookup.find(id));
}

//Assumes pos contains a player
//Assumes pos != nPos
//Returns the player removed, -1 if no player was removed
int Board::pureMove(POS_T pos, POS_T nPos)
{
	int removed = -1;
	map<POS_T, int>::iterator temp = boardLookup.find(pos);
	int id = temp->second;
	//Why not manually remove it?
	//Well pureRemove is garunteed to remove properly
	//that's why we made the pureRemove, so we don't have to worry about removing properly
	pureRemove(id);
	map<POS_T, int>::iterator nTemp = boardLookup.find(nPos);
	if (nTemp != boardLookup.end()) {
		
		removed = nTemp->second;
		pureRemove(nPos);
	}
	pureInsert(id, nPos);
	return removed;
}
