
#include "OpticNerveEstimator.hxx"

int main(int argc, char **argv ){

  //Command line parsing
  TCLAP::CmdLine cmd("Fit stem to eye ultrasound", ' ', "1");

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
  one.Fit( origImage, !noiArg.getValue(), !noiArg.getValue(), prefix);

  OpticNerveEstimator::Stem stem = one.GetStem();

  std::cout << std::endl;
  std::cout << "Estimated optic nerve width: " << 2 * stem.width << std::endl;
  std::cout << std::endl;


  return EXIT_SUCCESS;
}
