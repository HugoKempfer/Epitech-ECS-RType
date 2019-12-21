# Rtype

## ECS implementation

### State

It represents a "phase" of the game (ex: loading scene, player awating scene, boss scene, score scene).
The engine stops when it remains no active states.
There can be only one active state at one time.

#### specific features

The states can implements hooks :

- onStart
- onUpdate (executed each cycle)
- onPause (called when a state is pushed)
- onResumt (called when the top state is popped)
- onStop

The state is instanciated through the world.states.push<StateClass>().
Or by emplacing the current state with world.states.emplace<StateClass> (replaces the current state).

### Entity

An entity on only an ID stored in the engine.
It will be used to combine components together.

An entity can be created with `world.entity.add()`

### Component

A component is a data class attached to a specific entity.
Its goal is to store logic data that will be manipulated though systems.

A component should stick to a limited logic concern.
For example you should create two separated components to represent an entity position and dimentions.

### Systems

A system is a class where you can implement you game logic.
To do so you must implement a method `void run() final`.

When declaring a system you must provide a set of Components types you want to act on.
As said, at construction-time you can ask the engine an access on `Ressource`.

The systems are executed on each cycle in parallel as long as there is at least one active `State`.
Finally the `System` runs independantly of the `State`. If you want to restrict the state on which your system run on, you can provide this set of `State` using a dedicated constructor.

As you provide to the engine every dependance your system needs, you don't have to worry about data races issues tied to components/ressources access.

### Ressource

A ressource is very similar to a component.
Its purpose is the hold data no tied to a specific entity.

### Events

The events are a unidirectional way to do message passing between systems and states.

You create your own event by inheriting the `Engine::Event<YourClass>`.

You can *publish* events from anywhere in your program using `world.eventCtx.publish<EventType>(ctor args).

Every `System` or `State` which implements `Engine::EventHandler<EventType>` will receive the published event.

The engine has a bunch of built-in events that you can listen to.
Here is a non-exhaustive list :
* KeyboardEvent
* MouseEvent
* SignalEvent
* ConnectionEvent

### Bundle

The bundles aims to register the Systems/Ressources/Entities by concern.
For example you can group your PlayerSystem, PlayerRessources in a PlayerBundle.

You can use a bundle with the `world.useBundle<Bundle>(void)`.

There are a some built-in bundles as :
* RenderBundle