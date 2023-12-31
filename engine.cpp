

#include "engine.h"
#include "glm/ext.hpp"

Engine* engine;

// Global variables
float lastX = 0, lastY = 0;
float yaw, pitch;
bool firstMouse = true;

Engine::Engine(const char* name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
}


Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT);
  if(!m_window->Initialize())
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  m_camera = m_graphics->getCamera();
  engine = this;

  glfwSetCursorPosCallback(m_window->getWindow(), cursorPositionCallBack);
  //glfwSetScrollCallback(m_window->getWindow(), scroll_wheel_callback);

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while (!glfwWindowShouldClose(m_window->getWindow()))
  {
      ProcessInput();
      Display(m_window->getWindow(), glfwGetTime());
      glfwSetScrollCallback(m_window->getWindow(), scroll_callback);
      glfwPollEvents();
  }
  m_running = false;

}

void Engine::ProcessInput()
{

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->getWindow(), true);


    // Update camera animation here.
    float cameraSpeed = .05f;
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        m_camera->setPosition(m_camera->getPosition() + (cameraSpeed * m_camera->getUp()));
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        m_camera->setPosition(m_camera->getPosition() - (cameraSpeed * m_camera->getUp()));
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_graphics->getCamera()->setPosition(m_graphics->getCamera()->getPosition() - (glm::normalize(glm::cross(m_graphics->getCamera()->getFront(), m_graphics->getCamera()->getUp())) * cameraSpeed));

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_graphics->getCamera()->setPosition(m_graphics->getCamera()->getPosition() + (glm::normalize(glm::cross(m_graphics->getCamera()->getFront(), m_graphics->getCamera()->getUp())) * cameraSpeed));


    m_camera->Update();
}

void Engine::adjustZoom(double yoffset)
{
    m_camera->setFov(m_camera->getFov() - (float)yoffset);
    if (m_camera->getFov() < 1.0f)
        m_camera->setFov(1.0f);
    if (m_camera->getFov() > 90.0f)
        m_camera->setFov(90.0f);

    m_camera->Update();
}

void Engine::scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "Position: (" << xpos << ":" << ypos << ")";
    engine->adjustZoom(ypos);
}

void Engine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
 
    glfwGetCursorPos(window, &xpos, &ypos);
    std::cout << "Position: (" << xpos << ":" << ypos << ")";
}

double Engine::getDT()
{
  //long long TimeNowMillis = GetCurrentTimeMillis();
  //assert(TimeNowMillis >= m_currentTimeMillis);
  //unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  //m_currentTimeMillis = TimeNowMillis;
  //return DeltaTimeMillis;
    return glfwGetTime();
}

long long Engine::GetCurrentTimeMillis()
{
  //timeval t;
  //gettimeofday(&t, NULL);
  //long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  //return ret;
    return (long long) glfwGetTime();
}

void Engine::Display(GLFWwindow* window, double time) {

    m_graphics->Render();
    m_window->Swap();
    m_graphics->HierarchicalUpdate2(time);
}

static void cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos) {
    cout << xpos << " " << ypos << endl;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f; 
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    engine->getCamera()->setFront(glm::normalize(front));
}

static void scrollWheelCallBack(GLFWwindow* window,  double ypos)
{
    //engine->adjustZoom(ypos);
}