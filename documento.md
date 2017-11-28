# Documentação geral do projeto

Esse documento tem como objetivo descrever e mostrar as configuração de setup das ferramentas e programas usadas no projeto nesse período.

# Sobre o sensor biométrico


* Sobre a biblioteca usada

A biblioteca usada foi a biblioteca oficial do [adafruit](https://cdn-shop.adafruit.com/datasheets/ZFM+user+manualV15.pdf). A documentação está em inglês.  Primeiro, você precisa inserir a biblioteca do fingerprint adafruit. *Sketch* -> *Incluir Bibliotecas * -> *Gerenciar bibliotecas* . Na busca você digita: adafruit fingerprint

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
Para fazer uso do protocolo, usamos um cliente chamdo mosquitto.

Para realizar a install basta inserir os seguintes comandos em um terminal:

`# apt update`  
`# apt install mosquito`  
`# apt install mosquito-cients`

* Uso do MQTT com arduino
Para usar MQTT com arduino fizemos uso da biblioteca [PubSubClient](https://pubsubclient.knolleary.net/) e pode facilmente ser instalada via interface gráfica pela IDE arduino.

# Instalação das Programas/bibliotecas usadas
Programas e algumas bibliotecas são usadas nos programas desenvolvidos.

* [Node-red](https://nodered.org/docs/)
* [Python 3](https://python.org)
* Bibliotecas do Python
	- pip, virtualenv
	- paho (`# pip install paho`)
	- django (`# pip install django`)
	





