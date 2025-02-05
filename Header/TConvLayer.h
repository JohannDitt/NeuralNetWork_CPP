#ifndef _TConvLayer_h_
#define _TConvLayer_h_

#include "TMatrix.h"
#include "TLayer.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TConvLayer : public TLayer
{

    private:
    TLayer* fLayer;
    vector<TMatrix*> fInput;
    bool fInputClear=false;

    int fKernelSize;
    int fNKernel;
    vector<TMatrix*> fKernels;
    
    double fDelta;
    
    bool fPadding=false;

    vector<TMatrix*> fInputSums;
    bool fInputSumsClear=false;

    void BackpropagateDelta();
    TMatrix* GetKernelSizeMatrix(TMatrix* m, int Line, int Column);

    vector<TMatrix*> GetInput();
    vector<TMatrix*> GetInputSums();

    public:
    TConvLayer();
    TConvLayer(int nKernel, int KernelSize);
    TConvLayer(const TConvLayer& Cl);
    ~TConvLayer();

    void ConnectLayer(TLayer* Layer);

    void SetDelta(double Delta);
    void SetPadding(bool Padding);

    vector<TMatrix*> GetLayerOutput();
}


#endif