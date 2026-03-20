public interface Set {
    int Size(); // Retorna a cardinalidade dum conjunto.

    int Get(int i); // Retorna o i-ésimo elemento dum conjunto. Este método
    // pressupõe que os valores são internamente guardados numa determinada ordem.

    void Store(int v); // Acrescenta um inteiro a um conjunto, caso não esteja já
    // no conjunto. Operação destrutiva.

    boolean Belongs(int v); // Verifica se um inteiro pertence a um conjunto.

    Set Union(Set s); // Cria um NOVO conjunto, cujo conteúdo reúne o conteúdo de
    // dois conjuntos existentes.
    // Operação não destrutiva.

    void Print(); // Escreve no ecrã um conjunto: bonitinho e entre chavetas.
}