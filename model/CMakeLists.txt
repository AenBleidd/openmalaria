# CMake configuration for all code in this dir and below
# Copyright © 2005-2009 Swiss Tropical Institute and Liverpool School Of Tropical Medicine
# Licence: GNU General Public Licence version 2 or later (see COPYING)

# Don't use aux_source_directory on . because we don't want to compile openMalaria.cpp in to the lib.
set (Model_CPP
  Simulator.cpp
  Population.cpp
  PopulationAgeStructure.cpp
  PopulationStats.cpp
  Parameters.cpp
  
  Host/Human.cpp
  Host/InfectionIncidenceModel.cpp
  Host/NeonatalMortality.cpp
  Host/ImportedInfections.cpp
  
  Clinical/ClinicalModel.cpp
  Clinical/CaseManagementCommon.cpp
  Clinical/EventScheduler.cpp
  Clinical/ESCaseManagement.cpp
  Clinical/CMDecisionTree.cpp
  Clinical/ImmediateOutcomes.cpp
  Clinical/Episode.cpp
  Clinical/DecisionTree5Day.cpp
  Clinical/CM5DayCommon.cpp
  
  PkPd/LSTMModel.cpp
  PkPd/Drug/LSTMDrug.cpp
  PkPd/Drug/LSTMDrugType.cpp
  PkPd/Drug/LSTMDrugAllele.cpp
  PkPd/LSTMTreatments.cpp
  
  Transmission/TransmissionModel.cpp
  Transmission/NonVectorModel.cpp
  Transmission/VectorModel.cpp
  Transmission/PerHost.cpp
  Transmission/Anopheles/AnophelesModel.cpp
  Transmission/Anopheles/EmergenceModel.cpp
  Transmission/Anopheles/MosqTransmission.cpp
  Transmission/Anopheles/FixedEmergence.cpp
  Transmission/Anopheles/SimpleMPDEmergence.cpp
  #Transmission/Anopheles/LCEmergence.cpp
  #Transmission/Anopheles/LifeCycle.cpp
  #Transmission/Anopheles/ResourceFitter.cpp
  Transmission/Anopheles/PerHost.cpp
  
  WithinHost/WHInterface.cpp
  WithinHost/WHFalciparum.cpp
  WithinHost/WHVivax.cpp
  WithinHost/CommonWithinHost.cpp
  WithinHost/DescriptiveWithinHost.cpp
  WithinHost/Genotypes.cpp
  WithinHost/Infection/Infection.cpp
  WithinHost/Infection/DescriptiveInfection.cpp
  WithinHost/Infection/DummyInfection.cpp
  WithinHost/Infection/EmpiricalInfection.cpp
  WithinHost/Infection/MolineauxInfection.cpp
  WithinHost/Infection/PennyInfection.cpp
  WithinHost/Pathogenesis/PathogenesisModel.cpp
  WithinHost/Pathogenesis/Submodels.cpp
  WithinHost/Diagnostic.cpp
  WithinHost/Treatments.cpp
  
  mon/mon.cpp
  mon/misc.cpp
  
  util/BoincWrapper.cpp
  util/timer.cpp
  util/vectors.cpp
  util/DecayFunction.cpp
  util/errors.cpp
  util/checkpoint.cpp
  util/ModelOptions.cpp
  util/CommandLine.cpp
  util/random.cpp
  util/StreamValidator.cpp
  util/AgeGroupInterpolation.cpp
  util/sampler.cpp
  util/SpeciesIndexChecker.cpp
  util/DocumentLoader.cpp
  util/misc.cpp
  
  Monitoring/Continuous.cpp
  
  interventions/InterventionManager.cpp
  interventions/ITN.cpp
  interventions/IRS.cpp
  interventions/GVI.cpp
  interventions/Vaccine.cpp
)

# Headers - only included so they show up in IDEs:
# This misses loads of headers. Fix if you care.
file (GLOB_RECURSE Model_H "${CMAKE_SOURCE_DIR}/model/*.h")


include_directories (SYSTEM
  ${XSD_INCLUDE_DIRS}
  ${XERCESC_INCLUDE_DIRS}
  ${GSL_INCLUDE_DIRS}
  ${Z_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${SPIRIT_INCLUDE_DIRS}
  ${BOINC_INCLUDE_DIRS}

  ${CMAKE_SOURCE_DIR}/contrib
  ${CMAKE_SOURCE_DIR}/contrib/FastDelegate_src
  ${CMAKE_SOURCE_DIR}/contrib/floating_point_utilities_v3
)
include_directories (
  ${CMAKE_SOURCE_DIR}/model ${CMAKE_BINARY_DIR}
)

add_library (model
  ${Model_CPP}
  ${Model_H}
)

if (MSVC)
  set_target_properties (model PROPERTIES
    LINK_FLAGS "${OM_LINK_FLAGS}"
    COMPILE_FLAGS "${OM_COMPILE_FLAGS}"
  )
endif (MSVC)
