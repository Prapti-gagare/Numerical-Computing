#include "matrix.hpp"
#include "LinearSystem.hpp"
#include "gauss_jacobi.hpp"
#include "gauss_seidle.hpp"
#include "gaussian.hpp"
#include "dolittle.hpp"
#include "crouts.hpp"
#include "cholsky.hpp"
#include "gerschgorin.hpp"
#include "interpolation.hpp"   
#include "lagrange.hpp"        
#include <fstream>
#include <iostream>
using namespace std;
void solveLinearSystem(ofstream &fout);
void eigenvalueMenu(ofstream &fout);
void interpolationMenu(ofstream &fout);
int main()
{
    int Choice;
   cout << "Numerical Methods Suite\n";
cout << "1. Solve Linear System\n";
cout << "2. Eigenvalue Estimation\n";
cout << "3. Interpolation\n";
    cout << "Enter choice: ";
    cin >> Choice;

    ofstream fout("result.txt");
    if (!fout) { cerr << "Cannot open result.txt\n"; return 1; }

    try
    {
        switch (Choice)
        {
            case 1: solveLinearSystem(fout); break;
            case 2: eigenvalueMenu(fout);    break;
            case 3: interpolationMenu(fout); break;  
            default: cout << "Invalid choice.\n";
        }
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    fout.close();
    cout << "Result saved to result.txt\n";
    return 0;
}

void solveLinearSystem(ofstream &fout)
{
    string leftFile, rightFile, augFile;
    cout << "Enter left matrix file  (A): "; cin >> leftFile;
    cout << "Enter right matrix file (b): "; cin >> rightFile;
    cout << "Enter augmented output file: "; cin >> augFile;

    ifstream left(leftFile);
    if (!left) throw runtime_error("Cannot open left matrix file");
    int lr, lc;
    left >> lr >> lc;
    Matrix A(lr, lc);
    A.readFromFile(left);
    left.close();

    cout << "\nMatrix A:\n" << A;
    cout << "\nMatrix Properties:\n";
    cout << "Is Square:             " << (A.isSquare()            ? "Yes" : "No") << "\n";
    if (A.isSquare())
    {
        cout << "Is Symmetric:          " << (A.isSymmetric()         ? "Yes" : "No") << "\n";
        cout << "Is Diagonally Dominant:" << (A.isDiagonallyDominant()? "Yes" : "No") << "\n";
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
        { GaussJacobi  solver(Aug, 10000, 1e-10);
             solver.solve(fout); 
             break;
    }
        case 2: 
        {
             GaussSeidel solver(Aug, 10000, 1e-10); 
             solver.solve(fout);
              break;
             }
        case 3: 
        { GaussianElimination   solver(Aug); 
         solver.solve(fout);
             break;
          }
        case 4:
         {
             DolittleLU  solver(Aug); 
             solver.solve(fout); 
             break;
             }
        case 5:
         {
             CroutLU   solver(Aug);
           solver.solve(fout);
            break;
         }
        case 6:
         {
             CholeskyDecomposition solver(Aug);
          solver.solve(fout);
           break; 
        }
        default: cout << "Invalid choice\n";
    }
}

void eigenvalueMenu(ofstream &fout)
{
    string matFile;
    cout << "Enter matrix file: ";
    cin >> matFile;

    ifstream fin(matFile);
    if (!fin) throw runtime_error("Cannot open matrix file");
    int r, c;
    fin >> r >> c;
    Matrix A(r, c);
    A.readFromFile(fin);
    fin.close();

    cout << "\nChoose Method:\n";
    cout << "1. Gerschgorin Circle Theorem\n";
    cout << "Enter: ";
    int choice; cin >> choice;

    switch (choice)
    {
        case 1: { Gerschgorin g(A); g.printEigenvalues(fout); break; }
        default: cout << "Invalid choice\n";
    }
}


void interpolationMenu(ofstream &fout)
{

    string dataFile;
    cout << "Enter data-points file: ";
    cin >> dataFile;

    ifstream fin(dataFile);
    if (!fin) throw runtime_error("Cannot open data file");

    double xQuery;
    cout << "Enter the x value to interpolate at: ";
    cin >> xQuery;

    int choice;
    cout << "\nChoose Interpolation Method:\n";
    cout << "1. Lagrange Interpolation\n";
    cout << "Enter: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            Lagrange solver;
            solver.loadDataPoints(fin);
            fin.close();

            double result = solver.interpolate(xQuery, fout);
            cout << fixed;
            cout << "\nP(" << xQuery << ") = " << result << "\n";
            cout << "(Full working saved to result.txt)\n";
            break;
        }
        default:
            cout << "Invalid choice\n";
    }
}