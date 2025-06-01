// kernel_portable.c
// Versión portable: busca carpetas dentro de /sys (ej: /sys/boot, /sys/home, ...)
#define SYS_BASE "/sys/"
#define SYS_BOOT  SYS_BASE "boot/"
#define SYS_HOME  SYS_BASE "home/"
#define SYS_OPT   SYS_BASE "opt/"
#define SYS_APPS  SYS_BASE "apps/"
#define SYS_DEV   SYS_BASE "dev/"
#include "kernel.c"
// Todas las funciones y rutas usan los defines SYS_BASE, SYS_HOME, etc. para máxima compatibilidad.
// Acceso a Internet: asegurado por system() y comandos de red en kernel.c
// Solo cambia la raíz de las carpetas, todo lo demás igual.
