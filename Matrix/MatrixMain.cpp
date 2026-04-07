#include "matrix.hpp"
#include "LinearSystem.hpp"
#include "gauss_jacobi.hpp"
#include "gauss_seidle.hpp"
#include "gaussian.hpp"
#include "dolittle.hpp"
#include "crouts.hpp"
#include "cholsky.hpp"
#include "gerschgorin.hpp"
#include <fstream>
#include <iostream>
using namespace std; 

int main()
{
    int Choice;
    cout << "1. Solve Linear System\n";
    cout << "2. Gerschgorin Eigenvalue Estimation\n";
    cout << "Enter choice: ";
    cin >> Choice;

    ofstream fout("result.txt");

    if (Choice == 2)
    {
        string matFile;
        cout << "Enter matrix file: ";
        cin >> matFile;

        ifstream fin(matFile);
        if (!fin) { cerr << "Cannot open file\n"; return 1; }
        int r, c;
        fin >> r >> c;
        Matrix A(r, c);
        A.readFromFile(fin);
        fin.close();

        Gerschgorin g(A);
        g.printEigenvalues(fout);
        fout.close();
        cout << "Result saved to result.txt\n";
        return 0;
    }

    string leftFile, rightFile, augFile;
    cout << "Enter left matrix file (A):  "; cin >> leftFile;
    cout << "Enter right matrix file (b): "; cin >> rightFile;
    cout << "Enter augmented output file: "; cin >> augFile;

    try
    {
        ifstream left(leftFile);
        if (!left) throw runtime_error("Cannot open left matrix file");
        int lr, lc;
        left >> lr >> lc;
        Matrix A(lr, lc);
        A.readFromFile(left);
        left.close();
        cout << "\nMatrix A:\n" << A;

        cout << "\nMatrix Properties:\n";
        cout << "Is Square: " << (A.isSquare() ? "Yes" : "No") << "\n";
        if (A.isSquare())
        {
            cout << "Is Symmetric: " << (A.isSymmetric() ? "Yes" : "No") << "\n";
            cout << "Is Diagonally Dominant: " << (A.isDiagonallyDominant() ? "Yes" : "No") << "\n";
        }
        cout << "\nTranspose:\n" << A.transpose();

        GaussSeidel temp(A);
        temp.generateAugmentedMatrixFile(leftFile, rightFile, augFile);

        ifstream fin(augFile);
        if (!fin) throw runtime_error("Cannot open augmented file");
        int r, c;
        fin >> r >> c;
        Matrix Aug(r, c);
        Aug.readFromFile(fin);
        fin.close();

        int choice;
        cout << "\nChoose Method:\n";
        cout << "1. Gauss-Jacobi\n";
        cout << "2. Gauss-Seidel\n";
        cout << "3. Gaussian Elimination\n";
        cout << "4. Doolittle LU\n";
        cout << "5. Crout LU\n";
        cout << "6. Cholesky\n";
        cout << "Enter: ";
        cin >> choice;

        switch (choice)
        {
            case 1: 
            { 
                GaussJacobi solver(Aug, 10000, 1e-10);
                 solver.solve(fout); break;
         }
            case 2:
             { 
                GaussSeidel solver(Aug, 10000, 1e-10);
                 solver.solve(fout); break;
         }
            case 3: 
            { GaussianElimination solver(Aug); 
                solver.solve(fout); 
                break;
         }
            case 4: 
            {
                 DolittleLU solver(Aug);
                  solver.solve(fout); 
                  break;
            }
            case 5:
             { 
                CroutLU solver(Aug); 
                solver.solve(fout);
                 break;
         }
            case 6:
             { 
                CholeskyDecomposition solver(Aug); solver.solve(fout);
                 break;
             }
            default: cout << "Invalid choice\n";
        }
        fout.close();
        cout << "Result saved to result.txt\n";
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}