#define _hypercall1(type, name, a1)
({
    long __res, __ign1;
    asm volatile (
        "call hypercall_page _ ("STR(__HYPERVISOR_##name)"*32)"\
        : "=a" (__res), "=b" (__ign1)\
        : "1" ((long)(a1))\
        : "memory");
    (type)__res;
    )
})