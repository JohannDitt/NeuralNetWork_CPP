#include "../Header/TInputNeuron.h"

TInputNeuron::TInputNeuron():fNeuronInput(1.){

}

TInputNeuron::TInputNeuron(double Input):fNeuronInput(Input){

}

TInputNeuron::TInputNeuron(const TInputNeuron& In):fNeuronInput(In.fNeuronInput){

}

TInputNeuron::~TInputNeuron(){

}

double TInputNeuron::GetNeuronOutput(){

    return fNeuronInput;
}

void TInputNeuron::SetNeuronInput(double Input){
    fNeuronInput=Input;
}