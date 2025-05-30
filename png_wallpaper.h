// stb_image.h - decodificador PNG de dominio público
// Descargado de https://github.com/nothings/stb/blob/master/stb_image.h
// (Solo se incluye el encabezado, el usuario debe descargar el archivo completo para uso real)

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Ejemplo de cómo usar stb_image para decodificar un PNG embebido
// (debes convertir tu imagen.png a un array de bytes con xxd -i imagen.png > imagen_png.h)
#include "imagen_png.h"

void draw_png_wallpaper() {
    int w, h, comp;
    unsigned char *pixels = stbi_load_from_memory(imagen_png, imagen_png_len, &w, &h, &comp, 3);
    if (!pixels) return;
    // Dibuja la imagen centrada en 320x200
    int x0 = (320 - w) / 2;
    int y0 = (200 - h) / 2;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = (y * w + x) * 3;
            unsigned char r = pixels[idx];
            unsigned char g = pixels[idx+1];
            unsigned char b = pixels[idx+2];
            // Convertir RGB a un color VGA aproximado (usa solo 6 bits)
            unsigned char color = ((r >> 6) << 4) | ((g >> 6) << 2) | (b >> 6);
            putpixel(x0 + x, y0 + y, color);
        }
    }
    stbi_image_free(pixels);
}
