# Projeto de Controle de LEDs e Display OLED

Este projeto utiliza o Raspberry Pi Pico para controlar uma matriz de LEDs WS2812, um display OLED SSD1306, e LEDs físicos RGB (verde e azul). Ele também permite interagir com o sistema por meio de botões para alterar o estado dos LEDs e visualizar informações no display OLED.

## Componentes Utilizados

- **Raspberry Pi Pico**
- **Matriz de LEDs WS2812**
- **Display OLED SSD1306 (I2C)**
- **LEDs RGB (verde e azul)**
- **Botões físicos (para controlar os LEDs)**

## Funcionalidades

- **Controle de LEDs WS2812**: A matriz de LEDs pode exibir diferentes animações configuradas no código.
- **Controle de LEDs físicos**: O código permite ligar ou desligar LEDs verde e azul através de botões.
- **Display OLED SSD1306**: Exibe informações como o estado dos LEDs e a entrada de caracteres.

## Requisitos

- Raspberry Pi Pico ou qualquer placa com suporte para o Raspberry Pi Pico.
- Biblioteca `ssd1306` para controlar o display OLED.
- Biblioteca `ws2812` para controlar a matriz de LEDs WS2812.

## Como Usar

1. **Componentes BitDogLab**:
   - A matriz de LEDs WS2812 ao pino GPIO7.
   - O display OLED via I2C (SDA no GPIO14, SCL no GPIO15).
   - O LED verde ao pino GPIO11 e o LED azul ao pino GPIO12.
   - Conecte os botões aos pinos GPIO5 e GPIO6.

2. **Compilar e carregar o código**:
   - Abra o código no seu ambiente de desenvolvimento preferido e compile-o.
   - Carregue o código no Raspberry Pi Pico.

3. **Controle os LEDs**:
   - Pressione o **Botão A** para alternar o LED verde.
   - Pressione o **Botão B** para alternar o LED azul.
   - O display OLED exibirá o estado atual dos LEDs e outros dados.

## Exemplo de Saída no Display OLED

O display OLED exibirá informações como:
- O estado dos LEDs verde e azul.
- A letra ou caractere recebido do teclado.

## Bibliotecas Utilizadas

- `ssd1306`: Biblioteca para controle do display OLED SSD1306 via I2C.
- `ws2812`: Biblioteca para controle da matriz de LEDs WS2812 via PIO.
- `pico/stdlib`: Biblioteca padrão do Raspberry Pi Pico.

## Autor:

Matheus Santos Souza

## Código Base:

Professor Wilton Lacerda Git Hub --> [GitHubProfWilton](https://github.com/wiltonlacerda/EmbarcaTechU4C6.git)

## Link do Vídeo:

[Video de apresentação e demonstração](https://youtu.be/yX6q0HH_Tis)


