---
layout: post
title:  "Streaming Systems"
date:   2022-03-02 08:00:05 +0800
categories: coding
use_math: true
tags: coding
---

(작성-중) 


이것도 정리를 [여기](https://github.com/nailbrainz/nailbrainz.github.io/issues)다가 해 놨음. 중요한거만 따로 때 놓자


### Watermarks
- watermark: is a function (a point in processing time -> a point in event time)
- given a point in processing time, returns time from event timeline which guarantees that every items equal and before this event time items are all processed

### Triggers
- asd