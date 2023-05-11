#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include "helper/teapot.h"
#include <glm/glm.hpp>
#include "helper/plane.h"
#include "helper/objmesh.h"
#include "helper/skybox.h"


class SceneBasic_Uniform : public Scene
{
private:
   
    GLSLProgram prog;
    //Torus torus;
    //Teapot teapot;
    SkyBox skyBox; //skybox
    float angle, tPrev, rotSpeed;


    Plane plane; //plane surface
    std::unique_ptr<ObjMesh> bench; //Bench Mesh
    std::unique_ptr<ObjMesh> wall; //Garden wall mesh
    std::unique_ptr<ObjMesh> secondWall; //Garden wall mesh
    std::unique_ptr<ObjMesh> campfire; //Campfire mesh

    GLuint noiseTex;

    void compile();
    void setMatrices();

public:
    SceneBasic_Uniform();
    GLuint texIDs[5];
    void initScene();
    void update( float t );
    void render();
    void resize(int, int);

    
};

#endif // SCENEBASIC_UNIFORM_H
