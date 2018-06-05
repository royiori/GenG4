#ifndef SimDeposit_h
#define SimDeposit_h

#include "TObject.h"
#include <vector>

class SimDeposit : public TObject
{
  private:
    Int_t pdg_id;
    Int_t track_id;
    Int_t prod_id; // Producer ID

    // == Init ==
    Float_t pre_px;
    Float_t pre_py;
    Float_t pre_pz;
    Float_t pre_x;
    Float_t pre_y;
    Float_t pre_z;
    Double_t pre_t;

    // == Exit ==
    Float_t post_px;
    Float_t post_py;
    Float_t post_pz;
    Float_t post_x;
    Float_t post_y;
    Float_t post_z;
    Double_t post_t;

    // == Visible or Deposit Energy Related ==
    Float_t edep;
    Float_t length; // step length
    bool isFirstDeposit;

  public:
    SimDeposit()
    {
        pdg_id = 0;
        track_id = -1;
        prod_id = -1;

        // == Init ==
        pre_px = 0;
        pre_py = 0;
        pre_pz = 0;
        pre_x = 0;
        pre_y = 0;
        pre_z = 0;
        pre_t = 0;

        // == Exit ==
        post_px = 0;
        post_py = 0;
        post_pz = 0;
        post_x = 0;
        post_y = 0;
        post_z = 0;
        post_t = 0;

        // == Visible or Deposit Energy Related ==
        edep = 0;
        length = 0;
        isFirstDeposit = false;
    }
    virtual ~SimDeposit() {}

    //_____________
    // == Getter ==
    int GetPDGID() { return pdg_id; }
    int GetTrackID() { return track_id; }
    int GetProducerID() { return prod_id; }

    // == Pre ==
    float GetPrePx() {return pre_px;}
    float GetPrePy() {return pre_py;}
    float GetPrePz() {return pre_pz;}
    float GetPreX() { return pre_x; }
    float GetPreY() { return pre_y; }
    float GetPreZ() { return pre_z; }
    double GetPreT() { return pre_t; }
    
    // == Post ==
    float GetPostPx() {return post_px;}
    float GetPostPy() {return post_py;}
    float GetPostPz() {return post_pz;}
    float GetPostX() { return post_x; }
    float GetPostY() { return post_y; }
    float GetPostZ() { return post_z; }
    double GetPostT() { return post_t; }
    
    // == Visible or Deposit Energy Related ==
    float GetEdep() { return edep; }
    float GetStepLength() { return length; }
    bool IsFirstDeposit() { return isFirstDeposit; }

    //_____________
    // == Setter ==
    void SetPDGID(int val) { pdg_id = val; }
    void SetTrackID(int val) { track_id = val; }
    void SetProducerID(int val) { prod_id = val; }

    // == Pre ==
    void SetPrePx(float val) {pre_px = val;}
    void SetPrePy(float val) {pre_py = val;}
    void SetPrePz(float val) {pre_pz = val;}
    void SetPreX(float val) { pre_x = val; }
    void SetPreY(float val) { pre_y = val; }
    void SetPreZ(float val) { pre_z = val; }
    void SetPreT(double val) { pre_t = val; }
    
    // == Post ==
    void SetPostPx(float val) {post_px = val;}
    void SetPostPy(float val) {post_py = val;}
    void SetPostPz(float val) {post_pz = val;}
    void SetPostX(float val) { post_x = val; }
    void SetPostY(float val) { post_y = val; }
    void SetPostZ(float val) { post_z = val; }
    void SetPostT(double val) { post_t = val; }
    
    // == Visible or Deposit Energy Related ==
    void SetEdep(float val) { edep = val; }
    void SetStepLength(float val) { length = val; }
    void SetFirstDeposit(bool val) { isFirstDeposit = val; }

    ClassDef(SimDeposit, 1)
};

#endif
