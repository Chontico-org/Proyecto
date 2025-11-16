# Configuración de PlatformIO + Wokwi

## Problema Resuelto ✓

Se ha configurado correctamente el proyecto para que funcione con la simulación en Wokwi.

## Cambios realizados:

### 1. **platformio.ini** - Optimizado para Wokwi
- Agregadas banderas de compilación
- Configuración serial para Wokwi
- Deshabilitadas las líneas RTS/DTR

### 2. **wokwi.toml** - Configuración mejorada
- Puerto serial remoto habilitado (RFC2217)
- Referencias correctas a los binarios del firmware

### 3. **diagram.json** - Ya estaba bien configurado ✓
- Componentes correctamente conectados
- Pines asignados correctamente
- Dependencias incluidas

## Cómo usar:

### Opción 1: Compilar para Wokwi (Recomendado)
```bash
pio run -e esp32dev
```

### Opción 2: Compilar y subir a placa física
```bash
pio run -e esp32dev --target upload
```

### Opción 3: Monitor serial
```bash
pio device monitor -b 115200
```

## Pasos para ejecutar en Wokwi:

1. **Compilar el proyecto primero:**
   ```bash
   pio run -e esp32dev
   ```
   
2. **Abrir la simulación en Wokwi:**
   - Ir a https://wokwi.com
   - Cargar el proyecto desde la carpeta o crear uno nuevo
   - Usar `diagram.json` como referencia

3. **O usar la extensión de Wokwi en VS Code:**
   - Instalar la extensión "Wokwi Simulator"
   - Presionar `F1` y buscar "Wokwi: Start Simulator"

## Verificación de que todo funciona:

- ✓ Pantalla OLED conectada (I2C: SDA=21, SCL=22)
- ✓ Joystick conectado (X=35, Y=34, SW=32)
- ✓ Servos conectados (X=27, Y=26, Z=25)
- ✓ Voltaje correcto para componentes

## Troubleshooting:

Si aún tienes problemas:

1. **Limpia el build:**
   ```bash
   pio run --target clean
   pio run -e esp32dev
   ```

2. **Verifica las dependencias:**
   ```bash
   pio lib list
   ```

3. **Reconstruye todas las librerías:**
   ```bash
   pio run -e esp32dev --target uploadfs
   ```

4. **Reinicia PlatformIO:**
   - Cierra VS Code completamente
   - Abre de nuevo el proyecto
   - Ejecuta el build nuevamente

## Proyecto configurado con:
- **Placa:** ESP32 Dev Module
- **Framework:** Arduino
- **Velocidad serial:** 115200 baud
- **IDE:** PlatformIO + VS Code
- **Simulador:** Wokwi
