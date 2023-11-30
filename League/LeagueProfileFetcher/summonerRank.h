#ifndef SUMMONERRANK_H
#define SUMMONERRANK_H

#include "./CustomException.h"

class SummonerRank{
    private:
        QString tier, rank;
        int leaguePoints;
        int wins, losses;
        QString queue_type;

    public:
        SummonerRank();

        // Process the passed in data
        void process_rank_data(QJsonObject);
        void reset_rank_data();

        // Getters and setters
        QString get_tier() const;
        QString get_rank() const;
        int get_league_points() const;
        int get_wins() const;
        int get_losses() const;
        QString get_queue_type() const;

        void set_tier(const QString &);
        void set_rank(const QString &);
        void set_league_points(int);
        void set_wins(int);
        void set_losses(int);
        void set_queue_type(const QString &);
};

#endif // SUMMONERRANK_H
