# Danburite
A real-time rendering engine with core-profile OpenGL and C++.

### Abstract ###
Danburite is a rendering engine developed with core-profile OpenGL and latest C++ standard. 
Its architecture consists of 3 phases: ObjectGL(object-oriented OpenGL), rendering engine(Danburite), and the app. Danburite utilizes ObjectGL to abstractly handle OpenGL, while application developers use Danburite to create content. The engine offers simple and intuitive interfaces, facilitating the rapid and easy development of applications.

### Engine Features ###
- Blinn-Phong-based ordinary shading
- Silhouette shading (it feels like seeing an object in the fog)
- Alpha blending
- Postprocessing effect (It provides various filters like negative, grayscale, gaussian blur, edge detection, sharpen, etc.)
- Skybox
- Refraction/reflection shading
- Tessellation
- Multisample anti-aliasing
- Gamma correction
- Bindless texture
- Shadow
- Instancing
- Normal mapping
- Parallax mapping
- Advanced cpu-based shader compiler
- High dynamic range
- Skeletal animation (GPU skinning)

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
