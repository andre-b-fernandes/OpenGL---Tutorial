//
// Created by user on 06-07-2017.
//

#include "Triangle.h"


void Triangle ::initGLBuffers(vertexArgs va, colArgs ca, texArgs ta) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);



    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, va.infSize , va.inf, GL_STATIC_DRAW);


    //position
    glVertexAttribPointer(this->shader->layoutLocationVertex,3,GL_FLOAT,GL_FALSE, va.sizeNextVertex, (void *) va.posFirstVertex);
    glEnableVertexAttribArray(this->shader->layoutLocationVertex);


    //color
    if(ca.col){
        glVertexAttribPointer(this->shader->layoutLocationColor,3,GL_FLOAT,GL_FALSE, ca.sizeNextColor,(void *) ca.posFirstColor);
        glEnableVertexAttribArray(this->shader->layoutLocationColor);
    }

    //texture
    if(ta.tex){
        glVertexAttribPointer(this->shader->layoutLocationTex, 2 , GL_FLOAT, GL_FALSE, ta.sizeNextTex, (void *) ta.posFirstTex);
        glEnableVertexAttribArray(this->shader->layoutLocationTex);
    }

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glUseProgram(this->shader->ID);
}

void Triangle::draw() {
    glUseProgram(this->shader->ID);
    this->rotate(true,true,true,50 * (float)glfwGetTime(), "transform");
    this->changeColor(1,0,0,1);
    for(unsigned int i = 0; i < this->textures.size(); i++){
        glActiveTexture(this->textures[i]->getTextureUnit());
        glBindTexture(GL_TEXTURE_2D, this->textures[i]->getTexture());
    }
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0,3);
}