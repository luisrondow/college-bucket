> em ocaml, qual a diff de criar uma funcao com parametros entre parenteses let ex (a, b) e let ex a b ?

Em OCaml, isto cria **funções diferentes**:

```ocaml
let ex (a, b) = a + b
```

recebe **um único argumento**, que é um tuplo.

```ocaml
let ex a b = a + b
```

recebe **dois argumentos**, em forma curried.

## Diferença prática

### 1. Com tuplo

```ocaml
let ex (a, b) = a + b
```

Tipo:

```ocaml
ex : int * int -> int
```

Chamada:

```ocaml
ex (2, 3)
(* 5 *)
```

Aqui `(2, 3)` é **um só valor** do tipo `int * int`.

---

### 2. Com parâmetros separados

```ocaml
let ex a b = a + b
```

Tipo:

```ocaml
ex : int -> int -> int
```

Chamada:

```ocaml
ex 2 3
(* 5 *)
```

Isto é equivalente a:

```ocaml
let ex = fun a -> fun b -> a + b
```

Ou seja, `ex` recebe `a` e devolve uma função que recebe `b`.

## A maior diferença: aplicação parcial

Com parâmetros separados, podes fazer isto:

```ocaml
let add2 = ex 2

add2 3
(* 5 *)
```

Porque `ex 2` devolve uma nova função:

```ocaml
int -> int
```

Com tuplo, isto **não funciona da mesma forma**:

```ocaml
let ex (a, b) = a + b

let add2 = ex 2
(* erro *)
```

Porque `ex` espera um tuplo `(a, b)`, não apenas `a`.

## Quando usar cada um

Usa:

```ocaml
let ex a b = ...
```

quando queres uma função normal, reutilizável e que suporte aplicação parcial.

Usa:

```ocaml
let ex (a, b) = ...
```

quando a função naturalmente recebe um par, por exemplo vindo de uma lista de tuplos:

```ocaml
let pairs = [(1, 2); (3, 4)]

List.map ex pairs
```

Resumo:

```ocaml
let ex (a, b) = ...
(* recebe 1 argumento: um tuplo *)

let ex a b = ...
(* recebe 2 argumentos: curried *)
```

> como concatenar duas strings em ocaml?

Usa o operador `^`:

```ocaml
let nome = "Luis"
let msg = "Olá, " ^ nome ^ "!"
```

Resultado:

```ocaml
"Olá, Luis!"
```

> como compilar um arquivo ocaml em binario ?

Para compilar um arquivo OCaml para binário:

```bash
ocamlc -o programa programa.ml
```

Executar:

```bash
./programa
```

Para binário nativo mais rápido:

```bash
ocamlopt -o programa programa.ml
```

Exemplo:

```bash
ocamlopt -o main main.ml
./main
```

Normalmente, usa `ocamlopt` para gerar executáveis nativos.

> como usar o process builder do java para ler saidas de um programa

```java
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class HelloWorld {
    public static void main(String[] args) {
        try {
            ProcessBuilder pb = new ProcessBuilder("./programa_ocaml");
            pb.redirectErrorStream(true); // junta stdout + stderr

            Process processo = pb.start();

            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(processo.getInputStream()))) {

                String linha;
                while ((linha = reader.readLine()) != null) {
                    System.out.println("OCaml: " + linha);
                }
            }

            int exitCode = processo.waitFor();
            System.out.println("Processo terminou com código: " + exitCode);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

Compilar e executar:

```bash
javac HelloWorld.java
java HelloWorld
```

Assumindo que o binário OCaml foi criado assim:

```bash
ocamlopt -o programa_ocaml main.ml
```

E está na mesma pasta que o Java.
