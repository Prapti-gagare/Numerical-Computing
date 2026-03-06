#include "matrix.hpp"
#include "gaussian.hpp"
#include "crouts.hpp"
#include "dolittle.hpp"
#include "cholsky.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    string leftFile, rightFile, augFile;
    int choice, luChoice;

    cout << "Enter left matrix file: ";
    cin >> leftFile;

    cout << "Enter right matrix file: ";
    cin >> rightFile;

    cout << "Enter augmented output file: ";
    cin >> augFile;

    try
    {
        

        Matrix dummy;
        GaussianElimination temp(dummy);
        LinearSystem &sys = temp;

        sys.generateAugmentedMatrixFile(leftFile, rightFile, augFile);

    

        ifstream fin(augFile);
        ofstream fout("result.txt");

        int r, c;
        fin >> r >> c;

        Matrix A(r, c);
        A.readFromFile(fin);

        cout << "\nChoose method:\n";
        cout << "1. Gaussian Elimination\n";
        cout << "2. LU Decomposition\n";
        cout << "Enter choice: ";
        cin >> choice;

        LinearSystem *solver = nullptr;


        GaussianElimination gaussian(A);
        CroutLU crout(A);
        DolittleLU dolittle(A);
        CholeskyDecomposition chol(A);

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
        else
        {
            cout << "Invalid choice\n";
            return 0;
        }


        solver->solve(fout);

        cout << "\nResult saved in result.txt\n";
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}