#ifndef URI_H
#define URI_H

#include <string>

/*
  URI class:
  - Represents a Uniform Resource Identifier (URI).
  - The URI can be of different types, such as file, http, https, or bundle.
*/
class URI
{
public:
  enum class Type
  {
    Unknown,
    File,
    Http,
    Https,
    Bundle
  };

  /*
    - Constructs a URI with the given URI string.
      @param uri: The URI string.
  */
  URI(const std::string &uri) : uri_(std::move(uri))
  {
    if (uri.rfind("file://", 0) == 0)
    {
      type_ = Type::File;
    }
    else if (uri.rfind("http://", 0) == 0)
    {
      type_ = Type::Http;
    }
    else if (uri.rfind("https://", 0) == 0)
    {
      type_ = Type::Https;
    }
    else if (uri.rfind("bundle://", 0) == 0)
    {
      type_ = Type::Bundle;
    }
    else
    {
      type_ = Type::Unknown;
    }
  }
  /*
    - Gets the type of the URI.
      @return The type of the URI.
  */
  Type getType() const { return type_; }

  /*
    - Gets the URI string.
      @return The URI string.
  */
  std::string getUri() const { return uri_; }

private:
  Type type_;
  std::string uri_;
};

#endif