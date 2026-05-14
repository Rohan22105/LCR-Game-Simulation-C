#include "game.h"
#include "strings.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num_players = 3;
    printf(PROMPT_NUM_PLAYERS);
    int scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > MAX_PLAYERS) {
        printf(ERROR_INVALID_PLAYERS);
        num_players = 3;
    }

    unsigned seed = 4823;
    printf(PROMPT_SEED);
    scanf_result = scanf("%u", &seed);

    if (scanf_result < 1 || seed < 0 || seed > 999999) {
        printf(ERROR_INVALID_SEED);
        seed = 4823;
    }

    play_game(seed, num_players);

    return 0;
}
