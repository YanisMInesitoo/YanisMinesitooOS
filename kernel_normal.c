// kernel_normal.c
// Versión normal: busca carpetas en la raíz (ej: /boot, /home, ...)
#define SYS_BASE "/"
#define SYS_BOOT  SYS_BASE "boot/"
#define SYS_HOME  SYS_BASE "home/"
#define SYS_OPT   SYS_BASE "opt/"
#define SYS_APPS  SYS_BASE "apps/"
#define SYS_DEV   SYS_BASE "dev/"
#include "kernel.c"
// Todas las funciones y rutas usan los defines SYS_BASE, SYS_HOME, etc. para máxima compatibilidad.
// Acceso a Internet: asegurado por system() y comandos de red en kernel.c
// No hay funciones exclusivas, todo igual que kernel.c excepto rutas base.
