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

	//! Listen to user input commands
	void listenToTextCommands();

	//! Return the command if it there is a match
	static CommandType parseCommand(const QString& command);

	/*
	 * Parses the given string id and returns it as an integer
	 * Returns InvalidID whether the string id is ill-formed
	 * Returns NoID if an empty string is provided
	 */
	static int parseId(QStringList id);

	//! Returns true if parameters consistency is respected, else false
	static bool checkParamsIntegrity(CommandType command, int id);

	// Applies the given command and id on the thread pool regardless parameters integrity
	void applyCommand(CommandType command, int id);

private:
	ThreadPool _threadManager;
};


#endif//ASYNCTASKPROGRAM_COMMANDPARSER_H
