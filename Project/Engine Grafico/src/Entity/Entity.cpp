#include "Entity.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"

using namespace Engine;

glm::mat4 Entity::GetLocalModelMatrix() {

    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
        glm::radians(transform.eulerRot.x),
        glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
        glm::radians(transform.eulerRot.y),
        glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
        glm::radians(transform.eulerRot.z),
        glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const glm::mat4 roationMatrix = transformY * transformX * transformZ;

    // translation * rotation * scale (also know as TRS matrix)
    return glm::translate(glm::mat4(1.0f), transform.pos) *
        roationMatrix *
        glm::scale(glm::mat4(1.0f), transform.scale);
}

void Entity::UpdateSelfAndChild() {

    if (parent)
        transform.modelMatrix = parent->transform.modelMatrix * GetLocalModelMatrix();
    else
        transform.modelMatrix = GetLocalModelMatrix();

    for (auto&& child : children)
    {
        child->UpdateSelfAndChild();
    }
}

void Entity::AddChild(Entity* entity) {
    children.emplace_back(entity);
    children.back()->parent = this;
}