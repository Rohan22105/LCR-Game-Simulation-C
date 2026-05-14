#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Symbol;

/*
* Faces of the die are numbered 0 through 5, and each face has a symbol.
* Create an array of six Symbols that is indexed by the face number.  Then
* you can convert the roll of a die (0-5) into a Symbol by accessing the
* array like this:
*
*    Symbol sym = symbol_of_roll[roll];
*/
extern const Symbol symbol_of_roll[6];

char letter_of_symbol(Symbol sym);
int min(int a, int b);
int rand_roll(void);
int left_of(int player, int num_players);
int right_of(int player, int num_players);
void print_scores(int num_players);
void play_game(unsigned seed, int num_players);
