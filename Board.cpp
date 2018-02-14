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

//Log(N)
bool Board::occupied(XY_T x, XY_T y)
{
	return boardLookup.find(toPos(x, y)) != boardLookup.end();
}

//7Log(N) <- Worst
//(C) <- Best
bool Board::insert(int id, XY_T x, XY_T y)
{
	string context = "Failed to insert";
	//(C)
	if (!inBound(x, y))
	{
		string msg = to_string(x) + "," + to_string(y) + " is out of bounds!";
		//(C)
		printError(context, msg);
		return false;
	}
	//(C)
	else if (getPlayerCount() >= bound)
	{
		//(C)
		printError(context, "Cannot add anymore players!");
		return false;
	}
	//Log(N)
	 else if(find(id))
	{
		string msg = "Player " + to_string(id) + " already exists!";
		//(C)
		printError(context,msg);
		return false;
	}
	//4Log(N)
	else if (occupied(x, y))
	{
		string msg = to_string(x) + "," + to_string(y) + " is occupied!";
		printError(context,msg);
		return false;
	}
	//2Log(N)
	//Blindly inserts into the board
	pureInsert(id, x, y);
	return true;
}

//4Log(N) <- Worst
//Log(N) <- Best
bool Board::remove(int id)
{
	//Log(N)
	if(!find(id))
	{	
		string msg = "Player " + to_string(id) + " could not be found!";
		printError("Failed to remove",msg);
		return false;
	}
	//3Log(N)
	pureRemove(id);
	return true;
}

//Log(N)
bool Board::find(int id)
{
	return playerLookup.find(id) != playerLookup.end();
}

//11Log(N) <- Worst
//(C) <- Best
bool Board::moveTo(int id, int nX, int nY)
{
	string context = "Failed to move";
	//(C)
	if (!inBound(nX, nY))
	{
		string msg = to_string(nX) + "," + to_string(nY) + " is out of bounds!";
		//(C)
		printError(context,msg);
		return false;
	}

	//Log(N)
	map<int, POS_T>::iterator temp = playerLookup.find(id);
	if(temp == playerLookup.end())
	{
		string msg = "Player " + to_string(id) + " could not be found!";
		//(C)
		printError(context,msg);
		return false;
	}

	POS_T pos = temp->second;
	//(C)
	XY_T x = toX(pos);
	//(C)
	XY_T y = toY(pos);
	if (nX == x && nY == y)
		return true;//Assume moving to the tile we are at is valid

	//(C)
	if(!validMove(x,y,nX,nY))
	{
		string msg = "Can't move from " + to_string(x) + "," + to_string(y) + " to " + to_string(nX) + "," + to_string(nY) + "!";
		//(C)
		printError(context,msg);
		return false;
	}
	
	//10Log(N)
	int removed = pureMove(toPos(x, y), toPos(nX, nY));
	if(removed != -1)
	{
		cout << endl << "Player " << removed << " was defeated in battle." << endl;
	}
	return true;
}

//(N)
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


//(C)
void Board::init(int m)
{
	boardLookup = map<POS_T, XY_T>();
	playerLookup = map<XY_T, POS_T>();
	bound = m;
}

//(C)
bool Board::inBound(XY_T x, XY_T y)
{
	return (x < bound && y < bound);
}

//(C)
bool Board::validMove(XY_T x, XY_T y, XY_T x2, XY_T y2)
{


	int dX = (x2 - x);
	int dY = (y2 - y);
	dX = (dX < 0 ? -dX : dX);
	dY = (dY < 0 ? -dY : dY);

	return (dX == dY || dX == 0 || dY == 0);

}

//(C)
int Board::getPlayerCount()
{
	return playerLookup.size();
}

//(C)
void Board::printError(string context, string msg)
{
	cout << endl << "!!! ERROR !!!" << endl << context << endl << msg << endl;
}

//(C)
POS_T Board::toPos(XY_T x, XY_T y)
{
	POS_T xl = (POS_T)x;
	POS_T yl = (POS_T)y;
	xl = xl << LONG_TO_INT_BITS;//Returns number of bytes in int, multiply by bits, then shift
	return xl + yl;
}

//(C)
XY_T Board::toX(POS_T pos)
{
	pos = pos >> LONG_TO_INT_BITS;
	return (int)pos;
}

//(C)
XY_T Board::toY(POS_T pos)
{
	return (XY_T)pos;//Truncate
}

//2Log(N)
void Board::pureInsert(int id, int32_t x, int32_t y)
{
	pureInsert(id,toPos(x, y));
}

//2Log(N)
void Board::pureInsert(int id, POS_T pos)
{
	boardLookup[pos] = id;
	playerLookup[id] = pos;
}

//Assumes there exists a player with id
//3Log(N)
void Board::pureRemove(int id)
{
	POS_T pos = playerLookup[id];
	boardLookup.erase(boardLookup.find(pos));
	playerLookup.erase(playerLookup.find(id));
}

//Assumes pos contains a player
//3Log(N)
void Board::pureRemove(POS_T pos)
{
	int id = boardLookup[pos];
	boardLookup.erase(boardLookup.find(pos));
	playerLookup.erase(playerLookup.find(id));
}

//Assumes pos contains a player
//Assumes pos != nPos
//Returns the player removed, -1 if no player was removed
//10Log(N) <- Worst
//7Log(N) <- Best
int Board::pureMove(POS_T pos, POS_T nPos)
{
	int removed = -1;
	//Log(N)
	map<POS_T, int>::iterator temp = boardLookup.find(pos);
	int id = temp->second;
	//Why not manually remove it?
	//Well pureRemove is garunteed to remove properly
	//that's why we made the pureRemove, so we don't have to worry about removing properly
	//3log(N)
	pureRemove(id);
	//Log(N)
	map<POS_T, int>::iterator nTemp = boardLookup.find(nPos);
	if (nTemp != boardLookup.end()) {		
		removed = nTemp->second;
		//3Log(N)
		pureRemove(nPos);
	}
	//2Log(N)
	pureInsert(id, nPos);
	return removed;
}
