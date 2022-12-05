//
// Created by qdorleat on 04.12.22.
//

#ifndef ASYNCTASKPROGRAM_DEFINITIONS_H
#define ASYNCTASKPROGRAM_DEFINITIONS_H

#include "TaskState.h"
#include <limits>

constexpr int InvalidID = {std::numeric_limits<int>::max()};
constexpr int NoID = {std::numeric_limits<int>::max() - 1};

enum class TaskType
{
	A = 42,
	B = 666,
};

struct TaskStatus
{
	unsigned id;
	TaskType type;
	State state;
	float progress;
};

#endif//ASYNCTASKPROGRAM_DEFINITIONS_H
