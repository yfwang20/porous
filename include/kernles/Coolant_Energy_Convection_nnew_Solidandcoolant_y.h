#pragma once

#include "Kernel.h"

class Coolant_Energy_Convection_nnew_Solidandcoolant_y : public Kernel
{
public:
    Coolant_Energy_Convection_nnew_Solidandcoolant_y(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;


private:
    const MaterialProperty<Real> & _coolant_capacity;
    const Real & _tem_coolant_topboundary;
    const Real & _u_coolant_topboundary;
    int _component;
};