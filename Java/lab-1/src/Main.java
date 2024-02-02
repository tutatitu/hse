import java.util.Random;

public class Main {
    public static void main(String[] args) {
        test();
    }

    public static void test() {
        Random random = new Random();

        System.out.println("First matrix:");
        Matrix FirstMatrix = new Matrix(3, 3);
        for (int i = 0; i < FirstMatrix.getN(); ++i) {
            for (int j = 0; j < FirstMatrix.getM(); ++j) {
                FirstMatrix.set(i, j, new Complex((double) (random.nextInt(9)) + 1, random.nextInt(3)));
            }
        }
        FirstMatrix.print();
        System.out.println();

        System.out.println("Second matrix:");
        Matrix SecondMatrix = new Matrix(3, 3);
        for (int i = 0; i < SecondMatrix.getN(); ++i) {
            for (int j = 0; j < SecondMatrix.getM(); ++j) {
                SecondMatrix.set(i, j, new Complex((double) (random.nextInt(9)) + 1, random.nextInt(2)));
            }
        }
        SecondMatrix.print();
        System.out.println();

        System.out.println("FirstMatrix + SecondMatrix:");
        Matrix matrix_add = new Matrix(FirstMatrix.add(SecondMatrix));
        matrix_add.print();
        System.out.println();

        System.out.println("FirstMatrix * SecondMatrix:");
        Matrix matrix_mult = new Matrix(FirstMatrix.multiply(SecondMatrix));
        matrix_mult.print();
        System.out.println();

        System.out.println("FirstMatrix^T:");
        Matrix matrix_transpose = new Matrix(FirstMatrix.transpose());
        matrix_transpose.print();
        System.out.println();

        System.out.print("det(FirstMatrix): ");
        Complex matrix_det = new Complex(FirstMatrix.determinant());
        System.out.println(matrix_det.print());
        System.out.println();
    }
}
