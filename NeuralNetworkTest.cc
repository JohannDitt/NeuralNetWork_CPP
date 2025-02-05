#include "Header/TNeuralNetwork.h"

#include <iostream>



int main(){

    TNeuralNetwork* NeuralTest=new TNeuralNetwork();
    NeuralTest->SetNHiddenLayers(1);
    NeuralTest->SetEpochs(10000);
    NeuralTest->SetLearningRate(0.01);
    NeuralTest->SetBatchSize(1);

    TInputNeuron* In[4];
    TWorkingNeuron* Out[2];

    for(int i=0;i<4;i++){

        In[i]=NeuralTest->CreateInputNeuron();
        In[i]->SetNeuronInput((double)i+1.);
        
    }
    

    for(int i=0; i<2;i++){
        Out[i]=NeuralTest->CreateOutputNeuron();
        Out[i]->SetBias(0.5);
        Out[i]->SetActivationfunction("Identity");
    }

    for(int i=0; i<3; i++){
        NeuralTest->CreateHiddenNeuron(1, 0.5, "Identity");
    }

    
    std::vector<double> Weights;
    for(int i =0; i<12; i++){
        
        Weights.push_back(0.5);
       
    }
    std::vector<std::vector<double>> WeightsVector;
    WeightsVector.push_back(Weights);
    
    std::vector<double> Weights1;
    for(int i = 0; i<6; i++){
        
        Weights1.push_back(0.5);
       
    }
    //Weights1.at(5)=2.;
    WeightsVector.push_back(Weights1);

    NeuralTest->ConnectLayers(WeightsVector);

    std::vector<std::vector<double>> InputValues={{1,2,3,4},{2,3,4,5}};
    std::vector<std::vector<double>> DesiredOutput={{1,3},{3,4}};

    NeuralTest->Learning(InputValues, DesiredOutput);

    NeuralTest->GetCurrentWeights(WeightsVector);
    
    //NeuralTest->ConnectLayers();
    //In[3]->SetNeuronInput(5);
    for(int i=0;i<4;i++){
        
        //In[i]=NeuralTest->CreateInputNeuron();
        In[i]->SetNeuronInput((double)i+1.);
        std::cout<<In[i]->GetNeuronOutput()<<std::endl;
        
    }
    std::cout<<Out[0]->GetNeuronOutput()<<std::endl;
    std::cout<<Out[1]->GetNeuronOutput()<<std::endl;

    return 0;
}