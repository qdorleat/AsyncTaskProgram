//
// Created by qdorleat on 01.12.22.
//

#ifndef ASYNCTASKPROGRAM_THREADPOOL_H
#define ASYNCTASKPROGRAM_THREADPOOL_H

#include <QMap>

class ASynchronousTask;

class ThreadPool
{
public:
	bool contains(unsigned id);
	unsigned createTask();
	void pause(unsigned id);
	void printStatus(unsigned id = -1);
	void resume(unsigned id);
	void stop(unsigned id);
	void terminateAllTasks();

private:
	// incremental ID for ASynchronousTask objects;
	static unsigned ID;

	QMap<unsigned, ASynchronousTask*> _async_threads;
};


#endif//ASYNCTASKPROGRAM_THREADPOOL_H
