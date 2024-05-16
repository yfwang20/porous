#pragma once

#include "Kernel.h"

class Coolant_Energy_Exchangeheat_Solidandcoolant : public Kernel
{
public:
    Coolant_Energy_Exchangeheat_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _coolant_alpha;
    const MaterialProperty<Real> & _area;
    const VariableValue & _tem_solid;
    unsigned int _tem_solid_var;
};