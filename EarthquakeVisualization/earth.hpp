#ifndef EARTH_HPP
#define EARTH_HPP

#include "engine.hpp"
#include <vector>
using glm::vec2;
using glm::vec3;

class Earth {
public:
    void initialize(Engine *engine, int slices, int stacks, float spherical);
    float isSpherical();
    void setSpherical(float spherical);
    vec3 getPosition(float latitude, float longitude);
    vec3 getNormal(float latitude, float longitude);
    void draw(bool textured);
protected:
    int slices, stacks;
    int nVertices, nTriangles;
    float spherical;
    Engine *engine;

    // TODO: Define the necessary buffers and texture.
    // Feel free to add helper methods to update the buffers.
    int nVerts, nIndices;

    VertexBuffer vertexBuffer, normalBuffer, texCoordBuffer;
    ElementBuffer indexBuffer;
    Texture texture;
};

inline void Earth::initialize(Engine *e, int sl, int st, float sp) {
    engine = e;
    slices = sl;
    stacks = st;
    spherical = sp;

    // TODO: Initialize nVertices, nTriangles, buffers, texture
    std::vector<vec3> vertices, normals;
    std::vector<vec2> texCoords;

    for (int i = 0; i <= slices; i ++)
      for (int j = 0; j <= stacks; j ++) {
        vertices.push_back(vec3(i - slices / 2, j - stacks / 2, 0));
        normals.push_back(vec3(0, 0, 1));
        texCoords.push_back(vec2((double)i / slices, 1.0 - (double) j / stacks));

        vertices.push_back(vec3(i - slices / 2 + 1, j - stacks / 2, 0));
        normals.push_back(vec3(0, 0, 1));
        texCoords.push_back(vec2((double)i / slices, 1.0 - (double) j / stacks));
      }
    nVerts = vertices.size();
    vertexBuffer = engine->allocateVertexBuffer(nVerts*sizeof(vec3));
    engine->copyVertexData(vertexBuffer, &vertices[0], nVerts*sizeof(vec3));
    normalBuffer = engine->allocateVertexBuffer(nVerts*sizeof(vec3));
    engine->copyVertexData(normalBuffer, &normals[0], nVerts*sizeof(vec3));
    texCoordBuffer = engine->allocateVertexBuffer(nVerts*sizeof(vec2));
    engine->copyVertexData(texCoordBuffer, &texCoords[0], nVerts*sizeof(vec2));
    std::vector<int> indices;
    for (int i = 0; i <= slices; i ++)
      for (int j = 0; j < stacks; j ++) {
        int basis = 2 * i * (stacks + 1) + 2 * j;
        indices.push_back(basis);
        indices.push_back(basis + 2);
        indices.push_back(basis + 1);

        indices.push_back(basis + 1);
        indices.push_back(basis + 2);
        indices.push_back(basis + 3);
      }
    nIndices = indices.size();
    indexBuffer = engine->allocateElementBuffer(nIndices*sizeof(int));
    engine->copyElementData(indexBuffer, &indices[0], nIndices*sizeof(int));
    texture = engine->loadTexture(Config::textureFile);
}

inline float Earth::isSpherical() {
    return spherical;
}

inline void Earth::setSpherical(float s) {
    spherical = s;

    // TODO: Also update the relevant buffers.
    // You should only need to update two buffers, not all of them.

}

inline vec3 Earth::getPosition(float latitude, float longitude) {
    vec3 rectangularPosition(0,0,0), sphericalPosition(0,0,0);

    // TODO compute vertex positions on rectangle and sphere

    if (spherical == 0)
        return rectangularPosition;
    else if (spherical == 1)
        return sphericalPosition;
    else {

        // TODO compute the interpolated position
        return vec3(0,0,0);

    }
}

inline vec3 Earth::getNormal(float latitude, float longitude) {
    vec3 rectangularNormal(0,0,0), sphericalNormal(0,0,0);

    // TODO compute vertex positions on rectangle and sphere

    if (spherical == 0)
        return rectangularNormal;
    else if (spherical == 1)
        return sphericalNormal;
    else {

        // TODO compute the interpolated normal
        return vec3(0,0,0);

    }
}

inline void Earth::draw(bool textured) {

    // TODO: Draw the mesh (with or without texture, depending on the input)
    // Light gray background
    glClearColor(0.8,0.8,0.8, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Point and line size
    glPointSize(5);
    glLineWidth(2);
    // Draw mesh
    glColor3f(1,1,1);
//    glScalef(0.1, 0.1, 0.1);
    if (!textured)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    engine->setVertexArray(vertexBuffer);
    engine->setNormalArray(normalBuffer);
    engine->setTexCoordArray(texCoordBuffer);
    if (textured)
      engine->setTexture(texture);
    engine->drawElements(GL_TRIANGLES, indexBuffer, nIndices);
}

#endif
