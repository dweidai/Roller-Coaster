#include "CurveTrack.hpp"
#include "Curve.hpp"
#include <iostream>


CurveTrack::CurveTrack(){
    p0 = glm::vec3(0,0,0);
    p1 = glm::vec3(2,-1,-4);
    p2 = glm::vec3(3,-3,0);
    p3 = glm::vec3(0,0,-5);
    p4 = p3+(p3-p2);
    p5 = glm::vec3(8, -2, 0);
    p6 = glm::vec3(10, 3, 0);
    p7 = p6+(p6-p5);
    p8 = glm::vec3(14, -2, 0);
    p9 = glm::vec3(14, -4, 0);
    p10 = p9+(p9-p8);
    p11 = glm::vec3(10, -8, 1);
    p12 = glm::vec3(10, -10, 0);
    p13 = p12+(p12-p11);
    p14 = glm::vec3(10, -14, 2);
    p15 = glm::vec3(8, -14, 0);
    p16 = p15+(p15-p14);
    p17 = glm::vec3(2, -10, -3);
    p18 = glm::vec3(-2, -10, -3);
    p19 = p18+(p18-p17);
    p20 = glm::vec3(-2, -8, 4);
    p21 = glm::vec3(-2,-1, 3);
    p22 = p21+(p21-p20);
    p23 = p0 + (p0-p1);
   
    current = p0;
    
    curve1 = new Curve(p0, p1, p2, p3);
    curve2 = new Curve(p3, p4, p5, p6);
    curve3 = new Curve(p6, p7, p8, p9);
    curve4 = new Curve(p9, p10, p11, p12);
    curve5 = new Curve(p12, p13, p14, p15);
    curve6 = new Curve(p15, p16, p17, p18);
    curve7 = new Curve(p18, p19, p20, p21);
    curve8 = new Curve(p21, p22, p23, p0);
}
CurveTrack::~CurveTrack(){

}
void CurveTrack::update(float x, float y, float z){
    switch (currentID) {
        case 0:
            p0 = p0+glm::vec3(x,y,z);
            p23 = p23 + glm::vec3(x,y,z);
            p1 = p1 + glm::vec3(x,y,z);
            curve1->curve_update(p0, p1, p2, p3);
            curve8->curve_update(p21, p22, p23, p0);
            break;
        case 1:
            p1 = p1+glm::vec3(x,y,z);
            p23 = p23-glm::vec3(x,y,z);
            curve1->curve_update(p0, p1, p2, p3);
            curve8->curve_update(p21, p22, p23, p0);
            break;
        case 2:
            p2 = p2 + glm::vec3(x,y,z);
            p4 = p4 - glm::vec3(x,y,z);
            curve1->curve_update(p0, p1, p2, p3);
            curve2->curve_update(p3, p4, p5, p6);
            break;
        case 3:
            p3 = p3+glm::vec3(x,y,z);
            p2 = p2 + glm::vec3(x,y,z);
            p4 = p4 + glm::vec3(x,y,z);
            curve1->curve_update(p0, p1, p2, p3);
            curve2->curve_update(p3, p4, p5, p6);
            break;
        case 4:
            p4 = p4 + glm::vec3(x,y,z);
            p2 = p2 - glm::vec3(x,y,z);
            curve1->curve_update(p0, p1, p2, p3);
            curve2->curve_update(p3, p4, p5, p6);
            break;
        case 5:
            p5 = p5 + glm::vec3(x,y,z);
            p7 = p7 - glm::vec3(x,y,z);
            curve2->curve_update(p3, p4, p5, p6);
            curve3->curve_update(p6, p7, p8, p9);
            break;
        case 6:
            p5 = p5 + glm::vec3(x,y,z);
            p6 = p6 + glm::vec3(x,y,z);
            p7 = p7 + glm::vec3(x,y,z);
            curve2->curve_update(p3, p4, p5, p6);
            curve3->curve_update(p6, p7, p8, p9);
            break;
        case 7:
            p7 = p7 + glm::vec3(x,y,z);
            p5 = p5 - glm::vec3(x,y,z);
            curve2->curve_update(p3, p4, p5, p6);
            curve3->curve_update(p6, p7, p8, p9);
            break;
        case 8:
            p8 = p8+glm::vec3(x,y,z);
            p10 = p10 - glm::vec3(x,y,z);
            curve3->curve_update(p6, p7, p8, p9);
            curve4->curve_update(p9, p10, p11, p12);
            break;
        case 9:
            p8 = p8 + glm::vec3(x,y,z);
            p9 = p9 + glm::vec3(x,y,z);
            p10 = p10 + glm::vec3(x,y,z);
            curve3->curve_update(p6, p7, p8, p9);
            curve4->curve_update(p9, p10, p11, p12);
            break;
        case 10:
            p10 = p10 + glm::vec3(x,y,z);
            p8 = p8 - glm::vec3(x,y,z);
            curve3->curve_update(p6, p7, p8, p9);
            curve4->curve_update(p9, p10, p11, p12);
            break;
        case 11:
            p11 = p11+ glm::vec3(x,y,z);
            p13 = p13 - glm::vec3(x,y,z);
            curve4->curve_update(p9, p10, p11, p12);
            curve5->curve_update(p12, p13, p14, p15);
            break;
        case 12:
            p12 = p12+glm::vec3(x,y,z);
            p11 = p11 + glm::vec3(x,y,z);
            p13 = p13 + glm::vec3(x,y,z);
            curve4->curve_update(p9, p10, p11, p12);
            curve5->curve_update(p12, p13, p14, p15);
            break;
        case 13:
            p13 = p13 + glm::vec3(x,y,z);
            p11 = p11 - glm::vec3(x,y,z);
            curve4->curve_update(p9, p10, p11, p12);
            curve5->curve_update(p12, p13, p14, p15);
            break;
        case 14:
            p14 = p14+glm::vec3(x,y,z);
            p16 = p16 - glm::vec3(x,y,z);
            curve5->curve_update(p12, p13, p14, p15);
            curve6->curve_update(p15, p16, p17, p18);
            break;
        case 15:
            p15 = p15+glm::vec3(x,y,z);
            p14 = p14 + glm::vec3(x,y,z);
            p16 = p16 + glm::vec3(x,y,z);
            curve5->curve_update(p12, p13, p14, p15);
            curve6->curve_update(p15, p16, p17, p18);
            break;
        case 16:
            p16 = p16 + glm::vec3(x,y,z);
            p14 = p14 - glm::vec3(x,y,z);
            curve5->curve_update(p12, p13, p14, p15);
            curve6->curve_update(p15, p16, p17, p18);
            break;
        case 17:
            p17 = p17 + glm::vec3(x,y,z);
            p19 = p19 - glm::vec3(x,y,z);
            curve6->curve_update(p15, p16, p17, p18);
            curve7->curve_update(p18, p19, p20, p21);
            break;
        case 18:
            p18 = p18 + glm::vec3(x,y,z);
            p17 = p17 + glm::vec3(x,y,z);
            p19 = p19 + glm::vec3(x,y,z);
            curve6->curve_update(p15, p16, p17, p18);
            curve7->curve_update(p18, p19, p20, p21);
            break;
        case 19:
            p19 = p19 + glm::vec3(x,y,z);
            p17 = p17 - glm::vec3(x,y,z);
            curve7->curve_update(p18, p19, p20, p21);
            curve6->curve_update(p15, p16, p17, p18);
            break;
        case 20:
            p20 = p20 + glm::vec3(x,y,z);
            p22 = p22 - glm::vec3(x,y,z);
            curve7->curve_update(p18, p19, p20, p21);
            curve8->curve_update(p21, p22, p23, p0);
            break;
        case 21:
            p21 = p21 + glm::vec3(x,y,z);
            p20 = p20 + glm::vec3(x,y,z);
            p22 = p22 + glm::vec3(x,y,z);
            curve7->curve_update(p18, p19, p20, p21);
            curve8->curve_update(p21, p22, p23, p0);
            break;
        case 22:
            p22 = p22 + glm::vec3(x,y,z);
            p20 = p20 - glm::vec3(x,y,z);
            curve7->curve_update(p18, p19, p20, p21);
            curve8->curve_update(p21, p22, p23, p0);
            break;
        case 23:
            p23 = p23 + glm::vec3(x,y,z);
            p1 = p1 - glm::vec3(x,y,z);
            curve8->curve_update(p21, p22, p23, p0);
            curve1->curve_update(p0, p1, p2, p3);
            break;
        default:
            break;
    }
    
}
void CurveTrack::draw(GLint shaderProgram){
    curve1->draw(shaderProgram);
    curve2->draw(shaderProgram);
    curve3->draw(shaderProgram);
    curve4->draw(shaderProgram);
    curve5->draw(shaderProgram);
    curve6->draw(shaderProgram);
    curve7->draw(shaderProgram);
    curve8->draw(shaderProgram);
}
std::vector<glm::vec3> CurveTrack::movetrack(){
    std::vector<glm::vec3> toReturn;
    for(int i=0; i<curve1->getvertices().size();i++){
        toReturn.push_back(curve1->getvertices().at(i));
    }
    for(int i=0; i<curve2->getvertices().size();i++){
        toReturn.push_back(curve2->getvertices().at(i));
    }
    for(int i=0; i<curve3->getvertices().size();i++){
        toReturn.push_back(curve3->getvertices().at(i));
    }
    for(int i=0; i<curve4->getvertices().size();i++){
        toReturn.push_back(curve4->getvertices().at(i));
    }
    for(int i=0; i<curve5->getvertices().size();i++){
        toReturn.push_back(curve5->getvertices().at(i));
    }
    for(int i=0; i<curve6->getvertices().size();i++){
        toReturn.push_back(curve6->getvertices().at(i));
    }
    for(int i=0; i<curve7->getvertices().size();i++){
        toReturn.push_back(curve7->getvertices().at(i));
    }
    for(int i=0; i<curve8->getvertices().size();i++){
        toReturn.push_back(curve8->getvertices().at(i));
    }
    return toReturn;
}
