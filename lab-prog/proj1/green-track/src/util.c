#include "util.h"

#include <time.h>

#define SEGUNDOS_POR_DIA 86400

int date_now()
{
    struct tm epoca = {0};
    epoca.tm_year = 2026 - 1900;
    epoca.tm_mon = 0;
    epoca.tm_mday = 1;
    epoca.tm_isdst = -1;

    time_t inicio = mktime(&epoca);
    time_t agora = time(NULL);
    return (int)((agora - inicio) / SEGUNDOS_POR_DIA);
}
