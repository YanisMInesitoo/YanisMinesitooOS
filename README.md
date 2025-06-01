# 🚀 YanisMinesitoo OS 👾

¡Bienvenido a **YanisMinesitoo OS**! Un sistema operativo hecho desde cero, con login gráfico, fondo personalizado y utilidades de consola. 🖥️✨

---

## 🛠️ Compilación y Uso

1. **Requisitos**
   - 🪟 Windows + [MSYS2 MinGW 64-bit](https://www.msys2.org/)
   - 🧰 Paquetes: `gcc`, `binutils`, `nasm`, `make`, `qemu`, `grub`

2. **Instalación de dependencias**
   ```sh
   pacman -Syu --noconfirm
   pacman -S --needed --noconfirm mingw-w64-x86_64-binutils mingw-w64-x86_64-gcc mingw-w64-x86_64-nasm mingw-w64-x86_64-make mingw-w64-x86_64-qemu mingw-w64-x86_64-grub
   ```

3. **Compilar y generar la ISO**
   ```sh
   ./build.sh
   # o
   make
   ```
   📦 La ISO se generará en `build/YanisMinesitooOS.iso`

4. **Probar en QEMU**
   ```sh
   qemu-system-x86_64 -cdrom build/YanisMinesitooOS.iso
   ```

---

## 🖼️ Personaliza tu fondo de pantalla

1. Pon tu imagen PNG en la carpeta del proyecto (ej: `Nombre de usuario.png`).
2. Convierte la imagen a C:
   ```sh
   xxd -i "Nombre de usuario.png" > imagen_png.h
   ```
3. ¡Recompila y disfruta tu login gráfico! 🎨

---

## 🔑 Pantalla de Login
- Fondo gráfico PNG
- Input de usuario y contraseña
- Botón de "Iniciar sesión" 🟩
- Validación de usuario y contraseña (por defecto: `admin` / `1234`)

---

## 💻 Utilidades disponibles
- Shell interactiva 🐚
- Editor nano ✍️
- Descargas: wget, curl 🌐
- Compresión: tar, gzip 📦
- Gestor de paquetes simulado 🛒
- Listado de procesos y archivos 📄

---

## 📡 Conexión a WiFi

- Para conectarse a WiFi desde la shell, use:

  ```sh
  wifi <ssid> <password>
  ```
  Esto mostrará los comandos necesarios para conectar usando wpa_supplicant y dhclient (o udhcpc). También puedes usar el script `conectar_wifi.sh`:

  ```sh
  ./conectar_wifi.sh <ssid> <password>
  ```
  Requiere los binarios: `wpa_supplicant`, `wpa_passphrase`, `dhclient` o `busybox udhcpc`, y permisos de root.

- Si usas la versión portable, asegúrate de que los binarios estén en `/sys/dev` o en el PATH.

- Para redes WiFi empresariales (802.1X, WPA2-Enterprise):
  - Usa el comando:
    ```sh
    ./conectar_wifi.sh <ssid> <password> <usuario>
    ```
  - El script generará la configuración adecuada para wpa_supplicant (EAP-PEAP/MSCHAPv2).
  - Si tu red requiere certificado CA, edita `/tmp/wpa.conf` y descomenta la línea `ca_cert`.

- En la app gráfica (wifi-ui), si introduces usuario, se asume red 802.1X.

---

## ☕️ Java 21

- Puedes ejecutar programas Java si copias el binario de OpenJDK 21 en `/dev/java` o `/sys/dev/java`.
- El sistema añade automáticamente el path de Java si detecta la carpeta.
- Descarga OpenJDK 21 desde: https://jdk.java.net/21/

---

## 📂 Estructura del proyecto
```
YanisMinesitooOS/
├── kernel.c
├── kernel_entry.asm
├── linker.ld
├── build.sh
├── Makefile
├── grub.cfg
├── imagen_png.h
├── ...
```

---

## 🧑‍💻 Créditos
- Hecho por Yanis 💙
- Inspirado en proyectos open source y la comunidad OSDev 🌍

---

## 🦾 ¡Disfruta hackeando tu propio sistema operativo! 🦾

> Si tienes dudas, abre un issue o contacta al autor. ¡Feliz hacking! 😎
