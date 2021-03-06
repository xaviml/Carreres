/***************************************************/
/*           Definicio de la camera                */
/***************************************************/

#ifndef CAMERA_INCLOS
#define CAMERA_INCLOS
#include <stdio.h>

#include <Common.h>
#include <list>
#include <vector>
#include <QGLShaderProgram>

using namespace std;

#define PI 3.14159

#define MAXDPOST 100000
#define MINDANT -100000
#define EPS 0.001

#define DEGREES *180.0/PI

typedef enum {VISTA_X = 0, VISTA_Y = 1, VISTA_Z = 2, AXONOMETRIC = 3} TipVista; 

typedef enum {YAMUNT = 0, YABAIX = 1} Orienty; 

typedef enum {PARALLELA = 0, PERSPECTIVA = 1} TipProj; 


typedef struct
 {
  double      angy, angx, angz;  /* angles de gir del sistema de coords obser */
  vec4        vrp;               /* view reference point */
  vec4        obs;               /* posicio de l'observador */
 } VisuSystem;

typedef struct  
 {
  TipProj    proj;           /* tipus de proj: 0 paral 1 perpec */
  double     d;              /* distancia observador a pla proj */
  double     dant, dpost;    /* distancies al pla de retallat ante i post desde l'observador*/
  double     alfav, alfah;   /* angles d'obertura camera vertical i horitzontal */

} PiramProj;

/* =================================== */
/* =                                 = */
/* =             Camera              = */
/* =                                 = */
/* =================================== */

class Camera
{
public:
    Camera(QString name, int, int);
    ~Camera() {}

    /*Método que envía la cámara a la GPU*/
    void toGPU(QGLShaderProgram*);

    void setVRP(Capsa3D);
    void setOBS(Capsa3D);
    void setRotation(int, int);

    void CalculaMatriuModelView();
    void CalculaMatriuProjection();
    void CalculWindow(Capsa3D);
    void CalculWindowAmbRetallat();

    vec4 CalculObs(vec4 vrp, double d, double angx, double angy);
    vec4 CalculVup(double angx, double angy, double angz);

    void CreaMatSiv(mat4 &MSIV);
    void CreaMatVis(mat4 &MVIS);

    void CreaMatDp(mat4 &MDP);
    void AjustaAspectRatioWd();
    void AmpliaWindow(double r);
    void CalculAngleOberturaVertical();
    void CalculAngleOberturaHoritzontal();

    Capsa2D  CapsaMinCont2DXYVert( vec4 *v, int nv);

    void setViewport(int x, int y, int a, int h);
    void setModelView(mat4 m,QGLShaderProgram*);
    void setProjection(mat4 p,QGLShaderProgram*);

    void rotate(Capsa3D c);
    void pan();
    void zoom();

    QString name;

    VisuSystem vs;      /* Sistema de visualitzacio  */
    PiramProj piram;    /* Piramide de visualitzacio */
    Capsa2D wd;	      /* Window                    */
    Capsa2D vp;       /* Viewport                  */


private:
    void VertexCapsa3D(Capsa3D capsaMinima, vec4 vaux[8]);

    mat4  modView; // Matriu model-view de la CPU
    mat4  proj;  // Matriu projection de la CPU
    GLuint  model_view;  // model-view matrix uniform shader variable (GPU)
    GLuint  projection;  // projection matrix uniform shader variable (GPU)
};


#endif









