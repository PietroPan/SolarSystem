#include "terrain.h"
void cross(float *a, float *b, float *res) {
	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];

}


void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	if (l==0){
		a[0] = 0;
		a[1] = 0;
		a[2] = 0;
	} else {
		a[0] = a[0]/l;
		a[1] = a[1]/l;
		a[2] = a[2]/l;
	}

}

void sub (float *a, float *b, float *res){

	res[0] = a[0]-b[0];
	res[1] = a[1]-b[1];
	res[2] = a[2]-b[2];
}

void computeNormal(int i, int j,int w,unsigned char* c,vector<Point> &normal,float mult) {
	float fi=float(i);
	float fj=float(i);
	
	float p1[3] = {fi,float(c[ ((j-1)+(w*i)) ]*mult),fj-1};
	float p2[3] = {fi,float(c[ ((j+1)+(w*i)) ]*mult),fj+1};
	float p3[3] = {fi-1,float(c[ ((j)+(w*(i-1))) ]*mult) ,fj};
	float p4[3] = {fi+1,float(c[ (j+(w*(i+1))) ]*mult),fj};
	float v1[3] = {0,0,0};
	sub(p2,p1,v1);
	float v2[3] = {0,0,0};
	sub(p4,p3,v2);
	float n[3] = {0,0,0};
	cross(v1,v2,n);
	normalize(n);
	normal.push_back(Point(n[0],n[1],n[2]));
}

	// fill the normal vector with the normal for vertex at grid location (i,j)


void drawGrid(int h,int w,vector<Point> &p,unsigned char* c,vector<Point> &n,vector<Point2D> &t,float mult){
	float ih=-((float(h)-1)/2),iw=-((float(w)-1)/2);//posição do ponto incial
	for (int i=0;i<h-1;i++){
		for (int j=0;j<w;j++){
            p.push_back(Point(ih+j,(c[j+(w*i)])*mult,iw+i));
			t.push_back(Point2D(j,i));
			computeNormal(i,j,w,c,n,mult);
			//p.push_back(ih+j);
			//p.push_back(c[j+(w*i)]);//altura
			//p.push_back(iw+i);
            
            p.push_back(Point(ih+j,(c[j+(w*(i+1))])*mult,iw+(i+1)));
			t.push_back(Point2D(j,i+1));
			computeNormal(i+1,j,w,c,n,mult);
			//p.push_back(ih+j);
			//p.push_back(c[j+(w*(i+1))]);//altura
			//p.push_back(iw+(i+1));
		}
	}
}

void pointsTerrain(char * image, char * output,float mult){
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
	drawGrid(th,tw,p,imageData,normals,texPoints,mult);//prencher vetor de pontos de acordo com o tamanho da figura
	
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
