/*215. Kth Largest Element in an Array: [https://leetcode.com/problems/kth-largest-element-in-an-array/description/](https://leetcode.com/problems/kth-largest-element-in-an-array/description/)
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
Este problema exige encontrar o k-ésimo maior elemento de um array. A solução mais óbvia seria ordenar o array completamente, 
o que custaria O(n log n), e depois pegar o elemento na posição [n-k].

No entanto, o padrão de "Dividir e Conquistar" nos permite uma solução muito mais eficiente: O(n) em tempo médio.

A solução é o algoritmo Quickselect (Seleção Rápida). A ideia é "Dividir e Conquistar" de forma parecida com o Quicksort, mas com uma o
timização crucial: em vez de ordenar recursivamente ambos os lados do pivô, nós descartamos uma metade em cada passo e exploramos apenas 
o lado que sabemos que contém o nosso elemento-alvo.

O algoritmo funciona da seguinte forma:

1.  Tradução da Meta: Primeiro, traduzimos o problema. O "k-ésimo maior" elemento em um array de tamanho n é o mesmo que o "(n-k)-ésimo menor" 
elemento (em indexação base-0). Este (n - k) se torna o nosso targetIndex — o índice que estamos "caçando".

2.  O Loop D&C (Iterativo): Em vez de usar recursão (que custa O(log n) de espaço na pilha), usamos um loop while (left < right). Este loop representa 
nossa "busca", diminuindo o espaço do problema (o subarray [left, right]) a cada iteração, atingindo O(1) de espaço.

3.  A Partição (O Trabalho): A cada iteração, chamamos a função partition (usando a partição de Hoare). Ela seleciona um pivô (usamos o do meio para evitar 
o pior caso de O(n^2)) e reorganiza o subarray:
      Todos os elementos <= ao pivô são movidos para a esquerda.
      Todos os elementos >= ao pivô são movidos para a direita.
      A função retorna o pivotIndex (o índice j) que divide esses dois grupos.

4.  A Decisão (O "Conquistar"): Este é o núcleo do D&C. Após a partição, olhamos onde o pivotIndex (o divisor) caiu, em relação ao nosso targetIndex.

5.  Ajuste da Busca (O "Dividir"):
      Caso 1 (Alvo na Esquerda): Se targetIndex <= pivotIndex, sabemos que nosso alvo deve estar na partição da esquerda. Descartamos a partição da 
      direita definindo right = pivotIndex.
      Caso 2 (Alvo na Direita): Se targetIndex > pivotIndex, sabemos que nosso alvo deve estar na partição da direita. Descartamos a partição da esquerda
      definindo left = pivotIndex + 1.

      6.  Conclusão (Sucesso): O loop while para quando left == right. Como a lógica sempre "encurrala" o targetIndex, o loop só pode parar quando 
      left == right == targetIndex. Neste ponto, temos a garantia absoluta de que nums[targetIndex] contém a resposta correta, mesmo que o resto do array 
      esteja desordenado.
*/
#include <vector>
#include <algorithm> // Para std::swap

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        int n = nums.size();
        int targetIndex = n - k;
        
        quickSelect(nums, 0, n - 1, targetIndex);
        
        // O loop quickSelect garante que o elemento em targetIndex é o correto.
        return nums[targetIndex];
    }

private:
    /**
     * Versão iterativa do Quickselect (O(1) de espaço).
     */
    void quickSelect(std::vector<int>& nums, int left, int right, int targetIndex) {
        while (left < right) {
            // pivotIndex é o 'j' retornado por Hoare
            int pivotIndex = partition(nums, left, right); 


            if (targetIndex <= pivotIndex) {
                // O alvo está na partição da esquerda (inclusive).
                // Note que definimos 'right = pivotIndex', não 'pivotIndex - 1',
                // porque o 'pivotIndex' (j) faz parte dessa partição.
                right = pivotIndex;
            } else {
                // O alvo está na partição da direita.
                left = pivotIndex + 1;
            }
        }
        // O loop termina quando left == right == targetIndex.
    }

    /**
     * Implementação da Partição de Hoare (sem alterações).
     */
    int partition(std::vector<int>& nums, int left, int right) {
        // Usar o meio é uma boa heurística de pivô
        int pivotValue = nums[left + (right - left) / 2];

        int i = left;
        int j = right;

        while (true) {
            // Encontra o elemento na esquerda que é >= pivô
            while (nums[i] < pivotValue) {
                i++;
            }
            
            // Encontra o elemento na direita que é <= pivô
            while (nums[j] > pivotValue) {
                j--;
            }

            // Se os ponteiros se cruzaram, a partição está completa
            if (i >= j) {
                return j; // Retorna o índice de divisão
            }

            std::swap(nums[i], nums[j]);
            
            i++;
            j--;
        }
    }
};