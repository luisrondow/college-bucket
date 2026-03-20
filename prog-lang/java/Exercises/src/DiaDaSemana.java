import java.util.Scanner;

public class DiaDaSemana {
    static int getWeekday(int day, int month, int year) {
        int century = year/100;
        int centuryYear = year % 100;

        return (day + 26*(month+1)/10 + centuryYear + centuryYear/4 + century/4 + 5*century) % 7;
    }

    static String getWeekDayName(int dayIndex) {
        return switch (dayIndex) {
            case 0 -> "Sabado";
            case 1 -> "Domingo";
            case 2 -> "Segunda";
            case 3 -> "Terca";
            case 4 -> "Quarta";
            case 5 -> "Quinta";
            case 6 -> "Sexta";
            default -> "Dia invalido";
        };
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

        System.out.println("Digite o dia: ");
        int dia = in.nextInt();
        int maxDays = DiasDadoMesAno.getDays(mes, ano);

        while (dia < 1 || dia > DiasDadoMesAno.getDays(mes, ano)) {
            System.out.println("O mes " + mes + " so tem dias entre 1 e " + maxDays);
            dia = in.nextInt();
        }

        System.out.println("Para a data: " + dia + "/" + mes + "/" + ano + " (" + (DiasDadoMesAno.isBissexto(ano) ? "É bissexto" : "Nao é bissexto") + ")" );
        System.out.println("O dia da semana é: " + getWeekDayName(getWeekday(dia, mes, ano)));
    }
}
