# 🌟 YanisMinesitoo OS Portable - Estructura de carpetas SYS 🌟

¡Esta es la versión portable de YanisMinesitoo OS! Para funcionar correctamente, necesitas la carpeta `sys` con la siguiente estructura:

```
sys/
├── boot/   # Archivos necesarios para el arranque del sistema operativo
├── home/   # Aquí se crean los usuarios (con adduser <Nickname> <contraseña>)
├── opt/    # Programas adicionales (ej: gbdk, compiladores, herramientas)
└── apps/   # Aplicaciones instaladas por el usuario
y dev/
```

## 📁 Descripción de cada carpeta

- **boot/**: Contiene los archivos de arranque esenciales para que el sistema pueda iniciar correctamente.
- **home/**: Aquí se almacenan los datos de los usuarios. Cada usuario tiene su propia subcarpeta. Se crean con el comando:
  ```
  adduser <Nickname> <contraseña>
  ```
- **opt/**: Espacio para programas y herramientas opcionales, como compiladores, SDKs, etc.
- **apps/**: Carpeta donde se alojan las aplicaciones instaladas por el usuario o el sistema.

## 🚀 ¿Cómo usar la versión portable?
1. Asegúrate de tener la carpeta `sys` con la estructura anterior junto a tu ISO o binario de YanisMinesitoo OS.
2. El sistema detectará y usará estas carpetas automáticamente al arrancar.
3. Puedes añadir usuarios, instalar apps y copiar programas a `opt/` o `apps/` según tus necesidades.

---

¡Disfruta de tu YanisMinesitoo OS portable y flexible y facil de hackear! 😎🖥️
