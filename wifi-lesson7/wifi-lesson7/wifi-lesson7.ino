/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Osoyoo W5100 web server lesson 7
 * Send water level data to web browser
 * tutorial url: https://osoyoo.com/?p=10003
 */

#include "WiFiEsp.h"
#include <WiFiEspUdp.h>
#include "SoftwareSerial.h"
SoftwareSerial softserial(4, 5); // D4 to ESP_TX, D5 to ESP_RX by default

char ssid[] = "SKYAE8PJ";            // replace *** with your wifi network SSID (name)
char pass[] = "pWFuffDiDqsn";        // replace *** with your wifi network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned int local_port = 8888;        // local port to listen for UDP packets
unsigned int remote_port = 8888;        // remote port to listen for UDP packets

const int UDP_PACKET_SIZE = 255;  // UDP timestamp is in the first 48 bytes of the message
const int UDP_TIMEOUT = 3000;    // timeout in miliseconds to wait for an UDP packet to arrive

char packetBuffer[255];
const int analogInPin = A0; 
// A UDP instance to let us send and receive packets over UDP
WiFiEspUDP Udp;

void setup()
{
  Serial.begin(9600);   // initialize serial for debugging
  softserial.begin(115200);
  softserial.write("AT+CIOBAUD=9600\r\n");
  softserial.write("AT+RST\r\n");
  softserial.begin(9600);    // initialize serial for ESP module
  WiFi.init(&softserial);    // initialize ESP module

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network, press any key in APP to get sensor value!");
  
  Udp.begin(local_port);
 
}

void loop()
{

  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int sensorValue = analogRead(analogInPin)*100/900; 


    String msg="Water Level: "+String(sensorValue)+'\n';
    Serial.print(msg);
    char ReplyBuffer[60];
    msg.toCharArray(ReplyBuffer,60);
    Serial.println(msg);
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }


    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), 8888);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }

}

 
