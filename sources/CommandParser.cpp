//
// Created by qdorleat on 29.11.22.
//

#include "CommandParser.h"

#include <ASynchronousTask.h>

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
	if (command == "stop")
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

		QString id = "";
		if (args.size()>=2)
			id = args[1];

		processCommand(commandType, id);
	}
}

void CommandParser::processCommand(CommandType command, QString idStr /* = "" */)
{
	if (idStr == "" && (command == PAUSE || command == RESUME || command == STOP))
	{
		qWarning() << "Please provide an ID";
		return;
	}

	auto checkId = [](const QString& idStr)
	{
		bool castOk;
		unsigned int val = idStr.toUInt(&castOk, 10);
		return castOk ? val : -1;
	};
	int id = checkId(idStr);

	if (command != START &&
		command != STATUS &&
		id == -1)
	{
		qWarning() << "Please provide a correct ID";
		return;
	}

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
			_threadManager.printStatus(id);
			break;
		case QUIT:
			std::cout << "QUIT something" << std::endl;
			break;
		default:
			break;
	}
}

