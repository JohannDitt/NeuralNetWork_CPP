#include "../Header/TConvLayer.h"

TConvLayer::TConvLayer(){

}

TConvLayer::TConvLayer(int nKernel, int KernelSize):fNKernel(nKernel),fKernelSize(KernelSize){

}

TConvLayer::TConvLayer(const TConvLayer& Cl):fNKernel(Cl.fNKernel),fKernelSize(Cl.fKernelSize){

}

TConvLayer::~TConvLayer(){

}

void TConvLayer::SetDelta(double Delta){

    fDelta=Delta;
}

void TConvLayer::SetPadding(bool Padding){

    fPadding=Padding;
}

void TConvLayer::BackpropagateDelta(){

    fLayer->SetDelta(fDelta);
}

void TConvLayer::ConnectLayer(TLayer* Layer){

    fLayer=Layer;
}

vector<TMatrix*> TConvLayer::GetInputSums(){

    if(!fInputSumsClear){
        vector<TMatrix*> Input=GetInput();
        int Thickness=Input.size();

        vector<TMatrix*> InputSums;
        if(fPadding){
            for(int i=0; i<Thickness; i++){
                TMatrix* InputMatrix=Input.at(i);
                InputMatrix->->PreparePadding();

                TMatrix* m=new TMatrix(fKernelSize, fKernelSize);
                for(int k=0; k<fKernelSize; k++){
                    int LineEnd= fKernelSize-k-1;
                    for(int l=0; l<fKernelSize; l++){
                        int ColumnEnd=fKernelSize-l-1;
                        double Val;
                        Val=InputMatrix->GetSum(k,LineEnd,l,ColumnEnd);
                        m->SetElement(k,l, Val);
                    }
                }
                InputSums.push_back(m);
            }
        }

        fInputSums=InputSums;
        fInputSumsClear=true;
    }

    return fInputSums;
}


vector<TMatrix*> TConvLayer::GetInput(){


    if(!fInputClear){
        fInput=fLayer->GetLayerOutput();
        fInputClear=true;
    }

    return fInput;
}

vector<TMatrix*> TConvLayer::GetLayerOutput(){

    vector<TMatrix*> Output;

    vector<TMatrix*> Input=GetInput();
    int Thickness=Input.size();
    int OutLines= Input.at(0)->GetNLines();
    int OutColumns= Input.at(0)->GetNColumns();
    
    if(fPadding){
        for(int i=0; i<Thickness; i++){
            Input.at(i)->PreparePadding();
        }
    }

    for(int i=0; i<fNKernel; i++){
        TMatrix* Kernel=fKernels.at(i);
        for(int k=0; k=Thickness; k++){
            TMatrix* InputMatrix=Input.at(i);
            TMatrix* OutputMatrix=new TMatrix(OutLines, OutColumns);
            for(int l=1; l<InputMatrix->GetNLines-1; l++){
                for(int n=1; n<InputMatrix->GetNColumns()-1; n++){
                    TMatrix* m=GetKernelSizeMatrix(InputMatrix, l, i);
                    OutputMatrix->SetElement(l-1,n-1, m->Convolute(Kernel));
                }
            }
            Output.push_back(OutputMatrix);
        }
    }

    return Output;
}

TMatrix* TConvLayer::GetKernelSizeMatrix(TMatrix* m, int Line, int Column){

    TMatrix* matrix=new TMatrix(fKernelSize,fKernelSize);
    if(fKernelSize==2){
        matrix->SetElement(0,0, m->GetElement(Line-1,Column-1));
        matrix->SetElement(0,1, m->GetElement(Line-1,Column));
        matrix->SetElement(1,0, m->GetElement(Line,Column-1));
        matrix->SetElement(1,1, m->GetElement(Line,Column));
        return matrix;
    }

    int StepRange=(int)(fKernelSize-1)/2.;
    for(int i=0; i<fKernelSize; i++){
        for(int k=0; k<fKernelSize; k++){
            matrix->SetElement(i,k, m->GetElement(Line-StepRange+i, Column-StepRange+i));
        }
    }
    return matrix;
}