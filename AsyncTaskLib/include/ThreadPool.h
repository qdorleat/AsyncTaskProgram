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
	unsigned createTask();
	void pause(unsigned id);
	void resume(unsigned id);
	void stop(unsigned id);

private:
	// incremental ID for ASynchronousTask objects;
	static unsigned ID;

	QMap<unsigned, ASynchronousTask*> _async_threads;
};


#endif//ASYNCTASKPROGRAM_THREADPOOL_H
