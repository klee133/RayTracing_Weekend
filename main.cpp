#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int nx = 500;
    int ny = 350;
    //float slope = ny/nx;

    ofstream myfile;
    myfile.open("/Users/admin/RayTracing_Weekend/ColorTest.ppm");

    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
         /* float r = float(i) / float(nx);
            float b = float(i) / float(nx);
            float g = float(j) / float(ny);
            ir = int(255.99*rb*2);
          */
/*
            int ir = 0;
            int ib = 0;
            int ig = 250;
            if((float)ny - (float)i*slope >= j
                    || (float)ny - (float)(i+1)*slope <= j){
                myfile << ir << " " << ig << " " << ib << "\n";
            }else{
                myfile << ir << " 0 " << ib << "\n";
            }*/
            int ir = 0;
            int ib = 0;
            int ig = 250;
            if(j == 175){
                myfile << ir << " " << ig << " " << ib << "\n";
            }else{
                myfile << ir << " 0 " << ib << "\n";
            }
        }

    }

    myfile.close();

	return 0;
}

