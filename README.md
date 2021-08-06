# AWS IoT Core com Arduino ESP8622

## Objetivo: 

Através do sensor instalado no **"Arduino" (ESP8266)**, permitir a captura da Temperatura e Umidade e enviar para o **AWS Iot Core**, para posteriormente ser armazenado em **Banco de Dados - NOSQL (DynamoDB)**, através de uma **função Lambda (Pyhton)**. A linguagem de programação do Arduino utilizada neste contexto é a **Linguagem "C"**
Os códigos fonte estão disponíveis aqui neste tópico.

## Desenho de Solução:  

![image](https://user-images.githubusercontent.com/63315625/128429650-28329a7c-f80d-4298-94c8-0688077c0158.png)

# Pré-Requisitos  
   . Ter uma conta ativa na AWS  
   . Ter um microcontrolador NodeMCU ESP8266 com WiFi integrado  
      
   ![image](https://user-images.githubusercontent.com/63315625/128399371-aa27e3dc-4ffa-4445-a25d-493eaeedd43d.png)


# Biblioteca Necessárias

| Biblioteca  |  Link  | Complemento |
| ------------------- | ------------------- | ------------------- |
|  Arduino MQTT |  https://github.com/256dpi/arduino-mqtt   |   |
|  PubSubClient |  https://github.com/knolleary/pubsubclient |   |
|  ArduinoJSON |  https://github.com/bblanchon/ArduinoJson |  |
|  DH Sensor | https://drive.google.com/file/d/16brDLNmOVzmQs6sFh-_CAMivQu-cn6kg/view | Baixar somente se for utilizar o sensor de temperatura/umidade |
|  Adafruit Sensor | https://drive.google.com/file/d/19ypgAVNwn5f-kb4KDxFr0eOvMQz_yxSU/view | Baixar somente se for utilizar o sensor de temperatura/umidade |
 
# Passo-a-passo

Abaixo você verá as etapas necessárias de como realizar a integração do "Arduino" com o "IoT Core" da AWS

## Instalação do Arduino
Caso não tenha o **IDE** do Arduino instalado, deverá seguir os passos abaixo:
      
### Passo 01
Faça o Download do IDE no link: https://www.arduino.cc/en/software e efetue a instalação do mesmo  

### Passo 02
Configurar o Arduino para poder programar o microcontrolador NODEMCU ESP8266.
No menu, selecione Arquivo / Preferências, e cole o link http://arduino.esp8266.com/stable/package_esp8266com_index.json no item **URLs Adicionais para Gerenciadores de Placas**  
![image](https://user-images.githubusercontent.com/63315625/128394580-4798673f-d53b-401c-b6b0-df7aea81f02b.png)  

### Passo 03
No menu, selecione Ferramentas / Placas / Gerenciador de Placas. No campo para pesquisa procure por ESP8266 e realize a instalação do pacote, selecionando "Instalar”  

![image](https://user-images.githubusercontent.com/63315625/128395106-631e7f36-8e10-42fc-85e6-b35b3088ee9f.png)  

### Passo 04
No menu Ferramentas / Placa / ESP8266 Boards (v 3.0.2) e Selecione o modelo **NodeMCU 1.0 (ESP-12E Module)**, conforme imagem abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128395551-0f7bd826-ac3b-4880-a1c4-0b544ce67225.png)  

### Passo 05
Instalar as Bibliotecas necessárias, conforme lista de Bibliotecas. Lembrando que as últimas duas da lista são Bibliotecas para tratar o sensor de Temperatura e sua instalação é opcional dependendo do seu objetivo.
Para realizar a instalação das Bibliotecas, é necessário:  
  . Baixar os Arquivos Zip das mesmas  
  . Realizar a instalação, atravé do menu Sketch / Incluir Biblioteca / Adicionar Biblioteca.zip, conforme imagem abaixo:  
Para facilitar estou disponibilizando os arquivos no github, mas se necessário, poderá obter através dos links do item **Bibliotecas utilizadas**  
  
  ![image](https://user-images.githubusercontent.com/63315625/128442244-ba58a54f-dd88-42e0-a665-51a4beef08ac.png)

### Passo 06  
Baixar os arquivos **IotAWSESP8266.h** e **secret.h** disponibilizados na parte superior desta página.
Na menu do Arduino IDE, selecionar Arquivo / Novo. Será gerado um arquivo "Sketch_XXXXX".
Basta abrir o arquivo **IotAWSESP8266.h** no seu editor preferido e copiar as linhas para o arquivo criado no Arduino IDE
No menu, selecione a opção Sketch / Adicionar Arquivo e selecione o arquivo **secret.h** baixado anteriormente

Agora vamos aos passos de criação do IoT na AWS. Posteriormente voltaremos à IDE do Arduino para cmomplementar as informações do programa.

## Criação do IoT (Things) na AWS
Caso não tenha uma conta na AWS, efetue o cadastramento no site https://aws.amazon.com/pt/console/ 

      
### Passo 01
Faça o Download do IDE no link: https://www.arduino.cc/en/software e efetue a instalação do mesmo
### Passo 02
Configurar o Arduino para poder programar a NODEMCU ESP8266.

### Passo 03
navegue até o Gerenciador de Placas através do caminho Ferramentas/ Placa/ Gerenciador de placas. No campo para pesquisa procure por ESP8266 e realize a instalação do pacote, 

### Passo 04
Selecione o modelo da placa conforme imagem abaixo  

### Passo 05
Instalar as 
