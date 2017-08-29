//
//  GDMediaPlayer.h
//  pusher
//
//  Created by Alfonso Hernandez on 24/09/15.
//  Copyright © 2015 Move Fast UG. All rights reserved.
//

@import UIKit;
@import AVFoundation;

@class GDMediaPlayer;

// GDMediaPlayerContentType
//
// Defines the types of content the Media Player Support.
// Currently is Main Content (i.e. main Video or Audio) and Secondary
// content (i.e. prerolls, midrolls, ads, etc..) which is in parctice
// a secondary playable video or audio.
// GDMediaPlayerContentTypeOverall is used to report status relevant
// to the whole content overall.
typedef enum {
    GDMediaPlayerContentTypeNone = 0,
    GDMediaPlayerContentTypeMain = 1,
    GDMediaPlayerContentTypeSecondary = 2,
    GDMediaPlayerContentTypeOverall = 100
} GDMediaPlayerContentType;

// GDMediaPlayerSecondaryContentPlaybackMode
//
// Defines how the secondary content should be played
// in reference to the main conent.
typedef enum {
    GDMediaPlayerSecondaryContentPlaybackModeNotApplicable = -1,
    GDMediaPlayerSecondaryContentPlaybackModePreroll = 0,
    GDMediaPlayerSecondaryContentPlaybackModeMidroll = 1,
    GDMediaPlayerSecondaryContentPlaybackModePostroll = 2
} GDMediaPlayerSecondaryContentPlaybackMode;

// Type definitions
typedef void (^_Nullable GDTimeObservationBlock)(CMTime time);

#pragma mark -

// GDMediaPlayerStatusDelegateProtocol
//
// This protocol provides an interface for notifications related
// to loading and playability of content.
@protocol GDMediaPlayerStatusDelegateProtocol <NSObject>

@optional

/**
 loading of the media content for specified content type has failed, error information provided
 if mediaPlayerContentType == GDMediaPlayerContentTypeOverall, the player should be stopped and discarded. In any other case
 the player will switch to the other contentType automatically. In the later case, this call is just informational.
 */
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer failedToLoadMediaForContentType:(GDMediaPlayerContentType)mediaPlayerContentType error:(nonnull NSError *)error;

/**
 Underlying media assets are reported as not playable for the specified content type.
 if mediaPlayerContentType == GDMediaPlayerContentTypeOverall, the player should be stopped and discarded. In any other case
 the player will switch to the other contentType automatically. In the later case, this call is just informational.
 */
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer itemIsNotPlayableForContentType:(GDMediaPlayerContentType)mediaPlayerContentType;

/**
 underlying media item is ready to play for the sepcified content type
 */
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer itemIsReadyToPlayForContentType:(GDMediaPlayerContentType)mediaPlayerContentType;

/**
 underlying media assets metadata has been loaded for a specified content type
 */
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer assetsMetadataLoadedForContentType:(GDMediaPlayerContentType)mediaPlayerContentType;

@end

#pragma mark -

// GDMediaPlayerUIDelegateProtocol
//
// This delegate provides an interface for notification on
// MediaPlayer events that can affect the User Interface state
// of the Views presenting the media.
@protocol GDMediaPlayerUIDelegateProtocol <NSObject>

@optional

// the MediaPlayer has been reqeusted to start Playback, will start if ready (canPlayNow)
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer playbackHasBeenRequestedCanStartPlayback:(BOOL)canPlayNow;

// the MediaPlayer has effectivelly started the playback of the Media content for the specified content type
// Only called when the event occurs on the activeContentType
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer startedPlaybackForContentType:(GDMediaPlayerContentType)mediaPlayerContentType;

// Only called when the event occurs on the activeContentType
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer playbackWasPausedForContentType:(GDMediaPlayerContentType)mediaPlayerContentType;

// the MediaPlayer visual layers are ready to be displayed. The MediaPlayer might not be ready for Playback yet.
// Only called when the event occurs on the activeContentType
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer isReadyForDisplayForContentType:(GDMediaPlayerContentType)mediaPlayerContentType;

// the media content currently being played has stalled.
// Only called when the event occurs on the activeContentType
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer videoHasStalledForContentType:(GDMediaPlayerContentType)mediaPlayerContentType;

// the video content buffers for the activeContentType have reached a state where playback is again possible.
// the current Stalled status is also provided. Only called when the event occurs on the activeContentType
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer videoCanRestartPlaybackForContentType:(GDMediaPlayerContentType)mediaPlayerContentType wasStalled:(BOOL)wasStalled;

// the media for the activeContentType has reached the end mainContent will loop if indicated by willLoop.
// When all media content has been played mediaPlayerContentType == GDMediaPlayerContentTypeOverall
// in other cases mediaPlayerContentType specified the media content type that ended, and a new mediaPlayerContentType has started to play.
- (void)mediaPlayer:(nonnull GDMediaPlayer *)mediaPlayer videoHasReachedEndForContentType:(GDMediaPlayerContentType)mediaPlayerContentType willLoop:(BOOL)willLoop;

@end

#pragma mark -

@interface GDMediaPlayer : NSObject

#pragma mark - Properties

// Specifies the ContentType that is currently active.
@property (nonatomic, assign) GDMediaPlayerContentType activeContentType;

// Content URLs
@property (nonatomic, strong, nonnull) NSURL *mainContentURL; // Writing mainContentURL after loading started will have no effect
@property (nonatomic, strong, readonly, nullable) NSURL *secondaryContentURL;

// Delegates
@property (nonatomic, weak, nullable) NSObject<GDMediaPlayerStatusDelegateProtocol> *statusDelegate;
@property (nonatomic, weak, nullable) NSObject<GDMediaPlayerUIDelegateProtocol> *uiDelegate;
@property (nonatomic, weak, nullable) NSObject<GDMediaPlayerUIDelegateProtocol> *secondaryUIDelegate; // We support a secondary UI Delegate for cases like video Ads in PIP where UI actions need to be reported to diferent objects.

// Reference to associated Model object when applicable
@property (nonatomic, weak, nullable) id modelObject;

// Secondary content
@property (nonatomic, assign, readonly) GDMediaPlayerSecondaryContentPlaybackMode secondaryContentPlaybackMode;

// Video objects
@property (nonatomic, strong, readonly, nullable) CALayer *masterPlayerLayer;
@property (nonatomic, strong, readonly, nullable) CALayer *activeVideoPlayerLayer;

// Configuration flags
@property (nonatomic, assign) BOOL autoPlayWhenVisible;
@property (nonatomic, assign) BOOL plackbackLoopMode; // This applies to mainContentOnly and will prevent the use of Postroll!

// Time related variables
@property (nonatomic, assign, readonly) CMTime mainContentStartTime;

// Status flags
@property (nonatomic, assign, readonly) BOOL playbackRequested;
@property (nonatomic, assign, readonly) BOOL isPlaying;

// Tracking flags
@property (nonatomic, assign) BOOL wasPlayingWhenResignedActive;
@property (nonatomic, assign, readonly) BOOL mediaWasPlayed;
@property (nonatomic, assign) BOOL watchedOnFullScreenVideoPlayer;

// Video Quality Assessment
@property (nonatomic, assign) BOOL videoQualityAssessed;
@property (nonatomic, assign) BOOL qualityValidForPlayback;

#pragma mark - Class Methods

// Create an instance of mediaPlayer for single main content playback.
+ (nonnull instancetype)mediaPlayerWithMainContentURL:(nonnull NSURL*)mainContentURL;

// Create an instance of mediaPlayer for main content playback with secondary content as preroll.
+ (nonnull instancetype)mediaPlayerWithMainContentURL:(nonnull NSURL*)mainContentURL prerollContentURL:(nonnull NSURL *)secondaryContentURL;

// Create an instance of mediaPlayer for main content playback with secondary content as postroll.
+ (nonnull instancetype)mediaPlayerWithMainContentURL:(nonnull NSURL*)mainContentURL postrollContentURL:(nonnull NSURL *)secondaryContentURL;

// Create an instance of mediaPlayer for main content playback with secondary content as midroll at the specified midrollStartReference.
// midrollStartReference must be a value between 0 and 1, and specifies when the midroll content should start in relation to main content
// duration.
+ (nonnull instancetype)mediaPlayerWithMainContentURL:(nonnull NSURL*)mainContentURL midrollContentURL:(nonnull NSURL *)secondaryContentURL midrollStartReference:(float)midrollStartReference;

#pragma mark - Instance Methods

#pragma mark Initializers

- (nonnull instancetype) init __attribute__((unavailable("init not available")));

- (nonnull instancetype) initWithMainContentURL:(nonnull NSURL*)mainContentURL secondaryContentURL:(nullable NSURL *)secondaryContentURL secondaryContentPlaybackMode:(GDMediaPlayerSecondaryContentPlaybackMode)secondaryContentPlaybackMode secondaryContentStartReference:(CGFloat)secondaryContentStartReference NS_DESIGNATED_INITIALIZER;

#pragma mark Assest setup and content loading

// Preapre the media assets for playback, will start filling up content buffers if
// startContentLoadingWhenAssetsReady is set.
- (void)prepareMediaAssetsStartContentLoading:(BOOL)startContentLoadingWhenAssetsReady;

// Start buffer content loading if not done already for assets.
- (void)startContentLoading;

// Will Stop and content loading and will release the video assets.
- (void)stopContentLoadingAndReleaseAssets;

#pragma mark Playback Control

// Attempt to start playback of media, if not playable yet, will start
// playback as soon as media content is ready.
- (void)play;

// Intended to restart playback after media playback has stalled.
// It will only have effect if media isPlaying is set.
- (void)resumePlayback;

// Pause media playback. Restart with play.
- (void)pause;

// Bring playback pointer for main media content back to initial point.
// This will be Zero or the value of startTime if set.
- (void)backToBegining;

- (void)seekToTime:(CMTime)time completionHandler:(nullable void(^)(BOOL finished))completion;

// Sets the point where the main content media should comence
// playback from. (in seconds)
- (void)setStartTime:(NSTimeInterval)startTime;
// or in CMTime
- (void)setStartCMTime:(CMTime)startCMTime;

// Gets the start time in seconds.
- (NSTimeInterval)startTime;

#pragma mark Video Layer

// natural size for Active Video Content
- (CGSize)naturalSizeForActiveVideoContent;

// set the video layer frame
- (void)setMasterPlayerLayerFrame:(CGRect)frame;

// set the video gravity for active Content Type
- (void)setVideoGravity:(nonnull NSString *)videoGravity;

// Default video Gravity for Main and Secondary content type
- (void)setDefaultVideoGravityForMainContentType:(nonnull NSString *)videoGravity;
- (void)setDefaultVideoGravityForSecondaryContentType:(nonnull NSString *)videoGravity;

#pragma mark Status flags for the activeContent

// This checks if eithe the asset or the player is explicitly in
// a failed or cancelled state.
- (BOOL)hasFailedToLoad;

// is Ready to play reflect both the status of the asset and
// the video layer ready for display
- (BOOL)isReadyToPlay;

// indicates if the video buffer is currently not enough for
// playback and media has been stopped.
- (BOOL)isStalled;

// indicated if media content has reached end
- (BOOL)hasReachedEnd;

// indicates if the content (both main and secondary) uses
// local content. i.e. valid local file URLs.
- (BOOL)usesLocalContent;

// indicates if loading has been requested.
- (BOOL)loadingHasBeenRequested;

/// indicates if assets setup has been requested.
- (BOOL)assetsSetupRequested;

#pragma mark Time Status for activeContent

// Actual time for the activeContent
- (CMTime)currentTime;

// Remaining time for playback for the activeContent
- (CMTime)remainingTime;

// Video duration for the activeContent
- (CMTime)duration;

#pragma mark Time Status for mainContent

// Actual time for the mainContent
- (CMTime)currentTimeForMainContent;

// Remaining time for playback for the mainContent
- (CMTime)remainingTimeForMainContent;

// Video duration for the mainContent
- (CMTime)durationForMainContent;

#pragma mark Volume Control

- (float)volume;
- (void)setVolume:(float)volume;

#pragma mark External Stalled Controller

/// This method allows the marking of the stalled status as `YES`. The Stalled status is managed internally, but some implementation might perform stricter Stall detections. This method allows for such control.
- (void)markAsStalledForContentType:(GDMediaPlayerContentType)contentType;

/// This method allows clearing the Stalled status to `NO`. The Stalled status is managed internally, but some implementation might perform stricter Stall detections. This method allows for such control.
- (void)clearStalledForContentType:(GDMediaPlayerContentType)contentType;

#pragma mark Secondary Content configurations

// Defines the ammount of time in seconds after which the Secondary Content
// should be dismissed if a Stall situation.
// Setting 0 means no timeout. Default value is 0;
- (void)setStallTimeoutForSecondaryContent:(NSTimeInterval)stallTimeout;

#pragma mark Time Observations and data laoding observation

// Register for time observations on the active content.
// Must specify a block to served the obserbations to.
// Observations are served every .5 seconds
- (void)registerForTimedObservationsUsingBlock:(GDTimeObservationBlock)block;

// Stop time observation
- (void)unregisterForTimedObservations;

// Estimates the ammount of data loaded in a background thread.
// Must provide a block to deliver the estimation results to.
- (void)estimatedLoadedDataBitsCompletion:(void (^ _Nonnull)(double estimatedLoadedDataBits))block;

#pragma mark Frame Image helper

// Provide a UIImage for a frame in teh vecinity of provide time.
- (void)getImageForFrameAtTime:(CMTime)time completion:(void (^ _Nonnull)(UIImage * _Nullable image))block;

// Provide the best CMTime to use for frame image capture based on current playback time.
- (CMTime)optimalTimeForFrameImageCapture;

#pragma mark Accesors to Assets and underlying properties

// Provides the video asset if available for the given content type
- (nullable AVAsset *)videoAssetForContentType:(GDMediaPlayerContentType)videoPlayerContentType;

// specify if the main Content asset includes a Sound track
- (BOOL)mainContentHasSoundTrack;

@end
