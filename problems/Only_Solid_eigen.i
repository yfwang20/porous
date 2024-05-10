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
        type = Solid_Exchangeheat_Onlysolid
        variable = tem_solid
    []

    [solid_fissionheat]
        type = Solid_Fissionheat
        variable = tem_solid
        flux = flux
        # extra_vector_tags = 'eigen'
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
        type = Material_Porous_Singlegroup_Onlysolid
        tem_solid = tem_solid
        tem_coolant = 290
        porous_coefficient = 0.39
        velocity = 20000
        area = 31.94
        Eeff = 3.2E-11
        v = 2.5
        # v = 1
        power_coefficient = 1E+19
    []
[]

#TODO
[BCs]
    # active = 'neutron_vacuumbc_left neutron_vacuumbc_right neutron_vacuumbc_top neutron_vacuumbc_bottom delayed_c1_left delayed_c1_right delayed_c1_top delayed_c1_bottom tem_solid_left tem_solid_right tem_solid_top tem_solid_bottom'
    
    active = 'neutron_left neutron_right neutron_top neutron_bottom delayed_c1_left delayed_c1_right delayed_c1_top delayed_c1_bottom tem_solid_left tem_solid_right tem_solid_top tem_solid_bottom'
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
[]


[ICs]
    active = 'constant_tem_solid'
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