#include "MultiGameRunner.h"

MultiGameRunner::MultiGameRunner(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1, size_t totalGamesToBePlayed)
	: _player0{ player0 }, _player1{ player1 }, _totalGamesToBePlayed{ totalGamesToBePlayed }
{
}


void MultiGameRunner::play() const
{
	GameHandler gameHandler{};

	std::map<State::Outcome, size_t> gameOutcomes{ {State::Outcome::P0WIN, 0}, {State::Outcome::P1WIN, 0}, {State::Outcome::DRAW, 0} };

	for (size_t i{ 0 }; i < _totalGamesToBePlayed; ++i)
	{
		gameHandler.init(_player0, _player1);

		State::Outcome outcome = gameHandler.play();

		++gameOutcomes[outcome];
	}

	announceResults(gameOutcomes);
}

void MultiGameRunner::announceResults(const std::map<State::Outcome, size_t>& gameOutcomes) const 
{	
	std::cout << "Games Played: " << _totalGamesToBePlayed << "\n";
	std::cout << "P0( " << _player0->getPreferedName() << " ) won: " << gameOutcomes.at(State::Outcome::P0WIN) << " game\n";
	std::cout << "P1( " << _player1->getPreferedName() << " ) won: " << gameOutcomes.at(State::Outcome::P1WIN) << " game\n";
	std::cout << "Draws: " << gameOutcomes.at(State::Outcome::DRAW) << " game\n";
}	
