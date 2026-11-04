// 【交接】 GeneralPcr\EditModeType.h
// 作用：EditModeType。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
#pragma once

//实验编辑模式--包括无限制、IVD（只能修改样本信息）模式、运行中、运行结束
typedef enum ExpEditMode{
	EEEM_NOLIMIT,EEEM_IVD,EEEM_RUNNING,EEEM_END
}EEXPEDITMODE;
