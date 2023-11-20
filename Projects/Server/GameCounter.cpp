#include "GameCounter.h"

GameCounter::GameCounter(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1, const size_t& gameSample = 1)
	: _player0{ player0 }, _player1{ player1 }
{
	gameStats["p0win"];
	gameStats["p1win"];
	gameStats["draw"];
	gameStats["gamesPlayed"];
	gameStats["gameSample"] = gameSample;
}


void GameCounter::play() {


	GameHandler gameHandler{};
	size_t gameSample = gameStats["gameSample"];
	AbstractPlayer::Ptr player0 = getPlayer0();
	AbstractPlayer::Ptr player1 = getPlayer1();

	for (size_t i{ 0 }; i < gameSample; ++i) {
		
		gameHandler.init(player0, player1);
		

		State::Outcome result = gameHandler.play();
		++gameStats["gamesPlayed"];

		switch (result) 
		{
			case State::Outcome::P0WIN:
				++gameStats["p0win"];
				break;
			case State::Outcome::P1WIN:
				++gameStats["p1win"];
				break;
			case State::Outcome::DRAW:
				++gameStats["draw"];
				break;
			default:
				throw std::runtime_error{ "Invalid outcome for game result." };
		}
		
	}
}

std::ostream& operator<<(std::ostream& os, const GameCounter& gameCounter) 
{	
	os << "\n";
	os << "Games played: " << gameCounter.getGamesPlayed() << " / " << gameCounter.getGameSample() << "\n";
	os << "P0( " << gameCounter.getPlayer0Name() << " ) won: " << gameCounter.getP0Win() << " game";
	os << (gameCounter.getP0Win() > 1 ? "s" : "") << "\n";
	os << "P1( " << gameCounter.getPlayer1Name() << " ) won: " << gameCounter.getP1Win() << " game";
	os << (gameCounter.getP1Win() > 1 ? "s" : "") << "\n";
	os << "Draws: " << gameCounter.getDraw() << " game";
	os << (gameCounter.getDraw() > 1 ? "s" : "") << " drawn\n";
	
	return os;
}

size_t GameCounter::getP0Win() const{
	return gameStats.find("p0win")->second;
}

size_t GameCounter::getP1Win() const {
	return gameStats.find("p1win")->second;
}

size_t GameCounter::getDraw() const {
	return gameStats.find("draw")->second;
}

size_t GameCounter::getGamesPlayed() const {
	return gameStats.find("gamesPlayed")->second;
}

size_t GameCounter::getGameSample() const {
	return gameStats.find("gameSample")->second;
}

AbstractPlayer::Ptr GameCounter::getPlayer0() const {
	return _player0;
}

AbstractPlayer::Ptr GameCounter::getPlayer1() const {
	return _player1;
}

std::string GameCounter::getPlayer0Name() const {
	return _player0->getPreferedName();
}

std::string GameCounter::getPlayer1Name() const {
	return _player1->getPreferedName();
}
