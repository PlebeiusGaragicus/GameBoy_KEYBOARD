#include <stdint.h>
#include <stdio.h>
#include <rand.h>
// #include <types.h>  // for fixed type

#include <gb/gb.h>
// #include <gb/cgb.h>
// #include <gb/drawing.h>


void audio_init() {
    // This enables Sound
    // these registers must be in this specific order!

    // is 1000 0000 in binary and turns on sound
    NR52_REG = 0x80; 
    // sets the volume for both left and right channel just set to max 0x77
    NR50_REG = 0x77;
    // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
    NR51_REG = 0xFF;
}


// https://stackoverflow.com/questions/66105001/how-can-you-get-a-random-number-on-gbdk
void seed_prng()
{
    // printf("Build: %d", BUILD);
    printf("--------------------");
    printf("|                  |");
    printf("|    Retro  Boy    |");
    printf("|                  |");
    printf("--------------------");
    printf("\n\n\n");
    printf("    PRESS START!");
    printf("\n\n\n\n\n");
    printf("  Compiled on:\n\n");
    printf("%s", VERSION);

    waitpad(J_START);
    boop();

    uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);

    printf("\nLucky Number: %d", seed);
    // performantdelay(10);
    // clear_screen();
}


void boop() {
    NR10_REG=0X00;
    NR11_REG=0X81;
    NR12_REG=0X43;
    NR13_REG=0X73;
    NR14_REG=0X86;
}


void main() {
    // https://www.youtube.com/watch?v=nziu1O_cj1w&list=PLrW43fNmjaQVmjvIj3Ho3rzW46GEw14F9&index=5
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    audio_init();

    seed_prng();

    uint8_t key;

    while(TRUE) {

        key = joypad();

        if (key & J_START) {
            boop();
        }

        vsync();
    }
}
