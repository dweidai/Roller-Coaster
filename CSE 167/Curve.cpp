#include "Curve.hpp"
#include "Window.h"
#include <iostream>
#include <vector>

float total = 150;
Curve::Curve(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3,glm::vec3 p4){
    toWorld = glm::mat4(1.0f);
    point1 = p1;
    point2 = p2;
    point3 = p3;
    point4 = p4;
    dots.push_back(point1);
    dots.push_back(point2);
    dots.push_back(point3);
    dots.push_back(point4);
    for(int i=0; i<151;i++){
        vertices.push_back(berstein(point1, point2, point3, point4, i/total));
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, (vertices.size()*sizeof(glm::vec3)), vertices.data(), GL_STATIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
        3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
        GL_FLOAT, // What type these components are
        GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
        3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
        (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
    
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &PPO);
    glBindVertexArray(VAO2);
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, PPO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, (dots.size()*sizeof(glm::vec3)), dots.data(), GL_STATIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
        3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
        GL_FLOAT, // What type these components are
        GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
        3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
        (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
}
Curve::~Curve(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &PPO);
}

glm::vec3 Curve::berstein(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float t){
    glm::vec3 part1 = (-t*t*t + 3*t*t - 3*t + 1)*p1;
    glm::vec3 part2 = (3*t*t*t - 6*t*t + 3*t)*p2;
    glm::vec3 part3 = (-3*t*t*t + 3*t*t)*p3;
    glm::vec3 part4 = (t*t*t)*p4;
    return part1+part2+part3+part4;
}

void Curve::draw(GLint shaderProgram){

    // Calculate the combination of the model and view (camera inverse) matrices
    glm::mat4 model = toWorld;
    glm::mat4 view = Window::V;
    // We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
    // Consequently, we need to forward the projection, view, and model matrices to the shader programs
    // Get the location of the uniform variables "projection" and "modelview"
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uObjcolor = glGetUniformLocation(shaderProgram, "Objcolor");
    GLuint uModel = glGetUniformLocation(shaderProgram, "model");
    GLuint uView = glGetUniformLocation(shaderProgram, "view");
    // Now send these values to the shader program;
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModel, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(uView, 1, GL_FALSE, &view[0][0]);
    glm::vec3 objcolor = glm::vec3(1.0f,0.65f,0.0f);
    glUniform3fv(uObjcolor,1, &objcolor[0]);
    // the VAO associated with it.
    glBindVertexArray(VAO);
    glLineWidth(50);
    // Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
    glDrawArrays(GL_LINE_STRIP, 0, (int)vertices.size());
    glBindVertexArray(0);
   
    // Now drawing anchors;
    glBindVertexArray(VAO2);
    
    objcolor = glm::vec3(1.0f,0.0f,0.0f);
    glUniform3fv(uObjcolor,1, &objcolor[0]);
    glPointSize(10);
    glDrawArrays(GL_POINTS, 0, 1);
    
    objcolor = glm::vec3(0.0f,1.0f,0.0f);
    glUniform3fv(uObjcolor,1, &objcolor[0]);
    glPointSize(10);
    glDrawArrays(GL_POINTS, 1, 2);
    
    objcolor = glm::vec3(1.0f,0.0f,0.0f);
    glUniform3fv(uObjcolor,1, &objcolor[0]);
    glPointSize(10);
    glDrawArrays(GL_POINTS, 3, 1);
    
    objcolor = glm::vec3(1.0f,1.0f,0.0f);
    glUniform3fv(uObjcolor,1, &objcolor[0]);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);
    
}

void Curve::curve_update(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3,glm::vec3 p4){
    toWorld = glm::mat4(1.0f);
    point1 = p1;
    point2 = p2;
    point3 = p3;
    point4 = p4;
    dots.clear();
    vertices.clear();
    dots.push_back(point1);
    dots.push_back(point2);
    dots.push_back(point3);
    dots.push_back(point4);
    for(int i=0; i<151;i++){
        vertices.push_back(berstein(point1, point2, point3, point4, i/total));
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, (vertices.size()*sizeof(glm::vec3)), vertices.data(), GL_STATIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
    
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &PPO);
    glBindVertexArray(VAO2);
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, PPO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, (dots.size()*sizeof(glm::vec3)), dots.data(), GL_STATIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
}
