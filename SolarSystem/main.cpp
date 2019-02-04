/*
 * Martín Figueroa Padilla
 *
 * Solar System main.cpp
 * An OpenGL project representing the Solar System
 * This program uses the "Basic template OpenGL project"
 courtesy of Sergio Ruiz in the TC3022 - Computer Graphics Course.
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif
#ifdef _WIN32
#include "freeglut.h"
#endif
#ifdef __unix__
#include "GL/freeglut.h"
#include "GL/gl.h"
#endif

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <list>

float color_convert(int color);
void show_axes(float length, float line_weight);
void draw_rectangle(float x, float y, float width, float height, int R, int G, int B);
void draw_circle(float x, float y, float radius, int R, int G, int B);

class Satelite {
public:
    std::string name = "";
    float speed = 0.0f;
    float size = 0.0f;
    float distance = 0.0f;
    float * color;
    
    void rotate_around(float speed, float direction) {
        angle += this->speed * speed * direction;
    }
    
    float getAngle() {
        return angle;
    }
private:
    float angle = 0.0f;
};

class Planet {
public:
    std::string name = "";
    float speed = 0.0f;
    float size = 0.0f;
    float distance = 0.0f;
    float * color;
    std::list<Satelite> satelites;

    void translate(float speed, float direction) {
        angle += this->speed * speed * direction;
        if (angle >= 360.0f) {
            angle = 0.0f;
        }
    }

    float getAngle() {
        return angle;
    }

private:
    float angle = 0.0f;
};

std::list<Planet> planets;

float speed = 1.0f;
float direction = 1.0f;

void init_planets() {
    Planet mercury;
    mercury.name = "Mercury";
    mercury.distance = 3.0f;
    mercury.size = 1.0f;
    mercury.speed = 0.01f;
    mercury.color = new float[3] { 172, 64, 88 };
    
    Planet venus;
    venus.name = "Venus";
    venus.distance = 2.0f;
    venus.size = 1.0f;
    venus.speed = 0.05f;
    venus.color = new float[3] { 212, 79, 73 };
    
    Planet earth;
    earth.name = "Earth";
    earth.distance = 2.0f;
    earth.size = 1.0f;
    earth.speed = 0.03f;
    earth.color = new float[3] { 211, 231, 105 };
    
    Satelite earth_moon;
    earth_moon.name = "Moon";
    earth_moon.distance = 0.8f;
    earth_moon.size = 0.3f;
    earth_moon.speed = 0.06f;
    earth_moon.color = new float[3] { 255, 255, 255 };
    earth.satelites.push_back(earth_moon);
    
    Planet mars;
    mars.name = "Mars";
    mars.distance = 5.0f;
    mars.size = 1.0f;
    mars.speed = 0.02f;
    mars.color = new float[3] { 226, 27, 17 };
    
    Planet jupiter;
    jupiter.name = "Jupiter";
    jupiter.distance = 2.0f;
    jupiter.size = 4.0f;
    jupiter.speed = 0.01f;
    jupiter.color = new float[3] { 216, 147, 62 };
    
    Satelite jupiter_io;
    jupiter_io.name = "Io";
    jupiter_io.distance = 0.5f;
    jupiter_io.size = 0.2f;
    jupiter_io.speed = 0.1f;
    jupiter_io.color = new float[3] { 255, 255, 255 };
    jupiter.satelites.push_back(jupiter_io);
    
    Satelite jupiter_europa;
    jupiter_europa.name = "Europa";
    jupiter_europa.distance = 1.0f;
    jupiter_europa.size = 0.2f;
    jupiter_europa.speed = 0.2f;
    jupiter_europa.color = new float[3] { 255, 255, 255 };
    jupiter.satelites.push_back(jupiter_europa);
    
    Satelite jupiter_ganymede;
    jupiter_ganymede.name = "Ganymede";
    jupiter_ganymede.distance = 1.5f;
    jupiter_ganymede.size = 0.2f;
    jupiter_ganymede.speed = 0.5f;
    jupiter_ganymede.color = new float[3] { 255, 255, 255 };
    jupiter.satelites.push_back(jupiter_ganymede);
    
    Satelite jupiter_callisto;
    jupiter_callisto.name = "Callisto";
    jupiter_callisto.distance = 2.0f;
    jupiter_callisto.size = 0.2f;
    jupiter_callisto.speed = 0.05f;
    jupiter_callisto.color = new float[3] { 255, 255, 255 };
    jupiter.satelites.push_back(jupiter_callisto);
    
    Planet saturn;
    saturn.name = "Saturn";
    saturn.distance = 2.0f;
    saturn.size = 3.0f;
    saturn.speed = 0.05f;
    saturn.color = new float[3] { 126, 62, 64 };
    
    Planet uranus;
    uranus.name = "Uranus";
    uranus.distance = 1.5f;
    uranus.size = 2.0f;
    uranus.speed = 0.1f;
    uranus.color = new float[3] { 59, 42, 223 };
    
    Planet neptune;
    neptune.name = "Neptune";
    neptune.distance = 1.0f;
    neptune.size = 2.0f;
    neptune.speed = 0.2f;
    neptune.color = new float[3] { 79, 223, 252 };
    
    Planet pluto;
    pluto.name = "Pluto";
    pluto.distance = 2.0f;
    pluto.size = 0.5f;
    pluto.speed = 0.005f;
    pluto.color = new float[3] { 145, 246, 186 };
    
    planets.push_back(mercury);
    planets.push_back(venus);
    planets.push_back(earth);
    planets.push_back(mars);
    planets.push_back(jupiter);
    planets.push_back(saturn);
    planets.push_back(uranus);
    planets.push_back(neptune);
    planets.push_back(pluto);
}

void init() {
    init_planets();
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 110.0f,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    draw_circle(0, 0, 2.0f, 255, 255, 0); // The Sun
    
    bool planet_allignment = true;
    float global_distance = 1.0f;
    for (std::list<Planet>::iterator planet = planets.begin(); planet != planets.end(); ++planet) {
        global_distance += planet->distance + (planet->size / 2);
        glPushMatrix(); {
            glRotatef(planet->getAngle(), 0, 0, 1);
            glTranslatef(global_distance, 0, 0);
            draw_circle(0, 0, planet->size / 2,
                planet->color[0], planet->color[1], planet->color[2]);
            
            for(std::list<Satelite>::iterator satelite = planet->satelites.begin(); satelite != planet->satelites.end(); ++satelite) {
                glPushMatrix(); {
                    glRotatef(satelite->getAngle(), 0, 0, 1);
                    glTranslatef(planet->size / 2 + satelite->distance + satelite->size / 2, 0, 0);
                    draw_circle(0, 0, satelite->size / 2,
                        satelite->color[0], satelite->color[1], satelite->color[2]);
                }
                glPopMatrix();
                
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                draw_circle(0, 0, planet->size / 2 + satelite->distance + satelite->size / 2, 76, 76, 76);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                
            }
        }
        glPopMatrix();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        draw_circle(0, 0, global_distance, 76, 76, 76);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        global_distance += planet->size / 2;
        
        int _angle = floor(planet->getAngle());
        if (!((_angle >= 178 && _angle <= 182) || (_angle >= 358 && _angle <= 2))) {
            // std::cout << planet->name + std::to_string(planet->getAngle());
            planet_allignment = false;
        }
    }
    
    if (planet_allignment) {
        std::cout << "PLANET ALLIGNMENT\n";
    }
    
    glutSwapBuffers();
}

float color_convert(int color) {
    return (color * 1.0f) / 255.0f;
}

void show_axes(float length, float line_weight) {
    glLineWidth(line_weight);
    glBegin(GL_LINES); {
        glColor3f(1, 0, 0); // X is red
        glVertex3f(0, 0, 0); glVertex3f(length, 0, 0);
        
        glColor3f(0, 1, 0); // Y is green
        glVertex3f(0, 0, 0); glVertex3f(0, length, 0);
        
        glColor3f(0, 0, 1); // Z is blue
        glVertex3f(0, 0, 0); glVertex3f(0, 0, length);
    }
    glEnd();
}

void draw_rectangle(float x, float y, float width, float height, int R, int G, int B) {
    glColor3f(color_convert(R), color_convert(G), color_convert(B));
    glBegin(GL_POLYGON); {
        glVertex3f(x, y, 0);
        glVertex3f(x + width, y, 0);
        glVertex3f(x + width, y - height, 0);
        glVertex3f(x, y - height, 0);
    }
    glEnd();
}

void draw_circle(float x, float y, float radius, int R, int G, int B) {
    glColor3f(color_convert(R), color_convert(G), color_convert(B));
    glBegin(GL_POLYGON); {
        for (int i = 0; i < 360; i++) {
            float radians = 0.0174533f * i;
            float _x = radius * cos(radians);
            float _y = radius * -sin(radians);
            glVertex3f(x + _x, y + _y, 0);
        }
    }
    glEnd();
}

void idle() {
    for (std::list<Planet>::iterator planet = planets.begin(); planet != planets.end(); ++planet) {
        planet->translate(speed, direction);
        
        for (std::list<Satelite>::iterator satelite = planet->satelites.begin(); satelite != planet->satelites.end(); ++satelite) {
            satelite->rotate_around(speed, direction);
        }
    }
    
    glutPostRedisplay();
}

void reshape(int x, int y) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 150.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
    gluLookAt(0.0, 1.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    display();
}

void keyboard_listener(unsigned char key, int mouseX, int mouseY) {
    try {
        int input = std::stoi(std::to_string(key));
        if (input >= 48 && input <= 57) {
            speed = input - 48;
        }
    }
    catch (int e) {
        speed = 1.0f;
    }
}

void special_listener(int key, int mouseX, int mouseY) {
    switch (key) {
        case GLUT_KEY_LEFT:
            direction = -1.0f;
            break;
        case GLUT_KEY_RIGHT:
            direction = 1.0f;
            break;
        default: break;
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Solar System");
    
    init();
    glutKeyboardFunc(keyboard_listener);
    glutSpecialFunc(special_listener);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

