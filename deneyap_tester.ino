/*
 * Runs test scenarios according to inputs coming from serial channel
 * state 0: Ready to test
 * state 1: Setup RGB Test
 * state 2: Run RGB Test
 * state 3: Run button Test
 * state 4: Run Gpio Test
 * state 5: Run mic Test
 * state 6: Run Gyro Test
 * state 7: Run Accelometer Test
 * state 8: Run Tempature Test
 * state 9: Run DAC Test
 * state 10: Wait
 */

#include "mp34dt05.h"
#include "lsm6dsm.h"
 
#define BUTON GPKEY
#define ANALOG_TEST_PIN A3
#define DIGITAL_TEST_PIN D14
#define BUTTON_2_TEST_PIN D13
#define DAC_TEST_PIN DAC2

LSM6DSM IMU;

int state = 0;
const uint16_t LED_delay_time = 1000;
const uint16_t IMU_delay_time = 100;
const uint16_t analog_write_value = 100; // 0-255
int samples[BUFFER_SIZE];
FilterBeHp2 filter;
size_t num_bytes_read = 0;


void setup() {
  Serial.begin(9600);
//  setup_test_LED();
  pinMode(BUTON, INPUT);
  pinMode(ANALOG_TEST_PIN, INPUT);
  pinMode(DIGITAL_TEST_PIN, OUTPUT);
  pinMode(BUTTON_2_TEST_PIN, INPUT);
//  pinMode(DAC_TEST_PIN, INPUT);
  micBegin();
  IMU.begin();
}

void loop() {
  switch (state) {
    case 0:
      if (!Serial) {
        Serial.begin(9600);
      }
      delay(100);
      while(Serial.availableForWrite() == 0);
      Serial.printf("Welcome to the Deneyap Kart test interface\nchoose the test desired to be performed\n0 - Be ready\n1 - Setup RGB\n2 - Run RGB\n3 - Run button\n4 - Run GPIO\n5 - Run mic\n6 - Run Gyro\n7 - Run Accel\n8 - Run Temp\n10 - Wait", state);
      Serial.flush();
      state = 10;
      break;
      
    case 1:
      while(Serial.availableForWrite() == 0);
      Serial.flush();
      setup_test_LED();
      state = 2;
      break;
      
    case 2:
      
      test_LED();
      break;
      
    case 3:
      Serial.flush();
      while(Serial.availableForWrite() == 0);
      Serial.printf("%d\n", digitalRead(BUTTON_2_TEST_PIN));
//      Serial.printf("%d\n", !digitalRead(BUTON));
      Serial.flush();
      break;
      
    case 4:
      digitalWrite(DIGITAL_TEST_PIN, HIGH);
      delay(100);
      while(Serial.availableForWrite() == 0);
      Serial.printf("%d\n", analogRead(ANALOG_TEST_PIN));
      Serial.flush();
      break;
      
    case 5:
      micRead(&num_bytes_read, samples);
      if (num_bytes_read > 0) {
        int data = dataFilter(filter, num_bytes_read, samples);
        Serial.flush();
        Serial.println(data);
      }
      break;
      
    case 6:
      Serial.printf("%.2f,%.2f,%.2f\n", IMU.readFloatGyroX(), IMU.readFloatGyroY(),IMU.readFloatGyroZ());
      delay(IMU_delay_time);
      break;
      
    case 7:
      Serial.printf("%.2f,%.2f,%.2f\n", IMU.readFloatAccelX(), IMU.readFloatAccelY(),IMU.readFloatAccelZ());
      delay(IMU_delay_time);
      break;
      
    case 8:
      Serial.println(IMU.readTempC());
      delay(IMU_delay_time);
      break;

    case 9:
      analogWrite(DAC_TEST_PIN, analog_write_value);
      delay(100);
      while(Serial.availableForWrite() == 0);
      Serial.printf("%d\n", analogRead(ANALOG_TEST_PIN));
      Serial.flush();
      break;
       
    case 10:
      break;
    
    default:
      Serial.println("ERROR");
      break;
  }
  if (Serial.available()) {
     state = Serial.parseInt();
  }
  delay(500);
}

//*******************************   LED TEST   *****************************
void setup_test_LED() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void finish_test_LED() {
  pinMode(LEDR, INPUT);
  pinMode(LEDG, INPUT);
  pinMode(LEDB, INPUT);
}

void test_LED() {
//  // white
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  delay(LED_delay_time);
//
//  // red
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(LED_delay_time);
//
//  // green
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
  delay(LED_delay_time);

  // blue
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
  delay(LED_delay_time);

//  // cyan
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  delay(LED_delay_time);
//
//  // magenta
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
  delay(LED_delay_time);
//
//  // yellow
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
  delay(LED_delay_time);

  // no color
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(LED_delay_time);
}
//*****************************************************************************
