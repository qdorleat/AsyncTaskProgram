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
	task.resume();
	ASSERT_EQ(task.status(), State::RUNNING);
	task.stop();
	ASSERT_EQ(task.status(), State::STOPPED);
	task.resume();
	ASSERT_EQ(task.status(), State::STOPPED);
}

TEST(ASynchronousTaskTest, transitions_completed)
{
	ASynchronousTaskTest task(0);
	task.start();
	ASSERT_EQ(task.status(), State::RUNNING);

	// TODO wait til its finished
	ASSERT_EQ(task.status(), State::COMPLETED);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}