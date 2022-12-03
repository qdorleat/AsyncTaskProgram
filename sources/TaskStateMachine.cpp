//
// Created by qdorleat on 03.12.22.
//

#include "TaskStateMachine.h"

#include <QDebug>
#include <QSet>


QMap<State, QSet<State>> TaskStateMachine::transitions {
    {UNINITIALIZED, {RUNNING}},
    {RUNNING, {PAUSED, STOPPED, COMPLETED}},
    {PAUSED, {RUNNING, STOPPED}},
    {STOPPED, {}},
    {COMPLETED, {}},
};

QString TaskStateMachine::toString(State state)
{
	switch (state) {
		case (UNINITIALIZED): return "UnInitialized";
		case (RUNNING): return "Running";
		case (PAUSED): return "Paused";
		case (STOPPED): return "Stopped";
		case (COMPLETED): return "Completed";
		 default: return "Unknown State";
	}
}

bool TaskStateMachine::isTransitionAllowed(State from, State to)
{
	if (!transitions.contains(from))
	{
		return false;
	}
	return transitions[from].contains(to);
}

void TaskStateMachine::transition(State currentState, State desiredState, std::function<void()> const& callBack)
{
	bool stateTransitionPossible = isTransitionAllowed(currentState, desiredState);
	if (stateTransitionPossible)
	{
		// Execute the callback of state change
		callBack();
	}
	else
	{
		qWarning() << "Not allowed for the task to leave state" << toString(currentState) << "to state" << toString(desiredState);
	}
}