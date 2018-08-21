#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define println Serial.println
#define print   Serial.print

byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

// instances
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
IPAddress ip(192, 168, 0, 100);
IPAddress server(192, 168, 0, 101);

EthernetClient ethClient;
PubSubClient client(ethClient);


void setup() {
  Serial.begin(9600);
  detectFingerPrint();
  finger.begin(57600);

  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  delay(1500);
  
  fingerprintSensor();
  finger.getTemplateCount();
}

void loop() {
  int id = getFingerprintIDez();

  if (id != -1) {
    print("ID: "); println(id);
    if (!client.connected()) {
      reconnect();
    }
     client.publish("fingerprint/receive", String(id).c_str());
  }
  delay(50);   
}
