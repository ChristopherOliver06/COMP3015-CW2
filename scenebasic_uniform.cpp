#include "scenebasic_uniform.h"
#include "helper/torus.h"
#include <glm/glm.hpp>
#include <sstream>
#include "helper/texture.h"
#include "helper/noisetex.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

 
#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
#include "helper/glutils.h"

using glm::vec3;
using glm::mat4;

//SceneBasic_Uniform::SceneBasic_Uniform() : torus(0.7f, 0.3f, 16, 160) {}
//SceneBasic_Uniform::SceneBasic_Uniform() : teapot(50, glm::translate(mat4(1.0f), vec3(0.0f,0.0f,1.0f))) {}

SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f, 10.0f, 100, 100), angle(0.0f), tPrev(0.0f),
rotSpeed(glm::pi<float>() / 12.0f), skyBox(100.0f)
{
    campfire = ObjMesh::load("media/Campfire.obj", true);
    bench = ObjMesh::load("media/GardenBench.obj", true);
    wall = ObjMesh::load("media/Wall.obj", true);
    secondWall = ObjMesh::load("media/Wall.obj", true);
    
}


//void SceneBasic_Uniform::initScene()
//{
//    compile();
//    glEnable(GL_DEPTH_TEST);
//        model = mat4(1.0f);
//        model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
//        view = glm::lookAt(vec3(-1.0f, 6.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.1f, 0.0f));
//        projection = mat4(1.0f);
//
//        float x, z;
//        for (int i = 0; i < 3; i++)
//        {
//            std::stringstream name;
//            name << "Lights[" << i << "].Position";
//            x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
//            z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
//            prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z + 1.0f, 0.0f));    
//        }
//        prog.setUniform("Lights[0].La", vec3(0.0f, 0.0f, 0.1f));
//        prog.setUniform("Lights[1].La", vec3(0.0f, 0.1f, 0.0f));
//        prog.setUniform("Lights[2].La", vec3(0.1f, 0.0f, 0.0f));
//
//        prog.setUniform("Lights[0].Ld", vec3(0.0f, 0.0f, 2.8f));
//        prog.setUniform("Lights[1].Ld", vec3(0.0f, 2.8f, 0.0f));
//        prog.setUniform("Lights[2].Ld", vec3(2.8f, 0.0f, 0.0f));
//
//        prog.setUniform("Lights[0].Ls", vec3(0.0f, 0.0f, 0.8f));
//        prog.setUniform("Lights[1].Ls", vec3(0.0f, 0.8f, 0.0f));
//        prog.setUniform("Lights[2].Ls", vec3(0.8f, 0.0f, 0.0f));
//        
//        prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);       
//        prog.setUniform("Material.Ka", 0.9f, 0.9f, 0.9f);       
//        prog.setUniform("Material.Ks", 0.1f, 0.1f, 0.1f);
//        prog.setUniform("Material.Shininess", 100.0f);
//        
//}


void SceneBasic_Uniform::initScene()
{

    texIDs[0] = Texture::loadTexture("media/Bench.png");
    texIDs[1] = Texture::loadTexture("media/grass.png");
    texIDs[2] = Texture::loadTexture("media/Walls.png");
    texIDs[3] = Texture::loadTexture("media/FIRE.png");
    texIDs[4] = Texture::loadCubeMap("media/texture/cube/sky/sky");

    noiseTex = NoiseTex::generate2DTex(6.0f);

    compile();
    glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);
    angle = glm::radians(90.0f);
    float x, z;
    for (int i = 0; i < 3; i++)
    {
        std::stringstream name;
        name << "lights[" << i << "].Position";
        x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
        z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
        prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.0f, z +
            1.0f, 1.0f));

    }


    prog.setUniform("Lights[0].La", vec3(0.1f, 0.1f, 0.1f));
    prog.setUniform("Lights[1].La", vec3(0.1f, 0.1f, 0.1f));
    prog.setUniform("Lights[2].La", vec3(0.1f, 0.1f, 0.1f));
    
    prog.setUniform("Lights[0].Ld", vec3(0.1f, 0.1f, 0.1f));
    prog.setUniform("Lights[1].Ld", vec3(0.1f, 0.1f, 0.1f));
    prog.setUniform("Lights[2].Ld", vec3(0.1f, 0.1f, 0.1f));
    
    prog.setUniform("Lights[0].Ls", vec3(0.1f, 0.1f, 0.1f));
    prog.setUniform("Lights[1].Ls", vec3(0.1f, 0.1f, 0.1f));
    prog.setUniform("Lights[2].Ls", vec3(0.1f, 0.1f, 0.1f));

    prog.setUniform("Fog.MaxDistance", 400.0f);
    prog.setUniform("Fog.MinDistance", 1.0f);
    prog.setUniform("Fog.Colour", vec3(1.0f, 0.4f, 0.02f));

}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    float deltaT = t - tPrev;

    if (tPrev == 0.0f) deltaT = 0.0f;

    tPrev = t;

    angle += rotSpeed * deltaT;

    if (angle > glm::two_pi<float>()) angle -= glm::two_pi<float>();
}

void SceneBasic_Uniform::render()
{
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Camera rotation
    vec3 cameraPos = vec3(3.0f * cos(angle), 1.0f, 2.0f * sin(angle));
    view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

   
    prog.use();
    model = mat4(1.0f);
    prog.setUniform("noisePower", 0.1f);
    setMatrices();

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, noiseTex); 


    

    // activate and bind textures
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texIDs[4]);

    skyBox.render();
   


    //Set the Bench Object 
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 20.0f);
    prog.setUniform("noisePower", 0.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(270.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.50f, 0.30f, 0.30f));
    setMatrices();
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texIDs[0]);

    bench->render();

  
    //Set the Wall Object 
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 180.0f);
    prog.setUniform("noisePower", 0.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
    model = glm::translate(model, glm::vec3(1.0f, 1.0f, -50.0f));
    setMatrices();

    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texIDs[2]);

    wall->render();

    //Set the Second Wall Object 
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 30.0f);
    prog.setUniform("noisePower", 0.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), vec3(0.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
    model = glm::translate(model, glm::vec3(1.0f, 1.0f, -50.0f));
    setMatrices();

    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texIDs[2]);

    secondWall->render();

    // Draw Campfire object
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.1f, 0.5f, 0.1f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 180.0f);
    prog.setUniform("noisePower", 0.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), vec3(0.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(0.30f, 0.30f, 0.30f));
    model = glm::translate(model, vec3(6.0f, 0.0f, 4.5f));
    setMatrices();

    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texIDs[3]);

    campfire->render();

    // Draw plane object
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess",10.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();

    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texIDs[1]);

    plane.render();    

}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(90.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]),vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
    prog.setUniform("ProjectionMatrix", projection);

}