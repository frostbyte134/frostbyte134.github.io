---
layout: post
title:  "Launching Spark App (Yarn, k8s)"
date:   2023-04-30 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---

https://1ambda.blog/2022/01/02/practical-spark-12/

### Yarn

### https://sujithjay.com/spark/with-yarn
YARN is a generic resource-management framework for distributed workloads
- = a cluster-level operating system
- can handle many frameworks (MR / Spark / ...)
- The central theme of YARN is the division of resource-management functionalities into a global ResourceManager (RM) and per-application ApplicationMaster (AM)

Client mode
- The driver program, in this mode, runs on the YARN client. Thus, the driver is not managed as part of the YARN cluster.
- the driver program must listen for and accept incoming connections from its executors throughout its lifetime, the client cannot exit till application completion.
  - cannot be non-blocking in any way

Cluster mode
- in Yarn, setting `spark.yarn.submit.waitAppCompletion=false` will make spark-submit non-blocking
- In cluster deployment mode, since the driver runs in the ApplicationMaster which in turn is managed by YARN, `spark.driver.memory` property decides the memory available to the ApplicationMaster
  - this is ineffective in client mode, as the JVM which will run the driver is already executed


### https://docs.cloudera.com/documentation/enterprise/latest/topics/cdh_ig_running_spark_on_yarn.html

1. yarn AppMaster is responsible for requesting resources from the ResourceManager
2. Once the resources are allocated, the application instructs NodeManagers to start containers on its behalf
3. (ApplicationMasters eliminate the need for an active client = no need for blocking spark-submit on client)




여기 그림 갖다쓰면 될듯

### https://spark.apache.org/docs/latest/running-on-yarn.html

Before launching spark in yarn cluster mode, you must set the two environment variables YARN_CONF_DIR and HADOOP_CONF_DIR to the location of configuration directory of hadoop

Running Spark on YARN requires a binary distribution of Spark which is built with YARN support

### https://spark.apache.org/docs/latest/running-on-kubernetes.html

Prefixing the master string with k8s:// will cause the Spark application to launch on the Kubernetes cluster, with the API server being contacted at api_server_url

If you have a Kubernetes cluster setup, one way to discover the apiserver URL is by executing kubectl cluster-info.

```
$ kubectl cluster-info
Kubernetes master is running at http://127.0.0.1:6443
```

