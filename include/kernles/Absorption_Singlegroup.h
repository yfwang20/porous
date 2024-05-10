#pragma once

#include "Kernel.h"

class Absorption_Singlegroup : public Kernel
{
public:
    Absorption_Singlegroup(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _absorption_cross_section;
    // const MaterialProperty<Real> & _power_coefficient;
};