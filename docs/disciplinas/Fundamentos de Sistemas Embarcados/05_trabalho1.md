#

## 1. Controle dos semáforos/faixa de pedestre

### 1.1 Cruzamento 1

**Semáforos:**

- Há três bits, cada um representando um led e relacionado com um pino GPIO físico da RPI.

<center>

   | Item               | GPIO RPi (Saída) |
   |--------------------|:----------------:|
   | LED Verde (Bit 0)  | 17               |
   | LED Amarelo (Bit 1)| 18               |
   | LED Vermelho (Bit 2)| 23              |

</center>

- No cruzamento 1, o controle se da enviando sinais que ascendem ou desligam esses bits.
- O comportamento é:
   - Verde (10s) → 
   - Amarelo (2s) → 
   - Vermelho (10s) → 

**Botões de Pedestres:**

- São ativados apenas manualmente pelo dashboard.
- O comportamento é:
   - Se o semáforo está verde e o tempo mínimo (5 s) já passou: muda imediatamente para amarelo;
   - Se o semáforo está verde e o tempo mínimo não passou: aguarda o tempo mínimo e então muda para amarelo;
   - Se o semáforo já está amarelo ou vermelho: o botão não tem efeito adicional.

<center>

| Botão                             | Modelo | GPIO RPi (Entrada) |
|-----------------------------------|:------:|:------------------:|
| Pedestre Principal — Modelo 1     | M1     | 1                  |
| Pedestre Cruzamento — Modelo 1    | M1     | 12                 |


</center>

### 1.2 Cruzamento 2

**Semáforos e Faixas**

- Também há tres leds, cada led ligado a um pino GPIO.
- Esses pinos sao bits: podem ser 0 ou 1.

<center>

   | Bit | GPIO RPi (Saída) |
   |:---:|:----------------:|
   | 0   | 24               |
   | 1   | 8                |
   | 2   | 7                |

</center>

- RPI n controla um a um, ela manda um comando para os três de uma vez.
- Há 8 combinações: o resultados desse número binário de três bits vai de 0 a 7.

<center>

   | Código | Via Principal | Via Cruzamento | Ped. Principal | Ped. Cruzamento |
   |:------:|:-------------:|:--------------:|:--------------:|:---------------:|
   | 000     | Amarelo       | Amarelo        | Desligado      | Desligado       |
   | 001     | Verde         | Vermelho       | Vermelho       | Verde           |
   | 010     | Amarelo       | Vermelho       | Vermelho       | Vermelho        |
   | 011     | Amarelo       | Vermelho       | Vermelho       | Desligado       |
   | 100     | Vermelho      | Vermelho       | Vermelho       | Vermelho        |
   | 101     | Vermelho      | Verde          | Verde          | Vermelho        |
   | 110     | Vermelho      | Amarelo        | Vermelho       | Vermelho        |
   | 111     | Vermelho      | Amarelo        | Desligado      | Vermelho        |

</center>

- A RPI vai mandar essas combinações para o pinos, controlando os semáforos.
- A ESP vai ficar de olho nesses pinos e a partir deles abrir/fechar os semáforos/faixas.

**Botoes de pedestre**
- O ciclo acima é rodado.
- Se o pedestre apertar o botão no dashboard:
   - Botão Pedestre Principal: Se o sinal da via principal está verde e o tempo mínimo já passou, antecipa a mudança para amarelo;
   - Botão Pedestre Cruzamento: Se o sinal da via de cruzamento está verde e o tempo mínimo já passou, antecipa a mudança para amarelo.

<center>

   | Botão                             | Modelo | GPIO RPi (Entrada) |
   |-----------------------------------|:------:|:------------------:|
   | Pedestre Principal — Modelo 2     | M2     | 25                 |
   | Pedestre Cruzamento — Modelo 2    | M2     | 22                 |

</center>

## 2. Sensores de velocidade e Câmeras LPR


### 2.1 Sensores de Velocidade
- Há 2 sensores por cruzamento.
- Cada sensor usa dois pinos GPIO.

<center>

| Sensor | Cruzamento | GPIO RPi A | GPIO RPi B |
|:------:|:----------:|:----------:|:----------:|
| 1      | 1          | 16         | 20         |
| 2      | 1          | 21         | 27         |
| 3      | 2          | 11         | 0          |
| 4      | 2          | 5          | 6          |

</center>

- Quando um carro passa, a ESP joga um pulso no Pino A
- Quando o carro termina de passar ele jogo outro pulso no Pino B.
- Servidor distribuído calcula a diferença de tempo entre os dois pulsos.
- A cada 2 segundos o SD manda o número de veículos por sensor ao SC.
- Se a velocidade for maior que 60, o SD manda imediatamente o id do sensor e a velocidade para o SC.

### 2.2 Câmeras LPR

- Há duas câmeras por cruzamento na ESP.
- Cada câmera ligada com um sensor de velocidade.
- Elas ficam no modo de espera.
- Só tiram foto ao receber um comando do SC que passou um carro em velocidade alta.
- Cada câmera possui um endereço MODBUS.

<center>

| Dispositivo                        | Endereço MODBUS | Funções suportadas      |
|------------------------------------|:---------------:|-------------------------|
| Câmera LPR — Sensor 1              | 0x11            | 0x03 leitura / 0x10 escrita |
| Câmera LPR — Sensor 2              | 0x12            | 0x03 / 0x10             |
| Câmera LPR — Sensor 3              | 0x13            | 0x03 / 0x10             |
| Câmera LPR — Sensor 4              | 0x14            | 0x03 / 0x10             |
| Estado do Sistema                  | 0x20            | 0x03 leitura            |

</center>

- Cada câmera possui os seguintes registers

<center>

| Offset | Tamanho | Descrição                                | Tipo/Formato                            |
|:------:|:-------:|------------------------------------------|-----------------------------------------|
| 0      | 1       | **Status**                               | 0=Pronto, 1=Processando, 2=OK, 3=Erro   |
| 1      | 1       | **Trigger de Captura** (escrever 1 para disparar) | 0=Idle; escrever 1 inicia captura |
| 2      | 4       | **Placa [8 chars]**                      | 4 registradores (2 bytes cada) — ASCII  |
| 6      | 1       | **Confiança (%)**                        | 0–100                                   |
| 7      | 1       | **Código de Erro**                       | 0=nenhum                                |

</center>

**Fluxo de Multa:**

- SD identifica um carro em alta velocidade.
- SD envia o ID do sensor e a velocidade para o SC via TCP.
- SC manda um pacote MODBUS de Escrita para para câmera ligada com esse sensor
   - Comando para tirar foto: muda o Triger da câmera para 1,
- SC fica lendo em loop o Status da Câmera.
- Quando der 2, o SC le a Placa e a Confiança.
- SC recebe os bytes da placa, converte para texto e salva no arquivo multas.log.
- SC envia outro pacote MODBUS mudando o Trigger para 0.


## 3. Estado do Sistema

- É um bloco de memoria na ESP
- SC le a cada 200ms os registradores.
- Serve para o SC descobrir se:
   - Modo noturno foi ativado
   - Há um veículo de emergência.


<center>

| Offset | Tamanho | Campo               | Codificação                                                                 |
|:------:|:-------:|---------------------|-----------------------------------------------------------------------------|
| 0      | 1       | `active`            | 0 = sem emergência, 1 = emergência em curso                                 |
| 1      | 1       | `road`              | 0 = nenhuma, 1 = via principal (`main`), 2 = via auxiliar (`cross`)         |
| 2      | 1       | `direction`         | 0 = nenhuma, 1 = leste, 2 = oeste, 3 = norte, 4 = sul                       |
| 3      | 1       | `intersection_id`   | 0 = ambos / não se aplica, 1 = cruzamento 1, 2 = cruzamento 2               |
| 4      | 1       | `vehicle_type`      | 0 = nenhum, 1 = ambulância, 2 = bombeiros, 3 = polícia                      |
| 5      | 1       | `signal_group`      | 0 = nenhum, 1 = sinal principal (abrir verde), 2 = sinal auxiliar           |
| 6      | 1       | `timed_out`         | 0 = OK, 1 = último ciclo estourou o tempo máximo (incidente registrado)     |
| 7      | 1       | `unattended_count`  | Total acumulado de emergências não atendidas a tempo (16 bits)              |
| 8      | 1       | `elapsed_s_x10`     | Tempo decorrido do ciclo atual em **décimos de segundo** (e.g. 123 = 12.3s) |
| 9      | 1       | `max_time_s_x10`    | Tempo máximo aceitável em décimos de segundo (calculado pelo widget)        |
| 10     | 1       | `night_mode`        | `0` = modo Dia | `1` = modo Noite        |

</center>

**Fluxo de Emergência**

- SC lê active = 1.
- SC ordem via TCP para o SD afetado.
- SC abre o verde ordenado e trava o sinal aberto
- SC lê active = 0.
- Semáforo é descongelado.
 