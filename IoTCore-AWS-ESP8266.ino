#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson (use v6.xx)
#include <time.h>
#define emptyString String()
#include <DHT.h> //Inclui a biblioteca DHT Sensor Library
#define DHTPIN 5 //Pino digital 5 (pino D1) conectado ao DHT11
#define DHTTYPE DHT11 //DHT 11

//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)
DHT dht(DHTPIN, DHTTYPE); 

//define variaveis
float  vlTemperatura;
float  vlUmidade;
double dbDelay = 1000;

//instruções de preenchimento em https://github.com/salmarcelo/AWS-IoT-Core-com-Arduino-ESP8622-/blob/main/README.md
//Enter values in secrets.h ▼
#include "secrets.h"

#if !(ARDUINOJSON_VERSION_MAJOR == 6 and ARDUINOJSON_VERSION_MINOR >= 7)
#error "Install ArduinoJson v6.7.0-beta or higher"
#endif

//Informa os shadows de Publish e Subscribe
const int MQTT_PORT = 8883;
const char MQTT_SUB_TOPIC[] = "$aws/things/XXXXXXXX/shadow/name/sensor/get";
const char MQTT_PUB_TOPIC[] = "$aws/things/XXXXXXXX/shadow/name/sensor";

//utilização de horário de verão
#ifdef USE_SUMMER_TIME_DST
uint8_t DST = 1;
#else
uint8_t DST = 0;
#endif

WiFiClientSecure net;

// utilização dos certificados que constam no arquivo secrets.h
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

#include <MQTT.h>
MQTTClient client;

unsigned long lastMillis = 0;
time_t now;
time_t nowish = 1510592825;

void NTPConnect(void)
{
  Serial.print("Configurando Horário: ");
  configTime(TIME_ZONE * 3600, DST * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("Concluído!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Horário: ");
  Serial.print(asctime(&timeinfo));
}

#ifdef USE_PUB_SUB

void messageReceivedPubSub(char *topic, byte *payload, unsigned int length)
{
  Serial.print(" Recebido [");
  Serial.print(topic);
  Serial.println("]: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void pubSubErr(int8_t MQTTErr)
{
  if (MQTTErr == MQTT_CONNECTION_TIMEOUT)
    Serial.print("Connection tiemout");
  else if (MQTTErr == MQTT_CONNECTION_LOST)
    Serial.print("Connection lost");
  else if (MQTTErr == MQTT_CONNECT_FAILED)
    Serial.print("Connect failed");
  else if (MQTTErr == MQTT_DISCONNECTED)
    Serial.print("Disconnected");
  else if (MQTTErr == MQTT_CONNECTED)
    Serial.print("Connected");
  else if (MQTTErr == MQTT_CONNECT_BAD_PROTOCOL)
    Serial.print("Connect bad protocol");
  else if (MQTTErr == MQTT_CONNECT_BAD_CLIENT_ID)
    Serial.print("Connect bad Client-ID");
  else if (MQTTErr == MQTT_CONNECT_UNAVAILABLE)
    Serial.print("Connect unavailable");
  else if (MQTTErr == MQTT_CONNECT_BAD_CREDENTIALS)
    Serial.print("Connect bad credentials");
  else if (MQTTErr == MQTT_CONNECT_UNAUTHORIZED)
    Serial.print("Connect unauthorized");
}

#else

void messageReceived(String &topic, String &payload)
{
  Serial.println(" Recebido [" + topic + "]:");
  Serial.println(payload);
}

void lwMQTTErr(lwmqtt_err_t reason)
{
  if (reason == lwmqtt_err_t::LWMQTT_SUCCESS)
    Serial.print("Success");
  else if (reason == lwmqtt_err_t::LWMQTT_BUFFER_TOO_SHORT)
    Serial.print("Buffer too short");
  else if (reason == lwmqtt_err_t::LWMQTT_VARNUM_OVERFLOW)
    Serial.print("Varnum overflow");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_CONNECT)
    Serial.print("Network failed connect");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_TIMEOUT)
    Serial.print("Network timeout");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_READ)
    Serial.print("Network failed read");
  else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_WRITE)
    Serial.print("Network failed write");
  else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_OVERFLOW)
    Serial.print("Remaining length overflow");
  else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_MISMATCH)
    Serial.print("Remaining length mismatch");
  else if (reason == lwmqtt_err_t::LWMQTT_MISSING_OR_WRONG_PACKET)
    Serial.print("Missing or wrong packet");
  else if (reason == lwmqtt_err_t::LWMQTT_CONNECTION_DENIED)
    Serial.print("Connection denied");
  else if (reason == lwmqtt_err_t::LWMQTT_FAILED_SUBSCRIPTION)
    Serial.print("Failed subscription");
  else if (reason == lwmqtt_err_t::LWMQTT_SUBACK_ARRAY_OVERFLOW)
    Serial.print("Suback array overflow");
  else if (reason == lwmqtt_err_t::LWMQTT_PONG_TIMEOUT)
    Serial.print("Pong timeout");
}

void lwMQTTErrConnection(lwmqtt_return_code_t reason)
{
  if (reason == lwmqtt_return_code_t::LWMQTT_CONNECTION_ACCEPTED)
    Serial.print("Connection Accepted");
  else if (reason == lwmqtt_return_code_t::LWMQTT_UNACCEPTABLE_PROTOCOL)
    Serial.print("Unacceptable Protocol");
  else if (reason == lwmqtt_return_code_t::LWMQTT_IDENTIFIER_REJECTED)
    Serial.print("Identifier Rejected");
  else if (reason == lwmqtt_return_code_t::LWMQTT_SERVER_UNAVAILABLE)
    Serial.print("Server Unavailable");
  else if (reason == lwmqtt_return_code_t::LWMQTT_BAD_USERNAME_OR_PASSWORD)
    Serial.print("Bad UserName/Password");
  else if (reason == lwmqtt_return_code_t::LWMQTT_NOT_AUTHORIZED)
    Serial.print("Not Authorized");
  else if (reason == lwmqtt_return_code_t::LWMQTT_UNKNOWN_RETURN_CODE)
    Serial.print("Unknown Return Code");
}
#endif

void connectToMqtt(bool nonBlocking = false)
{
  Serial.print("Conectando ao AWS IoT Core MQTT: ");
  while (!client.connected())
  {
    if (client.connect(THINGNAME))
    {
      Serial.println("Conectado!");
      if (!client.subscribe(MQTT_SUB_TOPIC))
        lwMQTTErr(client.lastError());
    }
    else
    {
      Serial.print("Falha. Motivo -> ");
      lwMQTTErrConnection(client.returnCode());

      if (!nonBlocking)
      {
        Serial.println(" < Nova tentativa em 5 segundos");
        delay(5000);
      }
      else
      {
        Serial.println(" <");
      }
    }
    if (nonBlocking)
      break;
  }
}

void connectToWiFi(String init_str)
{
  if (init_str != emptyString)
    Serial.print(init_str);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (init_str != emptyString)
    Serial.println(" WiFi Conectado...");
}

void checkWiFiThenMQTT(void)
{
  connectToWiFi("Checking WiFi");
  connectToMqtt();
}

unsigned long previousMillis = 0;
const long interval = 5000;

void sendData(void)
{

  Serial.println("Preparando JSON para envio dos Dados ao AWS IOT Core.....");
  char cTemperatura[10];
  sprintf (cTemperatura, "%.2f", vlTemperatura); 
  char cUmidade[10];
  sprintf (cUmidade, "%.2f", vlUmidade); 
  
  StaticJsonDocument<200> doc;
  doc["Temperatura"] = cTemperatura;
  doc["Umidade"] = cUmidade;
  
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  if (!client.publish(MQTT_PUB_TOPIC, jsonBuffer, false, 0)) {
     Serial.println("Erro na comunicação MQTT AWS");   
     lwMQTTErr(client.lastError()); }
  else {
     Serial.println("Dados enviados ao AWS IoT Core"); }
      
}

//Funcao SETUP - é a inicialização do Arduino - executada somente uma vez quando liga ou faz o reset
void setup()
{
  Serial.begin(9600);
  delay(5000);
  Serial.println();
  WiFi.hostname(THINGNAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  connectToWiFi(String("Conectando com o WiFi Rede: ") + String(ssid));

  NTPConnect();

  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);

  client.begin(MQTT_HOST, MQTT_PORT, net);
  client.onMessage(messageReceived);

 //Conecta ao AWS MQTT
 connectToMqtt();
 
 //Inicializa o sensor DHT11 - Temperatura e Umidade
 dht.begin(); 
 
}

//Função Loop - fica executando sempre
//No exemplo abaixo ele captura as informações do sensor de 30 em 30 min e envia ao IoT Core
//Se receber uma mensagem ele apresenta na console
void loop()
{
  
  now = time(nullptr);
  if (!client.connected())
  {
    checkWiFiThenMQTT();
  }
  else
  {
    client.loop();
    if (millis() - lastMillis > 1800000)
    {
         
      //captura informações do sensor
      vlUmidade = dht.readHumidity(); //lê o valor da umidade e armazena na variável do tipo float (aceita números com casas decimais)
      vlTemperatura = dht.readTemperature(); //lê o valor da temperatura e armazena na variável do tipo float (aceita números com casas decimais)

      if (isnan(vlUmidade) || isnan(vlTemperatura)) { //Verifica se a umidade ou temperatura são ou não um número
         Serial.println("Erro ao obter temperatura");
         return; //Caso não seja um número retorna
      }

      Serial.println("...");
      Serial.print("Umidade: ");//Imprime no monitor serial a mensagem "Umidade: "
      Serial.print(vlUmidade);//Imprime na serial o valor da umidade
      Serial.println(" % ");//Imprime na serial o caractere "%" e salta para a próxima linha
      Serial.print("Temperatura: ");//Imprime no monitor serial a mensagem "Temperatura: "
      Serial.print(vlTemperatura);//Imprime na serial o valor da temperatura
      Serial.println(" C ");//Imprime no monitor serial " C " e salta para apróxima linha

      lastMillis = millis();
      //Envia os dados para o AWS IoT Core / MQTT
      sendData();
    }
  }
}