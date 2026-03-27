#include "matrix.hpp"
#include "LinearSystem.hpp"
#include "gauss_jacobi.hpp"
#include "gauss_seidle.hpp"
#include "gaussian.hpp"
#include "dolittle.hpp"
#include "crouts.hpp"
#include "cholsky.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    string leftFile, rightFile, augFile;

    cout << "Enter left matrix file (A):  "; cin >> leftFile;
    cout << "Enter right matrix file (b): "; cin >> rightFile;
    cout << "Enter augmented output file: "; cin >> augFile;

    try
    {
        ifstream left(leftFile);
        if (!left) throw runtime_error("Cannot open left matrix file: " + leftFile);

        int lr, lc;
        left >> lr >> lc;
        Matrix A(lr, lc);
        A.readFromFile(left);
        left.close();

        cout << "\nLeft Matrix A (" << lr << "x" << lc << "):\n" << A;

    
        cout << "\nMatrix Properties:\n";
        cout << "  Is Square:" << (A.isSquare()? "Yes" : "No") << "\n";
        cout << "  Is Null:" << (A.isNull() ? "Yes" : "No") << "\n";

        if (A.isSquare())
        {
            cout << "  Is Identity:" << (A.isIdentity()? "Yes" : "No") << "\n";
            cout << "  Is Symmetric:" << (A.isSymmetric()? "Yes" : "No") << "\n";
            cout << "  Is Diagonal:" << (A.isDiagonal()? "Yes" : "No") << "\n";
            cout << "  Is Diagonally Dominant: " << (A.isDiagonallyDominant()? "Yes" : "No") << "\n";

            if (!A.isDiagonallyDominant())
            {
                Matrix D = A.makeDiagonallyDominant();
                cout << "\nDiagonally Dominant form of A:\n" << D;
            }
        }
        else
        {
            cout << "  (Square-matrix operations skipped)\n";
        }

        Matrix T = A.transpose();
        cout << "\nTranspose of A:\n" << T;

        GaussSeidel temp(A); 
        temp.generateAugmentedMatrixFile(leftFile, rightFile, augFile);
        ifstream fin(augFile);
        if (!fin) throw runtime_error("Cannot open augmented matrix file: " + augFile);

        int r, c;
        fin >> r >> c;
        Matrix Aug(r, c);
        Aug.readFromFile(fin);
        fin.close();

        int methodChoice;
        cout << "\nChoose Solving Method:\n";
        cout << "  1. Gauss-Jacobi\n";
        cout << "  2. Gauss-Seidel\n";
        cout << "  3. Gaussian Elimination\n";
        cout << "  4. Dolittle LU\n";
        cout << "  5. Crout LU\n";
        cout << "  6. Cholesky Decomposition\n";
        cout << "Enter choice: ";
        cin >> methodChoice;

        int maxIter = 10000;
        double tol     = 1e-10;

        ofstream fout("result.txt");
        if (!fout) throw runtime_error("Cannot open result.txt for writing");

        switch (methodChoice)
        {
            case 1:
            {
                cout << "\nRunning Gauss-Jacobi...\n";
                GaussJacobi solver(Aug, maxIter, tol);
                solver.solve(fout);
                break;
            }
            case 2:
            {
                cout << "\nRunning Gauss-Seidel...\n";
                GaussSeidel solver(Aug, maxIter, tol);
                solver.solve(fout);
                break;
            }
            case 3:
            {
                cout << "\nRunning Gaussian Elimination...\n";
                GaussianElimination solver(Aug);
                solver.solve(fout);
                break;
            }
            case 4:
            {
                cout << "\nRunning Dolittle LU...\n";
                DolittleLU solver(Aug);
                solver.solve(fout);
                break;
            }
            case 5:
            {
                cout << "\nRunning Crout LU...\n";
                CroutLU solver(Aug);
                solver.solve(fout);
                break;
            }
            case 6:
            {
                cout << "\nRunning Cholesky Decomposition...\n";
                CholeskyDecomposition solver(Aug);
                solver.solve(fout);
                break;
            }
            default:
                cout << "Invalid choice.\n";
                return 1;
        }

        fout.close();
        cout << "Solution saved to result.txt\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}