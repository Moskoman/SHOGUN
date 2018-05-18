#pragma once
// é o debug iniciante
#include <iostream>
#include <glm\glm.hpp>
#include <string>

#ifndef DEBUGINICIANTE_H
#define DEBUGINICIANTE_H
#define USEDEBUG 0

#ifdef USEDEBUG
#define Debug(x) std::cout << "Debug: (" << x << ")\n"
#define Debug2(x, y) std::cout << "Debug: (" << x << ", " << y << ")\n"
#define Debug3(x, y, z) std::cout << "Debug: (" << x << ", " << y << ", " << z << ")\n"
#define Debug4(x, y, z, w) std::cout << "Debug: (" << x << ", " << y << ", " << z << ", " << w << ")\n"
#define Debugv(v) std::cout << v.x << " " << v.y << " " << v.z << "\n";
#else
#define Debug(x)
#define Debug2(x,y)
#define Debug3(x,y,z)
#define Debug4(x,y,z,w)


#endif

#endif 



