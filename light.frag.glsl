# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 





vec4 ComputeLight (vec3 direction, vec4 lightcolor, vec3 normal, vec3 halfvec, vec4 mydiffuse, vec4 myspecular, float myshininess) {
    
    float nDotL = dot(normal, direction)  ;
    vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;
    
    float nDotH = dot(normal, halfvec) ;
    vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ;
    
    vec4 retval = lambert + phong ;
    return retval ;
}




void main (void)
{       
    if (enablelighting) {       
        vec4 finalcolor = vec4(0,0,0,0);
        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader
        vec4 vertexM = modelview * myvertex;
        const vec3 eyepos = vec3(0,0,0) ;
        vec3 mypos = vertexM.xyz / vertexM.w ; // Dehomogenize current location
        vec3 eyedirn = normalize(eyepos - mypos);
        
        vec3 normal = normalize(mat3(transpose(mat3(inverse(modelview)))) * mynormal);
        
        for(int i = 0; i < numused;i++){
            vec3 direction;
            if(lightposn[i].w!=0){
                vec3 position = lightposn[i].xyz / lightposn[i].w ;
                direction = normalize (position - mypos) ; // no attenuation
            }
            else{
                direction = normalize(lightposn[i].xyz);
            }
            vec3 halfx = normalize(direction + eyedirn);
            vec4 col = ComputeLight(direction, lightcolor[i], normal, halfx, diffuse, specular, shininess) ;
            finalcolor += col;
        }
        // Color all pixels black for now, remove this in your implementation!
        
        fragColor = ambient + finalcolor;
    } else {
        fragColor = vec4(color, 1.0f); 
    }
}























