[Mesh]
    [generator]
        type = GeneratedMeshGenerator
        dim = 2
        xmax = 3
        ymax = 4
        nx = 80
        ny = 80
    []
[]

[Preconditioning]
    active = smp_all
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
        keff = 1.001487526
    []

    [delayedneutronsources]
        type = Delayed_NeutronSources
        variable = flux
        delayed_c1 = delayed_c1
    []


    # delayed 1

    [delayed_nucleus_c1_timederivate]
        type = DelayedNeutron_TimeDerivate
        variable = delayed_c1
    []

    [delayed_nucleus_c1_decayandfission]
        type = DelayedNeutron_Decayandfission
        variable = delayed_c1
        flux = flux
        keff = 1.001487526
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

    [coolant_energy_timederivative]
        type = Coolant_Energy_TimeDerivate
        variable = tem_coolant
    []

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
        # power_coefficient = 1
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
        value = 295
    []



[]


[ICs]
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

    [eigen_tem_coolant]
        type = SolutionIC
        solution_uo = eigensolution
        variable = tem_coolant
        from_variable = 'tem_coolant'
    []
[]

[UserObjects]
    [eigensolution]
        type = SolutionUserObject
        # mesh = 'results/Without_normalization/Only_Solid_eigen_out.e'
        mesh = 'results/4*3_Power=2500MW/Solidandcoolant_eigen_out.e'
        system_variables = 'flux delayed_c1 tem_solid tem_coolant'
        timestep = LATEST
    []
[]

[Executioner]
    type = Transient
    solve_type = PJFNK
    end_time = 2
    dt = 0.01
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
  [average_flux]
    type = ElementAverageValue
    variable = flux
    execute_on = 'initial linear'
  []

    [average_delayed_c1]
        type = ElementAverageValue
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

    [max_flux]
    type = ElementExtremeValue
    variable = flux
    execute_on = 'initial linear'
  []

    [max_delayed_c1]
        type = ElementExtremeValue
        variable = delayed_c1
        execute_on = 'initial linear'
    []

    [max_tem_solid]
        type = ElementExtremeValue
        variable = tem_solid
        execute_on = 'initial linear'
    []

    [max_tem_coolant]
        type = ElementExtremeValue
        variable = tem_coolant
        execute_on = 'initial linear'
    []

    [powernorm]
        type = ElementIntegralVariablePostprocessor
        variable = power
        execute_on = 'initial linear'
  []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]