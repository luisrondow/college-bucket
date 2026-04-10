#include "log.h"

int main()
{
    Log_msg("Sistema iniciado");
    Log_erro("Ficheiro não encontrado");

    Log_ativar(0);

    Log_msg("Nao deve imprimir");

    return 0;
}