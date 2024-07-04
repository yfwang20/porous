[Mesh]
    [generator]
        type = GeneratedMeshGenerator
        dim = 2
        xmax = 2
        ymax = 3
        nx = 50
        ny = 50
    []
[]

[Preconditioning]
    active = bdp
    [bdp]
        type = SMP
        petsc_options_iname = '-pc_type'
        petsc_options_value = 'lu'
        full = true
    []
[]

[Variables]
    [tem_coolant]
        order = FIRST
        family = LAGRANGE
    []
[]


[Kernels]
    # coolant
    

    # coolant_energy



    [coolant_energy_diffusion]
        type = Coolant_Energy_Diffusion_term
        variable = tem_coolant
    []

    [coolant_energy_convection]
        type = Coolant_Energy_Convection_nnew_Solidandcoolant_y
        variable = tem_coolant
        rhou = 700
        component = y
        # v = '0 1 0'
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




[]


[ICs]
    active = ' '
    [constant_tem_coolant]
        type = ConstantIC
        variable = tem_coolant
        value = 300
    []
    [constant_u_coolant]
        type = ConstantIC
        variable = u_coolant
        value = 1
    []
    [constant_pressure_solid]
        type = ConstantIC
        variable = pressure_coolant
        value = 7E+1
    []
[]

[Executioner]
    type = Steady
    solve_type = PJFNK

    #num_steps = 20
    #dt = 0.001
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