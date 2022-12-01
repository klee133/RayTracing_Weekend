#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include "vec3.h"

#define PI 3.14159265

using namespace std;

int main()
{
    /* 6 sections:
     *      1. Red->Yellow:     255 +0 0    ---> 255 255 0
     *      2. Yellow->Green:   -255 255 0  ---> 0 255 0
     *      3. Green->Cyan:     0 255 +0    ---> 0 255 255
     *      4. Cyan->Blue:      0 -255 255  ---> 0 0 255
     *      5. Blue->Magenta:   +0 0 255    ---> 255 0 255
     *      6. Magenta->Red:    255 0 -255  ---> 255 0 0
     *
     *  Divide 180 into 6 sections = 30 degrees each
     *  (Current degree-section start degree) / 30 degree = % de/increase
     *
     *  White center: Start increasing other non-255 values towards the middle
     *  Multiply by distance. Find shorter of two: x/2 or y
     *          Shorter will be the radius of the circle- at radius, min,
     *          at center, max brightness
     */

    int nx = 500;
    int ny = 350;
    float radius;
    double degree;
    int changeColor;


    if(nx/2 <= ny){
        radius = nx/2;
    }else{
        radius = ny;
    }

    ofstream myfile;
    myfile.open("/Users/admin/RayTracing_Weekend/ColorTest.ppm");
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(float(0), float(0), float(0));
            int sign = 1;
            int ele1 = 0;
            int ele2 = 2;

            // Finds degree of angle from bottom-center to current point
            if(i <= nx/2){
                degree = atan2(j, (nx/2 - i + 0.000001)) * 180 / PI;
            }else{
                degree = 180 - (atan2(j, (i - nx/2 + 0.000001)) * 180 / PI);
            }

            // Sets main color used to max and changeColor and sign to certain numbers
            // depending on how high the degree is
            while(degree >= 30.0){
                degree = degree - 30.0;
                ele1++;
                ele1 %= 6;
                ele2++;
                ele2 %= 6;
                sign = sign * -1;
            }
            ele1 = int(ele1 / 2);
            ele2 = int(ele2 / 2);

            // Converting degree to a percent of the current RGB section
            degree = degree / 30.0;

            // Increases the current changeColor's intensity depending on the angle
            // from bottom-center to current point
            if(sign == 1){
                col[ele1] = 1.0;
                changeColor = ele2;
                col[changeColor] += degree;
            // Decreases the current changeColor's intensity depending on the angle
            // from bottom-center to current point
            }else{
                col[ele1] = 1.0;
                col[ele2] = 1.0;
                changeColor = ele1;
                col[changeColor] -= degree;
            }

            // Makes values increasingly white towards the bottom-center
            float dist = sqrt(pow(j, 2) + pow(i - nx/2, 2));
            if(dist > radius){
                dist = radius;
            }
            float distPercent = 1.0 - (dist / radius);
            for(int cnt = 0; cnt < 3; cnt++){
                if(col[cnt] < 1){
                    col[cnt] += ((1.0 - col[cnt]) * distPercent);
                }
            }

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    myfile.close();

    return 0;
}



/*
    int nx = 200;
    int ny = 100;

    ofstream myfile;
    myfile.open("/Users/admin/RayTracing_Weekend/ColorTest.ppm");
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }

*/
