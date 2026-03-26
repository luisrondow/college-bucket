# Documentacao de bugs encontrados no codigo fornecido

## Erros de Sintaxe

- Linha 28 
    - O identificador `LC_ALL` necessidade da inclusa da livraria `clocale` no inicio do programa
- Linha 48 
    - Ha a falta de uma virgula enre o primeiro parametro (`"%f"`) e o segundo `&nota` no `scanf`.

## Erro de Execução

- Linha 83
    - A variavel `soma` não esta a ser inicializada com o valor 0.
    - Isso pode resultar em uma divisao entre um numero sem algum valor definido, ou seja o resultado nao é deterministico.
- Linha 90
    - Não ha guardrails para o caso de nenhum estudante estar registado (como há na funcao `listarEstudande`).
    - Isso resulta em uma divisao entre 2 variaveis em zero (caso seja corrigido o problema acima), comportamente é indeterminado.
- Linha 42-57
    - `switch` não possui um `default`
    - O utilizador pode inserir qualquer opçao e caso insira alguma que nao esteja coberta nos cases (1, 2 ou 3), o caminho do programa é indeterminado.

## Problema de Âmbito

- Linhas 8-9 e 26-27 
    - Nomes duplicados entre as propriedades do `struct` Estudante e as variaveis auxiliares de input do usuário
- Linhas 13-14 
    - Declaraçao de variaveis globais sem necessidade, poderia terem sido declaradas em `main` e passadas como referencia para as funções
    - Pode causar poluiçao no espaço de nomes e perda na rastreabilidade: uma vez que qualquer função pode alterar um dado global

## Fuga de Memória

- Linha 30
    - Memória alocada para `estudantes` nao esta a ser devidamente libertada.
