#ifndef _TMatrix_h_
#define _TMatrix_h_

#include <vector>
#include <iostream>
using namespace std;

class TMatrix
{
    
    private:
    int fLines=2;
    int fColumns=2;
    vector<vector<double>> fElements;

    void InitMatrix();

    bool IsSquare();

    public:
    TMatrix();
    TMatrix(int Lines, int Columns);
    TMatrix(const TMatrix& m);
    ~TMatrix();

    void SetElement(int Line, int Column, double Value);
    void SetElements(const vector<vector<double>> &Elements);
    void SetNLines(int nLines);
    void SetNColumns(int nColumns);
    void SetSquareSize(int Size);
    void SetLine(int Line, const vector<double> &LineElements);
    void SetColumn(int Column, const vector<double> &ColumnElements);

    double GetElement(int Line, int Column) {return fElements.at(Line).at(Column);}
    vector<vector<double>> GetElements() {return fElements;}
    int GetNLines() {return fLines;}
    int GetNColumns() {return fColumns;}
    vector<double> GetLine(int Line) {return fElements.at(Line);}
    vector<double> GetColumn(int Column);

    void AddLine(int Line);
    void AddColumn(int Column);
    void PreparePadding();

    double GetMaximum();
    double GetAverage();
    double GetSum(int LineLowEdge=0, int LineUpEdge=0, int ColumnLowEdge=0, int ColumnUpEdge=0);

    void Scale(double Value);

    double Convolute(TMatrix* m);

    TMatrix* operator+(TMatrix* m);
    TMatrix* operator-(TMatrix* m);
    TMatrix* operator*(TMatrix* m);

    bool operator==(TMatrix* m);
    bool operator!=(TMatrix* m);


};
#endif