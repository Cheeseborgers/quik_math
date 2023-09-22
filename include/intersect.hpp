#ifndef QUIKMAFF_INTERSECT_HPP
#define QUIKMAFF_INTERSECT_HPP

#include "vec3.hpp"

namespace qm {

template <typename T>
bool sphereSphereIntersect(const Vec3 &center1, T radius1, const Vec3 &center2, T radius2)
{
    // Calculate the distance between the centers of the spheres
    T distance = distance(center1, center2);

    // Check if the distance is less than the sum of the radii
    return distance <= (radius1 + radius2);
}

template <typename T>
bool aabbIntersect(const Vec3 &min1, const Vec3 &max1, const Vec3 &min2, const Vec3 &max2)
{
    // Check for overlap along each axis
    bool xOverlap = (min1.x <= max2.x) && (max1.x >= min2.x);
    bool yOverlap = (min1.y <= max2.y) && (max1.y >= min2.y);
    bool zOverlap = (min1.z <= max2.z) && (max1.z >= min2.z);

    // If there's overlap along all axes, there's an intersection
    return xOverlap && yOverlap && zOverlap;
}

template <typename T>
bool raySphereIntersect(const Vec3 &rayOrigin, const Vec3 &rayDirection, const Vec3 &sphereCenter,
                        T sphereRadius)
{
    // Calculate the vector from the ray origin to the sphere center
    Vec3 rayToSphere = sphereCenter - rayOrigin;

    // Calculate the projection of rayToSphere onto the ray direction
    T t = dot(rayToSphere, rayDirection);

    // Calculate the closest point on the ray to the sphere center
    Vec3 closestPoint = rayOrigin + t * rayDirection;

    // Calculate the distance between the closest point and the sphere center
    T distance = distance(sphereCenter, closestPoint);

    // Check if the distance is less than or equal to the sphere radius
    return distance <= sphereRadius;
}

} // namespace qm

#endif // QUIKMAFF_INTERSECT_HPP