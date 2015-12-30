# linux_deamon
This is a deamon program, which run with root privilege and can start any other program with root privilege.xiong-bin@live.com

compile command:
gcc pdeamon.c -o pdeamon
gcc client.c -o client

post-compile:
sudo chown root:root pdeamon
sudo chmod +s pdeamon
