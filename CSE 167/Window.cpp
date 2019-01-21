#include "Window.h"
#include "OBJObject.h"
#include "Curve.hpp"
#include "CurveTrack.hpp"

const char* window_title = "GLFW Starter Project";
Cube * cube; //this is the skybox
OBJObject* sphere;
//Curve * curve;
CurveTrack* track;

GLint shaderProgram;
GLint skyboxShader;
GLint trackShader;

// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "//Users/apple/Desktop/CSE 167/CSE 167 hw4/CSE 167/shader.vert"
#define FRAGMENT_SHADER_PATH "/Users/apple/Desktop/CSE 167/CSE 167 hw4/CSE 167/shader.frag"
#define SKYBOX_VERTEX_SHADER_PATH "/Users/apple/Desktop/CSE 167/CSE 167 hw4/CSE 167/skybox.vert"
#define SKYBOX_FRAGMENT_SHADER_PATH "/Users/apple/Desktop/CSE 167/CSE 167 hw4/CSE 167/skybox.frag"
#define TRACK_VERTEX_SHADER_PARTH "/Users/apple/Desktop/CSE 167/CSE 167 hw4/CSE 167/track.vert"
#define TRACK_FRAGMENT_SHADER_PARTH "/Users/apple/Desktop/CSE 167/CSE 167 hw4/CSE 167/track.frag"
// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is
std::vector <glm::vec3> movetrack;
int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;
int kb = 4;
int current = 1;
int changesize = 0;
int buttonsize = 0;
int scale = 1.5;
int pressed = 0;
float normal_coloring = 0;
float angle;
float near = 0.1f;
float far = 1000.0f;
int pause = 0;
int count = 0;
glm::vec3 last_position;
glm::vec3 current_position;
glm::vec3 move;
void Window::initialize_objects()
{
	cube = new Cube();
    sphere = new OBJObject("/Users/apple/Desktop/CSE 167/CSE 167 hw4/CSE 167/sphere.obj");
    //curve = new Curve(glm::vec3(0,0,0),glm::vec3(2,-1,0),glm::vec3(3,3,0),glm::vec3(5,0,0));
    track = new CurveTrack();
	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    skyboxShader = LoadShaders(SKYBOX_VERTEX_SHADER_PATH, SKYBOX_FRAGMENT_SHADER_PATH);
    trackShader = LoadShaders(TRACK_VERTEX_SHADER_PARTH, TRACK_FRAGMENT_SHADER_PARTH);
    movetrack = track->movetrack();
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(cube);
    delete(sphere);
    //delete(curve);
    delete(track);
    glDeleteShader(skyboxShader);
	glDeleteProgram(shaderProgram);
    glDeleteShader(trackShader);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
    }    //create  the cube as the first thing
    
	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);
	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
    movetrack = track->movetrack();
    if(pause == 1){
        glm::vec3 diff =movetrack.at((count+1) % (movetrack.size())) - movetrack.at((count) % (movetrack.size()));
        sphere->toWorld = sphere->toWorld * glm::translate(glm::mat4(1.0f), diff);
        count = count + 1;
    }
    else if (pause == 0){
        //do nothing
    }
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	
    glUseProgram(skyboxShader);
	// Render the cube
	cube->draw(skyboxShader);
    glUseProgram(shaderProgram);
    sphere->draw(shaderProgram);
    glUseProgram(trackShader);
    track->draw(trackShader);
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Check for a key press
    if (action == GLFW_PRESS)
    {
        // Check if escape was pressed
        if (key == GLFW_KEY_ESCAPE)
        {
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if (key == GLFW_KEY_LEFT){
            if(track->currentID == 0){
                track -> currentID = 23;
            }
            else{
                track->currentID = track->currentID -1;
            }
        }
        if (key == GLFW_KEY_RIGHT){
            if(track->currentID == 23){
                track->currentID = 0;
            }
            else{
                track->currentID = track->currentID +1;
            }
        }
        if(key == GLFW_KEY_UP){
            track->update(0.05, 0.05, 0.05);
        }
        if(key == GLFW_KEY_DOWN){
            track->update(-0.05, -0.05, -0.05);
        }
        if(key == GLFW_KEY_P){
            if(pause == 0){
                pause  = 1;
            }
            else if(pause == 1){
                pause = 0;
            }
        }
    }
}
glm::vec3 Window::trackBallMapping(double x, double y){
    glm::vec3 v = glm::vec3(0,0,0);
    double d;
    v.x = (2.0*x-width)/width;
    v.y = (height-2.0*y)/height;
    
    v.z = 0.0;
    d = glm::length(v);
    d = (d<1.0) ? d : 1.0;
    v.z = sqrtf(1.001 - d*d);
    v = glm::normalize(v);
    return v;
}
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(pressed == 0 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        //glfwGetCursorPos(window, &x, &y);
        pressed = 1;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        pressed = 0;
    }
}
void Window::cursor_callback( GLFWwindow *window, double x, double y ){
    //only continue if the mouse is pressed
    if(pressed == 1){
        last_position = Window::trackBallMapping(x, y);
        pressed = -1;
    }
    else if(pressed == 0){
        //do nothing
        return;
    }
    current_position = Window::trackBallMapping(x, y);
    move = glm::cross(last_position, current_position);
    angle = asin(glm::length(move));
    angle = angle/50;
    if(glm::length(current_position-last_position) < 0.01){
        return; //do nothing
    }
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, move);
    glm::vec3 d = cam_pos-cam_look_at; ////comment
    glm::vec4 temp = rotation*glm::vec4(d,0.0f);
    cam_look_at = glm::vec3(cam_pos.x-temp.x,cam_pos.y-temp.y, cam_pos.z-temp.z);
    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
}
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    if(yoffset>0){
        cam_pos = cam_pos + (0.05f) * glm::vec3(cam_look_at-cam_pos);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
    else{
        cam_pos = cam_pos - (0.05f) * glm::vec3(cam_look_at-cam_pos);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
}
