#ifndef SCENE4_H
#define SCENE4_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
#include "Camera.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;

class Scene4 : public Scene {
private:
	Body* sphere;
	Shader* shader;
	Mesh* mesh;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	bool drawInWireMode;
	float Tesslevel;
	Camera camera;
public:
	explicit Scene4();
	virtual ~Scene4();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE4P_H