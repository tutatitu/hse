public class Matrix {
    private Complex[][] matrix;
    private int n, m;

    public Matrix(int n, int m) {
        if (n <= 0 || m <= 0)
            return;
        this.n = n;
        this.m = m;
        this.matrix = new Complex[n][m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                this.matrix[i][j] = new Complex();
            }
        }
    }

    public Matrix(Matrix matrix) {
        this.n = matrix.n;
        this.m = matrix.m;
        this.matrix = new Complex[this.n][this.m];
        for (int i = 0; i < this.n; ++i) {
            for (int j = 0; j < this.m; ++j) {
                this.matrix[i][j] = new Complex();
                this.matrix[i][j] = matrix.get(i, j);
            }
        }
    }

    public int getN() {
        return n;
    }

    public int getM() {
        return m;
    }

    public void set(int i, int j, Complex number) {
        if (i < 0 || j < 0 || i >= this.n || j >= this.m)
            return;
        this.matrix[i][j] = number;
    }

    public Complex get(int i, int j) {
        if (i < 0 || j < 0 || i >= this.n || j >= this.m)
            return null;
        return this.matrix[i][j];
    }

    public Matrix add(Matrix matrix) {
        if (this.n != matrix.n || this.m != matrix.m)
            return this;
        Matrix copy = new Matrix(this);
        for (int i = 0; i < this.n; ++i) {
            for (int j = 0; j < this.m; ++j) {
                copy.set(i, j, copy.get(i, j).add(matrix.get(i, j)));
            }
        }
        return copy;
    }

    public Matrix multiply(Matrix matrix) {
        if (this.m != matrix.n)
            return this;
        Matrix result = new Matrix(this.n, matrix.m);
        for (int i = 0; i < result.n; ++i) {
            for (int j = 0; j < result.m; ++j) {
                Complex sum = new Complex();
                for (int k = 0; k < this.m; ++k) {
                    sum.equals(sum.add(this.matrix[i][k].multiply(matrix.get(k, j))));
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }

    public Matrix transpose() {
        Matrix result = new Matrix(this.m, this.n);
        for (int i = 0; i < this.n; ++i) {
            for (int j = 0; j < this.m; ++j) {
                result.set(j, i, this.get(i, j));
            }
        }
        return result;
    }

    public Complex determinant() {
        Matrix matrix = new Matrix(this);
        if (matrix.n != matrix.m)
            throw new IllegalArgumentException("Матрица должна быть квадратной.");
        for (int k = 0; k < matrix.n - 1; ++k) {
            for (int i = k + 1; i < matrix.n; ++i) {
                Complex factor = matrix.get(i, k).divide(matrix.get(k, k));
                for (int j = k; j < matrix.n; ++j) {
                    matrix.set(i, j, matrix.get(i, j).subtract(factor.multiply(matrix.get(k, j))));
                }
//                matrix.print();
//                System.out.println();
            }
        }

        Complex determinant = new Complex(1.0, 0);
        for (int i = 0; i < matrix.n; i++) {
            determinant.equals(determinant.multiply(matrix.get(i, i)));
        }

        return determinant;
    }

    public void print() {
        for (int i = 0; i < this.n; i++) {
            for (int j = 0; j < this.n; j++) {
                this.get(i, j).print();
            }
            System.out.println();
        }
        System.out.println();
    }
}
