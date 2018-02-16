# PHP-GLFW

Write games with PHP! 



## Notes / Disclaimer

Nobody asked for a library like this and still, I delivered. Please don't spend a tremendous amount of time writing a "real game" in PHP with this. Just because its possible does not mean it is a good idea. I have no idea how you would ship / distribute such a game. Therefore this library hopefully serves an educational purpose for people who want to get into graphics programming and mainly work with PHP.

I'm very far from being an expert with the Zend engine and the PHP internals. So there are pieces in this code that will make you want to pull out your hair. My focus was to make this thing run, bugs, performance and memory leaks can be fixed later. Or probably never because again this is not supposed to create production applications with.

Also keep in mind I did not spend time making this failsafe in any way. When you pass unexpected types you might end up with a segmentation fault.

## Installation

Make sure to install glfw3 

```
$ brew install glfw3 
```

Now you should be able to build the extension:

```
$ phpize
$ ./configure --enable-glfw
$ make && make install
```

## Example

## Whats inside?

This extension does not only deliver glfw and OpenGL bindings, it also comes with `linmath` and `stb_image` to make getting started easy.

To avoid copying and hopefully therefor increase performance all vectors and matricies are resources & allocated on the heap which results in a very akward syntax.

## API Differences

I've tried to keep the API as similar as possible to the original C API of glfw and OpenGL, but I had to change some things to make this work easily with PHP. 

### GLFW 

#### glfwMakeContextCurrent

This method will automatically load the **glad** function pointers.

### OpenGL

#### glShaderSource

The last argument the `length` has been removed from the `glShaderSource` function. When you want to add multiple simply use null termination, or just call the method multiple times.

#### glBufferData

The `glBufferData` method has been disabled and is replaced with multiple type specific buffer methods:
 
 * glBufferDataFloat
 * glBufferDataDouble
 * glBufferDataInt
 * glBufferDataLong

Also you don't need to pass in the size of your data this is solved by the type specific methods itself.

```php
glBufferDataFloat(GL_ARRAY_BUFFER, [1.0, 0.5, 0.0], GL_STATIC_DRAW);
``` 

#### glVertexAttribPointer

In phpglfw the `stride` (byte offset) and `pointer` offset of the vertext attributes is a simple number representing the count and not the size of the data. The size is then determined by the given type.

So this attribute pointer in C:

```c
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
```

Would be written in php be:

```php
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5, 3);
```

