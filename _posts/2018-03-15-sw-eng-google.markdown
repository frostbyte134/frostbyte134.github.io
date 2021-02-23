---
layout: post
title:  "Software Engineering at Google"
date:   2018-03-15 22:04:00
categories: coding
use_math: true
tags: coding
---

<a href="https://arxiv.org/abs/1702.01715" target="_blank">Software engineering at Google</a>


### The Source Repository
Most of the Google's code is stored in a single unified source code repo, and is accessible to all software engineers at Google. (except Chrome, Android and few secret projects)  
- Any engineer has access any piece of code, can check it out and build it, and can send changes for review by the code owners.  

Almost all development occurs at the `head` of the repo, not on branches.  

Automated system run tests frequently. Engineers try their best to maintain the build of head of the repo.  
* Build cop : senior engineer.  

### The Build System  
Uses distributed build system as Blaze: simultaneous testing at many machines.
- build files have high-level declarative build specs (libraries, dependencies, ...), so that the machines quickly figure out how to run the code.

Individual build steps are (made to be) deterministic, to cache the build results. They are safely shared between different users.

Presubmit tests. Each subtree of the repo can contain a configuration of when/how to run automated tests.

### Code Review  
In-house developed web based code review tool.
At least 1 reviewer must review the code. The author choose reviewers.

Engineers are encouraged to keep each individual change small. (for concrete build, and for easy review)  
30-99 lines: medium size  
300-999: large  

### Testing
Unit testing is strongly encouraged and widely practice at google.  
New code added are mostly required to add new test to cover the new functionality.

### Programming Languages
Interoperation between different programming languages are done using Protocol Buffers, which is a way of encoding structured data.

### Releasing
Releases are done frequently, weekly or fortnightly (some teams are daily)
- made possible by automating release tasks    
More release - motivated, more chance of feedback, ...
Release → `staging server` for integration testing  
→ `canary server` for processing small live traffic. (gradual roll-out process)  

### Frequent Rewrites
Most software at Google gets rewritten every few years.
It may seem costly, but is useful for following reasons.
requirements keep change
cutting complexity (which was accumulated during dealing with changing requirements without major rewrites)
Transferring knowledge and a sense of ownership.
Rewrite using modern tech and methods

### Project Management
20% of times on other projects

Individuals and teams at Google are required to (explicitly) document their goals, and to assess their progress towards these goals. 
- Bottom-up goal building process. 
- Progresses are evaled at the end of year.
- They are nor used directly as input to an individual's performance.
- The goals should be set high (desired avg score: 60%)
- key mechanism for comm. between each part

Somewhat frequent reorganizations.

### People
Mentor, Buddy.
Transfers between different parts of the company are encouraged.