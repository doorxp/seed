CONFIG += staticlib \
		  precompile_header \
		  silent
QT += opengl
TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += . \
	"../include" \
	"$$(SEEDSDK)/dependency/common/include" \
	"$$(SEEDSDK)/dependency/mingw/include"
DEFINES += _QT_
Debug {
	OBJECTS_DIR = ../bin/debug/qt/obj
	DESTDIR = ../bin/debug/qt
	MOC_DIR = ../bin/debug/qt/moc
	DEFINES += DEBUG \
		YMEM_DEBUG
}
Release {
	DESTDIR = ../bin/release/qt
	OBJECTS_DIR = ../bin/release/qt/obj
	MOC_DIR = ../bin/release/qt/moc
	DEFINES += RELEASE
}

PRECOMPILED_HEADER = ../include/platform/qt/QtPch.h

# Windows
win32:DEFINES += WIN32 \
	_WIN32_
HEADERS += ../include/StateMachine.h \
	../include/Dictionary.h \
	../include/Text.h \
	../include/Array.h \
	../include/FileSystem.h \
	../include/Rect.h \
	../include/extra/ymanager/ymemorymanager.h \
	../include/extra/ymanager/ydefines.h \
	../include/extra/ymanager/yallocwrap.h \
	../include/ParticleManager.h \
	../include/Key.h \
	../include/Sound.h \
	../include/StringCache.h \
	../include/Cartridge.h \
	../include/gui/Label.h \
	../include/gui/EventWidget.h \
	../include/gui/Button.h \
	../include/gui/WidgetContainer.h \
	../include/gui/TextArea.h \
	../include/gui/GuiManager.h \
	../include/EventInputMotion.h \
	../include/Sprite.h \
	../include/Renderer.h \
	../include/File.h \
	../include/MemoryManager.h \
	../include/Defines.h \
	../include/Movie.h \
	../include/Renderer2D.h \
	../include/Keyframe.h \
	../include/Config.h \
	../include/Configuration.h \
	../include/Trigonometry.h \
	../include/Input.h \
	../include/Particle.h \
	../include/Updater.h \
	../include/Profiler.h \
	../include/ModuleManager.h \
	../include/LeakReport.h \
	../include/interface/IBasicMesh.h \
	../include/interface/IRenderer2D.h \
	../include/interface/IEventInputMotionListener.h \
	../include/interface/IEventFileSystemListener.h \
	../include/interface/IEventResourceLoaderListener.h \
	../include/interface/IEventListener.h \
	../include/interface/IRenderable.h \
	../include/interface/ITimer.h \
	../include/interface/ISound.h \
	../include/interface/IInputPointer.h \
	../include/interface/IObject.h \
	../include/interface/IModule.h \
	../include/interface/IEventSystemListener.h \
	../include/interface/IInputJoystick.h \
	../include/interface/IEventWidgetListener.h \
	../include/interface/IScreen.h \
	../include/interface/ICartridge.h \
	../include/interface/IImage.h \
	../include/interface/IRenderer.h \
	../include/interface/ISoundSource.h \
	../include/interface/IEventMovieListener.h \
	../include/interface/ITransformable2D.h \
	../include/interface/ISprite.h \
	../include/interface/IMutex.h \
	../include/interface/IWidget.h \
	../include/interface/ISoundSystem.h \
	../include/interface/IInputMotion.h \
	../include/interface/IEventInputPointerListener.h \
	../include/interface/IThread.h \
	../include/interface/ISystem.h \
	../include/interface/IMemoryManager.h \
	../include/interface/IResource.h \
	../include/interface/IEvent.h \
	../include/interface/IEventInput.h \
	../include/interface/IMusic.h \
	../include/interface/IInputKeyboard.h \
	../include/interface/IMemoryPool.h \
	../include/interface/IEventInputKeyboardListener.h \
	../include/interface/IInput.h \
	../include/interface/IGameApp.h \
	../include/interface/IFileSystem.h \
	../include/interface/IPlayable.h \
	../include/EventMovie.h \
	../include/Enum.h \
	../include/EventInputPointer.h \
	../include/CollisionMask.h \
	../include/Image.h \
	../include/System.h \
	../include/Number.h \
	../include/EventInputKeyboard.h \
	../include/Mutex.h \
	../include/Point.h \
	../include/ResourceGroup.h \
	../include/EventFileSystem.h \
	../include/SoundSource.h \
	../include/SpriteObject.h \
	../include/Base.h \
	../include/ParticleEmitter.h \
	../include/platform/sdl/SdlSystem.h \
	../include/platform/sdl/SdlScreen.h \
	../include/platform/sdl/SdlImage.h \
	../include/platform/sdl/SdlThread.h \
	../include/platform/sdl/SdlMutex.h \
	../include/platform/sdl/SdlInput.h \
	../include/platform/sdl/SdlDefines.h \
	../include/platform/sdl/SdlTimer.h \
	../include/platform/iphone/IphDefines.h \
	../include/platform/iphone/IphMutex.h \
	../include/platform/iphone/IphMemoryPool.h \
	../include/platform/iphone/IphCartridge.h \
	../include/platform/iphone/IphFileSystem.h \
	../include/platform/iphone/IphMusic.h \
	../include/platform/iphone/IphSoundSystem.h \
	../include/platform/iphone/IphoneSystemStub.h \
	../include/platform/iphone/IphSound.h \
	../include/platform/iphone/IphRenderer2D.h \
	../include/platform/iphone/IphoneView.h \
	../include/platform/iphone/IphSystem.h \
	../include/platform/iphone/IphImage.h \
	../include/platform/iphone/IphScreen.h \
	../include/platform/iphone/IphRenderer.h \
	../include/platform/iphone/IphSprite.h \
	../include/platform/iphone/IphMemoryManager.h \
	../include/platform/iphone/IphInput.h \
	../include/platform/iphone/IphTimer.h \
	../include/platform/iphone/IphThread.h \
	../include/platform/pc/PcFileSystem.h \
	../include/platform/pc/platform.h \
	../include/platform/pc/PcCartridge.h \
	../include/platform/pc/PcMemoryPool.h \
	../include/platform/pc/PcMemoryManager.h \
	../include/platform/qt/QtSystem.h \
	../include/platform/qt/QtMutex.h \
	../include/platform/qt/QtScene.h \
	../include/platform/qt/QtScreen.h \
	../include/platform/qt/QtThread.h \
	../include/platform/qt/QtTimer.h \
	../include/platform/qt/QtImage.h \
	../include/platform/qt/QtInput.h \
	../include/platform/qt/QtDefines.h \
	../include/platform/wii/WiiCartridge.h \
	../include/platform/wii/WiiDefines.h \
	../include/platform/wii/WiiFileSystem.h \
	../include/platform/wii/WiiHomeButton.h \
	../include/platform/wii/WiiImage.h \
	../include/platform/wii/WiiInput.h \
	../include/platform/wii/WiiMemoryManager.h \
	../include/platform/wii/WiiMusic.h \
	../include/platform/wii/WiiMutex.h \
	../include/platform/wii/WiiRenderer2D.h \
	../include/platform/wii/WiiRenderer.h \
	../include/platform/wii/WiiScreen.h \
	../include/platform/wii/WiiSound.h \
	../include/platform/wii/WiiSoundHelper.h \
	../include/platform/wii/WiiSoundSource.h \
	../include/platform/wii/WiiSoundSystem.h \
	../include/platform/wii/WiiSprite.h \
	../include/platform/wii/WiiSystem.h \
	../include/platform/wii/WiiThread.h \
	../include/platform/wii/WiiTimer.h \
	../include/platform/wii/WiiWrapper.h \
	../include/Log.h \
	../include/ResourceLoader.h \
	../include/Formats.h \
	../include/ResourceManager.h \
	../include/MemoryPool.h \
	../include/ParticleEmitterObject.h \
	../include/Timeline.h \
	../include/Timer.h \
	../include/Package.h \
	../include/Font.h \
	../include/Thread.h \
	../include/EventSystem.h \
	../include/SeedInit.h \
	../include/SoundSystem.h \
	../include/PackageManager.h \
	../include/Seed.h \
	../include/Screen.h \
	../include/EventResourceLoader.h \
	../include/Music.h \
	../include/Rand.h \
	../include/Vector.h \
	../include/Checksum.h \
	../include/SaveSystem.h \
	../include/api/oal_ogg/vorbis_util.h \
	../include/api/oal_ogg/OalOggMusic.h \
	../include/api/oal_ogg/OalOggSound.h \
	../include/api/oal_ogg/OalOggSoundSource.h \
	../include/api/oal_ogg/OalOggSoundSystem.h \
	../include/api/ogl/OglRenderer.h \
	../include/api/ogl/OglRenderer2D.h \
	../include/api/ogl/OglSprite.h \
	../include/api/theora/Theora.h \
	../include/interface/IUpdatable.h \
	../include/interface/IVideo.h \
	../include/StringPool.h \
	../include/TString.h \
	../include/Singleton.h \
	../include/platform/qt/QtPch.h
SOURCES += ../source/EventInputPointer.cpp \
	../source/Package.cpp \
	../source/Timeline.cpp \
	../source/EventInputMotion.cpp \
	../source/EventSystem.cpp \
	../source/File.cpp \
	../source/EventFileSystem.cpp \
	../source/extra/ymanager/ymemorymanager.cpp \
	../source/extra/ymanager/yallocwrap.cpp \
	../source/EventResourceLoader.cpp \
	../source/EventInputKeyboard.cpp \
	../source/gui/Label.cpp \
	../source/gui/Button.cpp \
	../source/gui/WidgetContainer.cpp \
	../source/gui/EventWidget.cpp \
	../source/gui/TextArea.cpp \
	../source/gui/GuiManager.cpp \
	../source/Dictionary.cpp \
	../source/CollisionMask.cpp \
	../source/Updater.cpp \
	../source/Profiler.cpp \
	../source/ParticleEmitterObject.cpp \
	../source/LeakReport.cpp \
	../source/interface/IBasicMesh.cpp \
	../source/interface/IThread.cpp \
	../source/interface/IRenderable.cpp \
	../source/interface/IObject.cpp \
	../source/interface/IInputJoystick.cpp \
	../source/interface/IWidget.cpp \
	../source/interface/IInputKeyboard.cpp \
	../source/interface/IEventListener.cpp \
	../source/interface/IRenderer2D.cpp \
	../source/interface/ISoundSystem.cpp \
	../source/interface/ISprite.cpp \
	../source/interface/ISound.cpp \
	../source/interface/IInputPointer.cpp \
	../source/interface/ISoundSource.cpp \
	../source/interface/IInputMotion.cpp \
	../source/interface/IEventFileSystemListener.cpp \
	../source/interface/IImage.cpp \
	../source/interface/IEventMovieListener.cpp \
	../source/interface/IEventInputKeyboardListener.cpp \
	../source/interface/ICartridge.cpp \
	../source/interface/IEventInput.cpp \
	../source/interface/ISystem.cpp \
	../source/interface/IEvent.cpp \
	../source/interface/IResource.cpp \
	../source/interface/ITransformable2D.cpp \
	../source/interface/IModule.cpp \
	../source/interface/IMemoryManager.cpp \
	../source/interface/IScreen.cpp \
	../source/interface/ITimer.cpp \
	../source/interface/IEventInputPointerListener.cpp \
	../source/interface/IMemoryPool.cpp \
	../source/interface/IEventSystemListener.cpp \
	../source/interface/IFileSystem.cpp \
	../source/interface/IEventInputMotionListener.cpp \
	../source/interface/IGameApp.cpp \
	../source/interface/IMusic.cpp \
	../source/interface/IInput.cpp \
	../source/interface/IRenderer.cpp \
	../source/interface/IMutex.cpp \
	../source/interface/IEventResourceLoaderListener.cpp \
	../source/interface/IEventWidgetListener.cpp \
	../source/interface/IVideo.cpp \
	../source/interface/IPlayable.cpp \
	../source/Keyframe.cpp \
	../source/SpriteObject.cpp \
	../source/ResourceLoader.cpp \
	../source/SaveSystem.cpp \
	../source/Movie.cpp \
	../source/Formats.cpp \
	../source/EventMovie.cpp \
	../source/Particle.cpp \
	../source/ModuleManager.cpp \
	../source/ResourceManager.cpp \
	../source/platform/sdl/SdlSystem.cpp \
	../source/platform/sdl/SdlScreen.cpp \
	../source/platform/sdl/SdlInput.cpp \
	../source/platform/sdl/SdlMutex.cpp \
	../source/platform/sdl/SdlThread.cpp \
	../source/platform/sdl/SdlTimer.cpp \
	../source/platform/sdl/SdlImage.cpp \
	../source/platform/iphone/IphSound.cpp \
	../source/platform/iphone/IphFileSystem.cpp \
	../source/platform/iphone/IphCartridge.cpp \
	../source/platform/iphone/IphImage.cpp \
	../source/platform/iphone/IphSystem.cpp \
	../source/platform/iphone/IphMemoryPool.cpp \
	../source/platform/iphone/IphRenderer2D.cpp \
	../source/platform/iphone/IphMusic.cpp \
	../source/platform/iphone/IphInput.cpp \
	../source/platform/iphone/IphRenderer.cpp \
	../source/platform/iphone/IphScreen.cpp \
	../source/platform/iphone/IphMutex.cpp \
	../source/platform/iphone/IphTimer.cpp \
	../source/platform/iphone/IphMemoryManager.cpp \
	../source/platform/iphone/IphSprite.cpp \
	../source/platform/iphone/IphThread.cpp \
	../source/platform/iphone/IphLog.cpp \
	../source/platform/iphone/IphSoundSystem.cpp \
	../source/platform/pc/PcFileSystem.cpp \
	../source/platform/pc/PcLog.cpp \
	../source/platform/pc/PcMemoryPool.cpp \
	../source/platform/pc/posix.cpp \
	../source/platform/pc/PcCartridge.cpp \
	../source/platform/pc/win32.cpp \
	../source/platform/pc/PcMemoryManager.cpp \
	../source/platform/qt/QtSystem.cpp \
	../source/platform/qt/QtMutex.cpp \
	../source/platform/qt/QtThread.cpp \
	../source/platform/qt/QtScene.cpp \
	../source/platform/qt/QtScreen.cpp \
	../source/platform/qt/QtImage.cpp \
	../source/platform/qt/QtTimer.cpp \
	../source/platform/qt/QtInput.cpp \
	../source/ResourceGroup.cpp \
	../source/Key.cpp \
	../source/ParticleEmitter.cpp \
	../source/StringCache.cpp \
	../source/SeedInit.cpp \
	../source/Checksum.cpp \
	../source/Font.cpp \
	../source/Trigonometry.cpp \
	../source/PackageManager.cpp \
	../source/Text.cpp \
	../source/Rand.cpp \
	../source/Configuration.cpp \
	../source/ParticleManager.cpp \
	../source/api/oal_ogg/OalOggSoundSource.cpp \
	../source/api/oal_ogg/OalOggMusic.cpp \
	../source/api/oal_ogg/vorbis_util.cpp \
	../source/api/oal_ogg/OalOggSound.cpp \
	../source/api/oal_ogg/OalOggSoundSystem.cpp \
	../source/api/ogl/OglRenderer2D.cpp \
	../source/api/ogl/OglRenderer.cpp \
	../source/api/ogl/OglSprite.cpp \
	../source/api/theora/Theora.cpp \
	../source/interface/IUpdatable.cpp \
	../source/TString.cpp
