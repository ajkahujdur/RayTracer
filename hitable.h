#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include "aabb.h"

class material;

void get_sphere_uv(const vec3& p, float& u, float& v){
    float phi = atan2(p.z(),p.x());
    float theta = asin(p.y());
    u = 1 - (phi + 3.4)/(2*3.14);
    v = (theta + 3.14/2)/3.14;
}

struct hit_record
{
    float t, u, v;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable  {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
        virtual bool bounding_box(float t0, float t1, aabb& box)const = 0;
};

#endif

