import java.util.Scanner;

public class ValidarIdade {
    static void validarIdade(int idade) {
        if (idade < 0) {
            System.out.println("Idade invalida");

            return;
        }

        if (idade <  15) {
            System.out.println("Crianca");
            return;
        }

        if (idade < 18) {
            System.out.println("Adolescente");
            return;
        }

        if (idade < 66) {
            System.out.println("Adulto");
            return;
        }

        System.out.println("Idoso");
    }

    public static void main(String[] args) {
        System.out.println("Digite sua idade: ");
        Scanner in = new Scanner(System.in);

        int idade = in.nextInt();
        validarIdade(idade);
    }
}
