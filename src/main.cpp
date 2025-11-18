#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <Wire.h>

// ============================================
// CONFIGURACIÓN DE PINES
// ============================================
#define PIN_SDA 21
#define PIN_SCL 22

// Pines de Servos
#define SERVO_X 27    // Servo para movimiento izquierda/derecha
#define SERVO_Y 26    // Servo para movimiento arriba/abajo
#define SERVO_Z 25    // Servo para movimiento adicional (botón)

// Pines del Joystick
#define JOY_X 34      // Eje X del joystick (izquierda/derecha)
#define JOY_Y 35      // Eje Y del joystick (arriba/abajo)
#define JOY_SW 32     // Botón del joystick

// ============================================
// CONFIGURACIÓN PANTALLA OLED
// ============================================
#define ANCHO 128
#define ALTO 64
#define OLED_RESET -1
Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, OLED_RESET);

// ============================================
// OBJETOS DE SERVOS
// ============================================
Servo servoX;
Servo servoY;
Servo servoZ;

// ============================================
// VARIABLES GLOBALES
// ============================================
int anguloX = 90;
int anguloY = 90;
int anguloZ = 90;
String movimiento = "Neutral";

// Umbrales para detectar movimiento del joystick
#define UMBRAL_MINIMO 1500
#define UMBRAL_MAXIMO 2500

// ============================================
// PROTOTIPOS DE FUNCIONES
// ============================================
void determinaMovimiento(int xValue, int yValue, int swValue);
void controlarServos(int xValue, int yValue, int swValue);
void mostrarPantalla();
void dibujarBarraAngulo(int angulo, int posY);

// ============================================
// SETUP - Se ejecuta una sola vez
// ============================================
void setup() {
  Serial.begin(115200);
  
  // Inicializar servos
  servoX.attach(SERVO_X);
  servoY.attach(SERVO_Y);
  servoZ.attach(SERVO_Z);
  
  // Posiciones iniciales
  servoX.write(90);
  servoY.write(90);
  servoZ.write(90);
  
  // Inicializar pantalla OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error en pantalla OLED");
    while(1);
  }
  
  // Mostrar pantalla de bienvenida
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("Brazo Robot");
  display.setCursor(15, 45);
  display.setTextSize(1);
  display.println("Listo!");
  display.display();
  
  // Configurar botón del joystick
  pinMode(JOY_SW, INPUT_PULLUP);
  delay(2000);
}

// ============================================
// LOOP - Se ejecuta continuamente
// ============================================
void loop() {
  // Leer valores del joystick
  int xValue = analogRead(JOY_X);
  int yValue = analogRead(JOY_Y);
  int swValue = digitalRead(JOY_SW);
  
  // Determinar dirección del movimiento
  determinaMovimiento(xValue, yValue, swValue);
  
  // Controlar servos basado en el movimiento
  controlarServos(xValue, yValue, swValue);
  
  // Mostrar información en pantalla
  mostrarPantalla();
  
  delay(100);
}

// ============================================
// FUNCIÓN: Determinar movimiento del joystick
// ============================================
void determinaMovimiento(int xValue, int yValue, int swValue) {
  // EDITA AQUÍ: Modifica la lógica de detección de movimiento
  
  if (swValue == LOW) {
    movimiento = "AGARRANDO";
  }
  else if (yValue > UMBRAL_MAXIMO) {
    movimiento = "ARRIBA";
  }
  else if (yValue < UMBRAL_MINIMO) {
    movimiento = "ABAJO";
  }
  else if (xValue > UMBRAL_MAXIMO) {
    movimiento = "DERECHA";
  }
  else if (xValue < UMBRAL_MINIMO) {
    movimiento = "IZQUIERDA";
  }
  else {
    movimiento = "NEUTRAL";
  }
}

// ============================================
// FUNCIÓN: Controlar servos
// ============================================
void controlarServos(int xValue, int yValue, int swValue) {
  // Solo mover servos si el joystick pasa los umbrales
  if (xValue < UMBRAL_MINIMO) {
    anguloX = 0; // Izquierda
  } else if (xValue > UMBRAL_MAXIMO) {
    anguloX = 180; // Derecha
  } else {
    anguloX = 90; // Centro
  }

  if (yValue < UMBRAL_MINIMO) {
    anguloY = 0; // Abajo
  } else if (yValue > UMBRAL_MAXIMO) {
    anguloY = 180; // Arriba
  } else {
    anguloY = 90; // Centro
  }

  servoX.write(anguloX);
  servoY.write(anguloY);

  // Servo Z: se controla con el botón del joystick
  if (swValue == LOW) {
    anguloZ = 45;   // Cerrar (agarrar)
    servoZ.write(45);
  } else {
    anguloZ = 135;  // Abrir (soltar)
    servoZ.write(135);
  }
}

// ============================================
// FUNCIÓN: Mostrar información en pantalla
// ============================================
void mostrarPantalla() {
  // EDITA AQUÍ: Modifica qué se muestra en la pantalla OLED
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Título
  display.setCursor(25, 0);
  display.println("BRAZO ROBOT 2.0");
  
  // Línea divisoria
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
  
  // Movimiento actual
  display.setCursor(0, 13);
  display.print("Dir: ");
  display.println(movimiento);
  
  // Ángulos de servos en grande
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.print("X:");
  display.print(anguloX);
  display.print("  Y:");
  display.print(anguloY);
  display.print("  Z:");
  display.println(anguloZ);
  
  // Barra visual para ServoX
  display.setCursor(0, 35);
  display.println("Servo X:");
  dibujarBarraAngulo(anguloX, 41);
  
  // Barra visual para ServoY
  display.setCursor(0, 52);
  display.println("Servo Y:");
  dibujarBarraAngulo(anguloY, 58);
  
  display.display();
}

// ============================================
// FUNCIÓN: Dibujar barra de ángulo
// ============================================
void dibujarBarraAngulo(int angulo, int posY) {
  // EDITA AQUÍ: Modifica la visualización de las barras
  
  // Dibuja una barra que va de 0 a 180 grados
  int posicion = map(angulo, 0, 180, 0, 80);
  
  // Dibuja el rectángulo vacío
  display.drawRect(40, posY, 82, 6, SSD1306_WHITE);
  
  // Dibuja el rectángulo lleno (barra de progreso)
  display.fillRect(41, posY + 1, posicion, 4, SSD1306_WHITE);
}
