[Mesh]
    [generator]
        type = GeneratedMeshGenerator
        dim = 2
        xmax = 2
        ymax = 3
        nx = 40
        ny = 40
    []
[]

[Preconditioning]
    active = smp_all
    # smp_all:better(dt)!
    [bdp]
        type = SMP
        petsc_options_iname = '-pc_type'
        petsc_options_value = 'lu'
    []

    [smp_all]
        type = SMP
        full = true
        petsc_options_iname = '-pc_type'
        petsc_options_value = 'lu'
    []

    [fdp]
        type = FDP
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
    [neutrontimederivative]
        type = NeutronTimeDerivative
        variable = flux
    []
    
    [diffusion]
        type = Diffusion_term_Singlegroup
        variable = flux
    []

    [absorption]
        type = Absorption_Singlegroup
        variable = flux
    []

    [fission]
        type = Fission_Singlegroup_Transient
        variable = flux
        keff = 2.544552598
    []

    [delayedneutronsources]
        type = Delayed_NeutronSources
        variable = flux
        delayed_c1 = delayed_c1
    []

    # neutron 2
    [delayed_nucleus_c1_timederivate]
        type = DelayedNeutron_TimeDerivate
        variable = delayed_c1
    []

    [delayed_nucleus_c1_decayandfission]
        type = DelayedNeutron_Decayandfission
        variable = delayed_c1
        flux = flux
        keff = 2.544552598
    []

    # solid 1
    [solid_timederivative]
        type = Solid_TimeDerivative
        variable = tem_solid
    []

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
    []
[]

[AuxKernels]
    [power]
        type = Power
        variable = power
        flux = flux
        execute_on = 'initial timestep_end'
    []
[]

#TODO
[Materials]
    [porous]
        type = Material_Porous_Singlegroup_Onlysolid
        tem_solid = tem_solid
        # tem_coolant = 290
        tem_coolant = 280 # if changed
        porous_coefficient = 0.39 # HTR-PM
        velocity = 20000
        area = 31.94
        # area = 0.1
        Eeff = 3.2E-11
        v = 2.5
        power_coefficient = 1E+19
        # v = 0.8
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

    # delayed_c1
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
    active = 'eigen_flux eigen_c1 eigen_tem_solid'
    # active = 'constant_flux constant_delayed_c1 constant_tem_solid'
    [constant_flux]
        type = ConstantIC
        variable = flux
        value = 2000000
    []

    #[ran_flux]
    #    type = RandomIC
    #    seed = 5
    #    variable = flux
    #    max = 3
    #    min = 2
    #[]

    [constant_delayed_c1]
        type = ConstantIC
        variable = delayed_c1
        value = 2000000
    []

    [constant_tem_solid]
        type = ConstantIC
        variable = tem_solid
        value = 300
    []

    [eigen_flux]
        type = SolutionIC
        solution_uo = eigensolution
        variable = flux
        from_variable = 'flux'
    []

    [eigen_c1]
        type = SolutionIC
        solution_uo = eigensolution
        variable = delayed_c1
        from_variable = 'delayed_c1'
    []

    [eigen_tem_solid]
        type = SolutionIC
        solution_uo = eigensolution
        variable = tem_solid
        from_variable = 'tem_solid'
    []
[]

[UserObjects]
    [eigensolution]
        type = SolutionUserObject
        # mesh = 'results/Without_normalization/Only_Solid_eigen_out.e'
        mesh = 'results/Power=85MW_Without_normalization/Only_Solid_eigen_out.e'
        system_variables = 'flux delayed_c1 tem_solid'
        timestep = LATEST
    []
[]

[Executioner]
  type = Transient
  solve_type = PJFNK
  num_steps = 20
  dt = 0.001
  # l_max_its = 50

  automatic_scaling = true
  compute_scaling_once = false
  resid_vs_jac_scaling_param = 0
  off_diagonals_in_auto_scaling = false

   # line_search = 'none'
[]

[Postprocessors]
    [fnorm_flux]
        type = ElementIntegralVariablePostprocessor
        variable = flux
        execute_on = 'initial timestep_end'
    []

    [powernorm]
        type = ElementIntegralVariablePostprocessor
        variable = power
        execute_on = 'initial timestep_end'
    []

    [fnorm_delayed_c1]
        type = ElementIntegralVariablePostprocessor
        variable = delayed_c1
        execute_on = 'initial timestep_end'
    []

    [average_tem_solid]
        type = ElementAverageValue
        variable = tem_solid
        execute_on = 'initial timestep_end'
    []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true

  # print_linear_residuals = true
[]

[Debug]
   # show_var_residual_norms = true
[]