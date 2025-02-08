#ifndef COMPUTEPIPELINE_H
#define COMPUTEPIPELINE_H

#include "uri.h"
#include "item.h"
#include "action.h"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

/*
  ComputePipeline class:
  - Represents a pipeline of actions to be executed on an item.
  - The pipeline is responsible for loading the item and executing the actions in sequence until no action be processed.
*/
class ComputePipeline
{
public:
  /*
    - Constructs a compute pipeline with the given URI.
      @param uri: The URI of the item to process.
  */
  ComputePipeline(URI uri) : uri_(std::move(uri)) {};

  /*
    - Adds an action to the pipeline.
      @param action: The action to add.
  */
  void addAction(Action action) { actions_.push_back(std::move(action)); };

  /*
    - Executes the pipeline on the item.
      @return The final item after processing.
  */
  std::shared_ptr<Item> execute()
  {
    std::shared_ptr<Item> item = loadItem();
    while (true)
    {
      bool isDone = false;
      for (const auto &action : actions_)
      {
        if (action.canProcess(*item))
        {
          item = action.process(*item);
          isDone = true;
          break;
        }
      }
      if (!isDone)
        break;
    }
    return item;
  };

  /*
    - Loads the item based on the URI.
      @return The loaded item.
  */
  std::shared_ptr<Item> loadItem() const { return std::make_shared<Item>(nullptr, "json"); };

private:
  std::vector<Action> actions_;
  URI uri_;
};

#endif // COMPUTEPIPELINE_H