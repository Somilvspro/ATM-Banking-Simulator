
#include <stdio.h>
#include <string.h>

#define MAX_TRANSACTIONS 10

struct Transaction
{
    char type[20];
    float amount;
};

void checkBalance(float balance);
void deposit(float *balance, struct Transaction history[], int *count);
void withdraw(float *balance, struct Transaction history[], int *count);
void miniStatement(struct Transaction history[], int count);
void changePin(int *pin);

int main()
{
    int pin = 1234;
    int enteredPin;
    int attempts = 0;
    int choice;
    int loggedIn = 0;

    float balance = 5000.0;

    struct Transaction history[MAX_TRANSACTIONS];
    int count = 0;

    printf("\n====================================\n");
    printf("       WELCOME TO C ATM BANK\n");
    printf("====================================\n");

    /* PIN Verification */

    while (attempts < 3)
    {
        printf("\nEnter your 4-digit ATM PIN: ");

        if (scanf("%d", &enteredPin) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        if (enteredPin == pin)
        {
            printf("\nLogin Successful!\n");
            loggedIn = 1;
            break;
        }
        else
        {
            attempts++;
            printf("Incorrect PIN! Attempts left: %d\n",
                   3 - attempts);
        }
    }

    if (loggedIn == 0)
    {
        printf("\nYour account is temporarily locked.\n");
        return 0;
    }

    /* ATM Main Menu */

    do
    {
        printf("\n====================================\n");
        printf("              ATM MENU\n");
        printf("====================================\n");
        printf("1. Balance Enquiry\n");
        printf("2. Cash Withdrawal\n");
        printf("3. Cash Deposit\n");
        printf("4. Mini Statement\n");
        printf("5. Change PIN\n");
        printf("6. Exit\n");
        printf("====================================\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                checkBalance(balance);
                break;

            case 2:
                withdraw(&balance, history, &count);
                break;

            case 3:
                deposit(&balance, history, &count);
                break;

            case 4:
                miniStatement(history, count);
                break;

            case 5:
                changePin(&pin);
                break;

            case 6:
                printf("\nThank you for using C ATM Bank!\n");
                printf("Please collect your card.\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}

/* Balance Enquiry */

void checkBalance(float balance)
{
    printf("\nYour current balance is: Rs. %.2f\n", balance);
}

/* Cash Withdrawal */

void withdraw(float *balance,
              struct Transaction history[], int *count)
{
    float amount;

    printf("\nEnter withdrawal amount: Rs. ");

    if (scanf("%f", &amount) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    if (amount <= 0)
    {
        printf("Please enter a valid amount.\n");
    }
    else if (amount > *balance)
    {
        printf("Insufficient balance!\n");
    }
    else
    {
        *balance = *balance - amount;

        printf("\nWithdrawal successful!\n");
        printf("Remaining balance: Rs. %.2f\n", *balance);

        if (*count < MAX_TRANSACTIONS)
        {
            strcpy(history[*count].type, "Withdrawal");
            history[*count].amount = amount;
            (*count)++;
        }
        else
        {
            printf("Transaction history is full.\n");
        }
    }
}

/* Cash Deposit */

void deposit(float *balance,
             struct Transaction history[], int *count)
{
    float amount;

    printf("\nEnter deposit amount: Rs. ");

    if (scanf("%f", &amount) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    if (amount <= 0)
    {
        printf("Please enter a valid amount.\n");
    }
    else
    {
        *balance = *balance + amount;

        printf("\nAmount deposited successfully!\n");
        printf("Updated balance: Rs. %.2f\n", *balance);

        if (*count < MAX_TRANSACTIONS)
        {
            strcpy(history[*count].type, "Deposit");
            history[*count].amount = amount;
            (*count)++;
        }
        else
        {
            printf("Transaction history is full.\n");
        }
    }
}

/* Mini Statement */

void miniStatement(struct Transaction history[], int count)
{
    int i;

    printf("\n========== MINI STATEMENT ==========\n");

    if (count == 0)
    {
        printf("No transactions available.\n");
    }
    else
    {
        for (i = 0; i < count; i++)
        {
            printf("%d. %s : Rs. %.2f\n",
                   i + 1,
                   history[i].type,
                   history[i].amount);
        }
    }

    printf("====================================\n");
}

/* Change PIN */

void changePin(int *pin)
{
    int oldPin;
    int newPin;

    printf("\nEnter your current PIN: ");

    if (scanf("%d", &oldPin) != 1)
    {
        printf("Invalid input!\n");
        return;
    }

    if (oldPin == *pin)
    {
        printf("Enter your new 4-digit PIN: ");

        if (scanf("%d", &newPin) != 1)
        {
            printf("Invalid input!\n");
            return;
        }

        if (newPin >= 1000 && newPin <= 9999 &&
            newPin != *pin)
        {
            *pin = newPin;
            printf("\nPIN changed successfully!\n");
        }
        else
        {
            printf("Enter a different 4-digit PIN.\n");
        }
    }
    else
    {
        printf("Incorrect current PIN!\n");
    }
}

