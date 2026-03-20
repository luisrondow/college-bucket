public class GestorCurso {
    static final int NOTA_MIN = 0;
    static final int NOTA_MAX = 20;

    static void printInfo(char [][] info) {
        for (int i = 0; i < info.length; i++) {
            StringBuilder s = new StringBuilder();
            for (int j = 0; j < info[i].length; j++) {
                s.append(info[i][j]);
            }

            System.out.println(i + "-" + s);
        }
    }

    static void mediaDoCurso(char [][] info, int[] notas_das_disciplinas) {
        printInfo(info);
        float s = 0;

        for (int nota : notas_das_disciplinas) {
            s += nota;
        }

        System.out.println("Media: " + Math.round(s / notas_das_disciplinas.length));
    }

    static void maximoNota(char [][] info, int[] notas_das_disciplinas) {
        printInfo(info);
        int max = NOTA_MIN;

        for (int nota : notas_das_disciplinas) {
            if (nota > max) {
                max = nota;
            }
        }

        System.out.println("Max: " + max);
    }

    static void minimoNota(char [][] info, int[] notas_das_disciplinas) {
        printInfo(info);
        int min = NOTA_MAX;

        for (int nota : notas_das_disciplinas) {
            if (nota < min) {
                min = nota;
            }
        }

        System.out.println("Min: " + min);
    }

    public static void main(String[] args) {
        char[][] info = {
                {'L', 'I', 'C', 'E', 'N', 'C', 'I', 'A', 'T', 'U', 'R', 'A', ' ', 'I', 'N', 'F', 'O', 'R', 'M', 'A', 'T', 'I', 'C', 'A'},
                {'L', 'I', 'N', 'G', 'U', 'A', 'G', 'E', 'N', 'S', ' ', 'D', 'E', ' ', 'P', 'R', 'O', 'G', 'R', 'A', 'M', 'A', 'C', 'A', 'O'}
        };
        int[] notas = {11, 12, 13, 14, 15, 16, 17};

        mediaDoCurso(info, notas);
        maximoNota(info, notas);
         minimoNota(info, notas);
    }
}
