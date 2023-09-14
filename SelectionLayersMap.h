#ifndef SELECTIONLAYERSMAP_H
#define SELECTIONLAYERSMAP_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include <QLineEdit>
#include <bitset>

#include <../bazis/modelbp/model/MBPEnums.h>
#include "DelegateComboBox.h"
#include "MyComboBox.h"
#include "MyLineEdit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SelectionLayersMap; }
QT_END_NAMESPACE

///
/// \brief The SelectionLayersMap class - Класс Списка слоев
///
class SelectionLayersMap : public QWidget
{
    Q_OBJECT
    enum MyBPLayerType {
        m_cod = Qt::UserRole+1, //!< Код слоя
    };
signals:
    ///
    /// \brief dataChange - Сигнал изменения в списке слоев
    ///
    void dataChange();

public:
    SelectionLayersMap(QWidget *parent = nullptr);
    ~SelectionLayersMap();
public:
    ///
    /// \brief getListCheckLayer    - Функция возращает список включенных слоев
    /// \return                     - Лист кодов включенных слоев
    ///
    QList<unsigned int> getListCheckLayer();
    ///
    /// \brief getBitMaskLayer      - Функция возращает битовую маску
    /// \return                     - Битовая маска
    ///
    unsigned int getBitMaskLayer();

private slots:
    ///
    /// \brief addItem      - Функция добавления элемента модели
    /// \param itemList     - Код слоя
    /// \param itemModel    - Элемент для вставки в модель
    ///
    void addItem(MBP::ModelBPLayerType* itemList, QStandardItem *itemModel);
    ///
    /// \brief completionList   - Функция вспомогательная, для создания списка слоев
    ///
    void completionList();
    ///
    /// \brief updateModel      - Функция обновления модели
    ///
    void updateModel();
    ///
    /// \brief setCheckedFlags  - Функция установливает флаг в битовую маску
    /// \param cod              - Код слоя
    ///
    void setCheckedFlags(uint cod);
    ///
    /// \brief setUncheckedFlags    - Функция снимает флаг с битовой маске
    /// \param cod                  - Код слоя
    ///
    void setUncheckedFlags(uint cod);
    ///
    /// \brief checkFlags           - Функция вспомогательная, для вывода включенных слоев
    ///
    void checkFlags();
    ///
    /// \brief translateLines       - Функция переводит код в название слоя
    /// \param cod                  - Код слоя
    /// \return
    ///
    QString translateLines(MBP::ModelBPLayerType cod);

private:
    Ui::SelectionLayersMap *ui;
    QStandardItemModel* m_model;                    //!< Модель списка слоев
    unsigned int m_flags {0x00000000};              //!< Битовая маска
    QList<MBP::ModelBPLayerType> m_listItems;       //!< Список всех слоев
    QList<unsigned int> m_listCheckLayer;           //!< Список включенных слоев
    MyComboBox* m_combo;                            //!< Переопределенный combobox
};

#endif // SELECTIONLAYERSMAP_H
