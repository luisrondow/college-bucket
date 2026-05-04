package java_integration;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class HelloWorld {
    public static void main(String[] args) {
        try {
            ProcessBuilder pb = new ProcessBuilder("./hello");
            pb.redirectErrorStream(true);

            Process processo = pb.start();

            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(processo.getInputStream()))) {

                String linha;
                while ((linha = reader.readLine()) != null) {
                    System.out.println("OCaml: " + linha);
                }
            }

            int exitCode = processo.waitFor();
            System.out.println("Processo terminou com código: " + exitCode);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}