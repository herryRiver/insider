/******************************************************************************
* 系统名称：Net
* 文件名称：Net.h
* 版本    ：	V2.0.0.0.2
* 说明	  ：网络开发包接口,本SDK为和编码器交互提供接口
			该文件包含六部分：
			一、枚举类型定义；
			二、回调函数；
			三、接口结构类型定义；
			四、音视频网络帧头；
			五、函数接口定义；
* 其他说明: 无
******************************************************************************/
#ifndef  __NET_H__
#define  __NET_H__

#define PACKED  __attribute__((packed, aligned(1)))
#define PACKED4 __attribute__((packed, aligned(4)))


/*********************************  一、枚举类型定义  ******************************/

//1，数字视频服务器机器类型
typedef enum	DVS_MACHINE_TYPE_
{
	NONE = 0xff,
}DVS_MACHINE_TYPE;

//2，视频编码格式									
typedef enum  _ENCODE_VIDEO_TYPE
{
	EV_TYPE_NONE		= 0xFFFF,
}ENCODE_VIDEO_TYPE;

//3，升级类型
typedef enum _UPDATE_TYPE
{
	UPDATE_KERNEL,					//升级内核
	UPDATE_YUNTAI1,				//升级云台协议1
	UPDATE_YUNTAI2,				//升级云台协议2
	UPDATE_YUNTAI3,				//升级云台协议3
	UPDATE_YUNTAI4,				//升级云台协议4
	UPDATE_YUNTAI5,				//升级云台协议5
	UPDATE_YUNTAI6,				//升级云台协议6
	UPDATE_OCX,						//升级控件
	UPDATE_WEBPAGE,				//升级页面
	UPDATE_PATHFILE,				//升级特定目录文件
}UPDATE_TYPE;


//5，连接状态
typedef enum _CONNECT_STATUS
{
	CONNECT_STATUS_NONE,			//未连接
	CONNECT_STATUS_OK,				//已经连接
}CONNECT_STATUS;

//6，转发类型
typedef enum _RELAY_TYPE
{
	RELAY_LOGON,					//转发登录设置
	RELAY_PREVIEW,					//转发视频预览数据
	RELAY_TALK,						//转发对讲
	RELAY_AUDIOBRD,				//转发语音广播
	RELAY_QUERY						//转发的查询
}RELAY_TYPE;

//7，通知应用程序窗口消息命令
typedef enum _MSG_NOTIFY
{

    MSG_CONNECT_CLOSE,             //登录连接关闭 
    MSG_CHANNEL_CLOSE,             //通道连接关闭 
    MSG_TALK_CLOSE,                //对讲连接关闭 
    MSG_ALARM_OUTPUT,              //报警输出                   
    MSG_UPDATE_SEND_PERCENT,       //升级程序发送百分比 
    MSG_UPDATE_SAVE_PERCENT,       //升级写入发送百分比
    MSG_VIEWPUSH_CLOSE ,           //解码器视频输入关闭 
   	MSG_BROADCAST_ADD_FAILURE,     //加入语音广播组失败 
   	MSG_BROADCAST_CLOSE,           //语音广播中一个断开 
   	MSG_SENSOR_CAPTURE,            //探头触发的抓拍 
   	MSG_COM_DATA,                  //串口采集数据 
   	MSG_ALARM_LOST,                //报警消失                   
    MSG_ALARM_OUTPUT_NEW,          //报警输出(新)               
    MSG_ALARM_LOST_NEW,            //报警消失(新)               
    MSG_PICCHN_CLOSE,              //抓拍通道连接关闭 
}MSG_NOTIFY;


//8，错误码
typedef enum _ERR_CODE
{
	ERR_SUCCESS,					//操作成功
	ERR_FAILURE,					//操作失败
	ERR_REFUSE_REQ,				//请求被拒绝
	ERR_USER_FULL,					//登录用户已满
	ERR_PREVIEW_FULL,				//预览用户已满
	ERR_TASK_FULL,					//系统任务繁忙，待会尝试连接
	ERR_CHANNEL_NOT_EXIST,			//要打开的通道不存在或已满
	ERR_DEVICE_NAME,				//打开的设备不存在
	ERR_IS_TALKING,				//正在对讲
	ERR_QUEUE_FAILUE,				//队列出错
	ERR_USER_PASSWORD,				//用户名或密码和系统不匹配
	ERR_SHARE_SOCKET,				//socket 错误
	ERR_RELAY_NOT_OPEN,			//转发请求的服务还未打开
	ERR_RELAY_MULTI_PORT,			//转发多播端口错误
	ERR_VIEWPUSH_CHANNEL_USING,	//视频输入的通道已经被占用
	ERR_VIEWPUSH_DECODE_TYPE,		//视频输入通道的解码格式错误，0通道(4cif,2cif,cif),1通道(2cif,cif),2通道(cif),3通道(cif)
	ERR_AUTO_LINK_FAILURE,			//转发的自动连接失败
	ERR_NOT_LOGON,
	ERR_IS_SETTING,
	ERR_COMMAND_FAILURE,
	
	ERR_INVALID_PARAMETER=100,		//输入参数无效
	ERR_LOGON_FAILURE,				//登录失败
	ERR_TIME_OUT,					//操作超时
	ERR_SOCKET_ERR,				//SOCKET错误
	ERR_NOT_LINKSERVER,			//还未连接服务器
	ERR_BUFFER_EXTCEED_LIMIT,		//使用缓冲超过限制	
	ERR_LOW_PRIORITY,				//操作权限不足
	ERR_BUFFER_SMALL,				//缓冲太小
	ERR_IS_BUSY,					//系统任务正忙
	ERR_UPDATE_FILE,				//升级文件错误
	ERR_UPDATE_UNMATCH,			//升级文件和机器不匹配
	ERR_PORT_INUSE,				//端口被占用
	ERR_RELAY_DEVICE_EXIST,		//设备名已经存在
	ERR_CONNECT_REFUSED,			//连接时被拒绝
	ERR_PROT_NOT_SURPPORT,			//不支持该协议

	ERR_FILE_OPEN_ERR,            //打开文件失败
	ERR_FILE_SEEK_ERR,            //fseek失败 
	ERR_FILE_WRITE_ERR,           //fwrite失败 
	ERR_FILE_READ_ERR,            //fread失败 
	ERR_FILE_CLOSING,             //正在关闭文件 
	
}ERR_CODE;

//9，参数操作命令
typedef enum _CMD_NET
{
	//编码器命令
	CMD_GET_ALL_PARAMETER,			//得到所有编码器参数
	CMD_SET_DEFAULT_PARAMETER,	//恢复所有编码器默认参数
	CMD_SET_RESTART_DVS,			//重启编码器
	CMD_GET_SYS_CONFIG,			//获取系统设置
	CMD_SET_SYS_CONFIG,			//设置系统设置
	CMD_GET_TIME,					//获取编码器时间
	CMD_SET_TIME,					//设置编码器时间
	CMD_GET_AUDIO_CONFIG,			//获取音频设置
	CMD_SET_AUDIO_CONFIG,			//设置音频设置
	CMD_GET_VIDEO_CONFIG,			//获取视频设置
	CMD_SET_VIDEO_CONFIG,			//设置视频设置
	CMD_GET_VMOTION_CONFIG,		//获取移动侦测设置
	CMD_SET_VMOTION_CONFIG,		//设置移动侦测设置
	CMD_GET_VMASK_CONFIG,			//获取图像屏蔽设置
	CMD_SET_VMASK_CONFIG,			//设置图像屏蔽设置
	CMD_GET_VLOST_CONFIG,			//获取视频丢失设置
	CMD_SET_VLOST_CONFIG,			//设置视频丢失设置
	CMD_GET_SENSOR_ALARM,			//获取探头报警侦测设置
	CMD_SET_SENSOR_ALARM,			//设置探头报警侦测设置
	CMD_GET_USER_CONFIG,			//获取用户设置
	CMD_SET_USER_CONFIG,			//设置用户设置
	CMD_GET_NET_CONFIG,			//获取网络设置结构
	CMD_SET_NET_CONFIG,			//设置网络设置结构
	CMD_GET_COM_CONFIG,			//获取串口设置
	CMD_SET_COM_CONFIG,			//设置串口设置
	CMD_GET_YUNTAI_CONFIG,			//获取内置云台信息
	CMD_SET_YUNTAI_CONFIG,			//设置内置云台信息
	CMD_GET_VIDEO_SIGNAL_CONFIG,	//获取视频信号参数（亮度、色度、对比度、饱和度）
	CMD_SET_VIDEO_SIGNAL_CONFIG,	//设置视频信号参数（亮度、色度、对比度、饱和度）
	CMD_SET_PAN_CTRL,				//云台控制
	CMD_SET_COMM_SENDDATA,			//透明数据传输
	CMD_SET_COMM_START_GETDATA,	//开始采集透明数据
	CMD_SET_COMM_STOP_GETDATA,	//停止采集透明数据
	CMD_SET_OUTPUT_CTRL,			//继电器控制
	CMD_SET_PRINT_DEBUG,			//调试信息开关
	CMD_SET_ALARM_CLEAR,			//清除报警
	CMD_GET_ALARM_INFO,			//获取报警状态和继电器状态
	CMD_SET_TW2824,				//设置多画面芯片参数(保留)
	CMD_SET_SAVE_PARAM,			//设置保存参数
	CMD_GET_USERINFO,				//获取当前登陆的用户信息
	CMD_GET_DDNS,					//获取DDNS
	CMD_SET_DDNS,					//设置DDNS
	CMD_GET_CAPTURE_PIC,			//前端抓拍
	CMD_GET_SENSOR_CAP,			//获取触发抓拍设置
	CMD_SET_SENSOR_CAP,			//设置触发抓拍设置
	CMD_GET_EXTINFO,				//获取扩展配置
	CMD_SET_EXTINFO,				//设置扩展配置
	CMD_GET_USERDATA,				//获取用户配置
	CMD_SET_USERDATA,				//设置用户配置
	CMD_GET_NTP,					//获取NTP配置
	CMD_SET_NTP,					//设置NTP配置
	CMD_GET_UPNP,					//获取UPNP配置
	CMD_SET_UPNP,					//设置UPNP配置
	CMD_GET_MAIL,					//获取MAIL配置
	CMD_SET_MAIL,					//设置MAIL配置
	CMD_GET_ALARMNAME,				//获取报警名配置
	CMD_SET_ALARMNAME,				//设置报警名配置
	CMD_GET_WFNET,					//获取无线网络配置
	CMD_SET_WFNET,					//设置无线网络配置
	CMD_GET_SEND_DEST,				//设置视频定向发送目标机
	CMD_SET_SEND_DEST,				//设置视频定向发送目标机
	CMD_GET_AUTO_RESET,			//取得定时重新注册
	CMD_SET_AUTO_RESET,			//设置定时重新注册
	CMD_GET_REC_SCHEDULE,			//取得录像策略
	CMD_SET_REC_SCHEDULE,			//设置录像策略
	CMD_GET_DISK_INFO,				//取得磁盘信息
	CMD_SET_MANAGE,				//设置命令和操作
	CMD_GET_CMOS_REG,				//取得CMOS参数
	CMD_SET_CMOS_REG,				//设置CMOS参数
	CMD_SET_SYSTEM_CMD,			//设置执行命令
	CMD_SET_KEYFRAME_REQ,         //70.设置关键帧请求
    CMD_GET_CONFIGENCPAR,         //71.取得视频参数
    CMD_SET_CONFIGENCPAR,         //72.设置视频参�
    CMD_GET_ALL_PARAMETER_NEW,    //73.获取所有参数
    CMD_FING_LOG,                  //74.查找日志(查询方式:0－全部，1－按类型，2－按时间，3－按时间和类型 0xFF-关闭本次搜索)
    CMD_GET_LOG,                   //75.读取查找到的日志 
    CMD_GET_SUPPORT_AV_FMT,       //76.获取设备支持的编码格式、宽高及音频格式
    CMD_GET_VIDEO_CONFIG_NEW,     //77.获取视频参数－new
    CMD_SET_VIDEO_CONFIG_NEW,     //78.设置视频参数－new
    CMD_GET_VMOTION_CONFIG_NEW,   //79.获取移动报警参数－new
    CMD_SET_VMOTION_CONFIG_NEW,   //80.设置移动报警参数－new
    CMD_GET_VLOST_CONFIG_NEW,     //81.获取视频丢失报警参数－new
    CMD_SET_VLOST_CONFIG_NEW,     //82.设置视频丢失报警参数－new
    CMD_GET_SENSOR_ALARM_NEW,     //83.获取探头报警参数－new
    CMD_SET_SENSOR_ALARM_NEW,     //84.设置探头报警参数－new
    CMD_GET_NET_ALARM_CONFIG,     //85.获取网络故障报警参数
    CMD_SET_NET_ALARM_CONFIG,     //86.设置网络故障报警参数
    CMD_GET_RECORD_CONFIG,        //87.获取定时录像参数
    CMD_SET_RECORD_CONFIG,        //88.定时录像参数
    CMD_GET_SHOOT_CONFIG,         //89.获取定时抓拍参数
    CMD_SET_SHOOT_CONFIG,         //90.设置定时抓拍参数
    CMD_GET_FTP_CONFIG,           //91.获取FTP参数
    CMD_SET_FTP_CONFIG,           //92.设置FTP参数
    CMD_GET_RF_ALARM_CONFIG,      //93.获取无线报警参数
    CMD_SET_RF_ALARM_CONFIG,      //94.设置无线报警参数
    CMD_GET_EXT_DATA_CONFIG,      //95.获取其它扩展参数(如平台设置其它参数)
    CMD_SET_EXT_DATA_CONFIG,      //96.设置其它扩展参数(如平台设置其它参数)
    CMD_GET_FORMAT_PROCESS,       //97.获取硬盘格式化进度
    CMD_GET_PING_CONFIG,          //98.PING 设置获取
    CMD_SET_PING_CONFIG,          //99.PING 设置设置
	//解码器命令
	DDCMD_GET_ALL_PARAMETER = 100,	//获取解码器所有设置
	DDCMD_GET_TIME,				//获取系统时间
	DDCMD_SET_TIME,				//设置系统时间
	DDCMD_GET_SYS_CONFIG,			//获取系统配置
	DDCMD_SET_SYS_CONFIG,			//设置系统配置
	DDCMD_GET_NET_CONFIG,			//获取网络配置
	DDCMD_SET_NET_CONFIG,			//设置网络配置
	DDCMD_GET_COM_CONFIG,			//获取串口配置
	DDCMD_SET_COM_CONFIG,			//设置串口配置
	DDCMD_GET_VIDEO_CONFIG,		//获取视频配置
	DDCMD_SET_VIDEO_CONFIG,		//设置视频配置
	DDCMD_GET_ALARM_OPT,			//获取报警选项
	DDCMD_SET_ALARM_OPT,			//设置报警选项
	DDCMD_GET_USER_INFO,			//获取用户设置信息
	DDCMD_SET_USER_INFO,			//设置用户设置信息
	DDCMD_GET_ALARM_RECORD,		//获取报警记录信息
	DDCMD_GET_ADRRESS_BOOK,		//获取地址薄配置
	DDCMD_SET_ADRRESS_BOOK,		//设置地址薄配置
	DDCMD_SET_COMM,				//设置发送串口数据
	DDCMD_SET_CMD,					//设置透明的命令
	DDCMD_GET_YUNTAI_INFO,			//获取云台信息
	DDCMD_GET_YUNTAI_CONFIG,		//获取云台配置
	DDCMD_SET_YUNTAI_CONFIG,		//设置云台配置
	DDCMD_GET_ONELINK_ADDR,		//获取解码器单路连接的信息
	DDCMD_SET_ONELINK_ADDR,		//设置解码器单路连接的信息
	DDCMD_GET_CYCLELINK_ADDR,		//获取解码器循环连接的信息
	DDCMD_SET_CYCLELINK_ADDR,		//设置解码器循环连接的信息
	DDCMD_GET_EXTINFO,				//获取扩展配置
	DDCMD_SET_EXTINFO,				//设置扩展配置
	DDCMD_GET_NTP,					//获取NTP配置
	DDCMD_SET_NTP,					//设置NTP配置
	DDCMD_GET_UPNP,				//获取UPNP配置
	DDCMD_SET_UPNP,				//设置UPNP配置
	DDCMD_GET_MAIL,				//获取MAIL配置
	DDCMD_SET_MAIL,				//设置MAIL配置
	DDCMD_GET_ALARMNAME,			//获取报警名配置
	DDCMD_SET_ALARMNAME,			//设置报警名配置
	DDCMD_GET_WFNET,				//获取无线网络配置
	DDCMD_SET_WFNET,				//设置无线网络配置
	DDCMD_GET_SEND_DEST,			//设置视频定向发送目标机
	DDCMD_SET_SEND_DEST,			//设置视频定向发送目标机

	CMD_GET_VPN_CONFIG = 200,		//200.获取VPN设置参数
	CMD_SET_VPN_CONFIG = 201,		//201.设置VPN参数
	CMD_GET_3G_CONFIG  = 202,		//获取3G参数
	CMD_SET_3G_CONFIG  = 203,      //设置3G参数
	CMD_GET_GPS_CONFIG = 204,
	CMD_SET_GPS_CONFIG = 205,
	CMD_GET_3G_DIALCTRL= 206,
	CMD_SET_3G_DIALCTRL= 207,	
	
	//参数扩展===================
	CMD_GET_IR_CONFIG = 400,		//获取红外信息配置
	CMD_SET_IR_CONFIG,				//设置红外信息配置
	CMD_GET_ALL_CONFIGPARAM,		//获取所有参数
	CMD_SET_FORMATTING, 		//格式化

	
	CMD_SET_OSD_MSG = 500,
	CMD_CLEAR_OSD_MSG = 501,
	CMD_SET_OSD_START = 502,
	CMD_SET_OSD_CLOSE = 503,
	CMD_CLEAR_OSD_PTZMSG = 504,
	CMD_SET_OSD_PTZMSG = 505,
	CMD_SET_OSD_PTZORG  = 506,
	CMD_GET_OSD_PTZORG  = 507,

	CMD_GET_VI_SENSOR=1000,
	CMD_SET_VI_SENSOR,
	CMD_GET_VI_SCENE,
	CMD_SET_VI_SCENE,
	CMD_GET_VI_CFG,
	CMD_SET_VI_CFG,
}CMD_NET;

typedef enum _RELAY_CHECK_RET
{
	RCRET_SUCCESS = 0,
	RCRET_FAILURE = -1,
	RCRET_AUTO_LINK = 0x0101,	
}RELAY_CHECK_RET;



/*********************************  二、回调函数  ******************************/

//1，实时音视频数据流回调
typedef int  ( *ChannelStreamCallback)(HANDLE hOpenChannel,void *pStreamData,UINT dwClientID,void *pContext,ENCODE_VIDEO_TYPE encodeVideoType,ULONG frameno);

//2，实时对讲音频数据流回调
typedef int  ( *TalkStreamCallback)(void *pTalkData,UINT nTalkDataLen,void *pContext);

//3，消息通知，通知调用
typedef int  ( *MsgNotifyCallback)(UINT dwMsgID,UINT ip,UINT port,HANDLE hNotify,void *pPar);

//4，检查用户，客户端登陆时检查
typedef int  (*CheckUserPsw)(const CHAR *pUserName,const CHAR *pPsw);

//5，客户端传递的消息
typedef int  (*ServerMsgReceive)(ULONG ip,ULONG port,CHAR *pMsgHead);

//6，升级
typedef int	 (*ServerUpdateFile)(int nOperation,int hsock,ULONG ip,ULONG port,int nUpdateType,CHAR *pFileName,CHAR *pFileData,int nFileLen);


//7，转发服务的用户检测回调
typedef int	 (*RelayCheckUserCallback)(RELAY_TYPE relayType,UINT dwClientIP,USHORT wClientPort,CHAR *pszUserName,CHAR *pszPassword,CHAR *pszDeviceName,UINT dwRequstChannel,INT bOnline,CHAR *pDeviceIP,UINT *pdwDevicePort,CHAR *pContext);

//8，中心服务器模式用户检测回调
typedef int	 (*CenterCheckUserCallback)(INT bOnLine,DVS_MACHINE_TYPE machineType,UINT dwDeviceID,UINT dwChannelNum,UINT ip,USHORT port,CHAR *pszDeviceName,CHAR *pszUserName,CHAR *pszPassword,LPVOID pNetPar);

//9，搜索录像NVS回调
typedef void (*SearchRecNVSCallback)(CHAR *szNvsBuffer,int nBufferLen);

//10，搜索录像文件
//typedef void (WINAPI *SearchRecFileCallback)(void *pRecFile);
typedef void  (*SearchRecFileCallback)(UINT dwClientID,void *pRecFile);

//11，库消息回掉函数
typedef int	 (*MessageNotifyCallback)(UINT wParam, UINT lParam);



/******************************  三、接口结构类型定义  ***************************/
#ifndef AV_INFO_DEFINE
#define AV_INFO_DEFINE

//1，视频音频参数
typedef struct _AV_INFO
{
    //视频参数
    UINT			nVideoEncodeType;		//视频编码格式
    UINT			nVideoHeight;			//视频图像高
    UINT			nVideoWidth;			//视频图像宽
    //音频参数
    UINT			nAudioEncodeType;		//音频编码格式
    UINT			nAudioChannels;			//通道数
    UINT			nAudioBits;				//位数
    UINT			nAudioSamples;			//采样率
}AV_INFO,*PAV_INFO;

#endif //AV_INFO_DEFINE


//2，音视频数据帧头
typedef struct _FRAME_HEAD
{
	USHORT	zeroFlag;				// 0
	UCHAR   oneFlag;				// 1
	UCHAR	streamFlag;				// 数据帧标志 FRAME_FLAG_VP，FRAME_FLAG_VI，FRAME_FLAG_A
	
	ULONG	nByteNum;				//数据帧大小
	ULONG	nTimestamp;				//时间戳
}FRAME_HEAD;

//3,报警输出

typedef struct _ALARM_STATUS_OUTPUT_NEW
{
	unsigned char year;

	unsigned char month;

	unsigned char day;

	unsigned char week;

	unsigned char hour;

	unsigned char minute;

	unsigned char second;

	unsigned char millsecond; 

	unsigned int SensorAlarm;
	unsigned int MotionAlarm;
	unsigned int ViLoseAlarm;
	unsigned int RFSensorAlarm;
	unsigned int NetAlarm;

	unsigned int SensorAlarmRec[MAX_SENSOR_NUM];
	unsigned int MotionAlarmRec[MAX_VIDEO_NUM];
	unsigned int ViLoseAlarmRec[MAX_VIDEO_NUM];
	unsigned int RFSensorAlarmRec[MAX_RF_SENSOR_NUM];
	unsigned int NetAlarmRec;

	unsigned int OutputStatus;

	unsigned int reserved[19];
}ALARM_STATUS_OUTPUT_NEW;


//4，报警通知信息结构

typedef struct _ALARM_MSG_NOTIFY_NEW
{
	HANDLE hLogonServer;

	UINT dwClientID;

	UINT dwServerIP;

	UINT dwServerPort;

	ALARM_STATUS_OUTPUT_NEW alarmStatus;
}ALARM_MSG_NOTIFY_NEW;



//5，打开视频通道参数

typedef struct _OPEN_CHANNEL_INFO_EX
{
    ULONG                         dwClientID;                       //回调参数	(对应回调函数里的dwClientID)
    UINT                          nOpenChannel:8;                   //通道号（0 ～ 3）
    UINT                          nSubChannel:8;                    //0: 打开主码流      1: 打开从码流
    UINT                          res:16;                            //备用
    NET_PROTOCOL_TYPE             protocolType;                     //连接方式（TCP、UDP、多播）  
    ChannelStreamCallback         funcStreamCallback;              //音视频流数据回调函数 
    void                          *pCallbackContext;               //回调参数2(对应回调函数里的pContext) 
}OPEN_CHANNEL_INFO_EX;

//6，打开视频通道参数
typedef struct _OPEN_VIEWPUSH_INFO
{
	UINT					dwClientID;
	UINT					nViewPushChannel;
	NET_PROTOCOL_TYPE		protocolType;
	AV_INFO				avInformation;
	UINT					nMulticastAddr;
	UINT					nMulticastPort;
	UINT					nScreenCount;
	UINT					nScreenIndex;
}OPEN_VIEWPUSH_INFO;

//7，打开的服务器信息
typedef struct _SERVER_INFO
{
	HANDLE					hServer;
	CHAR					szServerIP[MAX_IP_NAME_LEN+1];
	UINT					nServerPort;
	CHAR					szDeviceName[DVS_NAME_LEN+1];
	UINT					nDeviceID;
	CHAR					szUserName[USER_NAME_LEN+1];
	CHAR					szUserPassword[USER_PASSWD_LEN+1];
	UINT					dwClientID;
	CONNECT_STATUS			logonStatus;
	UINT					nVersion;
	UINT					nLogonID;
	UINT					nPriority;
	UINT					nServerChannelNum;
	UINT					nLanguageNo;
	DVS_MACHINE_TYPE		nMachineType;
	INT						bPalStandard;
	UINT					nMulticastAddr;
	UINT					nMulticastPort;
	AV_INFO					avInformation[MAX_VIDEO_NUM];
}SERVER_INFO;

//8，打开的通道信息
typedef struct _CHANNEL_INFO
{
	HANDLE					hOpenChannel;
	CHAR					szServerIP[MAX_IP_NAME_LEN+1];
	UINT					nServerPort;
	CHAR					szDeviceName[DVS_NAME_LEN+1];
	CHAR					szUserName[USER_NAME_LEN+1];
	CHAR					szUserPassword[USER_PASSWD_LEN+1];
	UINT					dwClientID;
	CONNECT_STATUS			openStatus;
	UINT					nVersion;
	UINT					nOpenID;
	UINT					nPriority;
	UINT					nOpenChannelNo;
	UINT					nMulticastAddr;
	UINT					nMulticastPort;
	AV_INFO				avInformation;
	ENCODE_VIDEO_TYPE		encodeVideoType;
	NET_PROTOCOL_TYPE		protocolType;
	ChannelStreamCallback	funcStreamCallback;
	void					*pCallbackContext;
	UINT					dwDeviceID;	//V4.0 add
}CHANNEL_INFO;

//9，打开的解码器输入通道信息
typedef struct _VIEWPUSH_INFO
{
	HANDLE				hOpenChannel;
	CHAR				szServerIP[MAX_IP_NAME_LEN+1];
	UINT				nServerPort;
	CHAR				szDeviceName[DVS_NAME_LEN+1];
	CHAR				szUserName[USER_NAME_LEN+1];
	CHAR				szUserPassword[USER_PASSWD_LEN+1];
	UINT				dwClientID;
	CONNECT_STATUS		openStatus;
	UINT				nVersion;
	UINT				nOpenID;
	UINT				nPriority;
	UINT				nOpenChannelNo;
	UINT				nMulticastAddr;
	UINT				nMulticastPort;
	AV_INFO			avInformation;
	ENCODE_VIDEO_TYPE	encodeVideoType;
	NET_PROTOCOL_TYPE	protocolType;
	DVS_MACHINE_TYPE	nMachineType;
	UINT				dwChannelNum;	//解码器最大路数
}VIEWPUSH_INFO;

//10，对讲的信息
typedef struct _SS_TALK_INFO 
{
	HANDLE				hServer;
	CHAR				szServerIP[MAX_IP_NAME_LEN+1];
	UINT				nServerPort;
	CHAR				szDeviceName[DVS_NAME_LEN+1];
	CHAR				szUserName[USER_NAME_LEN+1];
	CHAR				szUserPassword[USER_PASSWD_LEN+1];
	ULONG		version;	
	ULONG		nMachineType;
	CONNECT_STATUS		logonStatus;
	//audio parameter
	UINT				nAudioEncodeType;
    UINT				nAudioChannels;
    UINT				nAudioBits;
    UINT				nAudioSamples;
}TALKING_INFO;

//11，语音广播的用户信息
typedef struct _BROADCAST_USER
{
	HANDLE	hBroadcastUser;
	CHAR	szServerIP[MAX_IP_NAME_LEN+1];
	UINT	port;
	CHAR	szDeviceName[DVS_NAME_LEN+1];	
	CHAR	szUserName[USER_NAME_LEN+1];
	CHAR	szUserPassword[USER_PASSWD_LEN+1];
	INT	bConnect;
	//SOCKET	hSock;
	//PVOID	pPar;
	//add v4.2
	UINT				machineType;
	ENCODE_VIDEO_TYPE	audioType;
}BROADCAST_USER;

//12，转发视频服务器
typedef struct _RELAY_NVS
{
	RELAY_TYPE			relayType;
	CHAR				szServerIP[MAX_IP_NAME_LEN+1];
	USHORT				wServerPort;
	CHAR				szDeviceName[DVS_NAME_LEN+1];
	UINT				dwChannelNo;
	UINT				dwCount;
}RELAY_NVS;	

//13，百分比消息通知
typedef struct _PERCENT_NOTIFY
{
	HANDLE				hLogon;
	UINT				dwClientID;
	UINT				dwPercent;
}PERCENT_NOTIFY;

//14，视频文件参数
typedef struct _FILE_INFO
{
	CHAR                szFileName[MAX_PATH];
	CHAR				szServerIP[MAX_IP_NAME_LEN+1];
	USHORT				wServerPort;
	CHAR				szUserName[USER_NAME_LEN+1];
	CHAR				szUserPassword[USER_PASSWD_LEN+1];
	INT                bRelay     ; // 此文件是否通过转发
}FILE_INFO;

//15，打开视频文件参数
typedef struct _OPEN_FILE_INFO
{
	UINT				dwClientID  ;
	UINT				nOpenChannel;
	NET_PROTOCOL_TYPE	protocolType;
	CHAR				szDeviceName[DVS_NAME_LEN+1];
	FILE_INFO        hhFile      ;       
	CHAR                szOpenMode[5];
	UINT				dwSocketTimeOut;
	
    // 输出
	UINT				dwFileSize;         // 文件大小
	UINT				dwStartTime;        // 播放开始时间(毫秒)
	UINT				dwEndTime;          // 播放结束时间(毫秒)
	
	UINT				nVideoEncodeType;	//视频编码格式
	UINT				nAudioEncodeType;	//音频编码格式	
}OPEN_FILE_INFO;

//16，启动搜索符合条件的NVS
typedef struct _SEARCH_REC_NVS
{
	UINT				dwClientID  ;
	// 存储录像文件的条件
	CHAR                Date[11];			// 条件1 录像日期 yyyy-mm-dd
    UCHAR                recType ;			// 条件2 录像类型: 0-所有，1-报警，2-手动，3-定时
	
	//SearchRecNVSCallback	funcSearchRecNvsCallback;	
}SEARCH_REC_NVS;

// 17，启动搜索符合条件的录像文件
typedef struct _SEARCH_REC_FILE
{
	UINT				dwClientID  ;

	// 存储录像文件的条件
    CHAR                szDir[MAX_PATH]; 	// 条件1: " Datae\\Ip-NVS\\Camera\\"
	CHAR				szTime1[6];      	// 条件2 时间段1 hh:mm
	CHAR				szTime2[6];      	// 条件2 时间段2 hh:mm
    UCHAR                recType ;	    	 // 条件3 录像类型: 0-所有，1-报警，2-手动，3-定时
	
	SearchRecFileCallback	funcSearchRecFileCallback;
}SEARCH_REC_FILE;

//18，转发查询
typedef struct _RELAY_QUERY_INFO
{
	UINT		dwSize;
	UINT		dwServerLogonNum;
	UINT		dwServerPreviewNum;
	UINT		dwServerTalkNum;
	UINT		dwServerBrdNum;
	UINT		dwClientLogonNum;
	UINT		dwClientPreviewNum;
	UINT		dwClientTalkNum;
	UINT		dwClientBrdNum;
	CHAR		reserve[16];
}RELAY_QUERY_INFO;



typedef struct _SEARCH_SER_INFO
{ 
	char				userName[USER_NAME_LEN+1];
	char				userPassword[USER_PASSWD_LEN+1];
	DVS_MACHINE_TYPE	nDeviceType;
	char				szDeviceName[64];
	unsigned long		ipLocal;
	unsigned char		macAddr[6];
	unsigned short		wPortWeb;
	unsigned short		wPortListen;
	unsigned long		ipSubMask;
	unsigned long		ipGateway;
	unsigned long		ipMultiAddr;
	unsigned long		ipDnsAddr;
	unsigned short		wMultiPort;
	int					nChannelNum;
}SEARCH_SER_INFO;

//========================================================================
//				四、 音视频网络帧头
//========================================================================

//1，数据帧标志
#define FRAME_FLAG_VP		0x0b	//视频的P帧
#define FRAME_FLAG_VI		0x0e	//视频的I帧
#define FRAME_FLAG_A		0x0d	//音频帧

//扩展帧头
#define	EXT_HEAD_FLAG	0x06070809
#define	EXT_TAIL_FLAG	0x0a0b0c0d

//音频编码算法
typedef enum  _PT_AENC_TYPE_E
{
	PT_AENC_NONE   = 0x0,
	PT_AENC_G726   = 0x01,
	PT_AENC_G722   = 0x02,
	PT_AENC_G711A  = 0x03,
	PT_AENC_ADPCM  = 0x04,
	PT_AENC_MP3    = 0x05,
	PT_AENC_PCM    = 0x06,
	PT_AENC_G711U  = 0x07,
	PT_AENC_AACLC  = 0x08,
	PT_AENC_AMRNB  = 0x09,
}PT_AENC_TYPE_E;


//视频编码算法
typedef enum  _PT_VENC_TYPE_E
{
	PT_VENC_NONE   = 0x0,
	PT_VENC_H264   = 0x01,
	PT_VENC_MPEG4  = 0x02,
	PT_VENC_MJPEG  = 0x03,
	PT_VENC_JPEG   = 0x04,
}PT_VENC_TYPE_E;



//视频参数
typedef struct _EXT_FRAME_VIDEO
{
	unsigned short	nVideoEncodeType;	//视频编码算法
	unsigned short	nVideoWidth;		//视频图像宽
	unsigned short	nVideoHeight;		//视频图像高
	unsigned char   nPal;               //制式
	unsigned char   bTwoFeild;			//是否是两场编码(如果是两场编码，PC端需要做deinterlace)
	unsigned char   nFrameRate;			//帧率
	unsigned char   szReserve[7];		//

} EXT_FRAME_VIDEO;

//音频参数
typedef struct _EXT_FRAME_AUDIO
{
	unsigned short	nAudioEncodeType;	//音频编码算法
	unsigned short	nAudioChannels;		//通道数
	unsigned short	nAudioBits;			//位数
	unsigned char   szReserve[2];
	unsigned long	nAudioSamples;		//采样率 	
	unsigned long	nAudioBitrate;		//音频编码码率
} EXT_FRAME_AUDIO;

typedef union _EXT_FRAME_TYPE
{
	EXT_FRAME_VIDEO	szFrameVideo;
	EXT_FRAME_AUDIO	szFrameAudio;
} EXT_FRAME_TYPE;

typedef struct _EXT_FRAME_HEAD
{
    unsigned long	nStartFlag;			//扩展帧头起始标识
    unsigned short	nVer;				//版本
    unsigned short	nLength;			//扩展帧头长度
	EXT_FRAME_TYPE	szFrameInfo;		
	unsigned long   nTimestamp;			//以毫秒为单位的时间戳
	unsigned long	nEndFlag;			//扩展帧头起始标识
}EXT_FRAME_HEAD;




typedef INT  (*StreamWriteCheck)(int nOperation,const CHAR *pUserName,const CHAR *pPsw,ULONG ip,ULONG port,OPEN_VIEWPUSH_INFO viewPushInfo,HANDLE hOpen);
typedef INT (*CallbackServerFind)(SEARCH_SER_INFO *pSearchInfo);

/********************************  五、函数接口定义  *****************************/

//启动服务
ERR_CODE		NET_Startup(USHORT nBasePort,MsgNotifyCallback msgCallback,CheckUserPsw checkUserPswCallback,ServerUpdateFile updateCallback,ServerMsgReceive msgCmdCallback,StreamWriteCheck streamWriteCheckCallback,ChannelStreamCallback funcChannelCallback);
//关闭服务
ERR_CODE		NET_Cleanup();


//登录服务器
ERR_CODE		NET_LogonServer(IN  CHAR *pServerIP,IN  UINT nServerPort,IN  CHAR *pDeviceName,IN	 CHAR *pUserName,IN	 CHAR *pUserPassword,IN UINT dwClientID,OUT  HANDLE *hLogonServer);
//注销服务器
ERR_CODE		NET_LogoffServer(IN  HANDLE hServer);
//读取登录服务器信息
ERR_CODE		NET_ReadServerInfo(IN  HANDLE hServer,OUT  SERVER_INFO *serverInfo);

//程序升级
ERR_CODE		NET_Update(IN HANDLE hServer,IN UPDATE_TYPE nUpdateType,IN CHAR *pFilePathName);


//读取登录服务器配置信息
ERR_CODE		NET_GetServerConfig(IN  HANDLE hServer,IN  CMD_NET nConfigCommand,OUT  CHAR *pConfigBuf,IN OUT  UINT *nConfigBufSize,IN  OUT  UINT *dwAppend);
//设置登录服务器配置信息
ERR_CODE		NET_SetServerConfig(IN  HANDLE hServer,IN  CMD_NET nConfigCommand,IN   CHAR *pConfigBuf,IN  UINT nConfigBufSize,IN  UINT dwAppend);


//打开视频通道
ERR_CODE		NET_OpenChannel(IN  CHAR *pServerIP,IN  UINT nServerPort,IN  CHAR *pDeviceName,IN  CHAR *pUserName,IN  CHAR *pUserPassword,IN  OPEN_CHANNEL_INFO_EX *pOpenInfo,OUT  HANDLE *hOpenChannel);
//关闭视频通道
ERR_CODE		NET_CloseChannel(IN  HANDLE hOpenChannel);

//读取打开视频通道信息
ERR_CODE		NET_ReadChannelInfo(IN  HANDLE hOpenChannel,OUT  CHANNEL_INFO *channelInfo);


//请求打开对讲
//ERR_CODE		NET_TalkRequsest(IN  CHAR *pServerIP,IN  UINT nServerPort,IN  CHAR *pDeviceName,IN	 CHAR *pUserName,IN	 CHAR *pUserPassword,IN TalkStreamCallback funcTalkCallback,IN void *pContext);
ERR_CODE		NET_TalkRequsest(IN  char *pServerIP, IN  UINT nServerPort,IN  char *pDeviceName,IN	 char *pUserName,IN	 char *pUserPassword,IN TalkStreamCallback funcTalkCallback,IN void *pContext, OUT  TALKHANDLE *hTalkback);

//结束对讲
//ERR_CODE		NET_TalkStop();
ERR_CODE		NET_TalkStop(IN  TALKHANDLE hTalkback);

//读取打开对讲信息
//ERR_CODE		NET_TalkReadInfo(TALKING_INFO *talkInfo);
//发送对讲数据
//ERR_CODE		NET_TalkSend(IN CHAR *pTalkData,IN UINT nDataLen);
ERR_CODE		NET_TalkSend(IN  TALKHANDLE hTalkback, IN char *pTalkData,IN UINT nDataLen);


//搜索网上设备
ERR_CODE		NET_SearchAllServer(UINT nTimeWait,	 CallbackServerFind  funcServerFind);
//设置视频服务器网络配置
ERR_CODE		NET_ConfigServer(UCHAR macAddr[6],CHAR *pUserName,CHAR *pUserPassword,
													   CHAR *pIP,CHAR *pDeviceName,CHAR *pSubMask,CHAR *pGateway,CHAR *pMultiAddr,
													   CHAR *pDnsAddr,USHORT wPortWeb,USHORT wPortListen,USHORT wPortMulti);

void NET_UpdatePercentNotify(int hsock,ULONG nPercent);

ERR_CODE        NET_SetNetApiSupportVersion(int nVersion);


#endif


