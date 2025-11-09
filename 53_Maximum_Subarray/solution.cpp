/*
53. Maximum Subarray: https://leetcode.com/problems/maximum-subarray/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
Esta solução implementa o paradigma de Dividir e Conquistar (D&C) para encontrar
a soma máxima do subarray, que resulta em uma complexidade de O(n log n).

A ideia central é que o subarray de soma máxima pode estar em três locais:
1. Totalmente na metade esquerda do array.
2. Totalmente na metade direita do array.
3. Cruzando o ponto médio, começando na metade esquerda e terminando na metade direita.

O algoritmo funciona da seguinte forma:
- Dividir: O array é dividido ao meio no índice meio.
- Conquistar (Recursão):
  1. Chamamos recursivamente a função para encontrar a soma máxima na metade
     esquerda (de esq até meio). Isso nos dá o valor (1).
  2. Chamamos recursivamente a função para encontrar a soma máxima na metade
     direita (de meio + 1 até dir). Isso nos dá o valor (2).
- Combinar:
  3. Calculamos a soma máxima de um subarray que "cruza o meio" (valor 3).
     - Para isso, encontramos a soma_borda_esq: a maior soma possível
       terminando exatamente em meio (varrendo do meio para a esquerda).
     - E encontramos a soma_borda_dir: a maior soma possível
       começando exatamente em meio + 1 (varrendo do meio + 1 para a direita).
     - A soma_cruzada é a soma desses dois valores.
- Resultado: A resposta final é o maior valor entre as três possibilidades
  (soma_max_esquerda, soma_max_direita, soma_cruzada).

O caso base da recursão é quando há apenas um elemento (esq == dir),
retornando o próprio elemento.
*/
class Solution {
public:
    int maxSubArrayRecursivo(vector<int>& nums, int esq, int dir) {
        // CASO BASE: Se há apenas um elemento, ele é a soma máxima.
        if (esq == dir) return nums[esq];

        // 1. DIVIDIR
        int meio = esq + (dir - esq)/2;

        // 2. CONQUISTAR (Chamadas recursivas para as metades)
        int soma_max_esquerda = maxSubArrayRecursivo(nums, esq, meio);
        int soma_max_direita = maxSubArrayRecursivo(nums, meio + 1, dir);

        // 3. COMBINAR (Calcular a soma cruzada)
        
        // Encontra a soma máxima da borda esquerda (terminando em 'meio')
        int soma_borda_esq = INT_MIN;
        int soma_atual = 0;
        for (int i = meio; i >= esq; i--) {
            soma_atual += nums[i];
            soma_borda_esq = max(soma_borda_esq, soma_atual);
        }

        // Encontra a soma máxima da borda direita (começando em 'meio + 1')
        int soma_borda_dir = INT_MIN;
        soma_atual = 0;
        for (int i = meio + 1; i <= dir; i++) {
            soma_atual += nums[i];
            soma_borda_dir = max(soma_borda_dir, soma_atual);
        }

        // A soma cruzada é a soma das duas melhores bordas
        int soma_cruzada = soma_borda_esq + soma_borda_dir;

        // Retorna o máximo das três possibilidades
        return max({soma_max_esquerda, soma_max_direita, soma_cruzada});
    }

    int maxSubArray(vector<int>& nums) {
        return maxSubArrayRecursivo(nums, 0, nums.size() -1);
    }
};
