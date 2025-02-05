#include "../Header/TMatrix.h"

TMatrix::TMatrix(){

    InitMatrix();
}

TMatrix::TMatrix(int Lines, int Columns):fLines(Lines),fColumns(Columns){

    InitMatrix();
}

TMatrix::TMatrix(const TMatrix& m):fLines(m.fLines),fColumns(m.fColumns),fElements(m.fElements){
    
    InitMatrix();
}

TMatrix::~TMatrix(){

}

void TMatrix::SetElement(int Line, int Column, double Value){

    fElements.at(Line).at(Column)=Value;
}

void TMatrix::SetElements(const vector<vector<double>> &Elements){

    int Lines=Elements.size();
    if(Lines != fLines){
        cout<<"ERROR: Not enough Columns!"<<endl;
        return;
    }
    for(int i=0; i<fLines; i++){
        int Columns=Elements.at(i).size();
        if(Columns != fColumns){
            cout<<"ERROR: Not enough Lines"<<endl;
            return;
        }
        for(int k=0; k<fColumns; k++){
            fElements.at(k).at(i)=Elements.at(k).at(i);
        }
    }
}

void TMatrix::SetNLines(int nLines){
    
    fLines=nLines;
}

void TMatrix::SetNColumns(int nColumns){

    fColumns=nColumns;
}

void TMatrix::SetSquareSize(int Size){

    fLines=Size;
    fColumns=Size;
}

void TMatrix::SetLine(int Line, const vector<double> &LineElements){
 
    if(Line >= fLines){
        cout<<"ERROR: Line "<< Line<<" out of range!"<<endl;
        return;
    }
    if(LineElements.size() != fColumns){
        cout<<"ERROR: Not enough Columns"<<endl;
        return;
    }
    
    fElements.at(Line)=LineElements;
}

void TMatrix::SetColumn(int Column, const vector<double> &ColumnElements){
    
    if(Column >= fColumns){
        cout<<"ERROR: Column "<< Column<<" out of range!"<<endl;
        return;
    }
    
    if(ColumnElements.size() != fLines){
        cout<<"ERROR: Not enough Lines"<<endl;
        return;
    }
   
    for(int i=0; i<fLines; i++){
        fElements.at(i).at(Column)=ColumnElements.at(i);
    }
}

vector<double> TMatrix::GetColumn(int Column){

    vector<double> ColumnElements;
    for(int i=0; i<fLines; i++){
        ColumnElements.push_back(fElements.at(i).at(Column));
    }

    return ColumnElements;
}

void TMatrix::Scale(double Value){

    for(int i=0; i<fLines; i++){
        for(int k=0; k<fColumns; k++){
            fElements.at(i).at(k) *=Value;
        }
    }

}

TMatrix* TMatrix::operator+(TMatrix* m){
    
    if(m->GetNColumns() != fColumns || m->GetNLines() != fLines){
        cout<<"FATAL ERROR: Matrices do not have the same size. Addition is not possible!"<<endl;
        return this;
    }
    TMatrix* Matrix=new TMatrix(fLines, fColumns);
    for(int i=0; i<fLines; i++){
        for(int k=0; k<fColumns; k++){
            double Value = fElements.at(i).at(k) + m->GetElement(i,k);
            Matrix->SetElement(i,k, Value);
        }
    }
    return Matrix;
}

TMatrix* TMatrix::operator-(TMatrix* m){
    
    if(m->GetNColumns() != fColumns || m->GetNLines() != fLines){
        cout<<"FATAL ERROR: Matrices do not have the same size. Subtraction is not possible!"<<endl;
        return this;
    }
    TMatrix* Matrix=new TMatrix(fLines, fColumns);
    for(int i=0; i<fLines; i++){
        for(int k=0; k<fColumns; k++){
            double Value = fElements.at(i).at(k) - m->GetElement(i,k);
            Matrix->SetElement(i,k, Value);
        }
    }
    return Matrix;

}

TMatrix* TMatrix::operator*(TMatrix* m){

    if(fColumns != m->GetNLines()){
        cout<<"FATAL ERROR: Number of Lines does not match Number of Columns. Multiplication not possible!"<<endl;
        return this;
    }

    int nColumns=m->GetNColumns();
    int nLines=fLines;
    TMatrix* Matrix=new TMatrix(nLines, nColumns);
    for(int i=0; i<nLines; i++){
        for(int k=0; k<nColumns; k++){
            double Value=0;
            for(int l=0; l<fColumns; l++){
                Value += fElements.at(i).at(l)*m->GetElement(l,k);
            }
            Matrix->SetElement(i,k, Value);
        }
    }

    return Matrix;

}

bool TMatrix::operator==(TMatrix* m){

    
    if(m->GetNColumns() != fColumns || m->GetNLines() != fLines){
        return false;       
    }else{
        for(int i=0; i<fLines; i++){
            for(int k=0; k<fColumns; k++){
                if(fElements.at(i).at(k) != m->GetElement(i,k)){
                    return false;
                }
            }
            
        }
    }
    return true;
    
}

bool TMatrix::operator!=(TMatrix* m){

    if(m->GetNColumns() != fColumns || m->GetNLines() != fLines){
        return true;       
    }else{
        for(int i=0; i<fLines; i++){
            for(int k=0; k<fColumns; k++){
                if(fElements.at(i).at(k) != m->GetElement(i,k)){
                    return true;
                }
            }
            
        }
    }
    return false;


}

bool TMatrix::IsSquare(){

    if(fColumns == fLines) return true;
    else return false;
}

double TMatrix::Convolute(TMatrix* m){

    if(!IsSquare()){
        cout<<"ERROR: Matrix is not square!"<<endl;
        return 0;
    }

    if(fColumns != m->GetNColumns() || fLines != m->GetNLines()){
        cout<<"ERROR: Matrices do not have the same size!"<<endl;
        return 0;
    }
    double Value=0;

    for(int i=0; i<fLines; i++){
        for(int k=0; k<fColumns; k++){
            Value += fElements.at(i).at(k)*m->GetElement(i,k);
        }
    }
    return Value;
}

double TMatrix::GetMaximum(){

    double Maximum=max(GetElement(0,0),GetElement(0,1));
    for(int i=0; i<fLines; i++){
        for(int k=0; k<fColumns; k++){
            if(i == 0 && k == 0) continue;
            if(i == 0 && k == 1) continue;
            if(GetElement(i,k) > Maximum){
                Maximum=GetElement(i,k);
            }
        }
    }
    return Maximum;
}

double TMatrix::GetAverage(){
    
    double Average=0;
    for(int i=0; i<fLines; i++){
        for(int k=0; k<fColumns; k++){
            Average += GetElement(i,k);
        }
    }
    Average /= (fLines*fColumns);
    return Average;
}

void TMatrix::InitMatrix(){

    if(fElements.size() == 0){
        
        for(int i=0; i<fLines; i++){
            vector<double> Line;
            for(int k=0; k=fColumns; k++){
                if(k==i) Line.push_back(1.);
                else Line.push_back(0.);
            }
            fElements.push_back(Line);
        }
    }
}

void TMatrix::AddLine(int Line){

    if(Line > fLines){
        cout<<"Line "<<Line<<" out of range "<<fLines<<"!"<<endl;
        return;
    }

    fLines++;
    
    vector<double> NewElements (fColumns,0);
    if(Line == fLines-1){
        SetLine(Line, NewElements);
    }else{
        TMatrix* matrix=new TMatrix(fLines, fColumns-1);
        matrix->SetElements(GetElements());
        for(int i=0; i<fLines-1; i++){
            if(i<Line) continue;
            if(i==Line) SetLine(i, NewElements);
            SetLine(i+1, matrix->GetLine(i));
        }
    }

}

void TMatrix::AddColumn(int Column){

    if(Column > fColumns){
        cout<<"Column "<<Column<<" out of range "<<fColumns<<"!"<<endl;
        return;
    }

    fColumns++;

    vector<double> NewElements (fLines,0);
    if(Column == fColumns-1){
        SetColumn(Column, NewElements);
    }else{
        TMatrix* matrix=new TMatrix(fLines, fColumns-1);
        matrix->SetElements(GetElements());
        for(int i=0; i<fColumns-1; i++){
            if(i<Column) continue;
            if(i==Column) SetColumn(i, NewElements);
            SetLine(i+1, matrix->GetColumn(i));
        }
    }

}

void TMatrix::PreparePadding(){

    AddColumn(fColumns);
    AddColumn(0);
    AddLine(fLines);
    AddLine(0);
}

double TMatrix::GetSum(int LineLowEdge, int LineUpEdge, int ColumnLowEdge, int ColumnUpEdge){

    double Sum=0;
    if(LineLowEdge > fLines-LineUpEdge || ColumnLowEdge > fColumns-ColumnUpEdge){
        cout<<"ERROR: Edges are out of range!"<<endl;
        returnSum;
    } 
    for(int i=LineLowEdge; i<fLines-LineUpEdge; i++){
        for(int k=ColumnLowEdge; k<fColumns-ColumnUpEdge; k++){
            Sum += GetElement(i,k);
        }
    }
    return Sum;
}