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
	_threadPool.createTask(TaskType::A);
	_threadPool.createTask(TaskType::B);
	_threadPool.createTask();

	EXPECT_TRUE(_threadPool.contains(0));
	EXPECT_TRUE(_threadPool.contains(1));
	EXPECT_TRUE(_threadPool.contains(2));

	EXPECT_EQ(_threadPool.status(0).type, TaskType::A);
	EXPECT_EQ(_threadPool.status(1).type, TaskType::B);
	EXPECT_EQ(_threadPool.status(2).type, TaskType::A);

	// Gives the time for the tasks to reach a certain state before stopping
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// Not more than 3 tasks were created at beginning
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

	// Ensure the thread pool was correctly cleaned
	EXPECT_FALSE(_threadPool.contains(3));
	EXPECT_FALSE(_threadPool.contains(4));
	EXPECT_FALSE(_threadPool.contains(5));
}

TEST_F(ThreadPoolTest, status)
{
	_threadPool.createTask();
	_threadPool.createTask();
	_threadPool.createTask();

	// Gives the time for the tasks to reach a certain state before stopping
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	EXPECT_EQ(_threadPool.status(6).state, RUNNING);
	EXPECT_EQ(_threadPool.status(7).state, RUNNING);
	EXPECT_EQ(_threadPool.status(8).state, RUNNING);

	// Should be greater than 0 after 1 second
	EXPECT_GT(_threadPool.status(6).progress, 0.0);
	EXPECT_GT(_threadPool.status(7).progress, 0.0);
	EXPECT_GT(_threadPool.status(8).progress, 0.0);
}

TEST_F(ThreadPoolTest, pausingAndStoppingTasks) {
	_threadPool.createTask();
	_threadPool.createTask();
	_threadPool.createTask();

	// Gives the time for the tasks to reach a certain state before stopping
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	EXPECT_EQ(_threadPool.status(9).state, RUNNING);
	EXPECT_EQ(_threadPool.status(10).state, RUNNING);
	EXPECT_EQ(_threadPool.status(11).state, RUNNING);
	// Should be greater than 0 after 1 second
	EXPECT_GT(_threadPool.status(9).progress, 0.0);
	EXPECT_GT(_threadPool.status(10).progress, 0.0);
	EXPECT_GT(_threadPool.status(11).progress, 0.0);

	_threadPool.pause(9);
	_threadPool.pause(10);
	_threadPool.pause(11);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	EXPECT_EQ(_threadPool.status(9).state, PAUSED);
	EXPECT_EQ(_threadPool.status(10).state, PAUSED);
	EXPECT_EQ(_threadPool.status(11).state, PAUSED);
	float progress9 = _threadPool.status(9).progress;
	float progress10 = _threadPool.status(10).progress;
	float progress11 = _threadPool.status(11).progress;
	EXPECT_GT(progress9, 0.0);
	EXPECT_GT(progress10, 0.0);
	EXPECT_GT(progress11, 0.0);

	// Wait a bit more
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// Confirm progress didn't change
	EXPECT_EQ(_threadPool.status(9).progress, progress9);
	EXPECT_EQ(_threadPool.status(10).progress, progress10);
	EXPECT_EQ(_threadPool.status(11).progress, progress11);

	// resume tasks
	_threadPool.resume(9);
	_threadPool.resume(10);
	_threadPool.resume(11);

	// Wait a second more
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	EXPECT_EQ(_threadPool.status(9).state, RUNNING);
	EXPECT_EQ(_threadPool.status(10).state, RUNNING);
	EXPECT_EQ(_threadPool.status(11).state, RUNNING);

	// Confirm that progress started to grow again
	float second_progress9 = _threadPool.status(9).progress;
	float second_progress10 = _threadPool.status(10).progress;
	float second_progress11 = _threadPool.status(11).progress;
	EXPECT_GT(second_progress9, progress9);
	EXPECT_GT(second_progress10, progress10);
	EXPECT_GT(second_progress11, progress11);

	// Now stop the task that is paused
	_threadPool.stop(9);
	_threadPool.stop(10);
	_threadPool.stop(11);
	EXPECT_EQ(_threadPool.status(9).state, STOPPED);
	EXPECT_EQ(_threadPool.status(10).state, STOPPED);
	EXPECT_EQ(_threadPool.status(11).state, STOPPED);

	// Wait a bit more
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// Confirm progress didn't change
	EXPECT_EQ(_threadPool.status(9).progress, second_progress9);
	EXPECT_EQ(_threadPool.status(10).progress, second_progress10);
	EXPECT_EQ(_threadPool.status(11).progress, second_progress11);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}