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
No menu, selecione **"Ferramentas / Placa / Gerenciador de Placas"**. No campo para pesquisa procure por ESP8266 e realize a instalação do pacote, selecionando "Instalar”  

![image](https://user-images.githubusercontent.com/63315625/128395106-631e7f36-8e10-42fc-85e6-b35b3088ee9f.png)  

### Passo 04
No menu **"Ferramentas / Placa / ESP8266 Boards (v 3.0.2)"**, selecione o modelo **NodeMCU 1.0 (ESP-12E Module)**, conforme imagem abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128395551-0f7bd826-ac3b-4880-a1c4-0b544ce67225.png)  

### Passo 05
Instalar as Bibliotecas necessárias, conforme lista de Bibliotecas. Lembrando que as últimas duas da lista são Bibliotecas para tratar o sensor de Temperatura e sua instalação é opcional dependendo do seu objetivo.
Para realizar a instalação das Bibliotecas, é necessário:  
  . Baixar os Arquivos Zip das mesmas  
  . Realizar a instalação, através do menu **"Sketch / Incluir Biblioteca / Adicionar Biblioteca.zip"**, conforme imagem abaixo:  
Para facilitar estou disponibilizando os arquivos no github, mas se necessário, poderá obter através dos links do item **Bibliotecas utilizadas**  
  
  ![image](https://user-images.githubusercontent.com/63315625/128442244-ba58a54f-dd88-42e0-a665-51a4beef08ac.png)

### Passo 06  
Baixar os arquivos **IotAWSESP8266.h** e **secret.h** disponibilizados na parte superior desta página.
No menu do Arduino IDE, selecionar **Arquivo / Novo**. Será gerado um arquivo "Sketch_XXXXX".
Basta abrir o arquivo **IotAWSESP8266.h** no  editor de sua preferência,  copiar as linhas e colar no arquivo criado no Arduino IDE.  
No menu, selecione a opção **"Sketch / Adicionar Arquivo"** e selecione o arquivo **secret.h** baixado anteriormente

Observações:  
  O arquivo **IoTAWSESP8266.h**, contem os códigos necessários para realizar a integração com o IoT Core AWS. Nele contem diversas funções, desde conexão com WiFi, Conexão comm MQTT, Geração de JSON, Envio de mensagens, Recebimento de Mensagens e por aí vai.  
  O arquivo **secrets.h**, contem os certificados necessários para realização de uma conexão segura com o AWS IoT Core.  
  
  Se for a primeira vez que está desenvolvendo algo no Arduino, vale lembrar as duas principais funções e sem as mesmas seu programa não funcionará.    
  
  A função **setup()** é executada apenas uma vez na inicialização do programa ou reset do microcontrolador, e é nela que você deverá descrever as configurações e instruções gerais para preparar o programa antes que o loop principal seja executado. Em outras palavras, a função setup() é responsável pelas configurações iniciais da placa microcontroladora, tais como definições de pinos de entrada e saída, inicialização da comunicação serial, entre outras.  
  
  A função **loop()** é a função principal do programa e é executada continuamente enquanto a placa microcontroladora estiver ligada. É nesta função que todos os comandos e operações deverão ser escritos.    

Agora vamos aos passos de criação do IoT na AWS. Posteriormente voltaremos à IDE do Arduino para cmomplementar as informações do programa.  

## Criação do IoT (Things) na AWS
Caso não tenha uma conta na AWS, efetue o cadastramento no site https://aws.amazon.com/pt/console/ 

      
### Passo 01
Acessar a Console da AWS (AWS Management Console) e escolher a Região de sua preferência (ex: São Paulo é "South America (São Paulo) sa-east-1)"  
Se o usuário utilizado na console não possuir privilégio total, precisa criar uma policy no Identity and Access Management (IAM) da Console.

**Policy**  
{  
    "Version": "2012-10-17",  
    "Statement": [  
        {  
            "Sid": "VisualEditor0",  
            "Effect": "Allow",  
            "Action": "iot:*",  
            "Resource": "*"  
        }  
    ]  
}  

### Passo 02
Na barra superior pesquisar o serviço IoT Core, conforme imagem abaixo: (Selecionar opção IoT Core)  

![image](https://user-images.githubusercontent.com/63315625/128445288-7a7478b9-997b-4190-965f-490e88bdfeaf.png)

![image](https://user-images.githubusercontent.com/63315625/128445868-7f219931-e90f-4eeb-b1b6-8e64c3880ad6.png)  


### Passo 03
Selecione a opção **"Manage / Things"** no menu lateral. Será apresentada a seguinte janela.  

![image](https://user-images.githubusercontent.com/63315625/128446067-b78614e0-4931-4b59-93cf-684e7e4c59eb.png)


### Passo 04
Chegou a hora de criar a sua "coisa" (internet das coisas) :)  
Para isto, basta Clicar no botão **Create things** e seguir os passos conforme imagens abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128446426-22f20fd3-fcbb-42c8-a2e2-71b662a82b74.png)
  
![image](https://user-images.githubusercontent.com/63315625/128446558-cb5a3ed8-ba4f-401a-922d-41d3fa518905.png)  

![image](https://user-images.githubusercontent.com/63315625/128446796-21beb178-2aea-4dc6-a5fd-580f669a8904.png)
  
Clicar em **Next**  

![image](https://user-images.githubusercontent.com/63315625/128446986-07d573fb-c989-4f59-88bd-69d4ade879f5.png)
  
![image](https://user-images.githubusercontent.com/63315625/128447033-b266a269-268c-4843-b103-bc11f5780b3d.png)  

Clicar em **Create thing**  

Será aberta uma janela para que realize o download dos certificados gerados. ** **ATENÇÃO**, pois este é o **ÚNICO**  momento de realizar esta etapa ** 

![image](https://user-images.githubusercontent.com/63315625/128447630-56f068d8-e2b6-44ec-86c1-4b375ea00daa.png)

### Passo 05
Criar a shadow do IoT Core, conforme imagens abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128501613-cb292961-4964-4849-b636-ecbae4c56d37.png)

![image](https://user-images.githubusercontent.com/63315625/128501861-041aaad2-b039-4fc3-942b-fb67dc770b30.png)  

![image](https://user-images.githubusercontent.com/63315625/128502443-2538f7d5-3c83-4aa4-ac6e-540172151098.png)  




