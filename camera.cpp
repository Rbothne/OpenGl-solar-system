#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
    width = w, height = h;
    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    //view = glm::lookAt( glm::vec3(x, y, z), //Eye Position
    //                    glm::vec3(0.0, 0.0, 0.0), //Focus point
    //                    glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);

    projection = glm::perspective(glm::radians(90.f), //the FoV typically 90 degrees is good which is what this is set to
        float(width) / float(height), //Aspect Ratio, so Circles stay Circular
        0.01f, //Distance to the near plane, normally a small value like this
        100.0f); //Distance to the far plane, 
    return true;
}

void Camera::Update() { //, glm::vec3 front)
    //cameraFront = front;
    view = glm::lookAt(cameraPos, //Eye Position
        cameraPos + cameraFront, //Focus point
        cameraUp); //Positive Y is up
    projection = glm::perspective(glm::radians(cameraFov), 
        float(width) / float(height), 
        0.01f, 
        100.0f); 
}

glm::mat4 Camera::GetProjection()
{
    return projection;
}

glm::mat4 Camera::GetView()
{
    return view;
}
