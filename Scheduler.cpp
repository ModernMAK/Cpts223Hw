#include "Scheduler.h"
#include <iostream>


Scheduler::Scheduler()
{
	init(2);
}
Scheduler::Scheduler(int processors)
{
	init(processors);
}


Scheduler::~Scheduler()
{
}

void Scheduler::print()
{
	printJobsStarted();
	_cluster.printJobsRunning();
	_cluster.printJobsCompleted();
	cout << "Processors Available : " << _cluster.getAvailableProcessors() << " / " << _cluster.getTotalProcessors() << endl;
}


void Scheduler::tick()
{
	_began_this_tick.clear();
	_cluster.tick();
	bool ranJob = true;
	while (ranJob & hasJobs())
	{
		ranJob = false;
		Job j = getShortestJob();
		if (_cluster.canRunJob(j)) {
			deleteShortestJob();
			_cluster.runJob(j);
			ranJob = true;
			_began_this_tick.push_back(j);
		}
	}
}

bool Scheduler::isIdle()
{
	return !hasJobs() && _cluster.isIdle();
}

bool Scheduler::hasJobs()
{
	return !_wait_queue.empty();
}

void Scheduler::submitJob(string description, int req_processors, int req_ticks)
{
	if (description == "NULL")
	{
		cout << "Submitted NULL Job" << endl << endl;
		return;
	}
	if (description == "EXIT")
	{
		cout << "Submitted EXIT Job" << endl << endl;
		exit(EXIT_SUCCESS);
		//return -1; //Formality really
	}
	int code = canInsertJob(req_processors, req_ticks);
	handleJobCode(code);
	if (code == JC_SUCCESS)
	{
		int submitted = insertJob(description, req_processors, req_ticks);
		cout << "Submitted Job #" << submitted << endl << endl;
	}
}

void Scheduler::printJobsStarted()
{
	if(_began_this_tick.empty())
		return;
	cout << "Jobs Started" << endl;

	for (Job j : _began_this_tick)
		cout << "Job #" << j.getId() << " (" << j.getDescription() << ")" << endl;
	cout << endl;
}


int Scheduler::canInsertJob(int req_processors, int req_ticks)
{

	if (0 > req_processors || req_processors > _cluster.getTotalProcessors())
		return JC_INVALID_PROCESSORS;
	if (req_ticks < 0)
		return JC_INVALID_TICKS;
	return JC_SUCCESS;
}

void Scheduler::handleJobCode(int job_code)
{
	switch(job_code)
	{
	case JC_INVALID_PROCESSORS:
		cout << "The cluster does not support that many processors." << endl << endl;
		break;
	case JC_INVALID_TICKS:
		cout << "The cluster does not support jobs with negative ticks." << endl << endl;
		break;
	case JC_SUCCESS:
		break;
	default:
		cout << "An invalid error code was submitted." << endl << endl;
		break;
	}
}
//O(1)
Job Scheduler::getShortestJob()
{
	return _wait_queue.top();
}

//O(2Log(J))
void Scheduler::deleteShortestJob()
{
	_wait_queue.pop();
}

int Scheduler::getNextId()
{
	return _cluster.requestId();
	
}

void Scheduler::init(int processors)
{
	_cluster = Cluster(processors);
}

//O(Log(J))
int Scheduler::insertJob(string description, int req_processors, int req_ticks)
{
	Job j = Job(getNextId(), description, req_processors, req_ticks);
	_wait_queue.push(j);
	return j.getId();
}
