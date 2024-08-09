  int kvmfd = open("/dev/kvm", O_RDWR);
    ioctl(kvmfd, KVM_GET_API_VERSION, 0);