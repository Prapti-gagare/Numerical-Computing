#include "matrix.hpp"
#include "gaussian.hpp"
#include "crouts.hpp"
#include "dolittle.hpp"
#include "cholsky.hpp"
#include "gauss_jacobi.hpp"
#include "gauss_seidle.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    string leftFile, rightFile, augFile;
    int choice, luChoice, iterChoice;

    cout << "Enter left matrix file: ";
    cin >> leftFile;

    cout << "Enter right matrix file: ";
    cin >> rightFile;

    cout << "Enter augmented output file: ";
    cin >> augFile;

    try
    {
        ifstream left(leftFile);
        if (!left)
            throw runtime_error("Failed to open left matrix file");

        int lr, lc;
        left >> lr >> lc;

        Matrix A(lr, lc);
        A.readFromFile(left);

        left.close();

        cout << "\nLeft Matrix A:\n";
        A << cout;

        cout << "\nMatrix Operations (on A)\n";

        cout << "Is Square: " << (A.isSquare() ? "Yes" : "No") << endl;
        cout << "Is Null: " << (A.isNull() ? "Yes" : "No") << endl;

        if (A.isSquare())
        {
            cout << "Is Identity: " << (A.isIdentity() ? "Yes" : "No") << endl;
            cout << "Is Symmetric: " << (A.isSymmetric() ? "Yes" : "No") << endl;
            cout << "Is Diagonal: " << (A.isDiagonal() ? "Yes" : "No") << endl;
            cout << "Determinant: " << A.determinant() << endl;
            cout << "Is Diagonally Dominant: "
                 << (A.isDiagonallyDominant() ? "Yes" : "No") << endl;

            if (!A.isDiagonallyDominant())
            {
                try
                {
                    Matrix D = A.makeDiagonallyDominant();

                    cout << "\nDiagonally Dominant Matrix:\n";
                    D << cout;
                }
                catch (const exception &e)
                {
                    cout << e.what() << endl;
                }
            }

            try
            {
                Matrix inv = A.inverse();

                cout << "\nInverse Matrix:\n";
                inv << cout;
            }
            catch (const exception &e)
            {
                cout << "\nInverse Error: " << e.what() << endl;
            }
        }
        else
        {
            cout << "Square matrix operations skipped.\n";
        }

        Matrix T = A.transpose();

        cout << "\nTranspose Matrix:\n";
        T << cout;

        // Generate augmented matrix
        Matrix dummy;
        GaussianElimination temp(dummy);
        LinearSystem &sys = temp;

        sys.generateAugmentedMatrixFile(leftFile, rightFile, augFile);

        ifstream fin(augFile);
        if (!fin)
            throw runtime_error("Failed to open augmented matrix file");

        ofstream fout("result3.txt");
        if (!fout)
            throw runtime_error("Failed to open result file");

        int r, c;
        fin >> r >> c;

        Matrix Aug(r, c);
        Aug.readFromFile(fin);

        cout << "\nChoose method:\n";
        cout << "1. Gaussian Elimination\n";
        cout << "2. LU Decomposition\n";
        cout << "3. Iterative Methods\n";
        cout << "Enter choice: ";
        cin >> choice;

        LinearSystem *solver = nullptr;

        // Create all solvers
        GaussianElimination gaussian(Aug);
        CroutLU crout(Aug);
        DolittleLU dolittle(Aug);
        CholeskyDecomposition chol(Aug);

        // Iterative params (optional)
        int maxIter = 1000;
        double tol = 1e-6;

        GaussJacobi jacobi(Aug, maxIter, tol);
        GaussSeidel seidel(Aug, maxIter, tol);

        if (choice == 1)
        {
            solver = &gaussian;
        }
        else if (choice == 2)
        {
            cout << "\nChoose LU Method:\n";
            cout << "1. Crout\n";
            cout << "2. Doolittle\n";
            cout << "3. Cholesky\n";
            cout << "Enter choice: ";
            cin >> luChoice;

            if (luChoice == 1)
                solver = &crout;
            else if (luChoice == 2)
                solver = &dolittle;
            else if (luChoice == 3)
                solver = &chol;
            else
            {
                cout << "Invalid LU choice\n";
                return 0;
            }
        }
        else if (choice == 3)
        {
            if (!Aug.isDiagonallyDominant())
            {
                cout << "\nWarning: Matrix is not diagonally dominant.\n";
                cout << "Iterative methods may not converge.\n";
            }

            cout << "\nChoose Iterative Method:\n";
            cout << "1. Gauss Jacobi\n";
            cout << "2. Gauss Seidel\n";
            cout << "Enter choice: ";
            cin >> iterChoice;

            if (iterChoice == 1)
                solver = &jacobi;
            else if (iterChoice == 2)
                solver = &seidel;
            else
            {
                cout << "Invalid Iterative choice\n";
                return 0;
            }
        }
        else
        {
            cout << "Invalid choice\n";
            return 0;
        }

        solver->solve(fout);

        cout << "\nSolution saved in result3.txt\n";

        fin.close();
        fout.close();
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}