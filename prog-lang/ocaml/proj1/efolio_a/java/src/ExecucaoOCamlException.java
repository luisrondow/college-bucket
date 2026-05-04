public class ExecucaoOCamlException extends Exception {
    public ExecucaoOCamlException(String mensagem) {
        super(mensagem);
    }

    public ExecucaoOCamlException(String mensagem, Throwable causa) {
        super(mensagem, causa);
    }
}
