# Script para compilar y ejecutar en Wokwi - PowerShell
# Uso: .\build_wokwi.ps1

param(
    [switch]$Clean = $false,
    [switch]$Upload = $false
)

Write-Host "====================================" -ForegroundColor Cyan
Write-Host "  Compilador para Wokwi - ESP32" -ForegroundColor Cyan
Write-Host "====================================" -ForegroundColor Cyan
Write-Host ""

# Verificar si pio está instalado
try {
    $pio = pio --version
    Write-Host "✓ PlatformIO encontrado: $pio" -ForegroundColor Green
}
catch {
    Write-Host "✗ ERROR: PlatformIO no está instalado o no está en el PATH" -ForegroundColor Red
    Write-Host "Instala PlatformIO desde: https://platformio.org/install" -ForegroundColor Yellow
    exit 1
}

# Limpiar build anterior si se solicita
if ($Clean) {
    Write-Host "[1] Limpiando build anterior..." -ForegroundColor Yellow
    & pio run --target clean -e esp32dev
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "✗ ERROR: Fallo al limpiar el build" -ForegroundColor Red
        exit 1
    }
    Write-Host "✓ Limpieza completada" -ForegroundColor Green
    Write-Host ""
}

# Compilar proyecto
Write-Host "[2] Compilando proyecto..." -ForegroundColor Yellow
& pio run -e esp32dev

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ ERROR: Fallo en la compilación" -ForegroundColor Red
    Write-Host "Verifica los errores arriba" -ForegroundColor Yellow
    exit 1
}

Write-Host ""
Write-Host "====================================" -ForegroundColor Green
Write-Host "  COMPILACIÓN EXITOSA ✓" -ForegroundColor Green
Write-Host "====================================" -ForegroundColor Green
Write-Host ""

Write-Host "El firmware está listo en:" -ForegroundColor Cyan
Write-Host "  • .pio/build/esp32dev/firmware.bin" -ForegroundColor White
Write-Host "  • .pio/build/esp32dev/firmware.elf" -ForegroundColor White
Write-Host ""

Write-Host "Pasos siguientes:" -ForegroundColor Cyan
Write-Host "  1. Abre https://wokwi.com" -ForegroundColor White
Write-Host "  2. Carga el archivo diagram.json" -ForegroundColor White
Write-Host "  3. El firmware se cargará automáticamente" -ForegroundColor White
Write-Host ""

if ($Upload) {
    Write-Host "[3] Subiendo a placa..." -ForegroundColor Yellow
    & pio run -e esp32dev --target upload
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "✗ ERROR: Fallo al subir el firmware" -ForegroundColor Red
        exit 1
    }
    Write-Host "✓ Firmware subido exitosamente" -ForegroundColor Green
}
