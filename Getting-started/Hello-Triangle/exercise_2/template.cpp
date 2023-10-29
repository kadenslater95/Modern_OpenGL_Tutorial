#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"


void init();
void render();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// set up vertex data (and buffer(s)) and configure vertex attributes
float vertices1[] = {
  // triangle 1
  0.24f, -0.5f, 0.0f,  // bottom right
  -0.76f, -0.5f, 0.0f, // bottom left
  -0.26f,  0.5f, 0.0f,  // top
};

float vertices2[] = {
  // triangle 2
  -0.24f, 0.5f, 0.0f,  // top left
  0.76f, 0.5f, 0.0f, // top right
  0.26f,  -0.5f, 0.0f,  // bottom  
};

unsigned int VBO[2], VAO[2];

Shader *myShader;


int main(int argc, char **argv)
{
  // glfw: initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cout << "GLEW Error: " << glewGetErrorString(err) << "\n";
  }


  // build and compile our shader program
  myShader = new Shader("shader.vert", "shader.frag");


  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO[0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  glBindVertexArray(VAO[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  // glBindVertexArray(0);


  init();

  // render loop
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    render();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}


void init()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}


void render()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // render the triangle
  myShader->use();
  glBindVertexArray(VAO[0]);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  glBindVertexArray(VAO[1]);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
}