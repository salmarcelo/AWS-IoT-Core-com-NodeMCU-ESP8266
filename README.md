# AWS IoT Core com "Arduino" (NodeMCU ESP8266)

## Objetivo do Projeto

Implementar a solução proposta, onde através do sensor instalado no **"Arduino" (NodeMCU ESP8266)**, irá capturar a Temperatura e Umidade e integrar com o **AWS IoT Core**, para posteriormente ser armazenado em **Banco de Dados - NoSQL (DynamoDB)**, através de uma **função Lambda (Pyhton)**. A linguagem de programação do Arduino utilizada neste contexto é a **Linguagem "C"**   
Os códigos fonte do Arduino e da Função Lambda estão disponíveis na lista de arquivos na parte superior deste Git.   

Vale lembrar que, se ainda não possui o NodeMCU ESP8266, você pode executar as demais etapas deste projeto (Relacionadas propriamente à Cloud AWS), inclusive **realizar testes reais** na **Console do Serviço Iot Core** com toda parte da AWS integrada (IoT Core + Lambda + DynamoDB).   

## Desenho de Solução  

![image](https://user-images.githubusercontent.com/63315625/128634518-654915f7-4fdf-424d-8fae-0e800c25d5bc.png)   
     
## Pré-Requisitos  
 - [x] Ter uma conta ativa na AWS  
 - [x] Ter um microcontrolador NodeMCU ESP8266 com WiFi integrado e Sensor de Temperatura/Umidade  
       Se tiver o Arduino e não tiver o Sensor, poderá simular enviando uma informação hardcoded ou randômica  
       O Arduino pode ser comprado no mercadolivre ou em casas de robótica. Caso não tenha e for comprar, lembre-se de adquirir o **modelo NodeMCU ESP8266**, pois o código e bibliotecas citadas nesta projeto são específicas para este modelo. Você irá se surpreender com o que é possível fazer com ele.  
       Estou usando o termo Arduino, pois é mais comum, mas a placa ESP8266 é de outro fabricante, porém totalmente compatível com a IDE do Arduino
                    
   ![image](https://user-images.githubusercontent.com/63315625/128514373-53c2cbf2-ccf0-4246-a93a-1cbd96cecfa0.png)

## Bibliotecas Necessárias

| Biblioteca  |  Link  | Nome do Arquivo .zip |
| ------------------- | ------------------- | ------------------- |
|  Arduino MQTT | [MQTT](https://github.com/256dpi/arduino-mqtt)   | *arduino-mqtt-master.zip*  |
|  PubSubClient | [PublicSubscriber](https://github.com/knolleary/pubsubclient) | *pubsubclient-master.zip*  |
|  ArduinoJSON | [JSon Arduino](https://github.com/bblanchon/ArduinoJson) | *ArduinoJson-6.x.zip* |
|  DH Sensor | [Sensor Temperatura](https://drive.google.com/file/d/16brDLNmOVzmQs6sFh-_CAMivQu-cn6kg/view) | *DHT-sensor-library.zip* |
|  Adafruit Sensor | [Sensor Temperatura](https://drive.google.com/file/d/19ypgAVNwn5f-kb4KDxFr0eOvMQz_yxSU/view) | *Adafruit_Sensor-master.zip* |
 
## Passo-a-passo

Abaixo você verá as etapas necessárias de como realizar a integração do "ESP8266" com o "IoT Core" da AWS

### Instalação da IDE do Arduino
      
#### Passo 01
Caso não tenha a **IDE do Arduino** instalada no seu computador, faça o Download do IDE no link: https://www.arduino.cc/en/software e efetue a instalação   

#### Passo 02
Configurar o Arduino para poder programar o microcontrolador **NodeMCU ESP8266.**   
No menu, selecione **Arquivo / Preferências**, e cole o link abaixo no item **URLs Adicionais para Gerenciadores de Placas**, conforme imagem:     

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

![image](https://user-images.githubusercontent.com/63315625/128394580-4798673f-d53b-401c-b6b0-df7aea81f02b.png)  

#### Passo 03
No menu, selecione **Ferramentas / Placa / Gerenciador de Placas**. No campo para pesquisa procure por **ESP8266** e realize a instalação do pacote, selecionando "Instalar”  

![image](https://user-images.githubusercontent.com/63315625/128395106-631e7f36-8e10-42fc-85e6-b35b3088ee9f.png)  

#### Passo 04
No menu **Ferramentas / Placa / ESP8266 Boards (v 3.0.2)**, selecione o modelo **NodeMCU 1.0 (ESP-12E Module)**, conforme imagem abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128522246-cac94d70-44a1-4385-ab37-7155b1f9a355.png)

#### Passo 05   
Instalar as Bibliotecas necessárias, conforme lista de Bibliotecas. Lembrando que as últimas duas da lista são Bibliotecas para tratar o sensor de Temperatura e sua instalação é opcional dependendo do seu objetivo.
Para realizar a instalação das Bibliotecas, é necessário:  
  . Baixar os Arquivos Zip das mesmas  
  . Realizar a instalação, através do menu **"Sketch / Incluir Biblioteca / Adicionar Biblioteca.zip"**, conforme imagem abaixo:  
Para facilitar estou disponibilizando os arquivos no github, mas se necessário, poderá obter através dos links do item **Bibliotecas utilizadas**  
     . Faça este processo para cada uma das Bibliotecas (.zip)   
  
  ![image](https://user-images.githubusercontent.com/63315625/128442244-ba58a54f-dd88-42e0-a665-51a4beef08ac.png)

#### Passo 06  
. Baixar os arquivos **IoTCore-AWS-ESP8266.ino** e **secret.h** disponibilizados neste Git.    
. No menu do Arduino IDE, selecionar **Arquivo / Novo**. Será gerado um arquivo "Sketch_XXXXX".    
. Basta abrir o arquivo **IoTCore-AWS-ESP8266.ino** baixado no passo 01 no editor de sua preferência, copiar as linhas e colar no arquivo criado no Arduino IDE.  
. No menu, selecione a opção **Sketch / Adicionar Arquivo** e selecione o arquivo **secret.h** baixado no passo 01     
. Utilizar a opção do menu **Arquivo / Salvar Como..."** e salvar o projeto com o nome de sua preferência ou o mesmo nome do arquivo disponibilizado **(IoTCore-AWS-ESP8266)**    
**Observações:**  
  O arquivo **IoTCore-AWS-ESP8266.ino**, contem os códigos necessários para conectar com a sua rede WiFi, realizar a integração com o IoT Core AWS, Geração de JSON, Publish, Subscribe, e por aí vai.  
  O arquivo **secrets.h**, conterá os certificados necessários para realização de uma conexão segura com o AWS IoT Core, bem como as informações para conexão no WiFi.
  
  Se for a primeira vez que está desenvolvendo algo no Arduino, vale lembrar as duas principais funções e que sem as mesmas seu programa não funcionará.    
  
  Função **setup()**   
  É executada apenas uma vez na inicialização ou no reset do microcontrolador, e é nela que você deverá descrever as configurações e instruções gerais para preparar o programa antes que o loop principal seja executado. A função setup() é responsável pelas configurações iniciais da placa.   
  
  Função **loop()**   
  É a função principal do programa e é executada continuamente enquanto a placa microcontroladora estiver ligada. É nesta função que todos os comandos e operações deverão ser escritos. Literalmente ela fica em LOOP executando seus comandos, portanto, é comum controlar os Delays necessários para a correta execução.   

Agora vamos aos passos de **criação do IoT na AWS**. Posteriormente voltaremos à IDE do Arduino para cmomplementar as informações do programa, conforme o avanço dos próximos passos.  

## Agora a "coisa" começou a ficar séria e mais legal :)

## Criação do IoT (Things) na AWS
Caso não tenha uma conta na AWS, efetue o cadastramento no site da [AWS](https://aws.amazon.com/pt/console/)    
      
#### Passo 01
Acessar a Console da AWS (AWS Management Console) e escolher a Região de sua preferência (ex: São Paulo é "South America (São Paulo) sa-east-1)"   
Para este processo eu utilizei a Região **US West (N. California )us-west-1**. Caso utilize alguma outra região, podem existir diferenças entre as Consoles, mas de qualquer forma, conseguirá  realizar as etapas sem dificuldades :)

#### Passo 02
Na barra superior pesquisar o serviço **IoT Core**, conforme imagem abaixo: (Selecionar opção IoT Core)  

![image](https://user-images.githubusercontent.com/63315625/128445288-7a7478b9-997b-4190-965f-490e88bdfeaf.png)

![image](https://user-images.githubusercontent.com/63315625/128633741-524aa3b0-430d-4dd2-86ff-e6c76071797f.png)   

#### Passo 03
Selecione a opção **"Manage / Things"** no menu lateral. Será apresentada a seguinte janela.  

![image](https://user-images.githubusercontent.com/63315625/128633805-406c1d13-67f0-4eb8-8912-a6444e46f0f1.png)  

#### Passo 04
**Chegou a hora de criar a sua "coisa"** (IoT | Internet das coisas | Internet of Things) :)  
Para isto, basta Clicar no botão **Create things** e seguir os passos conforme imagens abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128522934-16a0fbf6-d6e6-4412-9720-3c475d4ed4c1.png)
  
![image](https://user-images.githubusercontent.com/63315625/128446558-cb5a3ed8-ba4f-401a-922d-41d3fa518905.png)  

Digitar o "nome da coisa" **Thing name**  

![image](https://user-images.githubusercontent.com/63315625/128446796-21beb178-2aea-4dc6-a5fd-580f669a8904.png)
  
Clicar em **Next**  

![image](https://user-images.githubusercontent.com/63315625/128446986-07d573fb-c989-4f59-88bd-69d4ade879f5.png)

Clicar em **Create thing**  
Perceba que não estamos criando uma Policy neste momento. Faremos isso nos próximos passos, visando compreender melhor o formato da mesma.      

![image](https://user-images.githubusercontent.com/63315625/128526078-63e3e216-acdb-4f91-90c6-01c27873c166.png)

Será aberta uma janela para que realize o download dos certificados gerados.    
**ATENÇÃO**, pois este é o **ÚNICO** momento de realizar esta etapa    
Estes certificados é que irão garantir uma conexão segura entre o dispositivo e o IoT AWS    

![image](https://user-images.githubusercontent.com/63315625/128621124-bf3330c9-b86f-4a08-a1ef-535ccc4941de.png)

#### Passo 05
Criar a **Shadow** do IoT Core, conforme imagens abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128526910-1785484c-e256-45c2-afae-36498d3949ee.png)  

![image](https://user-images.githubusercontent.com/63315625/128621047-13985f29-5fa0-4ee3-ae82-0c5ac71c16fb.png)  

![image](https://user-images.githubusercontent.com/63315625/128621077-e42773c8-f9ba-420b-8d5c-7acc8c15dd95.png)

#### Passo 06
Agora precisaremos copiar o Endpoint do Thing que será utilizado para comunicação entre o ESP8266 e a AWS   
Basta selecionar a aba **Interact** e clicar no botão **View Settings**, conforme imagens abaixo:  

![image](https://user-images.githubusercontent.com/63315625/128584951-5528cc6f-b64c-42be-8485-3063b9b53464.png)

Agora copie o endereço Endpoint apresentado e cole em algum editor pois precisaremos dele nos próximos passos.  

![image](https://user-images.githubusercontent.com/63315625/128538113-209f347a-40ae-4552-bc43-22e4c27fde5a.png)

#### Passo 07   
Agora vamos criar a Policy e atachar a mesma no certificado. Esta Policy é que irá permitir o uso dos serviços de IoT.      
. No menu lateral, clicar em **Security**, **Policies** e **Create policy**  
. Preencher as informações solicitadas:    
  . name ```IoTSensorPolicy```     
  . Action ```Iot.*```    
  . Resource ARN ```*```     
  . Effect ```Allow```    
  . Clicar em **Create**   
**Obs:** Perceba que neste caso estamos dando total permissão para uso dos serviços relacionados ao IoT Core. Mas é indicado por melhores práticas de segurança, limitar somente ao que realmente irá executar. (Ex: Permitir somente Subscriber para um determinado Thing/Tópico).   

![image](https://user-images.githubusercontent.com/63315625/128606397-0e80655f-c96d-4dc7-8262-59d2ded13acc.png)

#### Passo 08
Agora temos que atachar a Policy ao Certificado   
  . No menu lateral, clicar em **Security**, **Certificates** e selecione o Certificado que foi criado no passo 04.   
  . Selecione a opção **Actions / Attach policy**   
  . Selecione a policy criada no passo anterior e clique em **Attach**       

![image](https://user-images.githubusercontent.com/63315625/128621190-00ff0e37-bebb-4610-b971-3d2c446068b0.png)   

![image](https://user-images.githubusercontent.com/63315625/128621208-c15b56cc-86b8-431b-b931-f53b00aa7ef7.png)

#### Passo 09   
A "primeira parte" de configuração da ASW foi concluída. Chegou a vez de atualizar os arquivos **IoTCore-AWS-ESP8266.ino** e **secret.h** diretamente na IDE do Arduino. Lembrando que você realizou a **etapa do Passo 06**, no **item Instalação do Arduino**.   

## Alterar Código Fonte

#### Passo 01       
No arquivo **IoTCore-AWS-ESP8266.ino**, alterar as informações de Shadows Publish e Subscribe, com o Thing name que você definiu (no exemplo usamos myespwork). Substituir o "XXXXX" pelo nome do seu Thing.   
```
 //Informa os shadows de Publish e Subscribe
 const int MQTT_PORT = 8883;
 const char MQTT_SUB_TOPIC[] = "$aws/things/XXXXXXX/shadow/name/sensor/get";
 const char MQTT_PUB_TOPIC[] = "$aws/things/XXXXXXX/shadow/name/sensor";
```

Se **NÃO FOR UTILIZAR** o sensor de Temperatura e enviar dados hardcoded, é necessário comentar todos os códigos abaixo:
```
#include <DHT.h> //Inclui a biblioteca DHT Sensor Library
#define DHTPIN 5 //Pino digital 5 (pino D1) conectado ao DHT11
#define DHTTYPE DHT11 //DHT 11

//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)
DHT dht(DHTPIN, DHTTYPE); 

//captura informações do sensor
vlUmidade = dht.readHumidity(); //lê o valor da umidade e armazena na variável do tipo float (aceita números com casas decimais)
vlTemperatura = dht.readTemperature(); //lê o valor da temperatura e armazena na variável do tipo float (aceita números com casas decimais)

if (isnan(vlUmidade) || isnan(vlTemperatura)) { //Verifica se a umidade ou temperatura são ou não um número
   Serial.println("Erro ao obter temperatura");
   return; //Caso não seja um número retorna
   }   
   
```

#### Passo 02    
Selecionar o arquivo **secret.h** que foi incluído no passo 06 da Instalação do Arduino, conforme abaixo:

![image](https://user-images.githubusercontent.com/63315625/128585628-c60d86ab-2d08-40a4-ac95-5782206e6adb.png)

Alterar as informações conforme abaixo:   
. Informar nas variáveis **ssid** e **pass** o nome da rede e a senha para conexão com wifi   
. Informar na variável **THINGNAME** o nome da Thing criado no IoT Core   
. Informar na variável **MQTT_HOST** o Endpoint criado para o Thing    
. Informar as variáveis de Certificados   
    . cacert - as informações contidas no certificado "AmazonRootCA1.pem"   
    . client_cert - informações contidas no certificado "xxxxxxx-certificate.pem"   
    . private_key - informações contidas no certificado "xxxxxx-private.pem.key"    
 Basta abrir os arquivos na pasta onde os downloads dos certificados foram realizados, copiar o texto e colar, substituindo o texto **"COLE AQUI OS DADOS/INFORMAÇÕES...."    

![image](https://user-images.githubusercontent.com/63315625/128621547-b4aa82ee-9675-4e6a-9da3-2c5f4e58169f.png)    

#### Passo 03   
Agora salve e arquivo e compile o programa **IoTCore-AWS-ESP8266.ino**   
Você já pode carregar o código no microcontrolador, usando a IDE Arduino, mas lembre-se que ainda faltam os passos para o armazenamento das informações.

![image](https://user-images.githubusercontent.com/63315625/128543144-c00458d7-c57a-4591-84cc-ba521f543640.png)

## Armazenamento das informações no Amazon DynamoDB 

**Osbervação:** Os próximos 3 tópicos obrigatórios caso queira que todo Publish seja armazenado em Banco de Dados. Caso contrário, não precisará executar as etapas dos tópicos de **Criação de Tabela DynamoDB**, **Criação da Função Lambda**, **Criar Trigger / Action - IoT Core com a Função Lambda**, que estarão mais adiante.   

### Criação da Tabela DynamoDB
Na console da AWS, selecione o serviço DynamoDB, conforme imagem abaixo:

![image](https://user-images.githubusercontent.com/63315625/128543833-2abbb9d9-7ef3-4aa2-a42f-e5050c8fc9c9.png)

Selecionar opção **Tables** e clicar no botão **Create Table**  
Neste tópico "vamos fazer o básico" e criaremos uma tabela com uma chave primária do tipo numérica que armazenará a data e hora do registro no formato NUMBER, pois armazenaremos a chave com o Ano+Mês+Dia+Hora+Min+Seg (AAAAMMDDHHMMSS).   

Não entrarei em detalhes em relação à Sort Keys, Índices, TTL, Etc. Mas dependendo da forma que for tratar as informações (*leitura, Exclusão, Atualização*) é fundamental que pense nestes pontos antes de criação da tabela, pois com certeza influenciarão em questões de **Performance, Custos $$$, Etc**. #Fica a Dica!!! 

![image](https://user-images.githubusercontent.com/63315625/128544169-90d4a21c-b5e1-46b0-a708-e0225602c849.png)

![image](https://user-images.githubusercontent.com/63315625/128545036-ab1c4bea-971b-4b56-b858-411024f021ff.png)

### Policies e Roles
Antes de criar a Função Lambda, vamos criar as permissões, dado que a Função irá acionar um serviço do DynamoDB e para isso é necessário que as permissões seja concedidas.   

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

**Continua para ambas as opções:**   
. Informar um nome para a policy ```(myPolicyDynamoDB)```   
. Clicar no botão **Create policy**    

![image](https://user-images.githubusercontent.com/63315625/128567746-6f5ceb88-4950-4295-b40f-9571bb165bd0.png)

**Nota:** O procedimento acima dá acesso total à todas as tabelas do DynamoDB. Deixei desta forma, visando facilitar caso queiram criar serviços de consulta, etc. Normalmente damos somente os acessos necessários, como por exemplo: "Acesso somente à Putitem de uma determinada tabela e para um determinado recurso" :)  

#### Criar Role
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

### Criação da Função Lambda
Na console da AWS, selecione o serviço **Lambda**, conforme imagem abaixo:

![image](https://user-images.githubusercontent.com/63315625/128545212-f20c35b0-da45-47da-9fb5-83da3de27138.png)  

Selecionar opção **Function** e clicar em **Create function** e preencher as informações conforme imagem abaixo:

![image](https://user-images.githubusercontent.com/63315625/128571298-34939237-991c-4b33-b6ad-dc67ff03ae3d.png)

A função será gerada e apresentada na Console   

![image](https://user-images.githubusercontent.com/63315625/128548003-f00c452f-21b4-4b17-bd11-ca4d7d3ea903.png)
   
Copiar o conteúdo do arquivo **RegistroTemperatura.py** disponibilizado neste Git e substituir a função padrão criada de forma padrão.   
Atentar para **substituir o nome da tabela** com o nome da tabela que **foi criada**
Clicar em **Deploy**

![image](https://user-images.githubusercontent.com/63315625/128553260-08486d71-73e7-4922-8922-c24aa47f5b89.png)

Para realizar um teste, acesse a aba **Test**, preencha as informações do JSON de entrada (exemplo abaixo), informe o name do Test (qualquer nome) e clique em **Test**   
```
{
  "Temperatura": "28.80",
  "Umidade": "60.00"
}
```

![image](https://user-images.githubusercontent.com/63315625/128554109-9d321568-ff74-4f15-91d4-4093b349961d.png)

**Verificar resultado**   

![image](https://user-images.githubusercontent.com/63315625/128571768-77c83a3d-d226-4aa8-a961-3c50df3a0cdf.png)

Retornando Status code 200, vale conferir no **DynamoDB** se o item foi incluído.  

### Criar Trigger / Action - IoT Core com a Função Lambda   
Agora que temos nossa **Function Lambda criada**, é necessário realizar a configuração para que, ao receber um Publish, o IoT Core acione a função Lambda que incluirá o item no DynamoDB, conforme proposta do Desenho de Solução.  

#### Passo 01   
Na Console da AWS, selecionar o serviço **IoT Core**, e no menu lateral selecionar a opção **Things**. Selecione o Thing criado anteriormente clicando sobre o nome do mesmo. (ex: myespwork)   

#### Passo 02   
Acesse a aba **Shadow** e copie o conteúdo da coluna **MQTT topic prefix**, conforme imagem abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128622311-616b6119-d6a1-4eaa-ab9c-e59a6a9bd798.png)

#### Passo 03   
No menu lateral selecionar a opção **Act / Rules**, em seguida clicar no botão **Create a rule** 

#### Passo 04   
Preencher as informações conforme detalhes e imagem abaixo:   
  . Preencher o nome da rule (Exemplo: IoTInvokeLambdaRule)   
  . No campo **Rule query statement**, preencher com o conteúdo com base na informação copiada do item shadow (MQTT topic prefix). Se o nome do seu Thing for myespwork e o nome do seu shadow for sensor, ficará exatamente igual ao exemplo abaixo. Caso contrário, basta substituir o texto "myespwork" pelo nome do seu Thing e o texto "sensor" pelo nome do seu shadow.   
  . Neste caso, estamos indicando que para cada  Publish recebido no tópico, ele irá acionar a função Lambda enviando as informações recebidas, ms você pode reestruturar a sua query da "forma que quiser", ou seja, consegue filtrar em qual condição você quer se seja acionada a função Lambda.   

Exemplo:   
```   
SELECT * FROM '$aws/things/myespwork/shadow/name/sensor'
```   

#### Passo 05   
Clicar no botão **Add action** do item **Set one or more actions**
  . Irá aparecer a lista de serviços que podemos triggar.   
  . Para a finalidade proposta, selecione a opção **Send a message to a Lambda function** e clique em **Configure action**   
  . Agora você irá escolher o qual função será invokada quando o IoT Core for acionado. Selecionar a função a criada e em seguida clicar em **Add action**.    
  . Para finalizar a criação da rule, clique no botão **Create rule**    
   
![image](https://user-images.githubusercontent.com/63315625/128582274-79940d1a-c57a-4cfc-93e8-93d266c1fc1f.png)

![image](https://user-images.githubusercontent.com/63315625/128582387-d10830ca-4106-4968-a669-76bd239efe36.png)

![image](https://user-images.githubusercontent.com/63315625/128582583-cec40e3e-4979-42ce-936a-e4e498d3ba7d.png)

![image](https://user-images.githubusercontent.com/63315625/128582635-4a08c372-27cb-44e4-a145-a9ef7cc9e4e8.png)

Irá aparecer a tela abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128582799-9f33eb69-7336-4dbf-bad2-347edd79aef3.png)   

Você também pode ir no menu do Lambda function, selecionar a função criada e perceber que o trigger foi criado com sucesso, conforme imagem abaixo:   

![image](https://user-images.githubusercontent.com/63315625/128582976-6767895f-ce83-4f58-a44f-4fc4de79c5dc.png)

### Tudo Pronto \o/ \o/ \o/
Agora é só testar..   
Você pode começar a testar diretamente pela console da AWS, efetuando os Publish e Subscribe no tópico criado.  
Lembrando que se foram utilizados os nomes conforme os exemplos, você utilizará para esse propósito os seguintes shadows. Basta realizar os testes e verificar se os itens estão sendo gravados no DynamoDB.     

```
Shadows   
$aws/things/myespwork/shadow/name/sensor
$aws/things/myespwork/shadow/name/sensor/get

JSON   
{
  "Temperatura": "28.80",
  "Umidade": "60.00"
}
```

![image](https://user-images.githubusercontent.com/63315625/128583268-f2e7f126-aed0-403c-a476-efd6a4972987.png)

**Obs 01:** Se você estiver com o Arduino conectado ao cabo USB ou Bateria (ou seja ligado), ele já estará executando os comandos que foram programados. Para isso, basta acessar a Console do Arduino, no menu **Ferramentas / Monitor Serial"** e acompanhar: 

obs: existem diversos shadows que podem ser utilizados conforme a sua necessidade. Para conhecer maiores detalhes, vale a pena conferir a documentação na AWS

Espero que tenham gostado deste conteúdo 🌟

## Autor: 
Marcelo Nardi (Sal)   
Arquiteto de Soluções   
[LinkedIin](https://www.linkedin.com/in/marcelo-fabiano-villarinho-nardi-sal-989a168b/)
