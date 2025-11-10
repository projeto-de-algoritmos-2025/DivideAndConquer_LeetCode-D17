/*
315. Count of Smaller Numbers After Self: [https://leetcode.com/problems/count-of-smaller-numbers-after-self/description/](https://leetcode.com/problems/count-of-smaller-numbers-after-self/description/)
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
Este problema pede para contar, para cada elemento, quantos elementos à sua direita são menores. A solução de força bruta, O(n^2), 
é muito lenta. Simplesmente ordenar o array não funciona, pois perderíamos a informação crucial da "direita" (o índice original).

O padrão "Dividir e Conquistar" oferece uma solução O(nlog n)que é ao mesmo tempo eficiente e elegante.

A solução é um Merge Sort Aumentado. Nós usamos a estrutura exata do Merge Sort (Dividir ao meio, Conquistar recursivamente), mas "aumentamos" a 
etapa de "Combinar" (merge) para fazer um trabalho extra: contar os elementos menores.

O algoritmo funciona da seguinte forma:

1.  Otimização de Memória e Índice: Para evitar o O(n^2) de alocação de memória (criando novos vetores `temp` em cada recursão) e para manter os 
índices originais, nós otimizamos:
        Criamos um vetor `indices` `[0, 1, 2, ..., n-1]`. Nosso algoritmo não vai ordenar `nums`, mas sim o vetor `indices` com base nos valores de `nums`.
        Alocamos os vetores `counts` (para o resultado) e `temp` (para o merge) uma única vez no início, passando-os por referência. Isso reduz a complexidade 
        de espaço da recursão para O(1) (além do O(n) inicial).

2.  Dividir e Conquistar: Chamamos `mergeSort` no vetor `indices`. Ele se divide recursivamente até termos subarrays de um único índice.

3.  A Combinação (O "Trabalho"): Esta é a etapa crucial. Quando combinamos (merge) duas metades já ordenadas (ex: `[left...mid]` e `[mid+1...right]`), usamos 
dois ponteiros (`i` e `j`) e um contador `rightElementsMoved`.

4.  A Lógica da Contagem (O "Aumento"):
    Caso 1 (Direita Menor): Se `nums[indices[j]] < nums[indices[i]]`, o elemento da metade direita é menor. Nós o movemos para o `temp` e incrementamos `rightElementsMoved`.
    Caso 2 (Esquerda Menor/Igual): Se `nums[indices[i]] <= nums[indices[j]]`, o elemento da metade esquerda é menor. Este é o momento-chave. Ao mover `indices[i]`, 
    sabemos que ele é maior (ou igual) do que todos os `rightElementsMoved` elementos da metade direita que já processamos.
    Ação: Como `i` (esquerda) veio antes de `j` (direita) na recursão, todos esses `rightElementsMoved` estavam "originalmente à direita" e são menores. 
    Portanto, `counts[indices[i]] += rightElementsMoved`.

5.  Limpeza e Cópia: Após o loop principal do `merge`, limpamos os elementos restantes (o `while (i <= mid)` é vital, pois esses elementos também adicionam 
`rightElementsMoved` à sua contagem). Finalmente, copiamos o `temp` ordenado de volta para o `indices`, garantindo que o próximo nível de recursão trabalhe 
com subarrays ordenados.

6.  Conclusão (Sucesso): Quando a chamada `mergeSort` inicial retorna, o vetor `indices` está totalmente ordenado, e o vetor `counts` está perfeitamente preenchido 
com as respostas.
*/
#include <vector>
#include <numeric> // Para std::iota

class Solution {
    // Vetor de contagem e vetor de índices
    std::vector<int> counts;
    std::vector<int> indices;
    
    // Vetor 'temp' pré-alocado
    std::vector<int> temp; 

public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return {};
        }

        // Inicializa os vetores UMA VEZ
        counts.resize(n, 0);
        indices.resize(n);
        temp.resize(n); // Pré-aloca o espaço do 'temp'

        // Preenche 'indices' com 0, 1, 2, ...
        std::iota(indices.begin(), indices.end(), 0); 

        // Chama o merge sort principal
        // Passamos 'nums' como const-ref, pois nunca o modificamos
        mergeSort(nums, 0, n - 1);

        return counts;
    }

private:
    /**
     * Função D&C recursiva
     */
    void mergeSort(const std::vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;

        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        // O merge não precisa mais alocar 'temp'
        merge(nums, left, mid, right);
    }

    /**
     * A etapa de "merge" otimizada
     */
    void merge(const std::vector<int>& nums, int left, int mid, int right) {
        int i = left;      // Ponteiro para a metade esquerda
        int j = mid + 1;   // Ponteiro para a metade direita
        int k = left;      // Ponteiro para 'temp'
        
        int rightElementsMoved = 0;

        // 1. Merge principal (comparando nums[indices[i]] e nums[indices[j]])
        while (i <= mid && j <= right) {
            // Comparamos os valores de nums USANDO os índices
            if (nums[indices[i]] <= nums[indices[j]]) {
                
                // LÓGICA CHAVE: Atualiza a contagem do índice da esquerda
                counts[indices[i]] += rightElementsMoved;
                
                // Coloca o índice (não o valor) no 'temp'
                temp[k++] = indices[i++];
            } else {
                // O elemento da direita é menor
                rightElementsMoved++;
                
                temp[k++] = indices[j++];
            }
        }

        // 2. Limpeza da esquerda
        while (i <= mid) {
            counts[indices[i]] += rightElementsMoved;
            temp[k++] = indices[i++];
        }

        // 3. Limpeza da direita
        while (j <= right) {
            temp[k++] = indices[j++];
        }

        // 4. Copia os índices ordenados de 'temp' de volta para 'indices'
        // Esta é a parte que ordena 'indices' para o próximo nível da recursão
        for (int p = left; p <= right; ++p) {
            indices[p] = temp[p];
        }
    }
};