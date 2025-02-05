#ifndef _NeuralNetwork_h_
#define _NeuralNetwork_h_

#include "TInputNeuron.h"
#include "TWorkingNeuron.h"


#include <vector>
#include <string>
//TODO: Zeichnung, Bias extrahieren
class TNeuralNetwork
{

    public:
    TNeuralNetwork();
    TNeuralNetwork(std::vector<TInputNeuron*> &In, std::vector<TWorkingNeuron*> &On, int HiddenLayers=0);
    TNeuralNetwork(const TNeuralNetwork& NN);
    ~TNeuralNetwork();

    void SetInputNeurons(std::vector<TInputNeuron*> &In);
    void SetOutputNeurons(std::vector<TWorkingNeuron*> &On);
    void SetNHiddenLayers(int HiddenLayers);
    void SetInOutLayers(std::vector<TInputNeuron*> &In, std::vector<TWorkingNeuron*> &On, int HiddenLayers=0);
    void SetLearningRate(double LearningRate);
    void SetEpochs(int Epochs);
    void SetBatchSize(int BatchSize);
    
    TInputNeuron* CreateInputNeuron();
    TWorkingNeuron* CreateOutputNeuron();

    void CreateHiddenNeuron(int Layer, double Bias, std::string Function);

    void ResetNeurons();
    
    void ConnectLayers();
    void ConnectLayers(const std::vector<std::vector<double>> &WeightsVector);

    void Learning(const std::vector<std::vector<double>> &InputValues, const std::vector<std::vector<double>> &DesiredOutput);    
    
    void GetCurrentWeights(std::vector<std::vector<double>> &WeightsVector);
    
    private:
    std::vector<TInputNeuron*> fInputNeurons;
    std::vector<TWorkingNeuron*> fOutputNeurons;
    int fHiddenLayers;

    bool fHiddenNeuronsExist=false;
    std::vector<std::vector<TWorkingNeuron*>> fHiddenNeurons;

    double fLearningRate=0.01;
    int fEpochs=1000;
    int fBatchSize=10;

    void ConnectLayer(int Layer);
    void ConnectLayer(int Layer, const std::vector<double> &Weights);

    void DeltaLearning(const std::vector<std::vector<double>> &InputValues, const std::vector<std::vector<double>> &DesiredOutput); 
    void Backpropagation(const std::vector<std::vector<double>> &InputValues, const std::vector<std::vector<double>> &DesiredOutput);



};



#endif
