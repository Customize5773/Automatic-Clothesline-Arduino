#include <DHT.h>
#include <Stepper.h>

// === CONFIGURABLE PARAMETERS ===
#define DHT_PIN          2
#define DHT_TYPE         DHT11
#define RAIN_SENSOR_PIN  A0
#define HUMIDITY_THRESHOLD 85        // % Relative Humidity
#define RAIN_THRESHOLD   500         // Analog value from YL-83 sensor
#define MOTOR_STEPS      2048        // Steps for full revolution (28BYJ-48)
#define MOTOR_SPEED      10          // RPM
#define OPERATION_STEPS  1024        // Steps per operation (half revolution)
#define DEBOUNCE_COUNT   3           // Number of consistent rain readings

// === MOTOR PIN CONFIGURATION ===
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// === SYSTEM STATES ===
enum ClotheslineState { EXTENDED, RETRACTED };

// === GLOBAL OBJECTS & VARIABLES ===
DHT dht(DHT_PIN, DHT_TYPE);
Stepper stepper(MOTOR_STEPS, IN1, IN2, IN3, IN4);

ClotheslineState currentState = EXTENDED;
unsigned long lastMotorAction = 0;
int rainDebounceCounter = 0;

// === FUNCTION PROTOTYPES ===
void initializeHardware();
bool isRainDetected();
float readHumidity();
void extendClothesline();
void retractClothesline();
void updateSystem();

void setup() {
  initializeHardware();
}

void loop() {
  updateSystem();
  delay(2000); // Main loop delay
}

// === FUNCTION IMPLEMENTATIONS ===

void initializeHardware() {
  Serial.begin(9600);
  dht.begin();
  stepper.setSpeed(MOTOR_SPEED);
  pinMode(RAIN_SENSOR_PIN, INPUT);

  Serial.println("Automatic Clothesline Initialized.");
}

float readHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read humidity from DHT11");
    return -1;
  }
  return h;
}

bool isRainDetected() {
  int rainValue = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Rain Sensor Reading: ");
  Serial.println(rainValue);

  if (rainValue < RAIN_THRESHOLD) {
    rainDebounceCounter = min(rainDebounceCounter + 1, DEBOUNCE_COUNT);
  } else {
    rainDebounceCounter = max(rainDebounceCounter - 1, 0);
  }

  return (rainDebounceCounter >= DEBOUNCE_COUNT);
}

void extendClothesline() {
  if (currentState == EXTENDED) return;

  Serial.println("Extending clothesline...");
  stepper.step(-OPERATION_STEPS); // Negative for extending
  currentState = EXTENDED;
  Serial.println("Clothesline extended.");
}

void retractClothesline() {
  if (currentState == RETRACTED) return;

  Serial.println("Retracting clothesline...");
  stepper.step(OPERATION_STEPS); // Positive for retracting
  currentState = RETRACTED;
  Serial.println("Clothesline retracted.");
}

void updateSystem() {
  float humidity = readHumidity();
  bool raining = isRainDetected();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% - ");
  Serial.println(raining ? "Rain Detected" : "No Rain");

  if (humidity == -1) {
    Serial.println("Skipping humidity check due to sensor error");
  }

  if (raining || (humidity > HUMIDITY_THRESHOLD && humidity != -1)) {
    retractClothesline();
  } else {
    extendClothesline();
  }
}
