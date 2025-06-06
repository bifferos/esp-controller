/*
  A UDP controlled switch.  Raises the RX pin high or low depending on the state returned from a remote UDP server

  On the ESP-01 The RX is the only GPIO pin without strings attached
  TX - Spews bootloader stuff on power up, GPIOs need to be in a certain state for boot, etc...
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "/home/biff/.wifi_credentials"
/* 
$ cat /home/biff/.wifi_credentials
#define CRED_SSID     "your_ssid"
#define CRED_PASSWORD "your_password"
*/

// Target IP and port
const char* udpAddress = "172.16.16.51";  
const int udpTxPort = 6060;

// The file to query, if present, state is considered true, otherwise false.
#define QUERY_STRING "output-state"


WiFiUDP udp;

char rx_buffer[256];
bool output_state = false;
unsigned long last_poll;

#define RX_PIN 3  // GPIO3 - normally RX


void sendPacket()
{
  udp.beginPacket(udpAddress, udpTxPort);
  udp.print(QUERY_STRING);
  udp.endPacket();
  Serial.println("UDP sent");
}


void updateStatus()
{

  int packetSize = udp.parsePacket();
  if (!packetSize)
  {
    return;
  }
  Serial.println("Received packet");
  if (packetSize < sizeof(rx_buffer)) {
    int len = udp.read(rx_buffer, sizeof(rx_buffer) - 1);
    rx_buffer[len] = 0;

    if (strcmp(rx_buffer, "true") == 0)
    {
      output_state = true;
      Serial.println(rx_buffer);
    }
    else if (strcmp(rx_buffer, "false") == 0)
    {
      output_state = false;
      Serial.println(rx_buffer);
    }
    else
    {
      Serial.print("Invalid response: '");
      Serial.print(rx_buffer);
      Serial.println("'");
    }

    // Clear any remaining data, in case of jumbo packet?
    while (udp.available()) {
      udp.read(); // Read one byte at a time and discard
    }
  }
}


void setup()
{
  pinMode(RX_PIN, OUTPUT);   // RX as output
  digitalWrite(RX_PIN, LOW);

  Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);
  Serial.println("");
  Serial.println("setup()");
  WiFi.mode(WIFI_STA);

  WiFi.begin(CRED_SSID, CRED_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // assigns random src port.  Confusingly a local port is always assigned
  // whether this line is here or not, however you won't receive anything
  // on that port unless you call begin explicitly.
  udp.begin(0);

  Serial.println(WiFi.localIP());

  last_poll = millis();
}


void loop()
{
  if (output_state)
  {
    digitalWrite(RX_PIN, HIGH);
  }
  else
  {
    digitalWrite(RX_PIN, LOW);
  }

  updateStatus();

  unsigned long time_now = millis();
  if ((time_now - last_poll) > 5000)
  {
    last_poll = time_now;
    sendPacket();
  }
}

