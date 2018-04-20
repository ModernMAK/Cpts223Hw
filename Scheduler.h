
#ifndef SCHEDULER_H 
#define SCHEDULER_H
#include "Cluster.h"
#include "JobComparar.h"
#include "Job.h"
#include "queue"
#include <functional>
using std::priority_queue;
//Job Codes (JC)
#define JC_SUCCESS 0
#define JC_INVALID_PROCESSORS -1
#define JC_INVALID_TICKS -2
class Scheduler
{
public:
	Scheduler();
	Scheduler(int processors);
	~Scheduler();


	void print();
	void tick();
	bool isIdle();
	bool hasJobs();
	//Inserts the job, and returns the job ID, -1 If the job was not inserted
	void submitJob(string description, int req_processors, int req_ticks);
	void printJobsStarted();
private:
	void init(int processors);
	//Inserts the job, and returns the job ID
	int insertJob(string description, int req_processors, int req_ticks);
	/*
	* Returns JC_SUCCESS On Sucess
	* Returns JC_INVALID_PROCESSORS On Not Enough Processors
	* Returns JC_INVALID_TICKS On Job With No Ticks
	*/
	int canInsertJob(int req_processors, int req_ticks);
	//Prints a message based on the Job Code submitted
	void handleJobCode(int job_code);

	Job getShortestJob();
	Cluster _cluster;
	void deleteShortestJob();
	int getNextId();
	priority_queue<Job, vector<Job>, JobComparar> _wait_queue;
	//Print Information
	vector<Job> _began_this_tick;

};

#endif