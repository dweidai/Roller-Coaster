#ifndef Curve_hpp
#define Curve_hpp

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stdio.h>
#define numCurves 8
class Curve{
public:
    glm::mat4 toWorld;
    glm::vec3 point1, point2, point3, point4;
    Curve(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3,glm::vec3 p4);
    ~Curve();
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> dots;
    glm::vec3 berstein(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3,glm::vec3 p4, float t);
    void draw(GLint shader);
    void curve_update(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3,glm::vec3 p4);
    std::vector<glm::vec3> getvertices(){
        return vertices;
    }
    GLuint VBO, VAO, VAO2, PPO;
    GLuint uProjection, uModel, uView;
    GLuint uObjcolor;
    glm::mat4 modelview;
};
#endif /* Curve_hpp */
