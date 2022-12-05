//
// Created by qdorleat on 01.12.22.
//

#ifndef ASYNCTASKPROGRAM_THREADPOOL_H
#define ASYNCTASKPROGRAM_THREADPOOL_H

#include "Definitions.h"
#include <QMap>

class ASynchronousTask;

/**
 * Thread pool class represents the API of the library operating commands from the user
 * It allows to create tasks and their safe manipulation.
 * It holds ownership on the tasks and is responsible of their destruction
 * All the function of the ThreadPool class are thread-safe
 */
class ThreadPool
{
public:
	~ThreadPool();

	//! Creates a task of a given type
	unsigned createTask(TaskType type = TaskType::A);
	//! Returns true whether there exists a thread with the given ID
	bool contains(unsigned id);
	//! Pauses the task of the given ID if it exists
	void pause(unsigned id);
	//! Prints the status of a task of the given ID if it exists or print the status of all task if NoId is provided
	void printStatus(unsigned id = NoID);
	//! Resumes the task of the given ID if it exists
	void resume(unsigned id);
	//! Returns a structure containing information of the current status of the task
	TaskStatus status(unsigned id);
	//! Stops the task of the given ID if it exists
	void stop(unsigned id);
	//! Terminate all the task without any waiting condition and clear the tasks map
	void terminateAllTasks();

private:
	// incremental ID for ASynchronousTask objects;
	static unsigned ID;

	QMap<unsigned, ASynchronousTask*> _async_threads;
};


#endif//ASYNCTASKPROGRAM_THREADPOOL_H
