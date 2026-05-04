import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class IntegradorOCaml {
    private final Path executavel;

    public IntegradorOCaml(Path executavel) {
        this.executavel = executavel.toAbsolutePath().normalize();
    }

    public Path getExecutavel() {
        return executavel;
    }

    public ResultadoProcesso executar(String comando, String... argumentos) throws ExecucaoOCamlException {
        validarExecutavel();

        List<String> comandoCompleto = new ArrayList<>();
        comandoCompleto.add(executavel.toString());
        comandoCompleto.add(comando);
        comandoCompleto.addAll(Arrays.asList(argumentos));

        ProcessBuilder processBuilder = new ProcessBuilder(comandoCompleto);
        processBuilder.directory(detectarDiretorioTrabalho().toFile());

        try {
            Process processo = processBuilder.start();
            ExecutorService leitores = Executors.newFixedThreadPool(2);

            Future<List<String>> stdout = leitores.submit(() -> lerLinhas(processo.getInputStream()));
            Future<List<String>> stderr = leitores.submit(() -> lerLinhas(processo.getErrorStream()));

            int codigo = processo.waitFor();
            ResultadoProcesso resultado = new ResultadoProcesso(codigo, stdout.get(), stderr.get());
            leitores.shutdown();

            if (resultado.terminouComErro()) {
                throw new ExecucaoOCamlException(criarMensagemErro(comandoCompleto, resultado));
            }

            return resultado;
        } catch (IOException e) {
            throw new ExecucaoOCamlException("Nao foi possivel iniciar o processo OCaml: " + e.getMessage(), e);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new ExecucaoOCamlException("A execucao do processo OCaml foi interrompida.", e);
        } catch (ExecutionException e) {
            throw new ExecucaoOCamlException("Nao foi possivel ler a saida do processo OCaml.", e);
        }
    }

    private void validarExecutavel() throws ExecucaoOCamlException {
        if (!Files.exists(executavel)) {
            throw new ExecucaoOCamlException(
                "Executavel OCaml nao encontrado: " + executavel
                    + System.lineSeparator()
                    + "Compile o projeto com 'dune build' ou indique o caminho do executavel ao iniciar o Java."
            );
        }

        if (!Files.isRegularFile(executavel)) {
            throw new ExecucaoOCamlException("O caminho indicado nao e um ficheiro regular: " + executavel);
        }

        if (!Files.isExecutable(executavel)) {
            throw new ExecucaoOCamlException("O ficheiro OCaml nao tem permissao de execucao: " + executavel);
        }
    }

    private List<String> lerLinhas(InputStream inputStream) throws IOException {
        List<String> linhas = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(
            new InputStreamReader(inputStream, StandardCharsets.UTF_8))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                linhas.add(linha);
            }
        }

        return linhas;
    }

    private Path detectarDiretorioTrabalho() {
        Path parent = executavel.getParent();

        if (parent != null && "bin".equals(parent.getFileName().toString())) {
            Path defaultDir = parent.getParent();
            if (defaultDir != null && "default".equals(defaultDir.getFileName().toString())) {
                Path buildDir = defaultDir.getParent();
                if (buildDir != null && "_build".equals(buildDir.getFileName().toString())) {
                    Path projeto = buildDir.getParent();
                    if (projeto != null) {
                        return projeto;
                    }
                }
            }
        }

        if (parent != null) {
            return parent;
        }

        return Paths.get(".").toAbsolutePath().normalize();
    }

    private String criarMensagemErro(List<String> comandoCompleto, ResultadoProcesso resultado) {
        StringBuilder mensagem = new StringBuilder();
        mensagem.append("O processo OCaml terminou com codigo ")
            .append(resultado.getCodigoSaida())
            .append(".")
            .append(System.lineSeparator())
            .append("Comando: ")
            .append(String.join(" ", comandoCompleto));

        if (!resultado.getSaidaErro().isEmpty()) {
            mensagem.append(System.lineSeparator())
                .append("Erro: ")
                .append(resultado.getSaidaErroComoTexto());
        }

        if (!resultado.getSaidaPadrao().isEmpty()) {
            mensagem.append(System.lineSeparator())
                .append("Saida parcial: ")
                .append(resultado.getSaidaPadraoComoTexto());
        }

        return mensagem.toString();
    }
}
