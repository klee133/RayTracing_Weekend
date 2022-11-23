#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    int nx = 500;
    int ny = 350;
    float startColor = 0;
    float colorRange = 255.99 - startColor;
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
            float r = float(i) / float(nx/2);
            float g = float(1) - (float(j) / float(ny));
            float b = float(1) - ((float(i)-float(nx/2)) / float(nx/2));

            int ir = 0;
            int ig = 0;
            int ib = 0;

            float lSlopeY = ny - (int)((i+1)*halfSlope);
            float lxIn;
            float lxOut;

            float rSlopeY = (int)((i+1)*halfSlope) - ny;
            float rxIn;
            float rxOut;

            // We need sections for R, RG, G, GB, B, RGB
            // Red
            if(j <= lSlopeY - blendShift){
                 ir = int(colorRange*r + startColor);
            // Red and Green
            }else if(j <= lSlopeY + blendShift){
                // Find the range of x that Red and Green will be blended in
                lxIn = float(-1)*(float(j)-blendShift-ny)/float(halfSlope);
                lxOut = float(-1)*(float(j)+blendShift-ny)/float(halfSlope);
                float lxDiff = lxIn - lxOut;
                // Divide the current color by the total x distance and multiply
                // by the distance from the current x to the x at the start of blend
                float r2 = r / (lxDiff) * (i - lxOut);
                float g2 = g / (lxDiff) * (lxIn - i);
                // Adding a small number to ensure we are not accidentally going negative
                r += float(0.01);
                g += float(0.01);
                // Subtracts an increasingly larger amount from color as it gets
                // closer to the end
                r -= r2;
                g -= g2;
                ir = int(colorRange*r + startColor);
                ig = int(colorRange*g + startColor);
            // Green
            }else if(j >= rSlopeY + blendShift){
                ig = int(colorRange*g + startColor);
            }

            // Green, Blue
            // Separated if statement so that it can check for the section that
            // intersects with the Red/Green blended section
            if((j <= rSlopeY + blendShift) && (j >= rSlopeY - blendShift)){
                // Find the range of x that Green and Blue will be blended in
                rxIn = (float(j)+blendShift+ny)/float(halfSlope);
                rxOut = (float(j)-blendShift+ny)/float(halfSlope);
                float rxDiff = rxOut - rxIn;
                // Divide the current color by the total x distance and multiply
                // by the distance from the current x to the x at the start of blend
                float g2 = g / (rxDiff) * (rxOut - i);
                float b2 = b / (rxDiff) * (i - rxIn);
                // Adding a small number to ensure we are not accidentally going negative
                g += float(0.01);
                b += float(0.01);
                // Subtracts an increasingly larger amount from color as it gets
                // closer to the end
                g -= g2;
                b -= b2;
                ig = int(colorRange*g + startColor);
                ib = int(colorRange*b + startColor);
            // Blue
            }else if(j <= rSlopeY - blendShift){
                ib = int(colorRange*b + startColor);
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
                float g2 = g / dist * (crossYIn - j);

                // Adding a small number to ensure we are not accidentally going negative
                g += float(0.01);
                // Subtracts an increasingly larger amount from color as it gets
                // closer to the end
                g -= g2;
                ig = int(colorRange*g + startColor);
            }
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    myfile.close();

	return 0;
}

/*
 *
 */
