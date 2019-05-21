#pragma once
#include "Renderable.h"
#include "Material.h"

class Cylinder : public Renderable {
private:
	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _numVertices;

protected:
	void init() {
		float cylinderVertices[] = {
			// position   // normals   // texture coords
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, 1.0f, -0.923879f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, 1.0f, 0.980785f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, 1.0f, 0.980786f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, 1.0f, 0.980786f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382682f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382682f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.555569f, 1.0f, 0.83147f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.707106f, 1.0f, 0.707108f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.707106f, 1.0f, 0.707108f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.831469f, 1.0f, 0.555571f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, 1.0f, 0.195091f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1e-06f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1e-06f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, 1.0f, -0.195089f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, 1.0f, -0.195089f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.83147f, 1.0f, -0.55557f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, 1.0f, -0.923879f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.83147f, 1.0f, -0.55557f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.707107f, 1.0f, -0.707106f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, 1.0f, -0.923879f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.707107f, 1.0f, -0.707106f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.555571f, 1.0f, -0.831469f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, 1.0f, -0.923879f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, 1.0f, -0.923879f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.195091f, 1.0f, -0.980785f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, 1.0f, -0.980785f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, -0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, -0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, 1.0f, -0.83147f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, 1.0f, -0.707107f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, 1.0f, -0.707107f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.83147f, 1.0f, -0.55557f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, 1.0f, -0.19509f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, 1.0f, 0.19509f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, 1.0f, 0.19509f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, 0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, 0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.83147f, 1.0f, 0.55557f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, 1.0f, 0.707107f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, 1.0f, 0.707107f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, 1.0f, 0.83147f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382682f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.707106f, 1.0f, 0.707108f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.707106f, 1.0f, 0.707108f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, 1.0f, -0.923879f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, -0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, -0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, 1.0f, -0.707107f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, 0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, 1.0f, 0.707107f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, 1.0f, 0.707107f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, 1.0f, -0.923879f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, 1.0f, 0.92388f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, 1.0f, 0.382684f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, 1.0f, -0.382683f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, 0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, 0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, -1.0f, 0.92388f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, -1.0f, 0.707107f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.83147f, -1.0f, 0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.83147f, -1.0f, 0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, -1.0f, 0.382683f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, -1.0f, 0.382683f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, -0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, -0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, -1.0f, -0.382683f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.92388f, -1.0f, -0.382683f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.83147f, -1.0f, -0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.83147f, -1.0f, -0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, -1.0f, -0.707107f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.707107f, -1.0f, -0.707107f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, -0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, -0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.382683f, -1.0f, -0.92388f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195091f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195091f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.382684f, -1.0f, -0.923879f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.555571f, -1.0f, -0.831469f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.555571f, -1.0f, -0.831469f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.707107f, -1.0f, -0.707106f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.83147f, -1.0f, -0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.83147f, -1.0f, -0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.92388f, -1.0f, -0.382683f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1e-06f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, 0.195091f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, 0.195091f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.923879f, -1.0f, 0.382684f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.831469f, -1.0f, 0.555571f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.831469f, -1.0f, 0.555571f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.707106f, -1.0f, 0.707108f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.707106f, -1.0f, 0.707108f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.555569f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.555569f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.382682f, -1.0f, 0.92388f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, 0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195091f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195091f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.555571f, -1.0f, -0.831469f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.555571f, -1.0f, -0.831469f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.83147f, -1.0f, -0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, 0.195091f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, 0.195091f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.831469f, -1.0f, 0.555571f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.55557f, -1.0f, 0.83147f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.83147f, -1.0f, -0.55557f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.19509f, -1.0f, -0.980785f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.195089f, -1.0f, 0.980786f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			-0.980785f, -1.0f, 0.19509f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.980785f, -1.0f, -0.195089f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, -0.0f, 0.0f, 1.0f, 0.978704f, 0.647296f,
			-0.19509f, -1.0f, 0.980785f, -0.1951f, 0.0f, 0.9808f, 0.501637f, 0.489866f,
			0.0f, -1.0f, 1.0f, -0.0f, 0.0f, 1.0f, 0.503776f, 0.490732f,
			-0.19509f, 1.0f, 0.980785f, -0.1951f, 0.0f, 0.9808f, 0.998195f, 0.550808f,
			-0.382683f, -1.0f, 0.92388f, -0.3827f, 0.0f, 0.9239f, 0.499388f, 0.48945f,
			-0.19509f, -1.0f, 0.980785f, -0.1951f, 0.0f, 0.9808f, 0.501637f, 0.489866f,
			-0.382683f, 1.0f, 0.92388f, -0.3827f, 0.0f, 0.9239f, 0.998503f, 0.452288f,
			-0.55557f, -1.0f, 0.83147f, -0.5556f, 0.0f, 0.8315f, 0.497121f, 0.489499f,
			-0.382683f, -1.0f, 0.92388f, -0.3827f, 0.0f, 0.9239f, 0.499388f, 0.48945f,
			-0.55557f, 1.0f, 0.83147f, -0.5556f, 0.0f, 0.8315f, 0.979575f, 0.355529f,
			-0.707107f, -1.0f, 0.707107f, -0.7071f, 0.0f, 0.7071f, 0.494928f, 0.490008f,
			-0.55557f, -1.0f, 0.83147f, -0.5556f, 0.0f, 0.8315f, 0.497121f, 0.489499f,
			-0.707107f, 1.0f, 0.707107f, -0.7071f, 0.0f, 0.7071f, 0.942108f, 0.264267f,
			-0.83147f, -1.0f, 0.55557f, -0.8315f, 0.0f, 0.5556f, 0.4929f, 0.490956f,
			-0.707107f, -1.0f, 0.707107f, -0.7071f, 0.0f, 0.7071f, 0.494928f, 0.490008f,
			-0.83147f, 1.0f, 0.55557f, -0.8315f, 0.0f, 0.5556f, 0.887522f, 0.182039f,
			-0.92388f, -1.0f, 0.382683f, -0.9239f, 0.0f, 0.3827f, 0.491121f, 0.492303f,
			-0.83147f, -1.0f, 0.55557f, -0.8315f, 0.0f, 0.5556f, 0.4929f, 0.490956f,
			-0.92388f, 1.0f, 0.382683f, -0.9239f, 0.0f, 0.3827f, 0.817911f, 0.112031f,
			-0.980785f, -1.0f, 0.19509f, -0.9808f, 0.0f, 0.1951f, 0.489673f, 0.493998f,
			-0.92388f, -1.0f, 0.382683f, -0.9239f, 0.0f, 0.3827f, 0.491121f, 0.492303f,
			-0.980785f, 1.0f, 0.19509f, -0.9808f, 0.0f, 0.1951f, 0.735964f, 0.056959f,
			-1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.488615f, 0.495968f,
			-0.980785f, -1.0f, 0.19509f, -0.9808f, 0.0f, 0.1951f, 0.489673f, 0.493998f,
			-1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.64485f, 0.01895f,
			-0.980785f, -1.0f, -0.19509f, -0.9808f, 0.0f, -0.1951f, 0.487973f, 0.498135f,
			-1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.488615f, 0.495968f,
			-0.980785f, 1.0f, -0.19509f, -0.9808f, 0.0f, -0.1951f, 0.547996f, 0.000100017f,
			-0.92388f, -1.0f, -0.382683f, -0.9239f, 0.0f, -0.3827f, 0.487724f, 0.500392f,
			-0.980785f, -1.0f, -0.19509f, -0.9808f, 0.0f, -0.1951f, 0.487973f, 0.498135f,
			-0.92388f, 1.0f, -0.382683f, -0.9239f, 0.0f, -0.3827f, 0.449398f, 0.000500977f,
			-0.83147f, -1.0f, -0.55557f, -0.8315f, 0.0f, -0.5556f, 0.487889f, 0.50266f,
			-0.92388f, -1.0f, -0.382683f, -0.9239f, 0.0f, -0.3827f, 0.487724f, 0.500392f,
			-0.83147f, 1.0f, -0.55557f, -0.8315f, 0.0f, -0.5556f, 0.352839f, 0.020099f,
			-0.707107f, -1.0f, -0.707107f, -0.7071f, 0.0f, -0.7071f, 0.488465f, 0.50486f,
			-0.83147f, -1.0f, -0.55557f, -0.8315f, 0.0f, -0.5556f, 0.487889f, 0.50266f,
			-0.707107f, 1.0f, -0.707107f, -0.7071f, 0.0f, -0.7071f, 0.262009f, 0.05811f,
			-0.55557f, -1.0f, -0.83147f, -0.5556f, 0.0f, -0.8315f, 0.489432f, 0.506915f,
			-0.707107f, -1.0f, -0.707107f, -0.7071f, 0.0f, -0.7071f, 0.488465f, 0.50486f,
			-0.55557f, 1.0f, -0.83147f, -0.5556f, 0.0f, -0.8315f, 0.180372f, 0.113047f,
			-0.382683f, -1.0f, -0.92388f, -0.3827f, 0.0f, -0.9239f, 0.490754f, 0.508754f,
			-0.55557f, -1.0f, -0.83147f, -0.5556f, 0.0f, -0.8315f, 0.489432f, 0.506915f,
			-0.382683f, 1.0f, -0.92388f, -0.3827f, 0.0f, -0.9239f, 0.111025f, 0.182793f,
			-0.19509f, -1.0f, -0.980785f, -0.1951f, 0.0f, -0.9808f, 0.492376f, 0.510315f,
			-0.382683f, -1.0f, -0.92388f, -0.3827f, 0.0f, -0.9239f, 0.490754f, 0.508754f,
			-0.19509f, 1.0f, -0.980785f, -0.1951f, 0.0f, -0.9808f, 0.056582f, 0.264698f,
			0.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.494248f, 0.511537f,
			-0.19509f, -1.0f, -0.980785f, -0.1951f, 0.0f, -0.9808f, 0.492376f, 0.510315f,
			0.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.01913f, 0.355628f,
			0.195091f, -1.0f, -0.980785f, 0.1951f, 0.0f, -0.9808f, 0.496297f, 0.51238f,
			0.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.494248f, 0.511537f,
			0.195091f, 1.0f, -0.980785f, 0.1951f, 0.0f, -0.9808f, 0.0001f, 0.452109f,
			0.382684f, -1.0f, -0.923879f, 0.3827f, 0.0f, -0.9239f, 0.498441f, 0.512817f,
			0.195091f, -1.0f, -0.980785f, 0.1951f, 0.0f, -0.9808f, 0.496297f, 0.51238f,
			0.382684f, 1.0f, -0.923879f, 0.3827f, 0.0f, -0.9239f, 0.000228f, 0.550466f,
			0.555571f, -1.0f, -0.831469f, 0.5556f, 0.0f, -0.8315f, 0.500607f, 0.512831f,
			0.382684f, -1.0f, -0.923879f, 0.3827f, 0.0f, -0.9239f, 0.498441f, 0.512817f,
			0.555571f, 1.0f, -0.831469f, 0.5556f, 0.0f, -0.8315f, 0.019522f, 0.646911f,
			0.707107f, -1.0f, -0.707106f, 0.7071f, 0.0f, -0.7071f, 0.502711f, 0.512425f,
			0.555571f, -1.0f, -0.831469f, 0.5556f, 0.0f, -0.8315f, 0.500607f, 0.512831f,
			0.707107f, 1.0f, -0.707106f, 0.7071f, 0.0f, -0.7071f, 0.05724f, 0.737726f,
			0.83147f, -1.0f, -0.55557f, 0.8315f, 0.0f, -0.5556f, 0.504673f, 0.511619f,
			0.707107f, -1.0f, -0.707106f, 0.7071f, 0.0f, -0.7071f, 0.502711f, 0.512425f,
			0.83147f, 1.0f, -0.55557f, 0.8315f, 0.0f, -0.5556f, 0.111918f, 0.819407f,
			0.92388f, -1.0f, -0.382683f, 0.9239f, 0.0f, -0.3827f, 0.506421f, 0.510447f,
			0.83147f, -1.0f, -0.55557f, 0.8315f, 0.0f, -0.5556f, 0.504673f, 0.511619f,
			0.92388f, 1.0f, -0.382683f, 0.9239f, 0.0f, -0.3827f, 0.181427f, 0.888813f,
			0.980785f, -1.0f, -0.195089f, 0.9808f, 0.0f, -0.1951f, 0.507895f, 0.508953f,
			0.92388f, -1.0f, -0.382683f, 0.9239f, 0.0f, -0.3827f, 0.506421f, 0.510447f,
			0.980785f, 1.0f, -0.195089f, 0.9808f, 0.0f, -0.1951f, 0.263078f, 0.943298f,
			1.0f, -1.0f, 1e-06f, 1.0f, 0.0f, 0.0f, 0.509032f, 0.507201f,
			0.980785f, -1.0f, -0.195089f, 0.9808f, 0.0f, -0.1951f, 0.507895f, 0.508953f,
			1.0f, 1.0f, 1e-06f, 1.0f, 0.0f, 0.0f, 0.353713f, 0.980794f,
			0.980785f, -1.0f, 0.195091f, 0.9808f, 0.0f, 0.1951f, 0.509863f, 0.50493f,
			1.0f, -1.0f, 1e-06f, 1.0f, 0.0f, 0.0f, 0.509032f, 0.507201f,
			0.980785f, 1.0f, 0.195091f, 0.9808f, 0.0f, 0.1951f, 0.449903f, 0.9999f,
			0.923879f, -1.0f, 0.382684f, 0.9239f, 0.0f, 0.3827f, 0.510255f, 0.502549f,
			0.980785f, -1.0f, 0.195091f, 0.9808f, 0.0f, 0.1951f, 0.509863f, 0.50493f,
			0.923879f, 1.0f, 0.382684f, 0.9239f, 0.0f, 0.3827f, 0.547968f, 0.9999f,
			0.831469f, -1.0f, 0.555571f, 0.8315f, 0.0f, 0.5556f, 0.510195f, 0.500145f,
			0.923879f, -1.0f, 0.382684f, 0.9239f, 0.0f, 0.3827f, 0.510255f, 0.502549f,
			0.831469f, 1.0f, 0.555571f, 0.8315f, 0.0f, 0.5556f, 0.644176f, 0.980801f,
			0.707106f, -1.0f, 0.707108f, 0.7071f, 0.0f, 0.7071f, 0.509681f, 0.497807f,
			0.831469f, -1.0f, 0.555571f, 0.8315f, 0.0f, 0.5556f, 0.510195f, 0.500145f,
			0.707106f, 1.0f, 0.707108f, 0.7071f, 0.0f, 0.7071f, 0.734846f, 0.94333f,
			0.555569f, -1.0f, 0.83147f, 0.5556f, 0.0f, 0.8315f, 0.508734f, 0.495621f,
			0.707106f, -1.0f, 0.707108f, 0.7071f, 0.0f, 0.7071f, 0.509681f, 0.497807f,
			0.555569f, 1.0f, 0.83147f, 0.5556f, 0.0f, 0.8315f, 0.816509f, 0.888916f,
			0.382682f, -1.0f, 0.92388f, 0.3827f, 0.0f, 0.9239f, 0.507393f, 0.493668f,
			0.555569f, -1.0f, 0.83147f, 0.5556f, 0.0f, 0.8315f, 0.508734f, 0.495621f,
			0.382682f, 1.0f, 0.92388f, 0.3827f, 0.0f, 0.9239f, 0.88605f, 0.819625f,
			0.195089f, -1.0f, 0.980786f, 0.1951f, 0.0f, 0.9808f, 0.505721f, 0.492014f,
			0.382682f, -1.0f, 0.92388f, 0.3827f, 0.0f, 0.9239f, 0.507393f, 0.493668f,
			0.195089f, 1.0f, 0.980786f, 0.1951f, 0.0f, 0.9808f, 0.940826f, 0.738052f,
			0.0f, -1.0f, 1.0f, -0.0f, 0.0f, 1.0f, 0.503776f, 0.490732f,
			0.195089f, -1.0f, 0.980786f, 0.1951f, 0.0f, 0.9808f, 0.505721f, 0.492014f,
			0.0f, 1.0f, 1.0f, -0.0f, 0.0f, 1.0f, 0.978704f, 0.647296f,
			-0.19509f, 1.0f, 0.980785f, -0.1951f, 0.0f, 0.9808f, 0.998195f, 0.550808f,
			-0.19509f, -1.0f, 0.980785f, -0.1951f, 0.0f, 0.9808f, 0.501637f, 0.489866f,
			-0.19509f, 1.0f, 0.980785f, -0.1951f, 0.0f, 0.9808f, 0.998195f, 0.550808f,
			-0.382683f, 1.0f, 0.92388f, -0.3827f, 0.0f, 0.9239f, 0.998503f, 0.452288f,
			-0.382683f, -1.0f, 0.92388f, -0.3827f, 0.0f, 0.9239f, 0.499388f, 0.48945f,
			-0.382683f, 1.0f, 0.92388f, -0.3827f, 0.0f, 0.9239f, 0.998503f, 0.452288f,
			-0.55557f, 1.0f, 0.83147f, -0.5556f, 0.0f, 0.8315f, 0.979575f, 0.355529f,
			-0.55557f, -1.0f, 0.83147f, -0.5556f, 0.0f, 0.8315f, 0.497121f, 0.489499f,
			-0.55557f, 1.0f, 0.83147f, -0.5556f, 0.0f, 0.8315f, 0.979575f, 0.355529f,
			-0.707107f, 1.0f, 0.707107f, -0.7071f, 0.0f, 0.7071f, 0.942108f, 0.264267f,
			-0.707107f, -1.0f, 0.707107f, -0.7071f, 0.0f, 0.7071f, 0.494928f, 0.490008f,
			-0.707107f, 1.0f, 0.707107f, -0.7071f, 0.0f, 0.7071f, 0.942108f, 0.264267f,
			-0.83147f, 1.0f, 0.55557f, -0.8315f, 0.0f, 0.5556f, 0.887522f, 0.182039f,
			-0.83147f, -1.0f, 0.55557f, -0.8315f, 0.0f, 0.5556f, 0.4929f, 0.490956f,
			-0.83147f, 1.0f, 0.55557f, -0.8315f, 0.0f, 0.5556f, 0.887522f, 0.182039f,
			-0.92388f, 1.0f, 0.382683f, -0.9239f, 0.0f, 0.3827f, 0.817911f, 0.112031f,
			-0.92388f, -1.0f, 0.382683f, -0.9239f, 0.0f, 0.3827f, 0.491121f, 0.492303f,
			-0.92388f, 1.0f, 0.382683f, -0.9239f, 0.0f, 0.3827f, 0.817911f, 0.112031f,
			-0.980785f, 1.0f, 0.19509f, -0.9808f, 0.0f, 0.1951f, 0.735964f, 0.056959f,
			-0.980785f, -1.0f, 0.19509f, -0.9808f, 0.0f, 0.1951f, 0.489673f, 0.493998f,
			-0.980785f, 1.0f, 0.19509f, -0.9808f, 0.0f, 0.1951f, 0.735964f, 0.056959f,
			-1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.64485f, 0.01895f,
			-1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.488615f, 0.495968f,
			-1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.64485f, 0.01895f,
			-0.980785f, 1.0f, -0.19509f, -0.9808f, 0.0f, -0.1951f, 0.547996f, 0.000100017f,
			-0.980785f, -1.0f, -0.19509f, -0.9808f, 0.0f, -0.1951f, 0.487973f, 0.498135f,
			-0.980785f, 1.0f, -0.19509f, -0.9808f, 0.0f, -0.1951f, 0.547996f, 0.000100017f,
			-0.92388f, 1.0f, -0.382683f, -0.9239f, 0.0f, -0.3827f, 0.449398f, 0.000500977f,
			-0.92388f, -1.0f, -0.382683f, -0.9239f, 0.0f, -0.3827f, 0.487724f, 0.500392f,
			-0.92388f, 1.0f, -0.382683f, -0.9239f, 0.0f, -0.3827f, 0.449398f, 0.000500977f,
			-0.83147f, 1.0f, -0.55557f, -0.8315f, 0.0f, -0.5556f, 0.352839f, 0.020099f,
			-0.83147f, -1.0f, -0.55557f, -0.8315f, 0.0f, -0.5556f, 0.487889f, 0.50266f,
			-0.83147f, 1.0f, -0.55557f, -0.8315f, 0.0f, -0.5556f, 0.352839f, 0.020099f,
			-0.707107f, 1.0f, -0.707107f, -0.7071f, 0.0f, -0.7071f, 0.262009f, 0.05811f,
			-0.707107f, -1.0f, -0.707107f, -0.7071f, 0.0f, -0.7071f, 0.488465f, 0.50486f,
			-0.707107f, 1.0f, -0.707107f, -0.7071f, 0.0f, -0.7071f, 0.262009f, 0.05811f,
			-0.55557f, 1.0f, -0.83147f, -0.5556f, 0.0f, -0.8315f, 0.180372f, 0.113047f,
			-0.55557f, -1.0f, -0.83147f, -0.5556f, 0.0f, -0.8315f, 0.489432f, 0.506915f,
			-0.55557f, 1.0f, -0.83147f, -0.5556f, 0.0f, -0.8315f, 0.180372f, 0.113047f,
			-0.382683f, 1.0f, -0.92388f, -0.3827f, 0.0f, -0.9239f, 0.111025f, 0.182793f,
			-0.382683f, -1.0f, -0.92388f, -0.3827f, 0.0f, -0.9239f, 0.490754f, 0.508754f,
			-0.382683f, 1.0f, -0.92388f, -0.3827f, 0.0f, -0.9239f, 0.111025f, 0.182793f,
			-0.19509f, 1.0f, -0.980785f, -0.1951f, 0.0f, -0.9808f, 0.056582f, 0.264698f,
			-0.19509f, -1.0f, -0.980785f, -0.1951f, 0.0f, -0.9808f, 0.492376f, 0.510315f,
			-0.19509f, 1.0f, -0.980785f, -0.1951f, 0.0f, -0.9808f, 0.056582f, 0.264698f,
			0.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.01913f, 0.355628f,
			0.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.494248f, 0.511537f,
			0.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.01913f, 0.355628f,
			0.195091f, 1.0f, -0.980785f, 0.1951f, 0.0f, -0.9808f, 0.0001f, 0.452109f,
			0.195091f, -1.0f, -0.980785f, 0.1951f, 0.0f, -0.9808f, 0.496297f, 0.51238f,
			0.195091f, 1.0f, -0.980785f, 0.1951f, 0.0f, -0.9808f, 0.0001f, 0.452109f,
			0.382684f, 1.0f, -0.923879f, 0.3827f, 0.0f, -0.9239f, 0.000228f, 0.550466f,
			0.382684f, -1.0f, -0.923879f, 0.3827f, 0.0f, -0.9239f, 0.498441f, 0.512817f,
			0.382684f, 1.0f, -0.923879f, 0.3827f, 0.0f, -0.9239f, 0.000228f, 0.550466f,
			0.555571f, 1.0f, -0.831469f, 0.5556f, 0.0f, -0.8315f, 0.019522f, 0.646911f,
			0.555571f, -1.0f, -0.831469f, 0.5556f, 0.0f, -0.8315f, 0.500607f, 0.512831f,
			0.555571f, 1.0f, -0.831469f, 0.5556f, 0.0f, -0.8315f, 0.019522f, 0.646911f,
			0.707107f, 1.0f, -0.707106f, 0.7071f, 0.0f, -0.7071f, 0.05724f, 0.737726f,
			0.707107f, -1.0f, -0.707106f, 0.7071f, 0.0f, -0.7071f, 0.502711f, 0.512425f,
			0.707107f, 1.0f, -0.707106f, 0.7071f, 0.0f, -0.7071f, 0.05724f, 0.737726f,
			0.83147f, 1.0f, -0.55557f, 0.8315f, 0.0f, -0.5556f, 0.111918f, 0.819407f,
			0.83147f, -1.0f, -0.55557f, 0.8315f, 0.0f, -0.5556f, 0.504673f, 0.511619f,
			0.83147f, 1.0f, -0.55557f, 0.8315f, 0.0f, -0.5556f, 0.111918f, 0.819407f,
			0.92388f, 1.0f, -0.382683f, 0.9239f, 0.0f, -0.3827f, 0.181427f, 0.888813f,
			0.92388f, -1.0f, -0.382683f, 0.9239f, 0.0f, -0.3827f, 0.506421f, 0.510447f,
			0.92388f, 1.0f, -0.382683f, 0.9239f, 0.0f, -0.3827f, 0.181427f, 0.888813f,
			0.980785f, 1.0f, -0.195089f, 0.9808f, 0.0f, -0.1951f, 0.263078f, 0.943298f,
			0.980785f, -1.0f, -0.195089f, 0.9808f, 0.0f, -0.1951f, 0.507895f, 0.508953f,
			0.980785f, 1.0f, -0.195089f, 0.9808f, 0.0f, -0.1951f, 0.263078f, 0.943298f,
			1.0f, 1.0f, 1e-06f, 1.0f, 0.0f, 0.0f, 0.353713f, 0.980794f,
			1.0f, -1.0f, 1e-06f, 1.0f, 0.0f, 0.0f, 0.509032f, 0.507201f,
			1.0f, 1.0f, 1e-06f, 1.0f, 0.0f, 0.0f, 0.353713f, 0.980794f,
			0.980785f, 1.0f, 0.195091f, 0.9808f, 0.0f, 0.1951f, 0.449903f, 0.9999f,
			0.980785f, -1.0f, 0.195091f, 0.9808f, 0.0f, 0.1951f, 0.509863f, 0.50493f,
			0.980785f, 1.0f, 0.195091f, 0.9808f, 0.0f, 0.1951f, 0.449903f, 0.9999f,
			0.923879f, 1.0f, 0.382684f, 0.9239f, 0.0f, 0.3827f, 0.547968f, 0.9999f,
			0.923879f, -1.0f, 0.382684f, 0.9239f, 0.0f, 0.3827f, 0.510255f, 0.502549f,
			0.923879f, 1.0f, 0.382684f, 0.9239f, 0.0f, 0.3827f, 0.547968f, 0.9999f,
			0.831469f, 1.0f, 0.555571f, 0.8315f, 0.0f, 0.5556f, 0.644176f, 0.980801f,
			0.831469f, -1.0f, 0.555571f, 0.8315f, 0.0f, 0.5556f, 0.510195f, 0.500145f,
			0.831469f, 1.0f, 0.555571f, 0.8315f, 0.0f, 0.5556f, 0.644176f, 0.980801f,
			0.707106f, 1.0f, 0.707108f, 0.7071f, 0.0f, 0.7071f, 0.734846f, 0.94333f,
			0.707106f, -1.0f, 0.707108f, 0.7071f, 0.0f, 0.7071f, 0.509681f, 0.497807f,
			0.707106f, 1.0f, 0.707108f, 0.7071f, 0.0f, 0.7071f, 0.734846f, 0.94333f,
			0.555569f, 1.0f, 0.83147f, 0.5556f, 0.0f, 0.8315f, 0.816509f, 0.888916f,
			0.555569f, -1.0f, 0.83147f, 0.5556f, 0.0f, 0.8315f, 0.508734f, 0.495621f,
			0.555569f, 1.0f, 0.83147f, 0.5556f, 0.0f, 0.8315f, 0.816509f, 0.888916f,
			0.382682f, 1.0f, 0.92388f, 0.3827f, 0.0f, 0.9239f, 0.88605f, 0.819625f,
			0.382682f, -1.0f, 0.92388f, 0.3827f, 0.0f, 0.9239f, 0.507393f, 0.493668f,
			0.382682f, 1.0f, 0.92388f, 0.3827f, 0.0f, 0.9239f, 0.88605f, 0.819625f,
			0.195089f, 1.0f, 0.980786f, 0.1951f, 0.0f, 0.9808f, 0.940826f, 0.738052f,
			0.195089f, -1.0f, 0.980786f, 0.1951f, 0.0f, 0.9808f, 0.505721f, 0.492014f,
			0.195089f, 1.0f, 0.980786f, 0.1951f, 0.0f, 0.9808f, 0.940826f, 0.738052f,
			0.0f, 1.0f, 1.0f, -0.0f, 0.0f, 1.0f, 0.978704f, 0.647296f,
			0.0f, -1.0f, 1.0f, -0.0f, 0.0f, 1.0f, 0.503776f, 0.490732f,
		};

		_numVertices = 372;

		// setup plane VAO
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cylinderVertices), &cylinderVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	}

public:
	Material material;

	Cylinder() : material() {
		init();
		_shader = Shader::getDefault();
	}

	Cylinder(Material material) : material(material) {
		init();
		_shader = Shader::getDefault();
	}

	Cylinder(Shader* shader) : material() {
		init();
		_shader = shader;
	}

	Cylinder(Material material, Shader* shader) : material(material) {
		init();
		_shader = shader;
	}

	~Cylinder() {
		glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VBO);
	}

	void render(const glm::mat4& projection, const glm::mat4& view) override {
		if (_shader != nullptr) {
			_shader->use();
			_shader->setMat4("model", transform.getTransformationMatrix());
			_shader->setMat4("view", view);
			_shader->setMat4("projection", projection);
			_shader->setMat3("normalMat", getNormalMatrix());
			material.bind(_shader);
		}
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, _numVertices);
		glBindVertexArray(0);
	}

};