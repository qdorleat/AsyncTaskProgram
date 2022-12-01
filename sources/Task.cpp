//
// Created by qdorleat on 29.11.22.
//

#include "Task.h"

#include <QDebug>
#include <QFile>

#include <iostream>
#include <thread>
#include <chrono>

void Task::runJob()
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
		if (_shouldStop)
//			break;
			_condition.wait(&_mutex);
		_shouldStop = false;
		_mutex.unlock();

		std::string outputNumber = std::to_string(l) + " \n";
		if(l%1000 == 0)
			file.write(outputNumber.c_str());
//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	file.close();

	qDebug() << "JOB HAS FINISHED OK";
	emit resultReady("JOB HAS FINISHED OK");
}

void Task::stop()
{
	_mutex.lock();
	_shouldStop = true;
	_mutex.unlock();
}

void Task::resume()
{
	_mutex.lock();
	_condition.wakeOne();
	_mutex.unlock();
}