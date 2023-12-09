#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<cmath>
#include<stack>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<SOIL2/soil2.h>
#include"Utils.h"
#include"Sphere.h"
#include"Torus.h"
#include"ImportedModel.h"
#include<glm/gtx/quaternion.hpp>

using namespace std;

#define numVAOs 1
#define numVBOs 4

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
float pyramidLoc_X, pyramidLoc_Y, pyramidLoc_Z;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// display()関数で使用される変数を確保し、レンダリング中に確保する必要がないようにする。
GLuint mvLoc, projLoc, nLoc;
GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mAmbLoc, mDiffLoc, mSpecLoc, mShiLoc;

int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, invTrMat;
glm::vec3 currentLightPos, lightPosV; //
float lightPos[3];//照明の座標

glm::mat4 tMat, rMat;

ImportedModel Akyo("3Dmodel/teapot.obj");

//Torus torus;

glm::vec3 initialLightLoc = glm::vec3(0.0f, 5.0f, 10.0f);

//白い照明
float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

//マテリアルプロパティ
float* matAmb = Utils::goldAmbient();
float* matDif = Utils::goldDiffuse();
float* matSpe = Utils::goldSpecular();
float matShi = Utils::goldShininess();

void setupVertices()
{

	std::vector<glm::vec3> vert = Akyo.getVertices();
	std::vector<glm::vec2> tex = Akyo.getTextureCoords();
	std::vector<glm::vec3> norm = Akyo.getNormals();

	std::vector<float> pvalues;//頂点座標
	std::vector<float> tvalues;//テクスチャ座標
	std::vector<float> nvalues;//法線ベクトル

	int numObjVertices = Akyo.getNumVertices();

	//std::vector<int> indicies = Akyo.getIndices();

	for (int i = 0; i < numObjVertices; i++)
	{

		pvalues.push_back(vert[i].x);
		pvalues.push_back(vert[i].y);
		pvalues.push_back(vert[i].z);
								
		tvalues.push_back(tex[i].s);
		tvalues.push_back(tex[i].t);
								
		nvalues.push_back(norm[i].x);
		nvalues.push_back(norm[i].y);
		nvalues.push_back(norm[i].z);

	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);


}

void window_reshape_callback(GLFWwindow* window, int w, int h)
{
	glfwGetFramebufferSize(window, &width, &height);
	// フレームバッファ全体をビューポートに設定する
	glViewport(0, 0, width, height);

}

GLuint brickTexture = 0;

void init(GLFWwindow* window) 
{

	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 12.0f;

	cubeLocX = 0.0f;
	cubeLocY = -2.0f;
	cubeLocZ = 0.0f;

	pyramidLoc_X = 1.0f;
	pyramidLoc_Y = 3.0f;
	pyramidLoc_Z = 0.0f;

	glfwSetWindowSizeCallback(window, window_reshape_callback);

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

	//brickTexture = Utils::loadTexture("Textures/tex_akyo.png");

	//glBindTexture(GL_TEXTURE_2D, brickTexture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);

	//異方性フィルタリングの追加(グラボが対応している場合)
	/*
	if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
	{
		printf("異方性フィルタリングの有効化\n");
		GLfloat anisoSetting = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&anisoSetting);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
	}
	*/


	setupVertices();

}

float x = 0.0f;
float inc = 0.01f;

void installLights(glm::mat4 vMatrix)
{
	// convert light’s position to view space, and save it in a float array
	lightPosV = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0));
	lightPos[0] = lightPosV.x;
	lightPos[1] = lightPosV.y;
	lightPos[2] = lightPosV.z;

	// get the locations of the light and material fields in the shader
	globalAmbLoc = glGetUniformLocation(renderingProgram, "globalAmbient");
	ambLoc = glGetUniformLocation(renderingProgram, "light.ambient");
	diffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
	specLoc = glGetUniformLocation(renderingProgram, "light.specular");
	posLoc = glGetUniformLocation(renderingProgram, "light.position");
	mAmbLoc = glGetUniformLocation(renderingProgram, "material.ambient");
	mDiffLoc = glGetUniformLocation(renderingProgram, "material.diffuse");
	mSpecLoc = glGetUniformLocation(renderingProgram, "material.specular");
	mShiLoc = glGetUniformLocation(renderingProgram, "material.shininess");

	// set the uniform light and material values in the shader
	glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmbient);
	glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
	glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
	glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
	glProgramUniform3fv(renderingProgram, posLoc, 1, lightPos);
	glProgramUniform4fv(renderingProgram, mAmbLoc, 1, matAmb);
	glProgramUniform4fv(renderingProgram, mDiffLoc, 1, matDif);
	glProgramUniform4fv(renderingProgram, mSpecLoc, 1, matSpe);
	glProgramUniform1f(renderingProgram, mShiLoc, matShi);

}

glm::quat Euler(const float& x, const float& y, const float& z)
{
	//x
	float yaw = glm::radians(x);// x* (PI / 180.0f);
	//y
	float pitch = glm::radians(y); //y * (PI / 180.0f);
	//z
	float roll = glm::radians(z); //z * (PI / 180.0f);


	glm::quat eulerRot;

	eulerRot.x = sin(roll / 2) * cos(pitch / 2) * cos(yaw / 2) - cos(roll / 2) * sin(pitch / 2) * sin(yaw / 2);
	eulerRot.y = cos(roll / 2) * sin(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * cos(pitch / 2) * sin(yaw / 2);
	eulerRot.z = cos(roll / 2) * cos(pitch / 2) * sin(yaw / 2) - sin(roll / 2) * sin(pitch / 2) * cos(yaw / 2);
	eulerRot.w = cos(roll / 2) * cos(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * sin(pitch / 2) * sin(yaw / 2);

	return eulerRot;
}

glm::vec3 CameraRot = glm::vec3(0.0f);

std::stack<glm::mat4> mvStack;
void display(GLFWwindow* window, double currentTime)
{

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		cameraZ -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		cameraZ += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		cameraX -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		cameraX += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		cameraY += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
	{
		cameraY -= 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_P))
	{
		CameraRot.y += 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_O))
	{
		CameraRot.y -= 0.1f;
	}

	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);

	glUseProgram(renderingProgram);//シェーダーの利用を宣言

	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);

	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");

	//ビュー行列、モデル行列の構築、そしてその連結(MV行列の作成)
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	//vMat *= glm::toMat4(Euler(CameraRot.x, CameraRot.y, CameraRot.z));
	mvStack.push(vMat);
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
	mMat *= glm::rotate(mMat, (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	mMat *= glm::scale(glm::mat4(1.0f), glm::vec3(0.01f));
	mvMat = vMat * mMat;

	

	invTrMat = glm::transpose(glm::inverse(mvMat));

	currentLightPos = glm::vec3(initialLightLoc.x, initialLightLoc.y, initialLightLoc.z);
	installLights(vMat);
	

	//ピラミッドは親オブジェクト
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, 2));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 0.0f, 0.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(3.0f));


	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
	glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTexture);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glFrontFace(GL_CW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	//glDrawElements(GL_TRIANGLES, Akyo.getIndices().size(), GL_UNSIGNED_INT, 0);//ピラミッドを描画
	
	glDrawArrays(GL_TRIANGLES, 0, Akyo.getNumVertices());
	mvStack.pop();//太陽の軸回転をスタックから取り除く

	while (mvStack.size() > 0)
	{
		mvStack.pop();
	}

	glEnableVertexAttribArray(0);
}


int main(int argc, char** argv)
{


	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter4-program1", NULL, NULL);
	if (!window)
	{
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window))
	{
		if (width > 0 && height > 0) 
		{
			display(window, glfwGetTime());
			glfwSwapBuffers(window);
		}
		glfwPollEvents();
	}

	std::cout << "It's exit." << std::endl;

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}
