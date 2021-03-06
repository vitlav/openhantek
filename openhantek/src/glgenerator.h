// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include <deque>

#include <QGLFunctions>
#include <QObject>

#include "analyse/dataanalyzerresult.h"
#include "scopesettings.h"
#include "viewconstants.h"
#include "viewsettings.h"
class GlScope;

////////////////////////////////////////////////////////////////////////////////
/// \class GlGenerator
/// \brief Generates the vertex arrays for the GlScope classes.
class GlGenerator : public QObject {
    Q_OBJECT

  public:
    /// \brief Initializes the scope widget.
    /// \param settings The target settings object.
    /// \param parent The parent widget.
    GlGenerator(DsoSettingsScope *scope, DsoSettingsView *view);
    void generateGraphs(const DataAnalyzerResult *result);
    const std::vector<GLfloat> &channel(int mode, unsigned channel, unsigned index) const;
    const std::vector<GLfloat> &grid(int a) const;
    bool isReady() const;

  private:
    typedef std::tuple<unsigned,unsigned,unsigned> PrePostStartTriggerSamples;
    typedef std::vector<GLfloat> DrawLines;
    typedef std::deque<DrawLines> DrawLinesWithHistory;
    typedef std::vector<DrawLinesWithHistory> DrawLinesWithHistoryPerChannel;
    DrawLinesWithHistoryPerChannel vaChannel[Dso::CHANNELMODE_COUNT];

    PrePostStartTriggerSamples computeSoftwareTriggerTY(const DataAnalyzerResult *result);
    DsoSettingsScope *settings;
    DsoSettingsView *view;
    std::vector<GLfloat> vaGrid[3];
    bool ready = false;

    const SampleValues &useSamplesOf(int mode, unsigned channel, const DataAnalyzerResult *result) const;
  signals:
    void graphsGenerated(); ///< The graphs are ready to be drawn
};
