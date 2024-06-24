## Objetivo

Este trabalho consiste na construção e utilização de estrutura hierárquica denominada trie (do inglês "re**trie**val", sendo também conhecida como **árvore de prefixos** ou ainda **árvore digital**) para a indexação e recuperação eficiente de palavras em grandes arquivos de dicionários (mantidos em memória secundária). A implementação deverá resolver dois problemas (listados a seguir), e os resultados deverão ser formatados em saída padrão de tela de modo que possam ser automaticamente avaliados no VPL.
<br/>
<br/>
A figura a seguir exemplifica a organização de um arquivo de dicionário. Cada linha apresenta a definição de uma palavra, sendo composta, no início, pela própria palavra com todos os caracteres em minúsculo (somente entre 'a' (97) e 'z' (122) da tabela [ASCII](https://pt.wikipedia.org/wiki/ASCII)) e envolvida por colchetes, seguida pelo texto de seu significado. Não há símbolos especiais, acentuação, cedilha, etc, no arquivo.

![Trie](https://private-user-images.githubusercontent.com/78831999/342508032-cbec6a13-dc31-44c0-b31c-062ba139ee66.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MTkyNjcxNDYsIm5iZiI6MTcxOTI2Njg0NiwicGF0aCI6Ii83ODgzMTk5OS8zNDI1MDgwMzItY2JlYzZhMTMtZGMzMS00NGMwLWIzMWMtMDYyYmExMzllZTY2LnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDA2MjQlMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwNjI0VDIyMDcyNlomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTE4Y2E3YzkzNGRhMGRiMzk0MDgzZTlhMjkwYmU0YjI1MGY3NWExMzE4NWQwYjMxZWJjMzliYzIxOGIzODVkZDAmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JmFjdG9yX2lkPTAma2V5X2lkPTAmcmVwb19pZD0wIn0.x9qoU72MXo6izugF4BqC-4Ws6-5C5hLmssS7pCwCOv0)

---

## Primeiro problema: identificação de prefixos

Construir a trie, em memória principal, a partir das palavras (definidas entre colchetes) de um arquivo de dicionário, conforme o exemplo acima. A partir deste ponto, a aplicação deverá receber uma série de palavras quaisquer (pertencentes ou não ao dicionário) e responder se trata de um prefixo (a mensagem 'P is prefix of N words' deve ser produzida, onde P é o nome da palavra e N é a quantidade de palavras) ou não (a mensagem 'P is not prefix' deve ser produzida na saída padrão). Sugestão de nó da trie:

```cpp
NoTrie {
    char           letra;        //opcional
    NoTrie        *filhos[26];
    unsigned long  posição;
    unsigned long  comprimento;  //se maior que zero, indica último caracter de uma palavra
}
```
---

## Segundo problema: indexação de arquivo de dicionário
A construção da trie deve considerar a localização da palavra no arquivo e o tamanho da linha que a define. Para isto, ao criar o nó correspondente ao último caracter da palavra, deve-se atribuir **a posição do caracter inicial** (incluindo o abre-colchetes '['), seguida pelo comprimento da linha (não inclui o caracter de mudança de linha) na qual esta palavra foi definida no arquivo de dicionário. Caso a palavra recebida pela aplicação exista no dicionário, estes dois inteiros devem ser determinados. <span style="color:red">Importante</span>: uma palavra existente no dicionário também pode ser prefixo de outra; neste caso, o caracter final da palavra será encontrado em um nó **não-folha** da trie e duas linhas deverão ser produzidas na saída padrão, a mensagem '**P is prefix of N words**' na primeira linha, e '**P is in (D,C)**' na linha seguinte (sendo **D** a posição, e **C** o comprimento).


### Exemplo:

Segue uma entrada possível para a aplicação, exatamente como configurada no VPL, contendo o nome do arquivo de dicionário a ser considerado, cuja a trie deve ser construída (no caso para '``dicionario1.dic``' da figura acima), e uma sequência de palavras, separadas por um espaço em branco e finalizada por '0' (zero); e a saída que deve ser produzida neste caso.

- Entrada:

`dicionario1.dic bear bell bid bu bull buy but sell stock stop 0`

- Saída:

```
bear is prefix of 1 words
bear is at (0,149)
bell is prefix of 1 words
bell is at (150,122)
bid is prefix of 1 words
bid is at (273,82)
bu is prefix of 2 words
bull is prefix of 1 words
bull is at (356,113)
buy is prefix of 1 words
buy is at (470,67)
but is not prefix
sell is prefix of 1 words
sell is at (538,97)
stock is prefix of 1 words
stock is at (636,79)
stop is prefix of 1 words
stop is at (716,92)
```
