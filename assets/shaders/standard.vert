// standard.vert
precision mediump float;

// Incoming attributes from your VBO (Vertex Buffer Object)
attribute vec3 aPosition;
attribute vec2 aTexCoord;

// Uniforms for the camera and chunk positioning
uniform mat4 uModelViewProjection;

// Pass these to the fragment shader
varying vec2 vTexCoord;

void main() {
    // Send the texture coordinate to the fragment shader
    vTexCoord = aTexCoord;
    
    // Transform vertex position by the combined camera matrices
    gl_Position = uModelViewProjection * vec4(aPosition, 1.0);
}
