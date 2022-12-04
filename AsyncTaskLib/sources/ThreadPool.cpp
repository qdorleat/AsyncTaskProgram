//
// Created by qdorleat on 01.12.22.
//

#include "ThreadPool.h"

#include "Definitions.h"
#include "ASynchronousTaskAlgoA.h"
#include "ASynchronousTaskAlgoB.h"

#include <QDebug>

unsigned ThreadPool::ID = 0;

unsigned ThreadPool::createTask(TaskType type)
{
	unsigned idNewAsyncTask = ID;

	if (!_async_threads.contains(idNewAsyncTask))
	{
		ASynchronousTask* task;
		if (type == TaskType::A)
			task = new ASyncTaskA(idNewAsyncTask);
		else
			task = new ASyncTaskB(idNewAsyncTask);

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
				<< "Type:" << QString::number(static_cast<unsigned int>(_async_threads[id]->type()))
				<< "Status:" << TaskStateMachine::toString(_async_threads[id]->status())
				<< "Progress:" << _async_threads[id]->progress() << "%";
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
