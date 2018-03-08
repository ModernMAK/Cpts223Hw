#include "Board.h"

//Constructor
Board::Board()
{
	init(1);//Initialize Bounds to 1
}


//Constructor
Board::Board(int m)
{
	init(m);//Initialize Bounds to m
}



//Constructors & Destructors
Board::~Board()
{
}

//Returns whether X,Y is occupied by a player
//Log(N)
bool Board::occupied(XY_T x, XY_T y)
{
	return boardLookup.find(toPos(x, y)) != boardLookup.end();
}

//Inserts a player with ID into the board at X,Y
//Returns True on success, False otherwise
//Prints an error specifying why it failed
//7Log(N) <- Worst (No Error) 
//(C) <- Best (An Error)
bool Board::insert(int id, XY_T x, XY_T y)
{
	//Context for error messages
	string context = "Failed to insert";

	//(C)
	//Throw error if Out of Bounds
	if (!inBound(x, y))
	{
		string msg = to_string(x) + "," + to_string(y) + " is out of bounds!";
		//(C)
		printError(context, msg);
		return false;
	}
	//(C)
	//Throw Error if Player Limit Met
	else if (getPlayerCount() >= bound)
	{
		//(C)
		printError(context, "Cannot add anymore players!");
		return false;
	}
	//Log(N)
	//Throw Error if Player already exists
	 else if(find(id))
	{
		string msg = "Player " + to_string(id) + " already exists!";
		//(C)
		printError(context,msg);
		return false;
	}
	//4Log(N)
	//Throw Error if Space is Occupied
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

//Removes the player with ID from the board
//Returns True on success, False otherwise
//Prints an error specifying why it failed
//4Log(N) <- Worst (No Error)
//Log(N) <- Best (An Error)
bool Board::remove(int id)
{
	//Log(N)
	//Throw Error if Player doesn't exist
	if(!find(id))
	{	
		string msg = "Player " + to_string(id) + " could not be found!";
		printError("Failed to remove",msg);
		return false;
	}
	//3Log(N)
	//Blindly removes from the board
	pureRemove(id);
	return true;
}

//Returns whether the player with ID is on the board
//Log(N)
bool Board::find(int id)
{
	return playerLookup.find(id) != playerLookup.end();
}

//Moves the player with ID to X,Y
//Removes the player at X,Y if occupied
//Returns True on success, False otherwise
//Prints an error specifying why it failed
//11Log(N) <- Worst (No Error)
//(C) <- Best (An Error)
bool Board::moveTo(int id, XY_T nX, XY_T nY)
{
	//Context for error messages
	string context = "Failed to move";
	//(C)
	//Throw Error if new position is out of bounds
	if (!inBound(nX, nY))
	{
		string msg = to_string(nX) + "," + to_string(nY) + " is out of bounds!";
		//(C)
		printError(context,msg);
		return false;
	}

	//Log(N)
	//Throw Error if Player couldn't be found
	map<int, POS_T>::iterator temp = playerLookup.find(id);
	if(temp == playerLookup.end())
	{
		string msg = "Player " + to_string(id) + " could not be found!";
		//(C)
		printError(context,msg);
		return false;
	}

	//Iterator ptr stores as pair <int,POS_T>
	POS_T pos = temp->second;
	//(C)
	XY_T x = toX(pos);
	//(C)
	XY_T y = toY(pos);
	//Assuming moving to the tile we are at is valid, moving to ourselves is a succesful move
	if (nX == x && nY == y)
		return true;

	//(C)
	//Throw Error if the move isn't valid
	if(!validMove(x,y,nX,nY))
	{
		string msg = "Can't move from " + to_string(x) + "," + to_string(y) + " to " + to_string(nX) + "," + to_string(nY) + "!";
		//(C)
		printError(context,msg);
		return false;
	}
	
	//10Log(N)
	//Blindly move, returns -1 if no player was removed, the player Id otherwise
	int removed = pureMove(toPos(x, y), toPos(nX, nY));
	if(removed != -1)
	{
		cout << endl << "Player " << removed << " was defeated in battle." << endl;
	}
	return true;
}

//Prints the players on the board in ascending order by ID
//(N)
void Board::printById()
{

	cout << endl << "All Players" << endl << "- - - - - -" << endl;
	//http://www.cplusplus.com/reference/map/map/
	//The above says the set IS ORDERED,
	//Meaning that I can just iterate over the map to print the players in ascending order
	//Since the map is ordered by key, in ascending order
	for(map<int,POS_T>::iterator i = playerLookup.begin(); i != playerLookup.end(); ++i)
	{
		//Convert to X,Y for printing
		XY_T x = toX(i->second);
		XY_T y = toY(i->second);
		cout << "\t" << "Player " << i->first << " : " << x << "," << y << endl;
	}
	cout << endl;
}


//Helper function to initialize the class
//(C)
void Board::init(int m)
{
	//No NEW, no problems
	boardLookup = map<POS_T, XY_T>();
	playerLookup = map<XY_T, POS_T>();
	bound = m;
}

//Returns whether X,Y is within bounds of the board
//(C)
bool Board::inBound(XY_T x, XY_T y)
{
	return (x < bound && y < bound);
}

//Returns whether moving from X,Y to X2,Y2 is allowed
//(C)
bool Board::validMove(XY_T x, XY_T y, XY_T x2, XY_T y2)
{
	//Get the delta (difference) X and delta Y
	XY_T dX = (x2 - x);
	XY_T dY = (y2 - y);
	//To make my life easy, instead of considering all quadrants,
	//move any difference to the first quadrant (+x, +y)
	dX = (dX < 0 ? -dX : dX);
	dY = (dY < 0 ? -dY : dY);
	//We can move Vertical (dY = 0)
	//We can move Horizontal (dX = 0)
	//We can move Diagnally IFF (dX = dY)
	return (dX == dY || dX == 0 || dY == 0);

}

//Returns the # of players
//(C)
int Board::getPlayerCount()
{
	return playerLookup.size();
}

//Helper function to print errors
//Useful to not repeat this cout every time, also gives error messages a little style consistancy
//(C)
void Board::printError(string context, string msg)
{
	cout << endl << "!!! ERROR !!!" << endl << context << endl << msg << endl;
}

//Helper function to convert X,Y to a position
//Required for my Map implimentation
//merges x and y into one variable, position
//(C)
POS_T Board::toPos(XY_T x, XY_T y)
{
	//Convert to avoid loss of precision
	POS_T xl = (POS_T)x;
	POS_T yl = (POS_T)y;
	//Shift x1, so that it now occupies the other half of it's space
	xl = xl << POS_TO_XY_BITS;
	//Add the two to squish them together
	//x1 is in the first half
	//y1 is in the second half
	return xl + yl;
}

//Helper function to get X from a position
//(C)
XY_T Board::toX(POS_T pos)
{
	//Shift x1, so that it now occupies the other half of it's space,
	//this erases y1, but we don't have to worry about that since we don't need y1 
	pos = pos >> POS_TO_XY_BITS;
	return (XY_T)pos;
}

//Helper function to get Y from a position
//(C)
XY_T Board::toY(POS_T pos)
{
	//by truncating the variable, we only get the half with y1
	return (XY_T)pos;//Truncate
}

//Inserts the player with ID into the board at X,Y
//This method does not check if ID exists or X,Y is occupied
//(Required for Bimap Implimentation)
//2Log(N)
void Board::pureInsert(int id, XY_T x, XY_T y)
{
	//Convert to position, then blindly insert
	pureInsert(id,toPos(x, y));
}

//Inserts the player with ID into the board at X,Y
//This method does not check if ID exists or Pos is occupied
//(Required for Bimap Implimentation)
//2Log(N)
void Board::pureInsert(int id, POS_T pos)
{
	//Blindly Insert
	boardLookup[pos] = id;
	playerLookup[id] = pos;
}

//Removes the player with ID
//Does not check if the player exists
//(Required for Safe Bimap Implimentation)
//3Log(N)
void Board::pureRemove(int id)
{
	//Blindly Remove
	//Could reduce to 2Log(N), but it works
	POS_T pos = playerLookup[id];
	boardLookup.erase(boardLookup.find(pos));
	playerLookup.erase(playerLookup.find(id));
}

//Removes the player at Pos
//Does not check if the player exists
//(Required for a Safe Bimap Implimentation)
//3Log(N)
void Board::pureRemove(POS_T pos)
{
	//Blindly Remove
	//Could reduce to 2Log(N), but it works
	int id = boardLookup[pos];
	boardLookup.erase(boardLookup.find(pos));
	playerLookup.erase(playerLookup.find(id));
}

//Moves the player at Pos to NPos
//Removes the player at NPos IF present
//Does not check if there is a player at Pos
//Does not check if moving is legal
//Assumes pos contains a player
//Assumes pos != nPos
//Returns the ID of the player removed, -1 if no player was removed
//10Log(N) <- Worst (Removes)
//7Log(N) <- Best (Doesn't Remove)
int Board::pureMove(POS_T pos, POS_T nPos)
{
	//ID of the player removed, -1 is the no player was removed code
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
