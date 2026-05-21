#include "output_fill_matrix_spiral.h"
#include "audio.h"
#include "display.h"
#include "main.h"
#include <Arduino.h>

void output_fill_matrix_spiral(bool init);

void output_init_matrix_spiral()
{
    output_fill_matrix_spiral(true);
}

void output_fill_matrix_spiral()
{
    output_fill_matrix_spiral(false);
}

void output_fill_matrix_spiral(bool init)
{
    static uint8_t round = 0;
    static uint8_t mode = mode_fill;
    static uint8_t direction = 0;

    if (init) {
        round = 0;
        mode = mode_fill;
        direction = dir_right;
        x = -1;
        y = 0;
    }

    if (countdown == 0) {
        if (mode == mode_fill) {
            if (x == round && y == round + 1) {
                direction = dir_right;
                playAudio(random(24 + random(24)), HALF);
                round++;
            } else if (x == 7 - round && y == round) {
                direction = dir_up;
            } else if (x == 7 - round && y == 7 - round) {
                direction = dir_left;
            } else if (x == round && y == 7 - round) {
                direction = dir_down;
            }

        } else {
            // clear
            if (x == round && y == round) {
                direction = dir_right;
            } else if (x == 7 - round && y == round) {
                direction = dir_up;
            } else if (x == 7 - round && y == 7 - round) {
                direction = dir_left;
            } else if (x == round - 1 && y == 7 - round) {
                direction = dir_down;
                playAudio(random(24 + random(24)), HALF);
                round--;
            }
        }

        switch (direction) {
        case dir_right:
            x++;
            break; // to the right
        case dir_up:
            y++;
            break; // upwards
        case dir_left:
            x--;
            break; // to the left
        case dir_down:
            y--;
            break; // downwards
        }

        matrixSetPixel(x, y, mode);

        if (mode == mode_fill && x == 3 && y == 4) { // last pixel activ - switch to turn off
            mode = mode_clear;
            direction = dir_right;
            x--;
            y--;
        }

        if (mode == mode_clear && x == 0 && y == 7) { // last pixel clear - refill again
            mode = mode_fill;
            direction = dir_right;
            x = -1;
            y = 0;
        }
        countdown = TIME_20_MS;
    }
}
