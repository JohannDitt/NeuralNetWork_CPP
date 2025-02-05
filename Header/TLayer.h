#ifndef _TLayer_h_
#define _TLayer_h_

#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
using namespace std;

class TLayer
{

    public:
    virtual vector<TMatrix*> GetLayerOutput()=0;
    virtual void SetDelta(double Delta)=0; 


};

#endif