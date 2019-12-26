#ifndef RAYINTERSECTION_H
#define RAYINTERSECTION_H

#include "stdafx.h"
#include "Ray.h"
#include "Node.h"

namespace MX
{
  class RayIntersection
  {
  public:
    MX_API bool calcIntersection(const Ray& ray, const std::shared_ptr<Node> node);

  private:
    MX_API bool rayBox(const Ray& ray, const std::shared_ptr<Node> node);
    MX_API bool raySphere(const Ray& ray, const std::shared_ptr<Node> node);
    MX_API bool rayCylinder(const Ray& ray, const std::shared_ptr<Node> node);
    MX_API bool rayTriangle(const Ray& ray, const std::shared_ptr<Node> node);
    MX_API bool rayPlane(const Ray& ray, const std::shared_ptr<Node> node);
  };
}

#endif // RAYINTERSECTION_H