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
#ifndef MU_ENGRAVING_PROPERTYVALUE_H
#define MU_ENGRAVING_PROPERTYVALUE_H

#include <variant>
#include <any>
#include <string>
#include <memory>

#include <QVariant>

#include "types/types.h"
#include "libmscore/types.h"
#include "libmscore/symid.h"
#include "libmscore/pitchvalue.h"
#include "libmscore/mscore.h"

#include "framework/global/logstream.h"

namespace Ms {
class Groups;
class TDuration;
}

namespace mu::engraving {
enum class P_TYPE {
    UNDEFINED = 0,
    // Base
    BOOL,
    INT,
    REAL,
    STRING,

    // Geometry
    POINT,              // point units, value saved as mm or spatium depending on EngravingItem->sizeIsSpatiumDependent()
    SIZE,
    PATH,
    SCALE,
    SPATIUM,
    MILLIMETRE,
    PAIR_REAL,

    // Draw
    COLOR,
    ORNAMENT_STYLE,
    GLISS_STYLE,

    // Layout
    ALIGN,
    PLACEMENT_V,
    PLACEMENT_H,
    TEXT_PLACE,
    DIRECTION_V,
    DIRECTION_H,
    BEAM_MODE,

    // Duration
    FRACTION,

    // Types
    LAYOUTBREAK_TYPE,
    VELO_TYPE,
    BARLINE_TYPE,
    NOTEHEAD_TYPE,

    TEMPO,
    GROUPS,
    SYMID,
    INT_LIST,

    HEAD_GROUP,         // enum class Notehead::Group
    ZERO_INT,           // displayed with offset +1

    SUB_STYLE,

    CHANGE_METHOD,      // enum class VeloChangeMethod (for single note dynamics)
    CHANGE_SPEED,       // enum class Dynamic::Speed
    CLEF_TYPE,          // enum class ClefType
    DYNAMIC_TYPE,       // enum class DynamicType
    KEYMODE,            // enum class KeyMode
    ORIENTATION,        // enum class Orientation

    HEAD_SCHEME,        // enum class NoteHead::Scheme

    PITCH_VALUES,
    HOOK_TYPE,
    ACCIDENTAL_ROLE,

    TDURATION
};

class PropertyValue
{
public:
    PropertyValue() = default;

    // Base
    PropertyValue(bool v)
        : m_type(P_TYPE::BOOL), m_data(make_data<bool>(v)) {}

    PropertyValue(int v)
        : m_type(P_TYPE::INT), m_data(make_data<int>(v)) {}

    PropertyValue(qreal v)
        : m_type(P_TYPE::REAL), m_data(make_data<qreal>(v)) {}

    PropertyValue(const char* v)
        : m_type(P_TYPE::STRING), m_data(make_data<QString>(QString(v))) {}

    PropertyValue(const QString& v)
        : m_type(P_TYPE::STRING), m_data(make_data<QString>(v)) {}

    // Geometry
    PropertyValue(const PointF& v)
        : m_type(P_TYPE::POINT), m_data(make_data<PointF>(v)) {}

    PropertyValue(const PairF& v)
        : m_type(P_TYPE::PAIR_REAL), m_data(make_data<PairF>(v)) {}

    PropertyValue(const SizeF& v)
        : m_type(P_TYPE::SIZE), m_data(make_data<SizeF>(v)) {}

    PropertyValue(const PainterPath& v)
        : m_type(P_TYPE::PATH), m_data(make_data<PainterPath>(v)) {}

    PropertyValue(const Spatium& v)
        : m_type(P_TYPE::SPATIUM), m_data(make_data<Spatium>(v)) {}

    PropertyValue(const Millimetre& v)
        : m_type(P_TYPE::MILLIMETRE), m_data(make_data<Millimetre>(v)) {}

    // Draw
    PropertyValue(const Color& v)
        : m_type(P_TYPE::COLOR), m_data(make_data<Color>(v)) {}

    PropertyValue(OrnamentStyle v)
        : m_type(P_TYPE::ORNAMENT_STYLE), m_data(make_data<OrnamentStyle>(v)) {}

    PropertyValue(GlissandoStyle v)
        : m_type(P_TYPE::GLISS_STYLE), m_data(make_data<GlissandoStyle>(v)) {}

    // Layout
    PropertyValue(Align v)
        : m_type(P_TYPE::ALIGN), m_data(make_data<Align>(v)) {}

    PropertyValue(PlacementV v)
        : m_type(P_TYPE::PLACEMENT_V), m_data(make_data<PlacementV>(v)) {}
    PropertyValue(PlacementH v)
        : m_type(P_TYPE::PLACEMENT_H), m_data(make_data<PlacementH>(v)) {}

    PropertyValue(TextPlace v)
        : m_type(P_TYPE::TEXT_PLACE), m_data(make_data<TextPlace>(v)) {}

    PropertyValue(DirectionV v)
        : m_type(P_TYPE::DIRECTION_V), m_data(make_data<DirectionV>(v)) {}
    PropertyValue(DirectionH v)
        : m_type(P_TYPE::DIRECTION_H), m_data(make_data<DirectionH>(v)) {}

    PropertyValue(BeamMode v)
        : m_type(P_TYPE::BEAM_MODE), m_data(make_data<BeamMode>(v)) {}

    // Duration
    PropertyValue(const Fraction& v)
        : m_type(P_TYPE::FRACTION), m_data(make_data<Fraction>(v)) {}

    // Types
    PropertyValue(LayoutBreakType v)
        : m_type(P_TYPE::LAYOUTBREAK_TYPE), m_data(make_data<LayoutBreakType>(v)) {}

    PropertyValue(VeloType v)
        : m_type(P_TYPE::VELO_TYPE), m_data(make_data<VeloType>(v)) {}

    PropertyValue(BarLineType v)
        : m_type(P_TYPE::BARLINE_TYPE), m_data(make_data<BarLineType>(v)) {}

    PropertyValue(NoteHeadType v)
        : m_type(P_TYPE::NOTEHEAD_TYPE), m_data(make_data<NoteHeadType>(v)) {}

    // not sorted
    PropertyValue(Ms::SymId v)
        : m_type(P_TYPE::SYMID), m_data(make_data<Ms::SymId>(v)) {}

    PropertyValue(Ms::HookType v)
        : m_type(P_TYPE::HOOK_TYPE), m_data(make_data<Ms::HookType>(v)) {}

    PropertyValue(Ms::DynamicType v)
        : m_type(P_TYPE::DYNAMIC_TYPE), m_data(make_data<Ms::DynamicType>(v)) {}

    PropertyValue(const Ms::PitchValues& v)
        : m_type(P_TYPE::PITCH_VALUES), m_data(make_data<Ms::PitchValues>(v)) {}

    PropertyValue(const QList<int>& v)
        : m_type(P_TYPE::INT_LIST), m_data(make_data<QList<int> >(v)) {}

    PropertyValue(const Ms::AccidentalRole& v)
        : m_type(P_TYPE::ACCIDENTAL_ROLE), m_data(make_data<Ms::AccidentalRole>(v)) {}

    PropertyValue(const Ms::Groups& v);
    PropertyValue(const Ms::TDuration& v);

    bool isValid() const;

    P_TYPE type() const;

    template<typename T>
    T value() const
    {
        if (m_type == P_TYPE::UNDEFINED) {
            return T();
        }

        assert(m_data);
        if (!m_data) {
            return T();
        }

        Arg<T>* at = get<T>();
        if (!at) {
            //! HACK Temporary hack for int to enum
            if constexpr (std::is_enum<T>::value) {
                if (P_TYPE::INT == m_type) {
                    return static_cast<T>(value<int>());
                }
            }

            //! HACK Temporary hack for enum to int
            if constexpr (std::is_same<T, int>::value) {
                if (m_data->isEnum()) {
                    return m_data->enumToInt();
                }
            }

            //! HACK Temporary hack for bool to int
            if constexpr (std::is_same<T, int>::value) {
                if (P_TYPE::BOOL == m_type) {
                    return value<bool>();
                }
            }

            //! HACK Temporary hack for int to bool
            if constexpr (std::is_same<T, bool>::value) {
                return value<int>();
            }

            //! HACK Temporary hack for real to Spatium
            if constexpr (std::is_same<T, Spatium>::value) {
                if (P_TYPE::REAL == m_type) {
                    Arg<qreal>* srv = get<qreal>();
                    assert(srv);
                    return srv ? Spatium(srv->v) : Spatium();
                }
            }

            //! HACK Temporary hack for Spatium to real
            if constexpr (std::is_same<T, qreal>::value) {
                if (P_TYPE::SPATIUM == m_type) {
                    return value<Spatium>().val();
                }
            }

            //! HACK Temporary hack for real to Millimetre
            if constexpr (std::is_same<T, Millimetre>::value) {
                if (P_TYPE::REAL == m_type) {
                    Arg<qreal>* mrv = get<qreal>();
                    assert(mrv);
                    return mrv ? Millimetre(mrv->v) : Millimetre();
                }
            }

            //! HACK Temporary hack for Spatium to real
            if constexpr (std::is_same<T, qreal>::value) {
                if (P_TYPE::MILLIMETRE == m_type) {
                    return value<Millimetre>().val();
                }
            }

            //! HACK Temporary hack for Fraction to String
            if constexpr (std::is_same<T, QString>::value) {
                if (P_TYPE::FRACTION == m_type) {
                    return value<Fraction>().toString();
                }
            }
        }
        return at->v;
    }

    bool toBool() const { return value<bool>(); }
    int toInt() const { return value<int>(); }
    qreal toReal() const { return value<qreal>(); }
    double toDouble() const { return value<qreal>(); }
    QString toString() const { return value<QString>(); }

    const Ms::Groups& toGroups() const;
    const Ms::TDuration& toTDuration() const;

    bool operator ==(const PropertyValue& v) const;
    inline bool operator !=(const PropertyValue& v) const { return !this->operator ==(v); }

    template<typename T>
    static PropertyValue fromValue(const T& v) { return PropertyValue(v); }

    //! NOTE compat
    QVariant toQVariant() const;
    static PropertyValue fromQVariant(const QVariant& v, P_TYPE type);

private:
    struct IArg {
        virtual ~IArg() = default;

        virtual bool equal(const IArg* a) const = 0;

        virtual bool isEnum() const = 0;
        virtual int enumToInt() const = 0;
    };

    template<typename T>
    struct Arg : public IArg {
        T v;
        Arg(const T& v)
            : IArg(), v(v) {}

        bool equal(const IArg* a) const override
        {
            assert(a);
            const Arg<T>* at = dynamic_cast<const Arg<T>*>(a);
            assert(at);
            return at ? at->v == v : false;
        }

        //! HACK Temporary hack for enum to int
        bool isEnum() const override
        {
            return std::is_enum<T>::value;
        }

        int enumToInt() const override
        {
            if constexpr (std::is_enum<T>::value) {
                return static_cast<int>(v);
            } else {
                return -1;
            }
        }
    };

    template<typename T>
    inline std::shared_ptr<IArg> make_data(const T& v) const
    {
        return std::shared_ptr<IArg>(new Arg<T>(v));
    }

    template<typename T>
    inline Arg<T>* get() const
    {
        return dynamic_cast<Arg<T>*>(m_data.get());
    }

    P_TYPE m_type = P_TYPE::UNDEFINED;
    std::shared_ptr<IArg> m_data = nullptr;

    //! HACK Temporary solution for some types
    std::any m_any;
};
}

inline mu::logger::Stream& operator<<(mu::logger::Stream& s, const mu::engraving::PropertyValue&)
{
    s << "property(not implemented log output)";
    return s;
}

#endif // MU_ENGRAVING_PROPERTYVALUE_H
