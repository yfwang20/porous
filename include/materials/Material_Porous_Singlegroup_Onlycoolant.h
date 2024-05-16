#pragma once

#include "Material.h"

class Material_Porous_Singlegroup_Onlycoolant : public Material
{
public:
    static InputParameters validParams();

    Material_Porous_Singlegroup_Onlycoolant(const InputParameters & parameters);

protected:
    virtual void computeQpProperties() override;

    const Real & _input_tem_solid;
    const VariableValue & _tem_coolant;
    const Real & _input_porous_coefficient;
    const Real & _input_velocity;
    const Real & _input_area;
    const Real & _input_Eeff;
    const Real & _input_v;
    const Real & _input_power_coefficient;
    const Real & _input_flow_resistance;

    MaterialProperty<Real> & _tem_solid;
    MaterialProperty<Real> & _solid_rho;
    MaterialProperty<Real> & _solid_capacity;
    MaterialProperty<Real> & _solid_k;
    MaterialProperty<Real> & _porous_coefficient;
    MaterialProperty<Real> & _area;
    MaterialProperty<Real> & _Eeff;

    MaterialProperty<Real> & _coolant_alpha;
    MaterialProperty<Real> & _coolant_rho;
    MaterialProperty<Real> & _coolant_capacity;
    MaterialProperty<Real> & _coolant_lambda;
    MaterialProperty<Real> & _flow_resistance;


    MaterialProperty<Real> & _beta;
    MaterialProperty<Real> & _lambda;
    MaterialProperty<Real> & _absorption_cross_section;
    MaterialProperty<Real> & _fission_cross_section;
    MaterialProperty<Real> & _fission_cross_section_v;
    MaterialProperty<Real> & _diffusion_coefficient;
    MaterialProperty<Real> & _velocity;
    MaterialProperty<Real> & _power_coefficient;
};

