// glass.frag
precision mediump float;
varying vec2 vTexCoord;

void main() {
    float edgeWidth = 0.05; 
    bool isEdge = (vTexCoord.x < edgeWidth || vTexCoord.x > 1.0 - edgeWidth ||
                   vTexCoord.y < edgeWidth || vTexCoord.y > 1.0 - edgeWidth);

    if (isEdge) {
        gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0); // Dark Gray Outline
    } else {
        gl_FragColor = vec4(0.5, 0.5, 0.5, 0.25); // 25% Gray Background
    }
}
