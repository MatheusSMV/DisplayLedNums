#include "hardware/i2c.h" //Biblioteca para controlar o barramento I2C no Raspberry Pi Pico.
#include "inc/ssd1306.h" //Biblioteca para controle do display OLED SSD1306, incluindo renderização de texto.
#include "inc/font.h" //Biblioteca onde está o nosso alfabeto.
#include <stdio.h> //Biblioteca padrão C.
#include "pico/stdlib.h" //Biblioteca das funções básicas do Raspberry Pi Pico, como inicialização e controle de GPIOs.
#include "hardware/pio.h" //Biblioteca das funções para manipulação do PIO (Programmable I/O) para controlar a matriz de LEDs WS2812.
#include "hardware/clocks.h" //Biblioteca das funções para trabalhar com temporizadores.
#include "hardware/timer.h" //Biblioteca das funções para trabalhar com controle de relógios.
#include "ws2812.pio.h" //Biblioteca das funções para controle da matriz de LEDs WS2812.
#include "anim.h" //Biblioteca onde está as nossas animações.


//Definição de pinos
#define I2C_PORT i2c1 //Definição das portas I2C.
#define I2C_SDA 14 //Definição das portas I2C.
#define I2C_SCL 15 //Definição das portas I2C.
#define endereco 0x3C //Endereço do display no barramento I2C.
#define IS_RGBW false //Apenas o RGB sem LED Branco.
#define WS2812_PIN 7 //A Matriz de LED GPIO 7.
#define DEBOUNCE_MS 200 //Tempo para evitar múltiplas leituras.
#define Led_G 11 //Definindo o pino 11 do led verde.
#define Led_B 12 //Definindo o pino 12 do led azul.
#define botao_a 5 //Definindo o botao a no pino 5.
#define botao_b 6 //Definindo o botao b no pino 6.

//Variáveis globais
uint8_t led_r = 50; //Potência do nosso led vermelho da matriz de leds.
uint8_t led_g = 0; //Verde desligado.
uint8_t led_b = 0; //Azul desligado


int led_green_state = 0; //0 = desligado, 1 = ligado Valor do led Verde.
int led_blue_state = 0; //0 = desligado, 1 = ligado Valor do led Azul.

volatile int display_botao_a = 0; //Variáveis voláteis que controlam a exibição da imagem no display OLED.
volatile int display_botao_b = 0; //Variáveis voláteis que controlam a exibição da imagem no display OLED.


//Função que envia um valor de cor para o pino de controle da matriz de LEDs WS2812.
static inline void put_pixel(uint32_t pixel_grb) {
  pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

//Função que converte valores RGB em um valor de 32 bits no formato GRB.
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

//Funções de Interrupção para os botões A e B.
void gpio_irq_handler(uint gpio, uint32_t events)
{
    static absolute_time_t ultimo_tempo_a = 0; //Inicia em 0 - não pressionado.
    static absolute_time_t ultimo_tempo_b = 0; //Inicia em 0 - não pressionado.

    if (gpio == botao_a) {
        //Botão A (Liga/desliga o LED verde).
        if (absolute_time_diff_us(ultimo_tempo_a, get_absolute_time()) > DEBOUNCE_MS * 1000) { //Lembrando do Debounce - Evitar leituras sucessivas.
            //Alterna o estado do LED verde.
            led_green_state = !led_green_state;  //Alterna entre 0 e 1.
            if (led_green_state) {
                gpio_put(Led_G, 1);  //Liga o LED verde.
                display_botao_a = 1; //Altera o valor no display. -- Variável que controla o display.
            } else {
                gpio_put(Led_G, 0);  //Desliga o LED verde.
                display_botao_a = 0; //Altera o valor no display. -- Variável que controla o display.

            }
            printf("Botão A pressionado (GPIO %d). LED verde %s\n", gpio, led_green_state ? "ligado" : "desligado"); //Mostrando o estado do led no serial monitor (UART).
            printf("Estado do Led verde = %d\n", display_botao_a); //Conferindo o valor da variável que controla o display.
            ultimo_tempo_a = get_absolute_time();
        }
    } 
    else if (gpio == botao_b) {
        //Botão B (Liga/desliga o LED azul).
        if (absolute_time_diff_us(ultimo_tempo_b, get_absolute_time()) > DEBOUNCE_MS * 1000) {//Lembrando do Debounce - Evitar leituras sucessivas.
            //Alterna o estado do LED azul.
            led_blue_state = !led_blue_state;  //Alterna entre 0 e 1.
            if (led_blue_state) {
                gpio_put(Led_B, 1);  //Liga o LED azul.
                display_botao_b = 1; //Altera o valor no display. -- Variável que controla o display.
            } else {
                gpio_put(Led_B, 0);  //Desliga o LED azul
                display_botao_b = 0; //Altera o valor no display. -- Variável que controla o display.
            }
            printf("Botão B pressionado (GPIO %d). LED azul %s\n", gpio, led_blue_state ? "ligado" : "desligado"); //Mostrando o estado do led no serial monitor (UART).
            printf("Estado do Led Azul = %d\n", display_botao_b); //Conferindo o valor da variável que controla o display.
            ultimo_tempo_b = get_absolute_time();
        }
    }
}

//Função para configurar os botões com interrupções.
void configurar_botao(uint pin, gpio_irq_callback_t handler) {
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_IN);
  gpio_pull_up(pin); //Configura os botões com pull-up.
  gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, true, handler); //Interrupção na borda de descida.
}


//Função para configurar as cores dos leds conforme a leitura e o setado nas variáveis globais.
void set_one_led(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t color = urgb_u32(r, g, b);
  for (int i = 0; i < NUM_PIXELS; i++) {
      put_pixel(led_buffer[i] ? color : 0);
  }
}

int main() {
  stdio_init_all(); //Inicializando serial.
  PIO pio = pio0; //Definindo o PIO 0 para controlar a matriz de leds.
  int sm = 0; //Maquina de estado = 0.
  uint offset = pio_add_program(pio, &ws2812_program); //Programa para controlar os leds da matriz.
  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW); //Inicializa o PIO com o programa WS2812.

  //I2C Inicialização.
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);
  ssd1306_t ssd; 
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
  ssd1306_config(&ssd);
  ssd1306_send_data(&ssd);

  //Inicializando os LEDs como saída.
  gpio_init(Led_G);
  gpio_set_dir(Led_G, GPIO_OUT); // LED verde
  gpio_init(Led_B);
  gpio_set_dir(Led_B, GPIO_OUT); // LED azul

  //Configura interrupções para os botões.
  configurar_botao(botao_a, gpio_irq_handler);
  configurar_botao(botao_b, gpio_irq_handler);

  while (true) {

    char c = getchar_timeout_us(0);  //Lê o caractere sem travar o loop.

    if (c >= '0' && c <= '9') {
        indice_animacao = c - '0';  //Converte char para número.
        selecionar_animacao();  //Atualiza a matriz de LEDs.
        char ste[2] = {c, '\0'};
        ssd1306_draw_string(&ssd, ste, 85, 40); //Posicionamento e print no display OLED.
        ssd1306_send_data(&ssd); //Atualizo o display.
    }else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        char str[2] = {c, '\0'};  //Cria uma string de um caractere.
        ssd1306_draw_string(&ssd, str, 85, 30); //Posicionamento e print no display OLED.
        ssd1306_send_data(&ssd); //Atualizo o display.
    }else 0;
    
    if (display_botao_a==1)
    {
        ssd1306_draw_string(&ssd, "1", 85, 10); //Desenha uma string.
        ssd1306_send_data(&ssd); //Atualizo o display.

    }else if(display_botao_a==0){

        ssd1306_draw_string(&ssd, "0", 85, 10); //Desenha uma string.
        ssd1306_send_data(&ssd);//Atualizo o display.

    }else 0;
    
    if (display_botao_b==1){

        ssd1306_draw_string(&ssd, "1", 85, 20);  //Desenha uma string.
        ssd1306_send_data(&ssd); //Atualizo o display.

    }else if(display_botao_b==0){

        ssd1306_draw_string(&ssd, "0", 85, 20);  //Desenha uma string.
        ssd1306_send_data(&ssd); //Atualizo o display.

    }else 0;

    ssd1306_draw_string(&ssd, "LED VERDE", 5, 10);  //Desenha uma string.
    ssd1306_draw_string(&ssd, "LED AZUL", 5, 20);  //Desenha uma string.
    ssd1306_draw_string(&ssd, "LETRA", 5, 30);  //Desenha uma string.
    ssd1306_draw_string(&ssd, "NUMERO", 5, 40);  //Desenha uma string.
    ssd1306_draw_string(&ssd, "MATHEUS SOUZA", 5, 50);  //Desenha uma string.
    ssd1306_send_data(&ssd); //Atualizo o display.

    set_one_led(led_r, led_g, led_b); //Seto os leds.
  }
}