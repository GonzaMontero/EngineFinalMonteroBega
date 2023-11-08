#include "ModelImp.h"
#include "glew.h"

using namespace Engine;

ModelImp::ModelImp() {
    _path = "";
    _directory = "";
}

ModelImp::ModelImp(string path, const char* modelTexture, Shader& shader, Renderer* renderer) : Entity2D() {

    _modelTexture = modelTexture;
    LoadModel(path);

    _shader = shader;
    _renderer = renderer;
}

ModelImp::ModelImp(string path, Shader& shader, Renderer* renderer) : Entity2D() {

    LoadModel(path);
    _shader = shader;
    _renderer = renderer;
    _texImporter = new TextureImporter();

}

ModelImp::~ModelImp() {

    if (_texImporter != NULL) {
        delete _texImporter;
        _texImporter = NULL;
    }
    if (_rootNode) {
        delete _rootNode;
        _rootNode = NULL;
    }
    if (!_meshes.empty()) {
        for (auto* mesh : _meshes) {
            if (mesh != NULL) {
                delete mesh;
                mesh = NULL;
            }
        }
        _meshes.clear();
    }
    if (!_rootNodeChildren.empty()) {
        for (auto* nodeChilds : _rootNodeChildren) {
            if (nodeChilds != NULL) {
                delete nodeChilds;
                nodeChilds = NULL;
            }
        }
        _rootNodeChildren.clear();
    }

    if (_boundingVolume != NULL) {
        delete _boundingVolume;
        _boundingVolume = NULL;
    }
}

void ModelImp::MoveModel(glm::vec3 direction) {

    for (int i = 0; i < _meshes.size(); i++) {
        _meshes[i]->Translate(direction.x, direction.y, direction.z);
    }

}

void ModelImp::ScaleModel(float x, float y, float z) {

    _rootNodeChildren[6]->_parent->Scale(x, y, z);
}

void ModelImp::RotateModelX(float x) {

    for (int i = 0; i < 1; i++) {
        _meshes[i]->RotateX(x);
    }
}

void ModelImp::RotateModelY(float y) {

    for (int i = 0; i < _meshes.size(); i++) {
        _meshes[i]->RotateY(y);
    }
}

void ModelImp::RotateModelZ(float z) {

    for (int i = 0; i < _meshes.size(); i++) {
        _meshes[i]->RotateZ(z);
    }
}

void ModelImp::LoadModel(string path) {

    Assimp::Importer importer; //First declare an Importer object from Assimp Namespace

    //Call the Importer큦 readFile which expects both a pass and post processing as its second argument (where we can force the 
    //importer to make extra calculations and operations on the data)
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

    //The Post Processing Options, in order, do:

    //aiProcess_Triangulate - Specify Assimp that the model is not entirely composed of triangles
    //aiProcess_GenNormals - Generates smooth normal vectors for each vertex if the model doesn't contain normal vectors.
    //aiProcess_CalcTangentSpace - Calculates tangents and Bi Tangents for all imported meshes
    //aiProcess_FlipUVs -  Flips the texture coordinates on the y-axis where necessary during processing


    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        //If te scene and root node are not null or DATA IS INCOMPLETE we return the error string
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }

    //Get the directory of the file path
    _directory = path.substr(0, path.find_last_of('/'));

    if (scene)
        ProcessNode(scene->mRootNode, scene, nullptr); //Pass the root node to a recursive function

    //_boundingVolume = GenerateGlobalAABB();

    std::cout << "rootNodeChildren: " << _rootNodeChildren.size() << std::endl;

}

AABB* ModelImp::GenerateGlobalAABB() {
    //Get global scale thanks to our transform
    glm::vec3 globalCenter{ GetModel() * glm::vec4(_boundingVolume->GetCenter(), 1.0f) };

    // Scaled orientation
    glm::vec3 right = transform.right * _boundingVolume->GetExtents().x;
    glm::vec3 up = transform.up * _boundingVolume->GetExtents().y;
    glm::vec3 forward = transform.forward * _boundingVolume->GetExtents().z;

    float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
        std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
        std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

    float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

    float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

    AABB* newAABB = new AABB(globalCenter, newIi, newIj, newIk);
    return newAABB;
}

void ModelImp::ProcessNode(aiNode* node, const aiScene* scene, Entity2D* parent) {
    
    Entity2D* actualNode = nullptr;

    if (parent == nullptr) { //Si no hay padre procesamos el nodo actual y agregamos como child una entity normalizada
        _rootNode = new Entity2D();
        actualNode = _rootNode;
        std::cout << "No hay padre, agregando hijo" << std::endl;
        //SetParent(_rootNode);
        AddChild(_rootNode);
    }

    if(parent) { //Si hay padre hacemos el nodo actual hijo del padre.
        actualNode = new Entity2D();
        parent->AddChild(actualNode);
        std::cout << "Hay padre, nodo actual hijo del padre" << std::endl;
        _rootNodeChildren.push_back(actualNode);
    }

    if (node->mNumMeshes > 0) {
        for (int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            Mesh* nMesh = ProcessMesh(mesh, scene);
            actualNode->AddChild(nMesh);
            _meshes.push_back(nMesh);
        }
    }


    std::cout << "Entro en ProcessNode!!!" << std::endl;

    //for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    //    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    //    _meshes.push_back(ProcessMesh(mesh, scene)); //pusehar la ultima mesh encontrada
    //}
    //
    ////procesar nodos para que se agrupen por jerarquia
    //

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene, actualNode);
    }
}

Mesh* ModelImp::ProcessMesh(aiMesh* mesh, const aiScene* scene) {

    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        //Process mesh positions, normals and UVs

        /*
        Processing a mesh is a 3-part process: retrieve all the vertex data, retrieve the mesh's indices, 
        and finally retrieve the relevant material data. The processed data is stored in one of the 3 vectors and 
        from those a Mesh is created and returned to the function's caller.
        */

        //We define a temporary Vec3 to store Assimp큦 data since it uses a different data type
        glm::vec3 vector;

        //In this case we store the vertex positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //If the mesh has normals, the procedure is roughly the same
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        //If the mesh contains texture coordinates (which is not always the case)
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex); //The process is repeated for each iteration of the mesh큦 vertices
    }

    /*
    Assimp's interface defines each mesh as having an array of faces, where each face represents a single primitive, 
    which in our case (due to the aiProcess_Triangulate option) are always triangles. A face contains the indices of the 
    vertices we need to draw in what order for its primitive. So if we iterate over all the faces and store all the face's 
    indices in the indices vector we're all set
    */

    //We use a for loop to iterate between each of its faces
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++) //Another loop to iterate between all indices in a face
            indices.push_back(face.mIndices[j]);
    }

    /*
    Similar to nodes, a mesh only contains an index to a material object. To retrieve the material of a mesh, 
    we need to index the scene's mMaterials array. The mesh's material index is set in its mMaterialIndex property, 
    which we can also query to check if the mesh contains a material or not:
    */
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex]; 

    //_boundingVolume = GenerateAABB(_meshes, vertices);

    //Load the material큦 diffuse texture
    vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuseM");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    //Load the material큦 specular texture
    vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specularM");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    //Load the material큦 normal texture
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    //Load the material큦 height texture
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    Mesh* newMesh = new Mesh(vertices, indices, textures, _meshes, _shader, _renderer);
    return newMesh;
}

vector<Texture> ModelImp::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {

    vector<Texture> textures;
    
    //We iterate over all texture locations of the texture type in order to retrieve the file location so we can load
    //and generate the texure and store it in a Vertex struct (in this case, the textures vertex)

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {

        aiString str; //aiString declaration for use in the next line

        mat->GetTexture(type, i, &str); //We use the GetTexture function which stores the file location in an aiString

        bool skip = false;

        for (unsigned int j = 0; j < _textures_loaded.size(); j++) {

            //We check if the texture which we are trying to load has already been loaded previously, so we can skip
            //loading and generation and use the located texture as the mesh큦 texture (this is due to loading and generating
            //a texture being an expensive process) 
            if (std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(_textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            //If the texture has not been loaded yet, we load it
            Texture texture;

            texture.id = _texImporter->TextureFromFile(str.C_Str(), this->_directory);
            texture.type = typeName;
            texture.path = str.C_Str();

            textures.push_back(texture);
            _textures_loaded.push_back(texture); //Add texture to loaded textures
        }
    }

    return textures;
}

void ModelImp::Draw(Shader& shader, Frustrum frustum) {

    UpdateSelfAndChild();
    UpdateVectors();

    std::cout << "_meshes size: " << _meshes.size() << std::endl;
    if (!_meshes.empty()) {
        for (auto* mesh : _meshes) {
            if (mesh != NULL) {
                //if(_boundingVolume->IsOnFrustum(frustum, mesh))
                mesh->Draw(shader, frustum);
            }
        }
    }
}

unsigned int ModelImp::TextureFromFile(const char* path, string const& directory, bool gamma) {

    string filename = string(path);
    filename = directory + '/' + path;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;

        if (nrComponents == 1)
            format = GL_RED;

        else if (nrComponents == 3)
            format = GL_RGB;

        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void ModelImp::LoadTexture() {

    if (_texImporter) {

        _texImporter->LoadImage(_width, _height, _transparency);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
        unsigned int textureDiffuseLoc = glGetUniformLocation(_shader.GetID(), "texture_diffuse1");
        glUniform1i(textureDiffuseLoc, _texImporter->GetTexture());
        glDisable(GL_TEXTURE_2D);
    }
}

unsigned int ModelImp::TextureModel(const char* texture) {

    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrComponents;
    unsigned char* data = stbi_load(texture, &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << texture << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}