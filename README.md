# Scripts
Este projeto contém scripts para capturar informações do sistema.
Abaixo contém uma breve demonstração do componente desenvolvido.
[![Componente desenvolvido no projeto](https://img.youtube.com/vi/aZUf6p3BbIc/0.jpg)](https://www.youtube.com/watch?v=aZUf6p3BbIc)



# Documentação geral do projeto

Esse documento tem como objetivo descrever e mostrar as configuração de setup das ferramentas e programas usadas no projeto de pesquisa.

# Sobre o sensor biométrico


* Sobre a biblioteca usada

A biblioteca usada foi a biblioteca oficial do [adafruit](https://cdn-shop.adafruit.com/datasheets/ZFM+user+manualV15.pdf). A documentação está em inglês.  Primeiro, você precisa inserir a biblioteca do fingerprint adafruit. *Sketch* -> *Incluir Bibliotecas * -> *Gerenciar bibliotecas* . Na busca você digita: *adafruit fingerprint*. Em seguida, instale a biblioteca.

* Sobre o código

A função ```getFingerprintID()``` checa se existe a ID salava. Se encontrada ela faz o retorno da ID, do contrario ela retornará -1.


* Configuração do sensor biométrico

Configure o sensor deve ser configurado conforme a tabela

| Cabo Sensor   |    Input Arduino |
|---------------|------------------|
|      Red      |        5v        |
|    Green      |       Digital2   |
|    White      |       Digital3   |
|    Black      |       GND        |

Você pode colocar os cabos `Green` e `Black` em qualquer outra porta digital desde que mude no momento  da instancia de `mySerial()`.



**Observação:**    

A biblioteca, após ser instalada, baixa uma série de programas básicos que podem ser usados como base para codificação.
Você pode encontra-las em *arquivo* > *exemplo* > *Adafruit FingerPrint Sensor Library*.

Nessa aba existem programas para apagar, cadastrar e listar digitais.


# Aplicativo mobile

 O aplicativo mobile foi criado usando [Ionic Creator](https://creator.ionic.io/). Ele contém botões que fazer requisições HTTP, essas por sua vez fazem chamadas MQTT.   
O artifício de comunicação foi criado com [Node-red](https://nodered.org/docs/).

O editor web (Ionic Creator) não pode gerar a aplicação com HTML, para isso baixa-se o aplicativo e o build é feito por meio da CLI do Ionic.

Os passos que seguem são necessários e sufientes para realizar o build.

É necessário realizar a instalação do [NodeJS](https://nodejs.org/) antes mais nada. Depois com o NodeJS já instalado e com [npm](https://www.npmjs.com/) funcinando faremos em um terminal:

1. Baixamos as bibliotecas.  
`# npm install -g ionic cordova`

2. Criamos o projeto  
`$ ionic start [nomedoprojeto] blank`

3. Enfim, colocamos o projeto do Ionic Creator na pasta.
4. Fazemos o adicionamento ao projeto Ionic  
`$ ionic cordova platform add browser`

5. Para concluir o build:
`$ ionic cordova build browser`



# API do SUAP para popular o banco
Para a montagem do script que faz chamadas e captura na [API do SUAP](https://suap.ifrn.edu.br/api/docs/) foi usada a liguagem de programação [Python](https://python.org/docs). O script está disponível [num repositório do Github](https://github.com/digituoficial/scripts).

Para fazer uso dele é necessário estar autenticado junto a API por meio de um Token forncecido mediante autenticação WEB na API.
Com o Token basta coloca-lo na variavel global do script `TOKEN=''`e começar a usar a aplicação.

Existem algumas funções:

`informacoes_basicas_aluno(matricula)`, essa função retorna dados públicos do aluno.  
`informacoes_basicas_servidor(token_servidor, matricula)`, essa função retorna dados do servidor (requer token do servidor).  
`informacoes_curso(id_curso)`, retorna informações do curso.



# MQTT
O MQTT é um protocolo de comunicação muito utilizado em IOT. Para instalar ele no arduino, utilizamos uma biblioteca muito popular.
Primeiro, você precisa inserir a biblioteca do fingerprint adafruit. *Sketch* -> *Incluir Bibliotecas* -> *Gerenciar bibliotecas* . Na busca você digita: *mqtt*. Em seguida, selecione a *PubSubClient* e instale a biblioteca.

Para fazer uso do protocolo, usamos um cliente chamdo mosquitto.

Para realizar a instalação basta inserir os seguintes comandos em um terminal:

`# apt update`  
`# apt install mosquito`  
`# apt install mosquito-cients`

* Uso do MQTT com arduino
Para usar MQTT com arduino fizemos uso da biblioteca [PubSubClient](https://pubsubclient.knolleary.net/) e pode facilmente ser instalada via interface gráfica pela IDE arduino.

* Comandos básicos do MQTT com o mosquitto
Criar um tópico:   
`$ mosquitto_sub -t 'topico'`   
O comando cria um tópico denominado *topico* e está apto a receber mensagens.  
Enviar mensagens a um tópico.   
`$ mosquitto_pub -t 'topico' -m 'mensagem' -h 'host.com' -p 1883`   
O comando acima envia uma mensagem para o tópico chamado *topico*. Para alterar o contedo basta passar entre aspas o conteúdo após o parâmetro *-m*.   

**Sobre o uso do MQTT com Python:**   
Para enviar/receber mensagens MQTT com Python faz-se uso de uma biblioteca externa, no caso `paho`.

Um simples script pode enviar/receber as mensagens:

``` python
# import a funcão com um 'alias' pub
import paho.mqtt.publish as pub
import paho.mqtt.client as mqtt


def initialize(client, userdata, flags, rc):
    '''
    Funcao que inicializa os tópicos, ou seja, cria e coloca os nomes.
    '''
    client.subscribe("fingerprint/receive")
    client.subscribe("fingerprint/confirm")


def send_message(msg, topic, port=1883, server=''):
    '''
    Funcao que envia mensagens para para o tópico especificado como parâmetro.
    '''
    if msg and topic and server:
        pub.single(topic, payload=msg, port=port, hostname=server)
        return True
    return False
    
def message(client, userdata, msg):
    '''
    Funcao que recebe mensagem e escreve no topico quando a mensagem é conhecida.
    '''
    if msg.topic == 'fingerprint/receive':
        if msg.payload.decode('utf-8') == 'conhecida':
            send_message("Abra a porta",
                         topic='fingerprint/confirm', server='localhost')
        else:
            send_message("A porta deve continuar fechada",
                         topic='fingerprint/confirm', server='localhost')
    elif msg.topic == 'fingerprint/confirm':
        pass

#Inicializa o programa.
if __name__ == '__main__':
    client = mqtt.Client()
    client.connect("localhost", 1883)
    client.on_connect = initialize
    client.on_message = message
    client.loop_forever()
```


# Node-Red

O Node-red é uma ferramenta de escrita visual projeta para desenvolver dashboards para a internet das coisas. Com a ferramenta facilmente pode-se criar um dashboards que recebe uma requisição HTTP e envia uma mensagem MQTT.

A instalação da ferramenta pode ser feita por meio do gerenciador de pacotes *npm*.   
Para isso é necessário a instalação do NodeJS.  
Num terminal basta inserir o comando no terminal:   
```# npm install -g node-red```   

Para iniciar basta inserir no terminal:

`$ node-red`

# Instalação das Programas/bibliotecas usadas
Programas e algumas bibliotecas são usadas nos programas desenvolvidos.

* [Node-red](https://nodered.org/docs/)
* [Python 3](https://python.org)
* Bibliotecas do Python
	- pip, virtualenv
	- paho (`# pip install paho`)
	- django (`# pip install django`)
	





