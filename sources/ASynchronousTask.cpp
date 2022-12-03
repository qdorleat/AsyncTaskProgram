//
// Created by qdorleat on 29.11.22.
//

#include "ASynchronousTask.h"

#include <QFile>
#include <QDebug>

#include <iostream>


QMap<State, QSet<State>> ASynchronousTask::transitions {
	{UNINITIALIZED, {RUNNING}},
	{RUNNING, {PAUSED, STOPPED, COMPLETED}},
	{PAUSED, {RUNNING, STOPPED}},
	{STOPPED, {}},
	{COMPLETED, {}},
};

bool ASynchronousTask::isTransitionAllowed(State from, State to)
{
	if (!transitions.contains(from))
	{
		return false;
	}
	return transitions[from].contains(to);
}

void ASynchronousTask::transition(State desiredState, std::function<void()> const& callBack)
{
	_mutex.lock();

	bool stateTransitionPossible = isTransitionAllowed(_state, desiredState);
	if (stateTransitionPossible)
	{
		// Execute the callback of state change
		callBack();
	}
	else
	{
		qWarning() << "Not allowed for the task" << _id << "to leave state" << _state << "to state" << desiredState;
	}
	_mutex.unlock();
}

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
	transition(State::PAUSED, actionPause);
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
	transition(State::RUNNING, actionResume);
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
	transition(State::STOPPED, actionStop);
}
