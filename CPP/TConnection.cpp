#include "../Header/TConnection.h"

TConnection::TConnection():fWeight(1.){

}

TConnection::TConnection(TNeuron* Neuron, double Weight):fNeuron(Neuron),fWeight(Weight){

}

TConnection::TConnection(const TConnection& Con):fNeuron(Con.fNeuron),fWeight(Con.fWeight){

}

TConnection::~TConnection(){

}

void TConnection::SetNeuron(TNeuron* Neuron){
    
    fNeuron=Neuron;
}

void TConnection::SetWeight(double Weight){
    
    fWeight=Weight;
}

void TConnection::SetNeuronWeight(TNeuron* Neuron, double Weight){
    
    fNeuron=Neuron;
    fWeight=Weight;
}

void TConnection::AddWeight(double WeightDiff){
    //fMomentum +=WeightDiff;
    //fMomentum *=0.9;

    fWeigthDiff += WeightDiff;
}


void TConnection::ApplyBatch(){

    fWeight +=fWeigthDiff;
    fWeigthDiff=0;
}

TNeuron* TConnection::GetNeuron(){

    return fNeuron;
}

double TConnection::GetWeight(){

    return fWeight;
}

double TConnection::GetConnectionValue(){

    return fNeuron->GetNeuronOutput()*fWeight;
}