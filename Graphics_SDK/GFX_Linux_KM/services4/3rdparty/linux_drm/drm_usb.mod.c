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
	{ 0x2dd4cf1a, "drm_global_mutex" },
	{ 0xd22db260, "dev_set_drvdata" },
	{ 0x26e7b620, "malloc_sizes" },
	{ 0xc0ba13f7, "mutex_unlock" },
	{ 0x4a4c0ddb, "drm_fill_in_dev" },
	{ 0xf7fd6dcf, "drm_put_minor" },
	{ 0x60fa9aee, "usb_deregister" },
	{ 0x27e1a049, "printk" },
	{ 0x74b397ca, "mutex_lock" },
	{ 0x9c3b3e1b, "drm_mode_group_init_legacy_group" },
	{ 0x33fb0e10, "drm_get_minor" },
	{ 0xb9012926, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x7c677373, "usb_register_driver" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x498dcb5e, "drm_ut_debug_printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=drm";


MODULE_INFO(srcversion, "7138C3EDE03B4ABCC8CF6CA");
