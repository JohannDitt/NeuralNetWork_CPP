#include "TNeuron.h"

#ifndef _InputNeuron_h_
#define _InputNeuron_h_

class TInputNeuron : public TNeuron
{
    public:

    TInputNeuron(); //default Constrcutor
    TInputNeuron(double Input); //Constructor with parameter and default value
    TInputNeuron(const TInputNeuron& In); //Copy Constructor
    ~TInputNeuron(); //Destructor

    double GetNeuronOutput();
    void SetNeuronInput(double Input);
    
    
    private: 
    double fNeuronInput;
};



#endif
