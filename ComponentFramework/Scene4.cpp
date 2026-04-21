#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <SDL3/SDL_events.h>
#include "Scene4.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"

Scene4::Scene4() :sphere{ nullptr }, shader{ nullptr }, mesh{ nullptr },
drawInWireMode{ true } {
	Debug::Info("Created Scene4TEST: ", __FILE__, __LINE__);
}

Scene4::~Scene4() {
	Debug::Info("Deleted Scene4: ", __FILE__, __LINE__);
}

bool Scene4::OnCreate() {
	Debug::Info("Loading assets Scene4: ", __FILE__, __LINE__);
	sphere = new Body();
	sphere->OnCreate();

	mesh = new Mesh("meshes/Plane.obj");
	mesh->OnCreate();
	
	shader = new Shader("shaders/TessVert.glsl", "shaders/TessFrag.glsl",
		"shaders/TessCTRL.glsl", "shaders/TessEval.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}
	
	projectionMatrix = MMath::perspective(35.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix.loadIdentity();
	return true;
}

void Scene4::OnDestroy() {
	Debug::Info("Deleting assets Scene4: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;


}
float tesslevel = 1.0f;
void Scene4::HandleEvents(const SDL_Event& sdlEvent) {
	switch (sdlEvent.type) {
	case SDL_EVENT_KEY_DOWN:
		switch (sdlEvent.key.scancode) {
		case SDL_SCANCODE_W:
			drawInWireMode = !drawInWireMode;
			break;

			switch (sdlEvent.key.scancode) {
			case SDL_SCANCODE_S:
				
				break;
			default:
				break;

				break;
			}
		}
	}
}

void Scene4::Update(const float deltaTime) {
	
}

void Scene4::Render() const {
	//wet the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.Render();
	if (drawInWireMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	
	//GLint loc = shader->GetUniformID("TessLevel");
	//glUniform1f(loc, tesslevel);
	//
	glUseProgram(shader->GetProgram());

	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	mesh->Render(GL_PATCHES);
	glUseProgram(0);
}




