#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <SDL3/SDL_events.h>
#include "Scene5.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"
Scene5::Scene5() :sphere{ nullptr }, shader{ nullptr }, mesh{ nullptr },
drawInWireMode{ true } {
	Debug::Info("Created Scene5: ", __FILE__, __LINE__);
}

Scene5::~Scene5() {
	Debug::Info("Deleted Scene5: ", __FILE__, __LINE__);
}

bool Scene5::OnCreate() {
	Debug::Info("Loading assets Scene5: ", __FILE__, __LINE__);
	sphere = new Body();
	sphere->OnCreate();

	  heighttexture = new Texture();
	if (heighttexture->LoadImage("textures/terrainHeight.png", GL_TEXTURE0) == false) {
		std::cerr << "OH NO!\n";
		return false;
	}
	 diffusetexture = new Texture();
	 if (diffusetexture->LoadImage("textures/terrainDiffuse.png", GL_TEXTURE1) == false) {
		 std::cerr << "OH NO!\n";
		 return false;
	 }

	 normaltexture = new Texture();
	 if (normaltexture->LoadImage("textures/terrainNormal.png", GL_TEXTURE2) == false) {
		 std::cerr << "OH NO!\n";
		 return false;
	 }
	
	 lightPos = Vec3(0.0, 1.0, 0.0);





	mesh = new Mesh("meshes/Plane.obj");
	mesh->OnCreate();

	shader = new Shader("shaders/TessVert.glsl", "shaders/TessFrag.glsl",
		"shaders/TessCTRL.glsl", "shaders/TessEval.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = MMath::translate(Vec3(0.0f, 0.0f,0.0f)) * MMath::rotate(60.0f,Vec3(-1.0f, 0.0f, 0.0f)) * MMath::rotate(60.0f, Vec3(0.0f, 0.0f, -1.0f));
	
}

void Scene5::OnDestroy() {
	Debug::Info("Deleting assets Scene5: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	delete heighttexture;
	delete normaltexture;
	delete diffusetexture;
}

void Scene5::HandleEvents(const SDL_Event& sdlEvent) {
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

void Scene5::Update(const float deltaTime) {

}

void Scene5::Render() const {
	//wet the background color then clear the screen
	glClearColor(0.2f, 0.3f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.Render();
	if (drawInWireMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	glUseProgram(shader->GetProgram());

	

	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, heighttexture->getTextureID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, diffusetexture->getTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normaltexture->getTextureID());
	mesh->Render(GL_PATCHES);

	

	glUseProgram(0);
}




