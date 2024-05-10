#pragma once

#include "Kernel.h"

class Solid_Exchangeheat_Onlysolid : public Kernel
{
public:
    Solid_Exchangeheat_Onlysolid(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _coolant_alpha;
    const MaterialProperty<Real> & _area;
    const MaterialProperty<Real> & _tem_coolant;
};