#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Card{
    int valueCard;
    int suitCard; // 0 para espadas, 1 para paus, 2 para copas, 3 para ouro.
    struct Card *next;
    struct Card *prev;
}Card;

void enqueue(Card **head, Card **tail, int cardValue, int cardSuit);
void initCards(Card **head, Card **tail);
int currentLengthCards(Card *head);
void deliverCards(Card **sourceHead, Card **sourceTail,  Card **destinationHead, Card **destinationTail, int i);
void insertionSort(Card *head); 
void displayCards(Card *head, int i);
void concatenateQueues(Card **head_01, Card **tail_01, Card **head_02, Card **tail_02); 
int compare(Card *hand);
bool isRoyalStraightFlush(Card *hand);
bool isStraightFlush(Card *hand);
bool isFourOfAKind(Card *hand);
bool isFullHouse(Card *hand);
bool isFlush(Card *hand);
bool isStraight(Card *hand);
bool isThreeOfAKind(Card *hand);
bool isTwoPair(Card *hand);
bool isOnePair(Card *hand);
void removeAtAnyPoint(Card **head, Card **tail, int i);

int main(){

    Card *headPlayer = NULL, *headCPU = NULL, *headDealer = NULL, *headCheap = NULL;
    Card *tailPlayer = NULL, *tailCPU = NULL, *tailDealer = NULL, *tailCheap = NULL;
    
    int cardValue, cardSuit;
    int fichasPlayer = 100;
    int fichasCPU = 100; 
    int fichasNaAposta = 0;


    
    while(1){
        printf("Bem Vindo ao Poker!\n");
        initCards(&headCheap, &tailCheap);

        //selecionando cartas jogadores    
        deliverCards(&headCheap, &tailCheap, &headPlayer, &tailPlayer, 2);

        //selecionando cartas para o computador 
        deliverCards(&headCheap, &tailCheap, &headCPU, &tailCPU, 2);

        //mostrando as cartas do jogador
        displayCards(headPlayer, 0);//cartas jogador

        
        //perguntar ao jogador se ele vai entrar no jogo; custo = 5 fichas;
        printf("Vai entrar na partida (Custo 5 fichas)? [0] para não [1] para sim\n ");
        int keepOnGame;
        scanf("%d", &keepOnGame);

        if (keepOnGame == 0){
            int sairDoJogo;
            printf("Deseja sair do jogo? [0] para não [1] para sim\n");
            scanf("%d", &sairDoJogo);
            if(sairDoJogo = 0 ){
                continue;
            }else{
                break;
            }
        }

        fichasPlayer = fichasPlayer -5;
        fichasCPU = fichasCPU -5;


        //reduzir 5 fichas no montante do jogador e da cpu;
        
        //selecionando as 3 cartas inicias da mesa
        deliverCards(&headCheap, &tailCheap, &headDealer, &tailDealer, 3);
        
        //mostrando as cartas da mesa
        displayCards(headDealer, 1);


        //rodada de aposta
        printf("%d \n Jogador, qual sua aposta?");
        int aposta1;
        scanf("%d", &aposta1);

        if(aposta1>fichasPlayer);
            printf("Você não pode apostar mais do que tem!!!");
            int apostaCorreta;
            scanf("%d", &apostaCorreta);
            aposta1 = apostaCorreta;
            
        fichasPlayer = fichasPlayer - aposta1;

        if(aposta1>fichasCPU){
            printf("CPU não tem a quantidade de fichas suficientes... Você o superou! \n Saindo do jogo.");
            break;
        }

        fichasCPU = fichasCPU - aposta1;
        
        
        //selecionando as 2 cartas finais do jogo
        deliverCards(&headCheap, &tailCheap, &headDealer, &tailDealer, 2);

        //mostrando as 3 cartas iniciais + 2 finais
        displayCards(headDealer, 1);

        //rodada de aposta final
        printf("%d \n Jogador, qual sua aposta?");
        int aposta2;
        scanf("%d", &aposta2);

        if(aposta1>fichasPlayer);
            printf("Você não pode apostar mais do que tem!!!");
            int apostaCorreta;
            scanf("%d", &apostaCorreta);
            aposta2 = apostaCorreta;
            
        fichasPlayer = fichasPlayer - aposta2;

        if(aposta1>fichasCPU){
            printf("CPU não tem a quantidade de fichas suficientes... Você o superou! \n Saindo do jogo.");
            break;
        }
        
        int handPlayer = compare(headPlayer);
        int handCPU = compare(headCPU);

        if(handPlayer>handCPU){
            fichasPlayer = fichasPlayer + aposta1 + aposta2;
            fichasCPU = fichasCPU - aposta1 - aposta2;
            printf("Parabéns! Você ganhou!");
        }else if (handCPU>handPlayer){
            fichasPlayer = fichasPlayer - aposta1 - aposta2;
            fichasCPU = fichasCPU + aposta1 + aposta2;
            printf("Você perdeu. ");
        }else{

        }

        int leaveGame;
        printf("Deseja continuar no jogo? \n[0] para continuar \t|\t [1] para sair\n");
        if(leaveGame==1){
            break;
        }
        
    }
    printf("\nFim do Jogo. Obrigado por jogar.\n");
    return 0;
}

void enqueue(Card **head, Card **tail, int cardValue, int cardSuit){
    /* enfileira as cartas na mão de cada jogador, mesa ou cpu;
    */
   Card* newcard = (Card *)malloc(sizeof(Card));

   if(newcard != NULL){

        newcard->suitCard = cardSuit;
        newcard->valueCard = cardValue;

        if(*head == NULL){
            newcard->prev = NULL;
            *head = newcard;
            *tail = newcard;
        }else{
            (*tail)->next = newcard;
            newcard->prev = *tail;
            *tail = newcard;
        }
   }
}

void initCards(Card **head, Card **tail){ //criação baralho 

    for(int i = 0; i < 4; i++){

        for(int j = 1; j < 14; j++){

            enqueue(head, tail, j, i);

        }
    }
}

int currentLengthCards(Card *head){

    Card *current = head;

    int length = 0;

    while(current != NULL){
        length++;
        current=current->next;
    }

    return length;
}

void deliverCards(Card **sourceHead, Card **sourceTail,  Card **destinationHead, Card **destinationTail, int i){
    // for de 1 a qtd de cartas a ser distribuida (i)

    // outro for pra escolher qual carta vai ser distribuida usando o rand, mas lembrar de percorrer até o retorno de currentLength

    // se estiver na ultima execução, enqueue a carta 

    for(int j = 0; j<i; j++){
        int currentLength = currentLengthCards(*sourceHead);
        int cardNumber = rand() % currentLength-1;

        Card *current = *sourceHead;

        for(int a = 0; a <= cardNumber; a++){

            if(a == cardNumber){
                enqueue(destinationHead, destinationTail, current->valueCard, current->suitCard);
                removeAtAnyPoint(sourceHead, sourceTail, a);
            }

            current=current->next;

        }
    }
}

void insertionSort(Card *head) {
    
    if (head == NULL || head->next == NULL) {
        return; 
    }
    
    Card *sorted = NULL; 

    while (head != NULL) {
        Card *current = head;
        head = head->next;

        if (sorted == NULL || current->valueCard <= sorted->valueCard) {
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            
            sorted = current;
                
        } else {
            Card *temp = sorted;
            while (temp->next != NULL && temp->next->valueCard < current->valueCard) {
                temp = temp->next;
            }
        
            current->next = temp->next;
        
            if (temp->next != NULL) {
                temp->next->prev = current;
            }
        
            temp->next = current;
            current->prev = temp;
        }
    }    
    head = sorted;
}



void displayCards(Card *head, int i){
    char flag[23];
    
    if(i==0){
        strcpy("Suas cartas são", flag);
    }
    else{
        strcpy("As cartas da mesa são", flag);
    } 
    
    printf("%s: ", flag); 
    
    while(head != NULL){
        if (head->suitCard = 0){ //naipe de espadas
            if(head->valueCard == 1){//Ás de Espadas
                printf("A|Espadas");
            }
            else if(head->valueCard == 11){//Valete de Espadas
                printf("J|Espadas");
            }
            else if(head->valueCard == 12){//Rainha de Espadas
                printf("Q|Espadas");
            }
            else if(head->valueCard == 13){//Rei de Espadas
                printf("K|Espadas");
            }
            else{// valor 2<=x<=10 de espadas
                printf("%d|Espadas", head->valueCard); 
            }
        }else if (head->suitCard == 1){ //naipe de paus
            if(head->valueCard == 1){//Ás de Paus
                printf("A|Paus");
            }
            else if(head->valueCard == 11){//Valete de Paus
                printf("J|Paus");
            }
            else if(head->valueCard == 12){//Rainha de Paus
                printf("Q|Paus");
            }
            else if(head->valueCard == 13){//Rei de Paus
                printf("K|Paus");
            }
            else{// valor 2<=x<=10 de Paus
                printf("%d|Paus", head->valueCard);
            }
        }else if (head->suitCard == 2){ //naipe de Copas
            if(head->valueCard == 1){//Ás de Copas
                printf("A|Copas");
            }
            else if(head->valueCard == 11){//Valete de Copas
                printf("J|Copas");
            }
            else if(head->valueCard == 12){//Rainha de Copas
                printf("Q|Copas");
            }
            else if(head->valueCard == 13){//Rei de Copas
                printf("K|Copas");
            }
            else{// valor 2<=x<=10 de Copas
                printf("%d|Copas", head->valueCard);
            }
        }else if (head->suitCard == 3){ //naipe de Ouro
            if(head->valueCard == 1){//Ás de Ouro
                printf("A|Ouro");
            }
            else if(head->valueCard == 11){//Valete de Ouro
                printf("J|Ouro");
            }
            else if(head->valueCard == 12){//Rainha de Ouro
                printf("Q|Ouro");
            }
            else if(head->valueCard == 13){//Rei de Ouro
                printf("K|Ouro");
            }
            else{// valor 2<=x<=10 de Ouro
                printf("%d|Ouro", head->valueCard);
            }
        }
        head = head->next; 
    }
}

// função p concatenar a fila da mãos dos jogadores + fila das cartas da mesa
void concatenateQueues(Card **head_01, Card **tail_01, Card **head_02, Card **tail_02) {
    if (*tail_01 != NULL && *head_02 != NULL) {
        (*tail_01)->next = *head_02;
        if (*head_02 != NULL) {
            (*head_02)->prev = *tail_01;
        }
        *tail_01 = *tail_02;
        *head_02 = *head_01;
        *head_01 = NULL;
    }
}

void removeAtAnyPoint(Card **head, Card **tail, int i) {
    if (*head == NULL) {
        return;
    }

    struct Card* current = *head;
    int currentPosition = 0;

    while (current != NULL && currentPosition < i) {
        current = current->next;
        currentPosition++;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        *tail = current->prev;
    }
    
    free(current);
}


//função para comparar as cartas
int compare(Card *hand) {
    if (isRoyalStraightFlush(hand)) {
        return 10;
    } else if (isStraightFlush(hand)) {
        return 9;
    } else if (isFourOfAKind(hand)) {
        return 8;
    } else if (isFullHouse(hand)) {
        return 7;
    } else if (isFlush(hand)) {
        return 6;
    } else if (isStraight(hand)) {
        return 5;
    } else if (isThreeOfAKind(hand)) {
        return 4;
    } else if (isTwoPair(hand)) {
        return 3;
    } else if (isOnePair(hand)) {
        return 2;
    } else {
        return 1; // High Card
    }
}

bool isRoyalStraightFlush(Card *hand) {
    // Verifica se é um Royal Straight Flush (sequência de 10 a Ás do mesmo naipe)
    int count = 0;
    int expectedValue = 10;
    int expectedSuit = hand->suitCard;

    while (hand != NULL) {
        if (hand->valueCard == expectedValue && hand->suitCard == expectedSuit) {
            count++;
            expectedValue++;
        } else if (hand->valueCard == 1 && hand->suitCard == expectedSuit) {
            // Ás
            count++;
            expectedValue = 2; // Continua a sequência após o Ás
        } else {
            count = 0;
            expectedValue = 10;
        }

        if (count == 5) {
            return true; // Encontrou uma sequência de 10 a Ás do mesmo naipe
        }

        hand = hand->next;
    }

    return false;
}

bool isStraightFlush(Card *hand) {
    // Verifica se é um Straight Flush (sequência de cartas do mesmo naipe)
    int count = 0;
    int expectedValue = hand->valueCard;
    int expectedSuit = hand->suitCard;

    while (hand != NULL) {
        if (hand->valueCard == expectedValue && hand->suitCard == expectedSuit) {
            count++;
            expectedValue++;
        } else {
            count = 0;
            expectedValue = hand->valueCard + 1; // Reinicia a sequência
        }

        if (count == 5) {
            return true; // Encontrou uma sequência do mesmo naipe
        }

        hand = hand->next;
    }

    return false;
}

bool isFourOfAKind(Card *hand) {
    int count;
    int currentValue;

    // Percorre cada valor de carta possível
    for (int value = 1; value <= 13; value++) {
        count = 0;
        currentValue = value;

        // Percorre a mão contando o número de cartas com o mesmo valor
        while (hand != NULL) {
            if (hand->valueCard == currentValue) {
                count++;
            }

            if (count == 4) {
                return true; // Encontrou quatro cartas do mesmo valor
            }

            hand = hand->next;
        }
    }

    return false; // Não encontrou quatro cartas do mesmo valor
}

bool isFullHouse(Card *hand) {
    int countTrinca = 0;
    int countPar = 0;
    int currentValue;

    // Percorre cada valor de carta possível
    for (int value = 1; value <= 13; value++) {
        currentValue = value;

        // Percorre a mão contando o número de cartas com o mesmo valor
        while (hand != NULL) {
            if (hand->valueCard == currentValue) {
                if (countTrinca == 0) {
                    countTrinca++;
                } else if (countPar == 0) {
                    countPar++;
                } else {
                    countTrinca = 1;
                    countPar = 0;
                }
            }

            hand = hand->next;
        }

        if (countTrinca == 1 && countPar == 1) {
            return true; // Encontrou um full house
        }
    }

    return false; // Não encontrou full house
}

bool isFlush(Card *hand) {
    int countSpades = 0;
    int countHearts = 0;
    int countDiamonds = 0;
    int countClubs = 0;
    while (hand != NULL) {
        switch (hand->suitCard) {
            case 0: // Espadas
                countSpades++;
                break;
            case 1: // Paus
                countClubs++;
                break;
            case 2: // Copas
                countHearts++;
                break;
            case 3: // Ouro
                countDiamonds++;
                break;
        }

        hand = hand->next;
    }

    return countSpades >= 5 || countClubs >= 5 || countHearts >= 5 || countDiamonds >= 5;
}


bool isStraight(Card *head) {
    // Ordenar as cartas antes de verificar a sequência
    insertionSort(head);

    int count = 0;
    int expectedValue = head->valueCard;

    while (head != NULL) {
        if (head->valueCard == expectedValue) {
            count++;
            expectedValue++;
        } else {
            count = 0;
            expectedValue = head->valueCard + 1; // Reinicia a sequência
        }

        if (count == 5) {
            return true; // Encontrou uma sequência
        }

        head = head->next;
    }

    return false;
}

bool isThreeOfAKind(Card *hand) {
    int count;
    int currentValue;

    // Percorre cada valor de carta possível
    for (int value = 1; value <= 13; value++) {
        count = 0;
        currentValue = value;

        // Percorre a mão contando o número de cartas com o mesmo valor
        while (hand != NULL) {
            if (hand->valueCard == currentValue) {
                count++;
            }

            if (count == 3) {
                return true; // Encontrou três cartas do mesmo valor
            }

            hand = hand->next;
        }
    }

    return false; // Não encontrou três cartas do mesmo valor
}

bool isTwoPair(Card *hand) {
    int countPairs = 0;
    int firstPairValue = 0;
    int secondPairValue = 0;

    // Percorre cada valor de carta possível
    for (int value = 1; value <= 13; value++) {
        int count = 0;

        // Percorre a mão contando o número de cartas com o mesmo valor
        while (hand != NULL) {
            if (hand->valueCard == value) {
                count++;
            }

            hand = hand->next;
        }

        if (count == 2) {
            // Encontrou um par
            countPairs++;

            if (countPairs == 1) {
                firstPairValue = value;
            } else if (countPairs == 2) {
                secondPairValue = value;
            }
        }
    }

    return countPairs == 2 && firstPairValue != secondPairValue;
}

bool isOnePair(Card *hand) {
    int countPairs = 0;

    // Percorre cada valor de carta possível
    for (int value = 1; value <= 13; value++) {
        int count = 0;

        // Percorre a mão contando o número de cartas com o mesmo valor
        while (hand != NULL) {
            if (hand->valueCard == value) {
                count++;
            }

            hand = hand->next;
        }

        if (count == 2) {
            // Encontrou um par
            countPairs++;
        }
    }

    return countPairs == 1;
}