//
// Created by mane on 29/03/21.
//
#include "gereIncludes.h"
#include "drawable.h"

extern bool drawCurves;
class Transformacao: public Drawable {};

// translacao
class Translacao: public Transformacao {
private:
    float x, y, z, time;
    vector<vector<float>> points;
    bool curve;

public:
    Translacao() {
        x = y = z = 0.0f;
    }

    Translacao(float x, float y, float z,vector<vector<float>> points,bool curve,float time) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->time = time;
        this->points = points;
        this->curve = curve;
    }

    void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

    void getCatmullRomPoint(float t, vector<float> p0, vector<float> p1, vector<float> p2, vector<float> p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
	
	float tm[4] = {t*t*t,t*t,t,1};
	float tmd[4] ={3*(t*t),2*t,1,0};
	// Compute A = M * P
	float pxr[4];
	float pyr[4];
	float pzr[4];
	float px[4]={p0[0],p1[0],p2[0],p3[0]};
	float py[4]={p0[1],p1[1],p2[1],p3[1]};
	float pz[4]={p0[2],p1[2],p2[2],p3[2]};
	multMatrixVector((float*)m,px,pxr);
	multMatrixVector((float*)m,py,pyr);
	multMatrixVector((float*)m,pz,pzr);
	
	// Compute pos = T * A
	pos[0]=0;pos[1]=0;pos[2]=0;
	for (int i=0;i<4;i++){
		pos[0]+=tm[i]*pxr[i];
		pos[1]+=tm[i]*pyr[i];
		pos[2]+=tm[i]*pzr[i];
	}
	// compute deriv = T' * A
	deriv[0]=0;deriv[1]=0;deriv[2]=0;
	for (int i=0;i<4;i++){
		deriv[0]+=tmd[i]*pxr[i];
		deriv[1]+=tmd[i]*pyr[i];
		deriv[2]+=tmd[i]*pzr[i];
	}
	// ...
}
    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {
        int point_count = (this->points).size();
	    float t = gt * point_count; // this is the real global t
	    int index = floor(t);  // which segment
	    t = t - index; // where within  the segment

	    // indices store the points
	    int indices[4]; 
	    indices[0] = (index + point_count-1)%point_count;	
	    indices[1] = (indices[0]+1)%point_count;
	    indices[2] = (indices[1]+1)%point_count; 
	    indices[3] = (indices[2]+1)%point_count;

	    getCatmullRomPoint(t, (this->points)[indices[0]], (this->points)[indices[1]], (this->points)[indices[2]], (this->points)[indices[3]], pos, deriv);
    }

    void renderCatmullRomCurve() {
    	float pos[3];
	    float deriv[3];
	    float t=0;

        // draw curve using line segments with GL_LINE_LOOP
	    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
	    for (int i = 0; i < 100; ++i,t+=(1.0f/100.0f)) {
		    getGlobalCatmullRomPoint(t,pos,deriv);
		    glVertex3f(pos[0], pos[1], pos[2]);
	    }
	    glEnd();
    }

    void cross(float *a, float *b, float *res) {

        res[0] = a[1]*b[2] - a[2]*b[1];
        res[1] = a[2]*b[0] - a[0]*b[2];
        res[2] = a[0]*b[1] - a[1]*b[0];
    }


    void normalize(float *a) {

        float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
        a[0] = a[0]/l;
        a[1] = a[1]/l;
        a[2] = a[2]/l;
    }


    void draw() {
        if (this->curve){
            if (drawCurves) renderCatmullRomCurve();
            float pos[3];
            float deriv[3];
            float timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
            float trueTime = ((float)timeSinceStart/1000.0f);
            getGlobalCatmullRomPoint(trueTime/(this->time),pos,deriv);
            extern float y[3];

            	float x[3]={deriv[0],deriv[1],deriv[2]};
                normalize(x);
                float z[3];
                cross(x,y,z);
                normalize(z);
                cross(z,x,y);
                normalize(y);
                float f[4]={0,0,0,1};
                
                float m[4][4];
                for (int i=0;i<3;i++) {
                    m[i][0]=x[i];
                    m[i][1]=y[i];
                    m[i][2]=z[i];
                    m[i][3]=0.0f;
                    m[3][i]=0.0f;
                }
                m[3][3]=1.0f;

            glTranslatef(pos[0],pos[1],pos[2]);
            glMultMatrixf(*m);

        } else
        glTranslatef(x, y, z);
    }
};

// rotacao
class Rotacao: public Transformacao {
private:
    int angulo;
    float x,y,z,time;
    bool rotating;

public:
    Rotacao(int ang, float time, float x, float y, float z,bool rotating) {
        this->angulo = ang;
        this->time = time;
        this->x = x;
        this->y = y;
        this->z = z;
        this->rotating=rotating;
    }

    void draw() {
        if (this->rotating){
            int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
            float trueTime = ((float)timeSinceStart/1000.0f);
            if (time>0){
                glRotatef(trueTime*360.0f/time,x,y,z);
            }
        } else {
            glRotatef(angulo, x, y, z);
        }
    }
};

// escala
class Escala: public Transformacao {
private:
    float x, y, z;
public:
    Escala(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void draw() {
        glScalef(x,y,z);
    }
};
