#include <stdint.h>
#include <string.h>
#include "imagen_png.h" // Incluye la imagen PNG para mostrar
#include "filesystem.h" // Simulación de sistema de archivos para listar imágenes

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define MAX_IMAGES 100

char image_files[MAX_IMAGES][NAME_LEN];
int image_count = 0;
int current_image = 0;

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

void draw_image(const uint8_t *image, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8_t color = image[y * width + x];
            putpixel(x, y, color);
        }
    }
}

void load_images_from_directory(const char *directory) {
    image_count = list_files(directory, image_files, MAX_IMAGES, ".png;.bmp;.jpg");
    current_image = 0;
}

void draw_image_from_file(const char *file_path) {
    // Decodificar y dibujar la imagen según su formato
    if (ends_with(file_path, ".png")) {
        draw_png(file_path);
    } else if (ends_with(file_path, ".bmp")) {
        draw_bmp(file_path);
    } else if (ends_with(file_path, ".jpg")) {
        draw_jpeg(file_path);
    } else {
        clear_screen();
        print("Formato no soportado: ");
        print(file_path);
    }
}

void imgviewer_main() {
    load_images_from_directory("/apps/imgviewer");
    if (image_count == 0) {
        clear_screen();
        print("No se encontraron imágenes en /apps/imgviewer");
        return;
    }

    while (1) {
        clear_screen();
        draw_image_from_file(image_files[current_image]);
        unsigned char c = get_key();
        if (c == 'n') { // Siguiente imagen
            current_image = (current_image + 1) % image_count;
        } else if (c == 'p') { // Imagen anterior
            current_image = (current_image - 1 + image_count) % image_count;
        } else if (c == 'q') { // Salir
            break;
        }
    }
}
