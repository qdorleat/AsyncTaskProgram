#include <gtest/gtest.h>

#include <ASynchronousTask.h>

#include <QDebug>
#include <chrono>

class ASynchronousTaskTest : public ASynchronousTask
{
public:
	ASynchronousTaskTest(unsigned id) : ASynchronousTask(id) {};

	TaskType type()
	{
		return TaskType::A;
	}
	void job()
	{
		_file.write("Test");
	}
};

TEST(ASynchronousTaskTest, transitions)
{
	ASynchronousTaskTest task(0);
	ASSERT_EQ(task.state(), State::UNINITIALIZED);

	task.start();
	// Sleep a bit to make sure the thread started
	std::this_thread::sleep_for(std::chrono::milliseconds (100));
	ASSERT_EQ(task.state(), State::RUNNING);
	task.pause();
	ASSERT_EQ(task.state(), State::PAUSED);
	task.pause();
	ASSERT_EQ(task.state(), State::PAUSED);
	task.resume();
	ASSERT_EQ(task.state(), State::RUNNING);
	task.stop();
	ASSERT_EQ(task.state(), State::STOPPED);
	task.resume();
	ASSERT_EQ(task.state(), State::STOPPED);

	task.quit();
	// Gives time for thread to quit
	std::this_thread::sleep_for(std::chrono::milliseconds (10));
}

TEST(ASynchronousTaskTest, transitions_completed)
{
	// Condition that wait for the thread to start
	QWaitCondition condition;
	QMutex mutex;

	ASynchronousTaskTest task(0);
	QObject::connect (&task, &ASynchronousTaskTest::stateChanged, [&condition](State newState){
		if (newState == RUNNING || newState == COMPLETED)
		{
			condition.wakeOne();
			qInfo() << "condition wake up when task is" << TaskStateMachine::toString(newState);
		}
	});
	EXPECT_EQ(task.status().state, UNINITIALIZED);
	EXPECT_EQ(task.status().progress, 0.0);
	task.start();

	// Wait until the thread started
	condition.wait(&mutex);
	ASSERT_EQ(task.state(), State::RUNNING);

	// Wait until the thread has finished
	condition.wait(&mutex);
	ASSERT_EQ(task.state(), State::COMPLETED);
	EXPECT_EQ(task.status().progress, 100.0);

	task.quit();
	mutex.unlock();

	// Gives time for thread to quit
	std::this_thread::sleep_for(std::chrono::milliseconds (10));
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}