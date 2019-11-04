#include <stdio.h>
struct player
{
    char letter;
    int age;
    double avg;
    
};
typedef struct player player_t;
void printPlayer(player_t p);
player_t scanPlayer(void);
int	compAB(player_t playerA, player_t playerB);

int main()
{
    player_t  p1, p2;
    p1 = scanPlayer();
    p2 = scanPlayer();
    compAB(p1, p2);
    return 0;
}

player_t scanPlayer(void)
{
    player_t playerA;
    printf("Enter first letter of player name>");
    scanf("%c", &playerA.letter);
    printf("Enter the age>");
    scanf("%d", &playerA.age);
    printf("Enter the batting average>");
    scanf("%lf", &playerA.avg);
    return playerA;
}

int	compAB(player_t playerA, player_t playerB)
{
    int result, diffage;
    double diffavg;
    diffavg = fabs(playerA.avg-playerB.avg);
    diffage = fabs(playerA.age-playerB.age);
    if(playerA.avg > (playerB.avg+10))
    {
        return 1;
    }
    else if(playerB.avg>(playerA.avg+10))
    {
        return -1;
    }
    else if(playerA.age<(playerB.age - 15) && diffAvg <= 10)
    {
        return 1;
    }
    else if(playerA.age>(playerB.age - 15) && diffAvg >= 10)
    {
        return -1;
    }
    else if(diffavg<=10 && diffavg <=15)
    {
        return 0;
    }
    
    
    


void printPlayer(player_t p)
{
    printf("%c %d %lf", p.letter, p.age, p.avg);
}


/*Binary is more secure as opposed to ASCI as the data is encoded.*/ 
