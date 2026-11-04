// 【交接】 PCRCtrlLib\SampleInfo.h
// 作用：SampleInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSampleInfo、SetPaitentID、GetPatientID、SetClinicID、GetClinicID、SetCaseID、GetCaseID、GetPatientName。
#pragma once

#include "DeclaresPCR.h"

// 样本信息，保存样本来源相关信息和检测信息
class AFX_EXT_CLASS CSampleInfo
{
public:
	// 函数 CSampleInfo
	// 作用：执行CSampleInfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetPaitentID。
	CSampleInfo(void);
	// 函数 ~CSampleInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetPaitentID。
	~CSampleInfo(void);

	// 函数 CSampleInfo
	// 作用：执行CSampleInfo。
	// 参数：samInfo。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetPaitentID。
	CSampleInfo(const CSampleInfo& samInfo);
	void operator=(const CSampleInfo& samInfo);
	BOOL operator==(const CSampleInfo& samInfo);

	// 函数 SetPaitentID
	// 作用：设置SetPaitentID。
	// 参数：strID：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPaitentID(CString strID) { m_strPatientID = strID; }
	// 函数 GetPatientID
	// 作用：读取GetPatientID。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetPatientID() { return m_strPatientID; }
	// 函数 SetClinicID
	// 作用：设置SetClinicID。
	// 参数：strID：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetClinicID(CString strID) { m_strClinicID = strID; }
	// 函数 GetClinicID
	// 作用：读取GetClinicID。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetClinicID() { return m_strClinicID; }
	// 函数 SetCaseID
	// 作用：设置SetCaseID。
	// 参数：strID：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCaseID(CString strID) { m_strCaseID = strID; }
	// 函数 GetCaseID
	// 作用：读取GetCaseID。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetCaseID() { return  m_strCaseID; }

	// 函数 GetPatientName
	// 作用：读取GetPatientName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetPatientName() { return m_strPatientName; }
	// 函数 SetPatientName
	// 作用：设置SetPatientName。
	// 参数：strName：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPatientName(CString strName) { m_strPatientName = strName; }
	// 函数 GetSexuality
	// 作用：读取GetSexuality。
	// 参数：无。
	// 返回：返回 ePatientSexuality。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	ePatientSexuality GetSexuality() { return m_nPatientSex; }
	// 函数 SetSexuality
	// 作用：设置SetSexuality。
	// 参数：nSex：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSexuality(ePatientSexuality nSex) { m_nPatientSex = nSex; }

	// 函数 SetSexuality
	// 作用：设置SetSexuality。
	// 参数：strData：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPaitentAge。
	void SetSexuality(CString strData);
	// 函数 GetSexualityString
	// 作用：读取GetSexualityString。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetPaitentAge。
	CString GetSexualityString();

	// 函数 GetAgeString
	// 作用：读取GetAgeString。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetPaitentAge。
	CString GetAgeString();
	// 函数 GetPaitentAge
	// 作用：读取GetPaitentAge。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetPaitentAge() { return m_nPatientAge; }
	// 函数 SetPaitentAge
	// 作用：设置SetPaitentAge。
	// 参数：iAge：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPaitentAge(int iAge) { m_nPatientAge = iAge; }

	// 函数 GetAgeUnit
	// 作用：读取GetAgeUnit。
	// 参数：无。
	// 返回：返回 ePatientAgeUnit。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	ePatientAgeUnit GetAgeUnit() { return m_nAgeUnit; }
	// 函数 SetAgeUnit
	// 作用：设置SetAgeUnit。
	// 参数：nUnit：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAgeUnit(ePatientAgeUnit nUnit) { m_nAgeUnit = nUnit; }
	// 函数 GetBeAbnormalAge
	// 作用：读取GetBeAbnormalAge。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetBeAbnormalAge(){return m_nPatientAge <= 0;}

	// 函数 GetAreaNo
	// 作用：读取GetAreaNo。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetAreaNo()  { return m_strAreaNo; }
	// 函数 SetAreaNo
	// 作用：设置SetAreaNo。
	// 参数：strArea：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAreaNo(CString strArea) { m_strAreaNo = strArea; }
	// 函数 GetRoomNo
	// 作用：读取GetRoomNo。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetRoomNo()  { return m_strRoomNo; }
	// 函数 SetRoomNo
	// 作用：设置SetRoomNo。
	// 参数：strRoom：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRoomNo(CString strRoom) { m_strRoomNo = strRoom; }
	// 函数 GetBedNo
	// 作用：读取GetBedNo。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetBedNo()  { return m_strBedNo; }
	// 函数 SetBedNo
	// 作用：设置SetBedNo。
	// 参数：strBed：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBedNo(CString strBed) { m_strBedNo = strBed; }
	// 函数 GetProposer
	// 作用：读取GetProposer。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetProposer()  { return m_strProposer; }
	// 函数 SetProposer
	// 作用：设置SetProposer。
	// 参数：strName：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetProposer(CString strName) { m_strProposer = strName; }
	// 函数 GetDepartment
	// 作用：读取GetDepartment。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetDepartment()  { return m_strDepartment; }
	// 函数 SetDepartment
	// 作用：设置SetDepartment。
	// 参数：strDept：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetDepartment(CString strDept) { m_strDepartment = strDept; }
	// 函数 GetHospital
	// 作用：读取GetHospital。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetHospital()  { return m_strHospital; }
	// 函数 SetHospital
	// 作用：设置SetHospital。
	// 参数：strHospital：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetHospital(CString strHospital) { m_strHospital = strHospital; }

	// 函数 GetCollectDate
	// 作用：读取GetCollectDate。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetCollectDate()  { return m_strCollectDate; }
	// 函数 GetCollectYMD
	// 作用：读取GetCollectYMD。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetCollectDate。
	CString GetCollectYMD();
	// 函数 SetCollectDate
	// 作用：设置SetCollectDate。
	// 参数：strDate：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCollectDate(CString strDate) { m_strCollectDate = strDate; }

	// 函数 SetCollectDateYMD
	// 作用：设置SetCollectDateYMD。
	// 参数：strDate：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetApplyDate。
	void SetCollectDateYMD(CString strDate);
	// 函数 SetSQMCollectDateYMD
	// 作用：设置SetSQMCollectDateYMD。
	// 参数：strDate：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetApplyDate。
	void SetSQMCollectDateYMD(CString strDate);

	// 函数 GetApplyDate
	// 作用：读取GetApplyDate。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetApplyDate()  { return m_strApplyDate; }
	// 函数 SetApplyDate
	// 作用：设置SetApplyDate。
	// 参数：strDate：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetApplyDate(CString strDate) { m_strApplyDate = strDate; }

	// 函数 Reset
	// 作用：更新或清除Reset。
	// 参数：无。
	// 返回：没有返回值。
	virtual void Reset();

public:
	CString				m_strPatientID; // 唯一标识，可以使ASSIC码
	CString				m_strClinicID; // 门诊号
	CString				m_strCaseID; // 病案号 病历号
	CString				m_strPatientName; // 姓名
	ePatientSexuality	m_nPatientSex; // 性别
	int					m_nPatientAge; // 年龄
	ePatientAgeUnit		m_nAgeUnit; // 年龄单位
	CString				m_strAreaNo; // 病区
	CString				m_strRoomNo; // 病房号
	CString				m_strBedNo; // 床号
	CString				m_strProposer; // 申请人，送检医生 20250307 根据用户要求需要替换技师
	CString				m_strDepartment; // 科室
	CString				m_strHospital; // 医院
	CString				m_strCollectDate; // 采集时间
	CString				m_strApplyDate; // 申请日期 20250307 根据用户要求需要替换为复检人姓名
};

