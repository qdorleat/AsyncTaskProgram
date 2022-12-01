//
// Created by qdorleat on 29.11.22.
//

#include "ASynchronousTask.h"

#include <QFile>
#include <QDebug>

#include <iostream>

ASynchronousTask::ASynchronousTask()
{
}

ASynchronousTask::~ASynchronousTask()
{
}

void ASynchronousTask::run()
{
	qDebug() << "Async _task begins to run";
	job();
	_condition.wait(&_mutex);
}

void ASynchronousTask::job()
{
	qDebug() << "Job starts running";

	/// JOB 1
	QString sourcePath = "../resources/jobs/job1.txt";
	QFile file(sourcePath);
	if (!file.exists())
	{
		qWarning() << "Read failed as file does not exist, path" << sourcePath;
		return;
	}

	if (!file.open(QFile::OpenModeFlag::ReadWrite))
	{
		qWarning() << "Read" << sourcePath << "failed" << file.errorString();
		return;
	}

	for (long l = 0 ; l < 100000000 ; ++l)
	{
		_mutex.lock();
		if (_shouldPause)
			_condition.wait(&_mutex);
		_shouldPause = false;
		_mutex.unlock();

		std::string outputNumber = std::to_string(l) + " \n";
		if(l%1000 == 0)
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