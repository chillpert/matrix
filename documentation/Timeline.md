# Timeline
This is an overview of planned and currently worked on features as well as issues that need to be fixed.

##### Core features
+ fully ray-trace based renderer
+ support for Direct3D and Vulkan
+ fully functional user interface
+ scripting
+ audio
+ animations
+ physics

##### Important Features
+ (GUI) add scroll bar to ```Explorer Window```
+ (GUI) add renaming feature to ```Hierachy Window```
+ (GUI) add up and down arrow to move nodes in scene graph in ```Hierachy Window```

##### Features
+ (GUI) display axes for selected node
+ (GUI) clickable elements in ```Viewport```
+ (Transform) review rotation component
+ (Renderer) ray intersection algorithm for general meshes

##### Important Issues
+ (GUI) buttons in ```Explorer Window``` should not move when scrolled
+ (GUI) image preview screen not working in ```Explorer Window```
+ (Renderer) lights do not get reset when scene is changed

##### Issues
+ (GUI) only leafs are drop sources in ```Hierachy```
+ (Events) imgui events are not bound to matrix event system
+ (Performance) add asynchronous model loading
+ (Performance) do small string optimizations
+ (Events) right click to control viewport should only be possible if done on viewport itself
+ (GUI) make ```Editor``` use the entire surface (does not seem to be possible in IMGUI)

##### Documentation Updates
+ add explanation on how to search nodes and cast their types
+ add explanation for ```Object Viewer``` including right click functions and context menu

##### Planned Applications
+ solar system simulator (with actual orbit physics)
+ build a Quake-like game showing matrix entire raytracing capabilities
