#include <stdio.h>
#include <stdlib.h>


FILE* config;
char version[15],command[190];
int mode;

int main() {
Menu:UI();
    system("clear");
    if (mode == 1) {
        install_snell();
        goto Menu;
    }
    else if (mode == 2) {
        printf("正在关闭snell. . .\n");
        system("systemctl stop snell");
        printf("正在启动snell. . .\n");
        system("systemctl start snell");
        printf("正在验证snell启动，不为空则启动成功. . .\n");
        system("ss -lp | grep snell");
        goto Menu;
    }
    else if (mode == 3) {
        printf("Snell配置:\n\n");
        system("cat /etc/snell/snell-server.conf");
        printf("\n\n");
        goto Menu;
    }
    else if (mode == 4) {
        printf("正在关闭snell. . .\n");
        system("systemctl stop snell");
        printf("正在生成配置文件. . .\n");
        config = fopen("/etc/snell/snell-server.conf", "w");
        fprintf(config, "[snell-server]\n");
        fprintf(config, "listen = 0.0.0.0:443\n");
        fprintf(config, "obfs = tls\n");
        fprintf(config, "psk = ");
        fclose(config);
        printf("正在生成强密码. . .\n");
        system("pwgen -s 28 1 > /etc/snell/passwd.conf");
        system("cat /etc/snell/passwd.conf >> /etc/snell/snell-server.conf");
        printf("正在启动snell. . .\n");
        system("systemctl start snell");
        printf("正在验证snell启动，不为空则启动成功. . .\n");
        system("ss -lp | grep snell");
        printf("snell部署完成！\n");
        printf("\nSnell配置:\n\n");
        system("cat /etc/snell/snell-server.conf");
        printf("\n\n");
        goto Menu;
    }
    else if (mode == 5) {
        printf("正在关闭snell. . .\n");
        system("systemctl stop snell");
        goto Menu;
    }
    else if (mode == 6) {
        SnellUpdate();
        goto Menu;
    }
    else {
        exit(0);
    }
    return 0;
}

int UI() {
    printf("-----------------------------------------------------------\n");
    printf("----------------------Surge Snell安装工具------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("----------------------当前Kernel版本-----------------------\n");
    system("uname -sr");
    printf("-----------------------------------------------------------\n");
    printf("1.安装Snell\n2.运行Snell\n3.显示配置\n4.修改配置\n5.关闭snell\n6.更新snell\n0.退出\n");
    printf("-----------------------------------------------------------\n");
    printf("请输入:");
    scanf("%d", &mode);
    return 0;
}

int install_snell() {
    KernelUpdate();
    system("setenforce 0");
    system("yum install -y curl pwgen unzip bind-utils");
    system("mkdir -p /etc/snell");
    system("wget https://github.com/surge-networks/snell/releases/download/v2.0.3/snell-server-v2.0.3-linux-amd64.zip -O snell-server-v2.0.3-linux-amd64.zip");
    system("unzip snell-server-v2.0.3-linux-amd64.zip");
    system("mv snell-server /usr/local/bin/");
    system("rm -rf snell-server-v2.0.3-linux-amd64.zip");
    printf("正在生成配置文件. . .\n");
    config = fopen("/etc/snell/snell-server.conf", "w");
    fprintf(config, "[snell-server]\n");
    fprintf(config, "listen = 0.0.0.0:443\n");
    fprintf(config, "obfs = tls\n");
    fprintf(config, "psk = ");
    fclose(config);
    printf("正在生成强密码. . .\n");
    system("pwgen -s 28 1 > /etc/snell/passwd.conf");
    system("cat /etc/snell/passwd.conf >> /etc/snell/snell-server.conf");
    printf("正在启动snell并将snell写入开机引导项. . .\n");
    system("curl https://raw.githubusercontent.com/HXHGTS/SnellServer/main/snell.service > /usr/lib/systemd/system/snell.service");
    system("systemctl daemon-reload");
    system("systemctl enable snell && systemctl start snell");
    printf("正在验证snell启动，不为空则启动成功. . .\n");
    system("ss -lp | grep snell");
    printf("snell部署完成！\n");
    printf("\nSnell配置:\n\n");
    system("cat /etc/snell/snell-server.conf");
    printf("\n\n");
    return 0;
}
int SnellUpdate() {
    printf("请输入当前最新版本号，如2.0.3:");
    scanf("%s", version);
    printf("正在关闭snell. . .\n");
    system("systemctl stop snell");
    sprintf(command,"wget https://github.com/surge-networks/snell/releases/download/v%s/snell-server-v%s-linux-amd64.zip -O snell-server-v%s-linux-amd64.zip",version,version,version);
    system(command);
    sprintf(command, "unzip snell-server-v%s-linux-amd64.zip",version);
    system(command);
    system("rm -rf /usr/local/bin/snell-server");
    system("mv snell-server /usr/local/bin/");
    sprintf(command, "rm -rf snell-server-v%s-linux-amd64.zip",version);
    system(command);
    printf("正在启动snell. . .\n");
    system("systemctl start snell");
    printf("正在验证snell启动，不为空则启动成功. . .\n");
    system("ss -lp | grep snell");
    printf("snell部署完成！\n");
    return 0;
}

int KernelUpdate() {
    if ((fopen("KernelUpdate.sh", "r")) == NULL) {
        printf("正在升级新内核. . .\n");
        system("wget https://github.com/HXHGTS/TCPOptimization/raw/master/KernelUpdate.sh");
        system("chmod +x KernelUpdate.sh");
        printf("正在升级，将自动触发重启以应用配置. . .\n");
        system("bash KernelUpdate.sh");
    }
    else {
        system("wget https://github.com/HXHGTS/TCPOptimization/raw/master/TCPO.sh");
        system("chmod +x TCPO.sh");
        system("bash TCPO.sh");
    }
    return 0;
}