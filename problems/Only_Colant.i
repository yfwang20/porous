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


[Kernels]
    # coolant
    # coolant_continuity

    [coolant_continuity]
        type = Coolant_Continuity_Fake
        variable = u_coolant
        tem_coolant_topboundary = 290
        u_coolant_topboundary = 1
    []

    # coolant_momentum
    [coolant_momentum_viscidityandg]
        type = Coolant_Momentum_Viscidityandg_Solidandcoolant
        variable = pressure_coolant
        u_coolant = u_coolant
    []

    [coolant_momentum_pressure]
        type = Coolant_Momentum_Pressure_Solidandcoolant
        variable = pressure_coolant
        component = y
    []

    # coolant_energy

    [coolant_energy_diffusion]
        type = Coolant_Energy_Diffusion_term
        variable = tem_coolant
    []

    [coolant_energy_convection]
        type = Coolant_Energy_Convection_Solidandcoolant
        variable = tem_coolant
        u_coolant = u_coolant
        tem_coolant = tem_coolant
        component = y
    []

    [coolant_energy_exchangeheat]
        type = Coolant_Energy_Exchangeheat_Onlycoolant
        variable = tem_coolant
    []
[]



#TODO
[Materials]
    [porous]
        type = Material_Porous_Singlegroup_Onlycoolant
        tem_solid = 300
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
        value = 7E+6
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
    type = Steady
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
    [average_tem_coolant]
        type = ElementAverageValue
        variable = tem_coolant
        execute_on = 'initial linear'
    []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]