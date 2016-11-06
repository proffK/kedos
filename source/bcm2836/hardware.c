#include "bcm2836/gpio.h"
#include "bcm2836/defines.h"
#include "lib/nostdlib.h"
#include "lib/error.h"
#include "sys/resources.h"
#include "sys/hardware.h"

static int processor_init(res_unit* proc)
{
        proc_res* proc_data = (proc_res*) kmalloc (sizeof(proc_res));
        if (proc_data == NULL) 
                return -ENOMEM;
        proc->data = proc_data;
        proc_data->cores = CORES_NUM;
        proc_data->freq = BASE_FREQ;
        return 0;
} 

static int processor_free(res_unit* proc)
{
        kfree(proc->data);
        return 0;
}

static int gpio_init(res_unit* gpio)
{
        gpio_res* gpio_data = (gpio_res*) kmalloc (sizeof(gpio_res));
        if (gpio_data == NULL) 
                return -ENOMEM;
        gpio_data->number = *((int*) gpio->data);
        gpio->data = gpio_data;
        return 0;
} 

static int gpio_free(res_unit* gpio) 
{
        kfree(gpio->data);
        return 0;
}

ftable proc_ftable = {
        processor_init,
        processor_free,
        NULL,
        NULL
};

ftable gpio_ftable = {
        gpio_init,
        gpio_free,
        NULL,
        NULL
};

int hardware_init()
{
        int i, ret;
        res_unit** table = res_table_get();
        if (table == NULL) 
                return -EINVAL;

        res_unit* processor = (res_unit*) kcalloc (1, sizeof(res_unit));
        if (processor == NULL) 
                return -ENOMEM;

        res_unit* gpio = (res_unit*) kcalloc 
                         (GPIO_NUM, sizeof(res_unit));
        if (gpio == NULL) {
                kfree(processor);
                return -ENOMEM;
        }

        processor->tb = (ftable*) &proc_ftable;
        processor->type = res_compose(RES_CPU, 0, 0, 0);
        res_add(processor);

        for (i = 0; i < GPIO_NUM; ++i) {
                *((int*) gpio[i].data) = i;
                gpio[i].tb = (ftable*) &gpio_ftable;
                gpio[i].type = res_compose(RES_DEV, RES_GPIO, 0, 0);
                res_add(gpio + i);
        }

        for (i = 0; table[i] != NULL; ++i) {
                ret = table[i]->tb->res_init(table[i]);
                if (ret != 0) {
                        goto fail;
                }
        }
        return 0;
fail:   
        kfree(processor);
        kfree(gpio);
        return ret;
}
