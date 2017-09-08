//
//  BUZZSDKOptions.h
//  BuzzSDK
//
//  Created by mdv on 25/01/16.
//  Copyright © 2016 Move Fast UG. All rights reserved.
//

#ifndef BUZZSDKOptions_h
#define BUZZSDKOptions_h

#import <Foundation/Foundation.h>

#pragma mark - Definitions

/*!
 * @typedef BUZZSDKPresentationMode
 * @brief A list of SDK Presentation modes.
 */
typedef NS_ENUM(NSInteger, BUZZSDKPresentationMode) {
    ///Acts as a "kill switch" and means that SDK must not start, or shutdown if it has been started before.
    BUZZSDKPresentationModeNever = 0,
    
    /*!Use this option if you want to control SDK presentation manually.
     *
     * Call @c [BuzzSDK presentDeck] whenever you want to show the card deck.
     *
     * <b>Note:</b> Only first call to this method has the effect. All subsequest calls are ignored.
     */
    BUZZSDKPresentationModeManual = 1,
    
    ///BUZZSDKPresentationModeOncePerDay
    BUZZSDKPresentationModeOncePerDay = 2,
    
    ///BUZZSDKPresentationModeOncePerWeek
    BUZZSDKPresentationModeOncePerWeek = 3,
    
    ///BUZZSDKPresentationModeWhenAppBecomesActive
    BUZZSDKPresentationModeWhenAppBecomesActive = 4
};

/*!
 * @typedef BUZZSDKLogLevel
 * @brief A list of SDK Log Levels.
 */
typedef NS_ENUM(NSInteger, BUZZSDKLogLevel) {
    BUZZSDKLogLevelNone = 0,
    BUZZSDKLogLevelError,
    BUZZSDKLogLevelWarning,
    BUZZSDKLogLevelInfo,
    BUZZSDKLogLevelDebug
};

#pragma mark - Options to be set by the host app

/**
 * Value from BUZZSDKLogLevel enum representing the log level desired on the app. Must be a NSNumber containing an integer value from BUZZSDKLogLevel enum. Default value if not provided or invalid is `BUZZSDKLogLevelNone`.
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionLogLevel;

/**
 *  Kicker font name
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleKickerFontNameKey;

/**
 *  Kicker font size (NSNumber)
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleKickerFontSizeKey;

/**
 *  Kicker text color (UIColor)
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleKickerTextColorKey;

/**
 *  Kicker background color (UIColor)
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleKickerBackgroundColorKey;

/**
 *  Title font name
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleTitleFontNameKey;

/**
 *  Title font size (NSNumber)
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleTitleFontSizeKey;

/**
 *  Title text color (UIColor)
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleTitleTextColorKey;

/**
 *  Title background color (UIColor)
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleTitleBackgroundColorKey;

/**
 *  Tag image appears at the top right of the card.
 *  Please specify a name of the image from your app's bundle
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionCardStyleTagImageNameKey;

/**
 * BuzzSDK can present a custom alert to allow the user to opt for an Ad free version of the app via payment or subscriptions.
 * To present such an alert the host app will need to provide the text string for the alert message in this option. If this string is not provided the alert will never be presented.
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionRemoveAdsAlertTextKey;

/**
 * This option will indicates whether that the SDK should ignore any Ads provided by the backend config for the SDK session.
 * This will be used when the host app still wants to present the SDK for content but no Ads (i.e. if the user is for example a subscribed user)
 * Default value is `NO`
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionNoAdsKey;

#pragma mark - Options to be set by the server

/**
 * SDK Presentation Mode. Default is BUZZSDKPresentationModeManual - it means that developer must call [BuzzSDK presentDeck]
 * to show the SDK's card deck
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionPresentationModeKey;


/**
 * This option will indicates that the SDK should not present to the user any content that has already been seen.
 * The video content is considered seen when: (1) The video plays until the end or (2) The user swipes away the video.
 * Default value is `NO`
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionExcludeSeenContentKey;

/**
 * Video Cards and PIP will autoplay when if user is in Wifi when this option is `YES`. Default is `YES`.
 * Video Ads allways autoplay.
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionVideoAutoplayInWifi;

/**
 * Video Cards and PIP will autoplay if user is in Cellular when this option is `YES`. Default is `NO`.
 * Video Ads allways autoplay.
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionVideoAutoplayInCellular;

/**
 *  The PIP Video views will try to fill up to the given fraction of the screen width
 *  as much as possible. It will be ignored if resulting size for PIP Video Views exceeds
 *  the allowed internal allowed range for width and height.
 *  Should be a value between 0 and 1.
 *  If 0 is provided, the app will dyanmically size the PIP Video Views to fill as much 
 *  of the leftover screen size below the card stack.
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionDesiredPIPFillWidthRatioToScreenWidthKey;


/**
 * Indicates maximum amount of time which SDK is allowed to stay alive if the app has made inactive (in seconds).
 * Default value is 600 seconds (10 minutes)
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionMaxTimeToLiveWhileAppInactiveKey;

/**
 *  A boolean value. If `true` a fade gradient will be presented below the PIP Video View when present.
 *  Default value is `false` i.e. not displayed.
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionDisplayFadeGradientUnderPIPVideoView;

/**
 * A boolean value. If `true` the tooltip `Pan Down to Dismiss` will be allowed to be presented when necessary on PIP user interactions.
 * Default value in `false` i.e. not diplayed.
 */
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionDisplayPanDownToDismissPIPTooltip;

//Facebook Ads Options
//In order to run a Facebook Ad you need to provide a valid Facebook Placement ID
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionFacebookPlacementIdKey;

//Mopub Ads Options
//In order to run a DFP MidRect Ads you need to provide a valid Mopub Placement ID
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionDFPMidRectPlacementIdKey;

/// The video AD VAST Tag URL
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionVideoAdUrlKey;

/// The index in the model stack where a video Ad should be first placed. If this index is greater than the number of content elements in the model, it will be added at the end.
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionVideoAdFirstPlacement;

/// Once a first video Ad is placed, this option controls the minimum number of cards that need to be fetched from the model before presenting another video ad.
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionMinimumNumberOfCardsBetweenVideoAds;

/// Defines if the first card (when a video or video ad) must be presented in Card Mode. If `false` it will be presented in PIP. Default value is `false`
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionFirstVideoInCardMode;

/// Defines if the hide actions (pressing the hide button or dismissing the PIP Playlist on the down direction) will actually dismiss the SDK or simply hide it and show a `show videos` button. If `YES`, it will dismiss the SDK, if `NO` it will hide it and show the button. Default value is `YES`
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionHideActionsDismissTheSDK;

/// Ammount of time (in milliseconds) the user must watch a video Ad before it becomes skipable in PIP. `-1` indicates the video must be watched in full. Default is `0` (i.e. user can skip at any time).
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionVideoAdSkipBlockInPIPMillisecondsKey;

//Indicates if sound should be on when video or video Ads are displayed for the firs time in the SDK session. Default is NO
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionVideoSoundIsOnByDefaultKey;

//The maximum allowed amount of time which SDK has to load its resources. Default value is 1.5 seconds.
//If timeout occurs, and the SDK hasn't completed its loading operations - it won't be presented
FOUNDATION_EXPORT NSString *const kBUZZSDKOptionSDKLoadTimeoutKey;

///Indicates whether card stack should be rotated or not
FOUNDATION_EXPORT NSString *const kBUZZSDKPrivateOptionStackRotationEnabledKey;


#endif /* BUZZSDKOptions_h */
