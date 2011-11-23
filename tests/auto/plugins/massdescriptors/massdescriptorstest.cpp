/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#include "massdescriptorstest.h"

#include <algorithm>

#include <chemkit/molecule.h>
#include <chemkit/moleculardescriptor.h>

void MassDescriptorsTest::initTestCase()
{
    std::vector<std::string> descriptors = chemkit::MolecularDescriptor::descriptors();
    QVERIFY(std::find(descriptors.begin(), descriptors.end(), "molecular-mass") != descriptors.end());
}

void MassDescriptorsTest::test_data()
{
    QTest::addColumn<QString>("formula");
    QTest::addColumn<int>("mass");

    QTest::newRow("water") << "H2O" << 18;
    QTest::newRow("methane") << "CH4" << 16;
    QTest::newRow("benzene") << "C6H6" << 78;
}

void MassDescriptorsTest::test()
{
    QFETCH(QString, formula);
    QFETCH(int, mass);

    chemkit::Molecule molecule(formula.toStdString(), "formula");
    QCOMPARE(molecule.formula(), formula.toStdString());
    QCOMPARE(molecule.descriptor("molecular-mass").toInt(), mass);
}

QTEST_APPLESS_MAIN(MassDescriptorsTest)