================================================================================
                                使用说明
================================================================================
版本历史 
日期        版本    负责人             MDK            描述
2020-10-15  2.00    Gmz              5.30.0.0      first version
================================================================================
InformationBuffer 存储空间分布，128个字节，0xFE~
InformationBuffer[0]	
InformationBuffer[1]
InformationBuffer[2]
InformationBuffer[3]
InformationBuffer[4]	电台编码-RadioAddress
InformationBuffer[5]	
InformationBuffer[6]
InformationBuffer[7]
InformationBuffer[8]
InformationBuffer[9]
InformationBuffer[10]	PlaneChannelNum
InformationBuffer[11]	PlaneChannelDate
InformationBuffer[12]	PlaneChannelTime
InformationBuffer[13]	PlaneChannelMinute高位
InformationBuffer[14]	PlaneChannelMinute低位
InformationBuffer[15]	表示是否修改过电台地址，0x01：修改过，0xFF：未修改
InformationBuffer[16]
InformationBuffer[17]
================================================================================
================================================================================
版本记录
================================================================================
版本号:V2.00
修改时间:2020-10-15
修改人:宫梦真
硬件版本:NEM-T-LORA(L130+6500S)_V2.01哈一
硬件版本:NEM-U-LORA(L130+6500S)_V2.01哈二
修改内容: 
(1)使用《hc32l13x_ddl_Rev1.8.0 Lite》库；
(2)低功耗串口（Lpuart0）采用RCL时钟，确保在深度休眠模式下仍运行；
(3)频率偏移计算公式由FrequencyDeviation = ((RadioStationAddress&0x03)*2%99)+ ((RadioStationAddress&0x03)/99)%99
更改为：FrequencyDeviation = ((RadioStationAddress&0xFF)*2%99)+ ((RadioStationAddress&0xFF)/99)%99
此频率偏移公式是水表和热表使用的；
(4)RadioStationAddress为低位在前；
(5)B0上传指令修改，直接上传buffersend数据；
(6)L130收到电台校时指令，发送给表端；
(7)CJ188协议指令增加CS校验；
(8)90B0指令更改为广播抄表指令；
(9)PlaneChannelMinute为两字节，存储位置改为InformationBuffer[13]和InformationBuffer[14]，后面的顺移一位；
(10)版本号改为两字节；
================================================================================
版本号:V2.01
修改时间:2020-11-23
修改人:宫梦真
硬件版本:NEM-T-LORA(L130+6500S)_V2.01哈一
硬件版本:NEM-U-LORA(L130+6500S)_V2.01哈二
修改内容: 
(1)向表端发送指令时，先填充0xFF，若未收到表端指令，返·回数据后面10字节为0xFF，便于LTN识别；
(2)生产信道上传数据频率不偏移；
(3)根据表端发送过来的指令5003判断是否进入工厂模式，删除9035指令，若130秒内未收到退出指令，自动退出并初始化到仓储信道；
(4)B0和CA广播指令取消校时补偿，LD要求，2020/12/01；
(5)默认表地址为999,999,999，方便电路板测试，工程部要求，2020/12/04；
================================================================================
版本号:V2.02
修改时间:2020-12-17
修改人:宫梦真
硬件版本:NEM-T-LORA(L130+6500S)_V2.01哈一
硬件版本:NEM-U-LORA(L130+6500S)_V2.01哈二
修改内容: 
(1)接受广播简码指令计算上传时间点算法改进，CAD_Minute_Num为最近一次的CAD心跳的分钟数；
if((SecondNum+LoraSetting[ChannelNumber].DeviceSendDelayS+TimeDeviation)>59)
{
	NextSendMinuteTime = (CAD_Minute_Num + (SecondNum+LoraSetting[ChannelNumber].DeviceSendDelayS+TimeDeviation)/60)%60;
	NextSendSecondTime = (SecondNum+LoraSetting[ChannelNumber].DeviceSendDelayS+TimeDeviation)%60;
}
else
{
	NextSendMinuteTime = CAD_Minute_Num;
	NextSendSecondTime = SecondNum + LoraSetting[ChannelNumber].DeviceSendDelayS + TimeDeviation;
}
(2)修改频率偏移公式：FrequencyDeviation  = ((RadioStationAddress>>8)*2%99)+ ((RadioStationAddress>>8)/99)%99;
================================================================================
版本号:V2.03
修改时间:2020-12-30
修改人:宫梦真
硬件版本:NEM-T-LORA(L130+6500S)_V2.01哈一
硬件版本:NEM-U-LORA(L130+6500S)_V2.01哈二
修改内容: 
(1)发送LoRa数据时添加延时，目的是防止CAD打断发送过程，导致乱码；
(2)CA广播指令增加计算时间偏移公式，切信道的时候重新计算时间偏移；
(3)更改程序版本号-2.03




待解决问题：
1、9E回复是不是应该不需要偏频；
2、需增加通过指令开关LOG功能；