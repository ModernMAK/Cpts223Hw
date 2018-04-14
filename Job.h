#pragma once

#include "string"
using std::string;
class Job
{
public:
	Job();
	Job(int id, string description, int req_processors, int req_ticks);
	~Job();


public:
	int getId() const;
	string getDescription() const;
	int getNumProcessorsRequired() const;
	int getTicksRequired() const;
	int getTicksRun() const;
	void tick();
	bool isDone() const;

private:
	void Init(int id, string description, int req_processors, int req_ticks);


	int _id;
	string _description;
	int _processors_requred;
	int _ticks_required;
	int _ticks_run;
};
