#ifndef FLAWDEFINE_H
#define FLAWDEFINE_H

#define EXCEED_PULSE 6553500
#define MAX_PULSE 4294967296

#define MAX_DATA_PACK_ROW_NUE_PER_FIELD 3

#include <windows.h>

typedef unsigned long DWORD;
typedef unsigned short WORD;

#pragma pack(push) //保存对齐状态
#pragma pack(1)

/*
typedef struct _SYSTEMTIME {
  WORD wYear;
  WORD wMonth;
  WORD wDayOfWeek;
  WORD wDay;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliseconds;
} SYSTEMTIME;
*/

//启停命令数据段数据结构
typedef struct _SysStartStopInfo {
    int op_flag; //命令类型  0x01:启动检测   0x02:停止检测
    int code_source_id; //编码源   可能存在两个编码信号来源 而 两个编码信号的单量可能不同
    int v_cut_type; //纵切刀类型 0x00:自动切刀  0x01:手动切刀
    int h_cut_id; //横切刀号 1,2,3,4
    int coating_flag; //镀膜标志 0x00:无膜  0x01:镀膜
    int shift_num; //班次
    int glass_lenght; //当前生产玻璃长度 单位：mm
    int glass_luminousness; //玻璃透光率 针对镀膜和非镀膜有不同的选项 和模板参数关联
    float glass_thicknes; //当前生产玻璃厚度 单位：mm

    float v_cut_pos[5]; //当前纵切刀位置（手动切刀时有效） 单位：mm
    int spurt_pos_valid[5 - 1]; //喷头是否有效
} SysStartStopInfo;

//缺陷检测参数数据结构
typedef struct _SysFlawDetectParam {
    float FlawPosAmd_Xmm; //缺陷X坐标修正 单位：mm
    float FlawPosAmd_Ymm; //缺陷Y坐标修正 单位：mm
    int FlawFilterMinLength; //缺陷图像高度大于该值不过滤
    int FakeCalcFlag; //假缺陷是否过滤 0：不过滤  1：过滤

    float FilterOpticPtsThre1; //核心计算变形点数过滤缺陷分段阈值
    float FilterOpticPtsThre2;
    float FilterOpticPtsThre3;
    float FilterOpticPtsThre4;
    float FilterOpticPtsThre5;

    float FilterMdptThre1; //核心计算 MDPT 过滤缺陷分段阈值
    float FilterMdptThre2;
    float FilterMdptThre3;
    float FilterMdptThre4;
    float FilterMdptThre5;

    //
    float FlawLengthSec1; //核心计算原始缺陷图高度 分段点，对应OpticDGate,mdpt阀值分段点
    float FlawLengthSec2;
    float FlawLengthSec3;
    float FlawLengthSec4;

    float CSizeAmendSec1; //缺陷核心长修正分段点一（单位：mm）
    float CSizeAmendSec2; //缺陷核心长修正分段点二（单位：mm）
    float CSizeAmendSec3; //缺陷核心长修正分段点三（单位：mm）
    float CSizeAmendSec4; //缺陷核心长修正分段点四（单位：mm）
    float CSizeAmendSec5; //缺陷核心长修正分段点五（单位：mm）
    float CSizeAmendSec6; //缺陷核心长修正分段点六（单位：mm）
    float CSizeAmendSec7; //缺陷核心长修正分段点七（单位：mm）

    float CSizeAmend_Kval1; //缺陷核心长小于等于分段点一的修正系数（缺陷核心修正系数一）
    float CSizeAmend_Kval2; //缺陷核心长小于等于分段点二的修正系数（缺陷核心修正系数二）
    float CSizeAmend_Kval3; //缺陷核心长小于等于分段点三的修正系数（缺陷核心修正系数三）
    float CSizeAmend_Kval4; //缺陷核心长小于等于分段点一的修正系数（缺陷核心修正系数四）
    float CSizeAmend_Kval5; //缺陷核心长小于等于分段点一的修正系数（缺陷核心修正系数五）
    float CSizeAmend_Kval6; //缺陷核心长小于等于分段点二的修正系数（缺陷核心修正系数六）
    float CSizeAmend_Kval7; //缺陷核心长小于等于分段点三的修正系数（缺陷核心修正系数七）
    float CSizeAmend_Kval8; //缺陷核心长小于等于分段点一的修正系数（缺陷核心修正系数八）

    float ReamSec1; //波筋修正值分段点一 （单位：度数）
    float ReamSec2; //波筋修正值分段点二 （单位：度数）
    float ReamSec3; //波筋修正值分段点三 （单位：度数）

    int ReamAmd1; //波筋度数小于等于分段点一的修正值（修正值一）
    int ReamAmd2; //波筋度数小于等于分段点一的修正值（修正值二）
    int ReamAmd3; //波筋度数小于等于分段点一的修正值（修正值三）
    int ReamAmd4; //波筋度数小于等于分段点一的修正值（修正值四）

    float Reserved[32]; //备用

} SysFlawDetectParam;

//系统运行参数
typedef struct _SysRunParam {
    //喷打抽样
    int MarkPosAmd; //喷打位置修正值 mm
    int MarkDelay; //玻璃开始喷打位置偏移 mm
    int SampleMarkFlag; //抽样模式，1表示长条抽样模式，非1表示打点抽样模式，默认是1
    int SampleMarkTime; //抽样长条模式打点持续时间，默认是3000
    int SampleMarkNum; //抽样打点模式点数，默认是4

    //180629 zkb add hvut pos param
    int HCutPos;
    int HCutPos1; //切刀1离检测设备的距离  mm
    int HCutPos2;
    int HCutPos3;
    int HCutPos4;

    //缺陷处理
    int GlassIgnoreL; //左边玻璃内不判等距离
    int GlassIgnoreR; //右边玻璃内不判等距离

    int Combine_X_Pix; //缺陷合并X方向允许像元数
    int Combine_Y_Code; //缺陷合并Y方向允许编码数
    int Combine_Wait_Code; //与最新的缺陷的编码差值超过该值则将等待合并缺陷取出，不再等待合并
    int Combine_Wait_Time; //等待合并时间超过该值则将等待合并缺陷取出，不再等待合并 （ms）
    int Combine_Wait_Length; //待合并缺陷长度超过该值则取出（mm）
    int Combine_Wait_Width; //待合并缺陷宽度超过该值则取出（mm）
    int Combine_Wait_FlawNum; //待合并缺陷数量超过该值则取出
    float ConfirmClassifyWeight; //当分类器计算得出的权重大于该值时，直接使用该权重对应的类型

    int FilterLWRatio; //缺陷过滤长宽比  长宽比超过该值则过滤
    int FlawPosCalcFlag; //缺陷位置运算方法，1表示取缺陷中间位置，0表示取缺陷结束位置，默认是1
    int MdptCalcPeriod; //条纹周期 0表示8周期，  1表示 12周期，非1表示16周期
    int GGradeRoundFlag; //玻璃等级判定是否四舍五入

    int RefLineFlag; //如果使用平场校正，则直接使用128，否则使用标准行  1为使用标准行

    //玻璃边压花
    int EdgeCalcOutCount; //更新玻璃边与压痕的运算次数
    int EdgePosAmd_L; //玻璃原左边缘位置修正值
    int EdgePosAmd_R; //玻璃原右边缘位置修正值
    int KnurlingValidDis_Cut; //压花到玻璃边的距离不能超过该值 mm
    int KnurlingDis_Edge; //外压痕与玻璃边缘间隔像素值，默认是200 检测到玻璃边后 从玻璃边往玻璃内部偏移KnurlingDis_Edge个像元开始查找外压花
    int KnurlingPosAmd_IL; //玻璃左压痕内侧位置修正值
    int KnurlingPosAmd_IR; //玻璃右压痕内侧位置修正值
    int KnurlingPosAmd_OL; //玻璃左压痕外侧位置修正值，默认是0
    int KnurlingPosAmd_OR; //玻璃右压痕外侧位置修正值，默认是0

    //报警功能参数
    int BrokenJudgeMinWidth; //图像宽度和长度要大于该值才进行炸板判断(像元)
    int BrokenJudgeMinLength;
    int BrokenDiffThre; //求炸板无玻璃区域时与标准行差分大于该值认为有效（灰度）
    int BrokenPersistTime; //在该时间段内持续出现炸板缺陷则认为已炸板（ms)
    int BrokenFlawNumThre; //在持续时间内出现超过该数量的炸板缺陷则任务炸板

    int CameraCurveAlarmMin; //相机曲线平均高度低于该值报警
    int CameraCurveAlarmMax; //相机曲线平均高度高于该值报警
    int KnurlingAlarmDisThre; //内压痕到切刀范围以内的时候，统计距离切刀距离小于该值的缺陷的个数
    int AlarmKeepTime; //报警持续时间 单位：s

    //系统调试功能
    int LogSwitch; //日志记录选择
    int SaveFlawFlag; //是否将缺陷保存为文件 1：保存  0：不保存
    float SaveFlawSizeThre; //将缺陷核心大于该值的保存

} SysRunParam;

//返回数据包格式
typedef struct _SingleRealLine {
    unsigned short int line_count; //行号
    unsigned char frame_num; //帧号
    unsigned char field_id; //场id
    unsigned char line_data[8188]; //图像数据
} SingleRealLine;
typedef struct _DataPack {
    //来自哪个相机
    unsigned int cameraID;

    //数据包ID
    unsigned short AssistID;

    //场的数量，最小值为1
    unsigned short Field_Size;

    //帧计数寄存器
    unsigned short Frame_cnt;

    //当前刀计数
    unsigned short CutNum;

    //刀头锁存编码值
    unsigned int CutCodeNum;

    //帧头锁存编码值
    unsigned int FrameCodeNum;

    //x方向起有效窗口始坐标设定值
    unsigned short Start_Win;

    //x方向有效窗口终止坐标设定值
    unsigned short End_win;

    // 行数量 用来标明每场有几行有效数据 用来兼容数据包里没有累加行的相机版本 [5/18/2017 Administrator]
    unsigned int Line_Num;

    //状态寄存器1~16
    unsigned int Status[16];

    SingleRealLine lineData[3 * MAX_DATA_PACK_ROW_NUE_PER_FIELD]; //参考行和实时行的数据 1行参考行+1行实时行+1行累加行
} DataPack;

//返回Mdpt曲线数据结构
typedef struct _MDPTCurve {
public:
    unsigned int cameraID; //所属于的下位机
    unsigned short FrameNum; //当前帧号
    unsigned short X_Win_S; //X有效像素起始点
    unsigned short X_Win_E; //X有效像素结束点
    unsigned long CutNum; //切刀计数
    unsigned long CutCodeNum; //切刀锁存编码
    unsigned long FrameCodeNum; //当前帧头锁存编码值

    float MDPTRow[7450];

} MDPTCurve;

enum FLAWTYPE //缺陷种类
{
    Noinit = -1 /*假缺陷*/,
    Bubble = 1 /*气泡*/,
    Stone = 2 /*结石*/,
    Ream = 3 /*波筋*/,
    Burl = 4 /*光变*/,
    Scaffolding = 5 /*结瘤*/,
    Line = 6 /*线道*/,
    Sulfide = 7 /*硫化物*/
    ,
    Lknurling = 8 /*左内压花*/,
    Rknurling = 9 /*右内压花*/,
    LEdge = 10 /*左玻璃边*/,
    REdge = 11 /*右玻璃边*/
    ,
    OLknurling = 12,
    ORknurling = 13,
    Dust = 16,
    Unknow = 20,
    TooMuch = 21,
    OtherType = 22
};

typedef struct _SimpleFlawInfo {
    unsigned int CameraID; //所属于的下位机
    unsigned int FlawGrade; //缺陷等级
    unsigned short FlawID; //缺陷包的ID
    unsigned short FrameNum; //缺陷所在帧号
    unsigned long CutNum; //缺陷结束时切刀计数
    unsigned long CutCodeNum; //刀头锁存编码值
    unsigned long FrameCodeNum; //缺陷结束时帧头编码值
    unsigned short Xs; //缺陷起始X坐标
    unsigned short Ys; //缺陷起始Y坐标
    unsigned short Xe; //缺陷结束X坐标
    unsigned short Ye; //缺陷结束Y坐标
    unsigned short SendWidth; //缺陷图片实际宽度
    unsigned short SendHeigh; //缺陷图片实际长度
    unsigned short CutFlag; //缺陷截断标志
    unsigned short int mix_Xs; //实际起始X坐标
    unsigned short int mix_Ys; //实际起始Y坐标
    unsigned short int mix_Xe; //实际结束X坐标
    unsigned short int mix_Ye; //实际结束Y坐标
    unsigned short int mix_Width; //实际宽度
    unsigned short int mix_Height; //实际高度
    unsigned int mix_Gsum; //像素灰度总和
    unsigned short int mix_FNumsum; //缺陷点像素个数和

    unsigned long ServerPusle; //保存组包时操作系统tick
    unsigned long Pulse; //缺陷的全局编码脉冲
    FLAWTYPE Type; //缺陷类型
    long X; //缺陷全局X值mm
    float CWidth; //缺陷核心宽mm
    float CLenth; //缺陷核心长mm
    float VWidth; //缺陷变形宽mm
    float VLenth; //缺陷变形长mm，波筋的时候为度数
    float Feature[40]; //特征值

} SimpleFlawInfo;
typedef struct _ShowFlawPack {
    SimpleFlawInfo simpleFlawInfo;
    unsigned char StdRow_1[256];
    unsigned char StdRow_2[256];
    unsigned char StdRow_3[256];
    unsigned char DataFlaw_1[256][256]; //
    unsigned char DataFlaw_2[256][256]; //
    unsigned char DataFlaw_3[256][256]; //

} ShowFlawPack;

//返回玻璃信息结构定义
enum GLASS_TYPE { G_A = 1,
    G_B,
    G_C,
    G_D,
    G_Z };
typedef struct _GlassInfo {
    char GlassID[32]; //玻璃ID
    int Grade; //玻璃等级
    int Width; //玻璃板宽
    int Lenth; //玻璃板长
    float Thick; //玻璃厚度
    GLASS_TYPE pos; //左板or右板
    int Sample; //抽样
    long Sp; //玻璃板起始编码脉冲
    long Ep; //玻璃板结束编码脉冲
    int LeftSide; //左边位置
    float Speed; //速度
    DWORD Batch; //批次
    int Reason; // 降等原因
    int ValidCutNum; //有效切刀数
    SYSTEMTIME time; //生成时间
} GlassInfo;

//返回切刀信息数据结构定义
typedef struct _NetVCut {
    float Cut[5];
} NetVCut;

//相机状体信息数据结构定义
typedef struct _CameraStatus {
    int cameraID;
    int curStatus; //状态1：正常 2：断开
    float curTemp; //温度
} CameraStatus;

/////////////////////////////////////////////////////////////////////////////////
//-liuhao 1227
//抽样玻璃板
typedef struct _SampleGlass {
    unsigned char GlassID[32]; //玻璃ID
    unsigned long Sp; //玻璃板起始编码脉冲
    unsigned long Ep; //玻璃板结束编码脉冲

} SampleGlass;

typedef struct _TaskInfo {
    unsigned long taskSearchID; //任务搜索ID -- 任务编码值
    unsigned char taskType; // 任务类型：0x01，固定喷打
    unsigned char portAddr; //任务端口地址，取值0x00~0x07对应喷打端口0~7.
    unsigned short opCode; //任务操作码 0x01喷打
    unsigned long opData0; //喷打点数
    unsigned long opData1; //喷打点间距
    unsigned long opData2; //喷打点持续时间
    unsigned long opData3; //undef
    unsigned long opData4; //undef
    unsigned long opData5; //undef
} TaskInfo;
////////////////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

//show
enum DrawFlawType {
    Triangle = 1, //三角形
    InnerStar = 2, //星
    OuterStar = 3, //星
    Cross = 4, //叉
    Diamond = 5, //菱形
    Hexagon = 6, //六边形
    QuestionMark = 7, //问号
    PressMark = 8, //压痕
    CircleMark = 9, //圆
    SvgStar = 10, //star svg
    TriStar = 11,
    QuarStar = 12,
    EightStar = 13,
    RectangleMark = 14,
    RhombusMark = 15,
    ReserveType = 255
};

#endif // FLAWDEFINE_H
