#ifndef SimTrack_h
#define SimTrack_h

#include "TObject.h"
#include <vector>

#include "SimDeposit.h"

class SimTrack : public TObject
{

  public:
    SimTrack() { MyClear(); }
    virtual ~SimTrack() {}

    inline void MyClear();

    //______________
    // === Getter ==
    int GetPDGID() { return pdg_id; }
    int GetTrackID() { return track_id; }
    float GetInitMass() { return init_mass; }
    float GetInitEk() { return init_Ek; }

    // == Init ==
    float GetInitPx() { return init_px; }
    float GetInitPy() { return init_py; }
    float GetInitPz() { return init_pz; }
    float GetInitX() { return init_x; }
    float GetInitY() { return init_y; }
    float GetInitZ() { return init_z; }
    double GetInitT() { return init_t; }

    // == Exit ==
    float GetExitPx() { return exit_px; }
    float GetExitPy() { return exit_py; }
    float GetExitPz() { return exit_pz; }
    float GetExitX() { return exit_x; }
    float GetExitY() { return exit_y; }
    float GetExitZ() { return exit_z; }
    double GetExitT() { return exit_t; }
    float GetTrackLength() { return track_length; }

    float GetEdep() { return tEdep; }

    const std::vector<Int_t> GetStepIdx() const { return stepIdx; }

    //_____________
    // == Setter ==
    void SetPDGID(int val) { pdg_id = val; }
    void SetTrackID(int val) { track_id = val; }
    void SetInitMass(float val) { init_mass = val; }
    void SetInitEk(float val) { init_Ek = val; }

    // == Init ==
    void SetInitPx(float val) { init_px = val; }
    void SetInitPy(float val) { init_py = val; }
    void SetInitPz(float val) { init_pz = val; }
    void SetInitX(float val) { init_x = val; }
    void SetInitY(float val) { init_y = val; }
    void SetInitZ(float val) { init_z = val; }
    void SetInitT(double val) { init_t = val; }

    // == Exit ==
    void SetExitPx(float val) { exit_px = val; }
    void SetExitPy(float val) { exit_py = val; }
    void SetExitPz(float val) { exit_pz = val; }
    void SetExitX(float val) { exit_x = val; }
    void SetExitY(float val) { exit_y = val; }
    void SetExitZ(float val) { exit_z = val; }
    void SetExitT(double val) { exit_t = val; }
    void SetTrackLength(float val) { track_length = val; }

    void SetEdep(float val) { tEdep = val; }

    void SetStepIdx(const std::vector<Int_t> &val) { stepIdx = val; }

    // == other functions ==
    void addDeposit(int idx, SimDeposit *aDep)
    {
        stepIdx.push_back(idx);
        tEdep += aDep->GetEdep();
        track_length += aDep->GetStepLength();
    }

  private:
    Int_t pdg_id;
    Int_t track_id;

    // == Init ==
    Float_t init_mass;
    Float_t init_Ek;
    Float_t init_px;
    Float_t init_py;
    Float_t init_pz;
    Float_t init_x;
    Float_t init_y;
    Float_t init_z;
    Double_t init_t;

    // == Exit ==
    Float_t exit_px;
    Float_t exit_py;
    Float_t exit_pz;
    Float_t exit_x;
    Float_t exit_y;
    Float_t exit_z;
    Double_t exit_t;

    Float_t track_length;

    Float_t tEdep;

    std::vector<Int_t> stepIdx;

    ClassDef(SimTrack, 1)
};

inline void SimTrack::MyClear()
{
    pdg_id = 0;
    track_id = -1;

    // == Init ==
    init_mass = 0;
    init_Ek = 0;
    init_px = 0;
    init_py = 0;
    init_pz = 0;
    init_x = 0;
    init_y = 0;
    init_z = 0;
    init_t = 0;

    // == Exit ==
    exit_px = 0;
    exit_py = 0;
    exit_pz = 0;
    exit_x = 0;
    exit_y = 0;
    exit_z = 0;
    exit_t = 0;
    track_length = 0.;

    // == Visible or Deposit Energy Related ==
    tEdep = 0;

    stepIdx.clear();
}

#endif
