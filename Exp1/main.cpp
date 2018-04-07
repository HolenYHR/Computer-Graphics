#include "shader_s.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

double Area(double x1, double y1, double x2, double y2, double x3, double y3);
bool ToLeft(double x1, double y1, double x2, double y2, double x3, double y3);
int which_selected(double xPos, double yPos);

float prevx;
float prevy;
double prevxx;
double prevyy;

//这个变量是确定哪个物体被选中的
//值可以为-1(没有物体被选中),0,1,2
int whichSelect;
//分别代表x,y,z位置的偏移
float X[3] = { 0};
float Y[3] = { 0 };
float Z[3] = { 0 };

float XX[3] = { 0 };
float YY[3] = { 0 };
float ZZ[3] = { 0 };

float XXX[3] = { 0 };
float YYY[3] = { 0 };
float ZZZ[3] = { 0 };

bool lbutton = false;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


float vertices[] = {
	// positions         // colors
	-0.7f, 0.2f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.3f, 0.2f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	-0.5f,  0.6f, 0.0f,  0.0f, 0.0f, 1.0f ,  // top 

};
float vertices2[] = {

	0.3f,0.2f,0.0f, 0.0f, 1.0f, 0.0f,
	0.7f,0.2f,0.0f, 1.0f, 0.0f, 0.0f,
	0.5f,0.6f,0.0f,0.0f, 0.0f, 1.0f
};

float vertices3[] = {
	-0.2f,-0.2f,0.0f,
	-0.2f,-0.8f,0.0f,
	0.2f,-0.2f,0.0f,
	0.2f,-0.2f,0.0f,
	0.2f,-0.8f,0.0f,
	-0.2f,-0.8f,0.0f

};



float vertices_c[] = {
	// positions         // colors
	-0.7f, 0.2f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.3f, 0.2f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	-0.5f,  0.6f, 0.0f,  0.0f, 0.0f, 1.0f ,  // top 

};
float vertices2_c[] = {

	0.3f,0.2f,0.0f, 0.0f, 1.0f, 0.0f,
	0.7f,0.2f,0.0f, 1.0f, 0.0f, 0.0f,
	0.5f,0.6f,0.0f,0.0f, 0.0f, 1.0f
};

float vertices3_c[] = {
	-0.2f,-0.2f,0.0f,
	-0.2f,-0.8f,0.0f,
	0.2f,-0.2f,0.0f,
	0.2f,-0.2f,0.0f,
	0.2f,-0.8f,0.0f,
	-0.2f,-0.8f,0.0f

};
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("3.3.shader.vs", "3.3.shader.fs"); // you can name your shader files however you like

														// set up vertex data (and buffer(s)) and configure vertex attributes
														// ------------------------------------------------------------------
	
	unsigned int VBOs[3], VAOs[3];
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAOs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	glBindVertexArray(VAOs[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute


	// render loop
	// -----------
	// In your CPP file:
	// ======================




	
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		glm::mat4 transform[3];
		transform[0] = glm::translate(transform[0], glm::vec3(XX[0], YY[0], ZZ[0]));
		transform[0] = glm::translate(transform[0], glm::vec3(X[0], Y[0], Z[0]));
		transform[1] = glm::translate(transform[1], glm::vec3(XX[1], YY[1], ZZ[1]));
		transform[1] = glm::translate(transform[1], glm::vec3(X[1], Y[1], Z[1]));
		transform[2] = glm::translate(transform[2], glm::vec3(XX[2], YY[2], ZZ[2]));
		transform[2] = glm::translate(transform[2], glm::vec3(X[2], Y[2], Z[2]));

		//transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));


		// render the triangle
		ourShader.use();
		
		for (int i = 0; i < 3; i++)
		{
			unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform[i]));
			glBindVertexArray(VAOs[i]);
			if (i != 2)
				glDrawArrays(GL_TRIANGLES, 0, 3);
			else
				glDrawArrays(GL_TRIANGLES, 0, 6);

		}
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	//std::cout << xPos << " " << yPos << std::endl;
	if (lbutton)
	{
		double x1 = xPos / 400 - 1;
		double y1 = -(yPos / 300 - 1);
		double x2 = prevx / 400 - 1;
		double y2 = -(prevy / 300 - 1);
		
		if (whichSelect >= 0)
		{
			X[whichSelect] = x1 - x2;
			
			Y[whichSelect] = y1 - y2;

			//if (whichSelect == 0)
			//{
			//	std::cout << "hahahhaha" << std::endl;
			//	vertices_c[0] += chax;
			//	vertices_c[1] += chay;
			//	vertices_c[6] += chax;
			//	vertices_c[7] += chay;
			//	vertices_c[12] += chax;
			//	vertices_c[13] += chay;

			//	//std::cout << vertices_c[0] << std::endl;
			//	//std::cout << vertices_c[1] << std::endl;
			//	//std::cout << vertices_c[6] << std::endl;
			//	//std::cout << vertices_c[7] << std::endl;
			//	//std::cout << vertices_c[12] << std::endl;
			//	//std::cout << vertices_c[13] << std::endl;
			//}
			//else
			//	if (whichSelect == 1)
			//	{
			//		vertices2_c[0] += chax;
			//		vertices2_c[1] += chay;
			//		vertices2_c[6] += chax;
			//		vertices2_c[7] += chay;
			//		vertices2_c[12] += chax;
			//		vertices2_c[13] += chay;
			//	}
			//	else
			//		if (whichSelect == 2)
			//		{
			//			vertices3_c[0] += chax;
			//			vertices3_c[1] += chay;
			//			vertices3_c[3] += chax;
			//			vertices3_c[4] += chay;
			//			vertices3_c[6] += chax;
			//			vertices3_c[7] += chay;
			//			vertices3_c[12] += chax;
			//			vertices3_c[13] += chay;
			//		}
			//
		}
	}

	
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		double x;
		double y;
		glfwGetCursorPos(window, &x, &y);
		double xx = x / 400 - 1;
		double yy = -(y / 300 - 1);
		

		
		whichSelect = which_selected(xx, yy);
		if (whichSelect >= 0)
		{
			for (int i = 0; i < 3; i++)
			{
				XXX[i] = XX[i];
				YYY[i] = YY[i];
			}

		}
		std::cout << "which " << whichSelect << std::endl;
		if (GLFW_PRESS == action)
		{
			
			//float x1=vertice
			lbutton = true;
			
			prevx = x;
			prevy = y;
			
		}
		else if (GLFW_RELEASE == action)
		{
			lbutton = false;
			for (int i = 0; i < 3; i++)
			{
				XX[i] += X[i];
				YY[i] += Y[i];
				X[i] = Y[i] = 0;
			}
			
		}
	}

}


int which_selected(double xPos, double yPos)
{
	int inwhich = -1;
	if (ToLeft(vertices_c[0]+XX[0], vertices_c[1]+YY[0], vertices_c[6]+XX[0], vertices_c[7]+YY[0], xPos, yPos) &&
		ToLeft(vertices_c[6]+XX[0], vertices_c[7]+YY[0], vertices_c[12]+XX[0], vertices_c[13]+YY[0], xPos, yPos) &&
		ToLeft(vertices_c[12]+XX[0], vertices_c[13]+YY[0], vertices_c[0]+XX[0], vertices_c[1]+YY[0], xPos, yPos))
		inwhich = 0;
	else
		if (ToLeft(vertices2_c[0]+XX[1], vertices2_c[1]+YY[1], vertices2_c[6]+XX[1], vertices2_c[7]+YY[1], xPos, yPos) &&
			ToLeft(vertices2_c[6]+XX[1], vertices2_c[7]+YY[1], vertices2_c[12]+XX[1], vertices2_c[13]+YY[1], xPos, yPos) &&
			ToLeft(vertices2_c[12]+XX[1], vertices2_c[13]+YY[1], vertices2_c[0]+XX[1], vertices2_c[1]+YY[1], xPos, yPos))
			inwhich = 1;
		else
			if (ToLeft(vertices3_c[0]+XX[2], vertices3_c[1]+YY[2], vertices3_c[3]+XX[2], vertices3_c[4]+YY[2], xPos, yPos) &&
				ToLeft(vertices3_c[3]+XX[2], vertices3_c[4]+YY[2], vertices3_c[12]+XX[2], vertices3_c[13]+YY[2], xPos, yPos) &&
				ToLeft(vertices3_c[12]+XX[2], vertices3_c[13]+YY[2], vertices3_c[6]+XX[2], vertices3_c[7]+YY[2], xPos, yPos) &&
				ToLeft(vertices3_c[6]+XX[2], vertices3_c[7]+YY[2], vertices3_c[0]+XX[2], vertices3_c[1]+YY[2], xPos, yPos))
				inwhich = 2;
	return inwhich;
}
bool ToLeft(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return Area(x1, y1, x2, y2, x3, y3) > 0;
}

double Area(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return x1*y2 - y1*x2
		+ x2*y3 - y2*x3
		+ x3*y1 - y3*x1;
}
