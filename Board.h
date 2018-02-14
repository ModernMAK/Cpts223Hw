#ifndef BOARD_H
#define BOARD_H
#include "map"
#include "string"
#include "iostream"
using std::to_string;
using std::cout;
using std::endl;
using std::map;
using std::string;

#define POS_T int64_t
#define XY_T int32_t
class Board
{
public:
	Board();
	Board(int m);
	~Board();

	bool insert(int id, XY_T x, XY_T y);
	bool remove(int id);
	bool find(int id);
	bool moveTo(int id, XY_T nX, XY_T nY);
	void printById();
	bool occupied(XY_T x, XY_T y);
	bool inBound(XY_T x, XY_T y);
	bool validMove(XY_T x, XY_T y, XY_T x2, XY_T y2);
	int getPlayerCount();

protected:
	void pureInsert(int id, XY_T x, XY_T y);
	void pureInsert(int id, POS_T pos);
	void pureRemove(int id);
	void pureRemove(POS_T pos);
	int pureMove(POS_T pos, POS_T nPos);
	void printError(string context, string msg);
	POS_T toPos(XY_T x, XY_T y);
	XY_T toX(POS_T pos);
	XY_T toY(POS_T pos);

private:
	void init(int m);
	XY_T bound;
	//Bimap, preferabbly, we could get away with using 1, but i'm lazy
	map<POS_T, int> boardLookup;
	map<int, POS_T> playerLookup;
	
	
};
#endif