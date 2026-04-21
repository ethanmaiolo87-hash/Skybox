#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <SDL3/SDL_events.h>
#include "Scene0g.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"

Scene0g::Scene0g() :sphere{nullptr}, shader{nullptr}, mesh{nullptr},
					drawInWireMode{false} {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0g::~Scene0g() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene0g::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	sphere = new Body();
	sphere->OnCreate();
	
	mesh = new Mesh("meshes/hatsunemiku.obj");
	mesh->OnCreate();

	skullMesh = new Mesh("meshes/Skull.obj");
	skullMesh->OnCreate();

	shader = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print("View matrix");
	
	lightPos = Vec3(-3.0f,0.0f, 0.0f);

	/*earthTexture = new Texture();
	if (earthTexture->LoadImage("textures/miku.png") == false) {
		std::cerr << "OH NO!\n";
		return false;
	}

	moonTexture = new Texture();
	if (moonTexture->LoadImage("textures/moon.jpg") == false) {
		std::cerr << "OH NO!\n";
		return false;
	}

	skullTexture = new Texture();
	if (skullTexture->LoadImage("textures/skull_texture.jpg") == false) {
		std::cerr << "OH NO!\n";
		return false;
	}*/

	return true;
}

void Scene0g::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;

	skullMesh->OnDestroy();
	delete skullMesh;

	shader->OnDestroy();
	delete shader;

	delete earthTexture;
	delete moonTexture;
	delete skullTexture;
	
}

void Scene0g::HandleEvents(const SDL_Event &sdlEvent) {
	trackball.HandleEvents(sdlEvent);
	switch (sdlEvent.type) {
	case SDL_EVENT_KEY_DOWN:
		switch (sdlEvent.key.scancode) {
			case SDL_SCANCODE_W:
				drawInWireMode = !drawInWireMode;
				break;
			default:
				break;
		}
		break;
	}
}

void Scene0g::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;
	earthModelMatrix = MMath::translate(Vec3(0.0f, 0.0f, 0.0f)) *
		MMath::rotate(10.0f * totalTime, Vec3(0.0f, 1.0f, 0.0f));
		MMath::rotate(-90.0f,Vec3(1.0f,0.0f,0.0f));

	moonModelMatrix = 
		MMath::translate(3.0f, 0.0f, 0.0f) *
		MMath::scale(0.24f, 0.24f, 0.24) *
		MMath::rotate(20.0f*totalTime,Vec3(0.0f,1.0f,0.0f));

	skullModelMatrix = MMath::translate(3.0f, 0.0f, 0.0f) *
		MMath::scale(0.24f, 0.24f, 0.24);
	
}

void Scene0g::Render() const {
	glEnable(GL_DEPTH_TEST);
	 //Set the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(drawInWireMode){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glUseProgram(shader->GetProgram());

	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	Matrix4 rotation = MMath::toMatrix4(trackball.getQuat());
	
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, earthModelMatrix * rotation);
	glBindTexture(GL_TEXTURE_2D, earthTexture->getTextureID());
	mesh->Render(GL_TRIANGLES);


	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, earthModelMatrix * moonModelMatrix);
	glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	mesh->Render(GL_TRIANGLES);


	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, earthModelMatrix * moonModelMatrix * skullModelMatrix);
	glBindTexture(GL_TEXTURE_2D, skullTexture->getTextureID());
	skullMesh->Render(GL_TRIANGLES);


	glBindTexture(GL_TEXTURE_2D,0);
	glUseProgram(0);
}



	
