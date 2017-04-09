#include "widget.h"

#include <SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

Widget::~Widget()
{

}

static const GLfloat g_vertex_buffer_data[] = {
	// Positions          // Colors           // Texture Coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
};

static GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3,  // First Triangle
	1, 2, 3   // Second Triangle
};


GLuint vertexbuffer;
GLuint VertexArrayID;

void Widget::initializeGL()
{
    makeCurrent();
    glewExperimental=true;
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        std::cerr << glewGetErrorString(err);
    }

    std::cerr << "using OpenGL " << format().majorVersion() << "." << format().minorVersion() << "\n";

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	m_shader = std::make_shared<Shader>("Shader//texture.vs", "Shader//texture.frag");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program.programId());
	GLuint VBO,  EBO;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

						  // Load and create a texture 

	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &m_texture1);
	glBindTexture(GL_TEXTURE_2D, m_texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("Image//container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glGenTextures(1, &m_texture2);
	glBindTexture(GL_TEXTURE_2D, m_texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("Image//awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Widget::paintGL()
{
	m_shader->Use();

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	// Get matrix's uniform location and set matrix
	GLint transformLoc = glGetUniformLocation(m_shader->Program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	glUniform1i(glGetUniformLocation(m_shader->Program, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2);
	glUniform1i(glGetUniformLocation(m_shader->Program, "ourTexture2"), 1);
	
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}
