# e-Folio A - Build e Execução

Este projeto contém duas partes:

1. Programa OCaml, localizado em `bin/main.ml`
2. Aplicação Java, localizada em `java/src`

Os comandos abaixo assumem que o terminal está neste diretório:

```bash
cd prog-lang/ocaml/proj1/efolio_a
```

## Pré-requisitos

- OCaml com `dune` instalado.
- Java JDK instalado, com `javac` e `java` disponíveis no terminal.
- Base de dados em `database/database_26.pl`.

## 1. Build do Projeto OCaml

```bash
dune build
```

Executável gerado:

```text
_build/default/bin/main.exe
```

## 2. Executar o Programa OCaml Diretamente

```bash
./_build/default/bin/main.exe listar_alunos
./_build/default/bin/main.exe indicadores 1
./_build/default/bin/main.exe avaliar 1
./_build/default/bin/main.exe listar_estados
```

## 3. Build da Aplicação Java

```bash
mkdir -p java/out
javac -d java/out java/src/*.java
```

Classes Java geradas em:

```text
java/out
```

## 4. Executar a Aplicação Java

Antes de executar o Java, garanta que o OCaml já foi compilado:

```bash
dune build
```

Depois execute:

```bash
java -cp java/out Aplicacao
```

A aplicação Java apresenta um menu interativo com as opções:

```text
1 - Listar alunos
2 - Consultar indicadores de um aluno
3 - Avaliar aluno
4 - Listar estados finais
5 - Emitir boletim JSON de aluno
0 - Sair
```

## 5. Executar Java Indicando o Executável OCaml

Se quiser indicar manualmente o executável OCaml:

```bash
java -cp java/out Aplicacao _build/default/bin/main.exe
```

Também é possível usar a variável de ambiente `OCAML_EXECUTAVEL`:

```bash
OCAML_EXECUTAVEL=_build/default/bin/main.exe java -cp java/out Aplicacao
```

## 6. Boletins JSON

Ao escolher a opção `5` no menu Java, é gerado um boletim JSON na pasta:

```text
boletins
```

## 7. Ordem Recomendada para Executar Tudo

```bash
dune build
mkdir -p java/out
javac -d java/out java/src/*.java
java -cp java/out Aplicacao
```

## 8. Problemas Comuns

### Erro: Executável OCaml não encontrado

**Solução:**

Executar primeiro:

```bash
dune build
```

### Erro: base de dados não encontrada

**Solução:**

Confirmar que existe o ficheiro:

```text
database/database_26.pl
```

Opcionalmente, indicar outro caminho com:

```bash
EFOLIO_DATABASE=/path/database_26.pl ./_build/default/bin/main.exe listar_alunos
```
