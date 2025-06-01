@echo off
REM build_auto.bat - Compila YanisMinesitoo OS automáticamente (normal y portable)

REM Detectar si x86_64-elf-gcc está en el PATH
where x86_64-elf-gcc >nul 2>nul
if errorlevel 1 (
    echo [ERROR] No se encontró x86_64-elf-gcc en el PATH.
    echo Descarga e instala un toolchain cruzado (ver instrucciones en README.md).
    pause
    exit /b 1
)

REM Compilar versión normal
call build_normal.bat
if errorlevel 1 (
    echo [ERROR] Falló la compilación de la versión normal.
    pause
    exit /b 1
)

REM Compilar versión portable
call build_portable.bat
if errorlevel 1 (
    echo [ERROR] Falló la compilación de la versión portable.
    pause
    exit /b 1
)

echo.
echo Compilación completada para ambas versiones.
pause
