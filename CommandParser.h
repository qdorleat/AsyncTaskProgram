//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_COMMANDPARSER_H
#define ASYNCTASKPROGRAM_COMMANDPARSER_H

#include "CommandType.h"

class QString;
class ASynchronousTask;

class CommandParser {
public:


	static CommandType toCommandType(const QString& command);

	static void listenToTextCommands();

	static void processCommand(CommandType command, int id);

private:
	static ASynchronousTask* _task;
};


#endif//ASYNCTASKPROGRAM_COMMANDPARSER_H
