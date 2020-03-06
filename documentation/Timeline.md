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
+ (GUI) implement sorting features in ```Explorer Window```

##### Features
+ (GUI) add preview for all common file types to ```Explorer Window``` 
+ (GUI) display axes for selected node
+ (GUI) clickable elements in ```Viewport``` 
+ (GUI) implement highlighting in ```Explorer Window```
+ (GUI) add renaming feature to ```Hierachy Window```
+ (GUI) add up and down arrow to move nodes in scene graph in ```Hierachy Window```
+ (GUI) implement ```Object Viewer``` for light sources
+ (Transform) review rotation component
+ (Renderer) ray intersection algorithm for general meshes
+ (GUI) add hard corners for buttons context menu in ```Explorer Window``` 
+ (GUI) image preview screen not working in ```Explorer Window``` 
+ (GUI) abstract hover info logic into new inherited popup class 

##### Important Issues
+ 

##### Issues
+ (GUI) right click context menues are not intuitive enough
+ (GUI) only leafs are drop sources in ```Hierachy```
+ (Renderer) lights do not get reset when scene is changed
+ (Events) imgui events are not bound to matrix event system
+ (Performance) add asynchronous model loading
+ (Performance) do small string optimizations
+ (GUI) pop up modals don't open
+ (GUI) delete button causes CTD
+ (GUI) improve visual fidelity of ```Explorer Window```'s context menu 
+ (GUI) continue swapping context menus with normal popups
+ (Events) right click to control viewport should only be possible if done on viewport itself

##### Documentation Updates
+ add explanation on how to search nodes and cast their types
+ add explanation for ```Object Viewer``` including right click functions and context menu

##### Planned Applications
+ solar system simulator (with actual orbit physics)
+ build a Quake-like game