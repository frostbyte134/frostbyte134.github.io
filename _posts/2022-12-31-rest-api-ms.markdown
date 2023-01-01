---
layout: post
title:  "API design best practice - Microsoft"
date:   2022-12-31 07:00:05 +0800
categories: coding
use_math: true
tags: coding
---

- 
<a href="https://cloud.google.com/apis/design/resources" target="_blank">google</a> / <a href="https://learn.microsoft.com/en-us/azure/architecture/best-practices/api-design" target="_blank">MS</a> design best practice
  - https://github.com/Microsoft/api-guidelines/blob/master/Guidelines.md
  - https://mathieu.fenniak.net/the-api-checklist/
- <a href="https://deview.kr/2017/schedule/212" target="_blank">그런 REST API로 괜찮은가</a>

### MS API design best practice

https://learn.microsoft.com/en-us/azure/architecture/best-practices/api-design

A well-designed web API should aim to support:
- Platform independence
- Service evolution

REST is independent of any underlying protocol and is not necessarily tied to HTTP.
- A primary advantage of REST over HTTP is that it uses open standards, and does not bind the implementation of the API or the client applications to any specific implementation

### main design principles of RESTful APIs using HTTP
- REST APIs are designed around resources
- Clients interact with a service by exchanging representations of resources (mostly json)
- REST APIs use a `uniform interface`, which helps to decouple the client and service implementations
  - or REST APIs built on HTTP, the uniform interface includes using standard HTTP verbs to perform operations on resources. The most common operations are GET, POST, PUT, PATCH, and DELETE.
- REST APIs use a stateless request model
  - HTTP requests should be independent and may occur in any order, so keeping transient state information between requests is not feasible. 
  - __The only place where information is stored is in the resources themselves,__ and each request should be an atomic operation. 
  - key to the scability
- REST APIs are driven by hypermedia links that are contained in the representation __(json repr of an order may contain links to update/delete the customer associated with the order)__



In 2008, Leonard Richardson proposed the following maturity model for web APIs:

- Level 0: Define one URI, and all operations are POST requests to this URI.
- Level 1: Create separate URIs for individual resources.
- Level 2: Use HTTP methods to define operations on resources.
- Level 3: Use hypermedia (`HATEOAS`)

Level 3 corresponds to a truly RESTful API according to Fielding's definition. In practice, many published web APIs fall somewhere around level 2.

### Organize the API design around resources

design api with the focus on the business entities (resource)

ex) creating an `order` (resource) = HTTP POST with the order information. 
- The HTTP response indicates whether the order was placed successfully or not
- When possible, resource URIs should be based on nouns (the resource) and not verbs (the operations on the resource).
  - https://adventure-works.com/orders // Good
  - https://adventure-works.com/create-order // Avoid
- the uri path doesnt need to reflex the db structure/data domain
  - A resource doesn't have to be based on a single physical data item. For example, an order resource might be implemented internally as several tables in a relational database, but presented to the client as a single entity. 
  - Avoid creating APIs that simply mirror the internal structure of a database. The purpose of REST is to model entities and the operations that an application can perform on those entities. A client should not be exposed to the internal implementation.


> Avoid requiring resource URIs more complex than collection/item/collection.

excessive multi-level uri - not flexible, easy to maintain
- Once an application has a reference to a resource, it should be possible to use this reference to find items related to that resource
- Avoid requiring resource URIs more complex than collection/item/collection.
  - provide links instead (HATEOS)
  - ex) `/customers/1/orders/99/products` -> `/customers/1/orders` to find all the orders for customer 1, and then `/orders/99/products` to find the products in this order.

> Avoid introducing dependencies between the web API and the underlying data sources. For example, if your data is stored in a relational database, the web API doesn't need to expose each table as a collection of resources. In fact, that's probably a poor design. Instead, think of the web API as an abstraction of the database. If necessary, introduce a mapping layer between the database and the web API. That way, client applications are isolated from changes to the underlying database scheme.

### Define API operations in terms of HTTP methods

The common HTTP methods(verbs) used by most RESTful web APIs are:
- `GET` retrieves a representation of the resource at the specified URI. The body of the response message contains the details of the requested resource 

- `PATCH` performs a partial update of a resource. The request body specifies the set of changes to apply to the resource.
- `DELETE` removes the resource at the specified URI.

The differences between POST, PUT, and PATCH can be confusing.


`POST`
- creates a new resource at the specified URI
  - __client cannot specify the uri for the created resource.__ The server assigns a URI for the new resource, and returns that URI to the client
  - not sure this is universal standard
  - ex) `/customers`. POST = create a customer, PUT = bulk upsert on customers.
- The body of the request message provides the details of the new resource. Note that POST can also be used to trigger operations that don't actually create resources.
- non-idempotent
- In the REST model, you frequently apply POST requests to collections. The new resource is added to the collection. A POST request can also be used to submit data for processing to an existing resource, without any new resource being created.

`PUT`
- upsert the resource at the specified URI
  - __The client specifies the URI for the resource__
- The body of the request message specifies the resource to be created or updated.
- usually used for update. Whether to support creation via PUT depends on whether the client can meaningfully assign a URI to a resource before it exists. If not, then use POST to create resources and PUT or PATCH to update.


`PATCH`
- partial update to an existing resource. The client specifies the URI for the resource. The request body specifies a set of changes to apply to the resource. This can be more efficient than using PUT, because the client only sends the changes, not the entire representation of the resource. Technically PATCH can also create a new resource (by specifying a set of updates to a "null" resource), if the server supports this.

PUT requests must be `idempotent`. If a client submits the same PUT request multiple times, the results should always be the same (the same resource will be modified with the same values). POST and PATCH requests are not guaranteed to be idempotent.


### Conform to HTTP semantics

`media types` (aka `MIME` types)
- format of data
- The `Content-Type` header in a request or response specifies the format of the representation
- If the server doesn't support the media type, it should return HTTP status code 415 (Unsupported Media Type).
- A client request can include an Accept header that contains a list of media types the client will accept from the server in the response message
  - If the server cannot match any of the media type(s) listed, it should return HTTP status code 406 (Not Acceptable).


GET
- ex) search
- 200 (successful search result) / 404 (no item) / (204 no content: no search result)

POST
- successfully created: 201
  - uri included in the `Location` header of response
  - response body = repr of the resource
- 200: did not created, but did some processing
  - response body = result of the processing
  - no result: 204

PUT  
If a PUT method creates a new resource, it returns HTTP status code 201 (Created), as with a POST method. If the method updates an existing resource, it returns either 200 (OK) or 204 (No Content). In some cases, it might not be possible to update an existing resource. In that case, consider returning HTTP status code 409 (Conflict).

Consider implementing bulk HTTP PUT operations that can batch updates to multiple resources in a collection. The PUT request should specify the URI of the collection, and the request body should specify the details of the resources to be modified. This approach can help to reduce chattiness and improve performance.

PATCH
- skipped
- https://tools.ietf.org/html/rfc7396
- The media type for JSON patch is `application/json-patch+json`.


#### Async operations

<a href="https://learn.microsoft.com/en-us/azure/architecture/best-practices/api-design#asynchronous-operations" target="_blank">reference</a>
- https://learn.microsoft.com/en-us/azure/architecture/best-practices/api-implementation#provide-asynchronous-support-for-long-running-requests
- 

Return HTTP status code 202 (Accepted) to indicate the request was accepted for processing but is not completed.
- You should expose an endpoint that returns the status of an asynchronous request, so the client can monitor the status by polling the status endpoint. Include the URI of the status endpoint in the Location header of the 202 response. For example:

> HTTP/1.1 202 Accepted  
Location: /api/status/12345

GET over the specified link example

> HTTP/1.1 200 OK
Content-Type: application/json
{
    "status":"In progress",
    "link": { "rel":"cancel", "method":"delete", "href":"/api/status/12345" }
}

If the asynchronous operation creates a new resource, the status endpoint should return status code 303 (See Other) after the operation completes. In the 303 response, include a Location header that gives the URI of the new resource:


### paging
- get with query params
- 스타게이트는 참...음...


### Use HATEOAS to enable navigation to related resources
> Currently there are no general-purpose standards that define how to model the HATEOAS principle. The examples shown in this section illustrate one possible, proprietary solution.

아 ㅋㅋ 컨텐트타입 정의하던가 ㅋㅋ



### Versioning a RESTful web API

uri versioning
- simple impl / understanding
- depends on the server routing the request to the appropriate endpoint. 
- possibly introduce diffuculties in maintanence of API
  - the server has to support a number of different versions
  - from a purist's point of view, in all cases the client applications are fetching the same data (customer 3), so the URI should not really be different depending on the version. 
  - This scheme also complicates implementation of HATEOAS as all links will need to include the version number in their URIs.

> When you select a versioning strategy, you should also consider the implications on performance, especially caching on the web server. The URI versioning and Query String versioning schemes are cache-friendly inasmuch as the same URI/query string combination refers to the same data each time.  
The Header versioning and Media Type versioning mechanisms typically require additional logic to examine the values in the custom header or the Accept header. In a large-scale environment, many clients using different versions of a web API can result in a significant amount of duplicated data in a server-side cache. This issue can become acute if a client application communicates with a web server through a proxy that implements caching, and that only forwards a request to the web server if it does not currently hold a copy of the requested data in its cache.