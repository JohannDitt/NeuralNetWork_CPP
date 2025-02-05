#ifndef _TInLayer_h_
#define _TInLayer_h_

#include "TLayer.h"
#include <iostream>
#include "TMatrix.h"
#include <vector>
using namespace std;
#include <string>

class TInLayer : public TLayer
{

    private:
    vector<TMatrix*> fNetInput;


    public:

    TInLayer();
    TInLayer(const vector<TMatrix*> &Input);
    TInLayer(const TInLayer& Il);
    ~TInLayer();

    vector<TMatrix*> GetLayerOutput();

    void SetNetInput(const vector<TMatrix*> &Input);
    void AddMatrix(TMatrix* m);
};

#endif