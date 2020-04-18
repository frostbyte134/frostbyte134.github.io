---
layout: post
title:  "Pipelining, Batch processing in TIOVX"
date:   2020-04-16  05:04:00 +0900
categories: coding
use_math: true
tags: coding C
---

* <a href="https://www.khronos.org/registry/OpenVX/extensions/vx_khr_pipelining/1.0.1/vx_khr_pipelining_1_0_1.html" target="_blank">OpenVX guide</a>
* <a href="http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/tiovx/docs/user_guide/TIOVX_USAGE_REC.html#TIOVX_USAGE_REC_SET_NODE_TARGET" target="_blank">TI guide</a>


- khronos예제에서는 releaseNode / Image (node의 파라미터)를 createGraph에서 함. 나중에 몰아서 할 필요 없고 그때그때 해줘야 하는 듯

### MAIN CONCEPTS
- `pipelining`: schedule multiple time, without waiting for prior complete
- `batch processing`: ability to execute a graph on a group or batch of input. the user provides a list of input and output references and a single graph schedule call processes the data without further intervention of the user application
- `streaming`: source - sink

파이프라이닝이 되는데 배치 프로세싱이 필요한가? HW가 GPU처럼 배치를 통해 이득보는 구조? 인건 아닌거 같은데 어쨋든 되는듯

### Graph parameter
- external ports of a (pipelined, streamlined, batched) graph
- when a `node` is registered as a `graph parameter`, enqueue-dequeue is required.
- enable the abstraction of the remaining graph ports which are not connected as graph parameters
- `vxGraphParameterEnqueueReadyRef` to insert insert graph parameters to be used by the graph
- `vxGraphParameterDequeueDoneRef` function to dequeue a number of data references from a graph parameter after the graph is done using them (thus, making them available for the application)
- `vxGraphParameterCheckDoneRef` function is a non-blocking call that can be used to determine if there are references available for dequeuing, and if so, how many.


#### Graph scheduling
- `VX_GRAPH_SCHEDULE_MODE_QUEUE_MANUAL`: need to call `vxScheduleGraph` (similar effect to the vxProcessGraph)
- `VX_GRAPH_SCHEDULE_MODE_QUEUE_AUTO`: no need to call scheduleGraph
  
In both ways, no need to call `vxProcessGraph`



#### vxGraphParameterEnqueueReadyRef
```c++
vx_status vxGraphParameterEnqueueReadyRef(
    vx_graph                                    graph,
    vx_uint32                                   graph_parameter_index,
    vx_reference *                              refs,
    vx_uint32                                   num_refs);
```
* num_refs: batch processing시 이게 1이 아니고 num_batch가 됨


#### Event handling
- later when needed



### Node parameters
- is not the parameters (vx_image, vx_scalar) of the nodes
- Concept exclusive in `TIOVX`
- In the TIOVX implementation, node parameters are used by the application to identify where __multiple buffers need to be created__ in the case of pipelining
- __pipelining depth and buffers are orthogonal__

- basic pipelining  
<img src="{{ site.url }}/images/tiovx/basic_graph_pipelined.png" width="800" class="center"/>  

- with buffer  
<img src="{{ site.url }}/images/tiovx/basic_graph_pipelined_buffering.png" width="800" class="center"/>  

- When developing a pipelined application, multiple buffers must be created between nodes in order to avoid any stalls in the pipeline


#### tivxSetNodeParameterNumBufByIndex
```c++
vx_status VX_API_CALL tivxSetNodeParameterNumBufByIndex	(	vx_node 	node,
                                                            vx_uint32 	index,
                                                            vx_uint32 	num_buf 
)	
```  

* \[in\]	node	Node reference
* \[in\]	index	Node parameter index
* \[in\]	num_buf	Number of buffers to allocate


- Set number of buffers to allocate at output of a node parameter.
- allows specifying the number of buffers to be used internally by the framework at a given node parameter
- The node parameter given to this API must be of an output type
- the node parameter given to this API must not already be created as a graph parameter 


#### tivxSetGraphPipelineDepth
- Indicates to the implementation the __depth of the graph pipeline__.


### Pipelining Graph Construction Considerations for Composite Objects

`Composite objects` are an OpenVX object that serves as a container for other OpenVX objects.
- Object Arrays, Pyramids, ROI (not supported by TIOVX)
- Object Arrays and Pyramids are treated similarly in TIOVX from a pipelining perspective


<img src="{{ site.url }}/images/tiovx/Object_Array_Produced.png" width="600" class="center"/>  

- use the `vxReplicateNode()` feature for sending separate elements of an object array to downstream nodes for processing

#### vxReplicateNode
```c++
vx_status VX_API_CALL vxReplicateNode	(	vx_graph 	graph,
                                            vx_node 	first_node,
                                            vx_bool 	replicate[],
                                            vx_uint32 	number_of_parameters 
)	
)	
```  
Creates replicas of the same node first_node to process a set of objects stored in vx_pyramid or vx_object_array. first_node needs to have as parameter levels 0 of a vx_pyramid or the index 0 of a vx_object_array. Replica nodes are not accessible by the application through any means. An application request for removal of first_node from the graph will result in removal of all replicas. Any change of parameter or attribute of first_node will be propagated to the replicas. vxVerifyGraph shall enforce consistency of parameters and attributes in the replicas.


* \[in\]	__graph__	The reference to the graph.
* \[in\]	__first_node__	The reference to the node in the graph that will be replicated.
* \[in\]	__replicate__	an array of size equal to the number of node parameters, vx_true_e for the parameters that should be iterated over (should be a reference to a vx_pyramid or a vx_object_array), vx_false_e for the parameters that should be the same across replicated nodes and for optional parameters that are not used. Should be vx_true_e for all output and bidirectional parameters.
* \[in\]	__number_of_parameters__	number of elements in the replicate array


- Set number of buffers to allocate at output of a node parameter.
- allows specifying the number of buffers to be used internally by the framework at a given node parameter
- The node parameter given to this API must be of an output type
- the node parameter given to this API must not already be created as a graph parameter 

Returned values
- __VX_ERROR_INVALID_REFERENCE__	If the first_node is not a vx_node, or it is not the first child of a vx_pyramid.
- __VX_ERROR_NOT_COMPATIBLE__	At least one of replicated parameters is not of level 0 of a pyramid or at index 0 of an object array.
- __VX_FAILURE__	If the node does not belong to the graph, or the number of objects in the parent objects of inputs and output are not the same.
