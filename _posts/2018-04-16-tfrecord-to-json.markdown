---
layout: post
title:  "tfrecord to json"
date:   2018-04-16 17:21:00
categories: deep_learning
use_math: true
tags: deep_learning tensorflow
---
```python
for example in tf.python_io.tf_record_iterator('/path/to/tfrecord/file'):
    jsonMessage = json_format.MessageToJson(tf.train.Example.FromString(example))
    d = json.loads(jsonMessage)
```