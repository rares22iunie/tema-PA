#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <math.h>
typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
}Player;

typedef struct playerList
{
    Player player;
    struct playerList *next;
}playerList;

typedef struct Team
{
    char* teamName;
    float teamPoints;
    playerList* players;
}Team;

typedef struct teamList
{
    Team team;
    struct teamList *next;
}teamList;

typedef struct teamQueue
{
    teamList *front, *rear;
}teamQueue;

typedef struct teamStack
{
    teamList* top;
}teamStack;

typedef struct Bst
{
    Team team;
    struct Bst* right;
    struct Bst* left;
}Bst;

typedef struct Avl
{
    Team team;
    struct Avl* left;
    struct Avl* right;
    int height;
} Avl;

Player* createPlayer(const char* firstName, const char* secondName, int points);
Team* createTeam(const char* teamName);
void addPlayerToTeam(Team* team, Player* player);
void addTeam(teamList** head, Team* newTeam, int numPlayers);
void printTeamList(teamList* head, FILE* filename);
void freePlayerList(playerList* head);
void freeTeamList(teamList* head);
void deleteLowestPointTeam(teamList** head);
void readData(teamList** teams, int* numTeams, FILE* file);
int nearestPower(int value);
teamQueue* createQueue();
void enQueue(teamQueue** q, Team* v);
Team* deQueue(teamQueue** q);
void freeQueue(teamQueue* q);
teamStack* createStack();
void push(teamStack** stackList, Team* team);
Team* pop(teamStack** stackList);
void freeStack(teamStack* stackList);
void createMatches(teamList* teams, teamQueue** q);
void playMatches(teamQueue** q, teamStack** winners, teamStack** losers);
void printMatches(teamQueue* q, FILE* filename);
void printWinners(teamQueue* q, FILE* filename);
void copyTeams(teamQueue* q, teamList** w);
Bst* createBstNode(Team* team);
Bst* insertTeam(Bst* head, Team* team);
void printBst(Bst* head, FILE* file);
void freeBst(Bst* head);
void doBst(teamList* w, FILE* file);
Avl* createAvlNode(Team* team);
int getHeight(Avl* node);
int getBalance(Avl* node);
Avl* rotateLeft(Avl* node);
Avl* rotateRight(Avl* node);
Avl* insertAvlTeam(Avl* root, Team* team);
void printLevel(Avl* root, int level, FILE* file);
void doAvl(teamList* w, FILE* file);
void freeAvl(Avl* root);
int max(int a, int b) ;
teamList* sortWinners(teamList* head);
void freeWinner(teamList* head);
