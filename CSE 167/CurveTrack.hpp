//
//  CurveTrack.hpp
//  CSE 167
//
//  Created by Dwei on 11/15/18.
//  Copyright © 2018 Dwei. All rights reserved.
//

#ifndef CurveTrack_hpp
#define CurveTrack_hpp

#include <stdio.h>
#include "Curve.hpp"
class CurveTrack{
public:
    int currentID = 0;
    glm::vec3 current;
    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    glm::vec3 p4;
    glm::vec3 p5;
    glm::vec3 p6;
    glm::vec3 p7;
    glm::vec3 p8;
    glm::vec3 p9;
    glm::vec3 p10;
    glm::vec3 p11;
    glm::vec3 p12;
    glm::vec3 p13;
    glm::vec3 p14;
    glm::vec3 p15;
    glm::vec3 p16;
    glm::vec3 p17;
    glm::vec3 p18;
    glm::vec3 p19;
    glm::vec3 p20;
    glm::vec3 p21;
    glm::vec3 p22;
    glm::vec3 p23;
    
    Curve* curve1;
    Curve* curve2;
    Curve* curve3;
    Curve* curve4;
    Curve* curve5;
    Curve* curve6;
    Curve* curve7;
    Curve* curve8;
    
    CurveTrack();
    ~CurveTrack();
    void draw(GLint shaderProgram);
    void update(float x, float y, float z);
    std::vector<glm::vec3> movetrack();
};
#endif /* CurveTrack_hpp */
