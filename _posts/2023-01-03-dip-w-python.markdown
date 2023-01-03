---
layout: post
title:  "Dependency Injection (w. Python)"
date:   2023-01-01 07:00:05 +0800
categories: coding
use_math: true
tags: coding
---


- <a href="https://stackoverflow.com/questions/2461702/why-is-ioc-di-not-common-in-python" target="_blank">https://stackoverflow.com/questions/2461702/why-is-ioc-di-not-common-in-python</a>
    - think the votes are bit biased for python side, but anyway think its a good page
- <a href="https://python-dependency-injector.ets-labs.org/introduction/di_in_python.html" target="_blank">https://python-dependency-injector.ets-labs.org/introduction/di_in_python.html</a>
- <a href="https://martinfowler.com/articles/injection.html" target="_blank">https://martinfowler.com/articles/injection.html</a>

TODO: do sth

### python-dependency-injector

<a href="https://python-dependency-injector.ets-labs.org/introduction/di_in_python.html" target="_blank">https://python-dependency-injector.ets-labs.org/introduction/di_in_python.html</a>

Dependency injection is a principle that helps to achieve an inversion of control. 
- for static typing language the DI frameworks can greatly improve productivity

Python is dynamic typing
- A lot of the flexibility is already built-in. ex) duck typing 

This page describes the advantages of applying dependency injection in Python. 
- demonstrates the usage of the Dependency Injector framework, its `container`, `Factory`, `Singleton`, and `Configuration providers`
- The example shows how to use providers’ `overriding feature` of Dependency Injector for testing or 
- re-configuring a project in different environments and explains why it’s better than monkey-patching

To implement the dependency injection, objects do not create and initialize each other anymore. DI framework provide a way to inject the dependencies instead.

With the dependency injection pattern, objects lose the responsibility of assembling the dependencies. The Dependency Injector absorbs that responsibility.
- When you need an object you place a `Provide` marker as a default value of a function argument
    - When you call this function, framework assembles and injects the dependency.

In Python, you can monkey-patch anything, anytime. The problem with monkey-patching is that it’s too fragile.
- With dependency injection, you patch the interface, not an implementation. This is a way more stable approach.
- Also, monkey-patching is way too dirty to be used outside of the testing code for re-configuring the project for the different environments (meh)



#### Provider
<a href="https://python-dependency-injector.ets-labs.org/providers/index.html#providers" target="_blank">https://python-dependency-injector.ets-labs.org/providers/index.html#providers</a>

They create objects and inject the dependencies.
- Each provider is a callable. You call the provider like a function when you need to create an object. Provider retrieves the underlying dependencies and inject them into the created object. It causes the cascade effect that helps to assemble object graphs
- Another providers feature is an overriding. You can override any provider with another provider. This helps in testing. <a href="https://python-dependency-injector.ets-labs.org/providers/overriding.html#provider-overriding" target="_blank">provider overriding</a>

Factory provider
- The first argument of the Factory provider is a class, a factory function or a method that creates an object.
- The rest of the Factory positional and keyword arguments are the dependencies
- Factory injects the dependencies every time when creates a new object. The dependencies are injected following these rules:

<a href="https://python-dependency-injector.ets-labs.org/providers/async.html" target="_blank">async injection</a>

#### Container
<a href="https://python-dependency-injector.ets-labs.org/containers/index.html#containers" target="_blank">https://python-dependency-injector.ets-labs.org/containers/index.html#containers</a>


```
class Container(containers.DeclarativeContainer):

    config = providers.Configuration()

    api_client = providers.Singleton(
        ApiClient,
        api_key=config.api_key,
        timeout=config.timeout,
    )

    service = providers.Factory(
        Service,
        api_client=api_client,
    )

def main(service: Service = Provide[Container.service]) -> None:
```

Containers are collections of the providers
- holds objects to inject

use cases of containers:
- Keeping all the providers in a single container (most common).
- Grouping of the providers from the same architectural layer (for example, Services, Models and Forms containers).
- Grouping of providers from the same functional groups (for example, container Users, that contains all functional parts of the users package).

miscs
- <a href="https://python-dependency-injector.ets-labs.org/containers/declarative.html" target="_blank">declarative</a>
- dynamic: runtime creation of container, without declaraing container's attributes
- <a href="https://python-dependency-injector.ets-labs.org/containers/overriding.html" target="_blank">overriding</a>


### Wiring
<a href="https://python-dependency-injector.ets-labs.org/wiring.html#wiring" target="_blank">https://python-dependency-injector.ets-labs.org/wiring.html#wiring</a>

Wiring feature provides a way to inject container providers into the functions and methods.

To use wiring you need:
- Place `@inject` decorator. Decorator @inject injects the dependencies.
- Place markers. Wiring marker specifies what dependency to inject, e.g. `Provide[Container.bar]`. This helps container to find the injections.
- Wire the container with the markers in the code. Call container.wire() specifying modules and packages you would like to wire it with.
- Use functions and classes as you normally do. Framework will provide specified injections.



examples
- https://python-dependency-injector.ets-labs.org/examples/application-single-container.html#application-single-container
- https://python-dependency-injector.ets-labs.org/examples/application-multiple-containers.html#application-multiple-containers
- https://python-dependency-injector.ets-labs.org/examples/decoupled-packages.html#decoupled-packages
