############################################################################
#
# Library:   UltrasoundOpticNerveEstimation
#
# Copyright 2010 Kitware Inc. 28 Corporate Drive,
# Clifton Park, NY, 12065, USA.
#
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
############################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

PROJECT(UltrasoundIntracranialPressure)

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE} )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )

#FIND_PACKAGE(SlicerExecutionModel REQUIRED)
#$INCLUDE(${SlicerExecutionModel_USE_FILE})


#ADD_EXECUTABLE(EllipseAffine EllipseAffine.cxx)
#TARGET_LINK_LIBRARIES (EllipseAffine ${ITK_LIBRARIES} )

#ADD_EXECUTABLE(FitStem FitStem.cxx)
#TARGET_LINK_LIBRARIES (FitStem ${ITK_LIBRARIES} )

ADD_EXECUTABLE(EstimateEyeAndStem EstimateEyeAndStem.cxx OpticNerveEstimator.cxx)
TARGET_LINK_LIBRARIES (EstimateEyeAndStem ${ITK_LIBRARIES} )

