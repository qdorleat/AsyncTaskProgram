//
// Created by qdorleat on 29.11.22.
//

#include "CommandParser.h"

#include "sources/ASynchronousTask.h"

#include <QObject>
#include <QTextStream>
#include <QString>
#include <QtConcurrent/QtConcurrent>

#include <iostream>

ASynchronousTask* CommandParser::_task = nullptr;

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
		processCommand(commandType);
		qDebug() << "Finished process command";
	}
}

void CommandParser::processCommand(CommandType command)
{
	switch (command)
	{
		case START:
		{
			std::cout << "START something" << std::endl;
			_task = new ASynchronousTask();
			_task->start();
			break;
		}
		case PAUSE:
			std::cout << "PAUSE something" << std::endl;
			break;
		case RESUME:
			std::cout << "RESUME something" << std::endl;
			_task->resume();
			break;
		case STOP:
			std::cout << "STOP something" << std::endl;
			_task->stop();
			break;
		case STATUS:
			std::cout << "STATUS something" << std::endl;
			break;
		case QUIT:
			std::cout << "QUIT something" << std::endl;
		default:
			break;
	}
}

