#include "graphics/glfw/glfw_drawer.h"
#include "shaders/fragment_shader.h"

GLFWDrawer::GLFWDrawer(size_t height, size_t width, vec3<> backgroundColor)
    : BaseDrawer(height, width, backgroundColor),
    _shaderProgramID(0),
    _window(nullptr),
    _isGLFWWindowCreated(false)
{
    
}

GLFWDrawer::~GLFWDrawer()
{

}


void GLFWDrawer::initScene()
{
    if (_isGLFWWindowCreated)
        return ;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    _window = glfwCreateWindow(_width, _height, "", NULL, NULL);
    if (_window == nullptr)
    {
        glfwTerminate();
        /* Throw exception */ //TODO
    }
    glfwMakeContextCurrent(_window);
    _isGLFWWindowCreated = true;

    glewInit();

	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);
	glViewport(0, 0, width, height);

    prepareShaderProgram();
}

void GLFWDrawer::resizeScene(size_t newHeight, size_t newWidth)
{
    _width = newWidth;
    _height = newHeight;
    _imageMatrix = math<>::image(_width, _height);

    _depthBuffer = std::make_shared<ZBuffer>(_height, _width);
    _frameBuffer = std::make_shared<FrameBuffer>(_height, _width, _backgroundColor);

    if (!_isGLFWWindowCreated)
        return ;

    glfwDestroyWindow(_window);
    _isGLFWWindowCreated = false;
    _window = glfwCreateWindow(_width, _height, "", NULL, NULL);
    if (_window == nullptr)
    {
        glfwTerminate();
        /* Throw exception */ //TODO
    }
    glfwMakeContextCurrent(_window);
    _isGLFWWindowCreated = true;

    int width, height;
	glfwGetFramebufferSize(_window, &width, &height);
	glViewport(0, 0, width, height);

    glDeleteProgram(_shaderProgramID);
    _shaderProgramID = 0;

    prepareShaderProgram();
}

void GLFWDrawer::swapBuffers()
{
    if (!_isGLFWWindowCreated)
        return ;

    GLfloat points[] = {
        -1.f, -1.f,  0.f,   0.f,  0.f,
         1.f, -1.f,  0.f,   1.f,  0.f,
         1.f,  1.f,  0.f,   1.f,  1.f,

        -1.f, -1.f,  0.f,   0.f,  0.f,
         1.f,  1.f,  0.f,   1.f,  1.f,
        -1.f,  1.f,  0.f,   0.f,  1.f
    };

    GLuint _VAOID, _VBOID;
    glGenVertexArrays(1, &_VAOID);
    glGenBuffers(1, &_VBOID);

    glBindBuffer(GL_ARRAY_BUFFER, _VBOID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindVertexArray(_VAOID);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    uint8_t *frameBufferData = getFrameBufferDataInBytes();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, frameBufferData);

    glUseProgram(_shaderProgramID);
    GLint textureLocation = glGetUniformLocation(_shaderProgramID, "texture1");
    glUniform1i(textureLocation, 0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(_VAOID);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(_window);

    delete frameBufferData;
    glDeleteProgram(_shaderProgramID);
	glDeleteBuffers(1, &_VBOID);
    glDeleteVertexArrays(1, &_VAOID);
    glDeleteTextures(1, &textureID);
}

void GLFWDrawer::terminateScene()
{
    if (_isGLFWWindowCreated)
       glfwDestroyWindow(_window);
    
    _isGLFWWindowCreated = false;
}


void GLFWDrawer::enableZBuffering()
{
    _isDepthTestingEnabled = true;
    glEnable(GL_DEPTH_TEST);
}

void GLFWDrawer::disableZBuffering()
{
    _isDepthTestingEnabled = false;
    glDisable(GL_DEPTH_TEST);
}

void GLFWDrawer::clearFrameBuffer()
{
    _frameBuffer->clearBuffer();
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLFWDrawer::clearZBuffer()
{
    _depthBuffer->clearBuffer();
    glClear(GL_DEPTH_BUFFER_BIT);
}


const char *vertexShaderCode =                  \
"#version 330 core\n"                           \
"out vec2 textureCoords;\n"                     \
"layout (location = 0) in vec3 pos;\n"          \
"layout (location = 1) in vec2 texCoords;\n"    \
"void main()\n"                                 \
"{\n"                                           \
"    textureCoords = texCoords;\n"              \
"    gl_Position = vec4(pos, 1.f);\n"           \
"}";

const char *fragmentShaderCode =                        \
"#version 330 core\n"                                   \
"out vec4 FragColor;\n"                                 \
"uniform sampler2D texture1;\n"                         \
"in vec2 textureCoords;\n"                              \
"void main()\n"                                         \
"{\n"                                                   \
"    FragColor = texture(texture1, textureCoords);\n"   \
"    //FragColor = vec4(1.f, 0.f, 0.f, 1.f);\n"   \
"}";

void GLFWDrawer::checkCompileErrors(unsigned int shader, GLObjectType type)
{
    int success;
    char infoLog[1024];
    if (type != GLObjectType::ShaderProgram)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            /* throw exception */
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            /* throw exception */
        }
    }
}

void GLFWDrawer::processInput()
{

}

void GLFWDrawer::prepareShaderProgram()
{
    const char* vShaderCode = vertexShaderCode;
    const char * fShaderCode = fragmentShaderCode;
    
    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, GLObjectType::Vertex);
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, GLObjectType::Fragment);
    
    _shaderProgramID = glCreateProgram();
    glAttachShader(_shaderProgramID, vertex);
    glAttachShader(_shaderProgramID, fragment);
    glLinkProgram(_shaderProgramID);
    checkCompileErrors(_shaderProgramID, GLObjectType::ShaderProgram);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


uint8_t* GLFWDrawer::getFrameBufferDataInBytes()
{
    uint8_t *data = new uint8_t[_height * _width * 3];
    if (data == nullptr)
    {
        throw BadAllocException(__FILE__, typeid(*this).name(), __LINE__,
            "Не удалось выделить память под копию буффера кадра");
    }

    size_t width_3 = _width * 3;
    size_t i_width_3 = 0;
    for (size_t i = 0; i < _height; i++)
    {
        size_t j3 = 0;
        for (size_t j = 0; j < _width; j++)
        {
            vec3<> clr = (*_frameBuffer)[i][j];
            data[j3 + i_width_3] = uint8_t(clr.r);
            data[j3 + i_width_3 + 1] = uint8_t(clr.g);
            data[j3 + i_width_3 + 2] = uint8_t(clr.b);
            j3 += 3;
        }
        i_width_3 += width_3;
    }

    return data;
}