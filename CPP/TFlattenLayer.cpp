#include "../Header/TFlattenLayer.h"

TFlattenLayer::TFlattenLayer(){

}

TFlattenLayer::TFlattenLayer(TLayer* Layer):fLayer(Layer){

}

TFlattenLayer::TFlattenLayer(const TFlattenLayer& Fl):fLayer(Fl.fLayer){

}

TFlattenLayer::~TFlattenLayer(){

}

vector<double> TFlattenLayer::GetLayerOutput(){

    vector<TMatrix*> Input=fLayer->GetLayerOutput();

    vector<double> Output;
    int Thickness=Input.size();
    for(int i=0; i<Thickness; i++){
        TMatrix* InHist_2d=Input.at(i);
        int Width=InHist_2d->GetNLines();
        for(int k=0; k<Width; k++){
            vector<double> Line=InHist_2d->GetLine(k);
            int Length=Line.size();
            for(int l=0; l<Length; l++){
                Output.push_back(Line.at(l));
            }
        }
    }
    return Output;
}

vector<TInputNeuron*> TFlattenLayer::GetLayerOutputAsNeurons(){


    vector<TInputNeuron*> Output;
    vector<double> Values=GetLayerOutput();

    for(int i=0; i<Values.size(); i++){
        TInputNeuron* In=new TInputNeuron(Values.at(i));
        Output.push_back(In);
    }
    return Output;
}

void TFlattenLayer::ConnectLayer(TLayer* Layer){
    
    fLayer=Layer;
}