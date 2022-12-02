//
// Created by qdorleat on 29.11.22.
//

#include "CommandParser.h"

#include "sources/ASynchronousTask.h"

#include <QTextStream>
#include <QString>
#include <QtConcurrent/QtConcurrent>

#include <iostream>

CommandType CommandParser::toCommandType(const QString& command)
{
	if (command.isNull() || command.isEmpty())
		return CommandType::NONE;

	if (command == "start")
		return CommandType::START;
	if (command == "pause")
		return CommandType::PAUSE;
	if (command == "resume")
		return CommandType::RESUME;
	if (command == "pause")
		return CommandType::STOP;
	if (command == "status")
		return CommandType::STATUS;
	if (command == "quit")
		return CommandType::QUIT;

	// Else, this is a wrong command
	return CommandType::NONE;
}

void CommandParser::listenToTextCommands()
{
	while(true)
	{
		std::cout << "  > ";
		QTextStream stdInput(stdin);
		QString line = stdInput.readLine();

		// Sorry, this is obsolete but really convenient, peace :)
		QStringList args = line.split(" ");

		if (args.empty())
			return;

		CommandType commandType = CommandParser::toCommandType(args[0]);


		auto checkId = [](const QString& idStr)
		{
			bool castOk;
			unsigned int val = idStr.toUInt(&castOk, 10);
			return castOk ? val : -1;
		};

		int id = -1;
		if (args.size()>=2)
			id = checkId(args[1]);

		processCommand(commandType, id);
	}
}

void CommandParser::processCommand(CommandType command, int id)
{
	switch (command)
	{
		case START:
			_threadManager.createTask();
			break;
		case PAUSE:
			_threadManager.pause(id);
			break;
		case RESUME:
			_threadManager.resume(id);
			break;
		case STOP:
			_threadManager.stop(id);
			break;
		case STATUS:
			std::cout << "STATUS something" << std::endl;
			break;
		case QUIT:
			std::cout << "QUIT something" << std::endl;
			break;
		default:
			break;
	}
}

