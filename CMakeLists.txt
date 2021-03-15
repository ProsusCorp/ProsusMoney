cmake_minimum_required(VERSION 3.5) 

include(CryptoNoteWallet.cmake)
include(src/QREncode.cmake)

project(${CN_PROJECT_NAME})

execute_process(COMMAND git log -1 --pretty=format:%h
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
OUTPUT_VARIABLE GIT_REVISION)

set (CRYPTONOTE_LIB Cryptonote)

include_directories(${CMAKE_BINARY_DIR}
    src
    src/libqrencode
    cli/include
    cli/src)

find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5LinguistTools REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
if(WIN32)
  set(Boost_USE_STATIC_RUNTIME OFF)
else(WIN32)
  set(Boost_USE_STATIC_RUNTIME ON)
endif(WIN32)

find_package(Boost 1.55 REQUIRED COMPONENTS date_time filesystem program_options regex serialization system thread chrono)
if ((${Boost_MAJOR_VERSION} EQUAL 1) AND (${Boost_MINOR_VERSION} EQUAL 54))
	message(SEND_ERROR "Boost version 1.54 is unsupported, more details are available here http://goo.gl/RrCFmA")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(VERSION "")
configure_file("cli/src/version.h.in" "version.h")
configure_file("src/CryptoNoteWalletConfig.h.in" "CryptoNoteWalletConfig.h")

add_definitions(-DVERSION=\"${CN_VERSION}\")
add_definitions(-DGIT_REVISION=\"${GIT_REVISION}\")

set(CMAKE_AUTOMOC ON)

set(CRYPTONOTE_SOURCES
  cli/src/Common/Base58.cpp
  cli/src/Common/CommandLine.cpp
  cli/src/Common/Util.cpp
  cli/src/Common/StringTools.cpp
  cli/src/Common/JsonValue.cpp
  cli/src/Common/ConsoleTools.cpp
  cli/src/Common/MemoryInputStream.cpp
  cli/src/Common/PathTools.cpp
  cli/src/Common/StdInputStream.cpp
  cli/src/Common/StdOutputStream.cpp
  cli/src/Common/StreamTools.cpp
  cli/src/Common/StringOutputStream.cpp
  cli/src/Common/StringView.cpp
  cli/src/Common/VectorOutputStream.cpp
  cli/src/crypto/blake256.c
  cli/src/crypto/chacha8.c
  cli/src/crypto/crypto-ops-data.c
  cli/src/crypto/crypto-ops.c
  cli/src/crypto/crypto.cpp
  cli/src/crypto/groestl.c
  cli/src/crypto/hash-extra-blake.c
  cli/src/crypto/hash-extra-groestl.c
  cli/src/crypto/hash-extra-jh.c
  cli/src/crypto/hash-extra-skein.c
  cli/src/crypto/hash.c
  cli/src/crypto/jh.c
  cli/src/crypto/keccak.c
  cli/src/crypto/oaes_lib.c
  cli/src/crypto/random.c
  cli/src/crypto/skein.c
  cli/src/crypto/slow-hash.c
  cli/src/crypto/slow-hash.cpp
  cli/src/crypto/tree-hash.c
  cli/src/CryptoNoteCore/BlockchainIndices.cpp
  cli/src/CryptoNoteCore/BlockchainMessages.cpp
  cli/src/CryptoNoteCore/BlockIndex.cpp
  cli/src/CryptoNoteCore/CoreConfig.cpp
  cli/src/CryptoNoteCore/CryptoNoteBasic.cpp
  cli/src/CryptoNoteCore/CryptoNoteTools.cpp
  cli/src/CryptoNoteCore/Currency.cpp
  cli/src/CryptoNoteCore/MinerConfig.cpp
  cli/src/CryptoNoteCore/Transaction.cpp
  cli/src/CryptoNoteCore/Account.cpp
  cli/src/CryptoNoteCore/Blockchain.cpp
  cli/src/CryptoNoteCore/Checkpoints.cpp
  cli/src/CryptoNoteCore/CryptoNoteBasicImpl.cpp
  cli/src/CryptoNoteCore/Core.cpp
  cli/src/CryptoNoteCore/CryptoNoteFormatUtils.cpp
  cli/src/CryptoNoteCore/CryptoNoteSerialization.cpp
  cli/src/CryptoNoteCore/Difficulty.cpp
  cli/src/CryptoNoteCore/IBlock.cpp
  cli/src/CryptoNoteCore/Miner.cpp
  cli/src/CryptoNoteCore/TransactionExtra.cpp
  cli/src/CryptoNoteCore/TransactionPool.cpp
  cli/src/CryptoNoteCore/TransactionPrefixImpl.cpp
  cli/src/CryptoNoteCore/TransactionUtils.cpp
  cli/src/InProcessNode/InProcessNode.cpp
  cli/src/InProcessNode/InProcessNodeErrors.cpp
  cli/src/NodeRpcProxy/NodeErrors.cpp
  cli/src/NodeRpcProxy/NodeRpcProxy.cpp
  cli/src/P2p/NetNodeConfig.cpp
  cli/src/Serialization/BinaryInputStreamSerializer.cpp
  cli/src/Serialization/BinaryOutputStreamSerializer.cpp
  cli/src/Serialization/JsonInputValueSerializer.cpp
  cli/src/Serialization/JsonOutputStreamSerializer.cpp
  cli/src/Serialization/KVBinaryInputStreamSerializer.cpp
  cli/src/Serialization/KVBinaryOutputStreamSerializer.cpp
  cli/src/Serialization/SerializationOverloads.cpp
  cli/src/Transfers/BlockchainSynchronizer.cpp
  cli/src/Transfers/SynchronizationState.cpp
  cli/src/Transfers/TransfersConsumer.cpp
  cli/src/Transfers/TransfersContainer.cpp
  cli/src/Transfers/TransfersSubscription.cpp
  cli/src/Transfers/TransfersSynchronizer.cpp
  cli/src/Wallet/LegacyKeysImporter.cpp
  cli/src/Wallet/WalletAsyncContextCounter.cpp
  cli/src/Wallet/WalletErrors.cpp
  cli/src/Wallet/WalletSerializationV1.cpp
  cli/src/Wallet/WalletSerializationV2.cpp
  cli/src/Wallet/WalletUtils.cpp
  cli/src/WalletLegacy/KeysStorage.cpp
  cli/src/WalletLegacy/WalletLegacy.cpp
  cli/src/WalletLegacy/WalletHelper.cpp
  cli/src/WalletLegacy/WalletLegacySerializer.cpp
  cli/src/WalletLegacy/WalletLegacySerialization.cpp
  cli/src/WalletLegacy/WalletTransactionSender.cpp
  cli/src/WalletLegacy/WalletUnconfirmedTransactions.cpp
  cli/src/WalletLegacy/WalletUserTransactionsCache.cpp
  cli/src/System/ContextGroup.cpp
  cli/src/System/Event.cpp
  cli/src/System/EventLock.cpp
  cli/src/System/InterruptedException.cpp
  cli/src/System/Ipv4Address.cpp
  cli/src/System/TcpStream.cpp
  cli/src/HTTP/HttpRequest.cpp
  cli/src/HTTP/HttpParser.cpp
  cli/src/HTTP/HttpParserErrorCodes.cpp
  cli/src/HTTP/HttpResponse.cpp
  cli/src/Rpc/HttpClient.cpp
  cli/src/Rpc/JsonRpc.cpp
  cli/src/P2p/NetNode.cpp
  cli/src/P2p/LevinProtocol.cpp
  cli/src/P2p/NetNodeConfig.cpp
  cli/src/P2p/PeerListManager.cpp
  cli/src/CryptoNoteProtocol/CryptoNoteProtocolHandler.cpp
  cli/src/Logging/ILogger.cpp
  cli/src/Logging/LoggerGroup.cpp
  cli/src/Logging/CommonLogger.cpp
  cli/src/Logging/LoggerManager.cpp
  cli/src/Logging/FileLogger.cpp
  cli/src/Logging/StreamLogger.cpp
  cli/src/Logging/ConsoleLogger.cpp
  cli/src/Logging/LoggerMessage.cpp
  cli/src/Logging/LoggerRef.cpp
  cli/src/BlockchainExplorer/BlockchainExplorer.cpp
  cli/src/BlockchainExplorer/BlockchainExplorerDataBuilder.cpp
  cli/src/BlockchainExplorer/BlockchainExplorerErrors.cpp
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE FORMS src/gui/ui/*.ui)
file(GLOB_RECURSE Mnemonics cli/src/mnemonics/*)

set(QRC src/resources.qrc)

qt5_wrap_ui(UIS ${FORMS})
qt5_add_resources(RCC ${QRC})


if (WIN32)
  if (NOT MSVC)
	message(FATAL_ERROR "Only MSVC is supported on this platform")
  endif ()
  add_definitions(/D_CRT_SECURE_NO_WARNINGS /D_WIN32_WINNT=0x0600 /DSTATICLIB)
  include_directories(cli/src/platform/msc)

  set(PLATFORM_DIR Windows)
  set(BUILD_PLATFORM WIN32)
  set(BUILD_RESOURCES src/cryptonotewallet.rc)
  set(QTMAIN Qt5::WinMain)

elseif (UNIX)
# set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} cryptonote/external/miniupnpc/minissdpc.c)
  if (APPLE)
    enable_language(ASM)
    file(GLOB_RECURSE OBJC_SOURCES src/*.mm)
    set(SOURCES ${SOURCES} ${OBJC_SOURCES})
    set(PLATFORM_DIR OSX)
    set(MACOSX_BUNDLE_INFO_STRING "Prosus GUI wallet")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_NAME "ProsusMoney")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "$${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")

    find_package(Qt5PrintSupport REQUIRED)

    include_directories(/usr/include/malloc)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11 -stdlib=libc++")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -maes -D_DARWIN_C_SOURCE")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework CoreFoundation -framework Carbon -framework IOKit -L/usr/lib")

    set(MACOSX_BUNDLE_ICON_FILE cryptonote.icns)
    set(APPLICATION_ICON src/images/cryptonote.icns)
    set_source_files_properties(${APPLICATION_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    set(BUILD_PLATFORM MACOSX_BUNDLE)
    set(BUILD_RESOURCES ${APPLICATION_ICON})
	
    GET_TARGET_PROPERTY(QT_LIB_DIR "${Qt5Widgets_LIBRARIES}" LOCATION)
    GET_FILENAME_COMPONENT(QT_LIB_DIR "${QT_LIB_DIR}" PATH)
  else(APPLE)
    set(PLATFORM_DIR Linux)
    list(REMOVE_ITEM HEADERS ${CMAKE_SOURCE_DIR}/src/gui/macdockiconhandler.h)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -std=c11")
  endif (APPLE)
endif ()

include_directories(cli/src/Platform/${PLATFORM_DIR})
include_directories(cli/src/Platform/Posix)
file(GLOB PLATFORM_SOURCES cli/src/Platform/${PLATFORM_DIR}/System/*)
set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} ${PLATFORM_SOURCES})

add_library(${CRYPTONOTE_LIB} STATIC ${CRYPTONOTE_SOURCES})
add_library(Mnemonics ${Mnemonics})
set_target_properties(${CRYPTONOTE_LIB} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${CRYPTONOTE_LIB} ${Boost_LIBRARIES})
set_target_properties(Mnemonics PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(Mnemonics ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} ${BUILD_PLATFORM} ${BUILD_RESOURCES} ${SOURCES} ${HEADERS} ${UIS} ${RCC})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${QTMAIN} ${CRYPTONOTE_LIB} ${QRENCODE_LIB} Mnemonics)

if (APPLE)
  qt5_use_modules(${PROJECT_NAME} PrintSupport)
elseif (UNIX)
  target_link_libraries(${PROJECT_NAME} -lpthread)
elseif (WIN32)
  target_link_libraries(${PROJECT_NAME} Imm32 Iphlpapi Winmm)
endif (APPLE)

qt5_use_modules(${PROJECT_NAME} Widgets Gui Network)

# Installation

set(CPACK_PACKAGE_NAME ${CN_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${CN_VERSION})
set(CPACK_PACKAGE_VENDOR "prosus-project")
set(CPACK_PACKAGE_CONTACT "http://prosus.money")
set(CPACK_STRIP_FILES ON)
if (APPLE)
    set(CPACK_GENERATOR DragNDrop)
    install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION .)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${VERSION_RELEASE}")
elseif (UNIX)
    find_program(RPMBUILD rpmbuild)

    install(PROGRAMS build/${PROJECT_NAME} DESTINATION bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    install(FILES src/prosuswallet.desktop DESTINATION share/applications)
    install(FILES src/images/cryptonote.png DESTINATION share/pixmaps RENAME prosus.png)
    install(FILES copyright DESTINATION share/doc/prosus)

    if (NOT RPMBUILD)
        set(CPACK_GENERATOR DEB)
        set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
        set(CPACK_SYSTEM_NAME 64-bit)
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR} <contacto@prosuscorp.com>")
        set(CPACK_DEBIAN_PACKAGE_SECTION Office)
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Prosus wallet
 Prosus is a decentralized, privacy oriented peer-to-peer
 cryptocurrency. It is open-source, nobody owns or controls Prosus
 and everyone can take part.")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${VERSION_RELEASE}${CPACK_SYSTEM_NAME}")
    else()
        set(CPACK_GENERATOR RPM)
        set(CPACK_SYSTEM_NAME x86_64)
        set(CPACK_RPM_PACKAGE_RELEASE ${VERSION_RELEASE})
        set(CPACK_RPM_PACKAGE_LICENSE "MIT")
        set(CPACK_RPM_PACKAGE_GROUP Office)
        set(CPACK_RPM_PACKAGE_REQUIRES "qt5-qtbase >= 5.3.2, qt5-qtbase-gui >= 5.3.2")
        set(CPACK_RPM_PACKAGE_SUMMARY "Prosus wallet")
        set(CPACK_RPM_PACKAGE_DESCRIPTION " __ Prosus Money __
 Prosus is a decentrilized, privacy oriented peer-to-peer
 cryptocurrency. It is open-source, nobody owns or controls Prosus
 and everyone can take part.")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${VERSION_RELEASE}${CPACK_SYSTEM_NAME}")
    endif ()
elseif (WIN32)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
  set(CPACK_GENERATOR ZIP)
endif (APPLE)

include(CPack)


set (FILES_TO_TRANSLATE )
set (FILES_TO_TRANSLATE ${FILES_TO_TRANSLATE} ${SOURCES} ${HEADERS} ${FORMS} PARENT_SCOPE)
#----------
file (GLOB TRANSLATIONS_FILES src/languages/*.ts)

option (UPDATE_TRANSLATIONS "Actualizando traducciones en src/languages/*.ts")
if (UPDATE_TRANSLATIONS)
  qt5_create_translation(QM_FILES ${FILES_TO_TRANSLATE} ${TRANSLATIONS_FILES})
else (UPDATE_TRANSLATIONS)
  qt5_add_translation(QM_FILES ${TRANSLATIONS_FILES})
endif (UPDATE_TRANSLATIONS)

add_custom_target (translations_target DEPENDS ${QM_FILES})

install(FILES ${QM_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/src/languages)

# prevent the generated files from being deleted during make clean
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM true)
#----------
