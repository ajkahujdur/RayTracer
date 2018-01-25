#ifndef PIRAMIDA_H
#define PIRAMIDA_H

class piramida : public hitable{
public:
    piramida(){}
    piramida(const vec3& v1,const vec3& v2,const vec3& v3,const vec3& v4, material *m);
    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec)const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const{
        //box = aabb(vec3(x0,y0,k-0.0001), vec3(x1,y1,k+0.0001));
        return true;
    }
    vec3 v1,v2,v3,v4;
    material *mat;
    hitable *list_ptr;
};

piramida::piramida(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& v4, material *m){
    hitable **list = new hitable*[4];
    list[0] = new trougao(v1, v2, v4, m);
    list[1] = new trougao(v2, v3, v4, m);
    list[2] = new trougao(v1, v3, v4, m);
    list[3] = new trougao(v1, v2, v3, m);
    //list[4] = new xz_rect(v0.x(), v1.x(), v2.z(), v3.z(), v4.y(), ptr);
    list_ptr = new hitable_list(list, 4);
}

bool piramida::hit(const ray& r, float t0, float t1, hit_record& rec)const{
    return list_ptr->hit(r,t0,t1,rec);
}





#endif // PIRAMIDA_H
