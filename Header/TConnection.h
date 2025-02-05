#ifndef _Connection_h_
#define _Connection_h_

#include "TNeuron.h"

class TConnection
{

    private:
    TNeuron* fNeuron;
    double fWeight;

    double fWeigthDiff=0;
    //double fMomentum=0;

    public:
    TConnection();
    TConnection(TNeuron* Neuron, double Weight);
    TConnection(const TConnection& Con);
    ~TConnection();

    void SetNeuron(TNeuron* neuron);
    void SetWeight(double weight);
    void SetNeuronWeight(TNeuron* Neuron, double Weight);
    void AddWeight(double WeightDiff);

    void ApplyBatch();

    TNeuron* GetNeuron();
    double GetWeight();

    double GetConnectionValue();
};


#endif