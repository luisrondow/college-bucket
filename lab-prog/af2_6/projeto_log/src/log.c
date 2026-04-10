#include "log.h"
#include <stdio.h>

static int ativo = 1;

void Log_msg(const char *mensagem)
{
    if (ativo == 0)
        return;

    printf("%s\n", mensagem);
}

void Log_erro(const char *erro)
{
    if (ativo == 0)
        return;

    printf("[ERRO] %s\n", erro);
}

void Log_ativar(int estado)
{
    ativo = estado;
}