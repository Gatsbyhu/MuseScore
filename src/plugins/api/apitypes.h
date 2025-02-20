/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MU_PLUGINS_APITYPES_H
#define MU_PLUGINS_APITYPES_H

#include <QObject>

#include "engraving/types/types.h"

namespace Ms::PluginAPI {
Q_NAMESPACE

enum class OrnamentStyle : char {
    DEFAULT = int(mu::engraving::OrnamentStyle::DEFAULT),
    BAROQUE = int(mu::engraving::OrnamentStyle::BAROQUE)
};
Q_ENUM_NS(OrnamentStyle);

enum class Align : char {
    LEFT     = char(mu::engraving::Align::LEFT),
    RIGHT    = char(mu::engraving::Align::RIGHT),
    HCENTER  = char(mu::engraving::Align::HCENTER),
    TOP      = char(mu::engraving::Align::TOP),
    BOTTOM   = char(mu::engraving::Align::BOTTOM),
    VCENTER  = char(mu::engraving::Align::VCENTER),
    BASELINE = char(mu::engraving::Align::BASELINE),
    CENTER = Align::HCENTER | Align::VCENTER,
    HMASK  = Align::LEFT | Align::RIGHT | Align::HCENTER,
    VMASK  = Align::TOP | Align::BOTTOM | Align::VCENTER | Align::BASELINE
};
Q_ENUM_NS(Align);

//! NOTE just Placement for compatibility
enum class Placement {
    ABOVE = int(mu::engraving::PlacementV::ABOVE),
    BELOW = int(mu::engraving::PlacementV::BELOW),
};
Q_ENUM_NS(Placement);

enum class Direction {
    AUTO = int(mu::engraving::DirectionV::AUTO),
    UP   = int(mu::engraving::DirectionV::UP),
    DOWN = int(mu::engraving::DirectionV::DOWN),
};
Q_ENUM_NS(Direction);

enum class DirectionH {
    AUTO  = int(mu::engraving::DirectionH::AUTO),
    LEFT  = int(mu::engraving::DirectionH::LEFT),
    RIGHT = int(mu::engraving::DirectionH::RIGHT),
};
Q_ENUM_NS(DirectionH);

enum class LayoutBreakType {
    PAGE = int(mu::engraving::LayoutBreakType::PAGE),
    LINE = int(mu::engraving::LayoutBreakType::LINE),
    SECTION = int(mu::engraving::LayoutBreakType::SECTION),
    NOBREAK = int(mu::engraving::LayoutBreakType::NOBREAK),
};
Q_ENUM_NS(LayoutBreakType);

enum class VeloType {
    OFFSET_VAL = int(mu::engraving::VeloType::OFFSET_VAL),
    USER_VAL = int(mu::engraving::VeloType::USER_VAL),
};
Q_ENUM_NS(VeloType);

enum class BeamMode {
    AUTO = int(mu::engraving::BeamMode::AUTO),
    BEGIN = int(mu::engraving::BeamMode::BEGIN),
    MID = int(mu::engraving::BeamMode::MID),
    END = int(mu::engraving::BeamMode::END),
    NONE = int(mu::engraving::BeamMode::NONE),
    BEGIN32 = int(mu::engraving::BeamMode::BEGIN32),
    BEGIN64 = int(mu::engraving::BeamMode::BEGIN64),
    INVALID = int(mu::engraving::BeamMode::INVALID),
};
Q_ENUM_NS(BeamMode);

enum class GlissandoStyle {
    CHROMATIC = int(mu::engraving::GlissandoStyle::CHROMATIC),
    WHITE_KEYS = int(mu::engraving::GlissandoStyle::WHITE_KEYS),
    BLACK_KEYS = int(mu::engraving::GlissandoStyle::BLACK_KEYS),
    DIATONIC = int(mu::engraving::GlissandoStyle::DIATONIC),
    PORTAMENTO = int(mu::engraving::GlissandoStyle::PORTAMENTO),
};
Q_ENUM_NS(GlissandoStyle);

enum class NoteHeadType {
    HEAD_AUTO = int(mu::engraving::NoteHeadType::HEAD_AUTO),
    HEAD_WHOLE = int(mu::engraving::NoteHeadType::HEAD_WHOLE),
    HEAD_HALF = int(mu::engraving::NoteHeadType::HEAD_HALF),
    HEAD_QUARTER = int(mu::engraving::NoteHeadType::HEAD_QUARTER),
    HEAD_BREVIS = int(mu::engraving::NoteHeadType::HEAD_BREVIS),
    HEAD_TYPES = int(mu::engraving::NoteHeadType::HEAD_TYPES),
};
Q_ENUM_NS(NoteHeadType);

//! HACK to force the build system to run moc on this file
class Mops : public QObject
{
    Q_GADGET
};
}

Q_DECLARE_METATYPE(Ms::PluginAPI::OrnamentStyle);
Q_DECLARE_METATYPE(Ms::PluginAPI::Align);
Q_DECLARE_METATYPE(Ms::PluginAPI::Placement);
Q_DECLARE_METATYPE(Ms::PluginAPI::Direction);
Q_DECLARE_METATYPE(Ms::PluginAPI::DirectionH);
Q_DECLARE_METATYPE(Ms::PluginAPI::LayoutBreakType);
Q_DECLARE_METATYPE(Ms::PluginAPI::VeloType);
Q_DECLARE_METATYPE(Ms::PluginAPI::BeamMode);
Q_DECLARE_METATYPE(Ms::PluginAPI::GlissandoStyle);
Q_DECLARE_METATYPE(Ms::PluginAPI::NoteHeadType);

#endif // MU_PLUGINS_APITYPES_H
