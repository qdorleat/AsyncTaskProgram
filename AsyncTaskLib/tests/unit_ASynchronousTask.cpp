#include <gtest/gtest.h>

#include <ASynchronousTask.h>

#include <QDebug>
#include <chrono>

class ASynchronousTaskTest : public ASynchronousTask
{
public:
	ASynchronousTaskTest(unsigned id) : ASynchronousTask(id) {}
};

TEST(ASynchronousTaskTest, transitions)
{
	ASynchronousTaskTest task(0);
	ASSERT_EQ(task.status(), State::UNINITIALIZED);

	task.start();
	// Sleep a bit to make sure the thread started
	std::this_thread::sleep_for(std::chrono::milliseconds (100));
	ASSERT_EQ(task.status(), State::RUNNING);
	task.pause();
	ASSERT_EQ(task.status(), State::PAUSED);
	task.pause();
	ASSERT_EQ(task.status(), State::PAUSED);
	task.resume();
	ASSERT_EQ(task.status(), State::RUNNING);
	task.stop();
	ASSERT_EQ(task.status(), State::STOPPED);
	task.resume();
	ASSERT_EQ(task.status(), State::STOPPED);

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
	task.start();

	// Wait until the thread started
	condition.wait(&mutex);
	ASSERT_EQ(task.status(), State::RUNNING);

	// Wait until the thread has finished
	condition.wait(&mutex);
	ASSERT_EQ(task.status(), State::COMPLETED);

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