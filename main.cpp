#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "util.h"
#include "ray.h"
#include "constant_texture.h"
#include "diffuse_light.h"
#include "xy_rect.h"
#include "flip_normals.h"
#include "box.h"
#include "trougao.h"
#include "rotate_y.h"
#include "piramida.h"
#include "image_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
             return emitted + attenuation*color(scattered, world, depth+1);
        }
        else {
            return emitted;
        }
    }
    else {
        return vec3(0,0,0);
    }
}



hitable *scene(){
    hitable **list = new hitable*[2000];
    int i = 0;

    material *light  = new diffuse_light(new constant_texture(vec3(7,7,7)));
    material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));

    list[i++] = new xz_rect(123,423,147,412,554,light);
    list[i++] = new piramida(vec3(550, 70, 30), vec3(400, 70, 30), vec3(475, 70, 180), vec3(475, 155, 105), new metal(vec3(0.8,0.8,0.9),10.0));
    list[i++] = new xz_rect(-150,650,-100,600,0,new lambertian(new constant_texture(vec3(0.48,0.83,0.53))));
    list[i++] = new sphere(vec3(285,270,300),50,new dielectric(1.5));
    list[i++] = new sphere(vec3(0,460,145), 50,new metal(vec3(0.8,0.8,0.9),10.0));

    int nx,ny,nn;
    unsigned char*tex_data = stbi_load("slika3.jpg",&nx,&ny,&nn,0);
    material *mat = new lambertian(new image_texture(tex_data,nx,ny));
    list[i++] = new sphere(vec3(450,400,400),100,mat);

    list[i++] = new box(vec3(200,0,250),vec3(300,200,350),new lambertian(new constant_texture(vec3(0.1,0.6,0.6))));

  
    list[i++] = new trougao(vec3(50,300,100),vec3(200,300,100),vec3(125,400,100), new lambertian(new constant_texture(vec3(0.1,0.1,0.9))));

    for(int j = 0; j < 20; j++){
        list[i++] = new rotate_y(new box(vec3(100,0,150),vec3(150,50,200),new lambertian(new constant_texture(vec3(0.1,0.6,0.6)))),j*10);
    }

    for(int j = 0; j < 1000; j++){
        list[i++] = new sphere(vec3(165*dis2(gen),165*dis2(gen),165*dis2(gen)),10,white);
    }
    return new hitable_list(list,i);
}


using namespace std;

int main() {
    int NX = 1600;
    int NY = 800;
    int NS = 100;

    ofstream fout;
    fout.open("konacna slika2.ppm");
    fout << "P3" <<endl;
    fout << NX << " " << NY << endl;
    fout << "255" << endl;

    hitable *list[5];
    float R = cos(3.14/4);
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(new constant_texture(vec3(0.1, 0.2, 0.5))));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(new constant_texture(vec3(0.8, 0.8, 0.0))));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));
    hitable *world = new hitable_list(list,5);
    world = scene();

    vec3 lookfrom(278,278,-800);
    vec3 lookat(278,278,0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 40.0;

    camera cam(lookfrom, lookat, vec3(0,1,0),vfov, float(NX)/float(NY), aperture, dist_to_focus);

    for (int j = NY-1; j >= 0; j--) {
        for (int i = 0; i < NX; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < NS; s++) {
                float u = float(i + dis1(gen)) / float(NX - 1);
                float v = float(j + dis1(gen)) / float(NY - 1);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world,0);
            }
            col /= float(NS);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            fout << ir << " " << ig << " " << ib << " ";
        }
        fout << endl;
    }
    return 0;
}




