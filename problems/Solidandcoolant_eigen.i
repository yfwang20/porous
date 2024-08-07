[Mesh]
    [generator]
        type = GeneratedMeshGenerator
        dim = 2
        xmax = 3
        ymax = 4
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

    [smp_test]
      type = SMP
      #full = true
      off_diag_row    = 'tem_solid'
      off_diag_column = 'flux'
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'lu'
    []

    [smp_all]
        type = SMP
        full = true
        petsc_options_iname = '-pc_type'
        petsc_options_value = 'lu'
    []

    [smp_lt]
      type = SMP
      #full = true
      off_diag_row    = 'delayed_c1 tem_solid tem_solid tem_coolant tem_coolant tem_coolant'
      off_diag_column = 'flux flux delayed_c1 flux delayed_c1 tem_solid'
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'lu'
    []

    [smp_set]
      type = SMP
      #full = true
      off_diag_row    = 'delayed_c1 tem_solid tem_coolant tem_coolant'
      off_diag_column = 'flux flux tem_solid flux'
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'lu'
    []

    [smp_ut]
      type = SMP
      #full = true
      off_diag_row    = 'flux flux delayed_c1 flux delayed_c1 tem_solid'
      off_diag_column = 'delayed_c1 tem_solid tem_solid tem_coolant tem_coolant tem_coolant'
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'lu'
    []

    [pbp_test]
		type = PBP
		solve_order = 'flux delayed_c1 tem_solid tem_coolant'
		preconditioner  = 'LU LU LU LU'
		#full = true
		off_diag_row    = 'tem_solid'
		off_diag_column = 'flux'
  []

  [pbp]
    type = PBP
    solve_order = 'flux delayed_c1 tem_solid tem_coolant'
    preconditioner  = 'LU LU LU LU'
    #full = true
    off_diag_row    = 'delayed_c1 tem_solid tem_solid tem_coolant tem_coolant tem_coolant'
    off_diag_column = 'flux flux delayed_c1 flux delayed_c1 tem_solid'
  []

	[pbp_lt]
		type = PBP
		solve_order = 'flux delayed_c1 tem_solid tem_coolant'
		preconditioner  = 'LU LU LU LU'
		#full = true
		off_diag_row    = 'delayed_c1 tem_solid tem_solid tem_coolant tem_coolant tem_coolant'
		off_diag_column = 'flux flux delayed_c1 flux delayed_c1 tem_solid'
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

    # coolant_energy

    [coolant_energy_diffusion]
        type = Coolant_Energy_Diffusion_term
        variable = tem_coolant
    []

    [coolant_energy_convection]
        type = Coolant_Energy_Convection_nnew_Solidandcoolant_y
        variable = tem_coolant
        tem_coolant_topboundary = 290
        u_coolant_topboundary = 5
        component = y
        # v = '0 1 0'
    []

    [coolant_energy_exchangeheat]
        type = Coolant_Energy_Exchangeheat_Solidandcoolant
        variable = tem_coolant
        tem_solid = tem_solid
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
        porous_coefficient = 0.5535
        velocity = 20000
        area = 187.9
        Eeff = 3.2E-11
        v = 2.5
        # v = 1
        power_coefficient = 3.43E+20 # 3.43E+20 confirmed
        flow_resistance = 0.1
    []
[]

#TODO
[BCs]
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
    

    # tem_coolant
    [tem_coolant_bottom]
        type = DirichletBC
        variable = tem_coolant
        boundary = 'bottom'
        value = 290
    []



[]


[ICs]
    active = ''
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

    free_power_iterations = 0
    automatic_scaling = true
    # normal_factor = 10.487E+17
    # normalization = average_flux

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
    [average_tem_coolant]
        type = ElementAverageValue
        variable = tem_coolant
        execute_on = 'initial linear'
    []
[]

[VectorPostprocessors]
  [eigenvalues]
    type = Eigenvalues
    execute_on = 'timestep_end'
  []

  [diagonal_flux]
    type = PointValueSampler
    variable = 'tem_coolant'
    points = '0 4 0 0.3 4 0 0.6 4 0 0.0 4 0 1.2 4 0 1.5 4 0 1.8 4 0 2.1 4 0 2.4 4 0 2.7 4 0 3 4 0'
    sort_by = x
  []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]