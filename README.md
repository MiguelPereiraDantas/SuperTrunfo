# Super Trunfo - Comparação com 2 Atributos em C

Este projeto em C implementa uma versão simplificada do jogo **Super Trunfo** com cartas que representam cidades brasileiras. O programa permite comparar duas cartas baseando-se em dois atributos numéricos escolhidos pelo usuário.

---

## Funcionalidades

- Cartas pré-definidas representando as cidades Itajaí (SC) e Maceió (AL).
- Cálculo automático da densidade populacional e PIB per capita.
- Menu interativo para o jogador escolher dois atributos diferentes para a comparação.
- Comparação dos dois atributos escolhidos, considerando regras especiais (ex: menor densidade vence).
- Soma dos valores dos atributos para decidir o vencedor da rodada.
- Tratamento de empates.
- Exibição clara e organizada do resultado da comparação.

---

## Atributos disponíveis para comparação

1. População  
2. PIB (em bilhões)  
3. Área (km²)  
4. Pontos turísticos  
5. Densidade demográfica (população/área)  
6. PIB per capita  

---

## Como compilar e executar

1. Certifique-se de ter o GCC instalado (ex: `gcc --version`).
2. Compile o código com:

   ```bash
   gcc Tema2.c -o Tema2
