#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x4cc15df2, "module_layout" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x215681ae, "drm_calc_timestamping_constants" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x431b892c, "drm_mode_create_from_cmdline_mode" },
	{ 0x341aa7b2, "drm_mode_destroy" },
	{ 0x26e7b620, "malloc_sizes" },
	{ 0x4d974b9c, "register_sysrq_key" },
	{ 0xf1421d13, "drm_mode_sort" },
	{ 0x3a212a7c, "drm_get_encoder_name" },
	{ 0x8949858b, "schedule_work" },
	{ 0xa5f0804c, "drm_get_connector_name" },
	{ 0x607a7a11, "drm_mode_parse_command_line_for_connector" },
	{ 0x1976aa06, "param_ops_bool" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0x6baae653, "cancel_delayed_work_sync" },
	{ 0xc0ba13f7, "mutex_unlock" },
	{ 0x35ec28e8, "atomic_notifier_chain_unregister" },
	{ 0x3823c7fa, "i2c_add_adapter" },
	{ 0xd2335101, "drm_fb_get_bpp_depth" },
	{ 0x88ab6fe3, "kgdb_active" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0x81bbc364, "drm_mode_find_dmt" },
	{ 0xcb7131fb, "fb_get_options" },
	{ 0x27e1a049, "printk" },
	{ 0xdbe3d949, "drm_mode_duplicate" },
	{ 0xc7805c4f, "register_framebuffer" },
	{ 0x74b397ca, "mutex_lock" },
	{ 0xfe5d283e, "drm_mode_width" },
	{ 0x1f8544b8, "panic_timeout" },
	{ 0x9745d638, "drm_err" },
	{ 0xac801c81, "drm_mode_connector_update_edid_property" },
	{ 0xa0951f62, "drm_mode_validate_size" },
	{ 0xb964fcc2, "drm_mode_connector_list_update" },
	{ 0x90e3da26, "drm_mode_set_crtcinfo" },
	{ 0xe156087b, "drm_mode_prune_invalid" },
	{ 0x45504103, "drm_mode_height" },
	{ 0xc12828b2, "drm_connector_property_set_value" },
	{ 0xa0fb7bd2, "atomic_notifier_chain_register" },
	{ 0x4dcf08ce, "drm_sysfs_hotplug_event" },
	{ 0x1aff077e, "panic_notifier_list" },
	{ 0x69e97209, "drm_mode_debug_printmodeline" },
	{ 0x4befbe6a, "drm_add_modes_noedid" },
	{ 0xb9012926, "kmem_cache_alloc_trace" },
	{ 0x3534e2a3, "system_nrt_wq" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0x65028277, "drm_mode_equal" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x498dcb5e, "drm_ut_debug_printk" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0xcbc9557f, "unregister_sysrq_key" },
	{ 0x47c149ab, "queue_delayed_work" },
	{ 0xfa4315a9, "drm_mode_vrefresh" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=drm";


MODULE_INFO(srcversion, "D820DAAC2778E359DF16364");
