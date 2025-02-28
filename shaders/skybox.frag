#version 150

in vec3 texCoord;  // Les coordonnées de texture venant du vertex shader
out vec4 fragColor; // La couleur finale du fragment

// Uniforms pour les 6 textures des faces du cubemap
uniform sampler2D Tex0; // Face avant
uniform sampler2D Tex1; // Face arrière
uniform sampler2D Tex2; // Face gauche
uniform sampler2D Tex3; // Face droite
uniform sampler2D Tex4; // Face du dessus
uniform sampler2D Tex5; // Face du dessous

// Fonction pour ajuster les coordonnées de texture avec plus de "padding"
vec2 adjustTexCoord(vec2 coord) {
    // Réduire davantage les coordonnées pour créer un petit espace entre les bords
    return (coord * 0.95) + 0.025;  // Réduire plus et ajouter un petit espace
}

void main() {
    // Normaliser les coordonnées pour obtenir un vecteur directionnel
    vec3 dir = normalize(texCoord);
    
    // Vérification des faces du cube à échantillonner en fonction de la direction du vecteur
    if (abs(dir.x) > abs(dir.y) && abs(dir.x) > abs(dir.z)) {
        // Face droite ou gauche avec inversion de l'axe x
        if (dir.x > 0.0) {
            fragColor = texture(Tex3, adjustTexCoord(vec2(dir.z, -dir.y) * 0.5 + 0.5)); // Face droite
        } else {
            fragColor = texture(Tex2, adjustTexCoord(vec2(-dir.z, -dir.y) * 0.5 + 0.5)); // Face gauche
        }
    } else if (abs(dir.y) > abs(dir.x) && abs(dir.y) > abs(dir.z)) {
        // Face haut ou bas
        if (dir.y > 0.0) {
            fragColor = texture(Tex4, adjustTexCoord(vec2(dir.x, -dir.z) * 0.5 + 0.5)); // Face du dessus
        } else {
            fragColor = texture(Tex5, adjustTexCoord(vec2(dir.x, dir.z) * 0.5 + 0.5)); // Face du dessous
        }
    } else {
        // Échanger les faces avant et arrière avec inversion de l'axe x
        if (dir.z > 0.0) {
            fragColor = texture(Tex1, adjustTexCoord(vec2(-dir.x, -dir.y) * 0.5 + 0.5)); // Face arrière
        } else {
            fragColor = texture(Tex0, adjustTexCoord(vec2(dir.x, -dir.y) * 0.5 + 0.5)); // Face avant
        }
    }
}