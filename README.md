**`animation_render`**
  * args:
    * Animation *animation: reference to animation struct that will be renderered
    * SDL_Window *window: reference to the window that will be rendered to
    * vec2 position: 32 bit float array that represents the CENTER of where the animation will be rendered
    * i32 z_index: represents the layering priority of the animation, lower z_index'd sprites will be rendered first
    * vec4 color: color the animation will be rendered
    * u32 texture_slots[32]: batch of textures that will be rendered
