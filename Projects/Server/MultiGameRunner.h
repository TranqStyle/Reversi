#ifndef MULTIGAMERUNNER_H
#define MULTIGAMERUNNER_H

#include "State.h"
#include "GameHandler.h"

#include <map>

class MultiGameRunner 
{
public:
	MultiGameRunner(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1, const size_t& gameSample);
	
	friend std::ostream& operator<<(std::ostream& os, const MultiGameRunner& multiGameRunner);

	void play();

	AbstractPlayer::Ptr getPlayer0() const;
	AbstractPlayer::Ptr getPlayer1() const;
	std::string getPlayer0Name() const;
	std::string getPlayer1Name() const;
	
private:
	AbstractPlayer::Ptr _player0;
	AbstractPlayer::Ptr _player1;
	
	std::map<State::Outcome, size_t> _gameOutcomes;
	
	size_t _totalGamesToBePlayed;
	size_t _currentGameCount;
};

#endif // MULTIGAMERUNNER_H