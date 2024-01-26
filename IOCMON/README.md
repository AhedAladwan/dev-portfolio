What is IOCMON?

It is an IOC monitoring application that runs @ the IOC (EPICS + vxWorks) and monitors the available resources. It extends the current vxstats functionality and provide the data in a more readable way. For example, instead of showing a string that includes all the boot parameters, we have separated each individual boot parameter and provide it as an independent EPICS channel. Moreover, it additionally report network interface statistics and channel access links.
For example it reports the following:

Memory

- Number of bytes in the IOC that is not allocated
- Number of bytes allocated
- Size of largest free block

CPU

- Estimated percent CPU usage by tasks
- CPU Heart Beat (Alive)
- System File Descriptors
- Number of file descriptors currently in use Channel Access
- Number of current CA clients
- Number of current CA clients connections
- Number of CA database links
- Number of CA database links not connected
- Number of CA database links disconnected Network Interface
- Number of times failed to find space
- Number of times waited for a space
- Number of times drained protocol for space (no. of IP fragments that are dropped)
- Number of sent packets
- Number of received packets
- Number of input errors
- Number of output errors
- Number of dropped packets
- Number of collisions (This is an indication of the network medium load seen by the IOC)

Examples of Use (Networking)

For example, we see output errors reported by the IOC.s Network Interface (EPICS 3.13.9, MVME2300, vxWorks 5.3.1) once the Network Switch is configured to Full Duplex. We assume if there is a miss configured device that is spamming packets, IOC.s in that subnet will start reporting collisions, the same should be true when the load goes very high.
This info can help to:
1- Detects problems in the network related to wrong equipment configuration and the like
2- Optimize our network stack configuration parameters to fit our applications needs
3- Anticipate future network operation needs

The GUI

![iocmon_T2_3 13 9_mv2300](https://github.com/AhedAladwan/dev-portfolio/assets/947732/e62cfd00-d857-4fc1-b9da-56025e7f32d3)
