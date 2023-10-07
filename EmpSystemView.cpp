
// EmpSystemView.cpp: CEmpSystemView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "EmpSystem.h"
#endif

#include "EmpSystemDoc.h"
#include "EmpSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEmpSystemView

IMPLEMENT_DYNCREATE(CEmpSystemView, CView)

BEGIN_MESSAGE_MAP(CEmpSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEmpSystemView 构造/析构

CEmpSystemView::CEmpSystemView() noexcept
{
	// TODO: 在此处添加构造代码

}

CEmpSystemView::~CEmpSystemView()
{
}

BOOL CEmpSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEmpSystemView 绘图

void CEmpSystemView::OnDraw(CDC* /*pDC*/)
{
	CEmpSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CEmpSystemView 打印

BOOL CEmpSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEmpSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEmpSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CEmpSystemView 诊断

#ifdef _DEBUG
void CEmpSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CEmpSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEmpSystemDoc* CEmpSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEmpSystemDoc)));
	return (CEmpSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CEmpSystemView 消息处理程序
