#include "computepipeline.h"


int main()
{
  URI uri("file://test.json");
  ComputePipeline pipeline(uri);

  pipeline.addAction(Action{DecodeImageAction{}});
  pipeline.addAction(Action{DecompressAction{}});
  pipeline.addAction(Action{ParseJsonAction{}});

  auto result = pipeline.execute();

  return 0;
}