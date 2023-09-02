#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

void append(struct node **q, int num)
{
    struct node *temp, *r;
    if (*q == NULL)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        temp->data = num;
        temp->link = NULL;
        *q = temp;
    }
    else
    {
        temp = *q;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        r = (struct node *)malloc(sizeof(struct node));
        r->data = num;
        r->link = r;
    }
}

char print(int);

void show(int frame[9])
{
    printf(" %c | %c | %c\n", print(frame[0]), print(frame[1]), print(frame[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", print(frame[3]), print(frame[4]), print(frame[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", print(frame[6]), print(frame[7]), print(frame[8]));
}
int win(int frame[9])
{
    int wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    int i;
    for (i = 0; i < 8; ++i)
    {
        if (frame[wins[i][0]] != 0 &&
            frame[wins[i][0]] == frame[wins[i][1]] &&
            frame[wins[i][0]] == frame[wins[i][2]])
            return frame[wins[i][2]];
    }
    return 0;
}

int algo(int frame[9], int player)
{
    int winner = win(frame);
    if (winner != 0)
        return winner * player;

    int move = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; ++i)
    {
        if (frame[i] == 0)
        {
            frame[i] = player;
            int temp = -algo(frame, player * -1);
            if (temp > score)
            {
                score = temp;
                move = i;
            }
            frame[i] = 0;
        }
    }
    if (move == -1)
        return 0;
    return score;
}

void Computer_chance(int frame[9])
{
    int move = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; ++i)
    {
        if (frame[i] == 0)
        {
            frame[i] = 1;
            int temp = -algo(frame, -1);
            frame[i] = 0;
            if (temp > score)
            {
                score = temp;
                move = i;
            }
        }
    }
    frame[move] = 1;
}

void User_chance(int frame[9])
{
    int move = 0;
    do
    {
        printf("\nInput move ([1..9]): ");
        scanf("%d", &move);
        move--;
        if(move>=9 || move<0){
            printf("\nInvalid choice. Try again.");
        }
        else if (frame[move] != 0)
        {
            printf("\nThe place is already filled. Try again.");
        }
        printf("\n");
    } while (move>=9 || move<0 || frame[move] != 0);
    frame[move] = -1;
}

int main()
{
    char x;
    struct node *p;
    p = NULL;
    do
    {
        int frame[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        printf("Computer: O    You: X\n\n");
        printf(" 1 | 2 | 3\n");
        printf("---+---+---\n");
        printf(" 4 | 5 | 6\n");
        printf("---+---+---\n");
        printf(" 7 | 8 | 9\n\n");
        printf("Would you like to play first?(Y/N) ");
        fflush(stdin);
        char play;
        scanf("%c", &play);
        fflush(stdin);
        printf("\n");
        int player = 0;
        if (play == 'y' || play == 'Y')
            player = 1;

        else
            player = 2;
        int chance = 0;
        for (chance = 0; chance < 9 && win(frame) == 0; ++chance)
        {
            if ((chance + player) % 2 == 0)
                Computer_chance(frame);
            else
            {
                show(frame);
                User_chance(frame);
            }
        }

        int y;
        switch (win(frame))
        {
        case 0:
            printf("It's a draw.\n");
            y = 0;
            break;
        case 1:
            show(frame);
            printf("You lose.\n");
            y = -1;
            break;
        case -1:
            printf("You win.\n");
            y = 1;
            break;
        }
        append(&p, y);
        printf("Do you want to play again?(Y/N)");
        scanf("%s", &x);
        printf("\n");
    } while (x == 'y' || x == 'Y');

    struct node *temp = p;
    int c = 1;
    while (temp != NULL)
    {
        if (temp->data == -1)
        {
            printf("Game %d. You won.\n", c++);
        }
        else if (temp->data == 0)
        {
            printf("Game %d. You lost.\n", c++);
        }
        else
        {
            printf("Game %d. It was draw\n", c++);
        }
        temp = temp->link;
    }
}

char print(int i)
{
    switch (i)
    {
    case -1:
        return 'X';
    case 0:
        return ' ';
    case 1:
        return 'O';
    }
}
