//
// Created by qdorleat on 29.11.22.
//

#include "ASynchronousTask.h"

#include "Task.h"

#include <QDebug>

#include <iostream>

unsigned ASynchronousTask::ID = 0;

ASynchronousTask::ASynchronousTask()
{
}

ASynchronousTask::~ASynchronousTask()
{
}

void ASynchronousTask::run()
{
	qDebug() << "Async _task begins to run";
	_mutex.lock();
	task = new Task;
	task->runJob();
	_condition.wait(&_mutex);
	_mutex.unlock();
}


void ASynchronousTask::handleResults(const QString &)
{
	qDebug() << "QDO manage results";
}