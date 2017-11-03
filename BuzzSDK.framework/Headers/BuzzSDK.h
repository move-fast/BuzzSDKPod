//
//  BuzzSDK.h
//  BuzzSDK
//
//  Created by mdv on 21/01/16.
//  Copyright © 2016 Move Fast UG. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BuzzSDK/BUZZSDKOptions.h>
#import <BuzzSDK/BUZZSDKSharedOptions.h>
#import <BuzzSDK/GDMediaPlayer.h>
#import <BuzzSDK/BUZZVideoPlaylistSDKModelManager.h>

//! Project version number for BuzzSDK.
FOUNDATION_EXPORT double BuzzSDKVersionNumber;

//! Project version string for BuzzSDK.
FOUNDATION_EXPORT const unsigned char BuzzSDKVersionString[];

/**
 
Presents the stack of cards, configured in the SDK's dashboard, including different types of Ads (e.g. Facebook Native Ads, DFP, Video Ads, etc.) on top of the host app UI.
 
To quick start the SDK please copy the lines below and paste them into your AppDelegate's <b>application:didFinishLaunchingWithOptions:launchOptions</b> method
    
    [BuzzSDK startWithAPIKey: @"YOUR_API_KEY" secretKey: @"YOUR_SECRET_KEY"];
    [BuzzSDK presentDeck];
 
BuzzSDK supports multiple presentation modes. Default presentation mode is set to <b>Manual</b>, which means that SDK will wait for a [BuzzSDK presentDeck]
call to actually present the card deck. 
 
<b>Available Presentation Modes: </b> <i>Never</i>, <i>Manual</i>, <i>Once per day</i>, <i>Once per week</i>, <i>Whenever app becomes active</i>. All modes are configurable through the dashboard.

<b>Prerequisites to running Facebook Native Ads and Medium Rectangle Ads using DFP (Double Click for Publishers)</b>

1. First, please make sure you have "-ObjC" flag set in the "Other Linker Flags" section of your app target's Build Settings.
2. Next, link either FBAudienceNetwork.framework or GoogleMobileAds.framework (or both) to your app's target.
3. Specify your "Ad placement IDs" in the SDK's dashboard.
 
<b>Advanced SDK launch example (with options):</b>
 
Set a delegate to navigate users on article card taps to relevant content inside the app:

    [BuzzSDK setDelegate:self]
 
Initialize the BuzzSDK with API key and secret key
 
    [BuzzSDK startWithAPIKey:@"YOUR_API_KEY" secretKey:@"YOUR_SECRET_KEY" andSDKOptions:sdkOptions];

Present the SDK's UI
 
    [BuzzSDK presentDeck];
 
<b>SDK Cards Styling</b>
 
Optionally, you can apply styles to the title and kicker of article and video cards.

Available styling options for card kicker & title:

 - font name
 - font size
 - text color
 - background color
 
You can find more information about supported option keys in <BUZZSDKOptions.h> header file.
 
@warning Note about the fonts. For custom fonts, which are not a part of the iOS SDK, you should include them into your app's bundle, and add corresponding key to the plist file.
 */

/**
 * UI state of the Buzz SDK.
 * BuzzSDKStateNone: The SDK is not loaded and its UI hierarchy is not set.
 * BuzzSDKStatePrepared: The SDK Session has started, the UI Hierarchy is not yet set and no content is currently being presented.
 * BuzzSDKStatePresenting: The SDK UI Hierarchy is set, and content is currently being presented.
 * BuzzSDKStateHiddenByHostApp: The SDK UI Hierarchy is set, content is displayed but currently hidden by host app request. User can not manually show it again.
 * BuzzSDKStateHiddenByUser: The SDK UI Hierarchy is set, content is displayed but currently hidden by user request. A show buttons is displayed so user can show the UI again on request.
 */
typedef enum : NSUInteger {
    BuzzSDKStateNone,
    BuzzSDKStatePrepared,
    BuzzSDKStatePresenting,
    BuzzSDKStateHiddenByHostApp,
    BuzzSDKStateHiddenByUser,
} BuzzSDKState;

@protocol BuzzSDKDelegate <NSObject>

@optional

/**
 * Notifies the delegate a Article Card has been tapped. 
 * `cardData` dictionary as configured in the dashboards is passed along.
 */
- (void)buzzSDKCardTap:(nonnull NSDictionary*)cardData;

/**
 * Notifies the delegate that the 'Remove Ads' button has been tapped.
 * When the button the Buzz SDK Card stack is minimized and any top video card sent to PIP.
 * The application should then direct the user to the payment or subscription views.
 */
- (void)buzzSDKRemoveAdsButtonTapped;


/// Notifies the delegate that the SDK has started playback of video content. This will be notified every time video playback starts if all video content was stopped or paused.
- (void)buzzSDKHasStartedVideoPlayback;


/// Notifies the delegate of a state change on the SDK. When started the SDK state is allways `BuzzSDKStateNone`
- (void)buzzSDKStateHasChanged:(BuzzSDKState)state;

@end

@interface BuzzSDK : NSObject

/**
 * @brief Initializes BuzzSDK
 * @param APIKey you can look up your API key at the dashboard
 * @param secretKey you can look up your secret key at the dashboard
 * @param groupId an Integer indicating the group configurations to be used.
 * @param SDKOptions a dictionary containing the initialization options. Please find all possible options in <BuzzSDK/BUZZSDKOptions.h> header file.
 */
+ (void)startWithAPIKey:(nonnull NSString *)APIKey secretKey:(nonnull NSString *)secretKey groupId:(NSInteger)groupId andSDKOptions:(nullable NSDictionary *)SDKOptions;

/**
 * @brief Initializes BuzzSDK
 * @param APIKey you can look up your API key at the dashboard
 * @param secretKey you can look up your secret key at the dashboard
 * @param SDKOptions a dictionary containing the initialization options. Please find all possible options in <BuzzSDK/BUZZSDKOptions.h> header file.
 */
+ (void)startWithAPIKey:(nonnull NSString *)APIKey secretKey:(nonnull NSString *)secretKey andSDKOptions:(nullable NSDictionary *)SDKOptions;

/**
 * @brief Initializes BuzzSDK. Simplified version of initialization (uses default options).
 * @param APIKey you can look up your API key at the dashboard
 * @param secretKey you can look up your secret key at the dashboard
 */
+ (void)startWithAPIKey:(nonnull NSString *)APIKey secretKey:(nonnull NSString *)secretKey;

/**
 *  @brief Sets an object to be forwarded taps on article cards.
 *  @param delegate An object that can respond to the callbacks that a user interaction on an article sends.
 */
+ (void)setDelegate:(nonnull NSObject<BuzzSDKDelegate> *)delegate;

/**
 * @brief Presents the BuzzSDK's UI on top of the host app's UI.
 * @discussion By default SDK is configured for Manual presentation. Call to this method takes the effect when 2 of the following conditions are met:
 *
 * 1. SDK Presentation Mode is set to Manual (default option).
 *
 * 2. You should first call one of the <i>start</i> methods (<b>startWithAPIKey:secretKey:andSDKOptions:</b> or <b>startWithAPIKey:secretKey:</b>).
 *
 * However you can change the presentation mode to one of available automatic presentation modes in the Dashboard.
 * @note It is safe to call this method multiple times, but only the first call will take place. All subsequent calls are ignored.
 */
+ (void)presentDeck;

/**
 * @brief Will hide the SDK UI (if presented) from the user. UI can be brought back on top of the host app UI by calling `presentDeck` again. If the UI is hidden when the app is sent to the background, the SDK will be dismissed and calling `presentDeck` will start a new SDK Session.
 */
+ (void)hideDeck;

/**
 * @brief Instructs the SDK to pause any video that is currently playing.
 */
+ (void)pause;

/**
 * @brief Will completely stop the SDK and remove it from the view hierarchy.
 */
+ (void)dismissDeck;

- (nonnull id) init __attribute__((unavailable("Please use 'startWithAPIKey:secretKey:groupId:andSDKOptions:' or 'startWithAPIKey:secretKey:' instead.")));

@end
