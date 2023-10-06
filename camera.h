#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();

    glm::vec3 getPosition() { return cameraPos; }
    glm::vec3 getFront() { return cameraFront; }
    glm::vec3 getUp() { return cameraUp; }
    float getFov() { return cameraFov; }

    void setPosition(glm::vec3 pos) { cameraPos = pos; }
    void setFront(glm::vec3 front) { cameraFront = front; }
    void setFov(float f) { cameraFov = f; }

    void Update();

private:
    glm::vec3 cameraPos = glm::vec3(0.f, 10.f, -16.f);
    glm::vec3 cameraFront = glm::vec3(0.f, -10.f, 16.f);
    glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);
    float cameraFov = 90;

    int width;
    int height;

    double x = 0.0;
    double y = 10.0;
    double z = -16.0;
    glm::mat4 projection;
    glm::mat4 view;
};

#endif /* CAMERA_H */
