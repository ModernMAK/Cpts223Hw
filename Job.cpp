#include "Job.h"



Job::Job()
{
	Init(-1, "NULL", 0, 0);
}

Job::Job(int id, string description, int req_processors, int req_ticks)
{
	Init(id, description, req_processors, req_ticks);
}

int Job::getId() const
{
	return _id;
}

string Job::getDescription() const
{
	return _description;
}

int Job::getNumProcessorsRequired() const
{
	return _processors_requred;
}

int Job::getTicksRequired() const
{
	return _ticks_required;
}

int Job::getTicksRun() const
{
	return _ticks_run;
}

void Job::tick()
{
	++_ticks_run;
}

bool Job::isDone() const
{
	return _ticks_run >= _ticks_required;
}

void Job::Init(int id, string description, int req_processors, int req_ticks)
{
	_id = id;
	_description = description;
	_processors_requred = req_processors;
	_ticks_required = req_ticks;
	_ticks_run = 0;
}


Job::~Job()
{
}
