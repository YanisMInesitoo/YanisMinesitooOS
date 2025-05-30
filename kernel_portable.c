// kernel_portable.c
// Versión portable: busca carpetas dentro de /sys (ej: /sys/boot, /sys/home, ...)
#include "kernel.c"
// Aquí puedes añadir defines o funciones específicas para la versión portable
// Por ejemplo, rutas base:
#define SYS_BASE "/sys/"
// Definiciones para soporte de rutas según versión (normal o portable)
#ifndef SYS_BASE
#define SYS_BASE "/sys/" // Por defecto, versión portable
#endif
#define SYS_BOOT  SYS_BASE "boot/"
#define SYS_HOME  SYS_BASE "home/"
#define SYS_OPT   SYS_BASE "opt/"
#define SYS_APPS  SYS_BASE "apps/"
#define SYS_DEV   SYS_BASE "dev/"
// ...lógica para usar SYS_BASE en las funciones de acceso a archivos...
