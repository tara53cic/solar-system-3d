#include "../Header/Vertices.h"

//temena 


//plo?ica sa imenom

float verticesNametag[] = {
    //   X      Y      U     V
    -1.0f, -0.85f,   0.0f, 1.0f, // top-left
    -1.0f, -1.0f,   0.0f, 0.0f, // bottom-left
    -0.4f, -1.0f,   1.0f, 0.0f, // bottom-right
    -0.4f, -0.85f,   1.0f, 1.0f  // top-right
};

//pozadina za Distance tekst

float verticesTopLeftRect[] = {
    //   X       Y      U     V
    -1.0f,  1.0f,    0.0f, 1.0f,  // top-left
    -1.0f,  0.85f,    0.0f, 0.0f,  // bottom-left
    -0.4f,  0.85f,    1.0f, 0.0f,  // bottom-right
    -0.4f,  1.0f,    1.0f, 1.0f   // top-right
};

//video

float videoVertices[] = {
	// Positions   // TexCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};

std::vector<float> generateCrosshairVertices(float aspect) {
	float cSize = 0.02f;
	float thick = 0.003f;

	float cSizeX = cSize / aspect;
	float thickX = thick / aspect;

	return {
		// Vertical Rectangle
		-thickX,  cSize,  0.0f, 1.0f,
		-thickX, -cSize,  0.0f, 0.0f,
		 thickX, -cSize,  1.0f, 0.0f,
		-thickX,  cSize,  0.0f, 1.0f,
		 thickX, -cSize,  1.0f, 0.0f,
		 thickX,  cSize,  1.0f, 1.0f,

		 // Horizontal Rectangle
		 -cSizeX,  thick,  0.0f, 1.0f,
		 -cSizeX, -thick,  0.0f, 0.0f,
		  cSizeX, -thick,  1.0f, 0.0f,
		 -cSizeX,  thick,  0.0f, 1.0f,
		  cSizeX, -thick,  1.0f, 0.0f,
		  cSizeX,  thick,  1.0f, 1.0f
	};
}


std::vector<float> generateSphere(float radius, int sectorCount, int stackCount) {
	std::vector<float> vertices;

	for (int i = 0; i <= stackCount; ++i) {
		float stackAngle = M_PI / 2 - i * M_PI / stackCount;
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; ++j) {
			float sectorAngle = j * 2 * M_PI / sectorCount;

			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);

			// Pozicija
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Boja
			vertices.push_back(0.2f);
			vertices.push_back(0.6f);
			vertices.push_back(1.0f);
			vertices.push_back(1.0f);
		}
	}
	return vertices;
}


SphereMesh generateSphereTextured(float radius, int sectorCount, int stackCount) {
	SphereMesh mesh;

	for (int i = 0; i <= stackCount; ++i) {
		float stackAngle = M_PI / 2 - i * M_PI / stackCount;
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle); 

		for (int j = 0; j <= sectorCount; ++j) {
			float sectorAngle = j * 2 * M_PI / sectorCount;

			float x = xy * cosf(sectorAngle);
			float y = xy * sin(sectorAngle);

			// Pozicija
			mesh.vertices.push_back(x);
			mesh.vertices.push_back(y);
			mesh.vertices.push_back(z);

			// Boja
			mesh.vertices.push_back(0.2f);
			mesh.vertices.push_back(0.6f);
			mesh.vertices.push_back(1.0f);
			mesh.vertices.push_back(1.0f);

			// UV 
			float u = (float)j / sectorCount; 
			float v = 1-((float)i / stackCount);  
			mesh.vertices.push_back(u);
			mesh.vertices.push_back(v);
		}
	}

	for (int i = 0; i < stackCount; ++i) {
		int k1 = i * (sectorCount + 1);
		int k2 = k1 + sectorCount + 1;

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
			mesh.indices.push_back(k1);
			mesh.indices.push_back(k2);
			mesh.indices.push_back(k1 + 1);

			mesh.indices.push_back(k1 + 1);
			mesh.indices.push_back(k2);
			mesh.indices.push_back(k2 + 1);
		}
	}

	return mesh;
}

RingMesh generateRing(
	float innerRadius,
	float outerRadius,
	int segments
) {
	RingMesh mesh;

	for (int i = 0; i <= segments; i++) {
		float angle = (float)i / segments * 2.0f * M_PI;
		float cosA = cosf(angle);
		float sinA = sinf(angle);

		mesh.vertices.insert(mesh.vertices.end(), {
			outerRadius * cosA, 0.0f, outerRadius * sinA,
			1.0f, 1.0f, 1.0f, 1.0f,
			(float)i / segments, 1.0f
			});

		mesh.vertices.insert(mesh.vertices.end(), {
			innerRadius * cosA, 0.0f, innerRadius * sinA,
			1.0f, 1.0f, 1.0f, 1.0f,
			(float)i / segments, 0.0f
			});
	}

	for (unsigned int i = 0; i < segments * 2; i += 2) {
		mesh.indices.insert(mesh.indices.end(), {
			i, i + 1, i + 2,
			i + 1, i + 3, i + 2
			});
	}

	return mesh;
}

SphereMesh generatePlanetTextured(float radius, int sectorCount, int stackCount) {
	SphereMesh mesh;
	float lengthInv = 1.0f / radius;

	for (int i = 0; i <= stackCount; ++i) {
		float stackAngle = M_PI / 2 - i * M_PI / stackCount;
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; ++j) {
			float sectorAngle = j * 2 * M_PI / sectorCount;
			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);

			// 1. Position (3 floats)
			mesh.vertices.push_back(x);
			mesh.vertices.push_back(y);
			mesh.vertices.push_back(z);

			// 2. Normal (3 floats)
			mesh.vertices.push_back(x * lengthInv);
			mesh.vertices.push_back(y * lengthInv);
			mesh.vertices.push_back(z * lengthInv);

			// 3. Color (4 floats)
			mesh.vertices.push_back(0.2f); mesh.vertices.push_back(0.6f);
			mesh.vertices.push_back(1.0f); mesh.vertices.push_back(1.0f);

			// 4. UV (2 floats)
			mesh.vertices.push_back((float)j / sectorCount);
			mesh.vertices.push_back(1.0f - ((float)i / stackCount));
		}
	}
	for (int i = 0; i < stackCount; ++i) {
		int k1 = i * (sectorCount + 1);
		int k2 = k1 + sectorCount + 1;

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
			mesh.indices.push_back(k1);
			mesh.indices.push_back(k2);
			mesh.indices.push_back(k1 + 1);

			mesh.indices.push_back(k1 + 1);
			mesh.indices.push_back(k2);
			mesh.indices.push_back(k2 + 1);
		}
	}
	return mesh;
}







