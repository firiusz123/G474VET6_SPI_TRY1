#include <EtherCard.h>
#include <IPAddress.h>
#include <SPI.h>

char payload[] = "PONGGG";
uint8_t ipDestinationAddress[IP_LEN];
char receivedData[50];
const int slaveSelectPin1 = 9; // SS pin of Arduino connected to NSS/CS pin of STM32
const int slaveSelectPin2 = 10; // SS pin of Arduino connected to NSS/CS pin of enc28j60
char txMsg[50];
char rxMsg[50];

#define STATIC 0  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// Ethernet interface IP address
static byte myip[] = { 192, 168, 1, 200 };
// Gateway IP address
static byte gwip[] = { 192, 168, 1, 1 };
#endif

// Ethernet MAC address - must be unique on your network
static byte mymac[] = { 0x70, 0x69, 0x69, 0x2D, 0x30, 0x31 };

byte Ethernet::buffer[500]; // TCP/IP send and receive buffer

void STMsendReceive(char *txMsg) {
  int index = 0;
  char last_sent = '\0';
  
  // Send all bytes of txMsg to STM32
  digitalWrite(slaveSelectPin1, LOW);
  for (int i = 0; txMsg[i] != '\0'; i++) {
    delay(1);
    SPI.transfer(txMsg[i]);
  }
  digitalWrite(slaveSelectPin1, HIGH);

  delay(10);

  // Now receive bytes from STM32 until the terminator '$' is encountered
  digitalWrite(slaveSelectPin1, LOW);
  while (1 ) {
    delay(1);
    char receivedChar = SPI.transfer(0x00); // Send dummy byte to receive data
    
    if (receivedChar != '\0' && receivedChar != last_sent) { // Only add non-empty bytes to rxMsg
      rxMsg[index++] = receivedChar;
      Serial.println("znak pierwszy    " +  String(receivedChar));
      Serial.println("znak ostatni     " + String(last_sent));
    }
    if (receivedChar == '$' ) {
      break;
    }
    last_sent = receivedChar;
  }
  digitalWrite(slaveSelectPin1, HIGH);
  
  // Null-terminate the received message
}
// Callback that prints received packets to the serial port
void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len) {
  IPAddress src(src_ip[0], src_ip[1], src_ip[2], src_ip[3]);

  Serial.print("Received from ");
  ether.printIp(src_ip);
  Serial.print(":");
  Serial.print(src_port);
  Serial.print(" - ");
  Serial.println(data);
  strcpy(receivedData, data);

  // Send received data to STM32 and wait for response
  STMsendReceive(receivedData);

  // Print the response from STM32
  Serial.print("Received from STM32: ");
  Serial.println(rxMsg);
  

  // Send the response from STM32 back via UDP
  ether.sendUdp(rxMsg, strlen(rxMsg), 1337, src_ip, src_port);
  memset(rxMsg, 0, sizeof(rxMsg));
  memset(txMsg, 0, sizeof(txMsg));
}

void setup() {
  Serial.begin(57600);
  pinMode(slaveSelectPin1, OUTPUT);
  digitalWrite(slaveSelectPin1, HIGH);
  pinMode(slaveSelectPin2, OUTPUT);
  digitalWrite(slaveSelectPin2, HIGH);                                                                             
  
  Serial.println(F("\n[backSoon]"));
  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
    Serial.println(F("Failed to access Ethernet controller"));

  #if STATIC
    ether.staticSetup(myip, gwip);
  #else
    if (!ether.dhcpSetup())
      Serial.println(F("DHCP failed"));
  #endif

  ether.parseIp(ipDestinationAddress, "192.168.1.100");
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  ether.udpServerListenOnPort(&udpSerialPrint, 1337);
}

void loop() {
  ether.packetLoop(ether.packetReceive());
}
