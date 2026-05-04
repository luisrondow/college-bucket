# OCaml

OCaml exercises, study notes, and small integration projects for the Programming Languages subject.

## Contents

| Path | Description |
|------|-------------|
| [fact.ml](./fact.ml) | Recursive factorial example |
| [lists.ml](./lists.ml) | List recursion exercises |
| [parking.ml](./parking.ml) | Parking price calculation exercise |
| [annotations.md](./annotations.md) | Notes on OCaml syntax, compilation, and Java `ProcessBuilder` integration |
| [java_integration](./java_integration) | Minimal Java program that executes an OCaml binary |
| [proj1/efolio_a](./proj1/efolio_a) | e-Folio A project combining an OCaml command-line program with a Java menu |

## Java Integration Example

From this directory:

```bash
cd java_integration
ocamlopt -o hello hello.ml
javac HelloWorld.java
java -cp .. java_integration.HelloWorld
```

## e-Folio A

See [proj1/efolio_a/README.md](./proj1/efolio_a/README.md) for the full build and execution steps.
