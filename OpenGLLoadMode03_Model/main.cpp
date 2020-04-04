#define GLEW_STATIC           ////////////////////5
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//����OpenGL��ѧ�����
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"
#pragma region Model Data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
//EBO����
unsigned int indices[] = {
	0,1,2,
	2,3,0
};
//10���������ƽ������
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region Camera Declare
//ȫ��camera
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
//ƽ�й�
LightDirectional lightD(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0));
//���Դ
LightPoint lightP0(glm::vec3(1.0f, .0f, .0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
LightPoint lightP1(glm::vec3(.0f, 1.0f, .0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
LightPoint lightP2(glm::vec3(.0f, .0f, 1.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 0.0f, 10.0f));
LightPoint lightP3(glm::vec3(1.0f, 3.0f, -.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));
//�۹��
LightSpot lightS(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion
#pragma endregion

#pragma region Input Declare
//���λ��
float lastX;
float lastY;
bool firstMouse = true;
//������ƺ�������
void processInput(GLFWwindow* window);
//���ص���������
void mouse_callback(GLFWwindow* window,double xPos,double yPos);
//���ֻص���������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//ͼƬ���غ�������
unsigned int loadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot, bool flipped);
#pragma endregion

int main(int argc,char** argv) {
	string path = argv[0];
	path = path.substr(0, path.find_last_of('\\'));
	path = path.substr(0, path.find_last_of('\\')) + "\\Model\\nanosuit.obj";
	#pragma region Open Window
	//��ʼ��
	glfwInit();
	//���ð汾3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ���������", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//�󶨴��ڵ���ǰ�߳�
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	//���ù��
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//ע������¼��ص�����
	glfwSetCursorPosCallback(window, mouse_callback);
	//ע�Ử���¼��ص�����
	glfwSetScrollCallback(window, scroll_callback);
	//���û�ͼ����
	glViewport(0, 0, 800, 600);
	//���ñ����޳� ��ʱ�����Ϊ����
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//����ֻ��������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//������Ȳ���  �ڵ��Ĳ�λ������Ƴ���
	glEnable(GL_DEPTH_TEST);
#pragma endregion

	#pragma region Init Shader Program
	Shader* pshader = new Shader("vertextSource.vert", "fragmentSource.frag");
	pshader->print();
#pragma endregion 

#pragma region Init Material
	/*Material* myMaterial = new Material(pshader,
		loadImageToGPU("container.png",GL_RGB,GL_RGB,Shader::DIFFUSE,true),
		loadImageToGPU("container_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR, false),
		loadImageToGPU("matrix.jpg", GL_RGB, GL_RGB, Shader::EMISSION, false),
		glm::vec3(1.0f, 1.0f, 1.0f), 
		32.0f);*/
#pragma endregion

	#pragma region Init and Load Models to VAO,VBO
	//Mesh cube(vertices);
	Model model(path);
	/*unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);*/

	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	//��layout(location=0)�� lacation ������λ��һ����0-15��
	//λ������
	//glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(15);
	////��ɫ����
	////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	////glEnableVertexAttribArray(1);
	////uv����
	//glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(7);
	////������
	//glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(9);
#pragma endregion 
	
	#pragma region Init and Load Texture
	/*unsigned int TexBufferA;
	TexBufferA = loadImageToGPU("box.jpg", GL_RGB, GL_RGB, 0, false);

	unsigned int TexBufferB;
	TexBufferB = loadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 13,true);*/
#pragma endregion 

	#pragma region Prepare MVP Matrices
	//�ֲ�����ת��������  ģ�;���
	glm::mat4 modelMat;
	
	//��������ת�������  �۲����
	glm::mat4 viewMat;
	
	//�������ת��Ļ���꣨2D��ͶӰ����
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion 

	#pragma region Render Loop
	while (!glfwWindowShouldClose(window))
	{
		//Process input
		processInput(window);
		//Clear screen
		glClearColor(0.01, 0.01, 0.01, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (size_t i = 0; i < 1; i++)
		{
			//set Model Matrix
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			//��ת
			/*if (i % 3 < 2) {
				modelMat = glm::rotate(modelMat, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			}*/
			//Set View and Projection here
			viewMat = camera.GetViewMatrix();

			//Set Material ->Shader Program
			pshader->use();

			//Set Material ->Texture
		/*	glActiveTexture(GL_TEXTURE0+Shader::DIFFUSE);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			glActiveTexture(GL_TEXTURE0+ Shader::SPECULAR);
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
			glActiveTexture(GL_TEXTURE0 + Shader::EMISSION);
			glBindTexture(GL_TEXTURE_2D, myMaterial->emission);*/

			//Set Material ->Unifrom
			//uniform����texture��ͼ����
			/*glUniform1i(glGetUniformLocation(pshader->ID, "ourTextrue"), 0);
			glUniform1i(glGetUniformLocation(pshader->ID, "ourFace"), 13);*/
			//uniform������תλ�Ƶȱ任�������ͶӰ
			glUniformMatrix4fv(glGetUniformLocation(pshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(pshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(pshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			//����������ɫ�ͻ�������ɫ
			glUniform3f(glGetUniformLocation(pshader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(pshader->ID, "ambientColor"), .3f, .3f, .3f);
			//ƽ�й�
			glUniform3f(glGetUniformLocation(pshader->ID, "lightD.color"), lightD.color.r, lightD.color.g, lightD.color.b);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightD.dirToLight"), lightD.direction.x, lightD.direction.y, lightD.direction.z);
			//���Դ0
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[0].pos"), lightP0.postion.x, lightP0.postion.y, lightP0.postion.z);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[0].color"), lightP0.color.r, lightP0.color.g, lightP0.color.b);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[0].constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[0].linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[0].quadratic"), lightP0.quadratic);
			//���Դ1
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[1].pos"), lightP1.postion.x, lightP1.postion.y, lightP1.postion.z);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[1].color"), lightP1.color.r, lightP1.color.g, lightP1.color.b);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[1].constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[1].linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[1].quadratic"), lightP1.quadratic);
			//���Դ2
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[2].pos"), lightP2.postion.x, lightP2.postion.y, lightP2.postion.z);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[2].color"), lightP2.color.r, lightP2.color.g, lightP2.color.b);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[2].constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[2].linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[2].quadratic"), lightP2.quadratic);
			//���Դ3
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[3].pos"), lightP3.postion.x, lightP3.postion.y, lightP3.postion.z);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightP[3].color"), lightP3.color.r, lightP3.color.g, lightP3.color.b);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[3].constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[3].linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP[3].quadratic"), lightP3.quadratic);
			//�۹��
			glUniform3f(glGetUniformLocation(pshader->ID, "lightS.pos"), lightS.postion.x, lightS.postion.y, lightS.postion.z);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightS.color"), lightS.color.r, lightS.color.g, lightS.color.b);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightS.quadratic"), lightS.quadratic);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightS.cosPhyOutter"), lightS.cosPhyOutter);

			glUniform3f(glGetUniformLocation(pshader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			//����material
			//glUniform3f(glGetUniformLocation(pshader->ID, "material.ambient"), 1.0f, 1.0f, 1.0f);
			//myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			////myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			////myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			//myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			//myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			//myMaterial->shader->SetUniform1i("material.emission", Shader::EMISSION);
			//myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
			//Draw Call VBO��ʽ����
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			//cube.Draw(pshader);
			model.Draw(pshader);
		}
		//Clean up,prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdateCameraPos();

	}
#pragma endregion

	//Exit Programe
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.speedZ = -1.0f;
	}
	else {
		camera.speedZ = .0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.speedX = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedX = -1.0f;
	}
	else {
		camera.speedX = .0f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.speedY = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.speedY = -1.0f;
	}
	else {
		camera.speedY = .0f;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = lastX- xpos;
	float yoffset = lastY- ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.speedZ = yoffset*100;
}

unsigned int loadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot, bool flipped)
{
	//���µߵ�texture��ͼ
	stbi_set_flip_vertically_on_load(flipped);
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	int width, height, numChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &numChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "load image failed0." << std::endl;
	}
	stbi_image_free(data);
	return TexBuffer;
}
