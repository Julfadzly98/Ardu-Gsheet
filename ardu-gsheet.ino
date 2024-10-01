#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Einstronic-2.4G";
const char* password = "*Eins1014#";

// Google Forms prefilled link template
String formURL = "https://docs.google.com/forms/d/e/1FAIpQLScN_KgO6oOvbFMPFAlFnWkAU7ZP7MAJYFRiQtah8XQC9RdrMQ/formResponse?usp=pp_url&entry.1894936920={}&entry.2062166182={}&entry.1508627887={}&entry.573509835={}&submit=Submit";

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Simulated sensor values
    float s1 = 0;
    float s2 = 0;
    float s3 = 0;
    float s4 = 0; // 1m - 0.01cm

    // Construct the final URL
    String fullURL = formURL;
    fullURL.replace("{}", String(s1));
    fullURL.replace("{}", String(s2));
    fullURL.replace("{}", String(s3));
    fullURL.replace("{}", String(s4));

    // Send HTTP GET request
    http.begin(fullURL);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("Data submitted successfully!");
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Close connection
  }

  delay(1000);  // Wait for 1 second before next submission
}
