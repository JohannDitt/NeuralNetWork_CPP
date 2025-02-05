#include "../Header/TNeuralNetwork.h"

TNeuralNetwork::TNeuralNetwork():fHiddenLayers(0){

}

TNeuralNetwork::TNeuralNetwork(std::vector<TInputNeuron*> &In, std::vector<TWorkingNeuron*> &On, int HiddenLayers):fInputNeurons(In),fOutputNeurons(On),fHiddenLayers(HiddenLayers){

}

TNeuralNetwork::TNeuralNetwork(const TNeuralNetwork& NN):fInputNeurons(NN.fInputNeurons),fOutputNeurons(NN.fOutputNeurons),fHiddenLayers(NN.fHiddenLayers){

}

TNeuralNetwork::~TNeuralNetwork(){

    
}

void TNeuralNetwork::SetInputNeurons(std::vector<TInputNeuron*> &In){

    fInputNeurons=In;
}

void TNeuralNetwork::SetOutputNeurons(std::vector<TWorkingNeuron*> &On){

    fOutputNeurons=On;
}

void TNeuralNetwork::SetNHiddenLayers(int HiddenLayers){

    fHiddenLayers=HiddenLayers;
}

void TNeuralNetwork::SetInOutLayers(std::vector<TInputNeuron*> &In, std::vector<TWorkingNeuron*> &On, int HiddenLayers){

    fInputNeurons=In;
    fOutputNeurons=On;
    fHiddenLayers=HiddenLayers;
}

void TNeuralNetwork::SetLearningRate(double LearningRate){

    fLearningRate=LearningRate;
}

void TNeuralNetwork::SetEpochs(int Epochs){

    fEpochs=Epochs;
}

void TNeuralNetwork::SetBatchSize(int BatchSize){

    fBatchSize=BatchSize;
}

TInputNeuron* TNeuralNetwork::CreateInputNeuron(){

    TInputNeuron* inn = new TInputNeuron();
    fInputNeurons.push_back(inn);

    return inn;

}

TWorkingNeuron* TNeuralNetwork::CreateOutputNeuron(){

    TWorkingNeuron* Out = new TWorkingNeuron();
    fOutputNeurons.push_back(Out);

    return Out;

}

void TNeuralNetwork::CreateHiddenNeuron(int Layer, double Bias, std::string Function){

    if(fHiddenNeurons.size() == 0){
        for(int i =0; i<fHiddenLayers; i++){
            std::vector<TWorkingNeuron*> NeuronVector;
            fHiddenNeurons.push_back(NeuronVector);
        }
    }
    
    TWorkingNeuron* HiddenNeuron = new TWorkingNeuron(Bias);
    HiddenNeuron->SetActivationfunction(Function);
    fHiddenNeurons.at(Layer-1).push_back(HiddenNeuron);

    fHiddenNeuronsExist=true;

}

void TNeuralNetwork::ResetNeurons(){

    for(auto const& On: fOutputNeurons){
        On->ResetNeuron();
    }

    for(int i=0; i< fHiddenLayers; i++){
        for(auto const& Wn: fHiddenNeurons.at(i)){
            Wn->ResetNeuron();
        }
    }
}

void TNeuralNetwork::ConnectLayer(int Layer){

    int nIn;
    int nOut;

    if(fHiddenLayers == 0){
        nIn = fInputNeurons.size();
        nOut = fOutputNeurons.size();
        
        int indxOut = 0; 
        for(auto const& OutNeuron: fOutputNeurons){
            OutNeuron->ResetConnections();
            int indxIn = 0;
            for(auto const& InNeuron: fInputNeurons){
                OutNeuron->ConnectNeuron(InNeuron, 1.);
                indxIn++;
            }
            indxOut++;
        }

    }else{

        if(Layer == 0) {

            nIn = fInputNeurons.size();
            nOut = fHiddenNeurons.at(Layer).size();

            int indxOut = 0; 
            for(auto const& HiddenNeuron: fHiddenNeurons.at(Layer)){
                HiddenNeuron->ResetConnections();
                int indxIn = 0;
                for(auto const& InNeuron: fInputNeurons){
                    HiddenNeuron->ConnectNeuron(InNeuron, 1.);
                    indxIn++;
                }
                indxOut++;
            }

        }else if(Layer=fHiddenLayers){

            nIn = fHiddenNeurons.at(Layer-1).size();
            nOut = fOutputNeurons.size();

            int indxOut = 0; 
            for(auto const& OutNeuron: fOutputNeurons){
                OutNeuron->ResetConnections();
                int indxIn = 0;
                for(auto const& HiddenNeuron: fHiddenNeurons.at(Layer-1)){
                    OutNeuron->ConnectNeuron(HiddenNeuron, 1.);
                    indxIn++;
                }
                indxOut++;
            }
        }else{
            
            nIn = fHiddenNeurons.at(Layer-1).size();
            nOut = fHiddenNeurons.at(Layer).size();

            int indxOut = 0; 
            for(auto const& HiddenNeuronNow: fHiddenNeurons.at(Layer)){
                HiddenNeuronNow->ResetConnections();
                int indxIn = 0;
                for(auto const& HiddenNeuron: fHiddenNeurons.at(Layer-1)){
                    HiddenNeuronNow->ConnectNeuron(HiddenNeuron, 1.);
                    indxIn++;
                }
                indxOut++;
            }

        }
    }
        
}

void TNeuralNetwork::ConnectLayer(int Layer, const std::vector<double> &Weights){
    
    int nIn;
    int nOut;
    int nWeights;

    if(fHiddenLayers == 0){
        nIn = fInputNeurons.size();
        nOut = fOutputNeurons.size();
        
        nWeights = Weights.size();
        if(nWeights < nOut*nIn) {
            std::cout<<"Not enough weights for all connections!"<<std::endl;
            std::cout<<std::endl;
            return;
        }
        int indxOut = 0; 
        for(auto const& OutNeuron: fOutputNeurons){
            OutNeuron->ResetConnections();
            int indxIn = 0;
            for(auto const& InNeuron: fInputNeurons){
                OutNeuron->ConnectNeuron(InNeuron, Weights.at(nIn*indxOut+indxIn));
                indxIn++;
            }
            indxOut++;
        }

    }else{

        if(Layer == 0) {

            nIn = fInputNeurons.size();
            nOut = fHiddenNeurons.at(Layer).size();

            nWeights = Weights.size();
            if(nWeights < nOut*nIn) {
                std::cout<<"Not enough weights for all connections!"<<std::endl;
                std::cout<<std::endl;
                return;
            }
            int indxOut = 0; 
            for(auto const& HiddenNeuron: fHiddenNeurons.at(Layer)){
                HiddenNeuron->ResetConnections();
                int indxIn = 0;
                for(auto const& InNeuron: fInputNeurons){
                    HiddenNeuron->ConnectNeuron(InNeuron, Weights.at(nIn*indxOut+indxIn));
                    indxIn++;
                }
                indxOut++;
            }

        }else if(Layer=fHiddenLayers){

            nIn = fHiddenNeurons.at(Layer-1).size();
            nOut = fOutputNeurons.size();

            nWeights = Weights.size();
            if(nWeights < nOut*nIn) {
                std::cout<<"Not enough weights for all connections!"<<std::endl;
                std::cout<<std::endl;
                return;
            }
            int indxOut = 0; 
            for(auto const& OutNeuron: fOutputNeurons){
                OutNeuron->ResetConnections();
                int indxIn = 0;
                for(auto const& HiddenNeuron: fHiddenNeurons.at(Layer-1)){
                    OutNeuron->ConnectNeuron(HiddenNeuron, Weights.at(nIn*indxOut+indxIn));
                    indxIn++;
                }
                indxOut++;
            }
        }else{
            
            nIn = fHiddenNeurons.at(Layer-1).size();
            nOut = fHiddenNeurons.at(Layer).size();

            nWeights = Weights.size();
            if(nWeights < nOut*nIn) {
                std::cout<<"Not enough weights for all connections!"<<std::endl;
                std::cout<<std::endl;
                return;
            }
            int indxOut = 0; 
            for(auto const& HiddenNeuronNow: fHiddenNeurons.at(Layer)){
                HiddenNeuronNow->ResetConnections();
                int indxIn = 0;
                for(auto const& HiddenNeuron: fHiddenNeurons.at(Layer-1)){
                    HiddenNeuronNow->ConnectNeuron(HiddenNeuron, Weights.at(nIn*indxOut+indxIn));
                    indxIn++;
                }
                indxOut++;
            }

        }
    }
        
}

void TNeuralNetwork::ConnectLayers(){
    
    int nOut=fOutputNeurons.size();
    int nIn=fInputNeurons.size();

    if(fHiddenLayers == 0){
        ConnectLayer(0);
    }else{ 
        ConnectLayer(0);
        ConnectLayer(fHiddenLayers);
        
        int indxLayer = 1;
        while(indxLayer < fHiddenLayers){
            
            ConnectLayer(indxLayer);
            indxLayer++;

        }

    }

    
}

void TNeuralNetwork::ConnectLayers(const std::vector<std::vector<double>> &WeightsVector){

    
    int nOut=fOutputNeurons.size();
    int nIn=fInputNeurons.size();

    int nConnections=WeightsVector.size();
    

    if(nConnections < fHiddenLayers+1){
        std::cout<<"Cannot connect all Layers. Too less connection blocks!"<<std::endl;
    }

    if(fHiddenLayers == 0 || nConnections==1){
        
        ConnectLayer(0, WeightsVector.at(0));
    }else{
        ConnectLayer(0, WeightsVector.at(0));
        ConnectLayer(fHiddenLayers, WeightsVector.at(fHiddenLayers));
        
        int indxLayer=1;
        while(indxLayer < fHiddenLayers){
            ConnectLayer(indxLayer, WeightsVector.at(indxLayer));
            indxLayer++;
        }
        
    }
    
}

void TNeuralNetwork::Learning(const  std::vector<std::vector<double>> &InputValues, const  std::vector<std::vector<double>> &DesiredOutput){

    
    if( fHiddenLayers == 0 || !fHiddenNeuronsExist) DeltaLearning(InputValues, DesiredOutput);
    else Backpropagation(InputValues, DesiredOutput);
    
 
}

void TNeuralNetwork::DeltaLearning(const std::vector<std::vector<double>> &InputValues, const std::vector<std::vector<double>> &DesiredOutput){


    int nInVals = InputValues.size();
    int nInNeurons = fInputNeurons.size();
    int nOutNeurons = fOutputNeurons.size();
    
    int epoch = 0;
    while (epoch < fEpochs){
        std::cout<<"Epoch: "<<epoch+1<<std::endl;
        int nNoChange = 0;
        for(int i=0; i < nInVals; i++){
            if(InputValues.at(i).size() != fInputNeurons.size() || DesiredOutput.at(i).size() != fOutputNeurons.size()){
                std::cout<<"ERROR: Number of Inputs or Number of desired Outputs doesn't match the Number of corresponding Neurons!"<<std::endl;
                std::cout<<std::endl;
                return;
            }else{
                std::vector<double> Inputs = InputValues.at(i);
                std::vector<double> Outputs = DesiredOutput.at(i);
                for(int inNeuron=0; inNeuron < nInNeurons; inNeuron++){
                    fInputNeurons.at(inNeuron)->SetNeuronInput(Inputs.at(inNeuron));
                }   
                ResetNeurons();
                double Delta;
                for(int outNeuron=0; outNeuron < nOutNeurons; outNeuron++){
                    TWorkingNeuron* WorkNeuron = fOutputNeurons.at(outNeuron);
                    WorkNeuron->SetDelta(Outputs.at(outNeuron));
                    WorkNeuron->Learning(fLearningRate);
                    Delta = WorkNeuron->GetDelta();
                    std::cout<<"Delta: "<<Delta<<std::endl;
                    if(abs(Delta) <= pow(10,-10)){
                        nNoChange++;
                    }
                }   
            }
        }
        if(nNoChange == nInVals*nOutNeurons) break;
        epoch++;
    }
    std::cout<<"Delta"<<std::endl;
    ResetNeurons();
} 

void TNeuralNetwork::Backpropagation(const std::vector<std::vector<double>> &InputValues, const std::vector<std::vector<double>> &DesiredOutput){

    int nInVals = InputValues.size();
    int nInNeurons = fInputNeurons.size();
    int nOutNeurons = fOutputNeurons.size();
    
    
    
    int epoch = 0;
    while( epoch < fEpochs){
        std::cout<<"Epoch: "<<epoch+1<<std::endl;
        int nNoChange = 0;
        int BatchStep = 0;
        for(int i=0; i < nInVals; i++){
            if(InputValues.at(i).size() != fInputNeurons.size() || DesiredOutput.at(i).size() != fOutputNeurons.size()){
                std::cout<<"ERROR: Number of Inputs or Number of desired Outputs doesn't match the Number of corresponding Neurons!"<<std::endl;
                std::cout<<std::endl;
                return;
            }else{
                std::vector<double> Inputs = InputValues.at(i);
                std::vector<double> Outputs = DesiredOutput.at(i);

                for(int inNeuron=0; inNeuron < nInNeurons; inNeuron++){
                    fInputNeurons.at(inNeuron)->SetNeuronInput(Inputs.at(inNeuron));
                }
                
                ResetNeurons();
                
                double Delta;
                for(int outNeuron=0; outNeuron<nOutNeurons; outNeuron++){
                    TWorkingNeuron* oNeuron=fOutputNeurons.at(outNeuron);
                    oNeuron->SetDelta(Outputs.at(outNeuron));
                    oNeuron->BackpropagateDelta();
                    oNeuron->Learning(fLearningRate);
                    Delta=oNeuron->GetDelta();

                    std::cout<<"Delta: "<<Delta<<std::endl;
                    if(abs(Delta) <= pow(10,-10)){
                        nNoChange++;
                    }
                }

                for(int k=fHiddenLayers; k<0; k--){
                    for(auto const& hiddenNeuron: fHiddenNeurons.at(k-1)){
                        hiddenNeuron->BackpropagateDelta();
                        hiddenNeuron->Learning(fLearningRate);
                    }
                }
                BatchStep++;
            }

            if(BatchStep%fBatchSize == 0){
                for(int i=0; i<fHiddenLayers; i++){
                    for(auto const& Wn: fHiddenNeurons.at(i)){
                        Wn->ApplyBatch();
                    }
                }
                for(auto const& Wn: fOutputNeurons){
                    Wn->ApplyBatch();
                }
            }
        }
        if(nNoChange == nInVals*nOutNeurons) break;
        epoch++;

    }
    std::cout<<"Back"<<std::endl;
    ResetNeurons();
    
}

void TNeuralNetwork::GetCurrentWeights(std::vector<std::vector<double>> &WeightsVector){

    int nInNeurons=fInputNeurons.size();
    int nOutNeurons=fOutputNeurons.size();

    int nConBlocks=WeightsVector.size();
    WeightsVector.clear();

    if(nConBlocks == 1){
        std::vector<double> Weights; 
        for(int i=0; i<nOutNeurons; i++){
            TWorkingNeuron* Wn=fOutputNeurons.at(i);
            for(int k=0; k<nInNeurons; k++){
                double Weight=Wn->GetConnection(k)->GetWeight();
                Weights.push_back(Weight);
            }
        }
        WeightsVector.push_back(Weights);
    }else{

        for(int i=0; i<nConBlocks; i++){
            
            std::vector<double> Weights;
            
            if(i=nConBlocks-1){
                int nHiddenNeurons=fHiddenNeurons.at(i-1).size();
                for(int k=0; k<nOutNeurons; k++){
                    TWorkingNeuron* Wn=fOutputNeurons.at(k);
                    for(int m=0; m<nHiddenNeurons; m++){
                        double Weight=Wn->GetConnection(m)->GetWeight();
                        Weights.push_back(Weight);
                    }
                }
            }
            if(i == 0){
                int nHiddenNeurons=fHiddenNeurons.at(i).size();
                for(int k=0; k<nHiddenNeurons; k++){
                    TWorkingNeuron* Wn=fHiddenNeurons.at(i).at(k);
                    for(int m=0; m<nInNeurons; m++){
                        double Weight=Wn->GetConnection(m)->GetWeight();
                        Weights.push_back(Weight);
                    }
                }
            }
            if( i!= 0 && i != (nConBlocks-1) ){
                int nHiddenNeuronsCurr=fHiddenNeurons.at(i).size();
                int nHiddenNeurons=fHiddenNeurons.at(i-1).size();
                for(int k=0; k<nHiddenNeuronsCurr; k++){
                    TWorkingNeuron* Wn=fHiddenNeurons.at(i).at(k);
                    for(int m=0; m<nHiddenNeurons; m++){
                        double Weight=Wn->GetConnection(m)->GetWeight();
                        Weights.push_back(Weight);
                    }
                }
                
            }
            WeightsVector.push_back(Weights); 

        }
    }

}