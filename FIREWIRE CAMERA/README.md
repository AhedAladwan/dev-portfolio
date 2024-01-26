FIREWIRE CAMERAS

Firewire (IEEE1394) is a very fast external bus standard that supports data transfer rates of up to 400Mbps in IEEE 1394a, and up to 3.2 Gbps in IEEE1394b. A single IEEE 1394 port can be used to connect up to 63 external devices. In addition to its high speed, IEEE1394 also supports isochronous data - delivering data at a guaranteed rate. This makes it ideal for devices that need to transfer high priority data in real-time, such as video devices. The IEEE1394 bus supports both Plug-and-Play and hot plugging, and also provides power to peripheral devices.

Many new cameras are equipped with Firewire interface. These cameras are more preferment, offering more valuable features in comparison to traditional analogue cameras. In order to fulfill all requirements in the SLS, it was decided to integrate the Firewire cameras to the existing control system. EPICS SERVER Epics Server: Introduction

Recent development in EPICS (3.14.x) has allowed for an operating system independent implementation. We decided to benefit from interfacing a Firewire camera to an EPICS server running on a Linux PC. Linux offers open source libraries that support Firewire devices, thus it appeared to be well suited for the camera integration. In addition, an X windows (motif) application was developed to provide a live feed from the camera by reading the image waveform. In the following, we explain software and hardware aspects, and typical applications of Firewire camera based systems at the SLS.

Epics Server: Server side

EPICS based image acquisition server depends on several software components which can be dynamically loaded to the Linux kernel at run time. The layered architecture of the EPICS server is presented in Fig. 1.
Recent Linux kernels (> 2.4) are coming with built-in IEEE1394 modules:

	*ieee1394: Core of the IEEE1394 subsystem.
	*raw1394: Higher level driver module for bus access.
	*video1394: Fast DMA frame transfer driver.
	*ohci1394: Low level host card driver.
At the user space level, Libraw1394 is a library that provides access to the raw1394 bus module and Libdc1394 is a high level API.


![image003](https://github.com/AhedAladwan/dev-portfolio/assets/947732/8d7155c0-d0bc-43e9-9df6-f9eef75eedec)

EPICS device support uses non-polling (blocking) DMA capture functions for image acquisition. An image acquisition process is repeated periodically. First the single image is captured, processed and then placed in the waveform. Any Channel Access (EPICS) based application can retrieve an image from the waveform.
Moreover, the server performs on-line centriod finding algorithm, background subtractions, averaging (i.e. improves signal-to-noise ratio), maximum pixelintensity calculation, standard deviation, and calibration.

Epics Server:Client side

An medm GUI is used to control the camera and EPICS server parameters, such as start/stop image transmission, region of interest selection, frame rate, shutter gain and threshold control. It also shows both vertical and horizontal distributions of the images pixel intensity, and includes an image save option (Fig. 2).

![image005](https://github.com/AhedAladwan/dev-portfolio/assets/947732/bd8dfda4-48a9-4a5d-85ca-f243d976d3f2)

A motif based application is used to display captured images in live mode. The application uses Channel Access libraries, therefore it is already integrated with EPICS. The application displays the images which are stored in the waveform channels on the server side. EPICS monitoring mechanism enables the client application to display newly acquired images when the waveform updates. The application can display monochrome and color images. Users can choose one of many color interpolation algorithms for Bayer color representation at run time (Fig. 3).

![image007](https://github.com/AhedAladwan/dev-portfolio/assets/947732/2a3c73de-c009-4a0a-89ce-81143654bad1)

Epics Server:Hardware Description

We are using a compact desktop (Barebone) called Pundit and Pundit-R, both manufactured by ASUS. This desktop is about a third of the volume of a conventional desktop PC. It has high-speed processing power with 2.8GHz Pentium 4 CPU and 1 GB RAM. The motherboard has a built-in Open Host Controller Interface (OHCI) compatible Firewire card with 6-pin port.
The Camera is a Point Grey Flea which is compliant with IIDC 1394-Based Digital Camera Specifications (also know as DCAM spec). This specification describes a CSR - Control and Status Register - layer on top of IEEE1394. The camera resolutions varies from a low of 640x480 to a high of 1024x768 pixels, it support frame rates from 1.875 up to 60 fps. It can use internal soft triggers or be triggered externally, this allows for synchronizing with other subsystems. The camera size is small, 30mm x 31mm x 29mm, this helps mounting it in crowded as well as not easily accessible locations.

Epics Server:Applications

FEMTO Slicing Laser Stabilization Feedback
The FEMTO laser focus point - where the electron and laser beams interact - is approximately 45 meters away from the laser source. With 4 mirrors along the laser path, there are many potential causes for laser drift (laser source, optical components, temperature). A laser monitoring system based on Firewire digital cameras was implemented. The image is grabbed, processed and the center of mass is calculated. A feedback system will use this information andadjust the mirrors accordingly to compensate for the drift. Thus it will maintain optimal electron and laser beams interaction conditions.

![image011](https://github.com/AhedAladwan/dev-portfolio/assets/947732/9db451b8-7d63-4bbf-90a6-856ebd360e46)

X-ray Beam-position Monitoring

Critical information about the X-ray beam shape, profile and position is extracted. The setup used at the micro Absorption Spectroscopy (mXAS) beamline includes a scintillator that converts x-rays into visible light, lenses that enables to change the field of view and thus obtain higher resolution, and a Firewire digital camera.

Beamline Equipment Commissioning

Commissioning of beamline optical components, using synchrotron light, such as monochromator crystals parallelism tests is an example of an application. Furthermore, stability of the synchrotron light and determining eventual sources of vibration are also sought.

Live feed

The client application is used to display a live feed of the monitored subsystem.

Epics Server: Results
The EPICS server approach allows for acquiring and processing the images at high rates (10 Hz). Thus, it can be used to track fast changes to the monitored system. On the other hand, it allows for online image processing to characterize synchrotron light and Laser beam. More importantly, it is fully integrated into the control system environment which has the obvious advantage of being operated simultaneously with other components in the beamlines or accelerator complex.
