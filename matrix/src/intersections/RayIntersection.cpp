#include "RayIntersection.h"

namespace MX
{
  bool RayIntersection::calcIntersection(const Ray& ray, const std::shared_ptr<Node> node)
  {
    // access node and see what kind of bounding box is available
    return false;
  }

  bool RayIntersection::rayBox(const Ray& ray, const std::shared_ptr<Node> node)
  {
    return false;
  }

  bool RayIntersection::raySphere(const Ray& ray, const std::shared_ptr<Node> node)
  {
    return false;
  }

  bool RayIntersection::rayCylinder(const Ray& ray, const std::shared_ptr<Node> node)
  {
    return false;
  }

  bool RayIntersection::rayTriangle(const Ray& ray, const std::shared_ptr<Node> node)
  {
    return false;
  }

  bool RayIntersection::rayPlane(const Ray& ray, const std::shared_ptr<Node> node)
  {
   
    return false;
  }
}