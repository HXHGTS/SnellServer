# SnellServer

## 警告⚠：此技术仅限用于个人搭建游戏加速器使用！！！若用于其他违法目的，后果自负！！！

搭建snell服务器

### 一句话执行(CentOS):
```
yum install -y gcc wget && wget https://github.com/HXHGTS/SnellServer/raw/main/SnellServer.c -O SnellServer.c && chmod +x SnellServer.c && gcc -o SnellServer SnellServer.c && ./SnellServer
```

第一次点击安装后会自动升级系统内核并触发重启，重启后输入
```
./SnellServer
```
并选1继续安装

### 安装前准备：

1.脚本仅支持CentOS系统，vps必须为KVM或XEN架构

2.脚本执行需要root权限登录系统，AWS等特殊机型打开root权限方法[看这里](https://hxhgts.icu/AWSECSRoot/)

3.请在服务器后台防火墙放行tcp443(https)端口