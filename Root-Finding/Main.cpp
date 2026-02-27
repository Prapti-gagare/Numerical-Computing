#include "./include/root.hpp"

int main()
{
    try
    {

        bisect b;
        newton n;
        fixedpoint f(0.5);
        root *r1=&b;
        double root1 = r1->solve();
        root *r2=&n;
        double root2 = r2->solve();
        root *r3=&f;
        double root3 = r3->solve();
        cout << "Bisection Root   = "<<root1<< "  Iterations = " << b.itr <<endl;
        cout << "Newton Root      = "<<root2<< "Iterations = " << n.itr <<endl;
        cout << "Fixed Point Root = "<<root3<< " terations = " << f.itr <<endl;
        if (n.itr <= b.itr && n.itr <= f.itr)
            cout << "Newton Raphson converges fastest.\n";
        else if (b.itr <= f.itr)
            cout << "Bisection converges faster than Fixed Point.\n";
        else
            cout << "Fixed Point converges faster than Bisection.\n";
    }
    catch (exception &e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}
