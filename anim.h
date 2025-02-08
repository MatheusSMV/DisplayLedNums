#ifndef ANIM_H
#define ANIM_H

#define NUM_PIXELS 25 // A matriz de Led 5x5

bool led_buffer[NUM_PIXELS]; //Armazinar o Número de Pixels
volatile int indice_animacao = 0; //Inicia animação apresentando o 0.


void animacao_0() //Animação para o número 0.
{
    bool animacao[5][5] = {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0}
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_1() //Animação para o número 1.
{
    bool animacao[5][5] = {
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };
    for (int k = 0; k < 5; k++) {
        for (int l = 0; l < 5; l++) {
            led_buffer[k * 5 + l] = animacao[k][l];
        }
    }
}

void animacao_2() //Animação para o número 2.
{
    bool animacao[5][5] = {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0}
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_3() //Animação para o número 3.
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},  
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 0, 0}, 
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_4() //Animação para o número 4.
{
    bool animacao[5][5] = {
    {0, 1, 0, 0, 0},   
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 0, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_5() //Animação para o número 5.
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},   
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 0, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_6() //Animação para o número 6.
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 0, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_7() //Animação para o número 7.
{
    bool animacao[5][5] = {
     {0, 1, 0, 0, 0},   
     {0, 0, 0, 1, 0}, 
     {1, 1, 1, 0, 0}, 
     {1, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_8() //Animação para o número 8.
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},   
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_9() //Animação para o número 9.
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},  
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
 }
}
}

void selecionar_animacao() { //Selecionar A animação
  switch (indice_animacao) {
      case 0: animacao_0(); break;
      case 1: animacao_1(); break;
      case 2: animacao_2(); break;
      case 3: animacao_3(); break;
      case 4: animacao_4(); break;
      case 5: animacao_5(); break;
      case 6: animacao_6(); break;
      case 7: animacao_7(); break;
      case 8: animacao_8(); break;
      case 9: animacao_9(); break;
  }
}

#endif