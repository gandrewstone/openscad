#pragma once

#include <iostream>
#include <atomic>

// FIXME: Default constructor Response()
enum class Response {ContinueTraversal, AbortTraversal, PruneTraversal};

class BaseVisitor
{
protected:
  volatile std::atomic_bool abortFlag;
public:
  BaseVisitor():abortFlag(false) {}
  virtual ~BaseVisitor() {}

  void resetAbort(void) { abortFlag = false; }
  void abort(void) { abortFlag = true; }
};

template <class T>
class Visitor
{
public:
  virtual Response visit(class State& state, const T&) = 0;
};

class BaseVisitable
{
public:
  virtual ~BaseVisitable() {}
  virtual Response accept(class State&, BaseVisitor&) const = 0;
protected:
  template <class T>
  static Response acceptImpl(class State& state, const T& node, BaseVisitor& visitor) {
    if (Visitor<T> *p = dynamic_cast<Visitor<T> *>(&visitor)) {
      return p->visit(state, node);
    }
    // FIXME: If we want to allow for missing nodes in visitors, we need
    // to handle it here, e.g. by calling some handler.
    // See e.g. page 225 of Alexandrescu's "Modern C++ Design"
    return Response::AbortTraversal;
  }
};

#define VISITABLE() \
  Response accept(class State& state, BaseVisitor& visitor) const override { \
    return acceptImpl(state, *this, visitor); \
  }
