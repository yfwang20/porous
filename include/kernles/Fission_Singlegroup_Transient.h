#pragma once

#include "Kernel.h"

class Fission_Singlegroup_Transient : public Kernel
{
public:
    Fission_Singlegroup_Transient(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const Real & _keff;
    
    const MaterialProperty<Real> & _fission_cross_section_v;
    const MaterialProperty<Real> & _beta;
};