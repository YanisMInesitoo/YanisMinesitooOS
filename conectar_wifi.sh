#!/bin/sh
# conectar_wifi.sh - Conecta a una red WiFi (WPA2-Personal o WPA2-Enterprise 802.1X)
# Uso:
#   ./conectar_wifi.sh <ssid> <password> [usuario]
# Si se indica usuario, se asume WPA2-Enterprise (EAP-PEAP/MSCHAPv2)

if [ $# -lt 2 ]; then
  echo "Uso: $0 <ssid> <password> [usuario]"
  exit 1
fi

SSID="$1"
PASS="$2"
USER="$3"

if [ -z "$USER" ]; then
  # WPA2-Personal
  echo "Generando /tmp/wpa.conf para WPA2-Personal..."
  wpa_passphrase "$SSID" "$PASS" > /tmp/wpa.conf
else
  # WPA2-Enterprise (EAP-PEAP/MSCHAPv2)
  echo "Generando /tmp/wpa.conf para WPA2-Enterprise..."
  cat > /tmp/wpa.conf <<EOF
network={
    ssid=\"$SSID\"
    key_mgmt=WPA-EAP
    eap=PEAP
    identity=\"$USER\"
    password=\"$PASS\"
    phase2=\"auth=MSCHAPV2\"
    # ca_cert=\"/ruta/a/ca.pem\" # Descomenta y ajusta si tu red lo requiere
}
EOF
fi

# Iniciar wpa_supplicant en segundo plano
echo "Conectando con wpa_supplicant..."
wpa_supplicant -B -i wlan0 -c /tmp/wpa.conf

# Obtener IP por DHCP
echo "Obteniendo IP..."
dhclient wlan0 || udhcpc -i wlan0

echo "¡Conexión WiFi intentada! (Verifica si tienes permisos root y los binarios necesarios)"
