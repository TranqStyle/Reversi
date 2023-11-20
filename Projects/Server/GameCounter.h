#ifndef GAMECOUNTER_H
#define GAMECOUNTER_H

#include "State.h"
#include "GameHandler.h"

#include <map>



class GameCounter {
public:
	GameCounter(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1, const size_t& gameSample);
	
	friend std::ostream& operator<<(std::ostream& os, const GameCounter& gameCounter);

	void play();

	size_t getP0Win() const;
	size_t getP1Win() const;
	size_t getDraw() const;
	size_t getGamesPlayed() const;
	size_t getGameSample() const;
	AbstractPlayer::Ptr getPlayer0() const;
	AbstractPlayer::Ptr getPlayer1() const;
	std::string getPlayer0Name() const;
	std::string getPlayer1Name() const;
	
private:
	AbstractPlayer::Ptr _player0;
	AbstractPlayer::Ptr _player1;
	std::map<std::string, size_t> gameStats;
	
	struct GameStats {
		size_t _gameSample;
		size_t _gamesPlayed;
		size_t _p0Win;
		size_t _p1Win;
		size_t _draw;
	};
};

#endif // GAMECOUNTER_H