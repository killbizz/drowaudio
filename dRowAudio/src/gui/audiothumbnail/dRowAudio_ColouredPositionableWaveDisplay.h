/*
  ==============================================================================

    dRowAudio_ColouredPositionableWaveDisplay.h
    Created: 9 Jul 2011 7:35:03pm
    Author:  David Rowland

  ==============================================================================
*/

#ifndef __DROWAUDIO_COLOUREDPOSITIONABLEWAVEDISPLAY_H_3C442B17__
#define __DROWAUDIO_COLOUREDPOSITIONABLEWAVEDISPLAY_H_3C442B17__

#include "../../core/dRowAudio_StandardHeader.h"

#include "../../audio/dRowAudio_FilteringAudioFilePlayer.h"
#include "dRowAudio_MultipleAudioThumbnailCache.h"
#include "dRowAudio_ColouredAudioThumbnail.h"
#include "../../utility/dRowAudio_StateVariable.h"

/**
 A class to display the waveform of an audio file.
	
	This will load an audio file and display its waveform. Clicking on the waveform will
	reposition the transport source. You can change the file loaded by the associated 
	AudioFilePlayer by dragging a new file onto the display.
 */
class ColouredPositionableWaveDisplay : public Component,
                                        public MultiTimer,
                                        public ChangeListener,
                                        public AsyncUpdater,
                                        public FilteringAudioFilePlayer::Listener,
                                        public DragAndDropTarget,
                                        public FileDragAndDropTarget
{
public:
	
	/// Used to start and stop the various internal timers
	enum
	{
		waveformUpdated,
		waveformLoading,
		waveformResizing
	};
	
	/**
		Creates the display.
		The file player associated with the display must be passed in.
		To save on the number of threads in your program you can optionally pass in your own
		AudioThumbnailCache. If you pass in your own the caller is responsible for deleting it,
		if not the PositionableWaveform will create and delete its own when not needed.	 
	 */
	explicit ColouredPositionableWaveDisplay (FilteringAudioFilePlayer *sourceToBeUsed,
                                              MultipleAudioThumbnailCache *cacheToUse =nullptr,
                                              ColouredAudioThumbnail *thumbnailToUse =nullptr);
	
	/// Destructor
	~ColouredPositionableWaveDisplay ();
	
	//====================================================================================
	void resized ();
	
	void paint (Graphics &g);

	//====================================================================================
	void timerCallback (const int timerId);

    void changeListenerCallback (ChangeBroadcaster* source);
    
    void handleAsyncUpdate();
	
	void fileChanged (FilteringAudioFilePlayer *player);
		
	//====================================================================================
	/// Sets the current horizontal zoom
	void setZoomFactor (float newZoomFactor);
	
	//==============================================================================
	void mouseDown(const MouseEvent &e);
	
	void mouseUp(const MouseEvent &e);
	
	void mouseDrag(const MouseEvent &e);
	
	//==============================================================================
	bool isInterestedInFileDrag (const StringArray &files);
	void fileDragEnter (const StringArray &files, int x, int y);
	void fileDragExit (const StringArray &files);
	void filesDropped (const StringArray &files, int x, int y);
	
	//==============================================================================
	bool isInterestedInDragSource (const SourceDetails& dragSourceDetails);
	
	void itemDragEnter (const SourceDetails& dragSourceDetails);
	
	void itemDragExit (const SourceDetails& dragSourceDetails);
	
	void itemDropped (const SourceDetails& dragSourceDetails);
	
	//==============================================================================	
	
private:
	
	void refreshWaveform();
	
	FilteringAudioFilePlayer* filePlayer;
	double fileLength, oneOverFileLength, currentSampleRate, oneOverSampleRate;
	
	// thumbnail classes
	AudioFormatManager* formatManager;
	OptionalScopedPointer<MultipleAudioThumbnailCache> thumbnailCache;
	OptionalScopedPointer<ColouredAudioThumbnail> thumbnailView;
	
    Image tempImage;
	Image waveformImage;
	
	StateVariable<int> transportLineXCoord;
	float zoomFactor, currentXScale;
	
	bool isInitialised, isMouseDown, interestedInDrag;
	double currentMouseX;
    
    double lastTimeDrawn;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColouredPositionableWaveDisplay);
};

#endif  // __DROWAUDIO_COLOUREDPOSITIONABLEWAVEDISPLAY_H_3C442B17__
