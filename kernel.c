volatile unsigned char *vidptr = (unsigned char*)0xb8000;
unsigned int cur = 0;

#define MAX_ENTRIES 32
#define NAME_LEN 16
#define PKG_MAX 32
#define PKG_NAME 32

char folders[MAX_ENTRIES][NAME_LEN];
char files[MAX_ENTRIES][NAME_LEN];
int folder_count = 0;
int file_count = 0;

char pkg_names[PKG_MAX][PKG_NAME];
int pkg_count = 0;

void print(const char *str) {
    while (*str) {
        vidptr[cur++] = *str++;
        vidptr[cur++] = 0x07;
    }
}

void clear() {
    for (unsigned int j = 0; j < 80 * 25 * 2; j += 2) {
        vidptr[j] = ' ';
        vidptr[j+1] = 0x07;
    }
    cur = 0;
}

void read_cmd(char *buf, int max) {
    int i = 0;
    while (i < max - 1) {
        unsigned char c = get_key();
        if (c == '\n') break;
        buf[i++] = c;
        vidptr[cur++] = c;
        vidptr[cur++] = 0x07;
    }
    buf[i] = 0;
}

unsigned char get_key() {
    unsigned char scancode;
    char c = 0;
    while (1) {
        scancode = inb(0x60);
        if (scancode & 0x80) continue;
        if (scancode == 0x1C) return '\n'; // Enter
        if (scancode == 0x0E) return 8; // Backspace
        if (scancode == 0x39) return ' '; // Espacio
        // Letras
        if (scancode == 0x1E) return 'a';
        if (scancode == 0x30) return 'b';
        if (scancode == 0x2E) return 'c';
        if (scancode == 0x20) return 'd';
        if (scancode == 0x12) return 'e';
        if (scancode == 0x21) return 'f';
        if (scancode == 0x22) return 'g';
        if (scancode == 0x23) return 'h';
        if (scancode == 0x17) return 'i';
        if (scancode == 0x24) return 'j';
        if (scancode == 0x25) return 'k';
        if (scancode == 0x26) return 'l';
        if (scancode == 0x32) return 'm';
        if (scancode == 0x31) return 'n';
        if (scancode == 0x18) return 'o';
        if (scancode == 0x19) return 'p';
        if (scancode == 0x10) return 'q';
        if (scancode == 0x13) return 'r';
        if (scancode == 0x1F) return 's';
        if (scancode == 0x14) return 't';
        if (scancode == 0x16) return 'u';
        if (scancode == 0x2F) return 'v';
        if (scancode == 0x11) return 'w';
        if (scancode == 0x2D) return 'x';
        if (scancode == 0x15) return 'y';
        if (scancode == 0x2C) return 'z';
        // Números
        if (scancode == 0x02) return '1';
        if (scancode == 0x03) return '2';
        if (scancode == 0x04) return '3';
        if (scancode == 0x05) return '4';
        if (scancode == 0x06) return '5';
        if (scancode == 0x07) return '6';
        if (scancode == 0x08) return '7';
        if (scancode == 0x09) return '8';
        if (scancode == 0x0A) return '9';
        if (scancode == 0x0B) return '0';
        // Símbolos básicos
        if (scancode == 0x0C) return '-';
        if (scancode == 0x0D) return '=';
        if (scancode == 0x1A) return '[';
        if (scancode == 0x1B) return ']';
        if (scancode == 0x27) return ';';
        if (scancode == 0x28) return '\'';
        if (scancode == 0x29) return '`';
        if (scancode == 0x2B) return '\\';
        if (scancode == 0x33) return ',';
        if (scancode == 0x34) return '.';
        if (scancode == 0x35) return '/';
        // Teclas de dirección (opcional, puedes mapearlas a códigos propios)
        if (scancode == 0x48) return 0x80; // Flecha arriba
        if (scancode == 0x50) return 0x81; // Flecha abajo
        if (scancode == 0x4B) return 0x82; // Flecha izquierda
        if (scancode == 0x4D) return 0x83; // Flecha derecha
        // Teclas de función
        if (scancode == 0x3B) return 0xF1; // F1
        if (scancode == 0x3C) return 0xF2; // F2
        if (scancode == 0x3D) return 0xF3; // F3
        if (scancode == 0x3E) return 0xF4; // F4
        if (scancode == 0x3F) return 0xF5; // F5
        if (scancode == 0x40) return 0xF6; // F6
        if (scancode == 0x41) return 0xF7; // F7
        if (scancode == 0x42) return 0xF8; // F8
        if (scancode == 0x43) return 0xF9; // F9
        if (scancode == 0x44) return 0xFA; // F10
        if (scancode == 0x57) return 0xFB; // F11
        if (scancode == 0x58) return 0xFC; // F12
        // Teclas modificadoras
        if (scancode == 0x1D) return 0xE0; // Ctrl izquierdo
        if (scancode == 0x2A) return 0xE1; // Shift izquierdo
        if (scancode == 0x36) return 0xE2; // Shift derecho
        if (scancode == 0x38) return 0xE3; // Alt izquierdo
        if (scancode == 0xE038) return 0xE4; // Alt derecho (AltGr, requiere manejo especial)
        if (scancode == 0xE01D) return 0xE5; // Ctrl derecho (requiere manejo especial)
        // Tecla Windows y Menú (requieren manejo especial)
        if (scancode == 0xE05B) return 0xE6; // Win izquierda
        if (scancode == 0xE05C) return 0xE7; // Win derecha
        if (scancode == 0xE05D) return 0xE8; // Menú
        // Bloqueo
        if (scancode == 0x3A) return 0xC0; // Caps Lock
        if (scancode == 0x45) return 0xC1; // Num Lock
        if (scancode == 0x46) return 0xC2; // Scroll Lock
    }
}

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

int strcmp(const char *a, const char *b) {
    while (*a && *b && *a == *b) a++, b++;
    return *a - *b;
}

int strncmp(const char *a, const char *b, int n) {
    while (n-- && *a && *b && *a == *b) a++, b++;
    return n < 0 ? 0 : *a - *b;
}

void add_pkg(const char *name) {
    if (pkg_count < PKG_MAX) {
        int i = 0;
        while (name[i] && i < PKG_NAME-1) {
            pkg_names[pkg_count][i] = name[i];
            i++;
        }
        pkg_names[pkg_count][i] = 0;
        pkg_count++;
    }
}

void remove_pkg(const char *name) {
    for (int i = 0; i < pkg_count; i++) {
        int match = 1;
        for (int j = 0; j < PKG_NAME; j++) {
            if (pkg_names[i][j] != name[j]) {
                match = 0;
                break;
            }
            if (!name[j]) break;
        }
        if (match) {
            for (int k = i; k < pkg_count-1; k++) {
                for (int j = 0; j < PKG_NAME; j++)
                    pkg_names[k][j] = pkg_names[k+1][j];
            }
            pkg_count--;
            break;
        }
    }
}

void list_pkgs() {
    print("\nPaquetes instalados:\n");
    for (int i = 0; i < pkg_count; i++) {
        print("  ");
        print(pkg_names[i]);
        print("\n");
    }
}

void shell() {
    char cmd[128];
    while (1) {
        print("\n> ");
        read_cmd(cmd, 128);

        if (!strcmp(cmd, "help")) {
            print("\nComandos: help, clear, about, echo, mkdir <nombre>, mkfile <nombre>, ls, minesitooxd -i/-ui/-ri/-ud -f <archivo>, pkglist, reboot, banner, count, whoami, time");
        } else if (!strcmp(cmd, "clear")) {
            clear();
        } else if (!strcmp(cmd, "about")) {
            print("\nYanisMinesitoo OS kernel propio!");
        } else if (!strncmp(cmd, "echo ", 5)) {
            print("\n");
            print(cmd + 5);
        } else if (!strncmp(cmd, "mkdir ", 6)) {
            if (folder_count < MAX_ENTRIES) {
                int i = 0;
                const char *name = cmd + 6;
                while (name[i] && i < NAME_LEN-1) {
                    folders[folder_count][i] = name[i];
                    i++;
                }
                folders[folder_count][i] = 0;
                folder_count++;
                print("\nCarpeta creada.");
            } else {
                print("\nNo se pueden crear más carpetas.");
            }
        } else if (!strncmp(cmd, "mkfile ", 7)) {
            if (file_count < MAX_ENTRIES) {
                int i = 0;
                const char *name = cmd + 7;
                while (name[i] && i < NAME_LEN-1) {
                    files[file_count][i] = name[i];
                    i++;
                }
                files[file_count][i] = 0;
                file_count++;
                print("\nArchivo creado.");
            } else {
                print("\nNo se pueden crear más archivos.");
            }
        } else if (!strcmp(cmd, "ls")) {
            print("\nCarpetas:\n");
            for (int i = 0; i < folder_count; i++) {
                print("  ");
                print(folders[i]);
                print("\n");
            }
            print("Archivos:\n");
            for (int i = 0; i < file_count; i++) {
                print("  ");
                print(files[i]);
                print("\n");
            }
        } else if (!strcmp(cmd, "pkglist")) {
            list_pkgs();
        } else if (!strncmp(cmd, "minesitooxd ", 12)) {
            print("\nSimulando gestor de paquetes minesitooxd...\n");
            const char *args = cmd + 12;
            int op = 0;
            const char *file = 0;
            if (strncmp(args, "-i ", 3) == 0) { op = 1; file = args + 5; }
            else if (strncmp(args, "-ui ", 4) == 0) { op = 2; file = args + 6; }
            else if (strncmp(args, "-ri ", 4) == 0) { op = 3; file = args + 6; }
            else if (strncmp(args, "-ud ", 4) == 0) { op = 4; file = args + 6; }
            else { print("Uso: minesitooxd -i/-ui/-ri/-ud -f <archivo>"); continue; }
            if (!file || !*file) { print("Falta el nombre del archivo."); continue; }
            if (op == 1) {
                print("Descargando "); print(file); print(" de servidores...\n");
                print("Instalando "); print(file); print("...\n¡Listo!");
                add_pkg(file);
            }
            else if (op == 2) {
                print("Desinstalando "); print(file); print("...\n¡Listo!");
                remove_pkg(file);
            }
            else if (op == 3) {
                print("Reinstalando "); print(file); print("...\n¡Listo!");
            }
            else if (op == 4) {
                print("Actualizando "); print(file); print("...\n¡Listo!");
            }
        } else if (!strcmp(cmd, "reboot")) {
            print("\nReiniciando...\n");
            __asm ("int $0x19");
        } else if (!strcmp(cmd, "banner")) {
            print("\n=== YanisMinesitoo OS ===\n");
        } else if (!strcmp(cmd, "count")) {
            print("\nContando: ");
            for (int i = 1; i <= 10; i++) {
                char num[3] = { '0' + i, 0 };
                print(num);
                print(" ");
            }
        } else if (!strcmp(cmd, "whoami")) {
            print("\nEres root (usuario único)");
        } else if (!strcmp(cmd, "time")) {
            print("\nFunción de reloj no implementada (kernel básico)");
        } else {
            print("\nComando no reconocido.");
        }
    }
}

// --- LOGIN SCREEN ---
#define LOGIN_USER "admin"
#define LOGIN_PASS "1234"

void draw_login_screen(const char *user_input, const char *pass_input, int focus, int error) {
    draw_png_wallpaper(); // Fondo de pantalla
    // Dibuja cajas de input y botón
    // Caja usuario
    for (int y = 60; y < 80; y++)
        for (int x = 90; x < 230; x++)
            putpixel(x, y, focus == 0 ? 15 : 8); // Blanco si enfocado, gris si no
    // Caja contraseña
    for (int y = 100; y < 120; y++)
        for (int x = 90; x < 230; x++)
            putpixel(x, y, focus == 1 ? 15 : 8);
    // Botón
    for (int y = 140; y < 160; y++)
        for (int x = 120; x < 200; x++)
            putpixel(x, y, focus == 2 ? 10 : 7); // Verde si enfocado, gris claro si no
    // Texto
    // (Solo modo texto, simplificado)
    cur = 0; // Reset cursor texto
    print("\n\n        Nombre de usuario:");
    cur = 160; // Ajusta para que el texto salga debajo de la caja
    print(user_input);
    cur = 160 + 80; // Ajusta para la segunda caja
    print("\n        Contraseña:");
    cur = 160 + 160;
    for (int i = 0; pass_input[i]; i++) print("*");
    cur = 160 + 240;
    print("\n         [ Iniciar sesión ]");
    if (error) {
        cur = 160 + 320;
        print("\n  Usuario o contraseña incorrectos");
    }
}

void login() {
    char user[16] = "";
    char pass[16] = "";
    int focus = 0; // 0: user, 1: pass, 2: botón
    int pos[2] = {0, 0};
    int error = 0;
    while (1) {
        clear();
        draw_login_screen(user, pass, focus, error);
        unsigned char c = get_key();
        if (c == '\n') {
            if (focus < 2) focus++;
            else {
                if (!strcmp(user, LOGIN_USER) && !strcmp(pass, LOGIN_PASS)) break;
                error = 1;
            }
        } else if (c == ' ') {
            focus = (focus + 1) % 3;
        } else if (c == 8) { // Backspace
            if (focus == 0 && pos[0] > 0) user[--pos[0]] = 0;
            if (focus == 1 && pos[1] > 0) pass[--pos[1]] = 0;
        } else if (c >= 'a' && c <= 'z') {
            if (focus == 0 && pos[0] < 15) { user[pos[0]++] = c; user[pos[0]] = 0; }
            if (focus == 1 && pos[1] < 15) { pass[pos[1]++] = c; pass[pos[1]] = 0; }
        }
    }
}

void set_video_mode(unsigned char mode) {
    __asm (
        "movb %0, %%al;"
        "movb $0x00, %%ah;"
        "int $0x10;"
        :
        : "a"(mode)
        : "ax"
    );
}

void putpixel(int x, int y, unsigned char color) {
    unsigned char *vidmem = (unsigned char*)0xA0000;
    vidmem[320 * y + x] = color;
}

void draw_wallpaper() {
    // Fondo degradado azul a verde
    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 320; x++) {
            unsigned char color = (x * 32 / 320) + (y * 32 / 200); // Degradado simple
            putpixel(x, y, color % 64 + 16); // Colores VGA del 16 al 79
        }
    }
    // Cuadro central
    for (int y = 80; y < 120; y++)
        for (int x = 110; x < 210; x++)
            putpixel(x, y, 15); // Blanco
    // Borde del cuadro
    for (int x = 110; x < 210; x++) {
        putpixel(x, 80, 12); putpixel(x, 119, 12);
    }
    for (int y = 80; y < 120; y++) {
        putpixel(110, y, 12); putpixel(209, y, 12);
    }
}

void kernel_main() {
    set_video_mode(0x13); // Modo gráfico 320x200x256
    login(); // Pantalla de login
    shell(); // Solo si login correcto
}

// Elimina la dependencia de stdint.h, define tipos básicos si se necesitan
// typedef unsigned int uint32_t; // Descomenta si usas uint32_t