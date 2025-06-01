#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define MAX_TEXT_LENGTH 1024

char text_buffer[MAX_TEXT_LENGTH];
int text_length = 0;
int cursor_position = 0;

void putpixel(int x, int y, uint8_t color) {
    uint8_t *vidmem = (uint8_t *)0xA0000;
    vidmem[SCREEN_WIDTH * y + x] = color;
}

void clear_screen() {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            putpixel(x, y, 0); // Negro
        }
    }
}

void draw_text(const char *text, int x, int y) {
    int cur = y * SCREEN_WIDTH + x;
    uint8_t *vidmem = (uint8_t *)0xA0000;
    for (int i = 0; text[i] != '\0'; i++) {
        vidmem[cur++] = text[i];
        vidmem[cur++] = 0x07; // Color blanco
    }
}

void draw_editor() {
    clear_screen();
    draw_text("Bloc de Notas - Presiona ESC para salir", 0, 0);
    draw_text(text_buffer, 0, 2);
    // Dibuja el cursor
    int cursor_x = cursor_position % SCREEN_WIDTH;
    int cursor_y = 2 + (cursor_position / SCREEN_WIDTH);
    putpixel(cursor_x, cursor_y, 0x0F); // Cursor blanco
}

void save_to_file(const char *username, const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "/home/%s/Documents/%s.txt", username, filename);

    FILE *file = fopen(path, "w");
    if (file) {
        fwrite(text_buffer, 1, text_length, file);
        fclose(file);
        print("Archivo guardado en: ");
        print(path);
    } else {
        print("Error al guardar el archivo.");
    }
}

void notepad_main(const char *username) {
    text_length = 0;
    cursor_position = 0;
    text_buffer[0] = '\0';

    char filename[32] = "";
    print("Introduce el nombre del archivo: ");
    read_cmd(filename, sizeof(filename));

    while (1) {
        draw_editor();
        unsigned char c = get_key();
        if (c == 27) { // ESC para salir
            save_to_file(username, filename);
            break;
        } else if (c == 8) { // Backspace
            if (cursor_position > 0) {
                for (int i = cursor_position; i < text_length; i++) {
                    text_buffer[i - 1] = text_buffer[i];
                }
                cursor_position--;
                text_length--;
                text_buffer[text_length] = '\0';
            }
        } else if (c >= 32 && c <= 126) { // Caracteres imprimibles
            if (text_length < MAX_TEXT_LENGTH - 1) {
                for (int i = text_length; i > cursor_position; i--) {
                    text_buffer[i] = text_buffer[i - 1];
                }
                text_buffer[cursor_position] = c;
                cursor_position++;
                text_length++;
                text_buffer[text_length] = '\0';
            }
        }
    }
}
