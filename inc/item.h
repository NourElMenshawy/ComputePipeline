#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <any>
#include <memory>

/*
  Item class:
  - Represents an item that can be processed by actions in a compute pipeline.
  - The item contains data and metadata.
  - The type of the item is determined by the metadata.
*/
class Item
{
public:
  /*
    Item type:
    - Represents the type of an item.
    - The type is determined by the metadata of the item.
  */
  enum class Type
  {
    Unknown,
    Images,
    Compressed,
    Json,
    Object
  };

  /*
    - Constructs an item with the given data and metadata.
      @param data: The data of the item.
      @param metadata: The metadata of the item.
  */
  explicit Item(std::any data, std::string metadata)
      : data_(std::move(data)), metadata_(std::move(metadata)) {}

  /*
    - Gets the type of the item.
      @return The type of the item.
  */
  Type getType() const
  {

    if (metadata_.rfind("image", 0) == 0)
    {
      return Type::Images;
    }
    else if (metadata_.rfind("json", 0) == 0)
    {
      return Type::Json;
    }
    else if (metadata_.rfind("zip", 0) == 0)
    {
      return Type::Compressed;
    }
    else if (metadata_.rfind("object", 0) == 0)
    {
      return Type::Object;
    }
    else
    {
      return Type::Unknown;
    }
  }
  /*
    - Gets the data of the item.
      @return The data of the item.
  */
  std::any getData() const { return data_; }

  /*
    - Gets the metadata of the item.
      @return The metadata of the item.
  */
  std::string getMetadata() const { return metadata_; }

private:
  std::any data_;
  std::string metadata_;
};

#endif