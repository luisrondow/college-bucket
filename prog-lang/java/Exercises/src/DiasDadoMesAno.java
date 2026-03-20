import java.util.Scanner;

public class DiasDadoMesAno {
    public static final int FEB_BISSEXTO_DAYS = 29;
    public static final int[] DAYS_IN_MONTH = {
            0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    static boolean isBissexto(int ano) {
        return ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0);
    }

    static int getDays(int mes, int ano) {
        if (mes == 2 && isBissexto(ano)) {
            return FEB_BISSEXTO_DAYS;
        }

        return DAYS_IN_MONTH[mes];
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.println("Digite o mes: ");
        int mes = in.nextInt();

        while (mes < 1 || mes > 12) {
            System.out.println("Insira um mês entre 1 e 12");
            mes = in.nextInt();
        }

        System.out.println("Digite o ano: ");
        int ano = in.nextInt();

        while (ano < 0) {
            System.out.println("Ano invalido... Insira novamente: ");
            ano = in.nextInt();
        }

        System.out.println("Este mes tem " + getDays(mes, ano) + " dias");
    }
}
