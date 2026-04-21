#ifndef SCENE5_H
#define SCENE5_H
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
class Texture;

class Scene5 : public Scene {
private:
	Body* sphere;
	Shader* shader;
	Mesh* mesh;
	Texture* heighttexture;
	Texture* texture1;
	Texture* diffusetexture;
	Texture* normaltexture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	bool drawInWireMode;
	Vec3 lightPos;
	// Tesslevel;
	Camera camera;
public:
	explicit Scene5();
	virtual ~Scene5();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE4P_H
