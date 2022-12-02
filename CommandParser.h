//
// Created by qdorleat on 29.11.22.
//

#ifndef ASYNCTASKPROGRAM_COMMANDPARSER_H
#define ASYNCTASKPROGRAM_COMMANDPARSER_H

#include "CommandType.h"

class QString;

class CommandParser {
public:


	static CommandType toCommandType(const QString& command);

	static void listenToTextCommands();

	static void processCommand(CommandType command);
};


#endif//ASYNCTASKPROGRAM_COMMANDPARSER_H
