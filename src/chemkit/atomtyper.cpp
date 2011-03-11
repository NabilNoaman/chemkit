/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
**
** This file is part of chemkit. For more information see
** <http://www.chemkit.org>.
**
** chemkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** chemkit is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with chemkit. If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

#include "atomtyper.h"

#include "atom.h"
#include "molecule.h"
#include "pluginmanager.h"

namespace chemkit {

namespace {

QHash<QString, AtomTyper::CreateFunction> typerPlugins;

} // end anonymous namespace

// === AtomTyperPrivate ==================================================== //
class AtomTyperPrivate
{
    public:
        QString name;
        const Molecule *molecule;
};

// === AtomTyper =========================================================== //
/// \class AtomTyper atomtyper.h chemkit/atomtyper.h
/// \ingroup chemkit
/// \brief The AtomTyper class assigns symbolic types to atoms.
///
/// To create atom typer objects use the AtomTyper::create() method.

// --- Construction and Destruction ---------------------------------------- //
AtomTyper::AtomTyper(const QString &name)
    : d(new AtomTyperPrivate)
{
    d->name = name;
    d->molecule = 0;
}

/// Destroys the atom typer object.
AtomTyper::~AtomTyper()
{
    delete d;
}

// --- Properties ---------------------------------------------------------- //
/// Returns the name of the atom typer.
QString AtomTyper::name() const
{
    return d->name;
}

/// Sets the molecule for the atom typer to \p molecule.
void AtomTyper::setMolecule(const Molecule *molecule)
{
    d->molecule = molecule;

    assignTypes(molecule);
}

/// Returns the molecule for the atom typer.
const Molecule* AtomTyper::molecule() const
{
    return d->molecule;
}

// --- Types --------------------------------------------------------------- //
/// Returns the symbolic type for the atom at \p index.
QVariant AtomTyper::type(int index) const
{
    Q_UNUSED(index);

    return QVariant();
}

/// Returns the symbolic type for \p atom.
QVariant AtomTyper::type(const Atom *atom) const
{
    return type(atom->index());
}

/// Returns the symbolic type for the atom at \p index as an integer.
int AtomTyper::typeNumber(int index) const
{
    return type(index).toInt();
}

/// Returns the symbolic type for \p atom as an integer.
int AtomTyper::typeNumber(const Atom *atom) const
{
    return type(atom).toInt();
}

/// Returns the symbolic type for the atom at \p index as a string.
QString AtomTyper::typeString(int index) const
{
    return type(index).toString();
}

/// Returns the symbolic type for \p atom as a string.
QString AtomTyper::typeString(const Atom *atom) const
{
    return type(atom).toString();
}

// --- Static Methods ------------------------------------------------------ //
/// Creates and returns a new atom typer with \p name. Returns \c 0
/// if \p name is invalid.
AtomTyper* AtomTyper::create(const QString &name)
{
    // ensure default plugins are loaded
    PluginManager::instance()->loadDefaultPlugins();

    CreateFunction createFunction = typerPlugins.value(name.toLower());
    if(createFunction){
        return createFunction();
    }

    return 0;
}

/// Returns a list of names of all the available atom typers.
QStringList AtomTyper::typers()
{
    // ensure default plugins are loaded
    PluginManager::instance()->loadDefaultPlugins();

    return typerPlugins.keys();
}

void AtomTyper::registerTyper(const QString &name, CreateFunction function)
{
    typerPlugins.insert(name.toLower(), function);
}

void AtomTyper::unregisterTyper(const QString &name, CreateFunction function)
{
    if(typerPlugins.value(name.toLower()) == function){
        typerPlugins.remove(name.toLower());
    }
}

// --- Internal Methods ---------------------------------------------------- //
void AtomTyper::assignTypes(const Molecule *molecule)
{
    Q_UNUSED(molecule);
}

} // end chemkit namespace