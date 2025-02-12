:: Copyright (C) 2024 The Qt Company Ltd.
:: SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0
qsb --glsl 320es,410 --hlsl 50 --msl 12 --msltess material.vert -o material.vert.qsb
qsb --glsl 320es,410 --hlsl 50 --msl 12 material.frag -o material.frag.qsb

qsb --glsl 320es,410 --msl 12 --tess-mode triangles material.tesc -o material.tesc.qsb
qsb --glsl 320es,410 --msl 12  --tess-vertex-count 3 material.tese -o material.tese.qsb

qsb -r hlsl,50,material_hull.hlsl material.tesc.qsb
qsb -r hlsl,50,material_domain.hlsl material.tese.qsb
