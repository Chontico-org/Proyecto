@echo off
REM Script para compilar y ejecutar en Wokwi - Windows
REM Uso: build_wokwi.bat

setlocal enabledelayedexpansion

echo ====================================
echo Compilador para Wokwi - ESP32
echo ====================================
echo.

REM Verificar si pio está instalado
pio --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: PlatformIO no está instalado o no está en el PATH
    echo Instala PlatformIO desde: https://platformio.org/install
    pause
    exit /b 1
)

echo [1] Limpiar build anterior...
call pio run --target clean -e esp32dev

if errorlevel 1 (
    echo ERROR: Fallo al limpiar el build
    pause
    exit /b 1
)

echo.
echo [2] Compilando proyecto...
call pio run -e esp32dev

if errorlevel 1 (
    echo ERROR: Fallo en la compilación
    echo Verifica los errores arriba
    pause
    exit /b 1
)

echo.
echo ====================================
echo COMPILACIÓN EXITOSA ✓
echo ====================================
echo.
echo El firmware está listo en:
echo   .pio/build/esp32dev/firmware.bin
echo   .pio/build/esp32dev/firmware.elf
echo.
echo Pasos siguientes:
echo 1. Abre https://wokwi.com
echo 2. Carga el archivo diagram.json
echo 3. El firmware se cargará automáticamente
echo.
pause
