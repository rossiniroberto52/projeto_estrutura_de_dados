
# Sistema de Autenticação - Tabela Hash em C
## 1 - Descrição do Projeto
Este projeto implementa um sistema de autenticação de usuários do zero em C. A arquitetura de dados baseia-se em uma Tabela Hash com Endereçamento Aberto e Duplo Hash para resolução de colisões. O sistema garante o isolamento de senhas em memória, não armazenando credenciais em texto limpo e operando sob o conceito de Lápides (Tombstones) para exclusão lógica de dados.
## 2 - Como Compilar e Executar
O sistema foi construído com a interface central em main.c e o motor do banco de dados na biblioteca local hash.h.
**Para comilar via terminal:**
``bash
    gcc main.c -o sistema_auth
``
**Para executar:**
``bash
    ./sistema_auth
``
*(no windows, execute: sistema_auth.exe)*

## 3 - Defesa Arquitetural e Funcionalidades

### A. A Função de Hash (valorString)
Uma abordagem ingênua para strings seria somar os valores da tabela ASCII de cada caractere. O problema matemático dessa abordagem é a geração de colisões absolutas em anagramas (ex: "roma" e "amor" gerariam o mesmo índice).Para evitar isso, a função valorString foi construída baseada em um multiplicador primo. Para cada caractere da string, o valor acumulado é multiplicado por $37$ (um número primo ímpar) antes de somar o próximo caractere. Isso garante um bit shifting irregular, espalhando os padrões binários e garantindo que a posição da letra altere drasticamente o hash final antes da aplicação do módulo:
 $hash = hash \pmod{TAM\_HASH}$.

### B. Tratamento de Colisões: Duplo Hash (Double Hashing)
A opção padrão de mercado para iniciantes é a Sondagem Linear, que sofre de uma falha crítica de performance chamada Agrupamento Primário (Primary Clustering) — a criação de blocos contíguos de memória ocupada que degradam a busca de $O(1)$ para $O(N)$.Para mitigar o agrupamento, este sistema utiliza Duplo Hash. Quando ocorre uma colisão, uma segunda função matemática independente ($h_2$) dita o tamanho do "salto" para a próxima tentativa.A fórmula do pulo é garantida matematicamente para nunca retornar $0$ (o que causaria loop infinito), utilizando um número primo menor ($17$) que o tamanho da tabela ($31$): $h_2(k) = 17 - (k \pmod{17})$, Desta forma, duas chaves que colidem no mesmo índice inicial terão trajetórias de dispersão completamente diferentes pela tabela.

### C. Estratégia de Exclusão: Lápides (Tombstones)

Em sistemas de endereçamento aberto, apagar fisicamente um dado quebra a corrente de busca para elementos que colidiram e pularam aquele índice no passado. A função removeHash aplica uma alteração de estado lógico (Tombstone):

    * Status 0: Vazio(Virgem).
    * Status 1: Ocupado.
    * Status 2: Removido (Tombstone/lapide)
A função de busca (buscaHash) ignora as lápides e continua varrendo a memória até encontrar o usuário correto ou um espaço de Status $0$, garantindo a integridade dos dados espalhados pelo Duplo Hash.

### D. Armazenamento e Validação de Senhas
O sistema atende ao rigor de não salvar a senha original.</br>
    1. Captura e Conversão: A senha é capturada no buffer da main, enviada para a função matemática de embaralhamento e convertida em um identificador numérico cego (sprintf).</br>
    2. Queima de Arquivo: Imediatamente após a conversão, a função memset(senha_limpa, 0, TAM_STR) é invocada para zerar o array original, removendo os rastros da senha em texto limpo da memória RAM antes de passar os dados para a estrutura da Tabela Hash.</br>
    3. Validação: No login, o processo é repetido. O sistema compara apenas os hashes convertidos dentro da struct usando strcmp.</br>