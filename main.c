#include "temapa.h"
int main(int argc, char* argv[])
{
    FILE *f;
    FILE *h;
    FILE *g;
    if((f = fopen(argv[1],"r")) == NULL)
    //if((f = fopen("c.in","r")) == NULL)
    {
        puts("Error opening file: c.in\n");
        exit(1);
    }
    if ((h = fopen(argv[2],"r")) == NULL)
    //if ((h = fopen("d.in","r")) == NULL)
    {
        printf("Error opening file: d.in\n");
        exit(1);
    }
    if((g = fopen(argv[3],"w")) == NULL)
    //if((g = fopen("r.out","w")) == NULL)
    {
        puts("Error opening file: r.out\n");
        exit(1);
    }
    int c[10],i;
    for(i = 1; i <= 5; i++)
    {
        fscanf(f, "%d", &c[i]);
    }
    if(c[1] == 1)
    {
        teamList* head = NULL;
        int numTeams = 0;
        readData(&head,&numTeams, h);
        if(c[2] == 1)
        {
            int num = nearestPower(numTeams);
            for(i = 1;i <= numTeams - num;i++)
                deleteLowestPointTeam(&head);
            numTeams = num;
        }
        printTeamList(head,g);
        if(c[3] == 1)
        {
            teamList* winner8 = NULL;
            fprintf(g, "\n");
            teamQueue* matchQueue = createQueue();
            teamStack* winnersStack = createStack();
            teamStack* losersStack = createStack();
            createMatches(head, &matchQueue);
            int round = 0;
            while(numTeams > 1)
            {
                round++;
                fprintf(g, "--- ROUND NO:%d\n",round);
                printMatches(matchQueue, g);
                teamQueue* currentQ = matchQueue;
                teamList* current = currentQ->front;
                playMatches(&matchQueue, &winnersStack, &losersStack);
                fprintf(g, "WINNERS OF ROUND NO:%d\n",round);
                printWinners(matchQueue, g);
                numTeams /= 2;
                if(numTeams > 1)
                    fprintf(g,"\n");
                if(numTeams == 8)
                {
                    copyTeams(matchQueue, &winner8);
                }
            }
            freeQueue(matchQueue);
            freeStack(winnersStack);
            freeStack(losersStack);
            if(c[4] == 1)
            {
                fprintf(g,"\n");
                fprintf(g,"TOP 8 TEAMS:\n");
                doBst(winner8, g);
            }
            if(c[5] == 1)
            {
                winner8 = sortWinners(winner8);
                fprintf(g,"\n");
                fprintf(g,"THE LEVEL 2 TEAMS ARE: \n");
                doAvl(winner8, g);
            }
            freeWinner(winner8);
        }
        freeTeamList(head);
    }
    fclose(f);
    fclose(g);
    return 0;
}
