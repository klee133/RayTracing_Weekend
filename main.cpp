#include <iostream>
#include <fstream>
#include <cmath>
#include "vec3.h"

using namespace std;

int main()
{
    int nx = 500;
    int ny = 350;
    float startColor = 100;
    float halfSlope = (float)ny/((float)nx / 2);
    // Amount of shift from halfslope for blended values
    float blendShift = (halfSlope) * (float(nx / 12));
    // Inner left slope equation = Inner right slope equation
    // ny - (int)((i+1)*halfSlope) + blendShift = (int)((i+1)*halfSlope) - ny + blendShift
    // Simplified and set to x
    // ny/halfSlope = (i+1)
    // Plug in x to one of the equations to get y
    float crossXInOut = ny/halfSlope;
    float crossYIn = ny - (int)(crossXInOut*halfSlope) + blendShift;

    ofstream myfile;
    myfile.open("/Users/admin/RayTracing_Weekend/ColorTest.ppm");
    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    for(int j = ny; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            // Initalize some values
            /*float r = float(i) / float(nx/2);
            float g = float(1) - (float(j) / float(ny));
            float b = float(1) - ((float(i)-float(nx/2)) / float(nx/2));*/
            vec3 col(
                (float(i)+startColor) / (float(nx/2)+255.99),
                float(1) - ((float(j) + startColor) / (float(ny) + 255.99)),
                float(1) - ((float(i)-float(nx/2) + startColor) / (float(nx/2) + 255.99))
                );

            int ir = 0;
            int ig = 0;
            int ib = 0;

            float lSlopeY = ny - (int)((i+1)*halfSlope);
            // Find the range of x that Red and Green will be blended in
            float lxIn = float(-1)*(float(j)-blendShift-ny)/float(halfSlope);
            float lxOut = float(-1)*(float(j)+blendShift-ny)/float(halfSlope);
            float lxDiff = lxIn - lxOut;

            float rSlopeY = (int)((i+1)*halfSlope) - ny;
            // Find the range of x that Green and Blue will be blended in
            float rxIn = (float(j)+blendShift+ny)/float(halfSlope);
            float rxOut = (float(j)-blendShift+ny)/float(halfSlope);
            float rxDiff = rxOut - rxIn;

            // We need sections for R, RG, G, GB, B, RGB
            // Red
            if(j <= lSlopeY - blendShift){
                 ir = int(255.99*col[0]);
            // Red and Green
            }else if(j <= lSlopeY + blendShift){
                // Divide the current color by the total x distance and multiply
                // by the distance from the current x to the x at the start of blend
                float r2 = col[0] / (lxDiff) * (i - lxOut);
                float g2 = col[1] / (lxDiff) * (lxIn - i);
                // Adding a small number to ensure we are not accidentally going negative
                col[0] += float(0.01);
                col[1] += float(0.01);
                // Subtracts an increasingly larger amount from color as it gets
                // closer to the end
                col[0] -= r2;
                col[1] -= g2;
                ir = int(255.99*col[0]);
                ig = int(255.99*col[1]);
            // Green
            }else if(j >= rSlopeY + blendShift){
                ig = int(255.99*col[1]);
            }

            // Green, Blue
            // Separated if statement so that it can check for the section that
            // intersects with the Red/Green blended section
            if((j <= rSlopeY + blendShift) && (j >= rSlopeY - blendShift)){
                // Divide the current color by the total x distance and multiply
                // by the distance from the current x to the x at the start of blend
                float g2 = col[1] / (rxDiff) * (rxOut - i);
                float b2 = col[2] / (rxDiff) * (i - rxIn);
                // Adding a small number to ensure we are not accidentally going negative
                col[1] += float(0.01);
                col[2] += float(0.01);
                // Subtracts an increasingly larger amount from color as it gets
                // closer to the end
                col[1] -= g2;
                col[2] -= b2;
                ig = int(255.99*col[1]);
                ib = int(255.99*col[2]);
            // Blue
            }else if(j <= rSlopeY - blendShift){
                ib = int(255.99*col[2]);
            }

            // Red, Green, Blue
            // Blends Green around the intersection point of the inner lines
            // Red and Blue have already been blended properly by the
            // Red/Green and Green/Blue if statements
            if((j >= lSlopeY - blendShift) && (j >= rSlopeY - blendShift)
                    && j <= crossYIn ){
                float endY;
                // Finds which outer lines' y to base the end of the blended
                // green on
                if(i < nx/2){
                    endY = lSlopeY - blendShift;
                }else{
                    endY = rSlopeY - blendShift;
                }
                // Total vertical distance between the inner lines' intersection
                // and the end of blended green, at current x
                float dist = crossYIn - endY;
                // Divide by total y and multiply by current y
                float g2 = col[1] / dist * (crossYIn - j);

                // Adding a small number to ensure we are not accidentally going negative
                col[1] += float(0.01);
                // Subtracts an increasingly larger amount from color as it gets
                // closer to the end
                col[1] -= g2;
                ig = int(255.99*col[1]);
            }
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
