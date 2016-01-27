//
// Created by Patataa on 09/11/2015.
//

#ifndef YAGUI_ASSIMPBUILDABLE_H
#define YAGUI_ASSIMPBUILDABLE_H


#include <wchar.h>

namespace Loader {

    enum E_BuildFlag {
        MESHES      = 1 << 0,
        CAMERAS     = 1 << 1,
        LIGHTS      = 1 << 2,
        MATERIALS   = 1 << 3,
        TEXTURES    = 1 << 4,
        ANIMATIONS  = 1 << 5,
        ALL         = true
    };

    class Builder{

    protected:
        E_BuildFlag m_buildFlag;

    public:
        Builder(const E_BuildFlag & buildFlag = ALL){};
        virtual ~Builder(){} ;

        /*
        template<typename Mesh>
        virtual Mesh * createMesh(const T &) = 0;

        template<typename Material>
        virtual Material * createMaterial(const T &) = 0;

        template <typename Camera>
        virtual Camera * createCamera(const T & ) = 0;

        template<typename Map>
        virtual Map * build(const T & ) = 0;

         */
    };
}
#endif //YAGUI_ASSIMPBUILDABLE_H
