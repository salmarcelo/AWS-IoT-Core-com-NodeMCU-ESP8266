# AWS IoT Core com Arduino ESP8622

## Objetivo: 

Através do sensor instalado no **"Arduino" (ESP8266)**, permitir a captura da Temperatura e Umidade e enviar para o **AWS Iot Core**, para posteriormente ser armazenado em **Banco de Dados - NOSQL (DynamoDB)**, através de uma **função Lambda (Pyhton)**. A linguagem de programação do Arduino utilizada neste contexto é a **Linguagem "C"**
Os códigos fonte do Arduino e da Função Lambda estão disponíveis aqui neste tópico.
A Parte de armazenamento das informações em banco de dados, será opcional, portanto será o último tópico deste conteúdo, dado que não tem impacto no Programa do Arduino.

## Desenho de Solução:  

![image](https://user-images.githubusercontent.com/63315625/128581103-9f3fb39d-4901-41e4-890c-f6e0cec6c94d.png)   

# Pré-Requisitos  
 - [x] Ter uma conta ativa na AWS  
 - [x] Ter um microcontrolador NodeMCU ESP8266 com WiFi integrado e Sensor de Temperatura/Umidade  
       Se não tiver o Sensor, poderá simular enviando uma informação hardcoded ou ramdômica
      
   ![image](https://user-images.githubusercontent.com/63315625/128514373-53c2cbf2-ccf0-4246-a93a-1cbd96cecfa0.png)


# Bibliotecas Necessárias

| Biblioteca  |  Link  | Complemento |
| ------------------- | ------------------- | ------------------- |
|  Arduino MQTT | [MQTT](https://github.com/256dpi/arduino-mqtt)   |   |
|  PubSubClient | [PublicSubscriber](https://github.com/knolleary/pubsubclient) |   |
|  ArduinoJSON | [JSon Arduino](https://github.com/bblanchon/ArduinoJson) |  |
|  DH Sensor | [Sensor Temperatura](https://drive.google.com/file/d/16brDLNmOVzmQs6sFh-_CAMivQu-cn6kg/view) | Baixar somente se for utilizar o sensor de temperatura/umidade |
|  Adafruit Sensor | [Sensor Temperatura](https://drive.google.com/file/d/19ypgAVNwn5f-kb4KDxFr0eOvMQz_yxSU/view) | Baixar somente se for utilizar o sensor de temperatura/umidade |
 
# Passo-a-passo

Abaixo você verá as etapas necessárias de como realizar a integração do "Arduino" com o "IoT Core" da AWS

## Instalação do Arduino
Caso não tenha o **IDE** do Arduino instalado, deverá seguir os passos abaixo:
      
### Passo 01
Faça o Download do IDE no link: https://www.arduino.cc/en/software e efetue a instalação   

### Passo 02
Configurar o Arduino para poder programar o microcontrolador NODEMCU ESP8266.
No menu, selecione **Arquivo / Preferências**, e cole o link abaixo no item **URLs Adicionais para Gerenciadores de Placas**, conforme imagem     
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

![image](https://user-images.githubusercontent.com/63315625/128394580-4798673f-d53b-401c-b6b0-df7aea81f02b.png)  

### Passo 03
No menu, selecione **"Ferramentas / Placa / Gerenciador de Placas"**. No campo para pesquisa procure por ESP8266 e realize a instalação do pacote, selecionando "Instalar”  

![image](https://user-images.githubusercontent.com/63315625/128395106-631e7f36-8e10-42fc-85e6-b35b3088ee9f.png)  

### Passo 04
No menu **"Ferramentas / Placa / ESP8266 Boards (v 3.0.2)"**, selecione o modelo **NodeMCU 1.0 (ESP-12E Module)**, conforme imagem abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128522246-cac94d70-44a1-4385-ab37-7155b1f9a355.png)

### Passo 05
Instalar as Bibliotecas necessárias, conforme lista de Bibliotecas. Lembrando que as últimas duas da lista são Bibliotecas para tratar o sensor de Temperatura e sua instalação é opcional dependendo do seu objetivo.
Para realizar a instalação das Bibliotecas, é necessário:  
  . Baixar os Arquivos Zip das mesmas  
  . Realizar a instalação, através do menu **"Sketch / Incluir Biblioteca / Adicionar Biblioteca.zip"**, conforme imagem abaixo:  
Para facilitar estou disponibilizando os arquivos no github, mas se necessário, poderá obter através dos links do item **Bibliotecas utilizadas**  
  
  ![image](https://user-images.githubusercontent.com/63315625/128442244-ba58a54f-dd88-42e0-a665-51a4beef08ac.png)

### Passo 06  
Baixar os arquivos **IoTCore-AWS-ESP3622.ino** e **secret.h** disponibilizados na parte superior desta página.
No menu do Arduino IDE, selecionar **Arquivo / Novo**. Será gerado um arquivo "Sketch_XXXXX".
Basta abrir o arquivo **IoTCore-AWS-ESP3622.ino** no  editor de sua preferência,  copiar as linhas e colar no arquivo criado no Arduino IDE.  
No menu, selecione a opção **"Sketch / Adicionar Arquivo"** e selecione o arquivo **secret.h** baixado anteriormente

Observações:  
  O arquivo **IoTCore-AWS-ESP3622.ino**, contem os códigos necessários para realizar a integração com o IoT Core AWS. Nele contem diversas funções, desde conexão com WiFi, Conexão comm MQTT, Geração de JSON, Envio de mensagens, Recebimento de Mensagens e por aí vai.  
  O arquivo **secrets.h**, contem os certificados necessários para realização de uma conexão segura com o AWS IoT Core.  
  
  Se for a primeira vez que está desenvolvendo algo no Arduino, vale lembrar as duas principais funções e sem as mesmas seu programa não funcionará.    
  
  A função **setup()** é executada apenas uma vez na inicialização do programa ou reset do microcontrolador, e é nela que você deverá descrever as configurações e instruções gerais para preparar o programa antes que o loop principal seja executado. Em outras palavras, a função setup() é responsável pelas configurações iniciais da placa microcontroladora, tais como definições de pinos de entrada e saída, inicialização da comunicação serial, entre outras.  
  
  A função **loop()** é a função principal do programa e é executada continuamente enquanto a placa microcontroladora estiver ligada. É nesta função que todos os comandos e operações deverão ser escritos.    

Agora vamos aos passos de criação do IoT na AWS. Posteriormente voltaremos à IDE do Arduino para cmomplementar as informações do programa.  

## Agora a "coisa" começou a ficar séria :) 

## Criação do IoT (Things) na AWS
Caso não tenha uma conta na AWS, efetue o cadastramento no site https://aws.amazon.com/pt/console/ 
      
### Passo 01
Acessar a Console da AWS (AWS Management Console) e escolher a Região de sua preferência (ex: São Paulo é "South America (São Paulo) sa-east-1)"   
Para este processo eu utilizei a Região **US West (N. California)us-west-1**. Caso utilize alguma outra região, podem existir diferenças entre as Consoles, mas de qualquer forma, conseguirá  realizar as etapas sem dificuldades :)

### Passo 02
Na barra superior pesquisar o serviço IoT Core, conforme imagem abaixo: (Selecionar opção IoT Core)  

![image](https://user-images.githubusercontent.com/63315625/128445288-7a7478b9-997b-4190-965f-490e88bdfeaf.png)

![image](https://user-images.githubusercontent.com/63315625/128522567-8fa70005-a2e3-43e2-9f2f-d06393450a75.png)


### Passo 03
Selecione a opção **"Manage / Things"** no menu lateral. Será apresentada a seguinte janela.  

![image](https://user-images.githubusercontent.com/63315625/128446067-b78614e0-4931-4b59-93cf-684e7e4c59eb.png)


### Passo 04
Chegou a hora de criar a sua "coisa" (internet das coisas) :)  
Para isto, basta Clicar no botão **Create things** e seguir os passos conforme imagens abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128522934-16a0fbf6-d6e6-4412-9720-3c475d4ed4c1.png)
  
![image](https://user-images.githubusercontent.com/63315625/128446558-cb5a3ed8-ba4f-401a-922d-41d3fa518905.png)  

Digitar o "nome da coisa" **Thing name**  

![image](https://user-images.githubusercontent.com/63315625/128446796-21beb178-2aea-4dc6-a5fd-580f669a8904.png)
  
Clicar em **Next**  

![image](https://user-images.githubusercontent.com/63315625/128446986-07d573fb-c989-4f59-88bd-69d4ade879f5.png)

Clicar em **Create thing**  
Perceba que não estamos criando uma Policy, mas em ambiente Produtivo a sugestão é criar um usuário específico para IoT e criar a Policy contendo somente as permissões necessárias.

![image](https://user-images.githubusercontent.com/63315625/128526078-63e3e216-acdb-4f91-90c6-01c27873c166.png)

Será aberta uma janela para que realize o download dos certificados gerados. ** **ATENÇÃO**, pois este é o **ÚNICO**  momento de realizar esta etapa ** 

![image](https://user-images.githubusercontent.com/63315625/128447630-56f068d8-e2b6-44ec-86c1-4b375ea00daa.png)

### Passo 05
Criar a shadow do IoT Core, conforme imagens abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128526910-1785484c-e256-45c2-afae-36498d3949ee.png)  

![image](https://user-images.githubusercontent.com/63315625/128501861-041aaad2-b039-4fc3-942b-fb67dc770b30.png)  

![image](https://user-images.githubusercontent.com/63315625/128502443-2538f7d5-3c83-4aa4-ac6e-540172151098.png)  

### Passo 06
Agora precisaremos copiar o Endpoint do Thing que será utilizado para comunicação entre Arduino e AWS
Basta selecionar opção **Interact**, e clicar no botão **View Settings**, conforme imagens abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128537785-e5b462c3-7a48-46a7-8d47-0f3dbf7e3bc1.png)

Agora copie o endereço Endpoint apresentado e cole em algum editor pois precisaremos dele nos próximos passos.  

![image](https://user-images.githubusercontent.com/63315625/128538113-209f347a-40ae-4552-bc43-22e4c27fde5a.png)

### Passo 07
A "primeira parte" de configuração da ASW foi concluída. Chegou a vez de atualizar os arquivos **IoTCore-AWS-ESP3622.ino** e **secret.h** diretamente na IDE do Arduino. Lembrando que você realizou a etapa do Passo 06 no item Instalação do Arduino.
Lembrando que a segunda parte de configuração na AWS é opcional, caso realmente queira que todo Publish seja armazenado em Banco de Dados. Caso não queira, não precisará executar as etapas no tópico **Armazenar Dados** que estará mais adiante

## Alterar Código Fonte

### **IoTCore-AWS-ESP3622.ino**  
Alterar as informações de Shadows Publish e Subscribe, com o Thing name que você definiu (no exemplo usamos myespwork)
```
 //Informa os shadows de Publish e Subscribe
 const int MQTT_PORT = 8883;
 const char MQTT_SUB_TOPIC[] = "$aws/things/XXXXXXX/shadow/name/update/get";
 const char MQTT_PUB_TOPIC[] = "$aws/things/XXXXXXX/shadow/name/update";
```

Se **NÃO FOR UTILIZAR** o sensor de Temperatura e enviar dados hardcoded, é necessário comentar todos os códigos abaixo:
```
#include <DHT.h> //Inclui a biblioteca DHT Sensor Library
#define DHTPIN 5 //Pino digital 5 (pino D1) conectado ao DHT11
#define DHTTYPE DHT11 //DHT 11

//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)
DHT dht(DHTPIN, DHTTYPE); 

//captura informações do sensor
vlUmidade = dht.readHumidity(); //lê o valor da umidade e armazena na variável h do tipo float (aceita números com casas decimais)
vlTemperatura = dht.readTemperature(); //lê o valor da temperatura e armazena na variável t do tipo float (aceita números com casas decimais)

if (isnan(vlUmidade) || isnan(vlTemperatura)) { //Verifica se a umidade ou temperatura são ou não um número
   Serial.println("Erro ao obter temperatura");
   return; //Caso não seja um número retorna
   }
```

### **secret.h**   
Selecionar o arquivo **secret.h** que foi incluído no passo 06 da Instalação do Arduino, conforme abaixo:

![image](https://user-images.githubusercontent.com/63315625/128541576-6e5ac9a1-2e79-4dfd-93a2-76e63aa70f41.png)

Alterar as informações conforme abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128542094-8ca64ca4-e1b9-4448-9632-fa4949229264.png)

### Com o Arduino conectado pelo cabo OSB, basta salvar, compilar o programa **IoTCore-AWS-ESP3622.ino** e carregá-lo no microcontrolador, usando a IDE Arduino

![image](https://user-images.githubusercontent.com/63315625/128543144-c00458d7-c57a-4591-84cc-ba521f543640.png)


## Armazenamento das informações no Amazon DynamoDB 

### Criação da Tabela DynamoDB
Na console da AWS, selecione o serviço DynamoDB, conforme imagem abaixo:

![image](https://user-images.githubusercontent.com/63315625/128543833-2abbb9d9-7ef3-4aa2-a42f-e5050c8fc9c9.png)

Selecionar opção **Tables** e clicar no botão **Create Table**  
Neste tópico serei simplista e criaremos uma tabela com uma chave primária do tipo numérica que armazenará a data e hora do registro no formato AAAAMMDDHHMMSS.
Não entrarei em detalhes em relação à Sort Keys, Íncides, etc. Mas dependendo da forma que for tratar as informações (leitura) é fundamental que pense nestes pontos antes de criação da mesma, pois com certeza influenciarão em questão de performance, custos de leitura, etc. #Fica a Dica!!! 

![image](https://user-images.githubusercontent.com/63315625/128544169-90d4a21c-b5e1-46b0-a708-e0225602c849.png)

![image](https://user-images.githubusercontent.com/63315625/128545036-ab1c4bea-971b-4b56-b858-411024f021ff.png)

### Policies e Roles
Antes de criar a Função Lambda, vamos criar as permissões, dado que a Função irá acionar um serviço do DynamoDB   

#### Criar Policie
No Identity and Access Management (IAM), Clicar em **Policies** e em seguida **Create Policy**

![image](https://user-images.githubusercontent.com/63315625/128567146-0228f4d5-d509-401b-b1a4-5955a5fd3fc3.png)


**Opção 01 - Clicar em JSON e colar a Policy abaixo**   

```
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "VisualEditor0",
            "Effect": "Allow",
            "Action": "dynamodb:*",
            "Resource": "*"
        }
    ]
}
```  

**Opção 02 - Seguir os passos abaixo:**  

. Clicar em **Choose a service** e informar DynamoDB para o filtro e selecione a opção **DynamoDB**  
. Selecionar a opção "All DynamoDB actions (dynamodb:*)"    
. Clicar no item *Resources* e selecione a opção "All Resources"    
. Clicar no botão **Next: Tags**    
. Clicar no botão **Next: Review**    

Continua para ambas as opções:  
. Informar um nome para a policy ```(myPolicyDynamoDB)```   
. Clicar no botão **Create policy**    

![image](https://user-images.githubusercontent.com/63315625/128567746-6f5ceb88-4950-4295-b40f-9571bb165bd0.png)

**Nota:** O procedimento acima dá acesso total ao DynamoDB. Deixei desta forma, visando facilitar caso queiram criar serviços de consulta, etc. Normalmente damos somente os acessos necessários, como por exemplo: "Acesso somente à Putitem de uma determinada tabela" :)  

### Criar Role
No Identity and Access Management (IAM), Clicar em **Roles** e em seguida **Create role**   

 ![image](https://user-images.githubusercontent.com/63315625/128569612-1a5cb6e6-c15b-4157-a26d-57bee8a58a0f.png)

. Clicar em **Lambda** e em **Next: Permissions**  
. No campo **Filter policies**, digite o nome da policy criada no passo anterior (myPolicyDinamoDB)  

 ![image](https://user-images.githubusercontent.com/63315625/128569964-f97ac623-44f2-4b41-882a-440471ed15fd.png)   

 . Clicar em **Next: tags**   
 . Clicar em **Next: Review**   
 . Informar um nome para a role ```(myRoleLambda-Dynamo)```   
 . Clicar no botão **Create role**    
 
 ![image](https://user-images.githubusercontent.com/63315625/128570306-3d76b98a-db6e-49a8-ba62-2792adf61ade.png)

### Função Lambda
Na console da AWS, selecione o serviço DynamoDB, conforme imagem abaixo:

![image](https://user-images.githubusercontent.com/63315625/128545212-f20c35b0-da45-47da-9fb5-83da3de27138.png)  


Selecionar opção **Function** e clicar em **Create function** e preencher as informações conforme imagem abaixo:

![image](https://user-images.githubusercontent.com/63315625/128571298-34939237-991c-4b33-b6ad-dc67ff03ae3d.png)

A função será gerada e apresentada na Console   

![image](https://user-images.githubusercontent.com/63315625/128548003-f00c452f-21b4-4b17-bd11-ca4d7d3ea903.png)
   
Copiar o conteúdo do arquivo **RegistroTemperatura.py** e substituir a função padrão criada automáticamente.
Atentar para **substituir o nome da tabela** com o nome da tabela que **foi criada**
Clicar em **Deploy**

![image](https://user-images.githubusercontent.com/63315625/128553260-08486d71-73e7-4922-8922-c24aa47f5b89.png)

Para realizar um teste, acesse a aba Test, preencha as informações do JSON de entrada e clique em **Test**

![image](https://user-images.githubusercontent.com/63315625/128554109-9d321568-ff74-4f15-91d4-4093b349961d.png)

**Verificar resultado**   

![image](https://user-images.githubusercontent.com/63315625/128571768-77c83a3d-d226-4aa8-a961-3c50df3a0cdf.png)

Retornando Status code 200, vale conferir no **DynamoDB** se o item foi incluído.  

### Triggar o IoT Core com a Função Lambda   
Agora que temos nossa Function Lambda criada, é necessário realizar a configuração para que, ao receber um Publish, o IoT core acione a função Lambda que incluirá o item no DynamoDB, conforme proposta do Desenho de Solução.  

Na Console da AWS, selecionar o serviço **IoT Core** e no menu lateral selecionar a opção **Things**.Selecione o Thing criado anteriormente clicando sobre o nome do mesmo. (ex: myespwork)   

Acesse a aba **Shadow** e copie o conteúdo da coluna **MQTT topic prefix**, conforme imagem abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128581799-84990f02-b4a9-4af4-bd2a-ad30ab1c7753.png)

No menu lateral selecionar a opção **Act / Rules**, em seguida clicar no botão **Create a rule** 

Preencher as informações conforme detalhes e imagem abaixo:   
. Preencher o nome da rule (Exemplo: IoTInvokeLambdaRule)   
. No campo **Rule query statement**, preencher com o conteúdo com base na informação copiada do item shadow (MQTT topic prefix). Se o nome do seu Thing for myespwork e o nome do seu shadow for update, ficará exatamente igual ao exemplo abaixo. Caso contrário, basta substituir o texto "myespwork" pelo nome do seu Thing e o texto "update" pelo nome do seu shadow.   

Exemplo:   
``` SELECT * FROM '$aws/things/myespwork/shadow/name/update'
```

![image](https://user-images.githubusercontent.com/63315625/128581604-195dfd3e-9959-411a-9311-d3fbfe3b6882.png)



## Autor: 
Marcelo Nardi (Sal)   
Arquiteto de Soluções   
[LinkedIin](https://www.linkedin.com/in/marcelo-fabiano-villarinho-nardi-sal-989a168b/)


