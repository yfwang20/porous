#pragma once

#include "Kernel.h"

class Solid_Fissionheat : public Kernel
{
public:
    Solid_Fissionheat(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _Eeff;
    const MaterialProperty<Real> & _porous_coefficient;
    const MaterialProperty<Real> & _fission_cross_section;
    const MaterialProperty<Real> & _power_coefficient;
    const VariableValue & _flux;
    unsigned int _flux_var;
};