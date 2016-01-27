//
// Created by Patataa on 16/11/2015.
//

#ifndef YAGUI_ASSIMPBUILDER_H
#define YAGUI_ASSIMPBUILDER_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <memory>
#include "Builder.h"
#include "Camera.h"
#include "Scene.h"

namespace Loader {


    class AssimpBuilder : public Builder{

    public:
        AssimpBuilder(const E_BuildFlag & buildFlag = ALL):
                Builder(buildFlag){}

        virtual ~ AssimpBuilder(){}


        //TODO: add the Materials, Uv mapping, Animations and Bones
        void importMesh(Scene * map, aiMesh * meshOrig, const Shader & shader)const{
            static int initName = 0;
            std::string name = "Name" + initName++;

            //TODO: Improve this process
            std::vector<GLfloat> vertices;
            std::vector<GLfloat> normals;
            std::vector<GLfloat> uv;
            std::vector<GLuint> indices;
            std::cout<<"Import Mesh"<<std::endl;


            //Get the vertices and Normals
            std::cout<<"MNumVertices : " << meshOrig->mNumVertices << std::endl;
            for(unsigned int i = 0; i < meshOrig->mNumVertices; ++i) {
                for(unsigned int j = 0; j < 3; ++j) {
                    vertices.push_back(meshOrig->mVertices[i][j]);
                    normals.push_back(meshOrig->mNormals[i][j]);
                }

            }

            //Get the indices
            std::cout<<"mNumFaces : " << meshOrig->mNumFaces << std::endl;
            for(unsigned int i = 0; i < meshOrig->mNumFaces; ++i ){
                for(unsigned int j = 0; j < 3; ++j) {
                    indices.push_back(meshOrig->mFaces[i].mIndices[j]);
                }
            }

            std::cout<<"EndInstertion"<<std::endl;

            std::cout<<"meshOrig->mName.C_Str()"<<meshOrig->mName.C_Str()<<std::endl;
            auto  resultInsertion = map->m_geometries.emplace(
                    std::make_pair(
                            (meshOrig->mName.length > 0) ? meshOrig->mName.C_Str() : name,
                            Geometry(vertices, normals, uv, indices)));

            //Build a tree with nodes scene
            //Todo : test the insertion
            //Todo : to improve
            auto mapPair = resultInsertion.first;
            Geometry & geometry = mapPair->second;
            map->m_allInstances.emplace_back(new Instance(geometry, shader));

        }

        /*
        template<typename Material>
        Material * createMaterial(const AiScene_Type &){

        }

        Camera * createCamera(const AiScene_Type & ){

        }
        */
        //TODO : define a conditional flag to parametrize the build
        //TODO : Remove the magic strings defining the default shaders to use
        Scene * build(const aiScene & scene)const{
            Scene * map = new Scene;


            Shader & shader = map->makeShader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

            //===================================================================

            std::cout<<"Shader Load !"<<std::endl;

            std::cout<<"Scene Build"<<std::endl;
            std::cout<<"Num Meshes : "<< scene.mNumMeshes <<std::endl;
            // Detach Geometry from instances
            if( scene.HasMeshes()) {
                //TODO : To parametrize
                for(unsigned int i =  0; i < scene.mNumMeshes; ++i) {
                    std::cout<<"Create Meshes : "<< i <<std::endl;
                    std::cout<<scene.mMeshes[i]->mName.C_Str()<<std::endl;
                    importMesh(map, scene.mMeshes[i], shader);
                }
            }

            return map;
        }

    };
}

#endif //YAGUI_ASSIMPBUILDER_H
