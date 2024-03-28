#include <iostream>
#include <fstream>
using namespace std;

class Vector {
    int* p = nullptr; // Указатель на массив значений вектора
    int n = 0; // Размер вектора

public:
    Vector(int* p, int n) { // Конструктор для создания вектора из массива значений
        this->n = n;
        this->p = new int[n];
        for (int i = 0; i < n; i++) this->p[i] = p[i];
    }

    Vector(int n) : n(n) { // Конструктор для создания пустого вектора заданного размера
        p = new int[n]();
    }

    Vector(const Vector& V) {
        n = V.n;
        p = new int[n];
        for (int i = 0; i < n; i++)
            p[i] = V.p[i];
    }

    Vector(Vector&& V) {
        std::swap(p, V.p);
        std::swap(n, V.n);
    }

    void print() const { // Метод для вывода значений вектора
        for (int i = 0; i < n; i++)
            cout << p[i] << " ";
        cout << endl;
    }

    int& operator[](int index) { // Перегруженный оператор индексации
        return p[index];
    }

    Vector& operator =(const Vector& v2) { // Перегруженный оператор присваивания с копированием
        if (this != &v2) { // Проверка, чтобы не было исключений
            n = v2.n;
            if (p != nullptr) delete[] p;
            p = new int[n];
            for (int i = 0; i < n; i++)
                p[i] = v2.p[i];
        }
        return *this;
    }

    Vector& operator =(Vector&& v2) { // Перегруженный оператор присваивания с перемещением
        if (this != &v2) { // Проверка, чтобы вызвалось без исключений
            std::swap(p, v2.p);
            std::swap(n, v2.n);
        }
        return *this;
    }

    bool operator<(const Vector& v2) const {
        if (n != v2.n) {
            return false;
        }

        for (int i = 0; i < n; ++i) {
            if (p[i] >= v2.p[i]) {
                return false;
            }
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const Vector& v) { // Перегруженный оператор вывода в поток
        for (int i = 0; i < v.n; i++) // Вывод значений вектора через поток вывода
            os << v.p[i] << " ";
        return os;
    }

    friend istream& operator>>(istream& is, Vector& v) { // Перегруженный оператор ввода из потока
        for (int i = 0; i < v.n; i++) // Считывание значений вектора из потока ввода
            is >> v.p[i];
        return is;
    }

    ~Vector() { // Деструктор класса
        delete[] p;
    }
};

int main() {
    ifstream input("input.txt");
    int size = 0;
    int size1 = 0;
    input >> size;
    input >> size1;
    int* values = new int[size];
    for (int i = 0; i < size; ++i) {
        input >> values[i];
    }
    int* values1 = new int[size1];
    for (int i = 0; i < size1; ++i) {
        input >> values1[i];
    }
    Vector v1(values, size);
    Vector v2(values1, size1);
    bool res = v1 < v2;
    cout << res;
    delete[] values;
    delete[] values1;
}