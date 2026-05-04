import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.OffsetDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Menu {
    private final IntegradorOCaml integradorOCaml;
    private final Scanner scanner;
    private final Path diretorioBoletins;

    public Menu(IntegradorOCaml integradorOCaml, Path diretorioBoletins) {
        this.integradorOCaml = integradorOCaml;
        this.scanner = new Scanner(System.in);
        this.diretorioBoletins = diretorioBoletins.toAbsolutePath().normalize();
    }

    public void iniciar() {
        boolean ativo = true;

        while (ativo) {
            mostrarOpcoes();
            String opcao = scanner.nextLine().trim();

            try {
                switch (opcao) {
                    case "1":
                        executarEApresentar("Listagem de alunos", "listar_alunos");
                        break;
                    case "2":
                        executarIndicadores();
                        break;
                    case "3":
                        executarAvaliacao();
                        break;
                    case "4":
                        executarEApresentar("Estados finais", "listar_estados");
                        break;
                    case "5":
                        emitirBoletim();
                        break;
                    case "0":
                        ativo = false;
                        System.out.println("Aplicacao terminada.");
                        break;
                    default:
                        System.out.println("Opcao invalida. Escolha uma opcao do menu.");
                        break;
                }
            } catch (ExecucaoOCamlException | IOException e) {
                System.out.println("Erro: " + e.getMessage());
            }

            if (ativo) {
                System.out.println();
            }
        }
    }

    private void mostrarOpcoes() {
        System.out.println("=== Integrador Java / OCaml ===");
        System.out.println("Executavel OCaml: " + integradorOCaml.getExecutavel());
        System.out.println("1 - Listar alunos");
        System.out.println("2 - Consultar indicadores de um aluno");
        System.out.println("3 - Avaliar aluno");
        System.out.println("4 - Listar estados finais");
        System.out.println("5 - Emitir boletim JSON de aluno");
        System.out.println("0 - Sair");
        System.out.print("Opcao: ");
        System.out.flush();
    }

    private void executarIndicadores() throws ExecucaoOCamlException {
        int alunoId = lerIdAlunoExistente();
        executarEApresentar("Indicadores do aluno " + alunoId, "indicadores", String.valueOf(alunoId));
    }

    private void executarAvaliacao() throws ExecucaoOCamlException {
        int alunoId = lerIdAlunoExistente();
        executarEApresentar("Avaliacao do aluno " + alunoId, "avaliar", String.valueOf(alunoId));
    }

    private void emitirBoletim() throws ExecucaoOCamlException, IOException {
        int alunoId = lerIdAlunoExistente();
        ResultadoProcesso indicadores = integradorOCaml.executar("indicadores", String.valueOf(alunoId));
        ResultadoProcesso avaliacao = integradorOCaml.executar("avaliar", String.valueOf(alunoId));
        ResultadoProcesso estados = integradorOCaml.executar("listar_estados");

        apresentarSaida("Indicadores", indicadores);
        apresentarSaida("Avaliacao", avaliacao);
        apresentarSaida("Listar estados", estados);

        Files.createDirectories(diretorioBoletins);
        Path ficheiro = diretorioBoletins.resolve("boletim_aluno_" + alunoId + ".json");
        Files.write(
            ficheiro,
            criarJsonBoletim(alunoId, indicadores, avaliacao, estados).getBytes(StandardCharsets.UTF_8)
        );

        System.out.println("Boletim gravado em: " + ficheiro);
    }

    private int lerIdAluno() {
        while (true) {
            System.out.print("ID do aluno: ");
            System.out.flush();
            String entrada = scanner.nextLine().trim();

            try {
                int alunoId = Integer.parseInt(entrada);
                if (alunoId > 0) {
                    return alunoId;
                }
                System.out.println("O ID deve ser um numero inteiro positivo.");
            } catch (NumberFormatException e) {
                System.out.println("ID invalido. Introduza um numero inteiro.");
            }
        }
    }

    private int lerIdAlunoExistente() throws ExecucaoOCamlException {
        while (true) {
            int alunoId = lerIdAluno();
            if (alunoExiste(alunoId)) {
                return alunoId;
            }

            System.out.println("Aluno nao encontrado na base de dados.");
        }
    }

    private boolean alunoExiste(int alunoId) throws ExecucaoOCamlException {
        ResultadoProcesso listagem = integradorOCaml.executar("listar_alunos");
        String prefixo = "ID: " + alunoId + " |";

        for (String linha : listagem.getSaidaPadrao()) {
            if (linha.startsWith(prefixo)) {
                return true;
            }
        }

        return false;
    }

    private void executarEApresentar(String titulo, String comando, String... argumentos)
        throws ExecucaoOCamlException {
        ResultadoProcesso resultado = integradorOCaml.executar(comando, argumentos);
        apresentarSaida(titulo, resultado);
    }

    private void apresentarSaida(String titulo, ResultadoProcesso resultado) {
        System.out.println();
        System.out.println("----- " + titulo + " -----");

        if (resultado.getSaidaPadrao().isEmpty()) {
            System.out.println("(sem saida)");
        } else {
            for (String linha : resultado.getSaidaPadrao()) {
                System.out.println("  " + linha);
            }
        }
    }

    private String criarJsonBoletim(
        int alunoId,
        ResultadoProcesso indicadores,
        ResultadoProcesso avaliacao,
        ResultadoProcesso estados
    ) {
        StringBuilder json = new StringBuilder();

        json.append("{").append(System.lineSeparator());
        adicionarCampo(json, 1, "alunoId", String.valueOf(alunoId), false, true);
        adicionarCampo(json, 1, "geradoEm", OffsetDateTime.now().format(DateTimeFormatter.ISO_OFFSET_DATE_TIME), true, true);
        adicionarCampo(json, 1, "executavelOCaml", integradorOCaml.getExecutavel().toString(), true, true);
        adicionarBlocoSaida(json, "indicadores", "indicadores", Arrays.asList(String.valueOf(alunoId)), indicadores, true);
        adicionarBlocoSaida(json, "avaliar", "avaliar", Arrays.asList(String.valueOf(alunoId)), avaliacao, true);
        adicionarBlocoSaida(json, "listar_estados", "listar_estados", Arrays.asList(), estados, false);
        json.append("}").append(System.lineSeparator());

        return json.toString();
    }

    private void adicionarBlocoSaida(
        StringBuilder json,
        String nome,
        String comando,
        List<String> argumentos,
        ResultadoProcesso resultado,
        boolean adicionarVirgula
    ) {
        json.append("  \"").append(escaparJson(nome)).append("\": {").append(System.lineSeparator());
        adicionarCampo(json, 2, "comando", comando, true, true);
        adicionarArray(json, 2, "argumentos", argumentos, true);
        adicionarCampo(json, 2, "codigoSaida", String.valueOf(resultado.getCodigoSaida()), false, true);
        adicionarCampo(json, 2, "saidaPadrao", resultado.getSaidaPadraoComoTexto(), true, false);
        json.append("  }");

        if (adicionarVirgula) {
            json.append(",");
        }

        json.append(System.lineSeparator());
    }

    private void adicionarCampo(
        StringBuilder json,
        int nivel,
        String nome,
        String valor,
        boolean texto,
        boolean virgula
    ) {
        json.append(identar(nivel))
            .append("\"")
            .append(escaparJson(nome))
            .append("\": ");

        if (texto) {
            json.append("\"").append(escaparJson(valor)).append("\"");
        } else {
            json.append(valor);
        }

        if (virgula) {
            json.append(",");
        }

        json.append(System.lineSeparator());
    }

    private void adicionarArray(
        StringBuilder json,
        int nivel,
        String nome,
        List<String> valores,
        boolean virgula
    ) {
        json.append(identar(nivel))
            .append("\"")
            .append(escaparJson(nome))
            .append("\": [");

        for (int i = 0; i < valores.size(); i++) {
            if (i > 0) {
                json.append(", ");
            }
            json.append("\"").append(escaparJson(valores.get(i))).append("\"");
        }

        json.append("]");

        if (virgula) {
            json.append(",");
        }

        json.append(System.lineSeparator());
    }

    private String identar(int nivel) {
        StringBuilder espacos = new StringBuilder();
        for (int i = 0; i < nivel; i++) {
            espacos.append("  ");
        }
        return espacos.toString();
    }

    private String escaparJson(String valor) {
        StringBuilder escapado = new StringBuilder();

        for (int i = 0; i < valor.length(); i++) {
            char ch = valor.charAt(i);
            switch (ch) {
                case '\\':
                    escapado.append("\\\\");
                    break;
                case '"':
                    escapado.append("\\\"");
                    break;
                case '\n':
                    escapado.append("\\n");
                    break;
                case '\r':
                    escapado.append("\\r");
                    break;
                case '\t':
                    escapado.append("\\t");
                    break;
                default:
                    if (ch < 32) {
                        escapado.append(String.format("\\u%04x", (int) ch));
                    } else {
                        escapado.append(ch);
                    }
                    break;
            }
        }

        return escapado.toString();
    }
}
