#include "model.h"

using namespace std;

void Model ::writeToFile(char *filename,char const *tag){
    ofstream file;
    file.open(filename);
    file << tag << "\n";
    file << to_string(this->points.size())+"\n";
     for(int i=0; i<points.size();i++)
       file << points.at(i).point_to_string()+"\n";

    file << to_string(this->indexs.size())+"\n";
    for (int i=0;i<indexs.size();i++)
        file << to_string(indexs.at(i))+"\n";

    //file << to_string(this->normals.size())+"\n";
    for (int i=0;i<normals.size();i++)
        file << normals.at(i).point_to_string()+"\n";

    //file << to_string(this->texPoints.size())+"\n";
    for (int i=0;i<texPoints.size();i++)
        file << texPoints.at(i).point_to_string()+"\n";
    
    file.close();
}

void Model ::writeTToFile(char *filename,char const *tag,int w, int h){
    ofstream file;
    file.open(filename);
    file << tag << "\n";
    file << to_string(w) << "\n";
    file << to_string(h) << "\n";
    //file << to_string(this->points.size())+"\n";
     for(int i=0; i<points.size();i++)
       file << points.at(i).point_to_string()+"\n";

    //file << to_string(this->normals.size())+"\n";
    for (int i=0;i<normals.size();i++)
        file << normals.at(i).point_to_string()+"\n";

    //file << to_string(this->texPoints.size())+"\n";
    for (int i=0;i<texPoints.size();i++)
        file << texPoints.at(i).point_to_string()+"\n";
    
    
    file.close();
}