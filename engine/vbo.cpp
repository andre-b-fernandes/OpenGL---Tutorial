//
// Created by user on 06-07-2017.
//

#include "vbo.h"

Shader * vbo:: shader = 0;

void vbo ::initGLBuffers(vertexArgs va, texArgs ta, normalArgs na) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, va.infSize , va.inf, GL_STATIC_DRAW);


    //position
    glVertexAttribPointer(this->shader->layoutLocationVertex,3,GL_FLOAT,GL_FALSE, va.sizeNextVertex, (void *) va.posFirstVertex);
    glEnableVertexAttribArray(this->shader->layoutLocationVertex);


    glVertexAttribPointer(this->shader->layoutLocationNormals, 3 , GL_FLOAT, GL_FALSE, na.sizeNextNorm, (void *) na.posFirstNorm);
    glEnableVertexAttribArray(this->shader->layoutLocationNormals);


    //texture
    glVertexAttribPointer(this->shader->layoutLocationTex, 2 , GL_FLOAT, GL_FALSE, ta.sizeNextTex, (void *) ta.posFirstTex);
    glEnableVertexAttribArray(this->shader->layoutLocationTex);


    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void vbo::updateTransform(const char *uniformTrans, const char * uniformRot, const char * uniformScale) {
    glm::mat4 trans;
    trans = glm::rotate(trans, glm::radians(this->degrees), glm::vec3((int)this->rotX, (int)this->rotY, (int)this->rotZ));
    this->shader->setMatrix4fv(uniformRot, trans);
    glm::mat4 trans2;
    trans2 = glm::translate(trans2, glm::vec3(this->x,this->y,this->z));
    this->shader->setMatrix4fv(uniformTrans, trans2);
    glm::mat4 trans3;
    trans3 = glm::scale(trans3, glm::vec3(this->sizex, this->sizey,this->sizez));
    this->shader->setMatrix4fv(uniformScale, trans3);
}

void vbo::updateNormals(const char *uniform) {
    glm::mat4 aux;
    aux = glm::transpose(glm::inverse(this->m));
    this->shader->setMatrix4fv(uniform, aux);
}

void vbo::updateCoordinates(const char *model) {
    this->shader->setMatrix4fv(model, m);
}


void vbo::draw() {
    this->updateTransform("transformTrans","transformRot","transformScale" );
    this->updateCoordinates("model");
    this->updateNormals("modelChanged");
    for(unsigned int i = 0; i < this->textures.size(); i++){
        glActiveTexture(this->textures[i]->getTextureUnit());
        glBindTexture(GL_TEXTURE_2D, this->textures[i]->getTexture());
    }

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0,this->numOfVert);
}
