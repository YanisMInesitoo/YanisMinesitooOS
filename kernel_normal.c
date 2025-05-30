// kernel_normal.c
// Versión normal: busca carpetas en la raíz (ej: /boot, /home, ...)
#include "kernel.c"
// Aquí puedes añadir defines o funciones específicas para la versión normal
#define SYS_BASE "/"
// Definiciones para soporte de rutas según versión (normal o portable)
#ifndef SYS_BASE
#define SYS_BASE "/" // Por defecto, versión normal
#endif
#define SYS_BOOT  SYS_BASE "boot/"
#define SYS_HOME  SYS_BASE "home/"
#define SYS_OPT   SYS_BASE "opt/"
#define SYS_APPS  SYS_BASE "apps/"
#define SYS_DEV   SYS_BASE "dev/"
// ...lógica para usar SYS_BASE en las funciones de acceso a archivos...
