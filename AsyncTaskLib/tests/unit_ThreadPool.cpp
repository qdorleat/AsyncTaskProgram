#include <gtest/gtest.h>

#include <ThreadPool.h>

#include <QMutex>
#include <QWaitCondition>

#include <thread>

class ThreadPoolTest : public ::testing::Test
{
protected:
	void SetUp() override;
	void TearDown() override;

protected:
	ThreadPool _threadPool;
};

void ThreadPoolTest::SetUp()
{
}

void ThreadPoolTest::TearDown()
{
	_threadPool.terminateAllTasks();
}

TEST_F(ThreadPoolTest, threadsCreation)
{
	_threadPool.createTask();
	_threadPool.createTask();
	_threadPool.createTask();

	// Gives the time for the tasks to reach a certain state before stopping
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	EXPECT_TRUE(_threadPool.contains(0));
	EXPECT_TRUE(_threadPool.contains(1));
	EXPECT_TRUE(_threadPool.contains(2));
	EXPECT_FALSE(_threadPool.contains(3));
}


TEST_F(ThreadPoolTest, terminateTasks)
{
	_threadPool.createTask();
	_threadPool.createTask();
	_threadPool.createTask();

	// Gives the time for the tasks to reach a certain state before stopping
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	_threadPool.terminateAllTasks();

	EXPECT_FALSE(_threadPool.contains(0));
	EXPECT_FALSE(_threadPool.contains(1));
	EXPECT_FALSE(_threadPool.contains(2));
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}