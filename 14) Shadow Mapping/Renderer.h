#pragma once
#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/HeightMap.h"
#include "../nclgl/Light.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window& parent);
	~Renderer(void);

	void UpdateScene(float dt) override;
	void RenderScene() override;

protected:
	void DrawShadowScene();
	void DrawMainScene();
	
	GLuint shadowTex;
	GLuint shadowFBO;
	GLuint sceneDiffuse;
	GLuint sceneBump;
	float sceneTime;
	
	Shader * sceneShader;
	Shader * shadowShader;
	
	vector < Mesh* > sceneMeshes;
	vector < Matrix4 > sceneTransforms;

	Camera* camera;
	Light* light;
};