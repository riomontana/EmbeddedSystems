/*
 * Lab4_Magnus.c
 *
 * Created: 2015-11-27 16:02:27
 *  Author: staff
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>			//rand
#include "lcd/lcd.h"
#include "numkey/numkey.h"
#include "delay/delay.h"
#include "hmi/hmi.h"
#include "guess_nr.h"

// for storage of pressed key
char key;
// for generation of variable string
char str[17];

int main(void)

{
	uint16_t rnd_nr;
	// initialize HMI (LCD and numeric keyboard)
	hmi_init();
	// generate seed for the pseudo-random number generator
		srand(1);															//random_seed();
	// show start screen for the game
	output_msg("WELCOME!", "LET'S PLAY...", 3);
	// play game
	while (1) {
		// generate a random number
		rnd_nr = rand()  % 101;														//random_get_nr(100) + 1;
		// play a round...
		play_guess_nr(rnd_nr);
	}
}