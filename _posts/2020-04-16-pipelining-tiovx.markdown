---
layout: post
title:  "Pipelining, Batch processing in TIOVX"
date:   2020-04-16  05:04:00 +0900
categories: coding
use_math: true
tags: coding C
---

### Rule of thumb
1. before using vxReplicateNode, the input/output of the target node must be the 1st item of an vxObjectArray. Their sizes also must match. Otherwise it gives VX_FAILURE
2. repliate array - counting excludes graph. vx_false for config struct (must be same across all replicas) and NULLs
3. add_graph_parameter_by_node_index의 node index는 해당 노드에서 그래프 파라미터로 추가할 객체의 node parameter index임
   1. 이함수는 tiovx 기본함수는 아님. AVP예제에서 가져와야 할 듯
4. tivxSetNodeParameterNumBufByIndex로 버퍼 만들기
    - pipelining depth와는 무관하진 않는데 같을 필욘 없음
    - node parameter index: <a href="https://e2e.ti.com/support/processors/f/791/t/894343" target="_blank">(TI forum 공식답변)</a> Index to node parameter (starts from -1, 0, 1, etc. -1 is the "graph" argument)
5. TIDL node처럼 input tensor/output tensor가 여러 개 배열로 있는 경우, 이것도 고려해 줘야 하는듯 (`app_tidl_avp`의 tidl node pipelining 참고)
6. Pipeline depth (tivxSetGraphPipelineDepth의 파라미터) != buffer queue depth (==graph_parameters_queue_params_list[graph_parameter_index].refs_list_size). buffer queue depth만큼 


BUFFER_QUEUE_DEPTH
- replicateNode와 관련 있음. replicate 되는 노드의 갯수
- 실제 replicate되는 노드의 갯수는, 노드의 입력/출력이 담겨있는 object_array의 길이
- pipeline depth는 


* <a href="https://www.khronos.org/registry/OpenVX/extensions/vx_khr_pipelining/1.0.1/vx_khr_pipelining_1_0_1.html" target="_blank">OpenVX guide</a>
* <a href="http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/tiovx/docs/user_guide/TIOVX_USAGE_REC.html#TIOVX_USAGE_REC_SET_NODE_TARGET" target="_blank">TI guide</a>
* TI forum
  * https://e2e.ti.com/support/processors/f/791/t/894343

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
<img src="{{ site.url }}/nailbrainz.github.io/images/tiovx/basic_graph_pipelined.png" width="800" class="center"/>  

- with buffer  
<img src="{{ site.url }}/nailbrainz.github.io/images/tiovx/basic_graph_pipelined_buffering.png" width="800" class="center"/>  

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


<img src="{{ site.url }}/nailbrainz.github.io/images/tiovx/Object_Array_Produced.png" width="600" class="center"/>  

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


The tivxSetNodeParameterNumBufByIndex() function accepts 3 parameters

1. Reference to a node

2. Index to node parameter (starts from -1, 0, 1, etc. -1 is the "graph" argument)

3. Number of buffers (aka buffer depth) per parameter.

This function is used for a fine-grain control of intermediate outputs shared between nodes. As a thumb rule, you could apply the following,

1. If two nodes are executed back-to-back on the same core then the buffer depth could simply be 1. This is because the nodes are executed sequentially on the same target. By default the framework assigns a buffer depth of 1 to all intermediate outputs, which basically makes the code run sequentially. 

2. If two nodes are executed back-to-back on different cores, then you have an opportunity to make these two nodes run in parallel by sizing the buffer depth accordingly. One assumption made in the AVP demos is that all nodes take the same time to execute irrespective of what core they are running. This allows a simple fixed allocation of buffers. For example, if node1 and node2 runs on C66x_1 and C71x_1 then assuming that both take same cycles the minimum buffer depth required is 2. (ping-pong). 

3. If two nodes are executed on different cores but are connected later in the pipeline, then a buffer depth of 2 will not help. For example, lets say we have 3 nodes, node1, node2 and node3. If node1 output is consumed by both node2 AND node3 then sizing the output of node1 as just 2 is not sufficient as node3 will be starved. So to keep all the nodes running in parallel then the minimum number of buffers required is 3 (circular-buffer).

4. If two nodes run on different cores and run back-to-back but take different time to execute, which is mostly the case, you can size the buffer depth such that the producer and consumer is not stalled. But as long as your use-case is met, it is not required to stress memory allocation and let one node wait for the other node to produce/consume accordingly. In the AVP demo, there is an underlying assumption that all nodes take same time and we simply do static allocation of buffer depth.

Hope this gives you an overview of what you can do with this function. This is required for all intermediate buffers in the graph. Basically the ones which are not graph parameters.

We mostly have one-graph parameter for input/output depending on the usecase. But it is possible to make all intermediate outputs as graph parameter as well but this is mostly not required.

Regards,  
Shyam




<a href="https://e2e.ti.com/support/processors/f/791/t/850997" target="_blank">https://e2e.ti.com/support/processors/f/791/t/850997</a>

Yongsig,

I realized that I would require more time to draft a complete design doc. So I am gonna attempt to explain a few concepts right here. Eventually we will have a detailed developer note as part of a user guide.

Firstly, doing multi-channel has nothing to do with OpenVx pipelining. Any node can be configured to execute in a multi-channel mode by using the vxReplicate functionality in OpenVx. By replicating a node, the user can configure which input/output parameters of a node needs to be replicated. The replicate factor is simple the number of channels. This is a very useful way of running an OpenVx node on multiple camera inputs and keep the graph compact.

Now lets say we have an OpenVx graph with 3 nodes and 3 compute cores with one node executing on each core. By default the graph execution execution will be sequential in nature, so even if then nodes are executing on different cores they will have to wait till one node completes its execution and generates the data required for the next connected node. This is largely a waste of compute because the other cores have to wait (remain in IDLE) till one core finishes.

In a pipeline execution model, all the cores are executing its respective node irrespective of the data being valid or not. The OpenVx framework which the help of some user inputs makes sure that data propagated from one node to the next is up-to-date so that compute does not go waste.

These user inputs are some of the things you have mentioned. Apart from creating a graph (connecting different nodes together) we need to specify two key things.

1. A graph parameter which can be enqueued/dequeued by the host.

2. Intermediate buffer depths between successive nodes.

Any node parameter (input/output parameter) can be made a graph parameter. In AVP demo for example, the input to the scalar node is made a graph parameter. This is because the host A72 need to read a file from SD card and put in a buffer in DDR before executing the graph. If the user is interested in writing the output to a file, he can make the final node (mosaic node) output as a graph parameter and then dump the output from a buffer to a file on SD card. In the AVP demo as the output is routed to a display there is only one graph parameter which is the input to the scalar node. This is achieved by add_graph_parameter_by_node_index(<graph>, <node>, <node parameter index>). We can make a list of such graph parameters and configure the graph schedule by calling vxSetGraphScheduleConfig(). This will help configure the graph to look out for parameters which the host will manage (manual enqueue/dequeue)

Now we need to set appropriate buffer depths between nodes so that all nodes can run concurrently on the different cores. As a general rule, for two adjacent nodes to run in parallel on different cores we can set the buffer depth as 2. But this will again be a function of how fast the producer node is generating outputs and consumer node is consuming the generated outputs. This is done by tivxSetNodeParameterNumBufByIndex(<node>, <node parameter index>, <buffer depth>)

In our example of 3 nodes, lets say the 3rd node accepts output from both 1st node and 2nd node. So we would setup the intermediate buffer depths as,

tivxSetNodePrarameterNumBufByIndex(<node1>, <node1 output parameter index>, 4)

tivxSetNodePrarameterNumBufByIndex(<node2>, <node2 output parameter index>, 2)

So between node1 and node3 the output buffer has a depth of 4 (can be 3 as well) and between node2 and node3 the buffer depth is 2.

The user is aware of how the nodes are connected in the graph so he can control buffer depths required between the nodes.

I hope this brief explanation has helped explain some of your questions. You can try and look at some more simpler pipelining examples in tiovx and get a better understanding of the same. Please feel free to discuss if something is not clear

Regards,  
Shyam