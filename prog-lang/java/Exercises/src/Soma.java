import java.util.Scanner;

public class Soma {
    public static void main(String[] args) {

        System.out.println("Voce deseja somar inteiros ou numeros com ponto flutuante: ");
        System.out.println("1 - Inteiros");
        System.out.println("2 - Float");
        System.out.println("===");

        Scanner in = new Scanner(System.in);
        int option = in.nextInt();

        while (option != 1 && option != 2) {
            System.out.println("Opcao Invalida, escolha novamente: ");
            option = in.nextInt();
        }

        if (option == 1) {
            int num1, num2;
            System.out.println("Insira o 1 numero");
            num1 = in.nextInt();

            System.out.println("Insira o 2 numero");
            num2 = in.nextInt();

            System.out.println("Resultado: " + (num1 + num2));
        }

        if (option == 2) {
            float fnum1, fnum2;
            System.out.println("Insira o 1 numero");
            fnum1 = in.nextFloat();

            System.out.println("Insira o 2 numero");
            fnum2 = in.nextFloat();

            System.out.println("Resultado: " + (fnum1 + fnum2));
        }
    }
}
