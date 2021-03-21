#include <stdio.h>

enum drinkOp
{
    WATER,
    ORANGE,
    APPLE,
    SPRITE,
    COLA,
    NUM_DRINKS_EXIT
};

enum coins
{
    SHEKEL,
    SHNEKEL,
    FIVE_SHEKELS,
    TEN_SHEKELS,
    NUM_COINS = 4
};

typedef struct
{
    unsigned int amountLeft;
    unsigned int price;
    char* name;

}  drink;

static const int g_baseDrinks = 10;
static drink g_drinksMachine[NUM_DRINKS_EXIT];
static const unsigned int g_coinsFactor[NUM_COINS] = {1, 2, 5, 10};

void init();
int menu();
unsigned int receivePayment();
void handleChange(unsigned int change);
void handlePayment(unsigned int price);
void runMachine(int option);

int main()
{
    int finish = 0;
    int option = 0;

    init();

    while(!finish)
    {
        option = menu();

        if(option != NUM_DRINKS_EXIT)
        {
            runMachine(option);
        }
        else
        {
            finish = 1;
        }
    }

    printf("Good bye.");

    return 0;
}

void init()
{
    for(int i = 0; i < NUM_DRINKS_EXIT; ++i)
    {
        g_drinksMachine[i].amountLeft = g_baseDrinks;
    }

    g_drinksMachine[WATER].price = 9;
    g_drinksMachine[APPLE].price = g_drinksMachine[ORANGE].price = 8;
    g_drinksMachine[SPRITE].price = g_drinksMachine[COLA].price = 4;

    g_drinksMachine[WATER].name  = "water";
    g_drinksMachine[ORANGE].name = "orange juice";
    g_drinksMachine[APPLE].name  = "apple juice";
    g_drinksMachine[SPRITE].name = "sprite";
    g_drinksMachine[COLA].name   = "cola";
}

int menu()
{
    unsigned int choosenOp = 0;
	int validOp = 0;

    while(!validOp)
    {
        printf("Please choose:\n");
        printf("1. Water.\n2. Orange juice.\n3. Apple juice.\n4. Sprite.\n5. Cola.\n6. exit.\n");
        scanf("%d", &choosenOp);

        --choosenOp; /* convert op to drinks enum */

        if(choosenOp <= NUM_DRINKS_EXIT)
        {
            validOp = 1;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

	return choosenOp;
}

void runMachine(int option)
{
    if(!g_drinksMachine[option].amountLeft)
    {
        printf("sorry no more bottels of %s left.\n", g_drinksMachine[option].name);
        return;
    }

    --g_drinksMachine[option].amountLeft;
    printf("The price is %d nis.\n", g_drinksMachine[option].price);
    
    handlePayment(g_drinksMachine[option].price);
}

void handlePayment(unsigned int price)
{
    int paymentOk = 0;
    unsigned int paid = 0;

    while(!paymentOk)
    {
        printf("To pay please enter 4 numbers.");
        printf("the first number is the amount of 1 nis coins,\n");
        printf("the second is the amount of 2 nis coins, then 5 and 10\n");
        printf("Please enter payment (1, 2, 5, 10):\n");

        paid = receivePayment();

        if(paid < price)
        {
            price -= paid;
            printf("The amount does not suffice! Please enter %d more nis\n", price);
        }
        else
        {
            paymentOk = 1;
        }
    }

    if(paid > price)
    {
        handleChange(paid - price);
    }

    printf("Thank you for buying!\n");
}

unsigned int receivePayment()
{
    unsigned int coins[NUM_COINS] = {0};
    unsigned int sum = 0;

    scanf("%d %d %d %d", &coins[SHEKEL], &coins[SHNEKEL], &coins[FIVE_SHEKELS], &coins[TEN_SHEKELS]);

    for(int i = 0; i < NUM_COINS; ++i)
    {
        sum += coins[i] * g_coinsFactor[i];
    }

    return sum;
}

void handleChange(unsigned int change)
{
    unsigned int changeInCoins[NUM_COINS] = {0};

    printf("your change is: %d nis.\n", change);

    for(int i = NUM_COINS - 1; i >= 0; --i)
    {
        changeInCoins[i] = change / g_coinsFactor[i];
        change %= g_coinsFactor[i];
    }

	printf("You get back (1, 2, 5, 10): %d %d %d %d\n", changeInCoins[SHEKEL], 
                changeInCoins[SHNEKEL], changeInCoins[FIVE_SHEKELS], changeInCoins[TEN_SHEKELS]);
}