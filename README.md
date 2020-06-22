# Rtype

## Introduction

This project is a minimal game engine design and implementation.
I chose to make an implementation proposal for the *E*ntity *C*omponent *S*ystem architecture.
A lot of inspiration came from the Rust Amethyst project and more specifically its SpECS module.

This architectural pattern mostly follows the Mixin design and composition over inheritance movance.
All relations between entities and components are made at runtime and are so called dynamic, which offers a lot of advantages in game programming.

https://en.wikipedia.org/wiki/Entity_component_system

This project is made with C++ 20.

## ECS implementation

### State

It represents a "phase" of the game (ex: loading scene, player awating scene, boss scene, score scene).
The engine stops when no active states remains.
There can be only one active state at one time.

#### specific features

The states can implements hooks:

- onStart
- onUpdate (executed each cycle)
- onPause (called when a state is pushed)
- onResume (called when the top state is popped)
- onStop

The state is instantiated through the world.states.push<StateClass>().
Or by emplacing the current state with world.states.emplace<StateClass> (replaces the current state).

### Entity

An entity on only an ID stored in the engine.
It will be used to combine components together.

An entity can be created with `world.entity.add()`

### Component

A component is a data class attached to a specific entity.
Its goal is to store a logic state that will be manipulated though systems.

A component should stick to a limited logic concern.
For example you should create two separated components to represent an entity position and dimensions.

#### Example of entity creation with components:

```cpp
	_world.entities.add()
		.addComponent<BulletComponent>(_world, BulletComponent::RIGHT)
		.addComponent<Engine::PositionComponent>(_world, player.pos_x, player.pos_y)
		.addComponent<SpriteComponent>(_world, "Damn.png", 15, 20);
```

### Queries

Your systems can retrieve a set of entities and its components from a query.
Only component intersection queries are supported.

An example query to get *bullets* in the RType game:

```cpp
	auto entities = _world.entities.query(*this)
		.with<Engine::PositionComponent>()
		.with<BulletComponent>().getIntersection();
```

### Systems

A system is a class where you can implement you game logic.
To do so you must implement a method `void run() final`.

When declaring a system you must provide a set of Components types you want to act on.
As said, at construction-time you can ask the engine an access on `Resource`.

The systems are executed on each cycle in parallel as long as there is at least one active `State`.
Finally the `System` runs independently of the `State`. If you want to restrict the state on which your system run on, you can provide this set of `State` using a dedicated constructor.

As you provide to the engine every dependence your system needs, you don't have to worry about data races issues tied to components/resources access.

### Resource

A resource is very similar to a component.
Its purpose is to represent a state no tied to a specific entity.

### Events

The events are an unidirectional way to do message passing between systems and states.

You create your own event by inheriting the `Engine::Event<YourClass>`.

You can *publish* events from anywhere in your program using `world.eventCtx.publish<EventType>(ctor args).`

Every `System` or `State` which implements `Engine::EventHandler<EventType>` will receive the published event.

The engine has a bunch of built-in events that you can listen to.
Here is a non-exhaustive list :
* KeyboardEvent
* MouseEvent
* SignalEvent
* ConnectionEvent

### Bundle

The bundles aims to register the Systems/Resources/Entities by concern.
For example you can group your PlayerSystem, PlayerRessources in a PlayerBundle.

You can use a bundle with the `world.useBundle<Bundle>(void)`.

There are a some built-in bundles as :

* RenderBundle