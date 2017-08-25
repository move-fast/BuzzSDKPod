//
//  AdModelManager.h
//  AdDeckSDK
//
//  Created by Alfonso Hernandez on 08/02/16.
//  Copyright © 2016 Move Fast UG. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol BUZZVideoPlaylistSDKModelManagerDelegate;

/*!
 * @brief AdModelManager  Builds and controls the Model for the AdDeck
 */
@interface BUZZVideoPlaylistSDKModelManager : NSObject

#pragma mark - Delegate

/**
 Delegate for model updates.
 */
@property(nonatomic, weak) _Nullable id<BUZZVideoPlaylistSDKModelManagerDelegate> delegate;

#pragma mark - Model Refresh and Update

/**
 Builds or rebuilds the Cards Model from the Array of objects passed
 @param objectsArray An array of valid model objects (AdDeckCard objects) to build the model from.
 */
- (void)buildModelFromObjectsArray:(nonnull NSArray *)objectsArray;

/**
 Removes an object from the model at the given index if present.
 @param indexOfObjectToRemove The index to the object in the Model array to be removed (if present).
 @return A boolean indicating the success of the removal.
 */
- (BOOL)removeObjectFromModelAtIndex:(NSInteger)indexOfObjectToRemove;

/**
 Updates the Model with a new model object at a given index.
 @param newModelObject The object to add to the model.
 @param index The index for insertion
 @param completion The completion block to run when done. It takes a parameter `changes` sepcifying if changes were made.
 */
- (void)updateModelDataWithNewModelObject:(nonnull id)newModelObject atIndex:(NSInteger)index completion:(nullable void (^)(BOOL changes))completion;

/// Tells the model a specific model object has been seen
- (void)modelObjectIsSeen:(nonnull id)modelObject;


#pragma mark - Model Query
/**
 Returns the object in the Model at a given index
 @param index The index to the object in the Model array to be fetched (if present).
 @return The retrieved object from the Model Array or `nil` if out of bounds.
 */
- (nullable NSObject *)objectInModelAtIndex:(NSInteger)index;

/**
 Returns the index of an object in the model array if present.
 @param modelObject The object to search for in the Model Array.
 @param startingIndex The index where to start the lookup, the whole array will be searched starting by `startingIndex` until the end
 and then from begining until `startingIndex` - 1.
 @return An Integer indicating the `index` of the `modelObject` in the Model Array, `NSNotFound` if not in Model Array.
 */
- (NSInteger)indexOfModelObject:(nonnull id)modelObject startAtIndex:(NSInteger)startingIndex;


/**
 Returns the number of objects currently present in the Model Array.
 @return An Integer indicating the current size of the Model Array.
 */
- (NSInteger)modelObjectCount;

/**
 Indicates wheter the model manager has objects that can be delivered immediately.
 i.e. There is at least one object fully ready to be presented.
 @return A Boolean indicting the readiness of at least one model object.
 */
- (BOOL)hasDeliverableObjects;

/**
 Indicates wheter all the objects in the model are currently deliverable or no objects at all.
 i.e. All objects in model are fully ready to be presented or there are no objects in the model therefore nothing to wait for.
 @return A Boolean indicting the readiness of all model objects.
 */
- (BOOL)isFullStackDeliverable;

@end


/*!
 * @brief BUZZVideoPlaylistSDKModelManagerDelegate  Set of methos to report model state
 */
@protocol BUZZVideoPlaylistSDKModelManagerDelegate <NSObject>

@optional

/*
 Report that all model objects have became deliverable.
 This is only called if the model had objects that will report a readiness state.
 Other objects are ready by default and require no loading time.
 */
- (void)buzzVideoPlaylistSDKModelManagerAllModelObjectsAreNowDeliverable:(nonnull BUZZVideoPlaylistSDKModelManager *)modelManager;

@end

