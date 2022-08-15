# bone-gpio-sysfs
bone-gpio-sysfs is a GPIO sysfs driver to handle GPIOs of the beagle bone black AM335x hardware through Sysfs interface.

The driver should support the below functionality
1. The driver should create a class "bone_gpios" under /sys/class (class_create)
2. For every detected GPIO in the device tree, the driver should create a device under /sys/class/bone_gpios (device_create)
3. The driver should also create 3 sysfs files(attributes) for gpio device </br>
&nbsp;&nbsp;&nbsp;Attributes: </br>
&nbsp;&nbsp;&nbsp;1. direction: used to configure gpio direction </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;possible values: 'in' and 'out' </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;mode: read/write </br>
&nbsp;&nbsp;&nbsp;2. value: used to enquire the state of the gpio or to write a new value to the gpio </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;possible values: 0 and 1 (read/write) </br>
&nbsp;&nbsp;&nbsp;3. label: used to enquire label of the gpio (read only) 
4. Implement show and store methods for the attributes
