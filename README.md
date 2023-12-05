# Danburite
A real-time rendering engine with core-profile OpenGL and C++.

### Abstract ###
Danburite is a rendering engine developed with core-profile OpenGL and latest C++ standard. 
Its architecture consists of 3 phases: ObjectGL(object-oriented OpenGL), rendering engine(Danburite), and the app. Danburite utilizes ObjectGL to abstractly handle OpenGL, while application developers use Danburite to create content. The engine offers simple and intuitive interfaces, facilitating the rapid and easy development of applications.

### Engine Features ###
- Blinn-Phong-based shading
- Silhouette shading
- Refraction/reflection shading
- Postprocessing effects
    - Nagative
    - Grayscale
    - Gaussian blur
    - Edge detection
    - Sharpening
    - Gamma correction
    - HDR
    - SSAO (Screen-Space Ambient Occlusion)
    - FXAA (Fast Approximate Anti-Aliasing)
- Skybox
- Tessellation
- Bindless texture
- PCSS (Percentage Closer Soft Shadows)
- Instancing
- Normal mapping
- Parallax mapping
- GPU skinning

### Demo ###
![silhouette](https://github.com/Twin-Monkeys/Danburite/assets/47758621/adc973ba-d12f-41c1-9a1e-30f8f2f367e1)
![edge detection](https://github.com/Twin-Monkeys/Danburite/assets/47758621/2f59cd6c-4a24-4234-8498-d4cdcd2bb7d6)
<img src="./Environment mapping.png">
<img src="./Normal mapping.png">
<img src="./Light-Prepass2.png">
<img src="./Light-Prepass3.png">
<img src="./Light-Prepass4.png">
<img src="./Light-Prepass5.png">
<img src="./SSAO+PCSS.png">
