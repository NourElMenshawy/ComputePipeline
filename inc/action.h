#ifndef ACTION_H
#define ACTION_H

#include "item.h"
#include <concepts>
#include <memory>
#include <functional>
#include "uri.h"

/*
  Action Concept:
  - A type T is an action if it has the following methods:
    - bool canProcess(const Item &item) const
    - std::shared_ptr<Item> process(const Item &item) const
*/
template <typename T>
concept ActionConcept = requires(T action, const Item &item) {
  { action.canProcess(item) } -> std::same_as<bool>;
  { action.process(item) } -> std::same_as<std::shared_ptr<Item>>;
};

/*
  Action class:
  - Represents an action that can be performed on an item.
  - The action is stored as a shared pointer to a polymorphic base class.
  - The action is type-erased, allowing different types of actions to be stored and executed
*/
class Action
{
public:
  /*
    - Constructs an action from a type that satisfies the ActionConcept.
      @param action: The action to store.
  */
  template <ActionConcept T>
  explicit Action(T action) : action_(std::make_shared<ActionModel<T>>(std::move(action))) {}

  /*
  - Checks if the action can process the given item.
    @param item: The item to process.
  */
  bool canProcess(const Item &item) const
  {
    return action_->canProcess(item);
  }

  /*
    - Processes the given item using the action.
      @param item: The item to process.
  */
  std::shared_ptr<Item> process(const Item &item) const
  {
    return action_->process(item);
  }

private:
  /*
    - Base class for type-erased actions.
  */
  struct ActionBase
  {
    virtual bool canProcess(const Item &item) const = 0;
    virtual std::shared_ptr<Item> process(const Item &item) const = 0;
    virtual ~ActionBase() = default;
  };

  /*
    - Model class that stores the actual action.
      @tparam U: The type of the action.
  */
  template <typename U>
  struct ActionModel : public ActionBase
  {
    ActionModel(U action) : action_(action) {}

    bool canProcess(const Item &item) const override
    {
      return action_.canProcess(item);
    }

    std::shared_ptr<Item> process(const Item &item) const override
    {
      return action_.process(item);
    }

    // The actual action
    U action_;
  };

  std::shared_ptr<ActionBase> action_;
};

// Note: Those classes should be defined in separate files in case of full implementation
class DecodeImageAction
{
public:
  bool canProcess(const Item &item) const { return false; };
  std::shared_ptr<Item> process(const Item &item) const { return nullptr; };
};

class DecompressAction
{
public:
  bool canProcess(const Item &item) const { return false; };
  std::shared_ptr<Item> process(const Item &item) const { return nullptr; };
};

class ParseJsonAction
{
public:
  bool canProcess(const Item &item) const { return false; };
  std::shared_ptr<Item> process(const Item &item) const { return nullptr; };
};

#endif