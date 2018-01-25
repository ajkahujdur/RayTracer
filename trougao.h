#ifndef TROUGAO_H
#define TROUGAO_H

class trougao : public hitable{
public:
    trougao(){}
    trougao(vec3 _v1,vec3 _v2, vec3 _v3, material *m):v1(_v1),v2(_v2),v3(_v3),mat(m){};
    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec)const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const{
        return true;
    }
    vec3 v1,v2,v3;
    material *mat;
};



bool trougao::hit(const ray& r, float t0, float t1, hit_record& rec)const{

    vec3 ivicaA = v2 - v1;
    vec3 ivicaB = v3 - v2;
    vec3 ivicaC = v1 - v3;

    vec3 normala = cross((v2-v1),(v3-v1));
    normala.make_unit_vector();
    float D = dot(normala, v1);

    float t = - (dot(normala, r.origin()) + D) / dot(normala, r.direction());

    if(t < t0 || t > t1)return false;
    vec3 p = r.origin() + t*r.direction();

    vec3 c1 = p - v1;
    vec3 c2 = p - v2;
    vec3 c3 = p - v3;

    if (!(dot(normala, cross(ivicaA, c1)) > 0 && dot(normala, cross(ivicaB, c2)) > 0 && dot(normala, cross(ivicaC, c3)) > 0)) return false;

    rec.t = t;
    rec.mat_ptr = mat;
    rec.p = r.point_at_parameter(t);
    rec.normal = normala;
    return true;

}




#endif // TROUGAO_H
