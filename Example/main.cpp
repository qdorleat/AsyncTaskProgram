#include <QApplication>
#include <QtCore>

#include <QCommandLineParser>
#include <QStringList>

#include "sources/CommandParser.h"

void processArgs(const QStringList& arguments)
{
	if (arguments.empty())
		return;

	QCommandLineParser parser;
	const char* description = "The follwing program allows to manage asynchronous tasks after running the program. Once the program will run, it will listen to the following commands\n\n"
	                          "commands:\n\n"
	                          "start                 starts a task of type 42 and prints its ID\n"
	                          "start  <task_type_id> starts a task of a given type among [42, 666] and and prints its ID \n"
	                          "pause  <task_id>      pause the task with the given id and print a confirmation message\n"
	                          "resume <task_id>      resume task with the given id (if paused) and print a confirmation message\n"
	                          "stop   <task_id>      stop the task with the given id (if not stopped) and print a confirmation message \n"
	                          "status                prints the id, the state, an indicator of progress for each task. and the task type ID.\n"
	                          "status <task_id>      As above, but for a single task.\n"
	                          "quit                  gracefully shut down";
	parser.setApplicationDescription(QString(description));
	parser.addHelpOption();
	parser.process(arguments);
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	processArgs(QCoreApplication::arguments());

	CommandParser parser;
	parser.listenToTextCommands();

	return EXIT_SUCCESS;
}
