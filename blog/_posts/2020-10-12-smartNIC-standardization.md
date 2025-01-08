---
layout: post
comments: true
author: Mario Baldi and Vipin Jain
title:  The Need for Standardization in a Thriving Network Ecosystem
date: 2020-10-12
---


The SmartNIC industry has made valuable strides in standardizing various interfaces of the infrastructure stack, but clearly there is a lot more work to be done as discussed above. Since its inception, Pensando has pursued a vision and focus on revolutionizing this space – including hardware, software, ecosystem, tools, manageability, standardization, and a push towards open source. Consequently, we are committed to contributing to an open and thriving SmartNIC ecosystem.

Open standards are an essential component in thriving technology ecosystems. They benefit users, vendors, and third parties developing software applications. An area that has seen explosive growth over the last few years is that of Network Interface Cards, commonly referred to as NICs. During this time of growth there has been a huge amount of innovation with some NICs evolving beyond general connectivity to taking over many other tasks, such as improving and accelerating server availability, bandwidth performance and data transport efficiency in a network, and even security.

Today, many of these devices have a processor, onboard memory, peripheral interfaces, and are often highly programmable. Some even incorporate functions that have traditionally been executed on dedicated appliances or switches. Sometimes called a FAC (Functional Accelerator Card – Gartner), FOCP (Functional Off-load CoProcessor – IDC), DPU (Data Processing Unit – NVidia), Nitro (AWS), SmartNIC or NIC, at Pensando we refer to our device as the Distributed Services Card (DSC). All these devices have one thing in common: they are the spot where the network and the server come together. For the purposes of this article we will use the term SmartNIC as a catch-all descriptor for this class of devices.

Even though SmartNICs have been used in the public cloud infrastructure for many years, the technology is still in the beginning of its life cycle in other application domains and the need for an open source ecosystem is perceived now stronger than ever.

Several elements of the SmartNIC solution stack call for standardization (beyond naming the devices themselves); each one is discussed in the following:

**IO Datapath**: One of the benefits of SmartNICs is the ability to offload functions for network, storage, observability, and security services applied to data entering and exiting the host. Being able to address a wide range of services and applications that generate traffic requires the SmartNIC data plane to be programmable. While programmability is beneficial to the SmartNIC vendor who can incrementally and promptly develop new features, it is even more valuable when customers and third parties can leverage it to address additional use cases, even proprietary and niche ones. This requires a standardized, open, portable, datapath definition so that the implementation of use cases is decoupled from the specific hardware datapath implementation. At Pensando, we are embracing open programmable datapath and P4 as the language of choice to program it. The initial datapath definition supported by the P4 community, the Portable Switch Architecture (PSA), was specified with network switches in mind. However, SmartNICs have always been seen as a possible target for P4 and, right after finalizing the PSA, the P4 community started working on a Portable NIC Architecture (PNA) specification. Pensando has joined the efforts of the Architecture Work Group to actively contribute to the PNA specification and help finalize it in the shortest time possible to confirm P4 as the standard programming language for the SmartNIC datapath.

**PCIe Software Interface**: access to peripherals in general, and the network interface in particular, must be standardized, so that users can deploy any standard operating system without having to depend on vendor specific drivers. But more importantly, end users and third parties can create new PCIe functions and acceleration logic independent of the SmartNIC vendor. While this has been addressed for a while by PCIe virtualization for virtual machines in virtualized environments, the time is ripe to introduce similar concepts on bare metal hosts: virtualized NVMe block storage and virtualized vDPA/VirtIO Ethernet drivers. At Pensando, we are embracing this approach and are working on drivers that we are being upstreamed in all major operating systems.

**Bootstrap and Hardware Management**: SmartNICs boot their own operating system, independent of the host one: they are a relatively small system with their own CPU, memory, and storage. A standard, secure way to boot an operating system, discovering any peripherals would be essential to enable SmartNIC vendors to bootstrap their choice of operating system. SmartNICs can follow the lead of the server boot process and consider UEFI (Unified Extensible Firmware Interface) or ACPI (Advanced Configuration and Power Interface) for peripheral discovery and operating system bootstrap. There are clearly some differences between a host and a SmartNIC architecture: a SmartNIC may not have a full BIOS, BMC (Baseboard Management Controller), the same level of hardware standardization, and a Redfish-like API to manage the SmartNIC when powered off. However, all of these aspects could be addressed by the community to converge towards a common, open, and standard solution. At Pensando, we plan to use UEFI, ACPI, and standardized server elements to allow for a portable operating system bootstrap.

**SmartNIC Operating System**: Many vendors use some flavor of Linux on their SmartNICs. Even though Linux is an open source software, there is no one distribution that can be deployed on all SmartNICs alike. Standardizing the SmartNIC bootstrap process and hardware management (much like ARM did with their Server Base System Architecture and Server Board Boot Requirements) will allow for the operating system to be standardized and open. This will open up opportunities for end users and third parties to create services and applications (including not just the fast datapath, but also exception path, control plane and management functionality) on SmartNICs. There are also efforts by software solution providers, such as VMware, to build a universal operating system for any SmartNIC: a version of the ESXi operating system called ESXio, Although universal, such operating system is not open, which represents a show stopper for many end users and use cases. At Pensando, we have adopted a Linux flavor and have open sourced all changes made to the kernel and relevant tools (see http://github.com/pensando), which is a first step towards an open SmartNIC operating system. Pensando is interested in working with the community towards a standardized solution.

**Portable APIs**: The usability of a great piece of hardware is determined by the software that wraps it up. Therefore simple, easy to understand, open APIs go a long way in streamlining the deployment of SmartNICs. Such APIs can be used to access, configure, control, and manage network, security, storage, and observability services offered by a SmartNIC. Whether exposed as network-based APIs (e.g., REST or gRPC), or linkable libraries, the availability of standardized APIs allows software developers to easily integrate SmartNICs in their environments, cloud and enterprise alike. There are many attempts in the industry to offer such standardized APIs for switches, one notable example being [SONIC](https://github.com/Azure/SONiC/blob/master/sourcecode.md). At Pensando, we are working towards defining cloud-like APIs that can be handily used by any cloud-like controller to control and manage various services, as well as for life cycle management of SmartNICs.

**Controller**: SmartNIC deployment at scale – key in cloud environments, but also important in many enterprise contexts – is subordinate to the availability of a management software that can handle hundreds and thousands of SmartNICs as a unified infrastructure. Users manage and control services implemented by the SmartNICs as abstract, distributed entities, with very limited need to ever refer to individual cards. While there are some open initiatives for the managements of networks of switches, such as [OVN](https://github.com/ovn-org/ovn), [OpenDayLight](https://www.opendaylight.org/) or [Tungsten fabric](https://tungsten.io/), there is currently no controller targeting a set of SmartNICs, which is a major challenge and something that requires a significant effort. At Pensando we have developed a controller called the Policy and Services Manager (PSM) that deploys an intent-based approach to the management of large sets of SmartNICs. Recognizing the value of open standards, Pensando is willing to share with the SmartNIC community its experience with the PSM for the definition of an open controller for SmartNICs.

**Cloud APIs**: The top level abstraction needed for a SmartNIC ecosystem is an API exposed by a SmartNIC controller. This is particularly critical for cloud deployments as it enables the integration of the controller with a cloud orchestrator, but it may be valuable also in enterprise scenarios. The most open and standard way of managing cloud applications is by means of Kubernetes and ServiceMesh. At Pensando, we embrace Kubernetes and other [Cloud Native Computing Foundation (CNCF)](https://www.cncf.io/) projects and plan to support Kubernetes APIs and ServiceMesh in the services offered on our platform, thereby keeping the users’ consumption model consistent, whether on-prem or in the cloud.

The SmartNIC industry has made valuable strides in standardizing various interfaces of the infrastructure stack, but clearly there is a lot more work to be done as discussed above. Since its inception, Pensando has pursued a vision and focus on revolutionizing this space – including hardware, software, ecosystem, tools, manageability, standardization, and a push towards open source. Consequently, we are committed to contributing to an open and thriving SmartNIC ecosystem.

*This article was [originally posted](https://pensando.io/a-chat-about-forwarding/) on the [Pensando Systems](https://pensando.io/) [blog](https://pensando.io/blog/).*