
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define GPIO_LED_R 16
#define GPIO_LED_G 17
#define GPIO_LED_B 18
#define BUZZER_PIN 15

const uint8_t columns[] = {6, 7, 8, 9};
const uint8_t rows[] = {10, 11, 12, 13};
const char KEY_MAP[4][4] = {
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

void gpio_put_rgb(bool r, bool g, bool b) {
    gpio_put(GPIO_LED_R, r);
    gpio_put(GPIO_LED_G, g);
    gpio_put(GPIO_LED_B, b);
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
// Função para tratar a tecla pressionada
void handle_key_press(char key) {
    switch (key) {
        case '1':
            gpio_put_rgb(1, 0, 0);
            break;
        case '2':
            gpio_put_rgb(0, 1, 0); 
            break;
        case '3':
            gpio_put_rgb(0, 0, 1);
            break;
        case '4':
            for (int i = 0; i < 10; i++) {
                gpio_put(GPIO_LED_R, 1); 
                sleep_ms(500);
                gpio_put(GPIO_LED_R, 0); 
                sleep_ms(500);
            }
            break;
        case '5':
            for (int i = 0; i < 10; i++) {
                gpio_put(GPIO_LED_G, 1); 
                sleep_ms(500);
                gpio_put(GPIO_LED_G, 0); 
                sleep_ms(500);
            }
            break;
        case '6':
            for (int i = 0; i < 10; i++) {
                gpio_put(GPIO_LED_B, 1); 
                sleep_ms(500);
                gpio_put(GPIO_LED_B, 0);
                sleep_ms(500);
            }
            break;
        case '7':
            for (int i = 0; i < 10; i++) {
                gpio_put_rgb(1, 1, 1); 
                sleep_ms(500);
                gpio_put_rgb(0, 0, 0); 
                sleep_ms(500);
            }
            break;
        case '8':
            for (int i = 0; i < 20; i++) {
                gpio_put_rgb(1, 1, 1); 
                sleep_ms(250);
                gpio_put_rgb(0, 0, 0); 
                sleep_ms(250);
            }
            break;
        case '9':
            for (int i = 0; i < 10; i++) {
                gpio_put_rgb(1, 1, 1);
                sleep_ms(5);
                gpio_put_rgb(0, 0, 0); 
                sleep_ms(5);
            }
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

char read_keypad() {
    for (int col = 0; col < 4; col++) {
        gpio_set_dir(columns[col], GPIO_OUT);
        gpio_put(columns[col], 0); // Ativa a coluna
        sleep_ms(1); // Aumenta o tempo de estabilização
        for (int row = 0; row < 4; row++) {
            gpio_set_dir(rows[row], GPIO_IN);
            gpio_pull_up(rows[row]); // Habilita o pull-up
            if (gpio_get(rows[row]) == 0) { // Detecta se a linha está baixa
                gpio_set_dir(columns[col], GPIO_IN);
                return KEY_MAP[row][col];
            }
        }
        gpio_set_dir(columns[col], GPIO_IN);
    }
    return '\0';
}

// Função Principal
int main() {
    stdio_init_all();

    for (int i = 0; i < 4; i++) {
        gpio_init(columns[i]);
        gpio_init(rows[i]);
    }

    gpio_init(GPIO_LED_R);
    gpio_set_dir(GPIO_LED_R, GPIO_OUT);
    gpio_init(GPIO_LED_G);
    gpio_set_dir(GPIO_LED_G, GPIO_OUT);
    gpio_init(GPIO_LED_B);
    gpio_set_dir(GPIO_LED_B, GPIO_OUT);
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    gpio_put_rgb(0, 0, 0); 
    buzzer_off(); 

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