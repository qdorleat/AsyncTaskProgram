//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_COMMANDPARSER_H
#define ASYNCTASKPROGRAM_COMMANDPARSER_H

#include "CommandType.h"
#include <ThreadPool.h>

class ASynchronousTask;
class QString;

class CommandParser
{
public:

	CommandType toCommandType(const QString& command);

	void listenToTextCommands();

	void processCommand(CommandType command, int id);

private:
	static ASynchronousTask* _task;

	ThreadPool _threadManager;
};


#endif//ASYNCTASKPROGRAM_COMMANDPARSER_H
