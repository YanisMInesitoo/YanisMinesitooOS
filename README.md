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
