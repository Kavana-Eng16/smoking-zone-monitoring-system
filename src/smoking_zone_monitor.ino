#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -------------------- Pin Configuration --------------------
const int MQ2_PIN = A0;   // MQ-2 analog output to Arduino A0
const int BUZZER  = 7;    // Buzzer positive leg to D7

int smokeValue = 0;       // current sensor reading
int threshold  = 812;     // adjust after calibration in clean air

// LCD object (I2C address, columns, rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);
  pinMode(MQ2_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Smoke Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);

  lcd.clear();
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();

  Serial.println("Automated Smoking Zone Monitoring Started...");
  Serial.println("------------------------------------------");
}

// -------------------- Main Loop --------------------
void loop() {
  smokeValue = analogRead(MQ2_PIN);

  Serial.print("Smoke Level: ");
  Serial.println(smokeValue);

  lcd.setCursor(0, 0);
  lcd.print("Smoke:");
  lcd.setCursor(7, 0);
  lcd.print(smokeValue);
  lcd.print("    ");               // clear trailing digits

  if (smokeValue >= threshold) {
    // ---- Alert Mode ----
    digitalWrite(BUZZER, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("SMOKE DETECTED! "); // exactly 16 characters
    Serial.println("Smoking Detected!");
  } else {
    // ---- Normal Mode ----
    digitalWrite(BUZZER, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: Normal  "); // exactly 16 characters
  }

  delay(500);
}
