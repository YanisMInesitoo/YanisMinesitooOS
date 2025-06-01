# apps/imgviewer - Visor de imágenes

Este visor de imágenes muestra una imagen PNG en pantalla completa.

## Uso

1. Asegúrate de que el archivo `imagen_png.h` contiene la imagen que deseas mostrar.
2. Compila el visor con un compilador compatible con tu sistema operativo.
3. Ejecuta el visor desde `/apps/imgviewer`.

## Dependencias

- `imagen_png.h`: Archivo que contiene la imagen en formato de matriz de bytes.
- Acceso a memoria de video (modo gráfico 320x200).

## Notas

- Este visor está diseñado para funcionar en modo gráfico VGA (320x200x256 colores).
- Puedes modificar `imagen_png.h` para cambiar la imagen mostrada.