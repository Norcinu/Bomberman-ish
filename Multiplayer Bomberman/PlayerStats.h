#ifndef PLAYER_STATS_H
#define PLAYER_STATS_H

// good place for observer / boost::signals?
struct PlayerStatsTracker_t
{
    int number_of_kills;
    int score;
    int bombs_fired;
};

struct GameStatsTracker_t
{
    bool game_running;
    int players_remaining;
};

#endif
