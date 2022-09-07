//
//  ViewController.m
//  BlockCompositionTest
//
//  Created by Xcode Developer on 9/5/22.
//

#import "ViewController.h"
#include <stdio.h>
#include <stdlib.h>

@interface ViewController ()

@end

@implementation ViewController



- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    float_block_iterator(10)(retain_block(contain_block(^ const float (const float f) {
        return f;
    })));
}


@end
