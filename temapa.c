#include "temapa.h"
Player* createPlayer(const char* firstName, const char* secondName, int points)
{
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    newPlayer->firstName = (char*)malloc(sizeof(char) * (strlen(firstName) + 1));
    strcpy(newPlayer->firstName, firstName);
    newPlayer->secondName = (char*)malloc(sizeof(char) * (strlen(secondName) + 1));
    strcpy(newPlayer->secondName, secondName);
    newPlayer->points = points;
    return newPlayer;
}

Team* createTeam(const char* teamName)
{
    Team* newTeam = (Team*)malloc(sizeof(Team));
    newTeam->teamName = (char*)malloc(sizeof(char) * (strlen(teamName) + 1));
    strcpy(newTeam->teamName, teamName);
    newTeam->teamPoints = 0;
    newTeam->players = NULL;
    return newTeam;
}

void addPlayerToTeam(Team* team, Player* player)
{
    playerList* newPlayerNode = (playerList*)malloc(sizeof(playerList));
    newPlayerNode->player = *player;
    newPlayerNode->next = team->players;
    team->players = newPlayerNode;
    team->teamPoints += player->points;
}

void addTeam(teamList** head, Team* newTeam, int numPlayers)
{
    teamList* newTeamNode = (teamList*)malloc(sizeof(teamList));
    newTeam->teamPoints =  (float) newTeam->teamPoints / numPlayers;
    newTeamNode->team = *newTeam;
    newTeamNode->next = *head;
    *head = newTeamNode;
}

void printTeamList(teamList* head, FILE* filename)
{
    teamList* current = head;
    while (current != NULL)
    {
        fprintf(filename,"%s\n", current->team.teamName);
        current = current->next;
    }
}

void freePlayerList(playerList* head)
{
    playerList* current = head;
    while (current != NULL)
    {
        playerList* temp = current;
        current = current->next;
        free(temp->player.firstName);
        free(temp->player.secondName);
        free(temp);
    }
}

void freeTeamList(teamList* head)
{
    teamList* current = head;
    while (current != NULL)
    {
        teamList* temp = current;
        current = current->next;
        free(temp->team.teamName);
        freePlayerList(temp->team.players);
        free(temp);
    }
}

void deleteLowestPointTeam(teamList** head)
{
    teamList* minPointsTeam = *head;
    teamList* current = *head;
    teamList* prev = NULL;
    teamList* prevMin = NULL;

    while (current != NULL)
    {
        if (current->team.teamPoints < minPointsTeam->team.teamPoints)
        {
            minPointsTeam = current;
            prevMin = prev;
        }
        prev = current;
        current = current->next;
    }
    if (minPointsTeam == *head)
        *head = (*head)->next;
    else
        prevMin->next = minPointsTeam->next;

    free(minPointsTeam->team.teamName);
    freePlayerList(minPointsTeam->team.players);
    free(minPointsTeam);
}

void readData(teamList** teams, int* numTeams, FILE* file)
{
    fscanf(file, "%d", numTeams);
    int i;
    for (i = 0; i < *numTeams; i++)
    {
        int numPlayers;
        char teamName[100];
        fscanf(file, "%d %[^\n]", &numPlayers, teamName);
        if(teamName[strlen(teamName) - 1] == ' ')
            teamName[strlen(teamName) - 1] = '\0';
        Team* teamData = createTeam(teamName);
        int j;
        for (j = 0; j < numPlayers; j++)
        {
            char firstName[100];
            char secondName[100];
            int points;
            fscanf(file, "%s %s %d", firstName, secondName, &points);
            Player* playerData;
            playerData = createPlayer(firstName, secondName, points);
            addPlayerToTeam(teamData, playerData);
        }

        addTeam(teams, teamData, numPlayers);
    }
}

int nearestPower(int value)
{
    int power = 1;
    while (value > 1)
    {
        value >>= 1;
        power <<= 1;
    }
    return power;
}

teamQueue* createQueue()
{
	teamQueue* q;
	q=(teamQueue*)malloc(sizeof(teamQueue));
	if (q==NULL) return NULL;
	q->front=q->rear=NULL;
	return q;
}

void enQueue(teamQueue** q, Team* v)
{
	teamList* newNode=(teamList*)malloc(sizeof(teamList));
	newNode->team=*v;
	newNode->next=NULL;
	if ((*q)->rear==NULL)
    {
        (*q)->front = newNode;
        (*q)->rear = newNode;
    }
	else
    {
		(*q)->rear->next = newNode;
        (*q)->rear = newNode;
	}
}

Team* deQueue(teamQueue** q)
{
    if ((*q)->front == NULL)
        return NULL;
	teamList* aux = (*q)->front;
	Team* d = &(aux->team);

	(*q)->front=((*q)->front)->next;
	free(aux);
	if ((*q)->front == NULL)
        (*q)->rear = NULL;
	return d;
}

void freeQueue(teamQueue* q)
{
	teamList* aux;
	while (!(q->front==NULL))
    {
		aux=q->front;
		q->front=q->front->next;
		free(aux);
	}
	free(q);
}

teamStack* createStack()
{
    teamStack* stackList = (teamStack*)malloc(sizeof(teamStack));
    stackList->top = NULL;
    return stackList;
}

void push(teamStack** stackList, Team* team1)
{
    teamList* newTeamStack = (teamList*)malloc(sizeof(teamList));
    newTeamStack->team = *team1;
    newTeamStack->next = (*stackList)->top;
    (*stackList)->top = newTeamStack;
}

Team* pop(teamStack** stackList)
{
    if ((*stackList)->top == NULL)
        return NULL;

    teamList* poppedTeamStack = (*stackList)->top;
    Team* poppedTeam = &(poppedTeamStack->team);
    (*stackList)->top = poppedTeamStack->next;
    free(poppedTeamStack);
    return poppedTeam;
}

void freeStack(teamStack* stackList)
{
    while (stackList->top != NULL)
    {
        teamList* current = stackList->top;
        stackList->top = current->next;
        free(current);
    }
    free(stackList);
}

void createMatches(teamList* teams, teamQueue** q)
{
    teamList* current = teams;
    while (current != NULL)
    {
        Team* team1 = &(current->team);
        enQueue(q, team1);
        current = current->next;
    }
}

void printMatches(teamQueue* q, FILE* filename)
{
    teamQueue* currentQ = q;
    teamList* current = currentQ->front;
    while (current != NULL)
    {
        int i;
        fprintf(filename,"%s", current->team.teamName);
        for(i=1;i<=33 - strlen(current->team.teamName);i++)
            fprintf(filename," ");
        fprintf(filename,"-");
        for(i=1;i<=33 - strlen(current->next->team.teamName);i++)
            fprintf(filename," ");
        fprintf(filename,"%s\n", current->next->team.teamName);
        current = current->next->next;
    }
    fprintf(filename,"\n");
}

void printWinners(teamQueue* q, FILE* filename)
{
    teamQueue* currentQ = q;
    teamList* current = currentQ->front;
    while (current != NULL)
    {
        int i;
        fprintf(filename,"%s", current->team.teamName);
        for(i=1;i<=34 - strlen(current->team.teamName);i++)
            fprintf(filename," ");
        fprintf(filename,"-");
        fprintf(filename,"  %.2f\n",current->team.teamPoints);
        current = current->next;
    }

}

void playMatches(teamQueue** q, teamStack** winners, teamStack** losers)
{
    while ((*q)->front != NULL)
    {
        Team* team1 = deQueue(q);
        Team* team2 = deQueue(q);
        if(team1->teamPoints>team2->teamPoints)
        {
            team1->teamPoints+=1;
            push(winners, team1);
            push(losers, team2);
        }
        else
        {
            team2->teamPoints+=1;
            push(winners, team2);
            push(losers, team1);
        }
    }
    freeStack(*losers);
    while((*winners)->top != NULL)
    {
        Team* teamw = pop(winners);
        enQueue(q, teamw);
    }
}

void copyTeams(teamQueue* q, teamList** w)
{
    teamList* current = q->front;
    while (current != NULL)
    {
        Team* team = &(current->team);
        teamList* newNode = (teamList*)malloc(sizeof(teamList));
        newNode->team = *team;
        newNode->next = *w;
        *w = newNode;
        current = current->next;
    }
}

Bst* createBstNode(Team* team)
{
    Bst* newNode = (Bst*)malloc(sizeof(Bst));
    newNode->team = *team;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Bst* insertTeam(Bst* head, Team* team)
{
    if (head == NULL)
        return createBstNode(team);
    if (team->teamPoints > head->team.teamPoints)
    {
        head->left = insertTeam(head->left, team);
    }
    else
    if (team->teamPoints < head->team.teamPoints)
    {
        head->right = insertTeam(head->right, team);
    }
    else
    {
        if (strcmp(team->teamName, head->team.teamName) > 0)
        {
            head->left = insertTeam(head->left, team);
        }
        else
        {
            head->right = insertTeam(head->right, team);
        }
    }
    return head;
}

void printBst(Bst* head, FILE* file)
{
    if (head == NULL) {
        return;
    }

    printBst(head->left, file);
    fprintf(file, "%s", head->team.teamName);
    int i;
    for(i=1;i<=34 - strlen(head->team.teamName);i++)
            fprintf(file," ");
    fprintf(file, "-  %.2f\n", head->team.teamPoints);
    printBst(head->right, file);
}

void freeBst(Bst* head)
{
    if (head == NULL)
    {
        return;
    }
    freeBst(head->left);
    freeBst(head->right);
    free(head);
}

void doBst(teamList* w, FILE* file)
{
    Bst* head = NULL;
    teamList* current = w;
    while (current != NULL)
    {
        head = insertTeam(head, &(current->team));
        current = current->next;
    }
    printBst(head, file);
    freeBst(head);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void doAvl(teamList* w, FILE* file)
{
    Avl* root = NULL;
    teamList* current = w;
    while (current != NULL)
    {
        root = insertAvlTeam(root, &(current->team));
        current = current->next;
    }
    printLevel(root, 0, file);
    freeAvl(root);
}

Avl* createAvlNode(Team* team)
{
    Avl* newNode = (Avl*)malloc(sizeof(Avl));
    newNode->team = *team;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    return newNode;
}

int getHeight(Avl* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(Avl* node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Avl* rotateLeft(Avl* node)
{
    Avl* newRoot = node->right;
    Avl* subtree = newRoot->left;
    newRoot->left = node;
    node->right = subtree;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}

Avl* rotateRight(Avl* node)
{
    Avl* newRoot = node->left;
    Avl* subtree = newRoot->right;
    newRoot->right = node;
    node->left = subtree;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}

Avl* insertAvlTeam(Avl* root, Team* team)
{
    if (root == NULL)
        return createAvlNode(team);

    if (team->teamPoints <= root->team.teamPoints)
        root->left = insertAvlTeam(root->left, team);
    else //if (team->teamPoints > root->team.teamPoints)
        root->right = insertAvlTeam(root->right, team);
   // else
       // return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && team->teamPoints < root->left->team.teamPoints)
        return rotateRight(root);

    if (balance < -1 && team->teamPoints > root->right->team.teamPoints)
        return rotateLeft(root);

    if (balance > 1 && team->teamPoints > root->left->team.teamPoints)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && team->teamPoints < root->right->team.teamPoints)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void printLevel(Avl* root, int currentLevel, FILE* file)
{
    if (root == NULL)
        return;

    if (currentLevel == 2)
        fprintf(file, "%s\n", root->team.teamName);
    printLevel(root->right, currentLevel + 1, file);
    printLevel(root->left, currentLevel + 1, file);

}

void freeAvl(Avl* root)
{
    if (root == NULL)
        return;

    freeAvl(root->left);
    freeAvl(root->right);
    free(root);
}

teamList* sortWinners(teamList* head)
{
    if (head == NULL || head->next == NULL)
        return head;
    teamList* slow = head;
    teamList* fast = head->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    teamList* secondHalf = slow->next;
    slow->next = NULL;
    teamList* sortedFirstHalf = sortWinners(head);
    teamList* sortedSecondHalf = sortWinners(secondHalf);
    teamList* mergedList = NULL;
    teamList* tail = NULL;

    while (sortedFirstHalf != NULL && sortedSecondHalf != NULL)
    {
        if (sortedFirstHalf->team.teamPoints > sortedSecondHalf->team.teamPoints ||
            (sortedFirstHalf->team.teamPoints == sortedSecondHalf->team.teamPoints &&
             strcmp(sortedFirstHalf->team.teamName, sortedSecondHalf->team.teamName) > 0))
        {
            if (mergedList == NULL)
                mergedList = tail = sortedFirstHalf;
            else
            {
                tail->next = sortedFirstHalf;
                tail = tail->next;
            }
            sortedFirstHalf = sortedFirstHalf->next;
        }
        else
        {
            if (mergedList == NULL)
                mergedList = tail = sortedSecondHalf;
            else
            {
                tail->next = sortedSecondHalf;
                tail = tail->next;
            }
            sortedSecondHalf = sortedSecondHalf->next;
        }
    }
    if (sortedFirstHalf != NULL)
        tail->next = sortedFirstHalf;
    else if (sortedSecondHalf != NULL)
        tail->next = sortedSecondHalf;

    return mergedList;
}

void freeWinner(teamList* head)
{
    teamList* current = head;
    while (current != NULL)
    {
        teamList* temp = current;
        current = current->next;
        free(temp);
    }
}
