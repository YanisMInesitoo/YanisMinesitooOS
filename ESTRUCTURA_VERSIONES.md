# 📦 Estructura de YanisMinesitoo OS: Normal vs Portable

## 🖥️ Versión Normal

- El contenido de las carpetas está en la raíz del sistema:
```
/boot    # Archivos de arranque
/home    # Usuarios
/opt     # Programas y herramientas
/apps    # Aplicaciones
/dev     # Dependencias y dispositivos
```

## 💼 Versión Portable

- El ISO va acompañado de la carpeta `sys`:
```
/sys/boot
/sys/home
/sys/opt
/sys/apps
/sys/dev
```

- El sistema detecta automáticamente si está en modo portable (con sys/) o normal (carpetas en raíz).

---

## 📁 Descripción de carpetas
- **boot/**: Archivos de arranque
- **home/**: Usuarios
- **opt/**: Programas y herramientas
- **apps/**: Aplicaciones
- **dev/**: Dependencias y dispositivos

---

¡Ambas versiones soportan la carpeta `dev` para dependencias!
