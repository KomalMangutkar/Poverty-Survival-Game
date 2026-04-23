#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player
{
    int money;
    int food;
    int life;
};

struct Room
{
    char title[50];
    char options[4][50];
};

void status(struct Player p)
{
    printf("\n STATUS  Money:%d  Food:%d  Life:%d\n", p.money, p.food, p.life);
}

int alive(struct Player p)
{
    if (p.money <= 0 || p.food <= 0 || p.life <= 0)
    {
        printf("\n GAME OVER  You couldn't survive poverty.\n");
        return 0;
    }
    return 1;
}

void randomEvent(struct Player *p, int seed)
{
    int r = seed % 3;

    if (r == 0)
    {
        printf("You fell sick! Life -10\n");
        p->life -= 10;
    }
    else if (r == 1)
    {
        printf("You found money! +10\n");
        p->money += 10;
    }
    else
    {
        printf("Someone gave you food! +10\n");
        p->food += 10;
    }
}

struct Player playRoom(struct Player p, struct Room r, int day)
{
    int c;

    printf("\n%s\n", r.title);

    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, r.options[i]);
    }

    printf("Choose: ");
    scanf("%d", &c);

    if (day == 1)
    {
        if (c == 1) { p.money += 15; p.food -= 10; p.life -= 5; }
        else if (c == 2) { p.food += 10; p.life -= 5; }
        else if (c == 3) { p.money += 25; p.life -= 20; }
        else if (c == 4) { p.life -= 15; }
    }
    else if (day == 2)
    {
        if (c == 1) { p.money -= 20; p.life += 15; }
        else if (c == 2) { p.life -= 5; }
        else if (c == 3) { p.life -= 15; }
        else if (c == 4) { p.money -= 10; p.life += 5; }
    }
    else if (day == 3)
    {
        if (c == 1) { p.money += 30; p.life -= 10; }
        else if (c == 2) { p.money += 15; p.life -= 5; }
        else if (c == 3) { p.money += 40; p.life -= 25; }
        else if (c == 4) { p.life += 10; p.food -= 5; }
    }
    else
    {
        printf("Wrong choice!\n");
    }

    randomEvent(&p, c + day);

    status(p);

    return p;
}

int main()
{
    struct Player player = {40, 40, 50};

    struct Room rooms[3] = {
        {
            "DAY 1: HUNGER",
            {"Work hard", "Beg for food", "Steal", "Ignore hunger"}
        },
        {
            "DAY 2: SHELTER",
            {"Rent a room", "Stay in slum", "Sleep on street", "Share room"}
        },
        {
            "DAY 3: INCOME",
            {"Get a job", "Daily wage", "Illegal work", "Take rest"}
        }
    };

    char name[30];

    printf("POVERTY SURVIVAL GAME\n");
    printf("Enter your name: ");
    scanf("%s", name);

    printf("\nWelcome %s! Survive 3 days.\n", name);

    for (int i = 0; i < 3; i++)
    {
        player = playRoom(player, rooms[i], i + 1);

        if (!alive(player))
            return 0;
    }

    if (player.money>40 && player.food>40 && player.life>40)
    {
        printf("\nYOU ESCAPED POVERTY SUCCESSFULLY!\n");
    }
    else
    {
        printf("\nYou survived, but life is still tough.\n");
    }

    printf("SDG 1: NO POVERTY\n");

    return 0;
}
