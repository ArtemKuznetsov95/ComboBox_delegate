#include "SelectionLayersMap.h"
#include "ui_SelectionLayersMap.h"

SelectionLayersMap::SelectionLayersMap(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SelectionLayersMap)
{
    ui->setupUi(this);
    m_combo = new MyComboBox(this);
    m_combo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);

    ui->horizontalLayout->addWidget(m_combo);

    m_model = new QStandardItemModel;
    m_combo->setModel(m_model);

    completionList();   //Заполняем лист слоями
    updateModel();      //Обновляем модель

    connect(this, &SelectionLayersMap::dataChange, this, &SelectionLayersMap::checkFlags); //Перехватываем событие checkbox
//    connect(,,this,&SelectionLayersMap::setCheckedFlags(uint cod));   //Установить слой
//    connect(,,this,&SelectionLayersMap::setUncheckedFlags(uint cod)); //Убрать слой

    MyLineEdit* myLineEdit = new MyLineEdit(m_combo);
    m_combo->setLineEdit(myLineEdit);
    m_combo->setCurrentIndex(-1);
    m_combo->setEditable(true);

    m_combo->lineEdit()->setText("Слои: ");
    m_combo->lineEdit()->setReadOnly(true);

    m_combo->lineEdit()->installEventFilter(myLineEdit);
}

SelectionLayersMap::~SelectionLayersMap()
{
    delete ui;
}

void SelectionLayersMap::addItem(MBP::ModelBPLayerType* itemList, QStandardItem* itemModel)
{
    itemModel->setCheckable(true);
    itemModel->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    itemModel->setData(Qt::Unchecked, Qt::CheckStateRole);
    itemModel->setData(static_cast<unsigned int>(*itemList), MyBPLayerType::m_cod);

    QString _title = translateLines(*itemList);
    itemModel->setText(_title);
}

void SelectionLayersMap::updateModel()
{
    for(auto item : m_listItems) {
        QStandardItem* itemModel = new QStandardItem();
        addItem(&item, itemModel);
        m_model->appendRow(itemModel);
    }

    connect(m_model, &QStandardItemModel::dataChanged, [&](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()){
        (void)bottomRight;
        (void)roles;

        QStandardItem* currentItem = m_model->item(topLeft.row());

        if(currentItem->checkState() == Qt::Checked){
            setCheckedFlags(currentItem->data(MyBPLayerType::m_cod).toUInt());
            emit dataChange();
        } else {
            setUncheckedFlags(currentItem->data(MyBPLayerType::m_cod).toUInt());
            emit dataChange();
        }
        });

    DelegateComboBox* delegate = new DelegateComboBox(m_model, this);
    m_combo->setItemDelegate(delegate);
    m_combo->setModel(m_model);
}

void SelectionLayersMap::completionList()
{
    m_listItems = {
    MBP::ModelBPLayerType::MBP_LT_ZONE_DESTROY,
    MBP::ModelBPLayerType::MBP_LT_ZONE_IMPACT,
    MBP::ModelBPLayerType::MBP_LT_ZONE_TIME,
    MBP::ModelBPLayerType::MBP_LT_ZONE_RECON,
    MBP::ModelBPLayerType::MBP_LT_ZONE_INFO,
    MBP::ModelBPLayerType::MBP_LT_ZONE_SUP,
    MBP::ModelBPLayerType::MBP_LT_NAVI_MODE,
    MBP::ModelBPLayerType::MBP_LT_GEO,
    MBP::ModelBPLayerType::MBP_LT_GEO_RELIEF,
    MBP::ModelBPLayerType::MBP_LT_GEO_PRIMING,
    MBP::ModelBPLayerType::MBP_LT_GEO_MAGNETIC,
    MBP::ModelBPLayerType::MBP_LT_GEO_GRAVITY,
    MBP::ModelBPLayerType::MBP_LT_GIDRO,
    MBP::ModelBPLayerType::MBP_LT_GIDRO_FLOW,
    MBP::ModelBPLayerType::MBP_LT_GIDRO_TEMP,
    MBP::ModelBPLayerType::MBP_LT_GIDRO_SOUND,
    MBP::ModelBPLayerType::MBP_LT_GIDRO_TIDES,
    MBP::ModelBPLayerType::MBP_LT_METEO,
    MBP::ModelBPLayerType::MBP_LT_METEO_CLOUD,
    MBP::ModelBPLayerType::MBP_LT_METEO_AIR,
    MBP::ModelBPLayerType::MBP_LT_METEO_WIND,
    MBP::ModelBPLayerType::MBP_LT_METEO_RAIN,
    MBP::ModelBPLayerType::MBP_LT_METEO_VISIB,
    MBP::ModelBPLayerType::MBP_LT_METEO_FREEZ,
    MBP::ModelBPLayerType::MBP_LT_METEO_GMY,
    MBP::ModelBPLayerType::MBP_LT_ICE,
    MBP::ModelBPLayerType::MBP_LT_ICE_COVER,
    MBP::ModelBPLayerType::MBP_LT_ICE_EDGE
    };
}

void SelectionLayersMap::setCheckedFlags(uint cod)
{
   m_flags |= static_cast<unsigned int>(cod);
}

void SelectionLayersMap::setUncheckedFlags(uint cod)
{
    m_flags &= ~static_cast<unsigned int>(cod);
}

QList<unsigned int> SelectionLayersMap::getListCheckLayer()
{
    m_listCheckLayer.clear();
    for (auto sloi : m_listItems) {
        if(((m_flags & (static_cast<unsigned int>(sloi))) ? true : false))
            m_listCheckLayer.append(static_cast<unsigned int>(sloi));
    }
    return m_listCheckLayer;
}

unsigned int SelectionLayersMap::getBitMaskLayer()
{
    return m_flags;
}

void SelectionLayersMap::checkFlags()
{
    for (auto sloi : m_listItems) {
        QString _title = translateLines(sloi);
        if(((m_flags & (static_cast<unsigned int>(sloi))) ? true : false))
            qDebug() << _title << "Слой включен!";
    }
}

QString SelectionLayersMap::translateLines(MBP::ModelBPLayerType cod)
{
    QString _title;
    switch(cod){
    case MBP::ModelBPLayerType::MBP_LT_ZONE_DESTROY:    _title = "1. Зон поражения оружием ОБП"; break;
    case MBP::ModelBPLayerType::MBP_LT_ZONE_IMPACT:     _title = "2. Областей боевого воздействия"; break;
    case MBP::ModelBPLayerType::MBP_LT_ZONE_TIME:       _title = "3. Временных матриц количества средств поражения от ОБП на прогнозируемый период с учётом параметров области обеспечения боевых действий"; break;
    case MBP::ModelBPLayerType::MBP_LT_ZONE_RECON:      _title = "4. Зон обнаружения ОБП"; break;
    case MBP::ModelBPLayerType::MBP_LT_ZONE_INFO:       _title = "5. Областей информационного взаимодействия"; break;
    case MBP::ModelBPLayerType::MBP_LT_ZONE_SUP:        _title = "6. Областей обеспечения продовольствия, БЗ и ГСМ"; break;
    case MBP::ModelBPLayerType::MBP_LT_NAVI_MODE:       _title = "7. Данные для обеспечения режима плавания"; break;
    case MBP::ModelBPLayerType::MBP_LT_GEO:             _title = "8. Геофизические данные"; break;
    case MBP::ModelBPLayerType::MBP_LT_GEO_RELIEF:      _title = "8.1 Данные о рельефе дна"; break;
    case MBP::ModelBPLayerType::MBP_LT_GEO_PRIMING:     _title = "8.2 Грунт морского дна"; break;
    case MBP::ModelBPLayerType::MBP_LT_GEO_MAGNETIC:    _title = "8.3 Параметры магнитного поля Земли"; break;
    case MBP::ModelBPLayerType::MBP_LT_GEO_GRAVITY:     _title = "8.4 Параметры гравитационного поля Земли"; break;
    case MBP::ModelBPLayerType::MBP_LT_GIDRO:           _title = "9. Гидрофизические данные"; break;
    case MBP::ModelBPLayerType::MBP_LT_GIDRO_FLOW:      _title = "9.1 Параметры течений"; break;
    case MBP::ModelBPLayerType::MBP_LT_GIDRO_TEMP:      _title = "9.2 Температура, плотность, соленость морской воды"; break;
    case MBP::ModelBPLayerType::MBP_LT_GIDRO_SOUND:     _title = "9.3 Скорость звука в воде"; break;
    case MBP::ModelBPLayerType::MBP_LT_GIDRO_TIDES:     _title = "9.4 Колебания уровня и приливы"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO:           _title = "10. Метеорологические данные"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO_CLOUD:     _title = "10.1 Параметры облачности"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO_AIR:       _title = "10.2 Температура и влажность воздуха"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO_WIND:      _title = "10.3 Характеристики приводного ветра и волнения моря"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO_RAIN:      _title = "10.4 Осадки"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO_VISIB:     _title = "10.5 Видимость"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO_FREEZ:     _title = "10.6 Брызговое обледенение"; break;
    case MBP::ModelBPLayerType::MBP_LT_METEO_GMY:       _title = "10.7 Опасные ГМЯ"; break;
    case MBP::ModelBPLayerType::MBP_LT_ICE:             _title = "11. Данные ледяного покрова"; break;
    case MBP::ModelBPLayerType::MBP_LT_ICE_COVER:       _title = "11.1 Данные ледяного покрова"; break;
    case MBP::ModelBPLayerType::MBP_LT_ICE_EDGE:        _title = "11.2 Данные ледяной кромки"; break;
    }
    return _title;
}


