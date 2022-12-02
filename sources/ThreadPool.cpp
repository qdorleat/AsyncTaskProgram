//
// Created by qdorleat on 01.12.22.
//

#include "ThreadPool.h"
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

void ThreadPool::pause(unsigned id)
{
	if (_async_threads.contains(id))
	{
		qInfo() << "Pausing task " << id;
		_async_threads[id]->pause();
	}
	else
	{
		qWarning() << "The map does not contain the task with the ID " << id;
	}
}

void ThreadPool::resume(unsigned id)
{
	if (_async_threads.contains(id))
	{
		qInfo() << "Resuming task " << id;
		_async_threads[id]->resume();
	}
	else
	{
		qWarning() << "The map does not contain the task with the ID " << id;
	}
}

void ThreadPool::stop(unsigned id)
{
	if (_async_threads.contains(id))
	{
		qInfo() << "Stoping task " << id;
		_async_threads[id]->stop();
	}
	else
	{
		qWarning() << "The map does not contain the task with the ID " << id;
	}
}
