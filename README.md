# AWS-IoT-Core-com-Arduino-ESP8622
Utilizando o AWS IoT Core com Arduino - Obter através de sensor a temperatura e umidade e armazenar na Cloud

# Objetivo: 

Através do "Arduino" (ESP8266), permitir a captura da Temperatura e Umidade e enviar para o AWS Iot Core, para posteriormente ser armazenado em Bando de Dados - NOSQL (DynamoDB), através de uma função Lambda

# Pré-Requisitos  
   . Ter uma conta ativa na AWS  
   . Ter um microcontrolador NodeMCU ESP8266 com WiFi integrado  
   ![image](https://user-images.githubusercontent.com/63315625/128397981-b3582876-53a9-4d55-a77e-75ce74433258.png)


                
# Biblioteca Necessárias


| Biblioteca  |  Link  | Complemento |
| ------------------- | ------------------- | ------------------- |
|  Arduino MQTT |  https://github.com/256dpi/arduino-mqtt   |   |
|  PubSubClient |  https://github.com/knolleary/pubsubclient |   |
|  ArduinoJSON |  https://github.com/bblanchon/ArduinoJson |  |
|  DH Sensor | https://drive.google.com/file/d/16brDLNmOVzmQs6sFh-_CAMivQu-cn6kg/view | Baixar somente se for utilizar o sensor de temperatura/umidade |
|  Adafruit Sensor | https://drive.google.com/file/d/19ypgAVNwn5f-kb4KDxFr0eOvMQz_yxSU/view | Baixar somente se for utilizar o sensor de temperatura/umidade |
 

# Passo-a-passo

Abaixo você verá um **passo-a-passo** de como realizar a integração do "Arduino" com o "IoT Core" da AWS

## Instalação do Arduino
Caso não tenha o IDE do Arduino instalado, seguir os passos abaixo: 
      
### Passo 01
Faça o Download do IDE no link: https://www.arduino.cc/en/software e efetue a instalação do mesmo
### Passo 02
Configurar o Arduino para poder programar a NODEMCU ESP8266.
Clique em Arquivo/ Preferências, e cole o link http://arduino.esp8266.com/stable/package_esp8266com_index.json no item URLs Adicionais para Gerenciadores de Placas  

![image](https://user-images.githubusercontent.com/63315625/128394580-4798673f-d53b-401c-b6b0-df7aea81f02b.png)  

### Passo 03
navegue até o Gerenciador de Placas através do caminho Ferramentas/ Placa/ Gerenciador de placas. No campo para pesquisa procure por ESP8266 e realize a instalação do pacote, selecionando "Instalar”  

![image](https://user-images.githubusercontent.com/63315625/128395106-631e7f36-8e10-42fc-85e6-b35b3088ee9f.png)  

### Passo 04
Selecione o modelo da placa conforme imagem abaixo  

![image](https://user-images.githubusercontent.com/63315625/128395551-0f7bd826-ac3b-4880-a1c4-0b544ce67225.png)  

### Passo 05
Instalar as 


