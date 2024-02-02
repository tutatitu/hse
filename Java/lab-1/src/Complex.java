public class Complex {
    private double real, imaginary;

    public Complex() {
        this(0, 0);
    }

    public Complex(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public Complex(Complex complex) {
        this.real = complex.real;
        this.imaginary = complex.imaginary;
    }

    public void equals(Complex complex) {
        this.real = complex.real;
        this.imaginary = complex.imaginary;
    }

    public Complex add(Complex complex) {
        return new Complex(this.real + complex.real, this.imaginary + complex.imaginary);
    }

    public Complex subtract(Complex complex) {
        return new Complex(this.real - complex.real, this.imaginary - complex.imaginary);
    }

    public Complex multiply(Complex complex) {
        return new Complex(this.real * complex.real - this.imaginary * complex.imaginary, this.imaginary * complex.real + this.real * complex.imaginary);
    }

    public Complex divide(Complex complex) {
        double d = Math.pow(complex.real, 2) + Math.pow(complex.imaginary, 2);
        if (d == 0) {
            return complex;
        }
        double _real = this.real * complex.real + this.imaginary * complex.imaginary;
        double _imaginary = this.imaginary * complex.real - this.real * complex.imaginary;
        return new Complex(_real / d, _imaginary / d);
    }

    public String print() {
        if (this.imaginary > 0) {
            return this.real + "+" + this.imaginary + "i";
        } else if (this.imaginary < 0) {
            return this.real + "" + this.imaginary + "i";
        } else {
            return this.real + "";
        }
    }
}