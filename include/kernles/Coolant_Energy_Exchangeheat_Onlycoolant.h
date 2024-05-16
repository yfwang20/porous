#pragma once

#include "Kernel.h"

class Coolant_Energy_Exchangeheat_Onlycoolant : public Kernel
{
public:
    Coolant_Energy_Exchangeheat_Onlycoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _coolant_alpha;
    const MaterialProperty<Real> & _area;
    const MaterialProperty<Real> & _tem_solid;
};