//
// Created by qdorleat on 04.12.22.
//

#ifndef ASYNCTASKPROGRAM_ASYNCHRONOUSTASKALGOB_H
#define ASYNCTASKPROGRAM_ASYNCHRONOUSTASKALGOB_H

#include "ASynchronousTask.h"

class ASyncTaskB : public ASynchronousTask
{
public:
	ASyncTaskB(unsigned id) : ASynchronousTask(id) {};

	QString type()
	{
		return QString::number(static_cast<unsigned int>(TaskType::B));
	}

	void job()
	{
		_file.write("B");
	}
};

#endif//ASYNCTASKPROGRAM_ASYNCHRONOUSTASKALGOB_H
