//
//  ViewController.h
//  BlockCompositionTest
//
//  Created by Xcode Developer on 9/5/22.
//

@import UIKit;
@import Foundation;
#import <objc/runtime.h>
#include <simd/simd.h>
#include <stdio.h>
#import <stdlib.h>
#include <Block.h>
#include <math.h>
#include <dispatch/dispatch.h>
#include <libkern/osatomic.h>
#include <sys/types.h>
#include <sys/mman.h>
@import CoreFoundation;

typedef typeof(unsigned long) predicate;
typedef typeof(const predicate(^)(void)) stored_predicate;
typedef typeof(const stored_predicate(^)(predicate)) predicate_storable;
typedef typeof(const predicate (^)(stored_predicate)) unstored_predicate;
typedef typeof(const predicate_storable(^)(unstored_predicate)) predicate_unstorable; // for storing the unstored_predicate to a new product_storable to create a new stored_predicate (this is how you pass a single predicate from block to block to invoke them in a particular order, one-at-a-time)
// TO-DO: Create a block that allows for simultaneous execution of predicate blocks, either because the order of invocation is not relevant or the predicates are different or their respective predicates join to form a single predicate for another predicate block, etc.
typedef typeof(const stored_predicate(^)(predicate)) predicate_store;

stored_predicate (^ const __strong store_predicate)(predicate) = ^ (predicate pred) {
    return ^ predicate {
        return pred;
    };
};


^{
    predicate initial_pred = 1UL;
    stored_predicate stored_predicate_composition = store_predicate(initial_pred);
};

typedef typeof(const joined_predicate_block(^)(predicate_evaluation)) joined_predicate_evaluation_block;

// the predicate blocks are invoked using their stored predicate
// Two situations:
//      - passing the output of an invoked predicate block (a predicate) that becomes the stored predicate of a new predicate block
//      - passing the output of an invoked predicate block combined with a new predicate that becomes the stored predicate of a new predicate block

//typedef typeof(const predicate_blk_ref (^)(predicate_ref)) predicate_blk;
//typedef typeof(const predicate_blk_ref (^)(predicate_join)) predicate_blk_composition;
//typedef typeof(const predicate_join (^)(predicate_join)) predicate_blk_composition;
//typedef typeof(const void *) predicate_blk_t;



predicate_join joined_predicate = ^ (predicate_blk_ref predicate_blk) {
    return store_predicate_ref(predicate_blk());
};


predicate_blk_ref (^compose_predicate_blk)(predicate_blk_t, predicate_blk_ref) = ^ predicate_blk_ref (predicate_blk_ref pred_blk_ref_a, predicate_blk_ref pred_blk_ref_b) {
    return store_predicate_ref(store_predicate_ref(join(pred_blk_a()))());
};


predicate_blk_t (^ const __strong retain_predicate_blk)(predicate_blk_ref) = ^ (predicate_blk_ref predicate_b) {
    return Block_copy((predicate_blk_t)CFBridgingRetain(predicate_b));
};

predicate_blk_ref (^release_predicate_blk)(predicate_blk_t) = ^ (predicate_blk_t predicate_expr) {
    return (typeof(predicate_blk_ref))CFBridgingRelease(predicate_expr);
};

static predicate_blk_ref predicate_block_composition = NULL;
static predicate_blk_ref (^compose_predicates)(predicate_blk_ref) = ^ predicate_blk_ref (predicate_blk_ref predicate_b) {
    static dispatch_once_t onceSecurePredicate;
    dispatch_once(&onceSecurePredicate, ^{
        predicate_block_composition = predicate_blk(1UL);
    });
    predicate_block_composition = predicate_b(predicate_block_composition());
    predicate_blk_ref predicate_block_composition_ref = release_
    predicate_block_composition = retain_predicate_blk(predicate_blk(1UL));
    return predicate_block_composition;
};

//unsigned long (^(^evaluate_predicate_blk)(const unsigned long))(const void * _Nonnull) = ^ (const unsigned long predicate) {
//    return ^ (const void * predicate_expr) {
//        return ((typeof(const unsigned long (^)(const unsigned long)))CFBridgingRelease(predicate_expr))(predicate);
//    };
//};


//predicate_blk(touch_property);
//const void * predicate_blk_ptr_x = predicate_blk_ref_t(p_ref);



@interface ViewController : UIViewController


@end

