#pragma once

#include "Kernel.h"

class Solid_Exchangeheat_Solidandcoolant : public Kernel
{
public:
    Solid_Exchangeheat_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _coolant_alpha;
    const MaterialProperty<Real> & _area;
    const VariableValue & _tem_coolant;
    unsigned int _tem_coolant_var;
};