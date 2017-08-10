// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <iostream>
#include <math.h>
using namespace std;
// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
  mat3 ret;
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.
    vec3 axisN = glm::normalize(axis);
    float x = axisN[0];
    float y = axisN[1];
    float z = axisN[2];
    float c = cos((degrees*pi)/180);
    float s  =sin((degrees*pi)/180);
    mat3 unit = mat3(1,0,0,
                     0,1,0,
                     0,0,1);
    mat3 mid = mat3(x*x,x*y,x*z,
                    x*y,y*y,y*z,
                    x*z,y*z,z*z);
    mat3 end = mat3(0,z,-y,
                    -z,0,x,
                    y,-x,0);
    
    // You will change this return call
    return c*unit +(1-c)*mid+s*end;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
    eye = eye*rotate(-degrees,up);
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE 
  // Likely the same as in HW 1.
    vec3 inity = glm::normalize(cross(eye,up));
    eye = eye*rotate(-degrees,inity);
    up = up*rotate(-degrees,inity);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    // YOUR CODE FOR HW1 HERE
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(cross(up,eye));
    vec3 v = glm::normalize(up);
    mat4 rotation = mat4(u.x,v.x,w.x,0,
                         u.y,v.y,w.y,0,
                         u.z,v.z,w.z,0,
                         0,0,0,1);
    mat4 translation = mat4(1,0,0,0,
                            0,1,0,0,
                            0,0,1,0,
                            -eye.x,-eye.y,-eye.z,1);
    mat4 result = glm::lookAt(eye,center,up);
    mat4 abc = rotation*translation;
    return abc;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    float D = 1/tan(glm::radians(fovy)/2);
    float F = zFar;
    float N = zNear;
    float A = -((F+N)/(F-N));
    float B = -((2*F*N)/(F-N));
    mat4 result = glm::perspective(fovy,aspect,zNear,zFar);
   
    mat4 abc = mat4(D/aspect,0,0,0,
                0,D,0,0,
                0,0,A,-1,
                0,0,B,0);
    return abc;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  return mat4(sx,0,0,0,
              0,sy,0,0,
              0,0,sz,0,
              0,0,0,1);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement translation 
    return mat4(1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                tx,ty,tz,1);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
