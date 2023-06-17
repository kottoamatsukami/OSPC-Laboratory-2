#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// ----< CONFIG >----
#define PORT 9002
// ------------------


// ----< OTHER >----
#define ARROW ">>> "
#define True 1
#define False 0
#define PRINT_DELAY 10000
// -----------------


// ----< FUNCS >----
void greeting()
{
  puts("__________________________________________________________________________________");usleep(PRINT_DELAY);
    puts("|   ________  ________  ________                 ________  ________  ________    |");usleep(PRINT_DELAY);
    puts("|  |\\   ____\\|\\   __  \\|\\   ____\\               |\\   __  \\|\\   __  \\|\\   __  \\   |");usleep(PRINT_DELAY);
    puts("|  \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\___|_  ____________\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\  |");usleep(PRINT_DELAY);
    puts("|   \\ \\  \\  __\\ \\   ____\\ \\_____  \\|\\____________\\ \\   __  \\ \\   ____\\ \\   ____\\ |");usleep(PRINT_DELAY);
    puts("|    \\ \\  \\|\\  \\ \\  \\___|\\|____|\\  \\|____________|\\ \\  \\ \\  \\ \\  \\___|\\ \\  \\___| |");usleep(PRINT_DELAY);
    puts("|     \\ \\_______\\ \\__\\     ____\\_\\  \\              \\ \\__\\ \\__\\ \\__\\    \\ \\__\\    |");usleep(PRINT_DELAY);
    puts("|      \\|_______|\\|__|    |\\_________\\              \\|__|\\|__|\\|__|     \\|__|    |");usleep(PRINT_DELAY);
    puts("|                         \\|_________|                                           |");usleep(PRINT_DELAY);
    puts("|________________________________________________________________________________|");usleep(PRINT_DELAY);
}

void put_arrow()
{
    printf(ARROW);
}

void main_menu()
{
	puts("|————————————————————————————————————————————————————————————————————————————————————————————————————|");usleep(PRINT_DELAY);
	puts("| Command manager:                                                                                   |");usleep(PRINT_DELAY);
    puts("| > launch <id>       --- launch the sattelite with <id>              | example: launch Johnny       |");usleep(PRINT_DELAY);
    puts("| > destroy <id>      --- destroy the sattelite with <id>             | example: destroy Johnny      |");usleep(PRINT_DELAY);
    puts("| > change_orbit <id> --- change the orbit of the sattelite with <id> | example: change orbit Billy  |");usleep(PRINT_DELAY);
    puts("| > get_coords <id>   --- get coords of the sattelite with <id>       | example: get coords Sputnik1 |");usleep(PRINT_DELAY);
    puts("| > exit              --- exit the application                                                       |");usleep(PRINT_DELAY);
	puts("|————————————————————————————————————————————————————————————————————————————————————————————————————|");usleep(PRINT_DELAY);
}

void launch_submenu()
{
	puts("Enter ID of new satellite or use <exit> to back in the main menu.");
}

int get_choice(int min, int max)
{
    char choice[16];
    fgets(choice, 16, stdin);
    
    int n = atoi(choice);
    if (!(n >= min && n <= max))
    {
        puts("Unexpected argument");
        return -1;
    }
    return n;
}


// ----------------
