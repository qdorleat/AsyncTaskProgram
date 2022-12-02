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
	/// JOB 1
	QString sourcePath = "../resources/jobs/job"+QString::number(_id)+".txt";
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
//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	file.close();

	qDebug() << "JOB HAS FINISHED OK";
//	emit resultReady("JOB HAS FINISHED OK");
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


void ASynchronousTask::handleResults(const QString &)
{
//	qDebug() << "QDO manage results";
}