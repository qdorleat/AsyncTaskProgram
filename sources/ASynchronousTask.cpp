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
	task = new Task;
	task->moveToThread(&_workingThread);

	connect(&_workingThread, &QThread::finished, task, &QObject::deleteLater);
	connect(this, &ASynchronousTask::operate, task, &Task::runJob);
	connect(task, &Task::resultReady, this, &ASynchronousTask::handleResults);
	_workingThread.start();

	qDebug() << "Command started";
}

ASynchronousTask::~ASynchronousTask()
{
	_workingThread.quit();
	_workingThread.wait();
}

void ASynchronousTask::start()
{
	qDebug() << __PRETTY_FUNCTION__;
	task->runJob();
}

void ASynchronousTask::pause()
{
}

void ASynchronousTask::stop()
{
}

void ASynchronousTask::handleResults(const QString &)
{
	qDebug() << "QDO manage results";
}