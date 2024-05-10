#pragma once

#include "Kernel.h"

class Fission_Singlegroup_Eigen : public Kernel
{
public:
    Fission_Singlegroup_Eigen(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _fission_cross_section_v;
    // const MaterialProperty<Real> & _power_coefficient;
};