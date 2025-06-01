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

// Definiciones para soporte de rutas según versión (normal o portable)
#ifndef SYS_BASE
#define SYS_BASE "/" // Por defecto, versión normal
#endif
#define SYS_BOOT  SYS_BASE "boot/"
#define SYS_HOME  SYS_BASE "home/"
#define SYS_OPT   SYS_BASE "opt/"
#define SYS_APPS  SYS_BASE "apps/"
#define SYS_DEV   SYS_BASE "dev/"

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
                // Prefijar ruta base para carpetas
                char fullpath[NAME_LEN + 32];
                int j = 0;
                const char *base = SYS_HOME; // Carpeta base por defecto
                while (base[j] && j < 31) { fullpath[j] = base[j]; j++; }
                int k = 0;
                while (name[k] && j < NAME_LEN + 31 - 1) { fullpath[j++] = name[k++]; }
                fullpath[j] = 0;
                // Guardar la ruta completa en folders
                for (i = 0; i < NAME_LEN-1 && fullpath[i]; i++)
                    folders[folder_count][i] = fullpath[i];
                folders[folder_count][i] = 0;
                folder_count++;
                print("\nCarpeta creada en: ");
                print(fullpath);
            } else {
                print("\nNo se pueden crear más carpetas.");
            }
        } else if (!strncmp(cmd, "mkfile ", 7)) {
            if (file_count < MAX_ENTRIES) {
                int i = 0;
                const char *name = cmd + 7;
                // Prefijar ruta base para archivos
                char fullpath[NAME_LEN + 32];
                int j = 0;
                const char *base = SYS_HOME; // Carpeta base por defecto
                while (base[j] && j < 31) { fullpath[j] = base[j]; j++; }
                int k = 0;
                while (name[k] && j < NAME_LEN + 31 - 1) { fullpath[j++] = name[k++]; }
                fullpath[j] = 0;
                // Guardar la ruta completa en files
                for (i = 0; i < NAME_LEN-1 && fullpath[i]; i++)
                    files[file_count][i] = fullpath[i];
                files[file_count][i] = 0;
                file_count++;
                print("\nArchivo creado en: ");
                print(fullpath);
            } else {
                print("\nNo se pueden crear más archivos.");
            }
        } else if (!strcmp(cmd, "ls")) {
            print("\nCarpetas en "); print(SYS_HOME); print(":\n");
            for (int i = 0; i < folder_count; i++) {
                print("  ");
                print(folders[i]);
                print("\n");
            }
            print("Archivos en "); print(SYS_HOME); print(":\n");
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
        } else if (!strncmp(cmd, "instalar ", 9)) {
            const char *file = cmd + 9;
            int len = strlen(file);
            if (len > 4 && !strcmp(file + len - 4, ".exe")) {
                print("\n[Windows] Instalador .exe detectado. Ejecutando (simulado)...\n");
                print("(No se puede ejecutar código Windows real, solo simulación de instalación)\n");
            } else if (len > 4 && !strcmp(file + len - 4, ".msi")) {
                print("\n[Windows] Instalador .msi detectado. Ejecutando (simulado)...\n");
                print("(No se puede ejecutar código MSI real, solo simulación de instalación)\n");
            } else if (len > 4 && !strcmp(file + len - 4, ".dll")) {
                print("\n[Windows] Librería .dll detectada. (No se puede cargar, solo simulado)\n");
            } else if (len > 4 && !strcmp(file + len - 4, ".deb")) {
                print("\n[Linux] Instalador .deb detectado. Usando dpkg si está disponible...\n");
                print("dpkg -i "); print(file); print("\n(Simulado, solo disponible si dpkg está en el sistema)\n");
            } else if (len > 4 && !strcmp(file + len - 4, ".rpm")) {
                print("\n[Linux] Instalador .rpm detectado. Ejecutando (simulado)...\n");
                print("(No se puede instalar RPM real, solo simulación de instalación)\n");
            } else {
                print("\nTipo de instalador no reconocido o no soportado.\n");
            }
        } else if (!strncmp(cmd, "wget ", 5)) {
            print("\nEjecutando wget...\n");
            system(cmd); // Solo funcionará si el OS es Linux+initramfs y wget está presente
        } else if (!strncmp(cmd, "curl ", 5)) {
            print("\nEjecutando curl...\n");
            system(cmd); // Solo funcionará si el OS es Linux+initramfs y curl está presente
        } else if (!strncmp(cmd, "ping ", 5)) {
            print("\nEjecutando ping...\n");
            system(cmd); // Solo funcionará si el OS es Linux+initramfs y ping está presente (busybox)
        } else if (!strncmp(cmd, "wifi ", 5)) {
            // wifi <ssid> <password>
            char ssid[64] = "";
            char pass[64] = "";
            int i = 0, j = 0;
            const char *args = cmd + 5;
            // Extraer SSID
            while (args[i] && args[i] != ' ' && i < 63) { ssid[i] = args[i]; i++; }
            ssid[i] = 0;
            if (args[i] == ' ') i++;
            // Extraer password
            while (args[i] && j < 63) { pass[j++] = args[i++]; }
            pass[j] = 0;
            if (!ssid[0] || !pass[0]) {
                print("\nUso: wifi <ssid> <password>");
            } else {
                print("\nConectando a WiFi: "); print(ssid); print(" ...\n");
                // Generar comando para conectar (requiere wpa_supplicant y dhclient o udhcpc)
                print("Ejecutando: wpa_passphrase \""); print(ssid); print("\" \""); print(pass); print("\" > /tmp/wpa.conf\n");
                print("wpa_supplicant -B -i wlan0 -c /tmp/wpa.conf\n");
                print("dhclient wlan0\n");
                print("(Asegúrate de tener wpa_supplicant, dhclient y permisos root)\n");
                // En un OS real, aquí se llamaría a system() con los comandos anteriores
            }
        } else if (!strcmp(cmd, "wifi-ui")) {
            wifi_app();
        } else if (!strcmp(cmd, "imgviewer")) {
            imgviewer_main();
        } else if (!strcmp(cmd, "notepad")) {
            notepad_main();
        } else if (!strcmp(cmd, "sysviewer")) {
            sysviewer_main("/");
        } else {
            print("\nComando no reconocido.");
        }
    }
}

// --- LOGIN SCREEN ---
#define LOGIN_USER "admin"
#define LOGIN_PASS "1234"

void draw_login_screen(const char *user_input, const char *pass_input, int focus, int error) {
    draw_login_wallpaper(); // Fondo de pantalla personalizado para login
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
    cur = 0;
    print("\n\n        Nombre de usuario:");
    cur = 160;
    print(user_input);
    cur = 160 + 80;
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

// --- WIFI APP ---
void draw_wifi_app(const char *ssid, const char *user, const char *pass, int focus, int status) {
    draw_wallpaper();
    // Caja SSID
    for (int y = 60; y < 80; y++)
        for (int x = 90; x < 230; x++)
            putpixel(x, y, focus == 0 ? 15 : 8);
    // Caja usuario (opcional)
    for (int y = 90; y < 110; y++)
        for (int x = 90; x < 230; x++)
            putpixel(x, y, focus == 1 ? 15 : 8);
    // Caja contraseña
    for (int y = 120; y < 140; y++)
        for (int x = 90; x < 230; x++)
            putpixel(x, y, focus == 2 ? 15 : 8);
    // Botón conectar
    for (int y = 160; y < 180; y++)
        for (int x = 120; x < 200; x++)
            putpixel(x, y, focus == 3 ? 10 : 7); // Verde si enfocado, gris claro si no
    // Texto
    cur = 0;
    print("\n\n        SSID de la red WiFi:");
    cur = 160;
    print(ssid);
    cur = 160 + 60;
    print("\n        Usuario (802.1X, opcional):");
    cur = 160 + 120;
    print(user);
    cur = 160 + 180;
    print("\n        Contraseña:");
    cur = 160 + 240;
    for (int i = 0; pass[i]; i++) print("*");
    cur = 160 + 300;
    print("\n         [ Conectar ]");
    if (status == 1) {
        cur = 160 + 360;
        print("\n  ¡Conectando a WiFi...");
    } else if (status == 2) {
        cur = 160 + 360;
        print("\n  ¡Conexión enviada! (Requiere soporte real en el sistema)");
    }
}

void wifi_app() {
    char ssid[32] = "";
    char user[32] = "";
    char pass[32] = "";
    int focus = 0; // 0: ssid, 1: user, 2: pass, 3: botón
    int pos[3] = {0, 0, 0};
    int status = 0;
    while (1) {
        clear();
        draw_wifi_app(ssid, user, pass, focus, status);
        unsigned char c = get_key();
        if (c == '\n') {
            if (focus < 3) focus++;
            else {
                status = 1;
                clear();
                draw_wifi_app(ssid, user, pass, focus, status);
                // Aquí se simularía la conexión, o se generaría la config adecuada
                status = 2;
            }
        } else if (c == ' ') {
            focus = (focus + 1) % 4;
        } else if (c == 8) { // Backspace
            if (focus == 0 && pos[0] > 0) ssid[--pos[0]] = 0;
            if (focus == 1 && pos[1] > 0) user[--pos[1]] = 0;
            if (focus == 2 && pos[2] > 0) pass[--pos[2]] = 0;
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '@' || c == '.' || c == '-' || c == '_') {
            if (focus == 0 && pos[0] < 31) { ssid[pos[0]++] = c; ssid[pos[0]] = 0; }
            if (focus == 1 && pos[1] < 31) { user[pos[1]++] = c; user[pos[1]] = 0; }
            if (focus == 2 && pos[2] < 31) { pass[pos[2]++] = c; pass[pos[2]] = 0; }
        }
        if (status == 2) break;
    }
}

void kernel_main() {
    set_video_mode(0x13); // Modo gráfico 320x200x256
    login(); // Pantalla de login
    shell(); // Solo si login correcto
}

// Elimina la dependencia de stdint.h, define tipos básicos si se necesitan
// typedef unsigned int uint32_t; // Descomenta si usas uint32_t