#include "Material_Porous_Singlegroup_Onlycoolant.h"

registerMooseObject("PorousApp", Material_Porous_Singlegroup_Onlycoolant);

InputParameters Material_Porous_Singlegroup_Onlycoolant::validParams()
{
    InputParameters params = Material::validParams();
    params.addClassDescription("For meterial in Porous");
    params.addRequiredParam<Real>("tem_solid", "temperature of solid");
    params.addRequiredCoupledVar("tem_coolant", "temperature of coolant");
    params.addRequiredParam<Real>("porous_coefficient", "porous coefficient");
    params.addRequiredParam<Real>("velocity", "nuetron velocity");
    params.addRequiredParam<Real>("area", "heat exchange area");
    params.addRequiredParam<Real>("Eeff", "E of single fission");
    params.addRequiredParam<Real>("v", "v of each fission");
    params.addParam<Real>("power_coefficient", 1.0, "power coefficient");
    params.addRequiredParam<Real>("flow_resistance", "flow resistance;");
    return params;
}

Material_Porous_Singlegroup_Onlycoolant::Material_Porous_Singlegroup_Onlycoolant(const InputParameters & parameters)
    :   Material(parameters),
        _input_tem_solid(getParam<Real>("tem_solid")),
        _tem_coolant(coupledValue("tem_coolant")),
        _input_porous_coefficient(getParam<Real>("porous_coefficient")),
        _input_velocity(getParam<Real>("velocity")),
        _input_area(getParam<Real>("area")),
        _input_Eeff(getParam<Real>("Eeff")),
        _input_v(getParam<Real>("v")),
        _input_power_coefficient(getParam<Real>("power_coefficient")),
        _input_flow_resistance(getParam<Real>("flow_resistance")),
        

        _tem_solid(declareProperty<Real>("tem_solid")),
        _solid_rho(declareProperty<Real>("solid_rho")),
        _solid_capacity(declareProperty<Real>("solid_capacity")),
        _solid_k(declareProperty<Real>("solid_k")),
        _porous_coefficient(declareProperty<Real>("porous_coefficient")),
        _area(declareProperty<Real>("area")),
        _Eeff(declareProperty<Real>("Eeff")),

        _coolant_alpha(declareProperty<Real>("coolant_alpha")),
        _coolant_rho(declareProperty<Real>("coolant_rho")),
        _coolant_capacity(declareProperty<Real>("coolant_capacity")),
        _coolant_lambda(declareProperty<Real>("coolant_lambda")),
        _flow_resistance(declareProperty<Real>("flow_resistance")),

        _beta(declareProperty<Real>("beta")),
        _lambda(declareProperty<Real>("lambda")),
        _absorption_cross_section(declareProperty<Real>("absorption_cross_section")),
        _fission_cross_section(declareProperty<Real>("fission_cross_section")),
        _fission_cross_section_v(declareProperty<Real>("fission_cross_section_v")),
        _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
        _velocity(declareProperty<Real>("velocity")),
        _power_coefficient(declareProperty<Real>("power_coefficient"))
{
}

void Material_Porous_Singlegroup_Onlycoolant::computeQpProperties()
{
    _tem_solid[_qp] = _input_tem_solid;
    _solid_rho[_qp] = 10690;
    _solid_capacity[_qp] = 244.91 + 0.0475 * _input_tem_solid + 0.0000258 * _input_tem_solid * _input_tem_solid;
    _solid_k[_qp] = 7.81 - 0.0083 * _input_tem_solid + 0.000003036 * _input_tem_solid * _input_tem_solid;
    _porous_coefficient[_qp] = _input_porous_coefficient;
    _area[_qp] = _input_area;
    _Eeff[_qp] = _input_Eeff;

    _coolant_alpha[_qp] = 4105;
    _coolant_rho[_qp] = 598.24 + 2.93 * _tem_coolant[_qp] - 0.836E-2 * _tem_coolant[_qp] * _tem_coolant[_qp];
    _coolant_capacity[_qp] = 2.06E+4 - 126 * _tem_coolant[_qp] + 0.2539 * _tem_coolant[_qp] * _tem_coolant[_qp];
    _coolant_lambda[_qp] = 0.355 + 0.34E-2 * _tem_coolant[_qp] - 8.82E-6 * _tem_coolant[_qp] * _tem_coolant[_qp];
    _flow_resistance[_qp] = _input_flow_resistance;

    _beta[_qp] = 0.0065;
    _lambda[_qp] = 0.0785;
    _absorption_cross_section[_qp] = 15.22 + 0.0000346 * _input_tem_solid + 0.0000104 * _tem_coolant[_qp];
    _fission_cross_section[_qp] = 18.9 - 0.000104 * _input_tem_solid - 0.0104 * _tem_coolant[_qp];
    _fission_cross_section_v[_qp] = (18.9 - 0.000104 * _input_tem_solid - 0.0104 * _tem_coolant[_qp]) * _input_v;
    _diffusion_coefficient[_qp] = 0.092 - 0.000000275 * _input_tem_solid - 0.000000275 * _tem_coolant[_qp];
    _velocity[_qp] = _input_velocity;
    _power_coefficient[_qp] = _input_power_coefficient;

    // _beta[_qp] = 0.0065;
    // _lambda[_qp] = 0.0785;
    // _absorption_cross_section[_qp] = 15.22;
    // _fission_cross_section[_qp] = 18.9;
    // _fission_cross_section_v[_qp] = (18.9) * _input_v;
    // _diffusion_coefficient[_qp] = 0.092;
    // _velocity[_qp] = _input_velocity;
}