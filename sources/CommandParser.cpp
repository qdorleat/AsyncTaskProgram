//
// Created by qdorleat on 29.11.22.
//

#include "CommandParser.h"

#include <ASynchronousTask.h>
#include <Definitions.h>

#include <QString>
#include <QTextStream>
#include <QtConcurrent/QtConcurrent>

#include <iostream>

CommandType CommandParser::parseCommand(const QString& command)
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

		CommandType commandType = CommandParser::parseCommand(args[0]);

		args.takeFirst();
		int id = parseId(args);

		bool areParametersConsistent = checkParamsIntegrity(commandType, id);
		if (areParametersConsistent)
		{
			applyCommand(commandType, id);
		}
	}
}

int CommandParser::parseId(QStringList id)
{
	if (id.size() > 1)
	{
		qWarning() << "Please provide a valid ID";
		return InvalidID;
	}

	if (id.size() == 0)
	{
		return NoID;
	}

	bool castOk;
	unsigned int val = id[0].toUInt(&castOk, 10);

	// Well-formed ID
	if (castOk)
	{
		return val;
	}

	return InvalidID;
}

bool CommandParser::checkParamsIntegrity(CommandType command, int id)
{
	switch (command)
	{
		case START:
		{
			switch (id)
			{
				case NoID: return true;
				case InvalidID:
				default:
					qWarning() << "Start command takes no ID";
					return false;
			}
		}
		case PAUSE:
		case RESUME:
		case STOP:
		{
			switch (id)
			{
				case NoID:
				{
					qWarning() << "Command takes no ID";
					return false;
				}
				case InvalidID:
				{
					qWarning() << "Invalid ID";
					return false;
				}
				default:
					return true;
			}
		}
		case STATUS:
		{
			switch (id)
			{
				case InvalidID: {
					qWarning() << "Invalid ID";
					return false;
				}
				case NoID:
				default:
					return true;
			}
		}
		case QUIT:
			return true;
	}

	return false;
}

void CommandParser::applyCommand(CommandType command, int id)
{
	switch (command)
	{
		case NONE:
			return;
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