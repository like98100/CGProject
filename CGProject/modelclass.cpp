////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"

void ObjconvertToText(char*, char*);
void GetModelFilename(char* filename);
bool ReadFileCounts(char*, int&, int&, int&, int&);
bool LoadDataStructures(char*, int, int, int, int, char*);

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;

	m_indexCount = 0;
	m_vertexCount = 0;

	m_textureCount = 0;
	m_normalCount = 0;
	m_faceCount = 0;

	m_collider = 0;
	maxx = 0.0f;	maxy = 0.0f;	maxz = 0.0f;
	minx = 100.0f;	miny = 100.0f;	minz = 100.0f;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, const WCHAR* textureFilename)
{
	bool result;
	m_collider = new ColliderType;
	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}
//bool ModelClass::Initialize(ID3D11Device* device, const WCHAR* modelFilename, const WCHAR* textureFilename)
//{
//	bool result;
//	m_collider = new ColliderType;
//	// Load in the model data,
//	result = LoadModel(modelFilename);
//	if (!result)
//	{
//		return false;
//	}
//
//	// Initialize the vertex and index buffers.
//	result = InitializeBuffers(device);
//	if(!result)
//	{
//		return false;
//	}
//
//	// Load the texture for this model.
//	result = LoadTexture(device, textureFilename);
//	if(!result)
//	{
//		return false;
//	}
//
//	return true;
//}


void ModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool ModelClass::LoadTexture(ID3D11Device* device, const WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

//bool ModelClass::LoadModel(const WCHAR* filename)
//{
//	ReadFileCounts(filename);
//
//	return true;
//}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}

//bool ModelClass::ReadFileCounts(const WCHAR* filename)
//{
//	ifstream fin;
//	char input;
//	// Initialize the counts.
//	int vertexCount = 0;
//	int textureCount = 0;
//	int normalCount = 0;
//	int faceCount = 0;
//	// Open the file.
//	fin.open(filename);
//	// Check if it was successful in opening the file.
//	if (fin.fail() == true)
//	{
//		return false;
//	}
//	// Read from the file and continue to read until the end of the file is reached.
//	fin.get(input);
//	while (!fin.eof())
//	{
//		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
//		if (input == 'v')
//		{
//			fin.get(input);
//			if (input == ' ') { vertexCount++; }
//			if (input == 't') { textureCount++; }
//			if (input == 'n') { normalCount++; }
//		}
//
//		// If the line starts with 'f' then increment the face count.
//		if (input == 'f')
//		{
//			fin.get(input);
//			if (input == ' ') { faceCount++; }
//		}
//
//		// Otherwise read in the remainder of the line.
//		while (input != '\n')
//		{
//			fin.get(input);
//			if (fin.eof())
//				break;
//		}
//
//		// Start reading the beginning of the next line.
//		fin.get(input);
//	}
//	// Close the file.
//	fin.close();
//
//	LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
//
//	return true;
//}

//bool ModelClass::LoadDataStructures(const WCHAR* filename, int vertexCount, int textureCount, int normalCount, int faceCount)
//{
//	XMFLOAT3* vertices, * texcoords, * normals;
//	FaceType* faces;
//	ifstream fin;
//	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
//	char input, input2;
//	ofstream fout;
//
//	// Initialize the four data structures.
//	vertices = new XMFLOAT3[vertexCount];
//	if (!vertices)
//	{
//		return false;
//	}
//
//	texcoords = new XMFLOAT3[textureCount];
//	if (!texcoords)
//	{
//		return false;
//	}
//
//	normals = new XMFLOAT3[normalCount];
//	if (!normals)
//	{
//		return false;
//	}
//
//	faces = new FaceType[faceCount];
//	if (!faces)
//	{
//		return false;
//	}
//
//	// Initialize the indexes.
//	vertexIndex = 0;
//	texcoordIndex = 0;
//	normalIndex = 0;
//	faceIndex = 0;
//
//	// Open the file.
//	fin.open(filename);
//
//	// Check if it was successful in opening the file.
//	if (fin.fail() == true)
//	{
//		return false;
//	}
//
//	// Read in the vertices, texture coordinates, and normals into the data structures.
//	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
//	fin.get(input);
//	while (!fin.eof())
//	{
//		if (input == 'v')
//		{
//			fin.get(input);
//
//			// Read in the vertices.
//			if (input == ' ')
//			{
//				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >>
//					vertices[vertexIndex].z;
//
//				// Invert the Z vertex to change to left hand system.
//				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
//				vertexIndex++;
//			}
//
//			// Read in the texture uv coordinates.
//			if (input == 't')
//			{
//				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;
//				// Invert the V texture coordinates to left hand system.
//				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
//				texcoordIndex++;
//			}
//
//			// Read in the normals.
//			if (input == 'n')
//			{
//				fin >> normals[normalIndex].x >> normals[normalIndex].y >>
//					normals[normalIndex].z;
//
//				// Invert the Z normal to change to left hand system.
//				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
//				normalIndex++;
//			}
//		}
//
//		// Read in the faces.
//		if (input == 'f')
//		{
//			fin.get(input);
//			if (input == ' ')
//			{
//				// Read the face data in backwards to convert it to a left hand system from right hand system.
//				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >>
//					input2 >> faces[faceIndex].nIndex3 >> faces[faceIndex].vIndex2 >> input2 >>
//					faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2 >>
//					faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >>
//					faces[faceIndex].nIndex1;
//				faceIndex++;
//			}
//		}
//
//		// Read in the remainder of the line.
//		while (input != '\n')
//		{
//			fin.get(input);
//			if (fin.eof())
//				break;
//		}
//
//		// Start reading the beginning of the next line.
//		fin.get(input);
//	}
//
//	//// Close the file.
//	//fin.close();
//	//// Open the output file.
//	//fout.open("model.txt");
//	//// Write out the file header that our model format uses.
//	//fout << "Vertex Count: " << (faceCount * 3) << endl;
//	//fout << endl;
//	//fout << "Data:" << endl;
//	//fout << endl;
//
//	m_vertexCount = faceCount * 3;
//
//	// Set the number of indices to be the same as the vertex count.
//	m_indexCount = m_vertexCount;
//
//	// Create the model using the vertex count that was read in.
//	m_model = new ModelType[m_vertexCount];
//	if (!m_model)
//	{
//		return false;
//	}
//
//	// Now loop through all the faces and output the three vertices for each face.
//	for (int i = 0; i < faceIndex; i++)
//	{
//		vIndex = faces[i].vIndex1 - 1;
//		tIndex = faces[i].tIndex1 - 1;
//		nIndex = faces[i].nIndex1 - 1;
//		//fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
//		//	<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
//		//	<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
//
//		m_model[i * 3].x = vertices[vIndex].x;
//		m_model[i * 3].y = vertices[vIndex].y;
//		m_model[i * 3].z = vertices[vIndex].z;
//
//		m_model[i * 3].tu = texcoords[tIndex].x;
//		m_model[i * 3].tv = texcoords[tIndex].y;
//
//		m_model[i * 3].nx = normals[nIndex].x;
//		m_model[i * 3].ny = normals[nIndex].y;
//		m_model[i * 3].nz = normals[nIndex].z;
//
//		vIndex = faces[i].vIndex2 - 1;
//		tIndex = faces[i].tIndex2 - 1;
//		nIndex = faces[i].nIndex2 - 1;
//		//fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
//		//	<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
//		//	<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
//
//		m_model[i * 3 + 1].x = vertices[vIndex].x;
//		m_model[i * 3 + 1].y = vertices[vIndex].y;
//		m_model[i * 3 + 1].z = vertices[vIndex].z;
//
//		m_model[i * 3 + 1].tu = texcoords[tIndex].x;
//		m_model[i * 3 + 1].tv = texcoords[tIndex].y;
//
//		m_model[i * 3 + 1].nx = normals[nIndex].x;
//		m_model[i * 3 + 1].ny = normals[nIndex].y;
//		m_model[i * 3 + 1].nz = normals[nIndex].z;
//
//		vIndex = faces[i].vIndex3 - 1;
//		tIndex = faces[i].tIndex3 - 1;
//		nIndex = faces[i].nIndex3 - 1;
//		//fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
//		//	<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
//		//	<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
//
//		m_model[i * 3 + 2].x = vertices[vIndex].x;
//		m_model[i * 3 + 2].y = vertices[vIndex].y;
//		m_model[i * 3 + 2].z = vertices[vIndex].z;
//
//		m_model[i * 3 + 2].tu = texcoords[tIndex].x;
//		m_model[i * 3 + 2].tv = texcoords[tIndex].y;
//
//		m_model[i * 3 + 2].nx = normals[nIndex].x;
//		m_model[i * 3 + 2].ny = normals[nIndex].y;
//		m_model[i * 3 + 2].nz = normals[nIndex].z;
//	}
//
//	//// Close the output file.
//	//fout.close();
//
//	//모델 사이즈 측정 추가**
////x-----------------------
//	for (int i = 0; i < m_vertexCount; i++)
//	{
//		if (maxx < m_model[i].x)
//		{
//			maxx = m_model[i].x;
//		}
//	}
//	for (int i = 0; i < m_vertexCount; i++)
//	{
//		if (minx > m_model[i].x)
//		{
//			minx = m_model[i].x;
//		}
//	}
//	//y-----------------------
//	for (int i = 0; i < m_vertexCount; i++)
//	{
//		if (maxy < m_model[i].y)
//		{
//			maxy = m_model[i].y;
//		}
//	}
//	for (int i = 0; i < m_vertexCount; i++)
//	{
//		if (miny > m_model[i].y)
//		{
//			miny = m_model[i].y;
//		}
//	}
//	//z-----------------------
//	for (int i = 0; i < m_vertexCount; i++)
//	{
//		if (maxz < m_model[i].z)
//		{
//			maxz = m_model[i].z;
//		}
//	}
//	for (int i = 0; i < m_vertexCount; i++)
//	{
//		if (minz > m_model[i].z)
//		{
//			minz = m_model[i].z;
//		}
//	}
//	//***
//
//	// Release the four data structures.
//	if (vertices)
//	{
//		delete[] vertices;
//		vertices = 0;
//	}
//
//	if (texcoords)
//	{
//		delete[] texcoords;
//		texcoords = 0;
//	}
//
//	if (normals)
//	{
//		delete[] normals;
//		normals = 0;
//	}
//
//	if (faces)
//	{
//		delete[] faces;
//		faces = 0;
//	}
//
//	return true;
//}

float ModelClass::GetMaxX()
{
	return m_collider->maxx;
}

float ModelClass::GetMinX()
{
	return m_collider->minx;
}

float ModelClass::GetMaxY()
{
	return m_collider->maxy;
}

float ModelClass::GetMinY()
{
	return m_collider->miny;
}

float ModelClass::GetMaxZ()
{
	return m_collider->maxz;
}

float ModelClass::GetMinZ()
{
	return m_collider->minz;
}

// 콜라이더 생성 함수
void ModelClass::SetCollider(XMMATRIX scale, XMMATRIX trans, XMMATRIX rotate)
{
	//x-----------------------
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (maxx < m_model[i].x)
		{
			maxx = m_model[i].x;
		}
	}
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (minx > m_model[i].x)
		{
			minx = m_model[i].x;
		}
	}
	//y-----------------------
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (maxy < m_model[i].y)
		{
			maxy = m_model[i].y;
		}
	}
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (miny > m_model[i].y)
		{
			miny = m_model[i].y;
		}
	}
	//z-----------------------
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (maxz < m_model[i].z)
		{
			maxz = m_model[i].z;
		}
	}
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (minz > m_model[i].z)
		{
			minz = m_model[i].z;
		}
	}


	XMMATRIX m_ColliderInfo = /*rotate * */trans;

	XMVECTOR collider_row_3 = m_ColliderInfo.r[3];

	float collider_m30 = XMVectorGetX(collider_row_3);	//matrix 3, 0(x)
	float collider_m31 = XMVectorGetY(collider_row_3);	//matrix 3, 1(y)
	float collider_m32 = XMVectorGetZ(collider_row_3);	//matrix 3, 2(z)

	XMVECTOR scale_row_0 = scale.r[0];
	XMVECTOR scale_row_1 = scale.r[1];
	XMVECTOR scale_row_2 = scale.r[2];

	float scale_m00 = XMVectorGetX(scale_row_0);	//matrix 0, 0(x)
	float scale_m11 = XMVectorGetY(scale_row_1);	//matrix 1, 1(y)
	float scale_m22 = XMVectorGetZ(scale_row_2);	//matrix 2, 2(z)

	m_collider->maxx = collider_m30 + ((maxx - minx) * scale_m00) / 2.0f;
	m_collider->minx = collider_m30 - ((maxx - minx) * scale_m00) / 2.0f;

	m_collider->maxy = collider_m31 + ((maxy - miny) * scale_m11) / 2.0f;
	m_collider->miny = collider_m31 - ((maxy - miny) * scale_m11) / 2.0f;

	m_collider->maxz = collider_m32 + ((maxz - minz) * scale_m22) / 2.0f;
	m_collider->minz = collider_m32 - ((maxz - minz) * scale_m22) / 2.0f;

	//printf("성공\n");
}

void ModelClass::SetCollider(float Xpos, float Ypos, float Zpos)
{
	m_collider->maxx = Xpos + 5 / 2;
	m_collider->minx = Xpos - 5 / 2;
	m_collider->maxy = Ypos + 5 / 2;
	m_collider->miny = Ypos - 5 / 2;
	m_collider->maxz = Zpos + 5 / 2;
	m_collider->minz = Zpos - 5 / 2;
}

// 콜라이더 체크 함수
bool ModelClass::checkCollider(float maxx, float minx, float maxy, float miny, float maxz, float minz)
{
	if ((minx <= m_collider->maxx && m_collider->maxx <= maxx) || (minx <= m_collider->minx && m_collider->minx <= maxx))
	{
		if ((miny <= m_collider->maxy && m_collider->maxy <= maxy) || (miny <= m_collider->miny && m_collider->miny <= maxy))
		{
			if ((minz <= m_collider->maxz && m_collider->maxz <= maxz) || (minz <= m_collider->minz && m_collider->minz <= maxz))
			{
				return true;
			}
		}
	}
	return false;
}

int ModelClass::getPolygon()
{
	return m_indexCount / 3;
}

typedef struct
{
	float x, y, z;
}VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;

void ObjconvertToTxt(char* filename, char* readfile)
{
	bool result;
	int vertexCount, textureCount, normalCount, faceCount;

	GetModelFilename(filename);

	// Read in the number of vertices, tex coords, normals, and faces so that the data structures can be initialized with the exact sizes needed.
	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return;
	}

	// Now read the data from the file into the data structures and then output it in our model format.
	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount, readfile);
	if (!result)
	{
		return;
	}
}

void GetModelFilename(char* filename)
{
	bool done;
	ifstream fin;

	// Loop until we have a file name.
	done = false;
	while (!done)
	{
		// Attempt to open the file.
		fin.open(filename);

		if (fin.good())
		{
			// If the file exists and there are no problems then exit since we have the file name.
			done = true;
		}
		else
		{
			// If the file does not exist or there was an issue opening it then notify the user and repeat the process.
			fin.clear();
		}
	}
	return;
}

bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;


	// Initialize the counts.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	fin.get(input);
	while (!fin.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// If the line starts with 'f' then increment the face count.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

		// Otherwise read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	return true;
}


bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount, char* readfile)
{
	VertexType* vertices, * texcoords, * normals;
	FaceType* faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	ofstream fout;


	// Initialize the four data structures.
	vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	// Initialize the indexes.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}

	// Read in the vertices, texture coordinates, and normals into the data structures.
	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// Read in the vertices.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Invert the Z vertex to change to left hand system.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			// Read in the texture uv coordinates.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// Invert the V texture coordinates to left hand system.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// Read in the normals.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Invert the Z normal to change to left hand system.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// Read in the faces.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// Read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	// Open the output file.
	fout.open(readfile);

	// Write out the file header that our model format uses.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data:" << endl;
	fout << endl;

	// Now loop through all the faces and output the three vertices for each face.
	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}

	// Close the output file.
	fout.close();

	// Release the four data structures.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	char readfile[50];
	strcpy_s(readfile, 50, filename);
	strcat_s(readfile, 50, txt);

	ObjconvertToTxt(filename, readfile);

	// Open the model file.
	fin.open(readfile);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	remove((CHAR*)readfile);

	//모델 사이즈 측정 추가************************************
	////x-----------------------
	//for (int i = 0; i < m_vertexCount; i++)
	//{
	//	if (maxx < m_model[i].x)
	//	{
	//		maxx = m_model[i].x;
	//	}
	//}
	//for (int i = 0; i < m_vertexCount; i++)
	//{
	//	if (minx > m_model[i].x)
	//	{
	//		minx = m_model[i].x;
	//	}
	//}
	////y-----------------------
	//for (int i = 0; i < m_vertexCount; i++)
	//{
	//	if (maxy < m_model[i].y)
	//	{
	//		maxy = m_model[i].y;
	//	}
	//}
	//for (int i = 0; i < m_vertexCount; i++)
	//{
	//	if (miny > m_model[i].y)
	//	{
	//		miny = m_model[i].y;
	//	}
	//}
	////z-----------------------
	//for (int i = 0; i < m_vertexCount; i++)
	//{
	//	if (maxz < m_model[i].z)
	//	{
	//		maxz = m_model[i].z;
	//	}
	//}
	//for (int i = 0; i < m_vertexCount; i++)
	//{
	//	if (minz > m_model[i].z)
	//	{
	//		minz = m_model[i].z;
	//	}
	//}
	//***********************************************************
	return true;
}