#include "Cluster.h"



Cluster::Cluster()
{
	init(2);
}

Cluster::Cluster(int processors)
{
	init(processors);
}


Cluster::~Cluster()
{
}

int Cluster::getTotalProcessors() const
{
	return _total_processors;
}

int Cluster::getRunningProcessors() const
{
	return getTotalProcessors() - getAvailableProcessors();
}

int Cluster::getAvailableProcessors() const
{
	return _processors_available.size();
}

void Cluster::runJob(Job j)
{
	vector<int> processors_allocated;
	while (processors_allocated.size() < j.getNumProcessorsRequired()) {
		int proc_id = _processors_available.front();
		processors_allocated.push_back(proc_id);
		_processors_available.pop();
	}
	_processors_per_job_table[j.getId()] = processors_allocated;
}

bool Cluster::canRunJob(Job j) const
{
	return j.getNumProcessorsRequired() <= getAvailableProcessors();
}

void Cluster::tick()
{
	_completed_this_tick.clear();
	for (list<Job>::iterator job = _run_queue.begin(); job != _run_queue.end(); ++job)
	{
		job->tick();
		if(job->isDone())
		{
			_completed_this_tick.push_back(job->getId());
			releaseJob(*job);
			job = _run_queue.erase(job);
		}
	}
}

int Cluster::requestId()
{
	int id = _id_pool.front();
	_id_pool.pop();
	if (_id_pool.empty())
		_id_pool.push(id + 1);
	return id;
}

bool Cluster::isIdle() const
{
	return getRunningProcessors() == 0;
}

void Cluster::init(int processors)
{
	_id_pool.push(0);
	_total_processors = processors;
	for (int i = 0; i < processors; i++)
		_processors_available.push(i);
}

void Cluster::releaseJob(Job j)
{
	map<int,vector<int>>::iterator it = _processors_per_job_table.find(j.getId());
	vector<int> released_list = it->second;
	for (int released_id : released_list)
		_processors_available.push(released_id);
	_processors_per_job_table.erase(it);
}
void Cluster::printJobsCompleted()
{
	cout << "Jobs Completed" << endl;
	for (int job_id : _completed_this_tick)
	{
		cout << "Job #" << job_id << endl;
	}
	cout << endl;
}
void Cluster::printJobsRunning()
{
	cout << "Jobs Running" << endl;
	for (Job j : _run_queue)
		cout << "Job #" << j.getId() << " (" << j.getDescription() << ") " << j.getTicksRun() << "/" << j.getTicksRequired() << endl;
	cout << endl;
}

