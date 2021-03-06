
/*=========================================================================

Library:   UltrasoundOpticNerveEstimation

Copyright 2010 Kitware Inc. 28 Corporate Drive,
Clifton Park, NY, 12065, USA.

All rights reserved.

Licensed under the Apache License, Version 2.0 ( the "License" );
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=========================================================================*/
#include <tclap/CmdLine.h>
#include "OpticNerveEstimator.hxx"

int main(int argc, char **argv ){

  //Command line parsing
  TCLAP::CmdLine cmd("Fit nerve to eye ultrasound", ' ', "1");

  TCLAP::ValueArg<std::string> imageArg("i","image","Ultrasound input image", true, "",
      "filename");
  cmd.add(imageArg);

  TCLAP::ValueArg<std::string> prefixArg("p","prefix","Prefix for storing output images", true, "",
      "filename");
  cmd.add(prefixArg);

  TCLAP::SwitchArg noiArg("","noimage","Do not output overlay image" );
  cmd.add(noiArg);

  try{
    cmd.parse( argc, argv );
  }
  catch (TCLAP::ArgException &e){
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return -1;
  }

  std::string prefix = prefixArg.getValue();

  ////
  //1. Read and preprocess the ultrasound image
  ////
  OpticNerveEstimator::ImageType::Pointer origImage = ImageIO<OpticNerveEstimator::ImageType>::ReadImage( imageArg.getValue() );

  OpticNerveEstimator one;
  OpticNerveEstimator::Status status = one.Fit( origImage, !noiArg.getValue(), prefix);

  if(status == OpticNerveEstimator::ESTIMATION_SUCCESS){
    if(!noiArg.getValue() ){
      OpticNerveEstimator::RGBImageType::Pointer overlayImage = one.GetOverlay(origImage);
#ifdef DEBUG_IMAGES
  ImageIO<OpticNerveEstimator::RGBImageType>::WriteImage( overlayImage, one.catStrings(prefix, "-overlay.png") );
#endif
    }
    OpticNerveEstimator::Nerve nerve = one.GetNerve();

    std::cout << std::endl;
    std::cout << "Estimated optic nerve width: " << 2 * nerve.width << std::endl;
    std::cout << std::endl;
  }
  else{
    std::cout << std::endl;
    std::cout << "Estimated optic nerve width: fail" << std::endl;
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
