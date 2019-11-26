#ifndef G2_PLAYER_H
#define G2_PLAYER_H

class g2_player
{
public:
    g2_player();

    /**
     * @brief card[i] is the number of the card at index i in this g2_player's hand if known to the player, it's -1 otherwise
     */
    int card[4];

    /**
     * @brief memoryx[i] holds -1 if this g2_player doesn't know the card at index i of opponentx;
     */
    int memory1[4], memory2[4];
};

#endif // G2_PLAYER_H
