#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int nx = 500;
    int ny = 350;
    float halfSlope = (float)ny/((float)nx / 2);

    //cout << slope << endl;

    ofstream myfile;
    myfile.open("/Users/admin/RayTracing_Weekend/ColorTest.ppm");

    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    int ir = 250;
    int ig = 250;
    int ib = 250;

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
         /* float r = float(i) / float(nx);
          * float g = float(j) / float(ny);
            float b = float(i) / float(nx);
            ir = int(255.99*rb*2);
          */


            if(i < nx / 2){
                if(j >= ny - (int)((i+1)*halfSlope)){
                    myfile << "0 " << ig << " 0\n";
                }else{
                    myfile << ir << " 0 " << "0\n";
                }
            }else{
                if(j >= ((int)((i+1)*halfSlope)) - ny){
                    myfile << "0 " << ig << " 0\n";
                }else{
                    myfile << "0 " << "0 " << ib << "\n";

                }

            }

        }

    }
    for(int i = 0; i < nx-1; i++){
        myfile << ir << " 0 " << ib << "\n";
    }
    myfile << ir << " " << ig << " " << ib << "\n";


//&& (float)j >= (float)ny - (float)(i+1)*slope
    myfile.close();

	return 0;
}

/*
 *
 */
