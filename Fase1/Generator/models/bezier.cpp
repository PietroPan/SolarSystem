#include "bezier.h"

vector<vector<float>> preCalculate(int h,vector<int> &patch,vector<float> &points){
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
            a[i][j]=points[patch[((i*4)+j)]*3+h];
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

void calculateIndexes(int n,int tess,vector<unsigned int> &ind){
    tess=tess+1;
    for (int k=0;k<n;k++){
        for (int i=0;i<tess-1;i++){
            for (int j=0;j<tess-1;j++){
                ind.push_back((i*tess+j)+tess+(k*tess*tess));
                ind.push_back(i*tess+j+(k*tess*tess));
                ind.push_back((i*tess+j)+tess+1+(k*tess*tess));

                ind.push_back(i*tess+j+(k*tess*tess));
                ind.push_back((i*tess+j)+1+(k*tess*tess));
                ind.push_back((i*tess+j)+tess+1+(k*tess*tess));
            }
        }
    }
}

void calculatePatches(int tess,vector<float> &iPoints,vector<vector<int>> &iPatches,vector<float> &p){
    float inc=float(1/float(tess));
    float u=0.0f,v=0.0f;
    float us[4];
    float vs[4];
    for (int n=0;n<32;n++){
        vector<vector<float>> rx = preCalculate(0,iPatches[n],iPoints);
        vector<vector<float>> ry = preCalculate(1,iPatches[n],iPoints);
        vector<vector<float>> rz = preCalculate(2,iPatches[n],iPoints);
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
            p.push_back(resx);
            p.push_back(resz);
            p.push_back(resy);
            }
        }
    }
}

void readFile(string nameOF,vector<float> &points,vector<vector<int>> &patches){
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

        for (auto &s: out) {
            points.push_back(stof(s));
        }
    }

}

void pointsBezier(char* inpFile,int tess,char* outFile){
    vector<float> points;
    vector<vector<int>> patches;
    readFile(inpFile,points,patches);

    vector<unsigned int> ind;
    vector<float> p;

    calculatePatches(tess,points,patches,p);
    calculateIndexes(patches.size(),tess,ind);

    ofstream file;
    file.open(outFile);
    file << "bezier" << "\n";
    file << to_string(p.size()/3)+"\n";
     for(int i=0; i<p.size();i+=3)
       file << to_string(p[i])+" "+to_string(p[i+1])+" "+to_string(p[i+2])+"\n";

    file << to_string(ind.size())+"\n";
    for (int i=0;i<ind.size();i++)
        file << to_string(ind[i])+"\n";
    
    file.close();
}