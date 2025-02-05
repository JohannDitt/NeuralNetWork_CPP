#ifndef _TFlattenLayer_h_
#define _TFlattenLayer_h_

#include "TInputNeuron.h"
#include "TLayer.h"
#include "TMatrix.h"
#include <iostream>
#include <vector>
using namespace std;

class TFlattenLayer
{

    public:
    TFlattenLayer()
    TFlattenLayer(TLayer* Layer);
    TFlattenLayer(const TFlattenLayer& Fl);
    ~TFlattenLayer();

    vector<double> GetLayerOutput();
    vector<TInputNeuron*> GetLayerOutputAsNeurons();

    void ConnectLayer(TLayer* Layer);

    private:
    TLayer* fLayer;
};

#endif