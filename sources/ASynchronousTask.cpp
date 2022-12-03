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

	_mutex.lock();
	_state = State::RUNNING;
	_mutex.unlock();

	for (long l = 0 ; l < 100000000 ; ++l)
	{
		_mutex.lock();
		if (_state == PAUSED)
		{
			_condition.wait(&_mutex);
		}
		if (_state == STOPPED)
		{
			_mutex.unlock();
			// Leave the loop so as to stop the task
			break;
		}
		_mutex.unlock();

		std::string outputNumber = std::to_string(l) + " \n";
		if(l%100000 == 0)
			file.write(outputNumber.c_str());
	}
	file.close();

	// Only if job finished by itself
	if (_state == RUNNING)
	{
		_state = State::COMPLETED;
		qInfo() << "Task " << _id << "just completed.";
	}
}

void ASynchronousTask::pause()
{
	auto actionPause = [&]()
	{
		// Will request the task to pause at next iteration in the job
		_state = State::PAUSED;
		qInfo() << "Pausing task " << _id;
	};

	_mutex.lock();
	transition(_state, State::PAUSED, actionPause);
	_mutex.unlock();
}

void ASynchronousTask::resume()
{
	auto actionResume = [&]()
	{
		_state = State::RUNNING;
		qInfo() << "Resuming task " << _id;
		// wake up the task
		_condition.wakeOne();
	};

	_mutex.lock();
	transition(_state, State::RUNNING, actionResume);
	_mutex.unlock();
}

void ASynchronousTask::stop()
{
	auto actionStop = [&]()
	{
		_state = State::STOPPED;
		qInfo() << "Stopping task " << _id;
		// wake up the task
		_condition.wakeOne();
	};

	_mutex.lock();
	transition(_state, State::STOPPED, actionStop);
	_mutex.unlock();
}
