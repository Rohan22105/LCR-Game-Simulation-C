#include "game.h"
#include "randi.h"
#include "strings.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Here is an array of player names.  Given a player number i, use the
* player names like this:
*
*   player_name[i]
*
* Following this array declaration is the definition of MAX_PLAYERS.  The
* player number i can be anything from 0 to MAX_PLAYERS - 1.
*/
const char *player_name[] = {

    "Ada Lovelace",
    /*
    * 1815-1852.  Wrote the first algorithm for a computer.
    */

    "Margaret Hamilton",
    /*
    * 1936-.  While in her 20s, lead the team that wrote and tested the
    * Apollo moon program's on-board flight software. Invented the term
    * "software engineering".
    */

    "Katherine Johnson",
    /*
    * 1918-2020.  Mathematician who hand-calculated trajectories for crewed
    * spaceflights.
    */

    "Joy Buolamwini",
    /*
    * ~1989-.  MIT computer scientist who works to challenge racial and
    * gender bias in AI-based decision software.
    */

    "Grace Hopper",
    /*
    * 1906-1992.  Mathematician and computer scientist who made the first
    * machine-independent computer language.
    */

    "Adele Goldberg",
    /*
    * 1945-.  Managed the team at Xerox that developed object-oriented
    * programming and graphical user interfaces.
    */

    "Annie Easley",
    /*
    * 1933-2011.  NASA computer scientist and mathematician who developed
    * algorithms that analyze various power technologies.
    */

    "Jeannette Wing",
    /*
    * 1956-.  Led many research projects as a university professor and as a
    * vice president at Microsoft Research.
    */

    "Mary Kenneth Keller",
    /*
    * 1913-1985.  First person to earn a Ph.D. in computer science in the
    * United States.
    */

    "Megan Smith",
    /*
    * 1964-.  Vice president at Google and 3rd Chief Technology Officer of
    * the United States.
    */

    "Radia Perlman",
    /*
    * 1958-.  Computer programmer and network engineer who invented many
    * network protocols include the Spanning Tree Protocol used by network
    * bridges.
    */
};

/*
* Faces of the die are numbered 0 through 5, and each face has a symbol.
* Create an array of six Symbols that is indexed by the face number.  Then
* you can convert the roll of a die (0-5) into a Symbol by accessing the
* array like this:
*
*    Symbol sym = symbol_of_roll[roll];
*/
const Symbol symbol_of_roll[6] = {
    DOT,
    DOT,
    DOT,
    LEFT,
    CENTER,
    RIGHT,
};

int score[MAX_PLAYERS];

// Purpose: Converts a dice dymbol to the character we print within the given parameters
//Paraemeters: sym — one of DOT, LEFT, CENTER, RIGHT.
// Returns: '.' for DOT, 'L' for LEFT, 'C' for CENTER, 'R' for RIGHT
 
char letter_of_symbol(Symbol sym) {
    switch (sym) {
    case DOT:    return '.';
    case LEFT:   return 'L';
    case CENTER: return 'C';
    case RIGHT:  return 'R';
    }
    return '?';
}

// Purpose: To return the smallest of two integers
//Parameters: a, b (ints to compare)
// Returns: a if a < b, or else returns b


int min(int a, int b) {
    return (a < b) ? a : b;
}

// Purpose: The next dice roll (LCR)
// Parameters: None
// Returns: integer in [0..5]
//Returns:  Call randi() and map with % 6
 

int rand_roll(void) {
    return randi() % 6;  
}
// Purpose:    Find the player to the LEFT within the given parameter 
//Parameter: ( player - current player's index num_players - total players in the game)
// Returns:    the index of the player on the left. (wraps around circle at +1)
 

int left_of(int player, int num_players) {
    return (player + 1) % num_players;   
}

// Purpose: Find the player to the RIGHT within the given parameter
//Parameter: (player - current player's index num_players - total players in the game)
//Returns:    index of the player on the right. (wraps around circle at -1)

int right_of(int player, int num_players) {
    return (player + num_players - 1) % num_players; 
}

// Purpose:    Print each player's chip count to the pot
//Parameters:  (num_players - number of players to print)
//Returns:    Doesn't print anything
 
void print_scores(int num_players) {
    printf(CURRENT_SCORES);
    int sum = 0;
    for (int i = 0; i < num_players; i++) {
        sum += score[i];
        printf(SCORE_ds, score[i], player_name[i]); 
    }
    int pot = 3 * num_players - sum;
    printf(SCORE_ds, pot, "pot");
}

//Purpose:   IF ALIVE,  count how many players still have more than 0 chips. (checks)
//Parameters: players alive - total players
// Returns:   the count of players with positive chip counts 

static int alive_fs(int num_players) {
    int a = 0;
    for (int i = 0; i < num_players; i++) {
        if (score[i] > 0) a++;
    }
    return a;
}

// Purpose: The purpose of this code is to simulate a game of LCR and print out the results
//Parameters: number of players between 3-11
// Returns: Prints turns, score tables, and the final winner
// Block by Block Comments Below

void play_game(unsigned seed, int num_players) {
    randi_seed(seed);

    // everyone starts with 3 chips
    for (int i = 0; i < num_players; i++) {
        score[i] = 3;
    }

    // initial table before any turns
    print_scores(num_players);

    int current = 0; // player 0 starts

    while (alive_fs(num_players) > 1) {
        int dice = min(3, score[current]);

        if (dice == 0) {
            printf("%s has no chips, skipping turn\n", player_name[current]);
        } else {
            // header when the player really rolls
            printf("%s's turn:\n", player_name[current]);

            for (int d = 0; d < dice; d++) {
                int roll = rand_roll();              // 0..5
                Symbol s = symbol_of_roll[roll];     // DOT/LEFT/CENTER/RIGHT
                char letter = letter_of_symbol(s);   // '.'/'L'/'C'/'R'

                printf("    Rolls %c\n", letter);

                // lines for L/R/C when used
                if (s == LEFT) {
                    int L = left_of(current, num_players);
                    printf("        Gives a chip to %s\n", player_name[L]);
                    score[current]--;
                    score[L]++;
                } else if (s == RIGHT) {
                    int R = right_of(current, num_players);
                    printf("        Gives a chip to %s\n", player_name[R]);
                    score[current]--;
                    score[R]++;
                } else if (s == CENTER) {
                    printf("        Puts a chip in the pot\n");
                    score[current]--;
                } else {
                    
                }
            }

            
            print_scores(num_players);
        }

        // next player going left
        current = left_of(current, num_players);
    }

    
    printf("Now only one player has chips\n");

    // Announce the Winner
    for (int i = 0; i < num_players; i++) {
        if (score[i] > 0) {
            printf("%s won!\n", player_name[i]);
            break;
        }
    }
}