# Documentation

This is the official (still very incomplete and WIP) documentation for Matrix. As features will finalize the documentation will be extended and kept up to date. It will work as a reminder for myself on implementation details, when I take longer breaks from developing on Matrix.

## Building Matrix
As of now there are no prebuild binaries available. Therefore you have to at least build matrix once. Matrix requires a few other repositories such as [SDL2](https://github.com/spurious/SDL-mirror) and [Assimp](https://github.com/assimp/assimp
). So do not forget to add ```--recursive```. Building requires ```Cmake Version 3.14.0``` or higher. At this time the default build setting is set to debug.

Building on Linux:
```sh
$ git clone https://github.com/chillpert/matrix --recursive
$ cd matrix
$ mkdir build
$ cd build
$ cmake ..
$ make all
```

Building on Windows should be just as self-explanatory. 

## General
All public functions provided by Matrix need to accessed using the ```MX::``` namespace. There are a bunch of macros that you can use to address core parts that you might want to use frequently. 
| Macro | Function | Type |
| :------ | :------: | -----: |
| MX_WORLD | Returns an object that holds all scenes of your loaded project | Object |
| MX_SCENE | Returns the currently active scene | Shared pointer |
| MX_SCENEGRAPH | Returns the scene graph of the currently active scene | Object |
| MX_CAMERA | Returns the camera of the currently active scene | Object |

## Scene Graph
Each scene has its own scene graph. At this moment in time there are a total of seven different nodes available.

#### Node
A node is an object of the base class. Most functions require a pointer to an object of this exact type. This class is pure virtual, therefore no instances can be created.
| Member | Meaning | Type |
| ------ | ------ | ----- |
| m_name | An unique name | std::string |
| m_shader | Shader used for rendering | std::shared_ptr<Shader> |
| m_parent | The parent of this node | Node* |
| m_children | All the children of this node | std::list<std::shared_ptr<Node>> |
| m_trans | Used to handle all basic types of transformation | Transform |
| m_visible | If set to false, object will not be rendered | bool |

#### Geometry Node
A geometry node is the only node that is actually visible, since it can hold any type of model that Matrix can handle.
| Member | Meaning | Type |
| ------ | ------ | ----- |
| m_model | The model of this node | std::shared_ptr<Model> m_Model |
| m_textures | contains all supported types of textures | std::shared_ptr<TextureProfile> |
| m_material | contains ambient, diffuse, specular and shininess properties of object | MaterialProfile |

The supported texture types are diffuse, specular, normal, bump and height maps. As of now only the first two are implemented. 

#### Container Node
A container node should be used to structure the scene graph by encapsulating nodes. It doesn't have any more functionality than the base class. 

#### Light Node
A light node is a pure virtual function, therefore no instances can be created. Use any inherited type below to illuminate your scene.
| Member | Meaning | Type |
| ------ | ------ | ----- |
| m_ambient | Ambient lighting property | glm::vec3 |
| m_diffuse | Diffuse lighting property | glm::vec3 |
| m_specular | Specular lighting property | glm::vec3 |
| m_ambient_strength | Intensity of ambient lighting | float |

#### Directional Light Node
A directional light node is a light source that uniformly illuminates your entire scene with equal intensity from one direction.
| Member | Meaning | Type |
| ------ | ------ | ----- |
| m_direction | Direction the light is coming from | glm::vec3 |

#### Point Light Node
A point light node is a light source that illuminates everything around it. It features light attenuation.
| Member | Meaning | Type |
| ------ | ------ | ----- |
| m_position | Position of light in world space | glm::vec3 |
| m_constant | Constant parameter of light attenuation | float |
| m_linear | Linear parameter of light attenuation | float |
| m_quadratic | Quadratic parameter of light attenuation | float |

#### Spot Light Node
A spot light node is a light source that creates a beam of light, similiar to a flashlight . It features light attenuation.
| Member | Meaning | Type |
| ------ | ------ | ----- |
| m_position | Position of light in world space | glm::vec3 |
| m_direction | Direction the light is coming from | glm::vec3 |
| m_constant | Constant parameter of light attenuation | float |
| m_linear | Linear parameter of light attenuation | float |
| m_quadratic | Quadratic parameter of light attenuation | float |
| m_cut_off | Inner cone of spot light | float |
| m_outer_cut_off | Outer cone of spot light | float

## Assets and Resources
All your files need to be somewhere within the Matrix main directory or any subdirectory recursively. Any other files can not be loaded nor accessed from the ```Explorer window``` in the user interface. This is because only relative paths will be used for loading and saving scene files. Scene files can be made from scratch without using the user interface, but it is not recommended to do so. However one can change simple entries, e.g. names and paths of any entity. Scenes for Matrix need to be saved to a file with the ending ".mx". You can use the Explorer window to get previews of multiple files, such as image files. Planned are previews for all types of files that matrix can work with.

To avoid any duplication of resources like textures or models, any already loaded data can be reused by using the following macros. The functions require the object's full path for searching. 

| Macro | Function | Type |
| ------ | ------ | ----- |
| MX_GET_SHADER(x) | Returns a shader and initializes it, if not already done  | Shared pointer |
| MX_GET_MODEL(x) | Returns a model and initializes it, if not already done | Shared pointer |
| MX_GET_TEXTURE(x) | Returns a texture and initializes it, if not already done | Shared pointer |

These macros can not be used to create objects.
