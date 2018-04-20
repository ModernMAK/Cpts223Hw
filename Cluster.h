#ifndef CLUSTER_H
#define CLUSTER_H


#include "Job.h"
#include <queue>
#include <list>
#include <map>
#include "iostream"
using std::list;
using std::queue;
using std::map;
using std::vector;
using std::iterator;
using std::endl;
using std::cout;

class Cluster
{
public:
	Cluster();
	Cluster(int processors);
	~Cluster();
	int getTotalProcessors() const;
	int getRunningProcessors() const;
	int getAvailableProcessors() const;

	void runJob(Job j);
	bool canRunJob(Job j) const;
	void tick();
	int requestId();
	bool isIdle() const;
	void printJobsCompleted();
	void printJobsRunning();
private:

	void init(int processors);
	void releaseJob(Job j);
	//We need to iterate over this queue, so we use list, we still treat it as a queue
	//We dont need random access, so we dont use vector
	list<Job> _run_queue;
	vector<int> _completed_this_tick;
	//We dont need to iterate over this queue, so we use a queue
	queue<int> _processors_available;
	map<int, vector<int>> _processors_per_job_table;
	int _total_processors;
	queue<int> _id_pool;
};

#endif