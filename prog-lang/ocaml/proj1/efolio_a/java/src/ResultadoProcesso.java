import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class ResultadoProcesso {
    private final int codigoSaida;
    private final List<String> saidaPadrao;
    private final List<String> saidaErro;

    public ResultadoProcesso(int codigoSaida, List<String> saidaPadrao, List<String> saidaErro) {
        this.codigoSaida = codigoSaida;
        this.saidaPadrao = Collections.unmodifiableList(new ArrayList<>(saidaPadrao));
        this.saidaErro = Collections.unmodifiableList(new ArrayList<>(saidaErro));
    }

    public int getCodigoSaida() {
        return codigoSaida;
    }

    public List<String> getSaidaPadrao() {
        return saidaPadrao;
    }

    public List<String> getSaidaErro() {
        return saidaErro;
    }

    public String getSaidaPadraoComoTexto() {
        return String.join(System.lineSeparator(), saidaPadrao);
    }

    public String getSaidaErroComoTexto() {
        return String.join(System.lineSeparator(), saidaErro);
    }

    public boolean terminouComErro() {
        return codigoSaida != 0;
    }
}
