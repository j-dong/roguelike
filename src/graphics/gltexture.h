#ifndef ROGUELIKE_INCLUDED_GRAPHICS_GLTEXTURE
#define ROGUELIKE_INCLUDED_GRAPHICS_GLTEXTURE

#include <GL/glew.h>

#include <lodepng.h>

#include <string>

namespace graphics {
    class GLTexture {
        GLuint id;
        static GLuint activeTexture; // used to optimize texture switching
    public:
        Texture(const std::string &fname);
        ~Texture();
        
        void activate();
        
        static void beginDraw(); // call before draw loop; resets active texture to 0
    };
}

#endif
