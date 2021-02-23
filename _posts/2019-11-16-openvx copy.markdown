---
layout: post
title:  "OpenVX + TIOVX"
date:   2019-11-16 09:00:05 +0800
categories: coding
use_math: true
tags: coding openvx
---

### OpenVX

<a href="https://www.khronos.org/registry/OpenVX/specs/1.0/html/index.html#sec_naming_conventions" target="_blanl">The OpenVX Specification</a>

1. Intro
   * `OpenVX` contains
     - lib of customizable vision functions
     - graph-based executation model
     - set of memory objs that abstracts the physical mem (?)
   * is a C API
   * `vxu` utility lib : each directly callable OpenVX function (no graph)
   * `Kernel`: computer vision function
  
2. Design overview
   - Memory that is imported or shared from other APIs is not subsumed by OpenVX and is still maintained and accessible by the originator.
   - OpenVX objects are both strongly typed at compile-time
   - Any object may be down-cast to a `vx_reference` safely to be used in functions that require this, specifically `vxQueryReference`, which can be used to get the `vx_type_e` value using an `vx_enum`.

3. Graph Verification
   Graphs within OpenVX must go through a rigorous validation process before execution to satisfy the design concept of eliminating run-time overhead (parameter checking) that guarantees safe execution of the graph. OpenVX must check for (but is not limited to) these conditions:

   * Parameters To Nodes:
      * Each required parameter is given to the node (vx_parameter_state_e). Optional parameters may not be present and therefore are not checked when absent. If present, they are checked.
      * Each parameter given to a node must be of the right direction (a value from vx_direction_e).
      * Each parameter given to a node must be of the right object type (from the object range of vx_type_e).
      * Each parameter attribute or value that has algorithmic significance must be verified. In the case of a scalar value, it may need to be range checked (e.g., \\( 0.5 <= k <= 1.0 \\)). The implementation is not required to do run-time range checking of scalar values. If the value of the scalar changes at run time to go outside the range, the results are undefined. The rationale is that the potential performance hit for run-time range checking is too large to be enforced. It will still be checked at graph verification time as a time-zero sanity check. If the scalar is an output parameter of another node, it must be initialized to a legal value. In the case of vxScaleImageNode, the relation of the input image dimensions to the output image dimensions determines the scaling factor. These values or attributes of data objects must be checked for compatibility on each platform.
      * Graph Connectivity - the vx_graph must be a Directed Acyclic Graph (`DAG`). No cycles or feedback is allowed. The vx_delay object has been designed to explicitly address feedback between Graph executions.
      * Resolution of `Virtual Data Objects` - Any changes to Virtual data objects from unspecified to specific format or dimensions, as well as the related creation of objects of specific type that are observable at processing time, takes place at Verification time.

3. OpenVX Lifecycle
   1. Context 
   <img src="https://www.khronos.org/registry/OpenVX/specs/1.0/html/msc_system.png">
   2. Graph
      construction - Graphs are created via vxCreateGraph, and Nodes are connected together by data objects.
Verification - The graphs are checked for consistency, correctness, and other conditions. Memory allocation may occur.
Execution - The graphs are executed via vxProcessGraph or vxScheduleGraph. Between executions data may be updated by the client or some other external mechanism. The client of OpenVX may change reference of input data to a graph, but this may require the graph to be validated again by checking vxIsGraphVerified.
Deconstruction - Graphs are released via vxReleaseGraph. All Nodes in the Graph are released.
