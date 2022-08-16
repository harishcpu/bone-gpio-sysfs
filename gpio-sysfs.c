/* -----------------------------------------------------------------------------
 * 	Filename   : gpio-sysfs.c	
 * 	Description: A GPIO sysfs driver  
 *	Created    : Monday 15 August 2022 01:36:37 IST
 *	Version    : 1.0
 *	Author     : Harish Kumar, Embedded Linux Developer, harishec031@gmail.com
 *	
 *	Copyright (c) 2022 Harish Kumar
 * ----------------------------------------------------------------------------- */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>

#undef pr_fmt
#define pr_fmt(fmt) "%s :" fmt, __func__

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harish Kumar <harishec031@gmail.com>");
MODULE_DESCRIPTION("A gpio sysfs driver");
MODULE_INFO(board, "Beaglebone Black REV A5");

/* Device private data structure */
struct gpiodev_private_data {
    char label[20];
};

/* Driver private data structure */
struct gpiodrv_private_data {
    int total_devices;
    struct class *class_gpio;
};

struct gpiodrv_private_data gpio_drv_data;


int gpio_sysfs_probe(struct platform_device *pdev) {
    int i = 0; 
    struct device *dev = &pdev->dev;
    const char *name;

    /* parent device node */
    struct device_node *parent = pdev->dev.of_node;
    struct device_node *child = NULL;

    struct gpiodev_private_data *dev_data;
    for_each_available_child_of_node(parent, child) {
        dev_data = devm_kzalloc(dev, sizeof(*dev_data), GFP_KERNEL);
        if(!dev_data) {
            dev_err(dev, "Cannot allocate memory\n");
            return -ENOMEM;
        }
        
        /* get label information of child nodes */
        if(of_property_read_string(child, "label", &name)) {
            dev_warn(dev, "Missing label information\n");
            snprintf(dev_data->label, sizeof(dev_data->label), "unknowngpio%d", i);
        } else {
            strcpy(dev_data->label, name);
            dev_info(dev, "GPIO label: %s\n", dev_data->label);
        } 
        ++i;
    }
    return 0;
}

int gpio_sysfs_remove(struct platform_device *pdev) {
    return 0;
}

struct of_device_id gpio_device_match[] = {
    {.compatible = "org,bone-gpio-sysfs"},
    {}
};

struct platform_driver gpiosysfs_platform_driver = {
    .probe = gpio_sysfs_probe,
    .remove = gpio_sysfs_remove,
    .driver = {
        .name = "bone-gpio-sysfs",
        .of_match_table = of_match_ptr(gpio_device_match) 
    }
};

int __init gpio_sysfs_init(void) 
{
    /* create a class named bone_gpios */
    gpio_drv_data.class_gpio = class_create(THIS_MODULE, "bone_gpios");
    if(IS_ERR(gpio_drv_data.class_gpio)) {
        pr_err("Error in creating class \n");
        return PTR_ERR(gpio_drv_data.class_gpio);
    }

    platform_driver_register(&gpiosysfs_platform_driver);
    pr_info("Module load success\n");
    return 0;
}

void __exit gpio_sysfs_exit(void) {
    class_destroy(gpio_drv_data.class_gpio);
    platform_driver_unregister(&gpiosysfs_platform_driver);
}
