#include "../Header/TInLayer.h"

TInLayer::TInLayer(){

}

TInLayer::TInLayer(const vector<TMatrix*> &Input):fNetInput(Input){

}

TInLayer::TInLayer(const TInLayer& Il):fNetInput(Il.fNetInput){
    
}

TInLayer::~TInLayer(){

}

vector<TMatrix*> TInLayer::GetLayerOutput(){

    return fNetInput;
}

void TInLayer::SetNetInput(const vector<TMatrix*> &Input){

    fNetInput=Input;
}

void TInLayer::AddMatrix(TMatrix* m){

    fNetInput.push_back(m);
}

