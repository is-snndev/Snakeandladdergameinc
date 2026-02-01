#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define boardsize 100
#define maxplayers 2

int snakes[][2] = { {17, 7}, {54, 34}, {62, 19}, {98, 79} };
int ladders[][2] = { {3, 38}, {24, 33}, {42, 93}, {72, 84} };

int playerpos[maxplayers];/*2 slots*/

//dice roll
int rolldice(){
    return (rand()%6)+1;/*+1 cause 0 to 5 will become 1to 6*/
}

//animate dice
void animatediceroll(int dice){
    printf("Rolling");
    fflush(stdout);
    for(int i=0; i<3; i++){
        Sleep(400);
        printf(".");
        fflush(stdout);
    }
    printf("\nResult: %d\n", dice);
}

//animate player movement
void animatemove(int oldpos, int newpos, int player){
    printf("Player %d moving:", player+1);
    for(int pos=oldpos+1; pos<=newpos; pos++){
    printf("%d.. ", pos);
    fflush(stdout);
    Sleep(300);
}
    printf("\n");
}

//check snake and ladder
int checksnakeorladder(int pos){
    int snakeCount = sizeof(snakes) / sizeof(snakes[0]); 
    int ladderCount = sizeof(ladders) / sizeof(ladders[0]);
    for(int i=0;i<snakeCount;i++){
        if(pos==snakes[i][0]) return snakes[i][1];}
    for(int i=0;i<ladderCount;i++){
        if(pos==ladders[i][0]) return ladders[i][1];
    }  
    return pos;      
}

//check winner
int iswinner(int pos){
    return pos==boardsize;
}

void playturn(int player){
    printf("\n--- It's Player %d's turn ---\n", player + 1); 
    printf("Press Enter to roll the dice or type 'q' to quit...\n"); 
    char input[10];
    fgets(input, sizeof(input), stdin); // waits for user to press Enter
    if (input[0] == 'q' || input[0] == 'Q') {
        printf("Player %d chose to quit. Goodbye!\n", player+1); 
        exit(0); // end program 
        }

    int dice=rolldice();
    animatediceroll(dice);
    //printf("Player %d rolled a %d\n",player+1,dice);

    int newpos=playerpos[player] + dice;
    if(newpos>boardsize){
        printf("Player %d stays at %d (overshoot)\n", player+1, playerpos[player]);
        return;
    }

    animatemove(playerpos[player],newpos,player);

    int adjustedPos = checksnakeorladder(newpos); 
    if (adjustedPos < newpos) 
    { printf("Oops! Snake! Player %d slides down to %d \n", player + 1, adjustedPos); }
    else if (adjustedPos > newpos) 
    { printf("Yay! Ladder! Player %d climbs up to %d \n", player + 1, adjustedPos); } 
    
    playerpos[player] = adjustedPos; 
    printf("Player %d is now at %d\n", player + 1, playerpos[player]);
    
    printf("Current positions: Player 1 = %d, Player 2 = %d\n", playerpos[0], playerpos[1]);

    if(iswinner(playerpos[player])){
        printf("Player %d wins\n", player+1);
        exit(0);
    }

}
int main(){
    srand(time(0));
    for(int i=0;i<maxplayers;i++){
        playerpos[i]=0;}

    printf("Welcome to Snake and Ladder!\n");

    int currentplayer=0;
    while(1){
        playturn(currentplayer);
        currentplayer=(currentplayer+1)%maxplayers;
    }
    return 0;

}







