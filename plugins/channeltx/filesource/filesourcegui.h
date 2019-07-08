///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef PLUGINS_CHANNELTX_FILESOURCE_FILESOURCEGUI_H_
#define PLUGINS_CHANNELTX_FILESOURCE_FILESOURCEGUI_H_

#include <QTime>

#include "plugin/plugininstancegui.h"
#include "dsp/channelmarker.h"
#include "gui/rollupwidget.h"
#include "util/messagequeue.h"

#include "filesourcesettings.h"

class PluginAPI;
class DeviceUISet;
class BasebandSampleSource;
class FileSource;

namespace Ui {
    class FileSourceGUI;
}

class FileSourceGUI : public RollupWidget, public PluginInstanceGUI {
    Q_OBJECT

public:
    static FileSourceGUI* create(PluginAPI* pluginAPI, DeviceUISet *deviceUISet, BasebandSampleSource *channelTx);
    virtual void destroy();

    void setName(const QString& name);
    QString getName() const;
    virtual qint64 getCenterFrequency() const;
    virtual void setCenterFrequency(qint64 centerFrequency);

    void resetToDefaults();
    QByteArray serialize() const;
    bool deserialize(const QByteArray& data);
    virtual MessageQueue *getInputMessageQueue() { return &m_inputMessageQueue; }
    virtual bool handleMessage(const Message& message);

public slots:
    void channelMarkerChangedByCursor();

private:
    Ui::FileSourceGUI* ui;
    PluginAPI* m_pluginAPI;
    DeviceUISet* m_deviceUISet;
    ChannelMarker m_channelMarker;
    FileSourceSettings m_settings;
    int m_sampleRate;
    double m_shiftFrequencyFactor; //!< Channel frequency shift factor
    QString m_fileName;
    int m_fileSampleRate;
    quint32 m_fileSampleSize;
    quint64 m_recordLength;
    quint64 m_startingTimeStamp;
    quint64 m_samplesCount;
    bool m_acquisition;
  	bool m_enableNavTime;
    bool m_doApplySettings;

    FileSource* m_fileSource;
    MessageQueue m_inputMessageQueue;

    QTime m_time;
    uint32_t m_tickCount;

    explicit FileSourceGUI(PluginAPI* pluginAPI, DeviceUISet *deviceUISet, BasebandSampleSource *channelTx, QWidget* parent = nullptr);
    virtual ~FileSourceGUI();

    void blockApplySettings(bool block);
    void applySettings(bool force = false);
    void applyChannelSettings();
    void configureFileName();
	void updateWithAcquisition();
	void updateWithStreamData();
	void updateWithStreamTime();
    void displaySettings();
    void displayRateAndShift();

    void leaveEvent(QEvent*);
    void enterEvent(QEvent*);

    void applyInterpolation();
    void applyPosition();

private slots:
    void handleSourceMessages();
    void onWidgetRolled(QWidget* widget, bool rollDown);
    void onMenuDialogCalled(const QPoint& p);
    void on_interpolationFactor_currentIndexChanged(int index);
    void on_position_valueChanged(int value);
	void on_showFileDialog_clicked(bool checked);
	void on_playLoop_toggled(bool checked);
	void on_play_toggled(bool checked);
	void on_navTime_valueChanged(int value);

    void tick();
};


#endif /* PLUGINS_CHANNELTX_FILESOURCE_FILESOURCEGUI_H_ */