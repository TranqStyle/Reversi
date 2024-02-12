#ifndef MULTIGAMERUNNER_H
#define MULTIGAMERUNNER_H

#include "State.h"
#include "GameHandler.h"

#include <map>

class MultiGameRunner 
{
public:

	MultiGameRunner(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1, const size_t& totalGamesToBePlayed);
	
	void play();

	void announceResults(const std::map<State::Outcome, size_t>&) const;
	
private:
	AbstractPlayer::Ptr _player0;
	AbstractPlayer::Ptr _player1;
	
	size_t _totalGamesToBePlayed;
};

#endif // MULTIGAMERUNNER_H