/**
 * @file standard.vert
 * @brief Vertex shader for textured and minimalist-style blocks.
 * @project Gladly Voxel Sandbox
 */

precision mediump float;

// Vertex attributes (data coming from your Mesh/VBO)
attribute vec3 aPosition;   // Local model-space position
attribute vec2 aTexCoord;   // UV map for textures
attribute float aShadow;    // Baked ambient occlusion (0.0 to 1.0)

// Uniforms (constants for the whole draw call)
uniform mat4 uModelViewProjection;

// Varyings (passed to the fragment shader)
varying vec2 vTexCoord;
varying float vShadow;

void main() {
    // Pass UVs and Shadow values to the fragment shader
    vTexCoord = aTexCoord;
    vShadow = aShadow;
    
    // Transform position into screen space
    gl_Position = uModelViewProjection * vec4(aPosition, 1.0);
}
