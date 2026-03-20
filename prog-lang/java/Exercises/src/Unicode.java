import java.util.Scanner;

public class Unicode {
    public static void main(String[] args) {
        System.out.println("Insira o código Unicode: ");
        int i;
        char c;
        Scanner in = new Scanner(System.in);

        do {
            i = in.nextInt();

            if (i < 33 || i > 127) {
                System.out.println("Valor deve ser um numero inteiro entre 33 e 127");
            }
        } while (i < 33 || i > 127);

        c = (char)i;
        System.out.println("Codigo: " + i + " - Caracter: " + c );
    }
}
