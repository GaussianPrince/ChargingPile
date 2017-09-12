#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
UInt8	AtModeEntry[] = "+++";
UInt8	NetMode[] = "at+netmode=0\r\n";
UInt8	NetDHCPC[] = "at+dhcpc=1\r\n";
UInt8	NetWIFIConf[96] = "at+wifi_conf=";
UInt8	NetRemotePro[] = "at+remotepro=tcp\r\n";
UInt8	NetWorkMode[] = "at+mode=client\r\n";
UInt8	NetRemoteIP[32] = "at+remoteip=";
UInt8	NetRemotePort[32] = "at+remoteport=";
UInt8	NetTCPTimeOut[] = "at+timeout=255\r\n";
UInt8	NetUart[] = "at+uart=115200,8,n,1\r\n";
UInt8   NetUartPackLen[] = "at+uartpacklen=256\r\n";
UInt8	NetUartTCPTimeOut[] = "at+uartpacktimeout=255\r\n";
UInt8	NetConfigCommit[] = "at+net_commit=1\r\n";
UInt8	NetReconn[] = "at+reconn=1\r\n";
UInt8   NetAssciiBuff[4];
UInt8   NetAssciiBuffIndex;
UInt8   NetIPIndex;
WIFIATHOperat WIFIATHOperatBuff;
#pragma DATA_SEG DEFAULT
DataConvert IPAddr;
static UInt8 Inet(void)
{
	UInt8 n;
	UInt8 i;
	IPAddr.UInt8_Data[0] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[7];
	IPAddr.UInt8_Data[1] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[7];
	IPAddr.UInt8_Data[2] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[7];
	IPAddr.UInt8_Data[3] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[7];
	NetIPIndex = 11;
	for (n = 0; n < 4; n++)
	{
		NetAssciiBuffIndex = 0;
		while (IPAddr.UInt8_Data[n] != 0)
		{
			NetAssciiBuff[NetAssciiBuffIndex++] = IPAddr.UInt8_Data[n] % 10+0x30;
			IPAddr.UInt8_Data[n] /= 10;
		}
		for (i = NetAssciiBuffIndex-1; i>0; i--)
		{
			NetRemoteIP[NetIPIndex++] = NetAssciiBuff[i];
		}
		NetRemoteIP[NetIPIndex++] = NetAssciiBuff[0];
		if (n != 3)
			NetRemoteIP[NetIPIndex++] = '.';
		else
		{
			NetRemoteIP[NetIPIndex++] = '\r';
			NetRemoteIP[NetIPIndex++] = '\n';
		}
	}
	return NetIPIndex;
}
static UInt8 Hton(void)
{
	UInt8 i;
	IPAddr.UInt8_Data[0] = HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[6];
	IPAddr.UInt8_Data[0] = HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[7];
	NetIPIndex = 13;
	NetAssciiBuffIndex = 0;
	while (IPAddr.UInt16_Data[0] != 0)
	{
		NetAssciiBuff[NetAssciiBuffIndex++] = IPAddr.UInt16_Data[0] % 10 + 0x30;
		IPAddr.UInt16_Data[0] /= 10;
	}
	for (i = NetAssciiBuffIndex - 1; i >0; i--)
	{
		NetRemotePort[NetIPIndex++] = NetAssciiBuff[i];
	}
	NetRemotePort[NetIPIndex++] = NetAssciiBuff[0];
	NetRemotePort[NetIPIndex++] = '\r';
	NetRemotePort[NetIPIndex++] = '\n';
	return NetIPIndex;
}
static UInt8 WIFIFormat(void)
{
	UInt8 n;
	NetIPIndex = 12;
	for (n = 6; n < (HMITxCmdBuff.Compts.ConfigPage.SSIDRec[2] + 3); n++)
	{
		NetWIFIConf[NetIPIndex++] = HMITxCmdBuff.Compts.ConfigPage.SSIDRec[n];
	}
	NetWIFIConf[NetIPIndex++] = ',';
	NetWIFIConf[NetIPIndex++] = 'w';
	NetWIFIConf[NetIPIndex++] = 'p';
	NetWIFIConf[NetIPIndex++] = 'a';
	NetWIFIConf[NetIPIndex++] = '2';
	NetWIFIConf[NetIPIndex++] = '_';
	NetWIFIConf[NetIPIndex++] = 'a';
	NetWIFIConf[NetIPIndex++] = 'e';
	NetWIFIConf[NetIPIndex++] = 's';
	NetWIFIConf[NetIPIndex++] = ',';
	for (n = 6; n < (HMITxCmdBuff.Compts.ConfigPage.PwdRec[2] + 3); n++)
	{
		NetWIFIConf[NetIPIndex++] = HMITxCmdBuff.Compts.ConfigPage.PwdRec[n];
	}
	NetWIFIConf[NetIPIndex++] = '\r';
	NetWIFIConf[NetIPIndex++] = '\n';
	return NetIPIndex;
}
void WIFIATHConfig(void)
{
	UInt8 n;
	if (WIFIATHOperatBuff.Compts.ConfigEntryFlag == 0)
	{
		SCI4SendN(AtModeEntry, 3);
	}
	else
	{
		switch (WIFIATHOperatBuff.Compts.WIFIATHState)
		{
		case 0:
			NetMode[11] = HMIOperationBuff.Compts.NetConfigType;
			SCI4SendN(NetMode, sizeof(NetMode));
			break;
		case 1:
			n = WIFIFormat();
			SCI4SendN(NetWIFIConf, n);
			break;
		case 2:
			SCI4SendN(NetDHCPC, sizeof(NetDHCPC));
			break;
		case 3:
			n = Inet();
			SCI4SendN(NetRemoteIP, n);
			break;
		case 4:
			n = Hton();
			SCI4SendN(NetRemotePort, n);
			break;
		case 5:
			SCI4SendN(NetRemotePro, sizeof(NetRemotePro));
			break;
		case 6:
			SCI4SendN(NetTCPTimeOut, sizeof(NetTCPTimeOut));
			break;
		case 7:
			SCI4SendN(NetMode, sizeof(NetMode));
			break;
		case 8:
			SCI4SendN(NetUart, sizeof(NetUart));
			break;
		case 9:
			SCI4SendN(NetUartPackLen, sizeof(NetUartPackLen));
			break;
		case 10:
			SCI4SendN(NetUartPackLen, sizeof(NetUartPackLen));
			break;
		case 11:
			SCI4SendN(NetUartTCPTimeOut, sizeof(NetUartTCPTimeOut));
			break;
		case 12:
			SCI4SendN(NetConfigCommit, sizeof(NetConfigCommit));
			break;
		case 13:
			SCI4SendN(NetReconn, sizeof(NetReconn));
			break;
		default:
			break;
		}
	}
}