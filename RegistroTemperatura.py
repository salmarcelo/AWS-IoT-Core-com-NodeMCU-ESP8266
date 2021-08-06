
# importa pacote de utilitario json - biblioteca
import json
# importa o AWS SDK (for Python the package name is boto3)
import boto3
# import pacotes para obtencao e formatacao de datas
from datetime import datetime

#dynamodb = boto3.resource('dynamodb')
client = boto3.client('dynamodb')

def lambda_handler(event, context):
  
  
  # cria variavel string no formato AAAAMMDDHHMMSS  (string pois vou complementar com caractres na chave)
  now = datetime.now()
  nowData = now.strftime("%Y%m%d")
  nowDataHora = now.strftime("%Y%m%d%H%M%S")  
  nowHora = now.strftime("%H%M%S")
  print(nowData)
  print(nowDataHora) 
  print(nowHora)


  data = client.put_item(
    TableName='IoTDados',
    Item={
        'DataHoraRegistro': {
          'N': nowDataHora
        },
        'DataRegistro': {
          'N': nowData
        },
        'HoraRegistro': {
          'N': nowHora
        },
        'Temperatura': {
          'N': event["Temperatura"]
        },
        'Umidade': {
          'N': event["Umidade"]
        }

    }
  )

  response = {
      'statusCode': 200,
      'body': 'successfully created item!',
      'headers': {
        'Content-Type': 'application/json',
        'Access-Control-Allow-Origin': '*'
      },
  }

  return response