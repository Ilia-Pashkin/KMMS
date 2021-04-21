using namespace std;
#include <iostream>
#include <math.h>
#include <omp.h>

double f(double x)
{
    return 4 / (1 + x*x);
}

int main() {
    double x[100];
    double Integral1, Integral2, Integral3;
    double a = 0.0, b = 1.0;
    double h = 0.001;
    const int n = int(round((b - a) / h));

    for(int i = 1; i <= n; i++){
        Integral1 = Integral1 + h * f(a + h * (i - 0.5));
    }
    cout << "Sequenced: " << Integral1 << "\n";

    #pragma omp parallel for num_threads(4)
    for(int i = 1; i <= n; i++){
        Integral2 = Integral2 + h * f(a + h * (i - 0.5));
    }
    cout << "Paralleled: " << Integral2 << "\n";

    #pragma omp parallel for num_threads(4) reduction(+: Integral3)
    for(int i = 1; i <= n; i++){
        Integral3 = Integral3 + h * f(a + h * (i - 0.5));
    }
    cout << "Paralleled with reduction: " << Integral3 << "\n";
}
