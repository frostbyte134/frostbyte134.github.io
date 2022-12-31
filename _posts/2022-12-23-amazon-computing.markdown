---
layout: post
title:  "The Distributed Computing Manifesto"
date:   2022-12-23 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---

<a href="https://www.allthingsdistributed.com/2022/11/amazon-1998-distributed-computing-manifesto.html" target="_blank">https://www.allthingsdistributed.com/2022/11/amazon-1998-distributed-computing-manifesto.htm</a>


언제 읽지 ㅋㅋ 재밌어 보이기는 함


### Intro
a canonical document of dist. system at 1998
- 'I was thinking: web servers and a database, how hard can that be?'

> Over the next two decades, Amazon would move from a monolith to a service-oriented architecture, to microservices, then to microservices running over a shared infrastructure platform. All of this was being done before terms like service-oriented architecture existed. Along the way we learned a lot of lessons about operating at internet scale.

started with a traditional two-tier architecture:
- a monolithic, stateless application (Obidos(?)) that was used to serve pages
- and a whole battery of databases that grew with every new set of product categories, customers, and countries that Amazon launched in

These databases were a shared resource, and eventually became the bottleneck for the pace that we wanted to innovate
- `Distributed Computing Manifesto` in 1998: separating the presentation layer, business logic and data (while ensuring that reliability, scale, performance and security)

> One of our Leadership Principles is to invent and simplify – our engineers really live by that moto

### BG
what form should the new architecture take and how do we move towards realizing it
- two-tier, client-server architecture is one that is essentially `data bound`
  - business app access the db directly, and have knowledge of the data model embedded in db
  - = a __very tight coupling between the app and the data model__ -> data model changes have to be accompanied by application changes (even if functionality remains the same)
- doesn't scale well, and makes distributing and segregating processing based on where data is located difficult since the __applications are sensitive to the interdependent relationships between data elements.__


### Key Concepts

two key concepts in the proposed architecture
1. to move toward a service-based model
2. shift our processing so that it more closely models a workflow approach (?)


#### Service-based model

Things to node:
- Physically the change remains the same (no additional hop required for these changes)
- What matters is a new interface (between app - db) is introduced
- In conclusion, we were able to __protect the domain__ (alas!) from the db models

2 tier -> 3 tier
- presentation (client=app), business logic and data are separated (aka `service-based architecture` (?))
- __The app (clients) cannot access the database directly, but only through a well-defined interface that encapsulates the business logic required to perform the function__
- client is no longer dependent on the underlying data structure or even where the data is located
- below 2 interfaces can change indenendently, without influencing each other
    - The interface between the business logic (in the service) and the database 
    - the client interface can evolve without impacting the interaction of the service and the underlying database.

Services will have to provide both `synchronous` and `asynchronous` methods
- Synchronous methods - applied when response is immediate. ex) adding a customer or looking up vendor information
- other operations that are asynchronous in nature will not provide immediate response. 
    - ex) pass a workflow onto the next processing node in the chain. in such case, 200 (or 202?): successfully queued
    - return - polling / callback
    - `callback`: the requestor passes the address of a routine to invoke when the request completed. used most commonly when the time between the request and a reply is relatively short.
      - cons: requestor may no longer be active when the request has completed making the callback address invalid
    - `polling` suffers from the overhead required to periodically check if a request has completed. The polling model is the one that will likely be the most useful for interaction with asynchronous services. (?)

Several important implications that have to be considered as we move toward a service-based model.
1. adopting a disciplined approach to software engineering
  - db access
    - as-is: ad hoc Perl script, different from each service 
    - to-be: direct client access to the database be phased out over a period of time
    - Without this, cannot bet the benefits of a 3-tier archi, such as (data-location transparency and the ability to evolve the data model, without negatively impacting clients)
    - The specification, design and development of services and their interfaces should occur in uniform way (between services), so that we do not end up with the current tangled proliferation.
2. (related to the first) significant mindset shift from `data-centric`
  - when we model a business requirement, firstly make db table/column changes to implement the solution
  - and we embed the data model within the accessing application
  - The `service-based approach` require us to break the solution to business requirements into at least 2 pieces
    1. modeling of the relationship between data elements just as we always have. (data model and the business rules that will be enforced in the service(s) that interact with the data)
    2. (never done before) designing the interface between the client / service, so that the underlying data model is not exposed to or relied upon by the client

### Workflow-based Model and Data Domaining

Amazon's business is well suited to a `workflow-based processing model`
- already have an "order pipeline": acted upon by various business processes, from the time a customer order is placed to the time it is shipped out the door
- Much of our processing is already workflow-oriented, albeit the workflow "elements" are static, residing principally in a `single database`
- ex) progression of customer_orders through the system
  - The condition attribute on each `customer_order` dictates the next activity in the workflow
  - current db workflow model will not scale well, b/c processing is being performed against a central instance (single db?)
  - solution: distribute the workflow processing

Implementing this requires that workflow elements like customer_orders would move between business processing ("nodes") that could be located on separate machines. Instead of processes coming to the data, the data would travel to the process. This means that each workflow element would require all of the information required for the next node in the workflow to act upon it. This concept is the same as one used in message-oriented middleware where units of work are represented as messages shunted from one node (business process) to another.

An issue with workflow is how it is directed. Does each processing node have the autonomy to redirect the workflow element to the next node based on embedded business rules (autonomous) or should there be some sort of workflow coordinator that handles the transfer of work between nodes (directed)? To illustrate the difference, consider a node that performs credit card charges. Does it have the built-in "intelligence" to refer orders that succeeded to the next processing node in the order pipeline and shunt those that failed to some other node for exception processing? Or is the credit card charging node considered to be a service that can be invoked from anywhere and which returns its results to the requestor? In this case, the requestor would be responsible for dealing with failure conditions and determining what the next node in the processing is for successful and failed requests. A major advantage of the directed workflow model is its flexibility. The workflow processing nodes that it moves work between are interchangeable building blocks that can be used in different combinations and for different purposes. Some processing lends itself very well to the directed model, for instance credit card charge processing since it may be invoked in different contexts. On a grander scale, DC processing considered as a single logical process benefits from the directed model. The DC would accept customer orders to process and return the results (shipment, exception conditions, etc.) to whatever gave it the work to perform. On the other hand, certain processes would benefit from the autonomous model if their interaction with adjacent processing is fixed and not likely to change. An example of this is that multi-book shipments always go from picklist to rebin.

The distributed workflow approach has several advantages. One of these is that a business process such as fulfilling an order can easily be modeled to improve scalability. For instance, if charging a credit card becomes a bottleneck, additional charging nodes can be added without impacting the workflow model. Another advantage is that a node along the workflow path does not necessarily have to depend on accessing remote databases to operate on a workflow element. This means that certain processing can continue when other pieces of the workflow system (like databases) are unavailable, improving the overall availability of the system.

However, there are some drawbacks to the message-based distributed workflow model. A database-centric model, where every process accesses the same central data store, allows data changes to be propagated quickly and efficiently through the system. For instance, if a customer wants to change the credit-card number being used for his order because the one he initially specified has expired or was declined, this can be done easily and the change would be instantly represented everywhere in the system. In a message-based workflow model, this becomes more complicated. The design of the workflow has to accommodate the fact that some of the underlying data may change while a workflow element is making its way from one end of the system to the other. Furthermore, with classic queue-based workflow it is more difficult to determine the state of any particular workflow element. To overcome this, mechanisms have to be created that allow state transitions to be recorded for the benefit of outside processes without impacting the availability and autonomy of the workflow process. These issues make correct initial design much more important than in a monolithic system, and speak back to the software engineering practices discussed elsewhere.

The workflow model applies to data that is transient in our system and undergoes well-defined state changes. However, there is another class of data that does not lend itself to a workflow approach. This class of data is largely persistent and does not change with the same frequency or predictability as workflow data. In our case this data is describing customers, vendors and our catalog. It is important that this data be highly available and that we maintain the relationships between these data (such as knowing what addresses are associated with a customer). The idea of creating data domains allows us to split up this class of data according to its relationship with other data. For instance, all data pertaining to customers would make up one domain, all data about vendors another and all data about our catalog a third. This allows us to create services by which clients interact with the various data domains and opens up the possibility of replicating domain data so that it is closer to its consumer. An example of this would be replicating the customer data domain to the U.K. and Germany so that customer service organizations could operate off of a local data store and not be dependent on the availability of a single instance of the data. The service interfaces to the data would be identical but the copy of the domain they access would be different. Creating data domains and the service interfaces to access them is an important element in separating the client from knowledge of the internal structure and location of the data.

### Vocabs
- canonical document: 규범이 되는 문서
- overhaul: 점검
- haphazard: without strict/unified plan, by coincedence