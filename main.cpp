#include <windows.h>
#include <chrono>
//OpenGL
#include <glfw/glfw3.h>
//IMAGES
#define STB_IMAGE_IMPLEMENTATION
#include <stb-image/stb_image.h>
//Константы
const int _SCREEN_WIDTH = 1280;
const int _SCREEN_HEIGHT = 720;
//Движок
#include <core/PFX_Context.h>
#include <core/PFX_Controls.h>

auto lastTime = std::chrono::high_resolution_clock::now();
float deltaTime = 0.0f;

void LockToCore(int coreId) {
    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    // 1. (Опционально) Привязываем весь процесс к определённым ядрам
    // Например, разрешаем использовать только ядра 0-7 (первый CCD)
    DWORD_PTR processAffinityMask = 0xFF; // 11111111 в двоичной (ядра 0-7)
    SetProcessAffinityMask(process, processAffinityMask);

    // 2. Привязываем конкретный поток рендера к одному ядру (например, 0)
    DWORD_PTR threadAffinityMask = 1ull << coreId; // Ядро coreId
    SetThreadAffinityMask(thread, threadAffinityMask);

    // Повышаем приоритет потока, чтобы ОС меньше дёргала
    SetThreadPriority(thread, THREAD_PRIORITY_HIGHEST);
}

// Обработка клавиатуры
void Callback_keyboard( GLFWwindow* window , int key , int scancode , int action , int mode );
// Обработка мышки
void Callback_mouse( GLFWwindow* window , double xpos , double ypos );

PFX_Controls control;

int main() {
    glfwInit();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode( monitor );
    glfwWindowHint( GLFW_RESIZABLE , GL_FALSE );
    glfwWindowHint( GLFW_DECORATED , NULL );
    glfwWindowHint( GLFW_RED_BITS , mode->redBits );
    glfwWindowHint( GLFW_GREEN_BITS , mode->greenBits );
    glfwWindowHint( GLFW_BLUE_BITS , mode->blueBits );
    glfwWindowHint( GLFW_REFRESH_RATE , mode->refreshRate );

    //Окно
    GLFWwindow* window = glfwCreateWindow( _SCREEN_WIDTH , _SCREEN_HEIGHT , "Game" , nullptr , nullptr );
    LockToCore( 0 );
    //Иниты GL
    glfwMakeContextCurrent( window );
    glfwSwapInterval( 0 );
    glfwSetKeyCallback( window , Callback_keyboard );
    glfwSetCursorPosCallback( window , Callback_mouse );
    //Контекст, нужен для работы движка и обмена данными
    PFX_Context& context = PFX_Context::GetInstance();
    context.InitConfig( _SCREEN_WIDTH , _SCREEN_HEIGHT );
    context.InitProjection();
    context.InitCamera();
    context.InitRender( window );
    context.InitPlayer();
    context.InitEngine();
    control.SetPlayer( context.Player() );
    //Объект уровня, грузим уровень
    PFX_Level& level = context.Level();
//    level.LoadData( 0 );
    //Сам объект движка, для обновлений и вывода
    PFX_Engine& engine = context.Engine();
    level.SetSizes( 5.0f , 0.0f , 5.0f );
 //   glfwSetWindowMonitor( window , monitor , 0 , 0 , _SCREEN_WIDTH , _SCREEN_HEIGHT , 0 );

 //   GLFWmonitor* MyMonitor =  glfwGetPrimaryMonitor(); // The primary monitor.. Later Occulus?..
//    const GLFWvidmode* mode = glfwGetVideoMode(MyMonitor);
//
//    glfwSetWindowSize ( window , mode->width , mode->height );

    //Основной цикл
    while ( !glfwWindowShouldClose( window ) )
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        LUT_TIME_DELTA = std::chrono::duration<float>( currentTime - lastTime ).count();
        lastTime = currentTime;

        // Ограничиваем deltaTime, чтобы при отладке не улететь в космос
        if ( LUT_TIME_DELTA > 0.1f ) LUT_TIME_DELTA = 0.1f;  // Максимум 100 мс

        glfwPollEvents();
        control.Update();
        engine.Update();
        engine.Draw();
    }
    glfwTerminate();
   // delete context;
    return 0;
}
// Is called whenever a key is pressed/released via GLFW
void Callback_keyboard( GLFWwindow* window , int key , int scancode , int action , int mode ) {
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose( window , GL_TRUE );

    control.Input( key , action );
}
// The MAIN function, from here we start the application and run the game loop
void Callback_mouse( GLFWwindow* window , double xpos , double ypos ) {
//    //Мышка
//    Mouse* mouse          = Mouse::getInstance();
//    glm::vec2 mouseOffset = mouse->GetOffset( xpos , ypos );
//    //Камера
//    Camera* camera = Camera::getInstance();
//    camera->SetYaw( mouseOffset.x );
//    camera->SetPitch( mouseOffset.y );
//    camera->Rotate();
}
