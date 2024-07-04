[Mesh]
    [generator]
        type = GeneratedMeshGenerator
        dim = 2
        xmax = 2
        ymax = 3
        nx = 100
        ny = 100
    []
[]

[Preconditioning]
    active = bdp
    [bdp]
        type = SMP
        petsc_options_iname = '-pc_type'
        petsc_options_value = 'lu'
    []
[]

[Variables]
    [flux]
        order = FIRST
        family = LAGRANGE
    []

    [delayed_c1]
        order = FIRST
        family = LAGRANGE
    []

    [tem_solid]
        order = FIRST
        family = LAGRANGE
    []
    
    [tem_coolant]
        order = FIRST
        family = LAGRANGE
    []

    [u_coolant]
        order = FIRST
        family = LAGRANGE
    []

    [pressure_coolant]
        order = FIRST
        family = LAGRANGE
    []
[]

[AuxVariables]
    [power]
        order = CONSTANT
        family = MONOMIAL
    []
[]

[Kernels]
    # neutron 1
    [diffusion]
        type = Diffusion_term_Singlegroup
        variable = flux
    []

    [absorption]
        type = Absorption_Singlegroup
        variable = flux
    []

    [fission]
        type = Fission_Singlegroup_Eigen
        variable = flux
        extra_vector_tags = 'eigen'
    []

    # delayed 1

    [delayed_nucleus_c1_decay]
        type = DelayedNeutron_Decay
        variable = delayed_c1
    []

    [delayed_nucleus_c1_fission]
        type = DelayedNeutron_Fission
        variable = delayed_c1
        flux = flux
        extra_vector_tags = 'eigen'
    []

    # solid 1

    [solid_diffusion]
        type = Solid_Diffusion_term
        variable = tem_solid
    []

    [solid_exchangeheat]
        type = Solid_Exchangeheat_Solidandcoolant
        variable = tem_solid
        tem_coolant = tem_coolant
    []

    [solid_fissionheat]
        type = Solid_Fissionheat
        variable = tem_solid
        flux = flux
        # extra_vector_tags = 'eigen'
    []

    # coolant

    # coolant_continuity



    # coolant_momentum
    [coolant_momentum_viscidityandg]
        type = Coolant_Momentum_u_Viscidityandg_Solidandcoolant
        variable = u_coolant
    []

    [coolant_momentum_pressure]
        type = Coolant_Momentum_u_Pressure_new_Solidandcoolant
        variable = u_coolant
        pressure_coolant = pressure_coolant
        v = '0 1 0'
    []

    # coolant_energy

    [coolant_energy_diffusion]
        type = Coolant_Energy_Diffusion_term
        variable = tem_coolant
    []

    [coolant_energy_convection]
        type = Coolant_Energy_Convection_new_Solidandcoolant
        variable = tem_coolant
        u_coolant = u_coolant
        tem_coolant = tem_coolant
        v = '0 1 0'
    []

    [coolant_energy_exchangeheat]
        type = Coolant_Energy_Exchangeheat_Solidandcoolant
        variable = tem_coolant
        tem_solid = tem_solid
    []

    # coolant_poission
    [coolant_poission]
        type = Coolant_Poission_Solidandcoolant
        variable = pressure_coolant
        v1 = '0 1 0'
        v2 = '0 1 0'
    []
[]

[AuxKernels]
    [power]
        type = Power
        variable = power
        flux = flux
        execute_on = 'initial linear'
    []
[]

#TODO
[Materials]
    [porous]
        type = Material_Porous_Singlegroup_Solidandcoolant
        tem_solid = tem_solid
        tem_coolant = tem_coolant
        porous_coefficient = 0.39
        velocity = 20000
        area = 31.94
        Eeff = 3.2E-11
        v = 2.5
        # v = 1
        power_coefficient = 1E+19
        flow_resistance = 0.1
    []
[]

#TODO
[BCs]
    # active = 'neutron_vacuumbc_left neutron_vacuumbc_right neutron_vacuumbc_top neutron_vacuumbc_bottom delayed_c1_left delayed_c1_right delayed_c1_top delayed_c1_bottom tem_solid_left tem_solid_right tem_solid_top tem_solid_bottom'
    
    active = 'neutron_left neutron_right neutron_top neutron_bottom delayed_c1_left delayed_c1_right delayed_c1_top delayed_c1_bottom tem_solid_left tem_solid_right tem_solid_top tem_solid_bottom tem_coolant_top u_coolant_top pressure_coolant_bottom'
    # neutron
    [neutron_left]
        type = DirichletBC
        variable = flux
        boundary = 'left'
        value = 0
    []

    [neutron_right]
        type = DirichletBC
        variable = flux
        boundary = 'right'
        value = 0
    []

    [neutron_top]
        type = DirichletBC
        variable = flux
        boundary = 'top'
        value = 0
    []

    [neutron_bottom]
        type = DirichletBC
        variable = flux
        boundary = 'bottom'
        value = 0
    []

    # neutron vacuum bc
    [neutron_vacuumbc_left]
        type = VacuumBC
        variable = flux
        alpha = 0.1
        boundary = 'left'
    []

    [neutron_vacuumbc_right]
        type = VacuumBC
        variable = flux
        alpha = 0.1
        boundary = 'right'
    []

    [neutron_vacuumbc_top]
        type = VacuumBC
        variable = flux
        alpha = 0.1
        boundary = 'top'
    []

    [neutron_vacuumbc_bottom]
        type = VacuumBC
        variable = flux
        alpha = 0.1
        boundary = 'bottom'
    []

    # c1
    [delayed_c1_left]
        type = DirichletBC
        variable = delayed_c1
        boundary = 'left'
        value = 0
    []

    [delayed_c1_right]
        type = DirichletBC
        variable = delayed_c1
        boundary = 'right'
        value = 0
    []

    [delayed_c1_top]
        type = DirichletBC
        variable = delayed_c1
        boundary = 'top'
        value = 0
    []

    [delayed_c1_bottom]
        type = DirichletBC
        variable = delayed_c1
        boundary = 'bottom'
        value = 0
    []


    # tem_solid
    # set 300 ssd
    [tem_solid_left]
        type = DirichletBC
        variable = tem_solid
        boundary = 'left'
        value = 300
    []

    [tem_solid_right]
        type = DirichletBC
        variable = tem_solid
        boundary = 'right'
        value = 300
    []

    [tem_solid_top]
        type = DirichletBC
        variable = tem_solid
        boundary = 'top'
        value = 300
    []

    [tem_solid_bottom]
        type = DirichletBC
        variable = tem_solid
        boundary = 'bottom'
        value = 300
    []

    # tem_coolant
    [tem_coolant_top]
        type = DirichletBC
        variable = tem_coolant
        boundary = 'top'
        value = 290
    []

    # u_coolant
    [u_coolant_top]
        type = DirichletBC
        variable = u_coolant
        boundary = 'top'
        value = 1
    []

    # pressure_coolant
    [pressure_coolant_bottom]
        type = DirichletBC
        variable = pressure_coolant
        boundary = 'bottom'
        value = 7E+1
    []

[]


[ICs]
    active = ' '
    [constant_flux]
        type = ConstantIC
        variable = flux
        value = 2
    []
    [constant_tem_solid]
        type = ConstantIC
        variable = tem_solid
        value = 300
    []
[]

[Executioner]
    type = Eigenvalue
    solve_type = PJFNK
    #normal_factor = 8.5211024147101e+7
    #normalization = powernorm
    # bx_norm = fnorm
    # n_eigen_pairs = 1
    # which_eigen_pairs = LARGEST_IMAGINARY

    automatic_scaling = true

    # l_max_its = 50
    # l_tol = 0.001
[]

[Postprocessors]
  [fnorm]
    type = ElementIntegralVariablePostprocessor
    variable = flux
    execute_on = 'initial linear'
  []

  [average_flux]
    type = ElementAverageValue
    variable = flux
    execute_on = 'initial linear'
  []

  [powernorm]
        type = ElementIntegralVariablePostprocessor
        variable = power
        execute_on = 'initial linear'
  []

    [fnorm_delayed_c1]
        type = ElementIntegralVariablePostprocessor
        variable = delayed_c1
        execute_on = 'initial linear'
    []

    [average_tem_solid]
        type = ElementAverageValue
        variable = tem_solid
        execute_on = 'initial linear'
    []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]