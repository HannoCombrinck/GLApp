---
title: Debugging OpenGL Applications 
author: Hanno Combrinck
slideLevel: 2
incremental: False
---

Debugging OpenGL Applications
-----------------------------

* Novice graphics programming experiences
* Common problems
* How these problems are solved
* Available graphics debugging tools
* How the tools work
* What you need to know to use the tools properly
* Examples


First graphics programming experiences 
--------------------------------------

Getting started with writing grahics applications can be painful...

* I did everything exactly like the tutorial said and there's nothing on the screen
* I completely rewrote the shaders and the rendered image still looks the same
* I did the math a hundred times and the result is exactly the opposite of what I expected


Why this happens
----------------

* The graphics pipeline can be seen as one big state machine
* Large number of bugs result from:
	* State not being set
	* State not being set correctly
	* State changes not being tracked properly


How these problems are solved
-----------------------------

* Trial and error
* Shooting in the dark
* Plain guessing 


How to solve these problems without pulling your hair out
---------------------------------------------------------

* Check ALL API errors and warnings
* Use the right tools


OpenGL debugging tools
----------------------

* [GDEBugger](http://www.gremedy.com)
* [NVidia NSight](http://www.nvidia.com/object/nsight.html)
* [VOGL](https://github.com/ValveSoftware/vogl)
* [GLSLDevil](http://www.vis.uni-stuttgart.de/glsldevil)
* [BuGLe](http://www.opengl.org/sdk/tools/BuGLe)
* [APITrace](https://github.com/apitrace/apitrace)
* [GLIntercept](https://code.google.com/p/glintercept)


OpenGL debugging tools
----------------------

Tools let you:

* Keep track of and record API interaction
* Take pipeline state snapshots
	* Inspect state
	* Inspect graphics memory


What you need to know
---------------------

For these debugging tools to be usefull it's important to understand all the phases of the graphics pipeline

* High level understanding of what each phase does
* What are the inputs and outputs of each phase
* Which states affect which phases of the pipeline


OpenGL Pipeline
---------------

![](/media/RenderingPipeline.png)

OpenGL Pipeline
---------------

* Pipeline input
	* VBO - Vertex Buffer Object
		* Actual vertex data 
	* VAO - Vertex Array Object
		* Vertex attributes that defines structure of vertex data

![](/media/VAOVBO.png)


OpenGL Pipeline
---------------

![](/media/RenderingPipeline1.png)

OpenGL Pipeline
---------------

* Vertex processing
	* Programmable via Vertex shader
	* Receives vertices as input and outputs transformed vertices
	* Typically applies world, view and projection matrices to transform vertices into clip-space

![](/media/heightmap.gif)

OpenGL Pipeline
---------------

* Primitive assembly
	* Collects output of vertex shaders and compose into primitive shapes

![](/media/Primitives.png)

OpenGL Pipeline
---------------

![](/media/RenderingPipeline2.png)


OpenGL Pipeline
---------------

* Tessellation (Optional phase)
	* Programmable via Tessellation Control and Evaluation shaders 
	* Tessellation Control defines how much new geometry is injected
	* Tessellation Evaluation transforms newly injected geometry

![](/media/Geodesic.gif)
(Gif from [The Little Grasshopper blog](http://prideout.net/blog/?p=48))

OpenGL Pipeline
---------------

![](/media/RenderingPipeline3.png)

OpenGL Pipeline
---------------

* Primitive processing (Optional phase)
	* Programmable via Geometry shader
	* Receives input from primitive assembly as input and outputs primitive
	* Can output zero or more primitives 
	* Can ouput completely different type of primitives

![](/media/GeometryShader.png)

OpenGL Pipeline
---------------

![](/media/RenderingPipeline4.png)

OpenGL Pipeline
---------------

* Transform Feedback (Optional opt-out)
	* Skips rest of the pipeline and returns output of geometry shader
	* Useful for GPU particle systems


OpenGL Pipeline
---------------

![](/media/RenderingPipeline5.png)


OpenGL Pipeline
---------------

* Clipping and Culling
	* Primitives outside fixed viewing volume are discarded
	* Custom clipping planes can be provided for additional clipping
	* Face culling (e.g. back facing primitives are discarded)
	* Viewport transform - primitive vertices are transformed from clip-space to window space


OpenGL Pipeline
---------------

![](/media/RenderingPipeline6.png)

OpenGL Pipeline
---------------

* Rasterization
	* Receives primitives as input and outputs sequence of fragments
	* Fragment data is interpolated from vertex data

![](/media/Rasterization.png)

OpenGL Pipeline
---------------

![](/media/RenderingPipeline7.png)

OpenGL Pipeline
---------------

* Fragment processing 
	* Programmable via Fragment shader
	* Receives input from rasterizer and outputs colours, depth values and stencil values
	* Only colour and depth output is programmable
	* Different colours can be output to different buffers simultaneously
	* Depth and stencil values can only be written to a single depth buffer at a time

OpenGL Pipeline
---------------

![](/media/RenderingPipeline8.png)

OpenGL Pipeline
---------------

* Per-Sample Operations
	* Receives input from fragment shaders and outputs final, if any, pixel to framebuffer
	* Performs stencil test
	* Performs depth test
	* Performs blending operation
	* Performs masking operations - colour, depth and stencil values can be masked
	* Blended fragments that pass all tests and aren't masked are written to the framebuffer

OpenGL Pipeline
---------------

![](/media/RenderingPipeline9.png)

Demo time!
----------
