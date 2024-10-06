#include <MPU6050_tockn.h>
#include <Wire.h>
#include <WiFi.h>

int nada[] = {
  0, 523, 587, 659, 698,  783, 880, 987, 1046, 1174,
  1318, 1396, 1567, 1769, 1975, 2093
};

int buzzPin = 18;
MPU6050 mpu6050(Wire);

// const char* ssid = "BOYTZY";
// const char* password = "wenakdek"; // Kata sandi WiFi Anda

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
  pinMode(buzzPin, OUTPUT);

  // connectToWiFi();
}

// void connectToWiFi() {
//   WiFi.begin(ssid);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Menghubungkan ke WiFi...");
//   }

//   Serial.println("Terhubung ke WiFi");
// }

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    mpu6050.update();
  
  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();
  float angleZ = mpu6050.getAngleZ();

  Serial.print("Sudut X: ");
  Serial.println(angleX);

  Serial.print("Sudut Y: ");
  Serial.println(angleY);

  Serial.print("Sudut Z: ");
  Serial.println(angleZ);

  if (angleX > 10) {
    Serial.println("Arah: Kanan");
  } else if (angleX < -10) {
    Serial.println("Arah: Kiri");
  } else if (angleY > 10) {
    Serial.println("Arah: Belakang");
  } else if (angleY < -10) {
    Serial.println("Arah: Depan");
  } else {
    Serial.println("Tidak ada perubahan arah.");
  }
  } else {
    Serial.println("Tidak terhubung ke WiFi, sensor MPU6050 tidak aktif.");
  }
  delay(200);
}


