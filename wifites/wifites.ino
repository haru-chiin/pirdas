#include <WiFi.h>

const char* ssid1 = "BOYTZY";         // Nama SSID pertama
const char* password1 = "wenakdek";  // Password SSID pertama
// const char* ssid2 = "punyaku";     // Nama SSID kedua

void setup() {
  Serial.begin(9600);
}

void loop() {
    int numNetworks = WiFi.scanNetworks();
  if (WiFi.status() != WL_CONNECTED) {
    // Jika koneksi terputus, coba terhubung ulang ke SSID kedua dan jika sudah terhubung akan berhenti
    connectToWiFi();
  }
}

void connectToWiFi() {
  Serial.print("Mencoba terhubung ke " + String(ssid1) + "...");
  WiFi.begin(ssid1, password1);

  int attempt = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    if (attempt >= 5) {
      break;  // Jika gagal terhubung dalam 5 detik, hentikan percobaan
    }
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" Terhubung ke " + String(ssid1) + "!");
  } else {
    Serial.println(" Gagal terhubung ke " + String(ssid1) + "!");
    Serial.println("Mencari koneksi Wi-Fi tanpa kata sandi...");

    int numNetworks = WiFi.scanNetworks();
    for (int i = 0; i < numNetworks; i++) {
       WiFi.begin(WiFi.SSID(i).c_str());
      // if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
      //   WiFi.begin(ssid.c_str());

      //   // Reset attempt setiap kali mencoba terhubung ke jaringan baru
      //   attempt = 0;
    }
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          Serial.print(".");
          if (attempt >= 5) {
            break;  // Jika gagal terhubung dalam 5 detik, hentikan percobaan
          }
          attempt++;
        }

        if (WiFi.status() == WL_CONNECTED) {
          Serial.println(" Terhubung ke " + WiFi.SSID() + "!");
          // break;
        } else {
          Serial.println(" Gagal terhubung ke " + WiFi.SSID() + "!");
        }
      }
    }


//   // Coba terhubung ke SSID pertama
//   WiFi.begin(ssid1, password1);

//   Serial.print("Mencoba terhubung ke " + String(ssid1) + "...");
//   int attempt = 0;

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//     if (attempt >= 5) {
//       break;  // Jika gagal terhubung dalam 5 detik, hentikan percobaan
//     }
//     attempt++;
//   }

//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println(" Terhubung ke " + String(ssid1) + "!");
//   } else {
//     // Jika gagal terhubung ke SSID pertama, coba terhubung ke SSID kedua
//     Serial.println(" Gagal terhubung ke " + String(ssid1) + "!");
//     // Serial.print("Mencoba terhubung ke " + String(ssid2) + "...");

//     int numNetworks = WiFi.scanNetworks();
//     for (int i = 0; i < numNetworks; i++) {
//       String ssid = WiFi.SSID(i);
//       if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
//         Serial.print("Mencoba terhubung ke " + ssid + "...");
//         WiFi.begin(ssid.c_str());
//         attempt = 0;

//         while (WiFi.status() != WL_CONNECTED) {
//           delay(1000);
//           Serial.print(".");
//           if (attempt >= 5) {
//             break;  // Jika gagal terhubung dalam 5 detik, hentikan percobaan
//           }
//           attempt++;
//         }

//         if (WiFi.status() == WL_CONNECTED) {
//           Serial.println(" Terhubung ke " + ssid + "!");
//           break;
//         } else {
//           Serial.println(" Gagal terhubung ke " + ssid + "!");
//         }
//       }
//     }
//   }
// }