import urllib3
import json


TOKEN = ''
AUTHORIZATION = ''


def informacoes_basicas_aluno(matricula):
    http = urllib3.PoolManager()
    global TOKEN
    r = http.request(
        'GET',
        'https://suap.ifrn.edu.br/api/v2/edu/alunos/{}/'.format(matricula),
        headers={'Accept': 'application/json',
                 'X-CSRFToken': TOKEN,
                 'Authorization': AUTHORIZATION,
                 }
    )

    return json.loads(r.data.decode('utf-8'))


def informacoes_basicas_servidor(token_servidor, matricula):
    http = urllib3.PoolManager()
    global TOKEN, AUTHORIZATION
    r = http.request(
        'GET',
        'https://suap.ifrn.edu.br/api/v2/edu/servidores/{}/'.format(matricula),
        headers={'Accept': 'application/json',
                 'X-CSRFToken': token_servidor,
                 'Authorization': AUTHORIZATION,
                 }
    )

    return json.loads(r.data.decode('utf-8'))


def informacoes_curso(id_curso):
    http = urllib3.PoolManager()
    global TOKEN
    r = http.request(
        'GET',
        'https://suap.ifrn.edu.br/api/v2/edu/cursos/{}/'.format(id_curso),
        headers={'Accept': 'application/json',
                 'X-CSRFToken': TOKEN,
                 }
    )

    return json.loads(r.data.decode('utf-8'))
