#ifndef _TPoolingLayer_h_
#define _TPoolingLayer_h_

#include <math.h>

#include "TLayer.h"
#include "TMatrix.h"
#include <string>
using namespace std;


class TPoolingLayer : public TLayer
{
    private:
    int fStride=2;
    int fKernelSize=2;
    TLayer* fLayer;
    double fDelta;
    bool fMaxPool=true;
    bool fAveragePool=false;

    void BackpropagateDelta();

    public:
    TPoolingLayer();
    TPoolingLayer(int KernelSize, int Stride);
    TPoolingLayer(TLayer* Layer);
    TPoolingLayer(const TPoolingLayer& Pl);
    ~TPoolingLayer()

    vector<TMatrix*> GetLayerOutput();

    void ConnectLayer(TLayer* Layer);
    
    void SetDelta(double Delta);
    void SetHyperParameters(int KernelSize, int Stride);
    void SetPooling(string Pooling);

};
#endif