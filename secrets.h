#include <pgmspace.h>

#define SECRET

const char ssid[] = "COLOQUE-O-NOME-DA-SUA-REDE-WIFI";  //Exemplo: RDWIFI
const char pass[] = "COLOQUE-A-SENHA-DA-SUA-REDE-WIFI"; //Exemplo: X3510rd08

#define THINGNAME "COLOQUE-O-NOME-DO-THINGNAME-CRIADO-NA-AWS" //Exemplo: myespwork

int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC
//#define USE_SUMMER_TIME_DST  //uncomment to use DST

const char MQTT_HOST[] = "COLOQUE-O-HOST-CRIADO-NA-AWS";  //Exemplo: xxxxxxxxxxo5p-ats.iot.sa-east-1.amazonaws.com
                          
// Obtain First CA certificate for Amazon AWS
// https://docs.aws.amazon.com/iot/latest/developerguide/managing-device-certs.html#server-authentication
// Copy contents from CA certificate here ▼
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
**COLE AQUI OS DADOS/LINHAS DO CERTIFICADO RSA 2048 CA1**
-----END CERTIFICATE-----
)EOF";

// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
**COLE AQUI OS DADOS/LINHAS DO CERTIFICADO DEVICE CERTIFICATE/CLIENT CERTIFICATE**
-----END CERTIFICATE-----
)KEY";

// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
**COLE AQUI OS DADOS/LINHAS DO CERTIFICADO PRIVATE PEM KEY**
-----END RSA PRIVATE KEY-----
)KEY";
