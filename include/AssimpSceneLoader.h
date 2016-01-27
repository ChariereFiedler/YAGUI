//
// Created by Patataa on 09/11/2015.
//

#ifndef YAGUI_SCENELOADER_H
#define YAGUI_SCENELOADER_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <memory>
namespace Loader {

    class AssimpSceneLoader {

    public:
        //std::vector<void(Builder::*)(const aiScene &)const> m_buildFunctions;

        AssimpSceneLoader(
                   )
                {}


        Scene * import(
                const std::string & file,
                const AssimpBuilder & builder,
                const unsigned int & flags = aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate            |
                                             aiProcess_JoinIdenticalVertices  |
                                             aiProcess_SortByPType) {

            Assimp::Importer importer;

            const aiScene *result =  importer.ReadFile(file, flags);

            if(!result)
                throw std::runtime_error("Unable to import the file");

            return builder.build(*result);
        }
    };
};

#endif //YAGUI_SCENELOADER_H
