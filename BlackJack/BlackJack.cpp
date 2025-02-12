#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int new_card();
void show_result(int player, int dealer, int *money, int bet);

int main()
{
	setlocale(LC_ALL,"portuguese");
    srand(time(NULL));    
    int player = 0, dealer = 0, card;
    int money = 100, bet;
    char choice;

    printf("Bem-vindo ao Blackjack!\nVoc� tem %d cr�ditos.\n", money);

    while (money > 0) {
        printf("\nDigite sua aposta: ");
        scanf("%d", &bet);

        if (bet > money || bet <= 0) {
            printf("Aposta inv�lida!\n");
            continue;
        }

        player = new_card() + new_card();
        dealer = new_card();
        printf("\nSuas cartas somam: %d\n", player);
        printf("Dealer tem: %d\n", dealer);

        while (player < 21) {
            printf("Deseja comprar outra carta? (s/n): ");
            scanf(" %c", &choice);
            if (choice == 'n' || choice == 'N')
                break;
            card = new_card();
            player += card;
            printf("Nova carta: %d | Total: %d\n", card, player);
        }

        while (dealer < 17) {
            dealer += new_card();
        }

        show_result(player, dealer, &money, bet);
    }

    printf("Voc� ficou sem cr�ditos! Jogo encerrado.\n");
    return 0;
}

int new_card()
{
    return rand() % 10 + 1;
}

void show_result(int player, int dealer, int *money, int bet)
{
    printf("\n--- Resultado ---\n");
    printf("Seu total: %d\n", player);
    printf("Total do Dealer: %d\n", dealer);

    if (player > 21) {
        printf("Voc� estourou! Perdeu a aposta.\n");
        *money -= bet;
    } else if (dealer > 21 || player > dealer) {
        printf("Voc� venceu! Ganhou %d cr�ditos.\n", bet);
        *money += bet;
    } else if (player == dealer) {
        printf("Empate! Sua aposta foi devolvida.\n");
    } else {
        printf("Dealer venceu! Voc� perdeu a aposta.\n");
        *money -= bet;
    }

    printf("Cr�ditos restantes: %d\n", *money);
}

