# Passeio do Cavalo - heurística de Warnsdoff
Implementação de um algoritmo de backtracking para o problema do passeio do cavalo em C para um tabuleiro 8x8 (tamanho ajustável através do parâmetro N).

Há um setup inicial, onde é criado o tabuleiro, e uma tabela de consulta de quantas casas são visitáveis a partir de cada posição.

A função passo itera recursivamente cada movimento, cuja ordem de tentativa é ordenada a partir da tabela de casas visitáveis, implementando assim a heurística de Warnsdoff. 

A cada passo tenta-se movimentar o cavalo para uma das casas disponíveis. Caso não haja casas não vizitadas, o passo anterior é retrocedido, e há uma tentativa diferente de movimento.

Há uma função de timeout que fora implementada antes dessa heurística, pois os casos demoravam mais que alguns minutos em média, no caso de tabuleiros 8x8. Após a implementação da heurística o tempo médio de cada caso 8x8 caiu para menos de 1 segundo.

Como especificado, ao final de cada chamada da função *passeio*, é escrita a matriz do tabuleiro resolvido, seguida de quantas casas foram avançadas e quantas foram retrocedidas. 

O arquivo **main.c** testa todos os casos possíveis para a posição inicial do tabuleiro, e imprime na tela o tempo gasto para cada caso. Foi verificado que todos os casos foram satisfeitos, mas a implementação não passa em um dos testes do arquivo **verificar.c**, exibindo a saída:

----------------------------
Verificando caso de teste 0
----------------------------
Matriz

7   44  9   24  5   46  19  22  
10  25  6   45  20  23  4   47  
43  8   51  34  53  64  21  18  
26  11  56  63  50  33  48  3   
57  42  59  52  35  54  17  32  
12  27  62  55  60  49  2   37  
41  58  29  14  39  36  31  16  
28  13  40  61  30  15  38  1   

A posição inicial (7, 7) é diferente da entrada (0, 0)