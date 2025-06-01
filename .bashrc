# YanisMinesitoo OS .bashrc
# Añade binarios y utilidades de red al PATH si no están

# Carpetas típicas de binarios en YanisMinesitoo OS
export PATH="$PATH:/dev:/apps:/opt:/sys/dev:/sys/apps:/sys/opt"

# Añadir Java 21 al PATH si está presente
if [ -d "/dev/java/bin" ]; then
  export PATH="$PATH:/dev/java/bin"
fi
if [ -d "/sys/dev/java/bin" ]; then
  export PATH="$PATH:/sys/dev/java/bin"
fi

# Alias útiles para comandos de red y utilidades
alias wget='busybox wget'
alias curl='busybox curl'
alias ping='busybox ping'

# Banner de bienvenida
clear
echo "\e[1;32mBienvenido a YanisMinesitoo OS\e[0m"
echo "\e[1;34mVersión: $([[ -d /sys ]] && echo 'Portable' || echo 'Normal')\e[0m"

# Sugerencia: añade aquí tus alias o funciones personalizadas
# Ejemplo: alias minesitooxd='echo "Gestor de paquetes YanisMinesitoo"'

# Fin de .bashrc
