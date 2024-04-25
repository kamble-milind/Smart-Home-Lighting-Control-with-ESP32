// Include necessary libraries
#define BLYNK_TEMPLATE_ID "TMPL3VrMiEldo"
#define BLYNK_TEMPLATE_NAME "smart home"
#define BLYNK_AUTH_TOKEN "hwr5FHC8jkNl29NyHaW9u99-j8qYAXZ8"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Initialize variables for Blynk authentication and Wi-Fi connection
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "realme narzo 60 5G";
char pass[] = "12345679";

// Initialize Blynk timer for periodic tasks
BlynkTimer timer;

// Define pin assignments for buttons and relays
#define button1_pin 4
#define button2_pin 5
#define relay1_pin 15
#define relay2_pin 2

// Initialize variables to track relay states
int relay1_state = 0;
int relay2_state = 0;

// Define virtual pin numbers for Blynk buttons
#define button1_vpin V1
#define button2_vpin V2

// Function to synchronize button states with Blynk app on connection
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  Blynk.syncVirtual(button2_vpin);
}

// Function to handle button press for relay 1
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}

// Function to handle button press for relay 2
BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}

// Setup function
void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Set button pins as inputs with internal pull-up resistors
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  
  // Set relay pins as outputs
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  
  // Initialize relays to default state (off)
  digitalWrite(relay1_pin, HIGH);
  digitalWrite(relay2_pin, HIGH);
  
  // Connect to Blynk server
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

// Loop function
void loop() {
  // Run Blynk tasks
  Blynk.run();
  timer.run();
  
  // Listen for button presses
  listen_push_buttons();
}

// Function to handle button presses
void listen_push_buttons() {
  // Check if button 1 is pressed
  if (digitalRead(button1_pin) == LOW) {
    delay(200); // Debounce delay
    control_relay(1); // Toggle relay 1
    Blynk.virtualWrite(button1_vpin, relay1_state); // Update Blynk button state
  }
  // Check if button 2 is pressed
  else if (digitalRead(button2_pin) == LOW) {
    delay(200); // Debounce delay
    control_relay(2); // Toggle relay 2
    Blynk.virtualWrite(button2_vpin, relay2_state); // Update Blynk button state
  }
}

// Function to toggle relay states
void control_relay(int relay) {
  if (relay == 1) {
    relay1_state = !relay1_state; // Toggle relay 1 state
    digitalWrite(relay1_pin, relay1_state); // Control relay 1
    delay(50); // Delay for stability
  }
  else if (relay == 2) {
    relay2_state = !relay2_state; // Toggle relay 2 state
    digitalWrite(relay2_pin, relay2_state); // Control relay 2
    delay(50); // Delay for stability
  }
}
