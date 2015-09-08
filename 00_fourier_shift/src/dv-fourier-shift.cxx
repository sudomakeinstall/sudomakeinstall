#include <cstdlib>
#include <complex>

#include <itkImageFileReader.h>
#include <itkImageRegionIteratorWithIndex.h>
#include <itkForwardFFTImageFilter.h>
#include <itkComplexToModulusImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkShiftScaleImageFilter.h>
#include <itkLogImageFilter.h>
#include <itkImageFileWriter.h>

const unsigned int Dimension = 2;
typedef double                     TRealPixel;
typedef std::complex< TRealPixel > TComplexPixel;
typedef unsigned short             TIOPixel;

typedef itk::Image< TRealPixel, Dimension >    TRealImage;
typedef itk::Image< TComplexPixel, Dimension > TComplexImage;
typedef itk::Image< TIOPixel, Dimension >      TIOImage;

typedef itk::ImageFileReader< TRealImage > TReader;
typedef itk::ForwardFFTImageFilter< TRealImage > TFFT;
typedef itk::ImageRegionIteratorWithIndex< TRealImage > TIterator;
typedef itk::ComplexToModulusImageFilter< TComplexImage, TRealImage > TComToMod;
typedef itk::ShiftScaleImageFilter< TRealImage, TRealImage > TShift;
typedef itk::RescaleIntensityImageFilter< TRealImage, TIOImage > TRescale;
typedef itk::ImageFileWriter< TIOImage > TWriter;
typedef itk::LogImageFilter< TRealImage, TRealImage > TLog;

int main()
{

  auto reader = TReader::New();
  reader->SetFileName( "../data/wires.png" );

  auto fft = TFFT::New();
  fft->SetInput( reader->GetOutput() );

  auto modulus = TComToMod::New();
  modulus->SetInput( fft->GetOutput() );

  auto shift = TShift::New();
  shift->SetInput( modulus->GetOutput() );
  shift->SetShift( 1.0 );

  auto log = TLog::New();
  log->SetInput( shift->GetOutput() );

  auto rescale = TRescale::New();
  rescale->SetInput( log->GetOutput() );

  auto writer = TWriter::New();
  writer->SetInput( rescale->GetOutput() );
  writer->SetFileName( "../data/spectrum.png" );
  writer->Update();

  // Checkerboard trick
  auto cameraman = reader->GetOutput();
  cameraman->DisconnectPipeline();

  TIterator it(cameraman, cameraman->GetLargestPossibleRegion() );

  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    {
    unsigned int indSum = 0;
    for (unsigned int i = 0; i < Dimension; ++i)
      indSum += it.GetIndex()[i];
    if (0 == indSum % 2) it.Value() *= -1;
    }

  fft->SetInput( cameraman );
  writer->SetFileName( "../data/shifted_spectrum.png" );
  writer->Update();  

  // Checkerboard spectrum
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    {
    unsigned int indSum = 0;
    for (unsigned int i = 0; i < Dimension; ++i)
      indSum += it.GetIndex()[i];
    it.Set(0 == indSum % 2 ? -1 : 1);
    }

  fft->SetInput( cameraman );
  rescale->SetInput( modulus->GetOutput() );
  writer->SetFileName( "../data/checkerboard_spectrum.png" );
  writer->Update();

  // Checkerboard
  rescale->SetInput( cameraman );
  writer->SetFileName( "../data/checkerboard.png" );
  writer->Update();

  return EXIT_SUCCESS;

}

