//
// Created by qdorleat on 01.12.22.
//

#include "ThreadPool.h"
#include "ASynchronousTask.h"

#include <QDebug>

unsigned ThreadPool::ID = 0;

unsigned ThreadPool::createTask()
{
	if (!_async_threads.contains(ID))
	{
		ASynchronousTask* task = new ASynchronousTask();
		task->start();
		_async_threads[ID++] = task;
		return (ID-1);
	}
	else
	{
		qWarning() << "The map already contains the trhead with the ID " << ID;
	}
	return -1;
}

void ThreadPool::pause(unsigned id)
{
	if (_async_threads.contains(id))
	{
		qInfo() << "Pausing thread " << id;
		_async_threads[id]->pause();
	}
	else
	{
		qWarning() << "The map does not contain the trhead with the ID " << id;
	}
}

void ThreadPool::resume(unsigned id)
{
	if (_async_threads.contains(id))
	{
		qInfo() << "Resuming thread " << id;
		_async_threads[id]->resume();
	}
	else
	{
		qWarning() << "The map does not contain the trhead with the ID " << id;
	}
}

void ThreadPool::stop(unsigned id)
{
	if (_async_threads.contains(id))
	{
		qInfo() << "Stoping thread " << id;
		_async_threads[id]->stop();
	}
	else
	{
		qWarning() << "The map does not contain the trhead with the ID " << id;
	}
}
