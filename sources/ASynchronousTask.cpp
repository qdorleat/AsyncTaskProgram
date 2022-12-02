//
// Created by qdorleat on 29.11.22.
//

#include "ASynchronousTask.h"

#include <QFile>
#include <QDebug>

#include <iostream>

ASynchronousTask::ASynchronousTask(unsigned id)
: _id(id)
{
}

ASynchronousTask::~ASynchronousTask()
{
}

void ASynchronousTask::run()
{
	job();
	_condition.wait(&_mutex);
}

void ASynchronousTask::job()
{
	QString sourcePath = "./job"+QString::number(_id)+".txt";
	QFile file(sourcePath);
	// Following will work in both case file exist or not.
	if (!file.open(QIODevice::WriteOnly))
	{
		qWarning() << "Cannot create file " << sourcePath << file.errorString() << ", please check your Write permissions";
		return;
	}

	for (long l = 0 ; l < 1000000000 ; ++l)
	{
		_mutex.lock();
		if (_shouldPause)
			_condition.wait(&_mutex);
		_shouldPause = false;
		_mutex.unlock();

		std::string outputNumber = std::to_string(l) + " \n";
		if(l%100000 == 0)
			file.write(outputNumber.c_str());
	}
	file.close();

	qInfo() << "Task " << _id << "just finished";
}

void ASynchronousTask::pause()
{
	_mutex.lock();
	_shouldPause = true;
	_mutex.unlock();
}

void ASynchronousTask::resume()
{
	_mutex.lock();
	_condition.wakeOne();
	_mutex.unlock();
}

void ASynchronousTask::stop()
{
	// TODO
}
