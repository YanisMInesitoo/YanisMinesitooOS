// Imagen BMP 24bpp 32x32 (ejemplo, fondo azul con un cuadrado rojo)
const unsigned char wallpaper_bmp[] = {
    0x42,0x4D,0x76,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
    0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
    0x00,0x00,0x40,0x0C,0x00,0x00,0x13,0x0B,0x00,0x00,0x13,0x0B,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,
    // ... (rellena con datos de píxeles: azul de fondo, cuadrado rojo en el centro) ...
};

// Decodificador BMP 24bpp muy simple para 32x32
void draw_bmp_wallpaper() {
    int width = 32, height = 32;
    int offset = 54; // Header BMP
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = offset + 3 * (x + (height - 1 - y) * width);
            unsigned char b = wallpaper_bmp[idx];
            unsigned char g = wallpaper_bmp[idx+1];
            unsigned char r = wallpaper_bmp[idx+2];
            // Convertimos RGB a un color VGA aproximado (usa solo azul y rojo)
            unsigned char color = (r > 128 ? 4 : 0) + (b > 128 ? 1 : 0);
            putpixel(x+144, y+84, color); // Centrado en 320x200
        }
    }
}
