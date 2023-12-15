# Simon Persson and William Strand Paurell

### Project Description
We made a simple Vampire Survivors type of game. The player moves around and automatically fires projectiles at nearby enemies.

### Design Patterns
We use:  
- Update Method pattern. All GameObjects in the game have an update method that will automatically be called by the engine every loop.
This was chosen because it is the way we are used to work and we needed some kind of game loop.
When a GameObject is created it is placed in a list, then every loop the engine calls a method that iterates through the list and calls every update method.

- Component pattern. A GameObject can attach components to implement different functionality.
This was chosen because it is how we are used to work and it is a good way to separate contents.
A component needs to implement an update method. Every GameObject has a list of components and every time the update method is called, the update method of every component in the list will also be called.

### Gameplay

https://github.com/FG22-GP/214-design-patterns-assignment-sp-kb-rh-wp/assets/115085829/d61f2d84-8bc3-40fd-8170-fb45c0860538

![Design Patterns Gameplay Screenshot 2](https://github.com/FG22-GP/214-design-patterns-assignment-sp-kb-rh-wp/assets/115085829/3e67ce9f-457a-48bc-a5ca-d087b0a7ff01)
![Design Patterns Gameplay Screenshot](https://github.com/FG22-GP/214-design-patterns-assignment-sp-kb-rh-wp/assets/115085829/3cafd227-17bf-4fa8-856e-4c8e3a77e801)
