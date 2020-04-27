---
layout: post
comments: true
title: "P4 Expert Roundtable Series: the Virtual Edition of the P4 Workshop"
author: "Mario Baldi"
permalink:
---

The P4 Workshop, the yearly event where the [P4 community](http://p4.org) gets together, usually at Stanford, to review a year of work, discuss future ideas, and in general discuss all things P4 was scheduled for today and tomorrow.
However, the COVID-19 pandemic got in the way, and as the date was approaching it became clear that such a large gathering of people would not be possible, even less would attendees from other areas be able to travel to California.<br>
Hence, a little more than three weeks ahead of the planned date, the Open Networking Foundation (ONF) took the somewhat brave decision to convert the event into a virtual one, which obviously implied changing the format of the event. And maybe to reinforce this, the name itself was changed to "[P4 Expert Roundtable Series](https://p4.org/events/2020-p4-summit/)".

# Pros and cons of a virtual event

Although, of course, the networking aspect of the P4 Workshop is missing (the one among people, not the one related to devices ...), judging by the program, the content does not seem to be affected by the change of format.  
On the other hand, since each talk has been separately recorded, the tight timing constraints of back-to-back talks typical of live events are relaxed and speakers have a chance to provide as much information as they deem needed. Not only, but if something goes wrong in the presentation, it can be fixed, thus potentially improving not only the content, but also the quality of presentations.   
Of course a Q&A discussion open to a wide audience is missing in the recorded sessions, but chairpersons have done a great job in making up for the lack of an audience by putting a particular effort in asking great questions. Moreover, the ONF organizers have come up with the good idea of structuring several of the presentations into panels, so that various presenters can discuss together and ask each other questions.

# Pensando contribution

Since [Pensando](http://pensando.io) with its P4 programmable platform is being [very active in this space](https://p4.org/p4/pensando-joins-p4.html), my colleagues and I are having a chance to experiment all three presentation formats that the virtual event offers.

Our CTO, [Vipin Jain](https://www.linkedin.com/in/jain-vipin/), is giving a [live webminar](https://www.youtube.com/watch?v=N3-IuAUsrio) on April 29, focusing on the motivation and benefits to extend P4 beyond packet processing to message processing, which is one of the areas that we are pioneering at Pensando with our P4-programmable [Distributed Services Card](https://pensando.io/assets/documents/Naples_100_ProductBrief-10-2019.pdf).

John Cruz and I participated in a roundtable on P4 Use Cases for Programmable NICs where, deploying code excerpts from the implementation of a few services, we demonstrated the benefits of  extending P4 and the PSA (Portable Switch Architecture) to account for the more articulated role of edge devices. This of course ties in the proposals we have made within the Architecture Working Group for the definition of a PNA (Portable NIC Architecture).  
We had a lively and interesting discussion with [Gordon Brebner](https://www.linkedin.com/in/gordonbrebner/) who was moderating the panel and has been also involved since the beginning in the efforts around the definition of a PNA.

Finally, I recorded a talk within the "Accepted Submissions" track. It presented a work co-authored with my colleagues Diego Crupnicoff and [Silvano Gai](https://www.linkedin.com/in/silvano-gai-15263b1/) (I'd like to thank also [Sameer Kittur](https://www.linkedin.com/in/sameer-kittur/), [Vijay Sampath](https://www.linkedin.com/in/vsampath/), and [Venkatesh Srinivasan](https://www.linkedin.com/in/venkatesh-srinivasan-76580515/) for sharing the results of their performance measurements) that shows how a few real world use cases can be optimally and efficiently supported by the various components of the programmable data plane of Pensando's [Distributed Services Card](https://pensando.io/assets/documents/Naples_100_ProductBrief-10-2019.pdf). Various performance measurements  show that the considered services can be executed at wire speed, and exemplify how the versatile programmable data plane architecture[^1] offers developers various options to ensure top performance. All of this was further enriched by the following discussion sparked by the very interesting and relevant questions asked by [Mina Tahmasbi Arashloo](http://www.cs.cornell.edu/~mt822/) who chaired the session.

[^1]: Although in the talk I provide an overview of architecture, if you want to know more about the ASIC implementing it in just a couple of minutes without going through my talk, take a look at this very cool [video](https://silvanogai.github.io/posts/capri/) by [Silvano](https://www.linkedin.com/in/silvano-gai-15263b1/)).

# Lots of great content: don't miss it!

All in all, as much as I regret the missed opportunity of seeing in person the various folks of this tight knit community I have been interacting with over the past years and grabbing a beer during the traditional evening reception, the recording of my contributions and the interactions with the chairperson and other contributors were very positive experiences, both personally and from the point of view of effectively sharing the work done. The [program](https://www.opennetworking.org/p4-expert-roundtable-series/) seems very promising and I am looking forward to watching the content that is made available. I highly recommend to register and get the videos.   
The one challenge will be to make sure to find the time for it among the various duties and conference calls we all have.  Being locked in the conference room of the Arrillaga Alumni Center would have helped a lot in this respect. But let's not allow this to compromise such a great opportunity to learn and get inspired.

And I am sure next year we'll see each other again in Stanford!
<br>
<br>
<hr>
