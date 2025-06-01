#include <stdint.h>
#include <string.h>
#include "filesystem.h" // Simulación de sistema de archivos para listar directorios y archivos

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define MAX_ENTRIES 100

char entries[MAX_ENTRIES][NAME_LEN];
int entry_count = 0;
int selected_entry = 0;

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

void draw_sysviewer(const char *directory) {
    clear_screen();
    draw_text("Gestor de Archivos - Presiona ESC para salir", 0, 0);
    draw_text(directory, 0, 1);

    for (int i = 0; i < entry_count; i++) {
        if (i == selected_entry) {
            draw_text(">", 0, 2 + i);
        }
        draw_text(entries[i], 2, 2 + i);
    }
}

void sysviewer_main(const char *directory) {
    entry_count = list_files(directory, entries, MAX_ENTRIES, NULL);
    selected_entry = 0;

    while (1) {
        draw_sysviewer(directory);
        unsigned char c = get_key();
        if (c == 27) { // ESC para salir
            break;
        } else if (c == 'w') { // Arriba
            selected_entry = (selected_entry - 1 + entry_count) % entry_count;
        } else if (c == 's') { // Abajo
            selected_entry = (selected_entry + 1) % entry_count;
        } else if (c == '\n') { // Enter para abrir
            char new_path[256];
            snprintf(new_path, sizeof(new_path), "%s/%s", directory, entries[selected_entry]);
            sysviewer_main(new_path); // Abrir el nuevo directorio
        }
    }
}
