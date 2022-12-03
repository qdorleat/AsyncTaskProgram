#include <gtest/gtest.h>

#include <TaskStateMachine.h>

#include <QDebug>

class TaskStateMachineTest : public TaskStateMachine
{
public:
	using TaskStateMachine::transition;
};

TEST(StateMachineTest, transitions)
{
	auto allowedTransition = [](){ qDebug() << "Transition accepted"; };
	auto illegalTransition = [](){ ASSERT_TRUE(false); };

	// In case a transition is illegal, is will pass illegalTransition and assert
	TaskStateMachineTest sm;
	sm.transition(State::UNINITIALIZED, State::UNINITIALIZED, illegalTransition);
	sm.transition(State::UNINITIALIZED, State::RUNNING, allowedTransition);
	sm.transition(State::UNINITIALIZED, State::PAUSED, illegalTransition);
	sm.transition(State::UNINITIALIZED, State::STOPPED, illegalTransition);
	sm.transition(State::UNINITIALIZED, State::COMPLETED, illegalTransition);

	sm.transition(State::RUNNING, State::UNINITIALIZED, illegalTransition);
	sm.transition(State::RUNNING, State::RUNNING, illegalTransition);
	sm.transition(State::RUNNING, State::PAUSED, allowedTransition);
	sm.transition(State::RUNNING, State::STOPPED, allowedTransition);
	sm.transition(State::RUNNING, State::COMPLETED, allowedTransition);

	sm.transition(State::PAUSED, State::UNINITIALIZED, illegalTransition);
	sm.transition(State::PAUSED, State::RUNNING, allowedTransition);
	sm.transition(State::PAUSED, State::PAUSED, illegalTransition);
	sm.transition(State::PAUSED, State::STOPPED, allowedTransition);
	sm.transition(State::PAUSED, State::COMPLETED, illegalTransition);

	sm.transition(State::STOPPED, State::UNINITIALIZED, illegalTransition);
	sm.transition(State::STOPPED, State::RUNNING, illegalTransition);
	sm.transition(State::STOPPED, State::PAUSED, illegalTransition);
	sm.transition(State::STOPPED, State::STOPPED, illegalTransition);
	sm.transition(State::STOPPED, State::COMPLETED, illegalTransition);

	sm.transition(State::COMPLETED, State::UNINITIALIZED, illegalTransition);
	sm.transition(State::COMPLETED, State::RUNNING, illegalTransition);
	sm.transition(State::COMPLETED, State::PAUSED, illegalTransition);
	sm.transition(State::COMPLETED, State::STOPPED, illegalTransition);
	sm.transition(State::COMPLETED, State::COMPLETED, illegalTransition);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}