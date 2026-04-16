# erros draft

### ex1

#### 1.
A condiçao do while esta seguindo uma má pratica em C. A flag de EOF so fica ativa depois da operacao de leitura falhar, ou seja o while pode aceitar um falso positivo, ocasionando um erro na hora do `fscanf`. O ideal seria usar o proprio fcanf no `while`.

#### 2.
Este codigo tambem nao garante que o CSV esta bem formato e que todos os campos possuem dados, ocasionando possiveis lixos de memoria sendo guardados nas propriedades do item no array `plantas`.

Corrigido

```c
int campos_lidos;

while ((campos_lidos = fscanf(f_plantas, "%d,%[^,],%[^,],%[^,],%d,%d\n",
           &plantas[total_plantas].id,
           plantas[total_plantas].nome,
           plantas[total_plantas].especie,
           plantas[total_plantas].data_plantio,
           &plantas[total_plantas].intervalo_rega,
           &plantas[total_plantas].ultima_rega)) == 6) {
    total_plantas++;
}
```

### ex2

#### 1.
Codicao de parada deveria ser `i < total_plantas` pois o i começa em 0 e faz tracking do index do array, euanquanto total_plantas representa a quantidade. Quando chega-se na condicao aceita de i == total_plantas teria-mos um erro de index out of bounds.

Corrigido

```c
void listar_plantas() {
    printf("=== PLANTAS ===\n");
    for (int i = 0; i < total_plantas; i++) {
        printf("ID: %d | Nome: %s | [...]\n", plantas[i].id, plantas[i].nome,
[...]);
    }
}
```

### ex3

Verificacoes nao feitas:
- se o `id_planta` é de uma planta valida (que existe no array `plantas`)
- se a `data` passada como parametro é um timestamp valido (max_data == date.now())
- se a `quantidade` é um valor poisitivo
- se o array `regas` tem espaços

Corrigido:
```c
int date_now() {...} // retorna o timestamp do dia de hoje

int registar_rega(int id_planta, time_t data, int quantidade) {
    if (total_regas >= MAX_REGAS) {
        printf("Erro: limite maximo de regas atingido.\n");
        return -1;
    }

    int planta_existe = 0;
    for (int i = 0; i < total_plantas; i++) {
        if (plantas[i].id == id_planta) {
            planta_existe = 1;
            break;
        }
    }
    if (!planta_existe) {
        printf("Erro: planta com id %d nao existe.\n", id_planta);
        return -1;
    }

    if (data > date_now()) {
        printf("Erro: data da rega nao pode estar no futuro.\n");
        return -1;
    }

    if (quantidade <= 0) {
        printf("Erro: quantidade de agua deve ser positiva (recebido: %d).\n", quantidade);
        return -1;
    }

    regas[total_regas].id_rega = total_regas + 1;
    regas[total_regas].id_planta = id_planta;
    regas[total_regas].data_rega = data;
    regas[total_regas].quantidade_agua = quantidade;
    total_regas++;

    return 1;
}
```

### ex4

#### 1.
A funçao nao devolve nada (tipo `void`), so imprime quais plantas precisam de rega, nao informa nada para o resto do programa. Pode-se devolver uma lista de IDs das plantas que precisam de regas e podemos, por exemplo:
- automatizar a rega de todas as plantas que precisam de uma vez
- automatizar a criacao de tarefas para todas as plantas que precisam de rega

#### 2.
A funcao esta a misturar duas responsabilidades: imprimir e identificar as plantas que precisam de regas, podemos separar em duas funcoes distintas.

Corrigido
```c

int verificar_rega(int data_atual, int ids[]) {
    int encontradas = 0;
    for (int i = 0; i < total_plantas; i++) {
        if (encontradas >= MAX_PLANTAS) break;  // proteção

        int dias = data_atual - plantas[i].ultima_rega;
        if (dias >= plantas[i].intervalo_rega) {
            ids[encontradas] = plantas[i].id;
            encontradas++;
        }
    }
    return encontradas;
}

void imprimir_plantas_a_regar() {
    int ids[MAX_PLANTAS];
    int n = plantas_precisam_rega(hoje, ids);

    printf("=== %d PLANTAS PRECISAM DE REGA ===\n", n);
    for (int i = 0; i < n; i++) {
        printf("Planta %s (ID: %d) precisa de rega! (ultima: %d dias atras)\n", plantas[i].nome, plantas[i].id, dias);
    }
}
```

### ex5

#### 1.
Verificar se o array tarefas tem espaço.

Corrigido

```c
if (total_tarefas >= MAX_TAREFAS) {
    printf("Erro: limite maximo de tarefas atingido.\n");
    return;
}
```

### ex6

#### 1.
Condicao if com apenas um `=` (atribuicao) inves de dois `==` (comparacao)

Corrigido

```c
if (tarefas[i].concluida == 0) {
```

### ex7

#### 1.
Condicao if com apenas um `=` (atribuicao) inves de dois `==` (comparacao)

Corrigido

```c
if (tarefas[i].id_tarefa == id) {
```

### ex8

#### 1.
Os dados de regas e tarefas nao estao a ser guardados. Ao reiniciar o programa, as plantas estarao la porém não sabes quando foi a última vez que regaste nada (o campo ultima_rega está salvo, mas o historico completo foi-se).

```c
void guardar_dados() {
    FILE *f_plantas = fopen("plantas.csv", "w");
    if (f_plantas == NULL) {
        printf("Erro ao abrir plantas.csv\n");
        return;
    }
    for (int i = 0; i < total_plantas; i++) {
        fprintf(f_plantas, "%d,%s,%s,%s,%d,%d\n",
                plantas[i].id, plantas[i].nome, plantas[i].especie,
                plantas[i].data_plantio, plantas[i].intervalo_rega,
                plantas[i].ultima_rega);
    }
    fclose(f_plantas);

    FILE *f_regas = fopen("regas.csv", "w");
    if (f_regas == NULL) {
        printf("Erro ao abrir regas.csv\n");
        return;
    }
    for (int i = 0; i < total_regas; i++) {
        fprintf(f_regas, "%d,%d,%d,%d\n",
                regas[i].id_rega, regas[i].id_planta,
                regas[i].data_rega, regas[i].quantidade_agua);
    }
    fclose(f_regas);

    FILE *f_tarefas = fopen("tarefas.csv", "w");
    if (f_tarefas == NULL) {
        printf("Erro ao abrir tarefas.csv\n");
        return;
    }
    for (int i = 0; i < total_tarefas; i++) {
        fprintf(f_tarefas, "%d,%s,%d,%d\n",
                tarefas[i].id_tarefa, tarefas[i].descricao,
                tarefas[i].data_prevista, tarefas[i].concluida);
    }
    fclose(f_tarefas);
}
```

### ex9

#### 1.
Quando o programa termina esse dado é apagado da memoria, por isso deve-se persistir os dados chamando a funcao `guardar_dados()` antes de sair do programa independentemente, sem depender da opção "Guardar" no menu.

```c
int main() {
    {...}
    do {
        // ... menu ...
        switch (opcao) {
            case 0:
                guardar_dados();
                printf("Dados guardados com sucesso!\n");
                break;
        }
    } while (opcao != 0);

    guardar_dados();
```

### ex10

#### 1.
O uso de scanf com `%s` é totalmente desaconselhado pois ele nao trata espaços, ele le ate encontrar um espaco ou um `\n` (enter). Deve-se usar fgets para esse uso (lê a linha inteira).

Corrigido
```c
printf("Nome: ");
fgets(nome, sizeof(nome), stdin);
nome[strcspn(nome, "\n")] = '\0';  // remove o \n do fim
```