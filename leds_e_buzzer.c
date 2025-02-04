//Programa para acionar leds e buzzer na placa BitDogLab
//SUBGRUPO 7

#include <stdio.h>
#include "pico/stdlib.h"     //biblioteca PICO
#include "hardware/gpio.h"  //biblioteca GPIO
#include "hardware/pwm.h"  //biblioteca PWM

#define GPIO_LED_R 16
#define GPIO_LED_G 17
#define GPIO_LED_B 18
#define BUZZER_PIN 15
#define FREQUENCIA 500  //define a frequencia do buzzer=500Hz

// Matriz de teclas do teclado matricial
const uint8_t columns[] = {6, 7, 8, 9}; //definição das colunas
const uint8_t rows[] = {10, 11, 12, 13}; //definição das linhas
const char KEY_MAP[4][4] = {    //definição da matriz de teclas
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para configurar os GPIOs dos LEDs RGB
void config_gpio_rgb_leds() {
    gpio_init(GPIO_LED_R);
    gpio_set_dir(GPIO_LED_R, GPIO_OUT);
    gpio_init(GPIO_LED_G);
    gpio_set_dir(GPIO_LED_G, GPIO_OUT);
    gpio_init(GPIO_LED_B);
    gpio_set_dir(GPIO_LED_B, GPIO_OUT);
   
    gpio_put(GPIO_LED_R, 0);
    gpio_put(GPIO_LED_G, 0);
    gpio_put(GPIO_LED_B, 0);
}

void gpio_put_rgb(bool r, bool g, bool b) { //função que liga/desliga os leds
    gpio_put(GPIO_LED_R, r);               //liga/desliga led vermelho
    gpio_put(GPIO_LED_G, g);              //liga/desliga led verde
    gpio_put(GPIO_LED_B, b);             //liga/desliga led azul
}

// Função para ligar o buzzer
void buzzer_on() {
    gpio_put(BUZZER_PIN, 1);
}
// Função para desligar o buzzer
void buzzer_off() {
    gpio_put(BUZZER_PIN, 0);
}
// Função para tocar um padrão de som no buzzer
void play_buzzer_pattern(char key) {
    switch (key) {
        case 'A':
            buzzer_on();
            sleep_ms(200);
            buzzer_off();
            sleep_ms(200);
            buzzer_on();
            sleep_ms(200);
            buzzer_off();
            break;
        case 'B':
            buzzer_on();
            sleep_ms(500);
            buzzer_off();
            break;
        case 'C':
            buzzer_on();
            sleep_ms(100);
            buzzer_off();
            sleep_ms(100);
            buzzer_on();
            sleep_ms(100);
            buzzer_off();
            break;
        case 'D':
            buzzer_on();
            sleep_ms(300);
            buzzer_off();
            sleep_ms(300);
            buzzer_on();
            sleep_ms(300);
            buzzer_off();
            break;
        default:
            break;
    }
}

//Implementando controle dos leds com temporizador
void timer_based_led_control(){
    int i;

    for(i = 0; i < 3; i++){ //fazer com que o led pisque 3x
        gpio_put_rgb(1, 1, 1);
        sleep_ms(1000);
        gpio_put_rgb(0, 0, 0);
        sleep_ms(1000);
    }
}

//configurar um padrão de som para algumas teclas
void custom_sound_pattern(){
    int i;

    for(i = 0; i < 4; i++){
        buzzer_on();
        sleep_ms(250);
        buzzer_off();
        sleep_ms(250);
    }
}

// Função para tratar a tecla pressionada
void handle_key_press(char key) {
    switch (key) {
        case '1':
            gpio_put_rgb(1, 0, 0);  
            sleep_ms(5000);
            gpio_put_rgb(0, 0, 0); 
            sleep_ms(100);
//nos casos 1-2-3 foi adicionado t=5s p/ desligamento
            break;
        case '2':
            gpio_put_rgb(0, 1, 0); 
            sleep_ms(5000);
            gpio_put_rgb(0, 0, 0); 
            sleep_ms(100);
            break;
        case '3':
            gpio_put_rgb(0, 0, 1);
            sleep_ms(5000);
            gpio_put_rgb(0, 0, 0); 
            sleep_ms(100);            
            break;
        case '4':
            for (int i = 0; i < 4; i++) {
                gpio_put(GPIO_LED_R, 1); 
                sleep_ms(500);
                gpio_put(GPIO_LED_R, 0); 
                sleep_ms(500);
            }
            break;
        case '5':
            for (int i = 0; i < 5; i++) {
                gpio_put(GPIO_LED_G, 1); 
                sleep_ms(500);
                gpio_put(GPIO_LED_G, 0); 
                sleep_ms(500);
            }
            break;
        case '6':
            for (int i = 0; i < 6; i++) {
                gpio_put(GPIO_LED_B, 1); 
                sleep_ms(500);
                gpio_put(GPIO_LED_B, 0);
                sleep_ms(500);
            }
            break;
        case '7':
            for (int i = 0; i < 7; i++) {
                gpio_put_rgb(1, 1, 1); 
                sleep_ms(500);
                gpio_put_rgb(0, 0, 0); 
                sleep_ms(500);
            }
            break;
        case '8':
            for (int i = 0; i < 8; i++) {
                gpio_put_rgb(1, 1, 1); 
                sleep_ms(500);
                gpio_put_rgb(0, 0, 0); 
                sleep_ms(500);
            }        //nos casos 4~9 foi alterada a quantidade
            break;  //de iterações 'for' para cada combinação
        case '9':  //'piscar' == número da tecla acionada
            for (int i = 0; i < 9; i++) {
                gpio_put_rgb(1, 1, 1);
                sleep_ms(500);
                gpio_put_rgb(0, 0, 0); 
                sleep_ms(500);
            }
            break;
        case '*':
            gpio_put_rgb(1,1,1);
            buzzer_on();
            sleep_ms(1000);
            gpio_put_rgb(0,0,0);
            buzzer_off();
            break;
        case '0':
            gpio_put_rgb(0, 0, 0); 
            buzzer_off();
            break;
        default:
            play_buzzer_pattern(key);
            break;
    }
}
// Função para ler a tecla pressionada
char read_keypad() {
    for (int col = 0; col < 4; col++) {
        gpio_set_dir(columns[col], GPIO_OUT);
        gpio_put(columns[col], 0); // Ativa a coluna
        sleep_ms(1); // Aumenta o tempo de estabilização
        for (int row = 0; row < 4; row++) {
            gpio_set_dir(rows[row], GPIO_IN);
            gpio_pull_up(rows[row]); // Habilita o pull-up
            if (gpio_get(rows[row]) == 0) { // Detecta se a linha está baixa
                while (gpio_get(rows[row]) == 0) sleep_ms(50); // Espera a tecla ser liberada
                gpio_set_dir(columns[col], GPIO_IN); // Retorna a coluna para entrada
                return KEY_MAP[row][col]; // Retorna a tecla pressionada
            }
        }
        gpio_set_dir(columns[col], GPIO_IN); // Retorna a coluna para entrada
    }
    return '\0'; // Nenhuma tecla pressionada
}

// Função Principal
int main() {
    stdio_init_all();

    for (int i = 0; i < 4; i++) {
        gpio_init(columns[i]);
        gpio_init(rows[i]);
    }

    // Configura os GPIOs para os LEDs RGB
    config_gpio_rgb_leds();

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT); 

    // Loop infinito para leitura das teclas
    char caracter_press;

    while (true) {
        caracter_press = read_keypad();
        if (caracter_press != '\0') {
            printf("\nTecla pressionada: %c\n", caracter_press);
            handle_key_press(caracter_press);
        }
        sleep_ms(100); 
    }
}