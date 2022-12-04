//
// Created by qdorleat on 01.12.22.
//

#include "ThreadPool.h"

#include "Definitions.h"
#include "ASynchronousTask.h"

#include <QDebug>

unsigned ThreadPool::ID = 0;

unsigned ThreadPool::createTask()
{
	unsigned idNewAsyncTask = ID;

	if (!_async_threads.contains(idNewAsyncTask))
	{
		ASynchronousTask* task = new ASynchronousTask(idNewAsyncTask);
		qInfo() << "Starting task " << idNewAsyncTask;
		task->start();
		_async_threads[idNewAsyncTask] = task;
		++ID;
		return (idNewAsyncTask);
	}
	else
	{
		qWarning() << "The map already contains the thread with the ID " << ID;
	}
	return -1;
}

bool ThreadPool::contains(unsigned id)
{
	return _async_threads.contains(id);
}

void ThreadPool::pause(unsigned id)
{
	if (_async_threads.contains(id))
	{
		_async_threads[id]->pause();
	}
	else
	{
		qWarning() << "There is no task with the given ID" << id;
	}
}

void ThreadPool::printStatus(unsigned id)
{
	// Print All task
	if (id == NoID)
	{
		for (auto const id : _async_threads.keys())
			printStatus(id);
			return;
	}
	if (_async_threads.contains(id))
	{
		qInfo() << "Task: ID " << id
		        << "Status:" << TaskStateMachine::toString(_async_threads[id]->status());
	}
	else
	{
		qWarning() << "There is no task with the given ID" << id;
	}
}

void ThreadPool::resume(unsigned id)
{
	if (_async_threads.contains(id))
	{
		_async_threads[id]->resume();
	}
	else
	{
		qWarning() << "There is no task with the given ID" << id;
	}
}

void ThreadPool::stop(unsigned id)
{
	if (_async_threads.contains(id))
	{
		_async_threads[id]->stop();
	}
	else
	{
		qWarning() << "There is no task with the given ID" << id;
	}
}

void ThreadPool::terminateAllTasks()
{
	for (auto const task: _async_threads)
	{
		task->stop();
		task->exit();
		task->deleteLater();
	}
	_async_threads.clear();
}
