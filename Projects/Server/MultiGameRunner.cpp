#include "MultiGameRunner.h"

MultiGameRunner::MultiGameRunner(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1, const size_t& totalGamesToBePlayed = 1)
	: _player0{ player0 }, _player1{ player1 }, _totalGamesToBePlayed{ totalGamesToBePlayed }
{
	_gameOutcomes[State::Outcome::P0WIN];
	_gameOutcomes[State::Outcome::P1WIN];
	_gameOutcomes[State::Outcome::DRAW];
	_currentGameCount = 0;
}


void MultiGameRunner::play() 
{
	GameHandler gameHandler{};

	for (size_t i{ 0 }; i < _totalGamesToBePlayed; ++i) 
	{	
		gameHandler.init(_player0, _player1);
		

		State::Outcome outcome = gameHandler.play();
		
		++_currentGameCount;
		++_gameOutcomes[outcome];	
	}
}

std::ostream& operator<<(std::ostream& os, const MultiGameRunner& multiGameRunner) 
{	
	os << "Games played: " << multiGameRunner._currentGameCount << " / " << multiGameRunner._totalGamesToBePlayed << "\n";
	os << "P0( " << multiGameRunner.getPlayer0Name() << " ) won: " << multiGameRunner._gameOutcomes.at(State::Outcome::P0WIN) << " game";
	os << (multiGameRunner._gameOutcomes.at(State::Outcome::P0WIN) > 1 ? "s" : "") << "\n";
	os << "P1( " << multiGameRunner.getPlayer1Name() << " ) won: " << multiGameRunner._gameOutcomes.at(State::Outcome::P1WIN) << " game";
	os << (multiGameRunner._gameOutcomes.at(State::Outcome::P1WIN) > 1 ? "s" : "") << "\n";
	os << "Draws: " << multiGameRunner._gameOutcomes.at(State::Outcome::DRAW) << " game";
	os << (multiGameRunner._gameOutcomes.at(State::Outcome::DRAW) > 1 ? "s" : "") << " drawn\n";
	
	return os;
}

AbstractPlayer::Ptr MultiGameRunner::getPlayer0() const 
{
	return _player0;
}

AbstractPlayer::Ptr MultiGameRunner::getPlayer1() const 
{
	return _player1;
}

std::string MultiGameRunner::getPlayer0Name() const 
{
	return _player0->getPreferedName();
}

std::string MultiGameRunner::getPlayer1Name() const 
{
	return _player1->getPreferedName();
}
