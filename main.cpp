#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include "ray.h"

using namespace std;

vec3 color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    float h = 0.5 * (unit_direction.x() + 1.0);
    vec3 hori = vec3(0.0, 0.0, 0.0);
    int first = 0;
    int second = 2;

    // Assigns values based on the x unit direction
    while(h > 0.166666){
        h -= 0.166666;
        first = (first+1)%6;
        second = (second+1)%6;
    }

    // Transitions: R->RG->G->GB->B->BR->R
    // If even, one value starts at 1.0 and the next increases from 0.0
    if(first % 2 == 0){
        hori.e[first/2] = 1;
        hori.e[second/2] = h/0.166666;
    // If odd, two values start at 1.0 and the first one decreases to 0.0
    }else{
        hori.e[first/2] = (0.166666-h)/0.166666;
        hori.e[second/2] = 1;
    }

    // Value based on the y unit direction
    // Results in colors transitioning from black to full color to white, vertically
    vec3 result;
    if(t > 0.5){
        result = hori*(1.0-t)*2;
    }else{
        result = (vec3(1.0,1.0,1.0)-hori)*(0.5-t)*2 + hori;
    }

    return result;
}

int main()
{
    int nx = 200;
    int ny = 100;

    ofstream myfile;
    myfile.open("/Users/admin/RayTracing_Weekend/ColorTest.ppm");
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    myfile.close();

    return 0;
}
