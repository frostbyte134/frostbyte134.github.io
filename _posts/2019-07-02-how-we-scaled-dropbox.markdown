---
layout: post
title:  "How We've Scaled Dropbox"
date:   2019-07-02 09:59:00 +0800
categories: coding
use_math: true
tags: coding
---

<a href="https://www.youtube.com/watch?v=PE4gwstWhmc" target="_blank">https://www.youtube.com/watch?v=PE4gwstWhmc</a>

### Dropbox Architecture
* dropbox domain: __more writes__ than typical systems (like, FB)
* enormous write volume : low cachebility.  
* In terms of `ACIDity`, 
    * Dont have much room for `Atomicity`, `Consistency`, and `Duration` (Durability guarantees that once a transaction has been committed, it will remain committed even in the case of a system failure (e.g., power outage or crash).)
    * Can trade-off some `Isolation` (Isolation ensures that concurrent execution of transactions leaves the database in the same state that would have been obtained if the transactions were executed sequentially.)

1. Original version  
    <img src="{{site.url}}/images/coding/mod_scale1.png" width="700">  
    * Initial startup, 0 users.
    * _The server_
2. 2nd  
    <img src="{{site.url}}/images/coding/mod_scale2.png" width="700">  
    `problems`
    * upload/download in one server
    * notification to user uses polling - too much workload for server
3. 3rd  
    <img src="{{site.url}}/images/coding/mod_scale3.png" width="700">  
    `solutions`
    * split of metaserver(in-house) / file block server(AWS) - separation of traffic
    * polling \\(\rightarrow\\) __NOT__ification server (socket? after all, if one does not want to use polling, socket (maintaining client information) is the only way)  

    `problems`
    * blockserver queries directly - two sources of queries, hard to optimize
4. 4th  
    <img src="{{site.url}}/images/coding/mod_scale4.png" width="700">  
    `solutions`
    * now blockserver uses LB (Load balancer) to query DB
    * multiple servers

    1. Scaling up mem-cache : had consistency problem
    2. Scaling up Load balancer : LB used python, so it suffered from GIL
    3. Blockserver : used block(4mb - some random, reasonable choice ('worked pretty well so far')) leverl de-duplication (with hash)
    4. share folder was problematic, which required relation table of users.

### Journaling (DB schema)
<img src="{{site.url}}/images/coding/mod_journal.png" width="700">

1. PRIMARY KEY : not only serve as the unique identifier, but all the files are sorted in PKEY : fast adding at the end / searching with P-KEY
2. retrieving past revisions (to show the revision history) was expensive : made _parent_ column
3. log become big \\(\rightarrow\\) slow update  
    \\(\rightarrow\\) : changed P-KEY to (ns_id (namespace_id) / latest / id)  
    (pre-work to make searching better : slower on write!)
4. removed `latest` from P-KEY: as mentioned, dropbox is _write-heavy_ system - for better write while tradeoffing bit of reading speed


