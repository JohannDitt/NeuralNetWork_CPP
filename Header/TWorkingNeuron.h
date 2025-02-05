#include "TNeuron.h"
#include "TConnection.h"

#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#ifndef _WorkingNeuron_h_
#define _WorkingNeuron_h_

class TWorkingNeuron : public TNeuron
{
    public:

    TWorkingNeuron(); //default Constrcutor
    TWorkingNeuron(double Bias);
    TWorkingNeuron(double Bias, std::vector<TConnection*> &Connections, std::string FunctionName); //Constructor with parameter and default value
    TWorkingNeuron(const TWorkingNeuron& wn); //Copy Constructor
    ~TWorkingNeuron(); //Destructor

    double GetNeuronOutput();
    double GetDerivation();
    TConnection* GetConnection(int con);
    double GetDelta();

    void AddDelta(double DeltaPlus);
    void ResetNeuron();

    void SetNeuronInputs(const std::vector<TConnection*> &Connections);
    void SetBias(double Bias);
    void SetActivationfunction(std::string FunctionName);
    void SetDelta(double Desired);
    void ApplyBatch();

    void ResetConnections();
    void ConnectNeuron(TConnection* Con);
    void ConnectNeuron(TNeuron* Neuron, double Weight);

    void Learning(double &LearningRate);
    void BackpropagateDelta();

    

    private: 
    double fBias;
    std::string fFunction;
    std::vector<TConnection*> fConnections;
    double fDelta=0;
    double fBiasDiff=0;

    double fNetInput=0;
    double fActivationLevel=0;
    double fDerivationValue=0;

    bool fNetInputCalculated=false;
    bool fOutputCalculated=false;
    bool fDerivationCalculated=false;


    
    
    double GetNetInput();
    
    double Activate(double x);

    double Identity(double x);
    double Sigmoid(double x);
    double TanH(double x);
    double ReLU(double x);
    double Softplus(double x);
    
    double Derivation(double x);

};


#endif