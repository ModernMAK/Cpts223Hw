#ifndef BOARD_H
#define BOARD_H
#include "map"
#include "string"
#include "iostream"
#include <cstdint>

//Not c++11 compliant
//using std::to_string; 
using std::cout;
using std::endl;
using std::map;
using std::string;

//We define theses type so that I can change it everywhere 
//Originally I had it at long, but this garuntees I get a 64 bit int
//If changed, MAKE SURE it has twice as many bits as XY_T
//Also update POS_TO_XY_BITS
#define POS_T std::int64_t
using std::int64_t;


//Originally I had it at int, but this garuntees I get a 32 bit int
//If changed, MAKE SURE it has half as many bits as POS_T
//Also update POS_TO_XY_BITS
#define XY_T std::int32_t
using std::int32_t;

//The different in bits between POS and XY
#define POS_TO_XY_BITS 32;

class Board
{
public:
	//Constructors & Destructors
	Board();
	Board(int m);
	~Board();

	//Inserts a player with ID into the board at X,Y
	//Returns True on success, False otherwise
	//Prints an error specifying why it failed
	bool insert(int id, XY_T x, XY_T y);

	//Removes the player with ID from the board
	//Returns True on success, False otherwise
	//Prints an error specifying why it failed
	bool remove(int id);

	//Returns whether the player with ID is on the board
	bool find(int id);

	//Moves the player with ID to X,Y
	//Removes the player at X,Y if occupied
	//Returns True on success, False otherwise
	//Prints an error specifying why it failed
	bool moveTo(int id, XY_T nX, XY_T nY);

	//Prints the players on the board in ascending order by ID
	void printById();

	//Returns whether X,Y is occupied by a player
	bool occupied(XY_T x, XY_T y);

	//Returns whether X,Y is within bounds of the board
	bool inBound(XY_T x, XY_T y);

	//Returns whether moving from X,Y to X2,Y2 is allowed
	bool validMove(XY_T x, XY_T y, XY_T x2, XY_T y2);

	//Returns the # of players
	int getPlayerCount();

protected:
	//Inserts the player with ID into the board at X,Y
	//This method does not check if ID exists or X,Y is occupied
	//(Required for Bimap Implimentation)
	void pureInsert(int id, XY_T x, XY_T y);

	//Inserts the player with ID into the board at Pos
	//This method does not check if ID exists or Pos is occupied
	//(Required for Safe Bimap Implimentation)
	void pureInsert(int id, POS_T pos);

	//Removes the player with ID
	//Does not check if the player exists
	//(Required for Safe Bimap Implimentation)
	void pureRemove(int id);

	//Removes the player at Pos
	//Does not check if the player exists
	//(Required for a Safe Bimap Implimentation)
	void pureRemove(POS_T pos);

	//Moves the player at Pos to NPos
	//Removes the player at NPos IF present
	//Does not check if there is a player at Pos
	//Does not check if moving is legal
	//Assumes pos contains a player
	//Assumes pos != nPos
	//Returns the ID of the player removed, -1 if no player was removed
	int pureMove(POS_T pos, POS_T nPos);
	
	//Helper function to print errors
	void printError(string context, string msg);
	
	//Helper function to convert X,Y to a position
	//Required for my Map implimentation
	//merges x and y into one variable, position
	POS_T toPos(XY_T x, XY_T y);

	//Helper function to get X from a position
	XY_T toX(POS_T pos);

	//Helper function to get Y from a position
	XY_T toY(POS_T pos);

private:
	//Helper function to initialize the class
	void init(int m);

	//The Width and Height of the board
	XY_T bound;

	//A Bimap implimentation
	//preferably, we would have a bimap class (which would hold our pureInsert/pureRemove logic)
	map<POS_T, int> boardLookup;
	map<int, POS_T> playerLookup;
	
	
};
#endif