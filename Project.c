#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "players.txt"
 
typedef struct {
  char name[64];
  int balance;
  int gain;
} Player;
 
void LoadPlayerData(const char* file_name, Player *p);
Player GetPlayerData(const char* name, Player *p);
void PushPlayerData(const char* file_name, Player *p);
void HandleChoice(int choice);
void PrintTopFive(Player *p, int type);
void DisplayMenu(void);
void PlayGame(void);
 
Player players[10];
FILE *fp;
 
int main(void) {
  LoadPlayerData(FILE_NAME, players);
  DisplayMenu();
  PushPlayerData(FILE_NAME, players);
  return 0;
}
 
void PlayGame(void){
    char name[64];
    int bal = 0;
    printf("Enter your name: ");
    scanf("%s", &name);
    Player p = GetPlayerData(name, players);
    //srand(time(NULL));
    getchar();
   
    while(1){
        printf("Press Enter to Roll the dice.\n");
        getchar();
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int diceSum = dice1+dice2;
        printf("The values of the dices are %d and %d whose sum is %d.\n", dice1, dice2, diceSum);
        if(diceSum == 7 || diceSum == 11){
            p.balance = p.balance+10;
            printf("You win the game. Your current balance is %d.\n", p.balance);
            char again;
            printf("Play another game? y/n ");
            scanf("%s", &again);
            if(again == 'y'){
                getchar();
                continue;
            }else{
                break;
            }
        }else if(diceSum == 2 || diceSum == 3 || diceSum == 12){
            p.balance = p.balance-1;
            printf("The house wins.\n Your current stake is %d.\n", p.balance);
            char again;
            printf("Play another game? y/n ");
            scanf("%s", &again);
            if(again == 'y'){
                getchar();
                continue;
            }else{
                getchar();
                break;
            }
        }else{
            int point = diceSum;
            while(1){
                printf("Press Enter to Roll the dice.\n");
                getchar();
                int dice1 = rand() % 6 + 1;
                int dice2 = rand() % 6 + 1;
                int diceSum = dice1+dice2;
                printf("The values of the dices are %d and %d whose sum is %d.\n", dice1, dice2, diceSum);
                if(diceSum == point){
                    p.balance = p.balance+10;
                    printf("You win the game. Your current balance is %d.\n", p.balance);
                    char again;
                    printf("Play another game? y/n ");
                    scanf("%s", &again);
                    if(again == 'y'){
                        getchar();
                        continue;
                    }else{
                        break;
                    }
                }else if(diceSum == 7){
                    p.balance = p.balance-1;
                    printf("The house wins.\n Your current stake is %d.\n", p.balance);
                    char again;
                    printf("Play another game? y/n ");
                    scanf("%s", &again);
                    if(again == 'y'){
                        getchar();
                        continue;
                    }else{
                        break;
                    }
                }else{
                    continue;
                }
            }
            break;
        }
       
    }
   
    getchar();
    DisplayMenu();
   
}
 
void LoadPlayerData(const char* file_name, Player *p) {
  fp = fopen(file_name, "r");
  int i = 0;
  for (;;) {
    if (fscanf(fp, "%s\t%d\t%d", p[i].name, &p[i].balance, &p[i].gain) != 3) {
      if (feof(fp)) {
        fclose(fp);
        break;
      }
    }
    i++;
  }
}
 
void PushPlayerData(const char* file_name, Player *p) {
  fp = fopen(file_name, "w");
  int i=0;
  for (;;) {
      fprintf(fp, "%s\t%d\t%d\n", p[i].name, p[i].balance, p[i].gain);
      if (feof(fp)) {
        fclose(fp);
        break;
      }
  }
}
 
void HandleChoice(int choice) {
  switch(choice) {
    case 0: {
      char name[64];
      int bal = 0;
      printf("Enter your name: ");
      scanf("%s", &name);
      Player p = GetPlayerData(name, players);
      printf("Set your balance to: ");
      scanf("%d", &bal);
      p.balance = bal;
      getchar();
      break;
    }
    case 1:
      PlayGame();
      break;
    case 2:
      PrintTopFive(players, 0);
      break;
    case 3:
      PrintTopFive(players, 1);
      break;
    case 4:
      exit(1);
      break;
    default:
      puts("[Err] An Unexpected error occured... Exiting.");
      exit(1);
  }
}
 
Player GetPlayerData(const char* name, Player *p) {
  int i = 0;
  for (;;) {
    if (strcmp(name, p[i].name) == 0) {
      return p[i];
    }
    i++;
  }
}
 
void PrintTopFive(Player *p, int type) {
  Player top[10];
  for (;;) {
 
  }
}
 
void DisplayMenu(void) {
  char keyPressed;
 
  for (;;) {
    // Print menu to the screen
    printf("0) Top up your balance.\n"
    "1) Play Game.\n"
    "2) Top 5 Players by Balance\n"
    "3) Top 5 Winners By What They Won\n"
    "4) Exit.\n"
    "Please type a number from 0 to 4 to select menu item:\n");
 
    keyPressed = getchar(); // Get user input (0-4)
 
    // Validate the input from the user...
    if( keyPressed == '4' ) {
      HandleChoice(4);
    } else if ( keyPressed < '0' || keyPressed > '4' ) {
      printf("\n[Err] Invalid Input... Try again.\n");
      continue; // Unknown input... we can safely loop back around
    } else {
    // Print the corresponding menu item
      switch(keyPressed) {
        case '0':
          HandleChoice(0);
          break;
        case '1':
          HandleChoice(1);
          break;
        case '2':
          HandleChoice(2);
          break;
        case '3':
          HandleChoice(3);
          break;
        default:
          puts("[Err] An un-expected error occured.");
          exit(1);
      }
    }
  }
}