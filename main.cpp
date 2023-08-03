// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <DApplication>
#include <QDir>
#include <QVBoxLayout>

#include <DListView>
#include <DBlurEffectWidget>
#include <DTitlebar>
#include <DWidgetUtil>
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.setApplicationVersion("1.0");
    a.setProductIcon(QIcon::fromTheme("audio-volume-muted"));
    a.setWindowIcon(QIcon::fromTheme("audio-volume-muted"));

    DBlurEffectWidget w;
    QVBoxLayout *lay = new QVBoxLayout(&w);

    DListView *iconView = new DListView(&w);
    iconView->setSpacing(20);
    iconView->setIconSize({64, 64});
    iconView->setItemSize({160, 160});
    iconView->setViewMode(DListView::IconMode);
    iconView->setOrientation(DListView::LeftToRight, true);
    iconView->setResizeMode(DListView::Adjust);
//    iconView->setEditTriggers(DListView::NoEditTriggers);
    iconView->setDragEnabled(false);

    QStandardItemModel *model = new QStandardItemModel;
    iconView->setModel(model);

    auto addIcons = [&](const QString &path){
        QStringList types = {"actions", "icons", "texts"};
        for (auto iconType : types) {
            QDir dir(path);
            dir.cd(iconType);
            for (const auto &file : dir.entryList()) {
                auto iconName = QFileInfo(file).baseName();
                // edit_copy_16px ==> edit_copy
                iconName = iconName.left(iconName.lastIndexOf("_"));
                DStandardItem *item = new DStandardItem(iconName);
                item->setToolTip(iconName);
                item->setIcon(QIcon::fromTheme(iconName));
                model->appendRow(item);
            }
        }
    };

    addIcons(":/icons/deepin/builtin/");
    addIcons(":/icons/deepin/builtin/dark");
    addIcons(":/icons/deepin/builtin/light");

    auto tb = new DTitlebar;
    tb->setIcon(QIcon::fromTheme("password_show"));
    tb->setTitle("builtin icons viewer");
    tb->setBackgroundTransparent(true);
    lay->addWidget(tb);
    lay->addWidget(iconView);
    w.show();

    w.resize(820, 680);
    moveToCenter(&w);

    return a.exec();
}
