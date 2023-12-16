#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

// НОД
int GreatestCommonDivisor(int a, int b) {
    if (b == 0) {
        return abs(a);
    }
    else {
        return GreatestCommonDivisor(b, a % b);
    }
}

class Rational {
public:
    Rational() {  // дробь по умолчанию — 0/1
        numerator = 0;
        denominator = 1;
    }
    Rational(int new_numerator, int new_denominator) {
        if (new_denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
        // сократим дробь, разделив числитель и знаменатель на их НОД
        numerator = new_numerator / gcd;
        denominator = new_denominator / gcd;
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

    Rational reciprocal() const {
        return Rational(denominator, numerator);
    }

    bool isInteger() const {
        return denominator == 1;
    }

    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

private:
    int numerator;
    int denominator;
};


// сравнение
bool operator == (const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() &&
           lhs.Denominator() == rhs.Denominator();
}

// сложение
Rational operator + (const Rational& lhs, const Rational& rhs) {
    return {
            lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

// вычитание
Rational operator - (const Rational& lhs, const Rational& rhs) {
    return {
            lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

// умножение
Rational operator * (const Rational& lhs, const Rational& rhs) {
    return {
            lhs.Numerator() * rhs.Numerator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

// деление
Rational operator / (const Rational& lhs, const Rational& rhs) {
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

// ввод
istream& operator >> (istream& is, Rational& r) {
    int n, d;
    char c;

    if (is) {
        is >> n >> c >> d;
        if (is) {
            if (c == '/') {
                r = Rational(n, d);
            }
            else {
                is.setstate(ios_base::failbit);
            }
        }
    }

    return is;
}

// вывод
ostream& operator << (ostream& os, const Rational& r) {
    return os << r.Numerator() << '/' << r.Denominator();
}

// отношение порядка
bool operator < (const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).Numerator() < 0;
}


#include <cassert>

void TestDefaultConstructor() {
    Rational r;
    assert(r.Numerator() == 0);
    assert(r.Denominator() == 1);
}

void TestConstructor() {
    Rational r(3, 4);
    assert(r.Numerator() == 3);
    assert(r.Denominator() == 4);
}

void TestEqualOperator() {
    assert(Rational(1, 2) == Rational(1, 2));
    assert(!(Rational(1, 2) == Rational(2, 3)));
}

void TestAddOperator() {
    assert(Rational(1, 2) + Rational(1, 2) == Rational(1, 1));
    assert(Rational(1, 2) + Rational(1, 3) == Rational(5, 6));
}

void TestSubtractOperator() {
    assert(Rational(1, 2) - Rational(1, 2) == Rational(0, 1));
    assert(Rational(1, 2) - Rational(1, 3) == Rational(1, 6));
}

void TestMultiplyOperator() {
    assert(Rational(1, 2) * Rational(2, 3) == Rational(1, 3));
    assert(Rational(3, 4) * Rational(4, 3) == Rational(1, 1));
}

void TestDivideOperator() {
    assert(Rational(1, 2) / Rational(2, 3) == Rational(3, 4));
    assert(Rational(3, 4) / Rational(4, 3) == Rational(9, 16));
}

void TestLessThanOperator() {
    assert(Rational(1, 2) < Rational(2, 3));
    assert(!(Rational(2, 3) < Rational(1, 2)));
}

void TestReciprocal() {
    assert(Rational(2, 3).reciprocal() == Rational(3, 2));
    assert(Rational(3, 4).reciprocal() == Rational(4, 3));
}

void TestIsInteger() {
    assert(Rational(2, 1).isInteger());
    assert(!Rational(2, 3).isInteger());
}

void TestToDouble() {
    assert(Rational(1, 2).toDouble() == 0.5);
    assert(Rational(2, 3).toDouble() == 2.0 / 3.0);
}

int main() {
    TestDefaultConstructor();
    TestConstructor();
    TestEqualOperator();
    TestAddOperator();
    TestSubtractOperator();
    TestMultiplyOperator();
    TestDivideOperator();
    TestLessThanOperator();
    TestReciprocal();
    TestIsInteger();
    TestToDouble();

    cout << "All tests passed." << endl;

    return 0;
}
