//
// Created by qdorleat on 03.12.22.
//

#ifndef ASYNCTASKPROGRAM_TASKSTATEMACHINE_H
#define ASYNCTASKPROGRAM_TASKSTATEMACHINE_H

#include "TaskState.h"
#include <QMap>
#include <functional>

class TaskStateMachine
{
public:
	//! Returns a stringified version of the state
	static QString toString(State state);

protected:
	//! Returns true whether the transition is allowed from state 'from' to state 'to'
	bool isTransitionAllowed(State from, State to);
	//! Performs the transition if allowed from 'currentState' to 'desiredState' by calling the callback
	void transition(State currentState, State desiredState, std::function<void()> const& callBack);

private:
	static QMap<State, QSet<State>> transitions;
};


#endif//ASYNCTASKPROGRAM_TASKSTATEMACHINE_H
