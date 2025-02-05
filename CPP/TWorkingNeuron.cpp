#include "../Header/TWorkingNeuron.h"

TWorkingNeuron::TWorkingNeuron():fBias(0.){

    
    
}

TWorkingNeuron::TWorkingNeuron(double Bias):fBias(Bias){

    
    
}

TWorkingNeuron::TWorkingNeuron(double Bias, std::vector<TConnection*> &Connections, std::string FunctionName):fBias(Bias),fConnections(Connections),fFunction(FunctionName){

    
}

TWorkingNeuron::TWorkingNeuron(const TWorkingNeuron& Wn):fBias(Wn.fBias),fConnections(Wn.fConnections),fFunction(Wn.fFunction){

   
}

TWorkingNeuron::~TWorkingNeuron(){

}

double TWorkingNeuron::GetNeuronOutput(){
    
    if(!fOutputCalculated){
       
        fActivationLevel=Activate(GetNetInput());
        
        fOutputCalculated=true;
    }
    
    return fActivationLevel;
}

double TWorkingNeuron::GetDerivation(){

    if(!fDerivationCalculated){
        fDerivationValue=Derivation(GetNetInput());
        fDerivationCalculated=true;
    }
    return fDerivationValue;
}

TConnection* TWorkingNeuron::GetConnection(int con){

    return fConnections.at(con);
}

double TWorkingNeuron::GetDelta(){
    
    return fDelta;
}

void TWorkingNeuron::AddDelta(double DeltaPlus){

    fDelta += (DeltaPlus*fDerivationValue);
}

void TWorkingNeuron::SetNeuronInputs(const std::vector<TConnection*> &Connections){

    fConnections=Connections;
}

void TWorkingNeuron::SetBias(double Bias){

    fBias=Bias;
}

void TWorkingNeuron::SetActivationfunction(std::string FunctionName){

    fFunction=FunctionName;
}

void TWorkingNeuron::SetDelta(double Desired){
    
    fDelta=(Desired-GetNeuronOutput())*GetDerivation();
    
}

void TWorkingNeuron::ApplyBatch(){

    for(auto const& Con: fConnections){
        Con->ApplyBatch();
    }
    SetBias(fBias+fBiasDiff);
    fBiasDiff=0;
}

void TWorkingNeuron::ResetConnections(){

    fConnections.clear();
}

void TWorkingNeuron::ConnectNeuron(TConnection* Con){

    fConnections.push_back(Con);

}

void TWorkingNeuron::ConnectNeuron(TNeuron* Neuron, double Weight){

    TConnection* Con= new TConnection(Neuron, Weight);
    fConnections.push_back(Con);
}

void TWorkingNeuron::Learning(double &LearningRate){
    
    double LRDelta=LearningRate*fDelta;

    for(auto const& Connection: fConnections){
        TNeuron* Neuron=Connection->GetNeuron();
        double WeightDiff=LRDelta*(Neuron->GetNeuronOutput());
        Connection->AddWeight(WeightDiff);
        fBiasDiff += LRDelta;
    }

    
}

void TWorkingNeuron::BackpropagateDelta(){

    for(auto const& Connection: fConnections){
        TNeuron* Neuron = Connection->GetNeuron();
        if(typeid(Neuron)==typeid(TWorkingNeuron())){
            TWorkingNeuron* Wn =(TWorkingNeuron*)Neuron;
            Wn->AddDelta(fDelta*Connection->GetWeight());
        }


    }
}

void TWorkingNeuron::ResetNeuron(){

    fNetInputCalculated=false;
    fOutputCalculated=false;
    fDerivationCalculated=false;
    fActivationLevel=0;
    fNetInput=0;
    fDerivationValue=0;
    fDelta=0;
    
}

double TWorkingNeuron::GetNetInput(){

    if(!fNetInputCalculated){
        double sum=fBias;
        for(auto const& Con: fConnections){
            sum += Con->GetConnectionValue();
        }

        fNetInput=sum;
        fNetInputCalculated=true;
    }

    return fNetInput;


}

double TWorkingNeuron::Activate(double x){

    if(fFunction == "Identity"){
        
        return Identity(x);

    }else if(fFunction == "Sigmoid"){
        
        return Sigmoid(x);

    }else if(fFunction == "TanH"){

        return TanH(x);

    }else if(fFunction == "ReLU"){

        return ReLU(x);

    }else if(fFunction == "Softplus"){
        
        return Softplus(x); 

    }else{
        std::cout<<"You're preferred function is not implemented yet!"<<std::endl;
        std::cout<<"Implemented functions:\n\"Identity\"\n\"Sigmoid\"\n\"TanH\"\n\"ReLU\"\n\"Softplus\" "<<std::endl;
        std::cout<<std::endl;
        return 0.;
    }
}

double TWorkingNeuron::Identity(double x){

    return x;
}

double TWorkingNeuron::Sigmoid(double x){

    return 1/(1+exp(-x));
}

double TWorkingNeuron::TanH(double x){

    return tanh(x);
}

double TWorkingNeuron::ReLU(double x){

    if(x<0) return 0;
    else return x;
}

double TWorkingNeuron::Softplus(double x){

    return log(1+exp(x));
}

double TWorkingNeuron::Derivation(double x){

    if(fFunction == "Identity"){
        
        return 1.;

    }else if(fFunction == "Sigmoid"){
        
        return Sigmoid(x)*(1-Sigmoid(x));

    }else if(fFunction == "TanH"){

        return 1-pow(TanH(x),2);

    }else if(fFunction == "ReLU"){

        if(x<0) return 0.;
        else return 1.;

    }else if(fFunction == "Softplus"){

        return Sigmoid(x);

    }else{
        /*std::cout<<"You're preferred function is not implemented yet!"<<std::endl;
        std::cout<<"Implemented functions:\n\"Identity\"\n\"Sigmoid\"\n\"TanH\"\n\"ReLU\"\n\"Softplus\" "<<std::endl;
        std::cout<<std::endl;
        return 0.;*/
    }
}