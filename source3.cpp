
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<cmath>
using namespace std;



const char* vertexshadersource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"

"out vec3 ourcolor;\n"
"void main()\n"
"{\n"
   "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"

"}\0";


const char* fragmentshadersource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor= vec4(0.8f,0.9f,0.0f,1.0f);\n"
"}\n\0";


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;




	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() == GLEW_OK)
	{
		cout << "Yeah" << endl;
	}

	int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexshadersource, NULL);
	glCompileShader(vertexshader);
	int success;
	char infolog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentshadersource, NULL);
	glCompileShader(fragmentshader);
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
	}


	int program = glCreateProgram();
	glAttachShader(program, vertexshader);
	glAttachShader(program, fragmentshader);
	glLinkProgram(program);
	// check for linking errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
	}
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);



	float position[] = {
	0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
	};
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	/*float posi[] = {
	0.5f,-0.5f,0.0f,
	1.0f,0.5f,0.0f,
	1.5f,-0.5f,0.0f

	};*/
	unsigned int VBO;
	//unsigned int buf;
	unsigned int VAO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		/*float timevalue = glfwGetTime();
		float value = (sin(timevalue)/2.0f) + 0.5f;
		int vertexcolorlocation = glGetUniformLocation(program,"ourcolor");
		glUniform4f(vertexcolorlocation,value,0.0f,0.0f,1.0f);
		*/




		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
		/*glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		*/

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	glfwTerminate();
	return 0;
}