import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(new BufferedInputStream(System.in));
        while(cin.hasNext()) {
            BigInteger x, y;
            x = cin.nextBigInteger();
            y = cin.nextBigInteger();
            x = x.add(BigInteger.ONE); x = x.subtract(BigInteger.TEN);
            x = x.multiply(BigInteger.ZERO);
            x = x.divide(y); x = x.remainder(y); x = x.mod(y);
            x = x.pow(10); x = x.gcd(y); x = x.abs(); x = x.negate();
            x = x.max(y); x = x.min(y);
            if (x.compareTo(y) > 0) { }
            if (x.equals(y)) { }
            x = new BigInteger("123456");
            x = new BigInteger("1010101", 2);
            x.toString();
            System.out.println(x);
            BigDecimal a, b;
            a = cin.nextBigDecimal();
            b = cin.nextBigDecimal();
            a = a.divide(b, 100, RoundingMode.HALF_UP);
            System.out.println(String.format("%.6f", a));
        }
    }
}
