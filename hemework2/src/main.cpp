#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

class Polynomial; // forward declaration

class Term {
    friend class Polynomial;
private:
    float coef; // coefficient
    int exp;    // exponent
};


class Polynomial {
public:
    Polynomial();                              
    Polynomial Add(const Polynomial& poly);   
    Polynomial Mult(const Polynomial& poly);   
    float Eval(float f);                      
    void NewTerm(float c, int e);              

    void Print();                              

private:
    Term* termArray; 
    int capacity;     
    int terms;       

    void Resize();  
};


Polynomial::Polynomial() {
    capacity = 10;
    terms = 0;
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(float c, int e) {
    if (c == 0) return;
    if (terms == capacity) Resize();
    termArray[terms].coef = c;
    termArray[terms].exp = e;
    ++terms;
}


void Polynomial::Resize() {
    capacity *= 2;
    Term* newArray = new Term[capacity];
    for (int i = 0; i < terms; ++i)
        newArray[i] = termArray[i];
    delete[] termArray;
    termArray = newArray;
}


Polynomial Polynomial::Add(const Polynomial& poly) {
    Polynomial result;
    int a = 0, b = 0;
    while (a < terms && b < poly.terms) {
        if (termArray[a].exp == poly.termArray[b].exp) {
            float sum = termArray[a].coef + poly.termArray[b].coef;
            if (sum != 0.0)
                result.NewTerm(sum, termArray[a].exp);
            ++a; ++b;
        } else if (termArray[a].exp > poly.termArray[b].exp) {
            result.NewTerm(termArray[a].coef, termArray[a].exp);
            ++a;
        } else {
            result.NewTerm(poly.termArray[b].coef, poly.termArray[b].exp);
            ++b;
        }
    }
 
    for (; a < terms; ++a)
        result.NewTerm(termArray[a].coef, termArray[a].exp);
    for (; b < poly.terms; ++b)
        result.NewTerm(poly.termArray[b].coef, poly.termArray[b].exp);
    return result;
}


Polynomial Polynomial::Mult(const Polynomial& poly) {
    Polynomial result;
    for (int i = 0; i < terms; ++i) {
        Polynomial temp;
        for (int j = 0; j < poly.terms; ++j) {
            float newCoef = termArray[i].coef * poly.termArray[j].coef;
            int newExp = termArray[i].exp + poly.termArray[j].exp;
            temp.NewTerm(newCoef, newExp);
        }
        result = result.Add(temp);
    }
    return result;
}

Polynomial ReadPolynomialFromInput() {
    Polynomial poly;
    string line;
    getline(cin, line); 
    istringstream iss(line);
    
    float coef;
    int exp;
    while (iss >> coef >> exp) {
        poly.NewTerm(coef, exp);
    }

    return poly;
}

float Polynomial::Eval(float f) {
    float result = 0;
    for (int i = 0; i < terms; ++i)
        result += termArray[i].coef * pow(f, termArray[i].exp);
    return result;
}


void Polynomial::Print() {
    for (int i = 0; i < terms; ++i) {
        cout << termArray[i].coef << "x^" << termArray[i].exp;
        if (i != terms - 1)
            cout << " + ";
    }
    cout << endl;
}

int main() {
    cout << "請輸入多項式 P1（格式：係數1 次方1 係數2 次方2 ...）：" << endl;
    Polynomial p1 = ReadPolynomialFromInput();

    cout << "請輸入多項式 P2（格式：係數1 次方1 係數2 次方2 ...）：" << endl;
    Polynomial p2 = ReadPolynomialFromInput();

    cout << "P1 = "; p1.Print();
    cout << "P2 = "; p2.Print();

    Polynomial sum = p1.Add(p2);
    cout << "P1 + P2 = "; sum.Print();

    Polynomial prod = p1.Mult(p2);
    cout << "P1 * P2 = "; prod.Print();

    float val;
    cout << "請輸入一個 x 值以計算 P1(x)：" << endl;
    cin >> val;
    cout << "P1(" << val << ") = " << p1.Eval(val) << endl;
    cout << "請輸入一個 x 值以計算 P2(x)：" << endl;
    cin >> val;
    cout << "P2(" << val << ") = " << p2.Eval(val) << endl;

    return 0;
}
