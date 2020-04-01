#include "filebrowse.h"

#include <QPushButton>
#include <QDateTime>
#include <QDebug>

#include "ui_filebrowse.h"

static const QString s_file_dir = "./xml";
static const QStringList s_fileters = {"*.xml"};

FileBrowse::FileBrowse(QWidget *parent) : QDialog(parent), ui(new Ui::FileBrowse), file_property_(nullptr)
{
    ui->setupUi(this);
    // 设置背景（不设置背景则会透明）
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("FileBrowse {background: white;}");

    initTableWidget();

    connect(ui->ok, &QPushButton::clicked, this, &FileBrowse::onClickOK);
    connect(ui->cancel, &QPushButton::clicked, this, &FileBrowse::onClickCancel);

    showIs();
}

FileBrowse::~FileBrowse()
{
}

void FileBrowse::initTableWidget()
{
    // 初始化表格
    ui->tableWidget->setColumnCount(4);
    const QStringList table_widget_head = {"想定名称", "创建时间", "最后修改时间", "备注"};
    ui->tableWidget->setHorizontalHeaderLabels(table_widget_head);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setHidden(true);                   // 隐藏行号
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择模式，选择单行
    ui->tableWidget->setShowGrid(false);                                  //设置不显示格子线
    QFont font = ui->tableWidget->horizontalHeader()->font();             //先获取字体
    font.setBold(true);                                                   //字体设置为粗体
    ui->tableWidget->horizontalHeader()->setFont(font);                   //设置每一列的标题字体为粗体
}

void FileBrowse::showIs()
{
    ui->tableWidget->clearContents(); // 清空非表头内容
    /* bool result =  */ scanDataFile(s_file_dir, s_fileters);
}

// 获取目录下某种类型的问题
bool FileBrowse::scanDataFile(const QDir &from_dir, const QStringList &filters)
{
    QFileInfoList file_info_list = from_dir.entryInfoList(filters, QDir::AllDirs | QDir::Files);
    foreach (QFileInfo file_info, file_info_list)
    {
        if (file_info.fileName() == "." || file_info.fileName() == "..")
            continue;
        if (file_info.isDir())
        {
            if (!scanDataFile(file_info.filePath(), filters))
                return false;
        }
        else
        {
            QStringList file_property;
            file_property << file_info.fileName() << file_info.birthTime().toString("yyyy-MM-dd hh:mm:ss")
                          << file_info.lastRead().toString("yyyy-MM-dd hh:mm:ss") << "";
            addTableWidgetRow(file_property);
        }
    }
    return true;
}

// 表格添加条目
void FileBrowse::addTableWidgetRow(const QStringList &data)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    for (int i = 0; i < 4; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(data.at(i));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, i, item);
    }
}
