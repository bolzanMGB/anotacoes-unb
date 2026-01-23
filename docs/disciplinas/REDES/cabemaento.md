# Padrão de Crimpage

---

## 1. Conceitos importantes

- Atenuação: perda de força do sinal ao longo do cabo;
- Blindagem: proteção física contra interferências eletromagnéticas;
- Crimpagem: processo de unir fisicamente um conector a um cabo por meio de pressão mecânica.
- Keystone jack: tomada modular para encaixar cabos em painéis ou paredes.
---

## 2. Cabeamento Estruturado

É uma infraestrutura organizada que conecta dispositivos de rede de forma padronizada e flexível e que é baseada em normas internacionais e brasileira.

**Normas Principais**:
- EIA/TIA-568B: define os padrões de pinagem (ordem das cores).
- EIA/TIA-569B: caminhos e espaços para cabeamento.
- EIA/TIA-606A: administração e identificação.
- EIA/TIA-607A: aterramento e proteção.

---

## 3. Cabos de par trançado

É o tipo de cabo mais usado em redes de computadores. Eles utilizam pares de fios trançado para reduzir interferências.

**Cores dos pares de fios**

| Par       | Cores dos fios           | Função geral                                   |
| --------- | ------------------------ | ---------------------------------------------- |
| **Par 1** | Branco/laranja + Laranja | Envio de dados (TX)                      |
| **Par 2** | Branco/verde + Verde     | Recepção de dados (RX)                         |
| **Par 3** | Branco/azul + Azul       | Comunicação auxiliar (voz ou dados adicionais) |
| **Par 4** | Branco/marrom + Marrom   | Envio de dados auxiliar         |

**Categoria dos pares**

| Categoria     | Velocidade / Frequência | Uso                        |
| ------------- | ----------------------- | -------------------------- |
| **CAT 1 e 2** | até 4 Mbps              | Voz e dados antigos        |
| **CAT 3**     | até 16 Mbps             | Antigo, em desuso          |
| **CAT 4**     | até 20 Mbps             | Em desuso                  |
| **CAT 5**     | até 100 Mbps            | Fast Ethernet              |
| **CAT 5e**    | até 155 Mbps            | Mais usado em redes locais |
| **CAT 6**     | até 1000 Mbps (1 Gbps)  | Gigabit Ethernet           |
| **CAT 7**     | até 10 Gbps             | Redes de alto desempenho   |

## 4. Ferramentas

**Alicate de crimpagem:** insere os fios no conector
**Testador de cabos** verifica se há continuidade e se os pares estão corretos
**Conector RJ-45:** possui 8 pinos, usado para conectar cabos de rede em dispositivos.

## 5. Tipos de cabos

**Cabo Direto (Straight-Through)**

- Conecta equipamentos diferentes (ex: computador -> switch);
- Mesmo padraão nas duas pontas;

**Cabo Cruzado (Cross-Over)**
- Conecta equipamentos iguais (ex: pc -> pc);

## 6. Padrões de Crimpagem

**Padrão T568A:**

- Branco/Verde
- Verde
- Branco/Laranja
- Azul
- Branco/Azul
- Laranja
- Branco/Marrom
- Marrom

**Padrão T568B (mais usado no Brasil)**

- Branco/Laranja
- Laranja
- Branco/Verde
- Azul
- Branco/Azul
- Verde
- Branco/Marrom
- Marrom

