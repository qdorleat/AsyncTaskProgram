#include <gtest/gtest.h>

#include "../sources/CommandParser.cpp"
#include <Definitions.h>

TEST(CommandParserTest, parsingID)
{
	QStringList correctId1 = {"0"};
	EXPECT_EQ(CommandParser::parseId(correctId1), 0);

	QStringList correctId2 = {"00"};
	EXPECT_EQ(CommandParser::parseId(correctId2), 0);

    QStringList correctId3 = {"42"};
    EXPECT_EQ(CommandParser::parseId(correctId3), 42);

	QStringList incorrectId1 = {"00s"};
	EXPECT_EQ(CommandParser::parseId(incorrectId1), InvalidID);

	QStringList incorrectId2 = {"incorrect"};
	EXPECT_EQ(CommandParser::parseId(incorrectId2), InvalidID);

	QStringList incorrectId3 = {"this", "is", "ill", "formed", "ID"};
	EXPECT_EQ(CommandParser::parseId(incorrectId3), InvalidID);

	QStringList noId = {};
	EXPECT_EQ(CommandParser::parseId(noId), NoID);
}

TEST(CommandParserTest, parsingCommand)
{
	EXPECT_EQ(CommandParser::parseCommand("start"), START);
	EXPECT_EQ(CommandParser::parseCommand("pause"), PAUSE);
	EXPECT_EQ(CommandParser::parseCommand("resume"), RESUME);
	EXPECT_EQ(CommandParser::parseCommand("stop"), STOP);
	EXPECT_EQ(CommandParser::parseCommand("status"), STATUS);
	EXPECT_EQ(CommandParser::parseCommand("quit"), QUIT);

	EXPECT_EQ(CommandParser::parseCommand(QString::null), NONE);
	EXPECT_EQ(CommandParser::parseCommand(""), NONE);
	EXPECT_EQ(CommandParser::parseCommand("statr"), NONE);
	EXPECT_EQ(CommandParser::parseCommand("This is not a valid command"), NONE);
}

TEST(CommandParserTest, checkCommandAndIdIntegrity)
{
	EXPECT_EQ(CommandParser::checkParamsIntegrity(START, 0), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(START, InvalidID), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(START, NoID), true);

	EXPECT_EQ(CommandParser::checkParamsIntegrity(PAUSE, 0), true);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(PAUSE, InvalidID), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(PAUSE, NoID), false);

	EXPECT_EQ(CommandParser::checkParamsIntegrity(RESUME, 0), true);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(RESUME, InvalidID), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(RESUME, NoID), false);

	EXPECT_EQ(CommandParser::checkParamsIntegrity(STOP, 0), true);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(STOP, InvalidID), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(STOP, NoID), false);

	EXPECT_EQ(CommandParser::checkParamsIntegrity(STATUS, 0), true);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(STATUS, InvalidID), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(STATUS, NoID), true);

	EXPECT_EQ(CommandParser::checkParamsIntegrity(QUIT, 0), true);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(QUIT, InvalidID), true);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(QUIT, NoID), true);

	EXPECT_EQ(CommandParser::checkParamsIntegrity(NONE, 0), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(NONE, InvalidID), false);
	EXPECT_EQ(CommandParser::checkParamsIntegrity(NONE, NoID), false);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}