#include "Renderer.h"

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
	heightMap = new HeightMap(TEXTUREDIR"noise.png");
	camera = new Camera(-45,0.0f, heightMap->GetHeightmapSize() * Vector3(0.5f,5.0f,0.5f));

	Vector3 dimensions = heightMap->GetHeightmapSize();
	camera->SetPosition(dimensions * Vector3(0.5, 2, 0.5));

	//shader = new Shader("PerPixelVertex.glsl ", "PerPixelFragment.glsl");
	shader = new Shader("bumpvertex.glsl ", "bumpfragment.glsl");
	if (!shader->LoadSuccess()) {
		return;
	}

	terrainTex = SOIL_load_OGL_texture(TEXTUREDIR "Barren Reds.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	bumpmap = SOIL_load_OGL_texture(TEXTUREDIR "Barren RedsDOT3.JPG",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (!terrainTex || !bumpmap) {
		return;

	}
	SetTextureRepeating(terrainTex, true);
	SetTextureRepeating(bumpmap, true);

	light = new Light(heightMap->GetHeightmapSize() * Vector3(0.5f, 1.5f, 0.5f),
		Vector4(1, 1, 1, 1), heightMap->GetHeightmapSize().x * 0.5f);

	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	init = true;
}

Renderer ::~Renderer(void) {
	delete heightMap;
	delete camera;
	delete shader;
	delete light;

}

void Renderer::UpdateScene(float dt) {
	camera->UpdateCamera(dt);
	viewMatrix = camera->BuildViewMatrix();
}

void Renderer::RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	BindShader(shader);

	glUniform1i(glGetUniformLocation(shader->GetProgram(),
		"diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrainTex);

	glUniform1i(glGetUniformLocation(shader->GetProgram(),
		"bumpTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpmap);
	glUniform3fv(glGetUniformLocation(shader->GetProgram(), "cameraPos"), 1, (float*)& camera->GetPosition());
	UpdateShaderMatrices();
	SetShaderLight(*light);
	heightMap->Draw();
}
