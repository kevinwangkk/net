net
	网络分层
	
	
	物理层 					PHY层
	数据链路层				MAC层(Medium Access Control 媒体访问控制)
								[解决 发给谁，谁接收的问题]
								最后面是CRC，循环冗余检测，XOR异或算法
								ARP协议，已知IP地址，获得MAC地址
								RARP协议，已知MAC地址，获得IP地址
	网络层 (路由协议)		IP层
	传输层					TCP / UDP层
	
	

一. 基础概念
1.	二层设备 L2
		工作在数据链路层的设备(把MAC头摘下来)，MAC层。(交换机switch)根据MAC地址进行转发或丢弃
		
	三层设备 L3
		工作在网络层的设备(把IP头摘下来)，IP层。(路由器)根据IP地址进行转发或丢弃
		
	

2.	MAC地址主要应用于局域网通信(MAC地址无定位功能)
	IP地址用于跨子网通信(IP地址有定位功能)	
	
	三层头中有协议类型(tcp / udp)
	四层头中有端口号(给哪个应用程序)


	
	
3.	命令 : ip addr (iproute2工具中) / ifconfig (net-tools工具中)
	
	net-tools起源于BSD，自2001年起，Linux社区已经对其停止维护，而iproute2旨在取代net-tools，并提供了一
	些新功能。一些Linux发行版已经停止支持net-tools，只支持iproute2。
	net-tools通过procfs(/proc)和ioctl系统调用去访问和改变内核网络配置，而iproute2则通过netlink套接字接口与
	内核通讯。
	net-tools中工具的名字比较杂乱，而iproute2则相对整齐和直观，基本是ip命令加后面的子命令。
	
	root@test:~# ip addr
	1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default 
		link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
		inet 127.0.0.1/8 scope host lo
		   valid_lft forever preferred_lft forever
		inet6 ::1/128 scope host 
		   valid_lft forever preferred_lft forever
	2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
		link/ether fa:16:3e:c7:79:75 brd ff:ff:ff:ff:ff:ff
		inet 10.100.122.2/24 brd 10.100.122.255 scope global eth0
		   valid_lft forever preferred_lft forever
		inet6 fe80::f816:3eff:fec7:7975/64 scope link 
		   valid_lft forever preferred_lft forever

	   
4.	无类型域间选路(CIDR)

		10.100.122.2/24 这种地址表现形式,就是CIDR. 32位中,前24位是网络号,后8位是主机号
		
		10.100.122.255 广播地址 
		255.255.255.0  子网掩码
		广播地址与子网掩码 AND计算 , 10.100.122.0 是网络号
		
5.	私有IP地址范围(局域网IP)
		A类 10.0.0.0 - 10.255.255.255			最大主机数 16777214
		B类 172.16.0.0 - 172.31.255.255 		65534
		C类 192.168.0.0 - 192.168.255.255		254
	
6.	net_device_flags 网络设备的状态标识
		eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
		
		UP 表示网卡处于启动的状态；
		
		BROADCAST 表示这个网卡有广播地址，可以发送广播包；
		
		MULTICAST 表示网卡可以发送多播包
		
		LOWER_UP 表示L1是启动的
		
		mtu 1500 MAC payload 不允许超过1500个字节  (MAC头14字节,尾部校验码4字节,二层MAC帧大小不超过1518)
		
		qdisc pfifo_fast  qdisc全称queueing discipline 排队规则
		
		pfifo_fast 队列包含三个波段(band) 
			band 0 优先级最高, band 2 最低
			band 0 里面有数据包,系统就不会处理band 1 里面的数据包
			数据包按照服务类型(Type of Service,TOS)被分配到三个band中.
				TOS是IP头中的一个字段
				
	
7. 配置IP地址
	net tools：
		$ sudo ifconfig eth1 10.0.0.1/24
		$ sudo ifconfig eth1 up
		   
	iproute2:
		$ sudo ip addr add 10.0.0.1/24 dev eth1
		$ sudo ip link set up eth1
		
8. 只有是一个网段的，它才会发送 ARP 请求，获取 MAC 地址。
	
   Linux 默认的逻辑是，如果这是一个跨网段的调用，它便不会直接将包发送到网络上，而是企图将包发送到网关。
   
   跨网段的通信，一般都是ip包头的目标地址是最终目标地址，但2层包头的目标地址总是下一个网关的
   
   
三. DHCP(动态主机配置协议 Dynamic Host Configuration Protocol)

	广播包封装了UDP，UDP封装了BOOTP
   
    PXE客户端， 安装系统


四. 交换机中使用 - STP协议（Spanning Tree Protocol）
	解决在网络中多个交换机的数据发送给谁的问题（交换机优先级）


五. VLAN
	二层的头上加一个 TAG，里面有一个 VLAN ID，一共12位，可以划分 4096 个 VLAN
	
	802.1Q Tag ： 类型， 优先级， 规范格式， VLAN ID（12位）


	VTAG   VLAN ID

二. 实验	   
	你网关的ip地址 不对  跨网段就ping不通   
	你直连 ping  即使网关ip不对也能ping通


	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   
	   


