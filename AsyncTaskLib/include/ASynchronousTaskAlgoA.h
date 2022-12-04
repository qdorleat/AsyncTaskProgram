//
// Created by qdorleat on 04.12.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASKALGOA_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASKALGOA_H

#include "ASynchronousTask.h"

class ASyncTaskA : public ASynchronousTask
{
public:
	ASyncTaskA(unsigned id) : ASynchronousTask(id) {};

	TaskType type()
	{
		return TaskType::A;
	}
	void job()
	{
		_file.write("A");
	}
};

#endif//ASYNCTASKPROGRAM_ASYNCHRONOUSTASKALGOA_H
