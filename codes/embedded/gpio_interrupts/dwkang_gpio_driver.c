#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

MODULE_LICENSE("Dual BSD/GPL");



#define MAJOR_NUMBER 240
#define DEVICE_NAME "irq_dwkang_test"
#define GPIO_DEBOUNCE_TIME 100
#define GPIO_OUT_PIN 30
#define GPIO_IN_PIN 60
#define LED_CLEAR 0
#define LED_SET 1

int gpio_irq_num = 0;
char toggle = 1;
int led_open(struct inode *, struct file *);
int led_release(struct inode *, struct file *);
long led_unlocked_ioctl(struct file *, unsigned int, unsigned long);
int led_init(void);
int led_exit(void);

int led_open(struct inode* inode_p, struct file* file_p){
    printk("[DWKANG] open() major = %d, minor = %d\n", MAJOR(inode_p->i_rdev), MINOR(inode_p->i_rdev));
    return 0;
}

int led_release(struct inode* inode_p, struct file* file_p){
    printk("[DWKANG] release");
    return 0;
}

long led_unlocked_iotcl(struct file* file_p, unsigned int command, unsigned long arg){
    switch(command){
        case 0:
        {
            if(arg == 0){
                gpio_set_value(GPIO_OUT_PIN, 0);
            }else if(arg == 1){
                gpio_set_value(GPIO_OUT_PIN, 1);
            }
            printk("[DWKANG] ioctl commane = %d, arg = %d\n", command, (int)arg);
        }
        break;
        default:
        printk("[dwkang] ioctl error\n");
        break;
    }
    return 0;
}

irqreturn_t irq_gpio(int irq, void *ident){
    printk("[DWKANG] interrupt by gpio 13\n");
    if(toggle){
        toggle = !toggle;
        gpio_set_value(GPIO_OUT_PIN, 1);
        printk("[dwkang] 1\n");
    }else{
        toggle = !toggle;
        gpio_set_value(GPIO_OUT_PIN, 0);
        printk("[dwkang] 0\n");
    }
    return IRQ_HANDLED;
}

struct file_operations led_file_oper = {
    .owner = THIS_MODULE,
    .open = led_open,
    .unlocked_ioctl = led_unlocked_iotcl,
    .release = led_release,
};

int led_init(void){
    if(gpio_request(GPIO_OUT_PIN, "DWKANG_OUT_INTERRPUT") != 0)
        printk("[DWKANG] gpio_request failed for out pin\n");
    
    if(gpio_request(GPIO_IN_PIN, "DWKANG_IN_INTERRPUT") != 0)
        printk("[DWKANG] gpio_request failed for in pin\n");

    if(gpio_export(GPIO_OUT_PIN, 1) < 0)
        printk("[DWKANG] gpio_export failed for out pin\n");
    
    if(gpio_export(GPIO_IN_PIN, 1) < 0)
        printk("[DWKANG] gpio_export failed for in pin\n");

    if(gpio_direction_output(GPIO_OUT_PIN, 1) != 0)
        printk("[DWKANG] gpio_direction_output failed for out pin\n");
    
    if(gpio_direction_input(GPIO_IN_PIN) != 0)
        printk("[DWKANG] gpio_direction_output failed for in pin\n");

    if(register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &led_file_oper) < 0){
        printk("[DWKANG] driver init failed\n");
        return -1;
    }    
    printk("1\n");
    gpio_set_debounce(GPIO_IN_PIN, GPIO_DEBOUNCE_TIME);
    printk("2\n");
    gpio_irq_num = gpio_to_irq(GPIO_IN_PIN);
    printk("3\n");
    int req_irq_rlt = request_irq(gpio_irq_num, irq_gpio, 0, "gpio_60", NULL);
    printk("4\n");
    if(req_irq_rlt < 0)
        printk("[DWKANG] request irq error with %d\n", req_irq_rlt);
    irq_set_irq_type(gpio_irq_num, IRQ_TYPE_EDGE_RISING);
    printk("[DWKANG] lef init success\n");
    return 0;
}

int led_exit(void){
    printk("[DWKANG] module is exiting\n");
    gpio_free(GPIO_OUT_PIN);
    gpio_free(GPIO_IN_PIN);
    printk("[DWKANG] freeing irq. why am i called?\n");
    free_irq(gpio_irq_num, NULL);
    unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
    return 0;
}

module_init(led_init);
module_exit(led_exit);