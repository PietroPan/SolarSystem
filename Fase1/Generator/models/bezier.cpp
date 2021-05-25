#include "bezier.h"

vector<vector<float>> preCalculate(char coord,vector<int> &patch,vector<Point> &points){
    float ri[4][4]={0};
    vector<vector<float>> r;
    for (int i=0;i<4;i++){
        vector<float> aux;
        for (int j=0;j<4;j++){
            aux.push_back(0);
        }
        r.push_back(aux);
    }
    float a[4][4]={0};
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (coord=='x'){
                a[i][j]=points[patch[((i*4)+j)]].getX();
            } else if (coord=='y'){
                a[i][j]=points[patch[((i*4)+j)]].getY();
            } else {
                a[i][j]=points[patch[((i*4)+j)]].getZ();
            }
        }
    }

    float M[4][4]={
        {-1.0f,3.0f,-3.0f,1.0f},
        {3.0f,-6.0f,3.0f,0.0f},
        {-3.0f,3.0f,0.0f,0.0f},
        {1.0f,0.0f,0.0f,0.0f}
    };

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                ri[i][j] += M[i][k] * a[k][j];


    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                r[i][j] += ri[i][k] * M[k][j];
    
    return r;
}

void calculateIndexes(int n,int tess,vector<int> &ind){
    tess=tess+1;
    for (int k=0;k<n;k++){
        for (int i=0;i<tess-1;i++){
            for (int j=0;j<tess-1;j++){
                ind.push_back((i*tess+j)+tess+(k*tess*tess));
                ind.push_back((i*tess+j)+tess+1+(k*tess*tess));
                ind.push_back(i*tess+j+(k*tess*tess));

                ind.push_back(i*tess+j+(k*tess*tess));
                ind.push_back((i*tess+j)+tess+1+(k*tess*tess));
                ind.push_back((i*tess+j)+1+(k*tess*tess));
            }
        }
    }
}

void calculatePatches(int tess,vector<Point> &iPoints,vector<vector<int>> &iPatches,vector<Point> &p){
    float inc=float(1/float(tess));
    float u=0.0f,v=0.0f;
    float us[4];
    float vs[4];
    for (int n=0;n<iPatches.size();n++){
        vector<vector<float>> rx = preCalculate('x',iPatches[n],iPoints);
        vector<vector<float>> ry = preCalculate('y',iPatches[n],iPoints);
        vector<vector<float>> rz = preCalculate('z',iPatches[n],iPoints);
        v=0.0f;
        for (int i=0;i<tess+1;v+=inc,i++){
            vs[0]=pow(v,3);vs[1]=pow(v,2);vs[2]=v;vs[3]=1;
            u=0.0f;
            for(int j=0;j<tess+1;u+=inc,j++){
                float interx[4]={0};
                float intery[4]={0};
                float interz[4]={0};
    
                float resx=0;
                float resy=0;
                float resz=0;
                us[0]=pow(u,3);us[1]=pow(u,2);us[2]=u;us[3]=1;
                for(int x=0;x<4;x++){
                    for (int y=0;y<4;y++){
                        interx[x]+=us[y]*rx[y][x];
                        intery[x]+=us[y]*ry[y][x];
                        interz[x]+=us[y]*rz[y][x];
                    }
                }

                for(int x=0;x<4;x++){
                    resx+=interx[x]*vs[x];
                    resy+=intery[x]*vs[x];
                    resz+=interz[x]*vs[x];
                }
            p.push_back(Point(resx,resy,resz));
            }
        }
    }
}

void readFile(string nameOF,vector<Point> &points,vector<vector<int>> &patches){
    ifstream readFile(nameOF);
    string line;
    //read number of patches
    getline (readFile, line);
    int n=stoi(line);

    //fill patches array
    regex regex(", ");
    for (int i=0;i<n;i++){
        getline (readFile, line);
    
        vector<string> out(
        sregex_token_iterator(line.begin(), line.end(), regex, -1),
        sregex_token_iterator()
        );
        vector<int> patch;
        for (auto &s: out) {
            patch.push_back(stoi(s));
        }
        patches.push_back(patch);
    }

    //read number of points
    getline (readFile, line);
    n=stoi(line);

    //fill points array
    for (int i=0;i<n;i++){
        getline (readFile, line);
    
        vector<string> out(
        sregex_token_iterator(line.begin(), line.end(), regex, -1),
        sregex_token_iterator()
        );
        
        for (int j=0;j<out.size();j+=3){
            points.push_back(Point(stof(out[j]),stof(out[j+1]),stof(out[j+2])));
        }
    }

}

void pointsBezier(char* inpFile,int tess,char* outFile){
    vector<Point> points;
    vector<vector<int>> patches;
    vector<Point> normals;
	vector<Point2D> texPoints;
    readFile(inpFile,points,patches);

    vector<int> ind;
    vector<Point> p;

    calculatePatches(tess,points,patches,p);
    calculateIndexes(patches.size(),tess,ind);

    Model model(p,ind,normals,texPoints);
    model.writeToFile(outFile,"bezierPatch");
}