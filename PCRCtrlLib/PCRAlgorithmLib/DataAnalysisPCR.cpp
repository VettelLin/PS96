// 【交接】 PCRCtrlLib\PCRAlgorithmLib\DataAnalysisPCR.cpp
// 作用：扩增曲线是否起峰的判断。IsPeakAml 只返回有没有起峰，不直接写阳性或阴性。
// 先看这些函数：CDataAnalysisPCR、InitPara、_T、GetPrivateProfileString、_ttof、_ttoi、CanNormalize、IsPeakAml。
#include "StdAfx.h"
#include "DataAnalysisPCR.h"

// 函数 CDataAnalysisPCR::CDataAnalysisPCR
// 作用：执行CDataAnalysisPCR。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDataAnalysisPCR::CDataAnalysisPCR(void)
{
	m_tagAbleToCalcuParam.dAmpNoNormalizeStd = 45.0;
	m_tagAbleToCalcuParam.dAmpNoNormalizeRatio = 1.03;
	m_tagAbleToCalcuParam.dAmpNormalizeStd = 0.007;
	m_tagAbleToCalcuParam.dAmpNormalizeRatio = 1.03;
	m_tagAbleToCalcuParam.dFDNoNormalizeVal = 10;
	m_tagAbleToCalcuParam.dFDNoNormalizeRatio = 1.1;
	m_tagAbleToCalcuParam.dFDNormalizeVal = 0.01;
	m_tagAbleToCalcuParam.dFDNormalizeRatio = 1.1;
	m_tagAbleToCalcuParam.dMeltNoNormalizeStd = 45;
	m_tagAbleToCalcuParam.dMeltNoNormalizeRatio = 1.1;
	m_tagAbleToCalcuParam.dMeltNormalizeStd = 0.01;
	m_tagAbleToCalcuParam.dMeltNormalizeRatio = 1.1;

	m_tagAbleToCalcuParam.bkCalcDotNum = 3;
	m_tagAbleToCalcuParam.dCrestBkRatio = 0.002;
	m_tagAmpNormalizedAnaParam.nAvgNum = 3;
	m_tagAmpNormalizedAnaParam.nNormalizeStartPreXPos = 8;

	m_tagAmpNormalizedAnaParam.bBaseCorrection = 1;
	m_tagAmpNormalizedAnaParam.dBCK = 65535;
	m_tagAmpNormalizedAnaParam.dBCR2 = 0.1;
	m_tagAmpNormalizedAnaParam.nBCXPosThre = 10;
	m_tagAmpNormalizedAnaParam.nBCStart = 1;
	m_tagAmpNormalizedAnaParam.nBCEndPreXPos = 3;
	m_tagAmpNormalizedAnaParam.nBCEndPreNumPos = 3;
	m_tagAmpNormalizedAnaParam.bMinus1 = true;
	m_tagAmpNormalizedAnaParam.bBaseSuppression = 1;
	m_tagAmpNormalizedAnaParam.dBSRatioAllData = 0.5;
	m_tagAmpNormalizedAnaParam.dBSRatioBaseLine = 0.5;
}


// 函数 CDataAnalysisPCR::~CDataAnalysisPCR
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDataAnalysisPCR::~CDataAnalysisPCR(void)
{
}

// 函数 CDataAnalysisPCR::InitPara
// 作用：初始化InitPara。
// 参数：strStartPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 _T、GetPrivateProfileString、_ttoi、_ttof。
void CDataAnalysisPCR::InitPara(CString strStartPath)
{
	CString strFilePath = strStartPath + _T("\\system\\AlgorithmPara.ini");
	TCHAR buf[128];

	//判定曲线是否满足计算的相关参数信息
	CString sSection=_T(""),sKeyName=_T("");
	sSection=_T("AbleToCalcu");

	sKeyName=_T("AmpNoNormalizeStd");
	GetPrivateProfileString(sSection, sKeyName,_T("-1"), buf, sizeof(buf), strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dAmpNoNormalizeStd = _ttof(buf);
	}
	sKeyName=_T("AmpNoNormalizeRatio");
	GetPrivateProfileString(sSection, sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dAmpNoNormalizeRatio = _ttof(buf);
	}
	sKeyName=_T("AmpNormalizeStd");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dAmpNormalizeStd = _ttof(buf);
	}
	sKeyName=_T("AmpNormalizeRatio");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dAmpNormalizeRatio = _ttof(buf);
	}
	//一阶导数最大值Max有效阈值及最大值/中位值 比率的有效阈值
	sKeyName=_T("FDNoNormalizeVal");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dFDNoNormalizeVal = _ttof(buf);
	}
	sKeyName=_T("FDNoNormalizeRatio");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dFDNoNormalizeRatio = _ttof(buf);
	}
	sKeyName=_T("FDNormalizeVal");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dFDNormalizeVal = _ttof(buf);
	}
	sKeyName=_T("FDNormalizeRatio");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dFDNormalizeRatio = _ttof(buf);
	}

	sKeyName=_T("MeltNoNormalizeStd");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dMeltNoNormalizeStd = _ttof(buf);
	}
	sKeyName=_T("MeltNoNormalizeRatio");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dMeltNoNormalizeRatio = _ttof(buf);
	}
	sKeyName=_T("MeltNormalizeStd");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dMeltNormalizeStd = _ttof(buf);
	}
	sKeyName=_T("MeltNormalizeRatio");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAbleToCalcuParam.dMeltNormalizeRatio = _ttof(buf);
	}

	sSection = _T("DD2CrestBackgroundRatioInfo");
	sKeyName=_T("BkCalculateDotNum");
	GetPrivateProfileString(sSection,sKeyName,_T("3"),buf,sizeof(buf),strFilePath);
	m_tagAbleToCalcuParam.bkCalcDotNum = _ttoi(buf);
	if(m_tagAbleToCalcuParam.bkCalcDotNum <= 0)
	{
		m_tagAbleToCalcuParam.bkCalcDotNum = 3;
	}

	sKeyName=_T("CrestBackgroundRatio");
	GetPrivateProfileString(sSection,sKeyName,_T("0.002"),buf,sizeof(buf),strFilePath);
	m_tagAbleToCalcuParam.dCrestBkRatio = _ttof(buf);


	//扩增曲线归一化处理相关参数信息
	sSection=_T("AmpNormalizedAna");

	sKeyName=_T("AvgNum");
	GetPrivateProfileString(sSection,sKeyName,_T("3"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.nAvgNum = _ttoi(buf);
	}
	sKeyName=_T("NormalizeStartPreXPos");
	GetPrivateProfileString(sSection,sKeyName,_T("8"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.nNormalizeStartPreXPos = _ttoi(buf);
	}
	sKeyName=_T("BaseCorrection");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.bBaseCorrection = _ttoi(buf);
	}
	sKeyName=_T("BCK");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.dBCK = _ttof(buf);
	}
	sKeyName=_T("BCR2");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.dBCR2 = _ttof(buf);
	}
	sKeyName=_T("BCXPosThre");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.nBCXPosThre = _ttoi(buf);
	}
	sKeyName=_T("BCStart");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.nBCStart = _ttoi(buf);
	}
	sKeyName=_T("BCEndPreXPos");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.nBCEndPreXPos = _ttoi(buf);
	}
	sKeyName=_T("BCEndPreNumPos");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.nBCEndPreNumPos = _ttoi(buf);
	}

	sKeyName=_T("Minus1");
	GetPrivateProfileString(sSection,sKeyName,_T("1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.bMinus1 = _ttoi(buf);
	}

	sKeyName=_T("BaseSuppression");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.bBaseSuppression = _ttoi(buf);
	}
	sKeyName=_T("BSRatioAllData");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.dBSRatioAllData = _ttof(buf);
	}
	sKeyName=_T("BSRatioBaseLine");
	GetPrivateProfileString(sSection,sKeyName,_T("-1"),buf,sizeof(buf),strFilePath);
	if(_ttoi(buf) != -1)
	{
		m_tagAmpNormalizedAnaParam.dBSRatioBaseLine = _ttof(buf);
	}
}

// 判断能否归一化，nAvgNum一般为3
// 函数 CDataAnalysisPCR::CanNormalize
// 作用：判断CanNormalize是否成立。
// 参数：iCycleCount：整数。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CDataAnalysisPCR::CanNormalize(int iCycleCount)
{
	return m_tagAmpNormalizedAnaParam.nAvgNum > 0 && m_tagAmpNormalizedAnaParam.nAvgNum < iCycleCount;
}

// 判断一条荧光曲线算不算起峰。返回 TRUE 只表示“有起峰”，这里不写阳性或阴性。
// 调用方在基线校正前使用中值滤波后的曲线。点数少于 8 时调用方不会进入这里。
// 必须按下面的顺序全部通过才算起峰：
// 1. 曲线不是全 0。
// 2. 整条曲线样本标准差大于 45。
// 3. 二阶导尖峰明显高于基线段，并且尖峰/背景比值大于 0.001。
// 4. 后段平均值大于前段平均值的 1.1 倍。第一次用原始曲线；没过并且尖峰在第 4 点之后，基线校正后再比一次。
// dOutCt 带回二阶导尖峰位置，供后面自动基线使用。位置为 0 表示没有找到可用尖峰。
BOOL CDataAnalysisPCR::IsPeakAml(double *pDX,double *pDY,int nDataNum,CPeakAmlCheckParam& peakAmlChkParam, double &dOutCt)
{
	double max = abs(pDY[0]);
	for(int i = 1;i < nDataNum;++i)
	{
		max = max > abs(pDY[i]) ? max : abs(pDY[i]);
	}	
	// 全 0 曲线没有扩增形状，直接失败。
	// 波动门槛用样本标准差，除数是 n-1。小于或等于 45 视为没有起峰。
	if (0 == max)
	{
		return FALSE;
	}

	double dSD = CalculateSD(nDataNum, pDY);
	if (dSD <= peakAmlChkParam.m_dStdThreshold)
		return FALSE;

	// 第一次前后段比较用尚未做尖峰滤波的原始输入。
	// 前段上限设成当前点数，相当于不额外截断，前段取 round(n/3) 个点。
	// 这次没通过先保留结果，等尖峰条件通过后再决定要不要补判。
	peakAmlChkParam.m_iForeAvgMax = nDataNum;
	BOOL bMeetAvg = MeetForeAvgAndEndAvgCondition(nDataNum, pDY, peakAmlChkParam);

	BOOL bFindNormalD2Max = FALSE;

	double* pDTemp = new double[nDataNum];
	memcpy(pDTemp,pDY,nDataNum * sizeof(double));
	double* pDReturn = new double[nDataNum];
	::memset(pDReturn,0,nDataNum);

	double* pDFiltered = new double [nDataNum];
	::memset(pDFiltered,0,nDataNum);

	// 尖峰检查前先做 1 次窗口为 5 的中值滤波，再做 3 次平滑，然后才算二阶导数。
	DigitalFilter(pDTemp, pDFiltered, nDataNum,CDataAlgorithmPCR::FILTERTYPE_MEDIAN, 5);
	memcpy(pDTemp,pDFiltered,sizeof(double) * nDataNum);

	for (int i=0; i<3; ++i)
	{
		KdsptForwardMBackN_New(nDataNum, pDTemp, pDFiltered, 2, 2);
		memcpy(pDTemp,pDFiltered,sizeof(double) * nDataNum);
	}
	//OutputPointerData(nDataNum, pDTemp);

	//计算二阶导数
	//NewCalDerivative(pDX, pDFiltered,nDataNum,2, pDReturn); 	
	CalcSecondDerivative(nDataNum, pDFiltered, pDReturn);
	//OutputPointerData(nDataNum, pDReturn);

	//计算二阶导数最大值
	double dmax = pDReturn[0]; 
	double dmin = pDReturn[0];
	// 尖峰位置不是“二阶导数组里最大的那个下标”。
	// CalcCtPosBySndDerivative 用宽度为 6 的窗口找尖峰，附近二阶导绝对值之和必须大于 60。
	// nxpos_max 是四舍五入后的点序号。dmax 取二阶导数组的 nxpos_max-1。
	// 找不到尖峰时 dXPosMax 为 0，这里会读到下标 -1。这是原有写法，交接时不要单独改这一行的取值顺序。
	double dXPosMax = CalcCtPosBySndDerivative(nDataNum, pDX, pDFiltered);
	dOutCt = dXPosMax;

	int nxpos_max = (int)(dXPosMax + 0.5);
	dmax = pDReturn[nxpos_max - 1];

	// 二阶导基线段：起点 m_start=1，终点在尖峰前 m_forwardNum=3 个点。
	// 默认时基线点数 = 尖峰序号 - 3。少于 2 个点就认为没有明显尖峰。
	// 尖峰处二阶导必须大于：基线均值 + 1.5 倍基线标准差。
	int blDotNum = nxpos_max - peakAmlChkParam.m_forwardNum - peakAmlChkParam.m_start + 1;
	if(blDotNum > 1)
	{
		double dBLAvg = 0,dBLSD = 0;
		//计算变异系数
		for(int i = 0; i < blDotNum;++i)
		{
			dBLAvg += pDReturn[i];
		}
		dBLAvg /= blDotNum;
		for(int i= 0;i < nxpos_max - 3;++i)
		{
			dBLSD += (pDReturn[i] - dBLAvg) * (pDReturn[i] - dBLAvg);
		}
		dBLSD = sqrt(dBLSD / (blDotNum - 1));

		if(dmax > (dBLAvg + peakAmlChkParam.m_sdMultiples * dBLSD))
		{
			bFindNormalD2Max = TRUE;
		}
		else
		{
			bFindNormalD2Max = FALSE;
		}
	}
	else
	{
		bFindNormalD2Max = FALSE;
	}	

	//计算二阶导最大值（从离散数据中寻找）和背景值（取滤波后数据前N个点）的比值
	double dCrestBkRatio = 0;
	double dBkSum = 0,dBkAvg = 0;
	// 尖峰背景比。分子是尖峰处二阶导绝对值，分母是原始曲线前 3 个点的平均值，不是滤波后的值。
	// 分母为 0 时比值保持 0，后面的大于 0.001 不成立。
	for(int i = 0;i < peakAmlChkParam.m_bkCalcDotNum;++i)
	{
		dBkSum += pDY[i];
	}
	if(peakAmlChkParam.m_bkCalcDotNum > 0)
	{
		dBkAvg = dBkSum / peakAmlChkParam.m_bkCalcDotNum;
	}

	if(0 != dBkAvg)
	{
		dCrestBkRatio = abs(dmax / dBkAvg);
	}

	BOOL bFindPeak = FALSE;
	// 尖峰明显高于基线、并且背景比大于 0.001，两件必须同时成立。
	// 前后段第一次已经通过，到这里就算起峰。
	// 第一次没通过时，只有尖峰序号大于 3 才做基线校正后的补判。
	// 补判时前段最多取到尖峰前 2 个点。尖峰落在前 3 个点里，不再补判。
	if (bFindNormalD2Max && dCrestBkRatio > peakAmlChkParam.m_dCrestBkRatio)
	{
		if (bMeetAvg)
		{
			bFindPeak = TRUE;
		}
		else if (nxpos_max > 3)
		{
			int iCurStart, iCurEnd;
			memcpy(pDFiltered,pDTemp,sizeof(double) * nDataNum);

			CalcAutoBaselinePosBySndDrvCt(dXPosMax, nDataNum, pDX, pDFiltered,iCurStart,iCurEnd);
			if (iCurEnd - iCurStart < dXPosMax / 2)
			{
				iCurStart = iCurEnd - int(dXPosMax / 2);
				if (iCurStart < 1)
				{
					iCurStart = 1;
				}
			}

			memcpy(pDFiltered,pDTemp,sizeof(double) * nDataNum);
			AdjustFluValueByBaseline(nDataNum, pDX, pDFiltered,iCurStart,iCurEnd);
			peakAmlChkParam.m_iForeAvgMax = nxpos_max -2;
			bFindPeak = MeetForeAvgAndEndAvgCondition(nDataNum, pDFiltered, peakAmlChkParam);
		}
		else
			bFindPeak = FALSE; 
	}
	else
	{
		bFindPeak = FALSE; 
	}

	delete [] pDTemp;
	delete [] pDFiltered;
	delete [] pDReturn;	

	//if (!bFindPeak && dXPosMax > 3)
	//{
	//	//bFindPeak = FindPeakAmlBySlope(nDataNum, pDX, pDY);
	//	int iFindIndex = AbleToCalculateCtBySndDerivative(nDataNum, pDX, pDY, 100);
	//	if (iFindIndex > 5)
	//	{
	//		bFindPeak = TRUE;
	//	}
	//}

	return bFindPeak;
}

// 满足标准方差条件
// 样本标准差，除数是点数减 1。IsPeakAml 用它和 45 比较。
// 函数末尾算出的变异系数 cv 没有返回，调用方只用标准差。
// 函数 CDataAnalysisPCR::CalculateSD
// 作用：计算CalculateSD。
// 参数：iDataCount：整数；pInputData：指针，指向调用方传入的对象。
// 返回：返回一个小数。
// 过程：函数里会调用 sqrt。
double CDataAnalysisPCR::CalculateSD(int iDataCount, double* pInputData)
{
	double dAvg = 0,dSD = 0;
	for(int i = 0;i < iDataCount;++i)
	{
		dAvg += pInputData[i];
	}

	dAvg /= iDataCount;
	for(int i = 0;i < iDataCount;++i)
		dSD += (pInputData[i] - dAvg) * (pInputData[i] - dAvg);
	dSD = sqrt(dSD / (iDataCount - 1));
	double cv = 0;
	if(0 != dAvg)
	{
		cv = dSD / dAvg;
	}
	else
	{
		cv = 0;
	}

	return dSD;
}
// 是否满足前后均值限制条件
// 后段是不是明显高于前段。
// 前段个数 = round(点数 / 3)，并且不能超过 m_iForeAvgMax。
// 后段起点先取 round(点数 * 8 / 9)。这个起点大于或等于 10 时，改成只取最后 3 个点。
// 通过条件：前段平均值 * m_dRatioThreshold(1.1) < 后段平均值。
BOOL CDataAnalysisPCR::MeetForeAvgAndEndAvgCondition(int iDataCount, double* pInputData, CPeakAmlCheckParam& peakAmlChkParam)
{
	double dForeAvg = 0,dEndAvg = 0;
	int nForeID = 0, nEndID = 0;
	nForeID = (int)(iDataCount / 3.0 + 0.5); 
	if (nForeID > peakAmlChkParam.m_iForeAvgMax)
		nForeID = peakAmlChkParam.m_iForeAvgMax;
	nEndID =(int)(iDataCount * 8 / 9 + 0.5);

	for(int i = 0;i < nForeID;++i)
	{
		dForeAvg += pInputData[i];
	}
	// 点数比较多时，后段不取后八分之一，只取最后 3 个点。
	if(nEndID >= 10)
	{
		nEndID = iDataCount - 3;
	}
	for(int i = nEndID;i < iDataCount;++i)
	{
		dEndAvg += pInputData[i];
	}

	dForeAvg = nForeID > 0 ? dForeAvg / (nForeID) : 0;
	dEndAvg = nEndID > 0 ? dEndAvg / (iDataCount - nEndID) : 0;

	return dForeAvg * peakAmlChkParam.m_dRatioThreshold < dEndAvg;
}

// 归一化处理
// 函数 CDataAnalysisPCR::CalcNormalize
// 作用：计算CalcNormalize。
// 参数：nPtCount：整数；pInputY：指针，指向调用方传入的对象；pOutputY：指针，指向调用方传入的对象；dAverage：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CDataAnalysisPCR::CalcNormalize(int nPtCount, double *pInputY, double *pOutputY, double dAverage)
{
	if(0 == dAverage)
	{
		for(int i = 0;i < nPtCount;++i)
		{
			pOutputY[i] = pInputY[i];
		}	
		return;
	}

	if(m_tagAmpNormalizedAnaParam.bMinus1)	//减1操作,便于对数曲线表现
	{
		for(int i=0; i<nPtCount; i++)
		{
			pOutputY[i] = pInputY[i] / dAverage - 1;
		}	
	}
	else
	{
		for(int i=0; i<nPtCount; i++)
		{
			pOutputY[i] = pInputY[i] / dAverage;
		}
	}
}

//计算△Rn
// 函数 CDataAnalysisPCR::CalcDeltaRn
// 作用：计算CalcDeltaRn。
// 参数：nPtCount：整数；pInputY：指针，指向调用方传入的对象；pOutputY：指针，指向调用方传入的对象；dAverage：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CDataAnalysisPCR::CalcDeltaRn(int nPtCount, double *pInputY, double *pOutputY, double dAverage)
{
	for(int i=0; i<nPtCount; i++)
	{
		pOutputY[i] = pInputY[i] - dAverage;
	}
}

// 根据基线区间拟合直线斜率对荧光值进行修正
// 函数 CDataAnalysisPCR::AdjustFluValueByBaseline
// 作用：执行AdjustFluValueByBaseline。
// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iStart：整数；iEnd：整数。
// 返回：没有返回值。
// 过程：函数里会调用 memcpy、LinearFit、fabs。
void CDataAnalysisPCR::AdjustFluValueByBaseline(int nPtCount, double *pInputX, double *pInputY, int iStart, int iEnd)
{
	if (iStart > nPtCount)
	{
		iStart = nPtCount;
	}
	if (iEnd >nPtCount)
	{
		iEnd = nPtCount;
	}
	int iStep = iEnd - iStart +1;

	if (iStep >= 2) // 基线区间包括2个点，进行线性拟合调整
	{
		double dCoef[3]={0};
		double* dTemp = new double[iStep];
		memcpy(dTemp, pInputY + (iStart - 1), sizeof(double) * iStep);
		LinearFit(pInputX, dTemp, iStep, dCoef);

		if (fabs(dCoef[1]) < 100 || (iEnd-iStart > nPtCount/3 || iEnd-iStart > 10))
		{
			for (int i = 0;i < nPtCount;++i)
			{
				pInputY[i] -= (pInputX[i] * dCoef[1]);
			}
		}

		if(NULL != dTemp)
		{
			delete [] dTemp;
			dTemp = NULL;
		}
	}
	return;
}

// 函数 CDataAnalysisPCR::CalcFluTurbidityAdjust
// 作用：计算CalcFluTurbidityAdjust。
// 参数：iCtMOT：整数；iCtPos：整数；dAdjustRatio：小数；nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；pOutputY：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CalcFluDataByCtAndMOT、memcpy、LinearFit、CalcLegalLineFitParam。
void CDataAnalysisPCR::CalcFluTurbidityAdjust(int iCtMOT, int iCtPos, double dAdjustRatio, int nPtCount, double* pInputX, double *pInputY, double *pOutputY)
{
	int nStartNo = iCtMOT -1;
	if (nStartNo < 0)
	{
		nStartNo = 0;
	}

	if (nStartNo < 3) // 只有3个点不需要进行线性拟合
	{
		if (iCtPos < 1) // 没有Ct
		{
			double dStartBase = pInputY[nStartNo];
			for (int j=0; j<nPtCount; j++)
			{
				if (j > nStartNo)
				{
					pOutputY[j] = dStartBase + (pInputY[j] - dStartBase) * dAdjustRatio;
				}
				else
				{
					pOutputY[j] = pInputY[j];
				}
			}
		}
		else
		{
			CalcFluDataByCtAndMOT(nStartNo, nPtCount, pInputY, dAdjustRatio, pOutputY);
		}
	}
	else 
	{
		int iMinPtCount = 4;// 4-6个点进行线性拟合，保证R大于9，不然较少拟合点数，最少4点
		double dMinR = 0.93;
		if (nStartNo < 8)
		{
			dMinR = 0.95;
		}
		else
		{
			iMinPtCount = 6;
			dMinR = 0.97;
		}

		double dCoef[3]={0};
		double* pdTmepX = new double[nStartNo+1];
		memcpy(pdTmepX, pInputX, sizeof(double) * (nStartNo+1));
		double* pdTempY = new double[nStartNo+1];
		memcpy(pdTempY, pInputY, sizeof(double) * (nStartNo+1));
		// LinearFit(pInputX, dTemp, nStartNo+1, dCoef);
		int iTempStart = CalcLegalLineFitParam(nStartNo+1, pdTmepX, pdTempY, dCoef, iMinPtCount, dMinR);

		double dMaxDecend = 0;
		if (dCoef[1] < 0)
		{
			for (int i=iMinPtCount+iTempStart; i<nPtCount; ++i)
			{
				double dTempY = pInputX[i] * dCoef[1] + dCoef[0];
				if (dTempY > pInputY[i])
				{
					if (dMaxDecend < dTempY - pInputY[i])
						dMaxDecend = dTempY - pInputY[i];
				}

				pInputY[i] = pInputY[i] + dMaxDecend;
			}
		}

		if (pdTmepX != NULL)
		{
			delete pdTmepX;
			pdTmepX = NULL;
		}
		if (pdTempY != NULL)
		{
			delete pdTempY;
			pdTempY = NULL;
		}
	}

	memcpy(pOutputY, pInputY, sizeof(double)*nPtCount);
	CalcFluDataByCtAndMOT(nStartNo, nPtCount, pInputY, dAdjustRatio, pOutputY);
}


// 根据给定比率进行荧光数据浊度调整
// 函数 CDataAnalysisPCR::CalcFluDataByCtAndMOT
// 作用：计算CalcFluDataByCtAndMOT。
// 参数：nStartNo：整数；nCycleCount：整数；pdValueY；dChangedRatio：小数；pdOutputY。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CDataAnalysisPCR::CalcFluDataByCtAndMOT(int nStartNo, int nCycleCount, double* pdValueY, double dChangedRatio, double* pdOutputY)
{
	double dStartBase = pdValueY[nStartNo];
	for (int j=nStartNo+1; j<nCycleCount; j++)
	{
		if (pdValueY[j] > dStartBase)
		{
			dStartBase = pdValueY[j];
		}
		else
		{
			double dCalcValue = dStartBase + (pdValueY[j] - dStartBase) * dChangedRatio;
			pdOutputY[j] = dCalcValue;
		}
	}
}

// 函数 CDataAnalysisPCR::AbleToCalculateCt
// 作用：执行AbleToCalculateCt。
// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；bNormalized：是或否。
// 返回：返回是或否。
// 过程：函数里会调用 NewAbleToCalculate。
BOOL CDataAnalysisPCR::AbleToCalculateCt(int nPtCount, double *pInputX, double *pInputY, BOOL bNormalized)
{
	m_tagAbleToCalcuParam.bNormalization = bNormalized;
	return NewAbleToCalculate(pInputX, pInputY, nPtCount, m_tagAbleToCalcuParam, m_tagAmpNormalizedAnaParam.nBCStart, m_tagAmpNormalizedAnaParam.nBCEndPreXPos, 3);
}

// 函数 CDataAnalysisPCR::NewAutoFindCrest
// 作用：执行NewAutoFindCrest。
// 参数：nCrestNum：整数；nPtNum：整数；dXValue：小数；dYValue：小数；dReturn：小数；pDCrestIndex：指针，指向调用方传入的对象；dThrePercent：小数；dHandSetThre：小数；bPosFstDerivative：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 RemoveAll、Add、GetSize、GetAt、SortDouble、fabs。
void CDataAnalysisPCR::NewAutoFindCrest(int nCrestNum,int nPtNum, double *dXValue, double *dYValue, double *dReturn,int* pDCrestIndex,double dThrePercent /* = 0.2 */,double dHandSetThre /*= 0*/,BOOL bPosFstDerivative /*= FALSE*/)
{
	CArray<int,int>  arrayTemp;
	arrayTemp.RemoveAll();
	double temp[3] = {0};
	for(int i=1; i<nPtNum-2; i++)
	{
		for(int j=0; j< 3; temp[j++] = 0);
		temp[0] = dYValue[i]- dYValue[i-1];
		temp[1] = dYValue[i]- dYValue[i+1];
		temp[2] = dYValue[i]- dYValue[i+2];

		if( temp[0] >0 && temp[1] >0  && temp[2]>0)
			arrayTemp.Add(i);
	}
	int nSize = (int) arrayTemp.GetSize();
	double *dTemp = new double[nSize];
	double *dOut = new double[nSize];
	for(int i=0; i< nSize; i++)
		dTemp[i] = dYValue[arrayTemp.GetAt(i)];
	SortDouble(nSize,dTemp,dOut);
	//进一步处理，以最高峰值的20%(缺省)作为阈值线，高于阈值线的即为有效峰
	float fThre = 0;
	if (nSize >= 1)
	{
		fThre = dOut[nSize -1] * dThrePercent;
	}

	fThre = dHandSetThre;

	//如果找到多个峰，过滤掉峰值比较小的数,20200225,孙文郎,20211111修改为过滤掉峰值绝对值较小的数
	//使用峰值的绝对值和峰高阈值作比较
	for (int i = 0; i < nSize; i++)
	{
		if (fabs(dOut[i]) < fThre)
			dOut[i] = -1;
	}
	int count = 0;
	for(int i=nSize-1; i>= nSize-nCrestNum && i >= 0; i--)
	{
		bool bfind = false;
		for(int j=0; j< nSize; j++)
		{
			if( dYValue[arrayTemp.GetAt(j)] == dOut[i])
			{
				bfind = true;
				pDCrestIndex[count] = arrayTemp.GetAt(j);
				dReturn[count++] = dXValue[arrayTemp.GetAt(j)];
				if(count >= nCrestNum)
				{
					goto SAMCRESTEXIST;	//两个峰值相同时，容易触发这个问题
				}
			}
		}
		if (!bfind)
		{
			pDCrestIndex[count] = 0; 
			dReturn[count++] = -1;
		}
	}

#ifdef _DEBUG
	if(count > 1)
	{
		int mm = 0;
		++mm;
	}
#endif

SAMCRESTEXIST:
	if(nCrestNum > nSize)
	{
		for(int i=nSize; i<nCrestNum; i++)
		{
			dReturn[i] = -1;
			pDCrestIndex[i] = -1;
		}			
	}

	delete [] dTemp;
	delete [] dOut;
}


// 函数 CDataAnalysisPCR::FindStartPlateauCycle
// 作用：执行FindStartPlateauCycle。
// 参数：iCycleCount：整数；pdInputX；pdInputY；dCt：小数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 int。
int CDataAnalysisPCR::FindStartPlateauCycle(int iCycleCount, double *pdInputX, double *pdInputY, double dCt)
{
	int iReturn = -1;
	int iStartCycle = int (dCt);
	double dStartBase = pdInputY[iStartCycle];
	
	for (int i=iStartCycle+1; i<iCycleCount; i++)
	{
		if (pdInputY[i] > dStartBase)
		{
			dStartBase = pdInputY[i];
		}
		else // 开始下降
		{
			iReturn = i;
			//for (int j=i; j>=1; j--)
			//{
			//	if ((pdInputY[j] - pdInputY[j-1]) > 50)
			//		break;
			//	else
			//		iReturn = j-1;
			//}
			break;
		}
	}

	return iReturn;
}

// 去除开始和结束位置的变动较大的点
// 函数 CDataAnalysisPCR::CalcBaselinePosOfNoCt
// 作用：计算CalcBaselinePosOfNoCt。
// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iOutStart：整数；iOutEnd：整数。
// 返回：没有返回值。
// 过程：函数里会调用 fabs、LinearFit。
void CDataAnalysisPCR::CalcBaselinePosOfNoCt(int nPtCount, double *pInputX, double *pInputY, int &iOutStart, int &iOutEnd)
{
	//if (nPtCount <= 10)
	{
		double dSum = 0;
		double dAverage = 0;
		for (int i=nPtCount/2; i<nPtCount; i++)
		{
			dSum += pInputY[i];
		}

		iOutStart = 1;
		iOutEnd = nPtCount;
		dAverage = dSum / nPtCount / 2;
		for (int i=1; i<nPtCount; i++)
		{
			if (fabs(pInputY[i] - pInputY[i-1]) > dAverage * 0.1)
			{
				iOutStart = i;
			}
			else
				break;
		}

		for (int i=nPtCount-1; i>iOutStart; i--)
		{
			if (fabs(pInputY[i] - pInputY[i-1]) > dAverage * 0.1)
			{
				iOutEnd = i-1;
			}
			else
				break;

		}

		if (iOutStart > nPtCount / 2 || iOutEnd < nPtCount / 2 || iOutEnd - iOutStart < nPtCount / 2)
		{
			iOutStart = 1;
			iOutEnd = nPtCount;
		}
	}

	//else
	//{
	//	double dCurCoef[3] = {0};
	//	int iWndWidth = nPtCount / 4;
	//	double* pdTempX = new double[iWndWidth];
	//	double* pdTempY = new double[iWndWidth];
	//	double fFirstSlope = 0;

	//	BOOL bFindPlateau = FALSE;
	//	BOOL bFindFirstSlope = FALSE;
	//	for (int i=0; i<=nPtCount-iWndWidth; i++)
	//	{
	//		for (int j=0; j<iWndWidth; j++)
	//		{
	//			pdTempX[j] = pInputX[i+j];
	//			pdTempY[j] = pInputY[i+j];
	//		}
	//		LinearFit(pdTempX, pdTempY, iWndWidth, dCurCoef);
	//		if (!bFindFirstSlope)
	//		{
	//			if (dCurCoef[1] < 50)
	//			{
	//				fFirstSlope = dCurCoef[1];
	//				iOutStart = i+1;
	//				bFindFirstSlope = TRUE;
	//				bFindPlateau = TRUE;
	//			}
	//		}
	//		else
	//		{
	//			if (fabs(dCurCoef[1]) < 25)
	//			{
	//				iOutEnd = i+iWndWidth+1;
	//				continue;
	//			}

	//			if (fabs(dCurCoef[1]-fFirstSlope) > fabs(fFirstSlope) * 0.5)
	//			{
	//				iOutEnd = i+iWndWidth+1;
	//				break;
	//			}
	//		}
	//	}

	//	if (!bFindPlateau)
	//	{
	//		int iStart1, iEnd1, iStart2, iEnd2;
	//		fFirstSlope = 0;
	//		BOOL bFirstPlateau = FALSE;
	//		bFindFirstSlope = FALSE;
	//		BOOL bFindSecondSlope = FALSE;

	//		for (int i=0; i<=nPtCount-iWndWidth; i++)
	//		{
	//			for (int j=0; j<iWndWidth; j++)
	//			{
	//				pdTempX[j] = pInputX[i+j];
	//				pdTempY[j] = pInputY[i+j];
	//			}
	//			LinearFit(pdTempX, pdTempY, iWndWidth, dCurCoef);
	//			if (!bFirstPlateau)
	//			{
	//				if (!bFindFirstSlope)
	//				{
	//					fFirstSlope = dCurCoef[1];
	//					iStart1 = i+1;
	//					iEnd1 = iStart1 + iWndWidth -1;
	//					bFindFirstSlope = TRUE;
	//				}
	//				else
	//				{
	//					if (fabs(dCurCoef[1]-fFirstSlope) > fabs(fFirstSlope) * 0.5)
	//					{
	//						iEnd1 = i + iWndWidth;
	//						bFirstPlateau = TRUE;
	//					}
	//				}
	//			}
	//			else
	//			{
	//				if (!bFindSecondSlope)
	//				{
	//					fFirstSlope = dCurCoef[1];
	//					iStart2 = i+1;
	//					iEnd2 = iStart2 + iWndWidth -1;
	//					bFindSecondSlope = TRUE;
	//				}
	//				else
	//				{
	//					if (fabs(dCurCoef[1]-fFirstSlope) > fabs(fFirstSlope) * 0.5)
	//					{
	//						iEnd2 = i + iWndWidth;
	//						break;
	//					}
	//				}
	//			}
	//		}

	//		if (iEnd1-iStart1 > nPtCount / 2 || iEnd1-iStart1 > iEnd2 - iStart2)
	//		{
	//			iOutStart = iStart1;
	//			iOutEnd = iEnd1;
	//		}
	//		else
	//		{
	//			iOutStart = iStart2;
	//			iOutEnd = iEnd2;
	//		}
	//	}
	//}
}


// 函数 CDataAnalysisPCR::CalcLegalLineFitParam
// 作用：计算CalcLegalLineFitParam。
// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；dReturn：小数；iMinPtCount：整数；dMinR：小数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 memset、LinearFit、memcpy。
int CDataAnalysisPCR::CalcLegalLineFitParam(int nPtCount, double *pInputX, double *pInputY, double *dReturn, int &iMinPtCount, double dMinR)
{
	double* pdTempX = new double[nPtCount];
	double* pdTempY = new double[nPtCount];

	double dMaxRParam[3] = {0};
	memset(dMaxRParam, 0, sizeof(double) * 3);
	int iStartPos = 0;
	BOOL bFindLegal = FALSE;

	int iTempCount = iMinPtCount;
	int iTempStart = nPtCount - iTempCount;

	double dTempCoef[3] = {0};
	while (TRUE)
	{
		for(int i=0; i<iTempCount; i++)
		{
			pdTempX[i] = pInputX[i+iTempStart];
			pdTempY[i] = pInputY[i+iTempStart];
		}

		LinearFit(pdTempX, pdTempY, iTempCount, dTempCoef);

		if (bFindLegal)
		{
			if (dTempCoef[2]*dTempCoef[2] > dMinR)
			{
				memcpy(dMaxRParam, dTempCoef, sizeof(double) * 3);
				iStartPos = iTempStart;
				iMinPtCount = iTempCount;
				iTempCount += 1;
			}
		}
		else
		{
			if (dTempCoef[2]*dTempCoef[2] > dMinR)
			{
				memcpy(dMaxRParam, dTempCoef, sizeof(double) * 3);
				iStartPos = iTempStart;
				bFindLegal = TRUE;
				iMinPtCount = iTempCount;
				iTempCount += 1;
			}
			else if (dTempCoef[2]*dTempCoef[2] > dMaxRParam[2])
			{
				memcpy(dMaxRParam, dTempCoef, sizeof(double) * 3);
				iStartPos = iTempStart;
			}
		}

		iTempStart -= 1;
		if (iTempStart < 0)
			break;
	}

	if (pdTempX != NULL)
	{
		delete pdTempX;
		pdTempX = NULL;
	}
	if (pdTempY != NULL)
	{
		delete pdTempY;
		pdTempY = NULL;
	}

	memcpy(dReturn, dMaxRParam, sizeof(double) * 3);

	return iStartPos;
}

// 函数 CDataAnalysisPCR::FindPeakAmlBySlope
// 作用：执行FindPeakAmlBySlope。
// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iWndWidth：整数。
// 返回：返回是或否。
// 过程：函数里会调用 LinearFit。
BOOL CDataAnalysisPCR::FindPeakAmlBySlope(int nPtCount, double *pInputX, double *pInputY, int iWndWidth)
{
	BOOL bFindPeak = FALSE;

	double dPreCoef[3] = {0};
	double dCurCoef[3] = {0};
	double* pdTempX = new double[iWndWidth];
	double* pdTempY = new double[iWndWidth];

	for (int i=3; i<nPtCount-iWndWidth+1; i++)
	{
		BOOL bContinueRise = TRUE;
		for (int j=0; j<iWndWidth-1; j++)
		{
			if (pInputY[j+i+1] < pInputY[j+i])
			{
				bContinueRise = FALSE;
				break;
			}
		}

		if (bContinueRise) // 计算前后点的斜率
		{
			int iTempCount = iWndWidth;
			for(int ii=0; ii<iTempCount; ii++)
			{
				pdTempX[ii] = pInputX[ii+i];
				pdTempY[ii] = pInputY[ii+i];
			}
			LinearFit(pdTempX, pdTempY, iTempCount, dCurCoef);
			if (dCurCoef[1] < 80)
				continue;

			if (i < iWndWidth)
			{
				iTempCount = i+1;
			}

			for(int ii=0; ii<iTempCount; ii++)
			{
				pdTempX[ii] = pInputX[i-iTempCount+1+ii];
				pdTempY[ii] = pInputY[i-iTempCount+1+ii];
			}
			LinearFit(pdTempX, pdTempY, iTempCount, dPreCoef);


			if (dCurCoef[1] - dPreCoef[1] > 50)
			{
				bFindPeak = TRUE;
				break;
			}
		}
	}

	delete pdTempX;
	delete pdTempY;

	return bFindPeak;
}

// 使用二阶导数连续超过某个最小值的5个数作为判定是否扩增的条件
// 函数 CDataAnalysisPCR::AbleToCalculateCtBySndDerivative
// 作用：执行AbleToCalculateCtBySndDerivative。
// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；dMinValue：小数；iValueCount：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 memcpy、KdsptForwardMBackN_New、CalcSecondDerivative。
int CDataAnalysisPCR::AbleToCalculateCtBySndDerivative(int nPtCount, double *pInputX, double *pInputY, double dMinValue, int iValueCount)
{
	int iLastPoint = -1;
	// 先进行均值滤波
	double *pDTempY = new double[nPtCount];
	if(NULL == pDTempY)
		return iLastPoint;
	memcpy(pDTempY, pInputY, sizeof(double)*nPtCount);

	double *pDReturn = new double[nPtCount];
	if(NULL == pDReturn)
	{
		delete pDTempY;
		return iLastPoint;
	}
	for (int i=0; i<2; i++)
	{
		KdsptForwardMBackN_New(nPtCount,pDTempY,pDReturn, 2, 2);
		memcpy(pDTempY, pDReturn, sizeof(double)*nPtCount);
	}

	double* pdSecondDer = new double[nPtCount];
	CalcSecondDerivative(nPtCount, pDReturn, pdSecondDer);
	int iLegalCount = 0;
	int iMinLegalCount = 0;
	for (int i=0; i<nPtCount; i++)
	{
		if (pdSecondDer[i] > 50)
		{
			iMinLegalCount ++;
		}

		if (pdSecondDer[i] > dMinValue)
		{
			iLegalCount ++;
		}
		else
		{
			iLegalCount = 0;
		}

		if (iLegalCount >= iValueCount)
		{
			iLastPoint = i;
			break;
		}
	}

	//if (iMinLegalCount < 5 && iLastPoint > 0)
	//	iLastPoint = -1;

	delete pDTempY;
	delete pDReturn;
	delete pdSecondDer;
	return iLastPoint;
}
