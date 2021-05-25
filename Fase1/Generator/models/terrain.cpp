#include "terrain.h"


void drawGrid(int h,int w,vector<Point> &p,unsigned char* c){
	float ih=-((float(h)-1)/2),iw=-((float(w)-1)/2);//posição do ponto incial
	for (int i=0;i<h-1;i++){
		for (int j=0;j<w;j++){
            p.push_back(Point(ih+j,c[j+(w*i)],iw+i));
			//p.push_back(ih+j);
			//p.push_back(c[j+(w*i)]);//altura
			//p.push_back(iw+i);
            
            p.push_back(Point(ih+j,c[j+(w*(i+1))],iw+(i+1)));
			//p.push_back(ih+j);
			//p.push_back(c[j+(w*(i+1))]);//altura
			//p.push_back(iw+(i+1));
		}
	}
}

void pointsTerrain(char * image, char * output){
    // 	Load the height map "terreno.jpg"
	unsigned int t;
	unsigned char* imageData;
	ilGenImages(1,&t);
	ilBindImage(t);
	// terreno.jpg is the image containing our height map
	ilLoadImage((ILstring)image);
	// convert the image to single channel per pixel
	// with values ranging between 0 and 255
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
	// important: check tw and th values
	// both should be equal to 256
	// if not there was an error loading the image
	// most likely the image could not be found
	int tw = ilGetInteger(IL_IMAGE_WIDTH);
	int th = ilGetInteger(IL_IMAGE_HEIGHT);
	// imageData is a LINEAR array with the pixel values
	imageData = ilGetData();


// 	Build the vertex arrays
	
	vector<Point> p;//pontos
	vector<Point> normals;
	vector<Point2D> texPoints;
	//preparar pontos
	drawGrid(th,tw,p,imageData);//prencher vetor de pontos de acordo com o tamanho da figura
	
    Model model(p,normals,texPoints);
    model.writeTToFile(output,"terrain",tw,th);
    /*verticeCount = p.size() / 3;

	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER,vertices);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*p.size(),p.data(),GL_STATIC_DRAW);

// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
    */
}

void init() {
}