#include <bcl.h>
#include <bc_usb_cdc.h>

bc_led_t led;

bc_lis2dh12_t a;
bc_lis2dh12_result_g_t a_result;

void lis2_event_handler(bc_lis2dh12_t *self, bc_lis2dh12_event_t event, void *event_param)
{
    (void)self;
    (void)event_param;

    if (event == BC_LIS2DH12_EVENT_UPDATE)
    {
        bc_lis2dh12_get_result_g(&a, &a_result);
        char message[100];
        sprintf(message, "X: %f\r\nY: %f\r\nZ: %f\r\n", a_result.x_axis, a_result.y_axis, a_result.z_axis);
        bc_usb_cdc_write(message, strlen(message));
    }
    else
    {
        bc_usb_cdc_write("error\r\n", strlen("error\r\n"));
    }
}

void application_init(void)
{
    bc_lis2dh12_init(&a, BC_I2C_I2C0, 0x19);
    bc_lis2dh12_set_event_handler(&a, lis2_event_handler, NULL);
    bc_lis2dh12_set_update_interval(&a, 1000);

    bc_usb_cdc_init();
}