#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "Enemy.h"

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

char *my_readline(void)             //// READLINE
{
  char    *buff;
  ssize_t size;

  buff = malloc(sizeof(*buff) * (50 + 1));
  if (buff == NULL)
    return NULL;
  size = read(0, buff, 50);
  if (size > 1) {
    buff[size - 1] = '\0';
    return buff;
  }
  free(buff);
  return buff;
}
////////////////

void my_putchar(char c)                //// PUTSTR (Printf)
{
  write(1, &c, 1);
}

void my_putstr(const char *str)
{
    int len = 0;
    while (str[len])
    {
        my_putchar(str[len]);
        len++;
    }
}
//////////////////////
void	my_putnbr(int nb)                   ////// Print Nbr
{
    int modulo = 0;
    
    if (nb <= 9 && nb >= 0)
        my_putchar(nb + '0');
    if (nb < 0) {
        my_putchar('-');
        nb = nb * (- 1);
        if (nb <= 9 && nb >=0)
            my_putnbr(nb);
    } if (nb > 9) {
        modulo = nb % 10;
        my_putnbr(nb / 10);
        my_putchar(modulo + '0');
        }
}
////////////////////////////////////////////////////////////////////////////
int my_strcmp(const char *s1, const char *s2) {
    int i = 0;
    int r;
    for (; s1[i] || s2[i] != '\0'; i++) {

        if (s1[i] != s2[i])  {
            r = s1[i] - s2[i];
            return r;
        }
    }
    return r = s1[i] - s2[i];
}

void my_putstr();
////////////////////////////////////////////////////////////////////////////
typedef struct Struct_Player               ///// STRUCTURE Player
{
    char *name;
    int pv;
    int stg;
    int heal;

}Player_;

typedef struct Struct_Mob             
{
    char *name;
    int pv;
    int stg;

}Mob_;
////////////////////////////////////////////////////////////////////////////////////////////////
int main()                          /////// MAIN
{
    Player_ *player1 = malloc(sizeof(Player_));
    Mob_ *mob1 = malloc(sizeof(Mob_));

    my_putstr("Please enter your name :\n\n");
    player1->name = my_readline();
    my_putstr("Good luck, ");
    my_putstr(player1->name);
    my_putstr("\n\n");
    sleep(3);
/////////////////////////////////////
    my_putstr("What if you could change the destiny of hundreds of thousands of people ? \n\n");
    sleep(5);
    my_putstr("Would you take the risk to do whatever it takes ? \n\n");
    sleep(5);
    my_putstr("You have the chance to change one of these three situations by fighting it : \n\n"); 
    sleep(5);
    my_putstr("Global Warming...");
    sleep(4);
    my_putstr("Wars all around the wolrd...");
    sleep(4);
    my_putstr("and...");
    sleep(5);
    my_putstr("Latifi's crash in Abu Dhabi");
    sleep(5);
    my_putstr("\n\nNow let the fun begin!");
    sleep(4);

    time_t t;

    srand((unsigned) time(&t));
    int r = rand() % 3;

    mob1->name = Enemy_name[r] ;
    mob1->pv = Enemy_hp[r];
    mob1->stg = Enemy_stg[r];

    player1->pv = 100;
    player1->stg = 15;
    player1->heal = 20;
/////////////////////////////////////////////////////////////////////////////////:
    int i = 0;
    char *command;

    my_putstr("\n\n= = = = = = = = = ");
    my_putstr(mob1->name);
    my_putstr(" appears ! = = = = = = = = = \n\n"); 

    for(i = 0; mob1->pv > 0 && player1->pv > 0; i++) {
        sleep(2);
        if (i % 2 == 0) {                //tour du player                 
            do { 
                my_putstr("              >>>>> action <<<<< \n");     
                my_putstr("\n    ~ [A] Attack ~        ~ [H] Heal ~\n");
                my_putstr("\n    ~ [L] Leave ~        \n");
                command = my_readline();
            } while ((my_strcmp(command,"A") != 0) && (my_strcmp(command,"H") != 0) && (my_strcmp(command,"L")));  
            if (my_strcmp(command,"A") == 0) {                      
                my_putstr(player1->name);
                my_putstr(" hit ");
                my_putstr(mob1->name); 
                my_putstr("            ");
                my_putstr(mob1->name);
                my_putstr("'s HP : ");
                my_putnbr(mob1->pv -= player1->stg); 
                my_putstr("\n\n"); 
            } if(my_strcmp(command,"H") == 0) {
                my_putstr(player1->name); 
                my_putstr(" healed ");
                my_putnbr(player1->heal);
                my_putstr(" HP                  ");       
                my_putstr(player1->name);
                my_putstr("'s HP : ");
                my_putnbr(player1->pv += player1->heal);
                my_putstr("\n\n");  
            } if(my_strcmp(command,"L") == 0) {
                my_putstr("you can't leave, ");
                my_putstr(mob1->name);
                my_putstr(" is blocking the way ");
            }
            sleep(1);
        } else {                            //tour mob                                            
            my_putstr(mob1->name); 
            my_putstr(" attacked, you lost ");
            my_putnbr(mob1->stg);
            my_putstr(" HP                  ");       
            my_putstr(player1->name);
            my_putstr("'s HP : ");
            my_putnbr(player1->pv -= mob1->stg);
            my_putstr("\n\n");
        }
        my_putstr("\n ======================================= \n\n");
    }
/////////////                    
    if (player1->pv <= 0)
        my_putstr(" you just lost \n\n");
    else 
        my_putstr(" you just stopped ");
        my_putstr(mob1->name);
        my_putstr("                     xp +20 !\n\n");
    return(0);
}