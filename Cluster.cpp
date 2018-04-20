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

//O(Log(J)) # of jobs running
void Cluster::runJob(Job j)
{
	vector<int> processors_allocated;
	while (processors_allocated.size() < j.getNumProcessorsRequired()) {
		int proc_id = _processors_available.front();//O(1)
		processors_allocated.push_back(proc_id);//O(1)
		_processors_available.pop();//O(1)
	}
	_processors_per_job_table[j.getId()] = processors_allocated;//Log(J)
	_run_queue.push_back(j);//O(1)
}

//O(1)
bool Cluster::canRunJob(Job j) const
{
	return j.getNumProcessorsRequired() <= getAvailableProcessors();
}
//O(P*J*Log(J))
void Cluster::tick()
{
	_completed_this_tick.clear();//O(C) <- Basically an amortized constant (Imagine inserting N jobs over N ticks, setup to finish on the same tick, this will run with O(N), however it will do so over N ticks, O(N)/N -> O(C)  
	for (list<Job>::iterator job = _run_queue.begin(); job != _run_queue.end(); job++)		//O(J)
	{
		job->tick();//O(1)
		if(job->isDone())//O(1)
		{
			_completed_this_tick.push_back(job->getId());//O(1)
			releaseJob(*job);//Log(J)P
			job = _run_queue.erase(job);//O(1)
			if (job == _run_queue.end())//Catch erasing the end of the list
				break;
		}
	}
}
//O(1)
int Cluster::requestId()
{
	int id = _id_pool.front();
	_id_pool.pop();
	if (_id_pool.empty())
		_id_pool.push(id + 1);
	return id;
}

//O(1)
bool Cluster::isIdle() const
{
	return getRunningProcessors() == 0;
}

//O(P)
void Cluster::init(int processors)
{
	_id_pool.push(0);
	_total_processors = processors;
	for (int i = 0; i < processors; i++)
		_processors_available.push(i);
}
//O(Log(J)P)
void Cluster::releaseJob(Job j)
{
	map<int,vector<int>>::iterator it = _processors_per_job_table.find(j.getId());//J
	vector<int> released_list = it->second;
	for (vector<int>::iterator it = released_list.begin(); it != released_list.end(); it++)//P
		_processors_available.push(*it);
	_processors_per_job_table.erase(it);
}
//O(J)
void Cluster::printJobsCompleted()
{
	if (_completed_this_tick.empty())
		return;
	cout << "Jobs Completed" << endl;
	for (vector<int>::iterator it = _completed_this_tick.begin(); it != _completed_this_tick.end(); it++)//J
	{
		cout << "Job #" << *it << endl;
	}
	cout << endl;
}
//O(J)
void Cluster::printJobsRunning()
{
	if(_run_queue.empty())
		return;
	cout << "Jobs Running" << endl;
	for (list<Job>::iterator it = _run_queue.begin(); it != _run_queue.end(); it++)//J
		cout << "Job #" << it->getId() << " (" << it->getDescription() << ") " << it->getTicksRun() << "/" << it->getTicksRequired() << endl;
	cout << endl;
}

