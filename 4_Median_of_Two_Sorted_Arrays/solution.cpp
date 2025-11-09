/*
4. Median of Two Sorted Arrays: https://leetcode.com/problems/median-of-two-sorted-arrays/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
Este problema exige encontrar a mediana de dois arrays ordenados em tempo 
O(log(m+n)). Isso descarta a mesclagem (merge), que seria O(m+n).

A solução é uma Busca Binária não nos valores, mas no "local do corte" 
(partição). O objetivo é dividir o conjunto total (nums1 + nums2) em duas 
metades de tamanho igual (ou quase igual, se for ímpar), onde:
"metade esquerda" <= "metade direita".

O algoritmo funciona da seguinte forma:
1.  Garantia de Log(min(m, n)): Asseguramos que nums1 seja o menor
    array. A busca binária será feita nele. Isso garante a complexidade 
    de tempo ideal.
2.  Definir a Meta: Calculamos tamanho_metade_esquerda, que é o 
    número total de elementos que a "metade esquerda" combinada deve ter. 
    A fórmula (m + n + 1) / 2 funciona tanto para totais pares quanto ímpares.
3.  Busca Binária: Iniciamos uma busca binária no array nums1 (o menor).
    - esq = 0, dir = m.
    - O corte1 é o ponto médio (nosso mid) dessa busca. Ele representa 
      quantos elementos de nums1 entrarão na "metade esquerda".
    - O corte2 é derivado de corte1 para completar o tamanho
      necessário: corte2 = tamanho_metade_esquerda - corte1.
4.  Verificar a Partição: O ponto crucial. Verificamos se a partição
    está correta. Para isso, olhamos os 4 "elementos de borda":
    - maior_esq_nums1 (L1): O maior da esquerda de nums1.
    - menor_dir_nums1 (R1): O menor da direita de nums1.
    - maior_esq_nums2 (L2): O maior da esquerda de nums2.
    - menor_dir_nums2 (R2): O menor da direita de nums2.
    - Casos de Borda: Usamos INT_MIN e INT_MAX para tratar casos em
      que um corte é 0 (esquerda vazia) ou m/n (direita vazia).
    - Condição de Sucesso: A partição está correta se L1 <= R2 E
      L2 <= R1. Isso prova que todos na esquerda são <= todos na direita.
5.  Calcular a Mediana (Sucesso):
    - Total Par: A mediana é a média dos dois elementos centrais:
      max(L1, L2) e min(R1, R2). Usamos / 2.0 para garantir a 
      divisão de ponto flutuante.
    - Total Ímpar: A mediana é o único elemento central, que é
      o maior elemento da "metade esquerda": max(L1, L2).
6.  Ajustar a Busca (Falha):
    - Se L1 > R2: O corte1 está muito à direita (L1 é muito grande).
      Movemos a busca para a esquerda: dir = corte1 - 1.
    - Se L2 > R1: O corte1 está muito à esquerda (L2 está "invadindo").
      Movemos a busca para a direita: esq = corte1 + 1.
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 1. Garantir que a busca binária seja no array menor (nums1)
        if (nums1.size() > nums2.size()) swap(nums1, nums2);

        int m = nums1.size();
        int n = nums2.size();

        // 2. Definir o tamanho total da "metade esquerda" combinada
        int tamanho_metade_esquerda = (m + n + 1) / 2;

        // 3. Iniciar a busca binária no espaço de corte de nums1
        int esq = 0;
        int dir = m;

        int corte1;
        int corte2;
        int maior_esq_nums1;
        int menor_dir_nums1;
        int maior_esq_nums2;
        int menor_dir_nums2;

        while (esq <= dir) {
            // Define os cortes (partições)
            corte1 = esq + (dir-esq) / 2;
            corte2 = tamanho_metade_esquerda - corte1;

            // 4. Definir os 4 elementos de borda, tratando cortes vazios
            maior_esq_nums1 = (corte1 == 0) ? INT_MIN : nums1[corte1-1];
            menor_dir_nums1 = (corte1 == m) ? INT_MAX : nums1[corte1];
            maior_esq_nums2 = (corte2 == 0) ? INT_MIN : nums2[corte2-1];
            menor_dir_nums2 = (corte2 == n) ? INT_MAX : nums2[corte2];

            // 5. Condição de Sucesso: Partição está correta
            if ((maior_esq_nums1 <= menor_dir_nums2) && (maior_esq_nums2 <= menor_dir_nums1)) {
                
                // Total de elementos é PAR
                if ((m + n) % 2 == 0) {
                    return (max(maior_esq_nums1, maior_esq_nums2) + min(menor_dir_nums1, menor_dir_nums2)) / 2.0;
                } 
                // Total de elementos é ÍMPAR
                else {
                    return max(maior_esq_nums1, maior_esq_nums2);
                }
            } 
            // 6. Ajustar a Busca (corte1 muito à direita)
            else if (maior_esq_nums1 > menor_dir_nums2) {
                dir = corte1 - 1;
            } 
            // 6. Ajustar a Busca (corte1 muito à esquerda)
            else {
                esq = corte1 + 1;
            }
        }

        return 0; // Se os arrays estiverem corretos, nunca deve chegar aqui
    }
};
