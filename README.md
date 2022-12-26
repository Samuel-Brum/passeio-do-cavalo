# Passeio do Cavalo - heurística de Warnsdoff
Implementação de um algoritmo de backtracking para o problema do passeio do cavalo em C para um tabuleiro 8x8 (tamanho ajustável através do parâmetro N).

Há um setup inicial, onde é criado o tabuleiro, e uma tabela de consulta de quantas casas são visitáveis a partir de cada posição.

A função passo itera recursivamente cada movimento, cuja ordem de tentativa é ordenada a partir da tabela de casas visitáveis, implementando assim a heurística de Warnsdoff. 

A cada passo tenta-se movimentar o cavalo para uma das casas disponíveis. Caso não haja casas não vizitadas, o passo anterior é retrocedido, e há uma tentativa diferente de movimento.

Há uma função de timeout que fora implementada antes dessa heurística, pois os casos demoravam mais que alguns minutos em média, no caso de tabuleiros NxN. Após a implementação da heurística o tempo médio de cada caso 8x8 caiu para alguns microsegundos.

Como especificado, ao final de cada chamada da função *passeio*, é escrita a matriz do tabuleiro resolvido, seguida de quantas casas foram avançadas e quantas foram retrocedidas. 

O arquivo **main.c** testa todos os casos possíveis para a posição inicial do tabuleiro, e imprime na tela o tempo gasto para cada caso. Foi verificado que todos os casos foram satisfeitos, mas a implementação não passa em um dos testes do arquivo **verificar.c**, exibindo a saída:
