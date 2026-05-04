import java.nio.file.Path;
import java.nio.file.Paths;

public class Aplicacao {
    public static void main(String[] args) {
        try {
            Path executavel = localizarExecutavel(args);
            Path diretorioBoletins = localizarDiretorioBoletins(executavel);

            IntegradorOCaml integradorOCaml = new IntegradorOCaml(executavel);
            Menu menu = new Menu(integradorOCaml, diretorioBoletins);
            menu.iniciar();
        } catch (IllegalArgumentException e) {
            System.out.println("Erro: " + e.getMessage());
            System.out.println("Utilizacao: java Aplicacao [caminho_do_executavel_ocaml]");
        }
    }

    private static Path localizarExecutavel(String[] args) {
        if (args.length > 1) {
            throw new IllegalArgumentException("Numero de argumentos invalido.");
        }

        if (args.length == 1 && !args[0].trim().isEmpty()) {
            return Paths.get(args[0]);
        }

        String variavelAmbiente = System.getenv("OCAML_EXECUTAVEL");
        if (variavelAmbiente != null && !variavelAmbiente.trim().isEmpty()) {
            return Paths.get(variavelAmbiente);
        }

        Path[] candidatos = {
            Paths.get("main.exe"),
            Paths.get("efolio_a", "main.exe"),
            Paths.get("_build", "default", "bin", "main.exe"),
            Paths.get("efolio_a", "_build", "default", "bin", "main.exe")
        };

        for (Path candidato : candidatos) {
            if (candidato.toFile().exists()) {
                return candidato;
            }
        }

        return Paths.get("main.exe");
    }

    private static Path localizarDiretorioBoletins(Path executavel) {
        Path absoluto = executavel.toAbsolutePath().normalize();
        Path parent = absoluto.getParent();

        if (parent != null && "bin".equals(parent.getFileName().toString())) {
            Path defaultDir = parent.getParent();
            if (defaultDir != null && "default".equals(defaultDir.getFileName().toString())) {
                Path buildDir = defaultDir.getParent();
                if (buildDir != null && "_build".equals(buildDir.getFileName().toString())) {
                    Path projeto = buildDir.getParent();
                    if (projeto != null) {
                        return projeto.resolve("boletins");
                    }
                }
            }
        }

        if (parent != null) {
            return parent.resolve("boletins");
        }

        return Paths.get("boletins");
    }
}
