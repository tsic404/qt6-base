# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(QT_FEATURE_dnslookup AND (QT_FEATURE_libresolv OR WIN32))
    add_subdirectory(qdnslookup)
    add_subdirectory(qdnslookup_appless)
endif()
if(QT_FEATURE_networkinterface)
    add_subdirectory(qnetworkaddressentry)
    add_subdirectory(qnetworkproxyfactory)
    add_subdirectory(qnetworkinterface)
endif()
if(QT_FEATURE_networkproxy)
    add_subdirectory(qnetworkproxy)
endif()
if(QT_FEATURE_udpsocket)
    add_subdirectory(qnetworkdatagram)
endif()
add_subdirectory(qhostaddress)
if(QT_FEATURE_private_tests AND NOT MACOS AND NOT INTEGRITY)
    add_subdirectory(qhostinfo)
endif()
if(QT_FEATURE_private_tests)
    add_subdirectory(qauthenticator)
    add_subdirectory(qnetworkinformation)
    add_subdirectory(qnetworkinformation_appless)
endif()
