#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int nx = 500;
    int ny = 350;
    float slope = (float)ny/(float)nx;

    cout << slope << endl;

    ofstream myfile;
    myfile.open("/Users/admin/RayTracing_Weekend/ColorTest.ppm");

    myfile << "P3\n" << nx << " " << ny << "\n255\n";

    int ir = 0;
    int ig = 250;
    int ib = 0;

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
         /* float r = float(i) / float(nx);
          * float g = float(j) / float(ny);
            float b = float(i) / float(nx);
            ir = int(255.99*rb*2);
          */



            if(j == (int)(i*slope)
                    || j == (int)((i+1)*slope)){
                myfile << ir << " " << ig << " " << ib << "\n";
                //cout << "IF --- j: " << j << ", i: " << i << ", (int)(i*slope) = "
                  //   << (int)(i*slope) << "\t(int)((i+1)*slope) = " <<
                    //    (int)((i+1)*slope) << endl;
            }else{
                myfile << ir << " 0 " << ib << "\n";
                //cout << "--- ELSE --- j: " << j << ", i: " << i << ", (int)(i*slope) = "
                  //   << (int)(i*slope) << "\t(int)((i+1)*slope) = " <<
                    //    (int)((i+1)*slope) << endl;
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
