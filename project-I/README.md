## Objetivo

Este projeto consiste na utilização de estruturas lineares, vistas até o momento no curso, e aplicação de conceitos de pilha e/ou fila para o processamento de arquivos XML contendo matrizes binárias que representam cenários de ação de um robô aspirador. A implementação deverá resolver dois problemas (listados a seguir), e os resultados deverão ser formatados em saída padrão de tela de modo que possam ser automaticamente avaliados no VPL.

---

## **Primeiro problema**: validação de arquivo XML

Para esta parte, pede-se exclusivamente a verificação de aninhamento e fechamento das marcações (tags) no arquivo XML (qualquer outra fonte de erro pode ser ignorada). Se houver um erro de aninhamento, deve se impresso <span style="color: red">erro</span> na tela. Um identificador constitui uma marcação entre os caracteres <span style="color: pink;">&lt</span> e <span style="color: pink;">&gt</span>, podendo ser de abertura (por exemplo: <span style="color: pink;">&ltcenario&gt</span>) ou de fechamento com uma <span style="color: pink;">/</span> antes do identificador (por exemplo: <span style="color: pink;">&lt/cenario&gt</span>). Como apresentando em sala de aula, o algoritmo para resolver este problema é baseado em pilha (<span style="color: red">LIFO</span>):

- Ao encontrar uma marcação de abertura, empilha o identificador
- Ao encontrar uma marcação de fechamento, verifica se o topo da pilha tem o mesmo identificador e desempilha. Aqui duas situações de erro podem ocorrer:
	- Ao consultar o topo, o identificador é diferente (ou seja, uma marcação aberta deveria ter sido fechada antes)
	- Ao consultar o topo, a pilha encontra-se vazia (ou seja, uma marcação é fechada sem que tenha sido aberta antes)
- Ao finalizar a análise (parser) do arquivo, é necessário que a pilha esteja vazia. Caso não esteja, mais uma situação de erro ocorre, ou seja, há marcação sem fechamento

---

## **Segundo problema:** determinação de área do espaço que o robô deve limpar  

Cada XML, contém matrizes binárias, com altura e largura, definidas respectivamente pelas marcações **<span style="color: pink">&ltaltura&gt</span>** e **<span style="color: pink;">&ltlargura&gt</span>**, e sequência dos pontos, em modo texto, na marcação **<span style="color: pink;">&ltmatriz&gt</span>**. Cada ponto corresponde a uma unidade de área, sendo 0 para não pertencente ou 1 para pertencente ao espaço que deve ser limpo, como passo mínimo do robô em uma de quatro direções possíveis (vizinhança-4),  Para cada uma dessas matrizes, pretende-se determinar a área (quantidade de pontos iguais a 1 na região do robô) que deve ser limpa, conforme a posição inicial, linha **<span style="color: pink">&ltx&gt</span>** e coluna **<span style="color: pink">&lty&gt</span>**, do robô (primeira linha e primeira coluna são iguais a zero). Para isso, seguem algumas definições importantes:

- A **vizinhança-4** de um ponto na linha _**x**_ e coluna _**y**_, ou seja, na coordenada **(_x_,_y_)**, é um conjunto de pontos adjacentes nas coordenadas:
    - **(_x_-1, _y_)**
    - **(_x_+1, _y_)**
    - **(_x_, _y_-1)**
    - **(_x_, _y_+1)**
- Um **caminho** entre um um ponto _**p**_**1** e outro _**pn**_ é em um sequência de pontos distintos **<_p_1,_p_2,...,_pn_>**, de modo que _**pi**_ é vizinho-4 de _**pi**_**+1**., sendo **_i_=1,2,...,_n_-1**
- Um ponto **_p_** é **conexo** a um ponto _**q**_ se existir um caminho de _**p**_ a _**q**_ (no contexto deste trabalho, só há interesse em pontos com valor 1, ou seja, pertencentes ao espaço a ser limpo)
- Um **componente conexo** é um conjunto maximal (não há outro maior que o contenha) _**C**_ de pontos, no qual quaisquer dois pontos selecionados deste conjunto _**C**_ são conexos

Para a determinação da área a ser limpa, é necessário identificar quantos pontos iguais a 1 estão na região em que o robô se encontra, ou seja, é preciso determinar a área do componente conexo. Conforme apresentado em aula, segue o algoritmo de reconstrução de componente conexo usando uma fila (**FIFO**):

- Criar uma matriz **R** de **0** (zeros) com o mesmo tamanho da matriz de entrada **E** lida
- Inserir **(x,y)** na fila
    - na coordenada **(x,y)** da imagem **R**, atribuir **1**
- Enquanto a fila não estiver vazia
    - **(x,y)** ← remover da fila
    - inserir na fila as coordenadas dos quatro vizinhos que estejam dentro do domínio da matriz (não pode ter coordenada negativa ou superar o número de linhas ou de colunas), com intensidade **1** (em **E**) e ainda não tenha sido visitado (igual a **0** em **R**)
        - na coordenada de cada vizinho selecionado, na imagem **R**, atribuir **1**

O conteúdo final da matriz **R** corresponde ao resultado da reconstrução. A quantidade de **1** (uns) deste único componente conexo é a resposta do segundo problema.
