#include "../Header/TPoolingLayer.h"

TPoolingLayer::TPoolingLayer(){

}

TPoolingLayer::TPoolingLayer(int KernelSize, int Stride):fKernelSize(KernelSize),fStride(Stride){

}

TPoolingLayer::TPoolingLayer(TLayer* Layer):fLayer(Layer){

    
}

TPoolingLayer::TPoolingLayer(const TPoolingLayer& Pl):fKernelSize(Pl.fKernelSize),fStride(Pl.fStride),fLayer(Pl.fLayer){

}

TPoolingLayer::~TPoolingLayer(){

}

vector<TMatrix*> TPoolingLayer::GetLayerOutput(){

    vector<TMatrix*> Input=fLayer->GetLayerOutput();
    vector<TMatrix*> Output;
    
    int Thickness=Input.size();
    if(fMaxPool){
        for(int i=0; i<Thickness; i++){
            TMatrix* InHist_2d=Input.at(i);
            int Width=InHist_2d->GetNColumns();
            int Length=InHist_2d->GetNLines();
            
            if(Length!= Width) cout<<"WARNING: Input picture is no square!"<<endl;

            TMatrix* OutHist_2d=new TMatrix(Length/fStride, Width/fStride);

            vector<double> OutLine;
            int indx=0;
            for(int k=1; k<Width; k+fStride){
                vector<double> Line=InHist_2d->GetLine(k);
                vector<double> UpperLine=InHist_2d->GetLine(k-1);       
               
                for(int l=1; l<Length; l+fStride){

                    TMatrix* HelpMatrix=new TMatrix(fKernelSize,fKernelSize);
                    HelpMatrix->SetElement(0,0, UpperLine.at(l-1));
                    HelpMatrix->SetElement(0,1, UpperLine.at(l));
                    HelpMatrix->SetElement(1,0, Line.at(l-1));
                    HelpMatrix->SetElement(1,1, Line.at(l));
                    

                    OutLine.push_back(HelpMatrix->GetMaximum());
                }
                OutHist_2d->SetLine(indx, OutLine);
                indx++;
            }
            Output.push_back(OutHist_2d);
        }

    }

    if(fAveragePool){
        for(int i=0; i<Thickness; i++){
            TMatrix* InHist_2d=Input.at(i);
            int Width=InHist_2d->GetNColumns();
            int Length=InHist_2d->GetNLines();
            
            if(Length!= Width) cout<<"WARNING: Input picture is not square!"<<endl;

            TMatrix* OutHist_2d=new TMatrix(Length/fStride, Width/fStride);

            vector<double> OutLine;
            int indx=0;
            for(int k=1; k<Width; k+fStride){
                vector<double> Line=InHist_2d->GetLine(k);
                vector<double> UpperLine=InHist_2d->GetLine(k-1);       
               
                for(int l=1; l<Length; l+fStride){

                    TMatrix* HelpMatrix=new TMatrix(fKernelSize,fKernelSize);
                    HelpMatrix->SetElement(0,0, UpperLine.at(l-1));
                    HelpMatrix->SetElement(0,1, UpperLine.at(l));
                    HelpMatrix->SetElement(1,0, Line.at(l-1));
                    HelpMatrix->SetElement(1,1, Line.at(l));
                    

                    OutLine.push_back(HelpMatrix->GetAverage());
                }
                OutHist_2d->SetLine(indx, OutLine);
                indx++;
            }
            }
            Output.push_back(OutHist_2d);
        }

    }

    return Output;
}

void TPoolingLayer::ConnectLayer(TConvolutionalLayer* Cl){

    fLayer=Cl;
}

void TPoolingLayer::SetDelta(double Delta){

    fDelta=Delta
}

void TPoolingLayer::SetHyperParameters(int KernelSize, int Stride){

    fKernelSize=KernelSize;
    fStride=Stride;
}

void TPoolingLayer::SetPooling(string Pooling){

    if(Pooling == "Max"){
        fMaxPool=true;
        fAveragePool=false;
    }
    if(Pooling == "Average"){
        fMaxPool=false;
        fAveragePool=true;
    }
}

void TPoolingLayer::BackpropagateDelta(){

    fLayer->SetDelta(fDelta);
}