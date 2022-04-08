#pragma once

#include "BaseVisitable.h"
#include "node.h"
#include "State.h"

class NodeVisitor :
  public BaseVisitor,
  public Visitor<class AbstractNode>,
  public Visitor<class AbstractIntersectionNode>,
  public Visitor<class AbstractPolyNode>,
  public Visitor<class ListNode>,
  public Visitor<class GroupNode>,
  public Visitor<class RootNode>,
  public Visitor<class LeafNode>,
  public Visitor<class CgalAdvNode>,
  public Visitor<class CsgOpNode>,
  public Visitor<class LinearExtrudeNode>,
  public Visitor<class RotateExtrudeNode>,
  public Visitor<class RoofNode>,
  public Visitor<class ImportNode>,
  public Visitor<class TextNode>,
  public Visitor<class ProjectionNode>,
  public Visitor<class RenderNode>,
  public Visitor<class SurfaceNode>,
  public Visitor<class TransformNode>,
  public Visitor<class ColorNode>,
  public Visitor<class OffsetNode>
{
public:
  NodeVisitor() {}
  ~NodeVisitor() {}

  Response traverse(const AbstractNode& node, const class State& state = NodeVisitor::nullstate);

  Response visit(class State& state, const class AbstractNode& node) override = 0;
  Response visit(class State& state, const class AbstractIntersectionNode& node) override {
      if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class AbstractPolyNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class ListNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }

  Response visit(class State& state, const class GroupNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const RootNode& node) override {
    if (!abortFlag) return visit(state, (const class GroupNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class LeafNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractPolyNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class CgalAdvNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class CsgOpNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class LinearExtrudeNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractPolyNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class RotateExtrudeNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractPolyNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class RoofNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractPolyNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class ImportNode& node) override {
    if (!abortFlag) return visit(state, (const class LeafNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class TextNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractPolyNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class ProjectionNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractPolyNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class RenderNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class SurfaceNode& node) override {
    if (!abortFlag) return visit(state, (const class LeafNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class TransformNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class ColorNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractNode&)node);
      else return Response::AbortTraversal;
  }
  Response visit(class State& state, const class OffsetNode& node) override {
    if (!abortFlag) return visit(state, (const class AbstractPolyNode&)node);
      else return Response::AbortTraversal;
  }
  // Add visit() methods for new visitable subtypes of AbstractNode here

private:
  static State nullstate;
};
