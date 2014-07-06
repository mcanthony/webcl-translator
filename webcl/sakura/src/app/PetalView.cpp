//
//  PetalView.cpp
//  Sakura GL Toy
//
//  Created by Kyle Halladay on 2014-06-14.
//  Copyright (c) 2014 Kyle Halladay. All rights reserved.
//

#include "PetalView.h"
#include "ObjParser.h"
#include "ParticlePrototype.h"
#define CONTROL_SENSITIVITY 0.3f

PetalView::PetalView(int p, float aspect)
{
    petalCount = p;
    initPetals();
    camera = new Camera(60.0f, aspect, 0.01f, 500.0f);
    kmVec3 camPos;
    kmVec3Fill(&camPos, 0.0, 0.0, 10.0);
    
    bgPlane = new ShaderPlane((char*)"vs_ndcPlane.h", (char*)"fs_background.h");
    
    camera->setPosition(camPos);
    camera->lookAt(KM_VEC3_ZERO);
}

void PetalView::initPetals()
{
    shaderLoader = new ShaderLoader();
    
    char* vertex = (char*)"vs_diffuse.h";
    char* fragment = (char*)"fs_diffuse.h";
    
    kmVec3Fill(&lightDirection, -1.0, -1.0, 0.0);
    ParticlePrototype* pType = new ParticlePrototype();
    pType->setShader(shaderLoader->loadShaderFromResources(vertex, fragment));
    pType->setMesh((char*)"tri_petal_normals.obj");
    
    particleSystem = new CLParticleSystem(pType);
   
}

void PetalView::update()
{
    particleSystem->update(camera->getViewProjectionMatrix());
}

void PetalView::draw()
{
    particleSystem->drawParticles(camera->getViewProjectionMatrix(), lightDirection);
    bgPlane->draw(camera->getViewProjectionMatrix());
}