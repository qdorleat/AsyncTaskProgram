//
// Created by qdorleat on 29.11.22.
//

#include "ASynchronousTask.h"

#include <QFile>
#include <QDebug>

#include <cmath>
#include <iostream>


ASynchronousTask::ASynchronousTask(unsigned id)
: _id(id)
{
}

ASynchronousTask::~ASynchronousTask()
{
}

bool ASynchronousTask::setup()
{
	QString sourcePath = "./job"+QString::number(_id)+".txt";
	_file.setFileName(sourcePath);
	// Following will work in both case file exist or not.
	if (!_file.open(QIODevice::WriteOnly))
	{
		qWarning() << "Cannot create file " << sourcePath << _file.errorString() << ", please check your Write permissions";
		return false;
	}
	return true;
}

void ASynchronousTask::run()
{
	setup();

	_mutex.lock();
	_state = State::RUNNING;
	emit stateChanged(_state);
	_mutex.unlock();

	for (int l = 0 ; l < 100000000 ; ++l)
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
		_progress = std::roundf((l+1) / 1000000);
		_mutex.unlock();

		std::string outputNumber = std::to_string(l) + " \n";
		if(l%100000 == 0)
			job();

	}
	_file.close();

	// Only if job finished by itself
	if (_state == RUNNING)
	{
		_state = State::COMPLETED;
		emit stateChanged(_state);
		qInfo() << "Task " << _id << "just completed.";
	}
}

State ASynchronousTask::state()
{
	State state;

	_mutex.lock();
	state = _state;
	_mutex.unlock();

	return state;
}

TaskStatus ASynchronousTask::status()
{
	TaskStatus status;

	_mutex.lock();
	status.id = _id;
	status.type = type();
	status.state = _state;
	status.progress = _progress;
	_mutex.unlock();

	return status;
}

void ASynchronousTask::pause()
{
	auto actionPause = [&]()
	{
		// Will request the task to pause at next iteration in the job
		_state = State::PAUSED;
		emit stateChanged(_state);
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
		emit stateChanged(_state);
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
		emit stateChanged(_state);
		qInfo() << "Stopping task " << _id;
		// wake up the task
		_condition.wakeOne();
	};

	_mutex.lock();
	transition(_state, State::STOPPED, actionStop);
	_mutex.unlock();
}


