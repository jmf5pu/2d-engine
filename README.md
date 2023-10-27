Prioritized:
* make crosshair not spawn on top of player
* implement reloading / ammo count
  * add reload animations (or placeholders) 
* implement HUD
  * Add new glViewport for HUD items so that changes rendering width/height of main cam won't affect HUD scaling 
* implement 8 directional movement
  * ~~add movement logic~~
  * ~~add shooting logic~~
  * add player anims
* implement crouched aiming (360 deg)
  * ~~implement base mechanics~~
  * ~~add bullet anims~~
  * add player anims
* ~~integrate camera~~
  * ~~add base logic~~
  * ~~add screen splitting logic~~

TODOs:
* ~~add destructor for entities and bodies~~
* finish implementing a map
  * add a second pickup (armor?)
    * ~~adding animations and anim transitions on pickup~~
    * ~~add armor attribute to player~~
    * ~~update original anim (hair)~~
    * ~~add anims to m44~~
    * add dying anims
  * ~~pull out props to separate sprites~~
  * ~~make m16 burst fire~~
  * ~~refactor sprites to use string manipulation based on status of the player~~
  * ~~fix sprite/aabb size for players~~
  * ~~remove old props from bg sprite~~
  * ~~fix players running into their own bullets~~
  * fix dying animation
  * add props to map bg
  * ~~fix animation bug (one player flips the other)~~
* add crouching and 360 deg aiming
* add weaker spawn weapon
* implement pause menu
* figure out why static bodies aren't rendering with `render_bodies` flag
