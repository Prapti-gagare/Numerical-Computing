#include "matrix.hpp"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    try
    {
        string leftFile, rightFile, augFile;
        cout << "Enter left matrix file (coefficients): ";
         cin >> leftFile;
        cout << "Enter right matrix file (constants): ";
         cin >> rightFile;
        cout << "Enter output file for augmented matrix: ";
         cin >> augFile;

        Matrix tmp;
        tmp.generateAugmentedMatrixFile(leftFile, rightFile, augFile);

        ifstream finAug(augFile);
        ofstream fout("result.txt");
        if(!finAug || !fout) throw runtime_error("File opening error.");

        int r,c; finAug >> r >> c;
        Matrix A(r,c); A.readFromFile(finAug);

        fout << "\nSolution vector:\n";
        GaussianElimination gauss(A);
        gauss.solve(fout);           
        ifstream finL(leftFile); 
        ifstream finR(rightFile);
        int rL,cL,rR,cR; finL >> rL >> cL; finR >> rR >> cR;
        Matrix L(rL,cL), R(rR,cR);
         L.readFromFile(finL);
          R.readFromFile(finR);

        try
         { 
            Matrix sum = L.add(R);
             fout << "\nAddition of matrices:\n"; 
            sum.displayToFile(fout);
         }
        catch (const exception &e) 
        {
             fout << "\nAddition Error: " << e.what() << "\n";
         }

        try
         { 
            Matrix diff = L.subtract(R);
             fout << "\nSubtraction of matrices:\n"; 
             diff.displayToFile(fout); 
            }
        catch (const exception &e)
         {
             fout << "\nSubtraction Error: " << e.what() << "\n";
             }

        finAug.close(); 
        finL.close();
         finR.close();
          fout.close();
        cout << "Results saved to result.txt\n";
    }
    catch(exception &e)
     {
         cout << "Error: " << e.what() << endl; 
        }

    return 0;
}