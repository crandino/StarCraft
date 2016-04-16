#ifndef __ZERGLING_ANIMATIONS_H__
#define __ZERGLING_ANIMATIONS_H__

//------------------Idle Animation------------------
idle_up.frames.push_back({ 0, 0, 128, 128 });
idle_right_up.frames.push_back({ 384, 0, 128, 128 });
idle_right.frames.push_back({ 512, 0, 128, 128 });
idle_right_down.frames.push_back({ 768, 0, 128, 128 });
idle_down.frames.push_back({ 1024, 0, 128, 128 });
idle_left_down.frames.push_back({ 1152, 0, 128, 128 });
idle_left.frames.push_back({ 1536, 0, 128, 128 });
idle_left_up.frames.push_back({ 1792, 0, 128, 128 });

//-----------------Walking Animation---------------
walk_up.frames.push_back({ 0, 512, 128, 128 });
walk_up.frames.push_back({ 0, 640, 128, 128 });
walk_up.frames.push_back({ 0, 768, 128, 128 });
walk_up.frames.push_back({ 0, 896, 128, 128 });
walk_up.frames.push_back({ 0, 1024, 128, 128 });
walk_up.frames.push_back({ 0, 1152, 128, 128 });
walk_up.frames.push_back({ 0, 1280, 128, 128 });
walk_up.frames.push_back({ 0, 1408, 128, 128 });
walk_up.speed = 0.02f;
walk_up.loop = true;

walk_right_up.frames.push_back({ 384, 512, 128, 128 });
walk_right_up.frames.push_back({ 384, 640, 128, 128 });
walk_right_up.frames.push_back({ 384, 768, 128, 128 });
walk_right_up.frames.push_back({ 384, 896, 128, 128 });
walk_right_up.frames.push_back({ 384, 1024, 128, 128 });
walk_right_up.frames.push_back({ 384, 1152, 128, 128 });
walk_right_up.frames.push_back({ 384, 1280, 128, 128 });
walk_right_up.frames.push_back({ 384, 1408, 128, 128 });
walk_right_up.speed = 0.02f;
walk_right_up.loop = true;

walk_right.frames.push_back({ 512, 512, 128, 128 });
walk_right.frames.push_back({ 512, 640, 128, 128 });
walk_right.frames.push_back({ 512, 768, 128, 128 });
walk_right.frames.push_back({ 512, 896, 128, 128 });
walk_right.frames.push_back({ 512, 1024, 128, 128 });
walk_right.frames.push_back({ 512, 1152, 128, 128 });
walk_right.frames.push_back({ 512, 1280, 128, 128 });
walk_right.frames.push_back({ 512, 1408, 128, 128 });
walk_right.speed = 0.02f;
walk_right.loop = true;

walk_right_down.frames.push_back({ 768, 512, 128, 128 });
walk_right_down.frames.push_back({ 768, 640, 128, 128 });
walk_right_down.frames.push_back({ 768, 768, 128, 128 });
walk_right_down.frames.push_back({ 768, 896, 128, 128 });
walk_right_down.frames.push_back({ 768, 1024, 128, 128 });
walk_right_down.frames.push_back({ 768, 1152, 128, 128 });
walk_right_down.frames.push_back({ 768, 1280, 128, 128 });
walk_right_down.frames.push_back({ 768, 1408, 128, 128 });
walk_right_down.speed = 0.02f;
walk_right_down.loop = true;

walk_down.frames.push_back({ 1024, 512, 128, 128 });
walk_down.frames.push_back({ 1024, 640, 128, 128 });
walk_down.frames.push_back({ 1024, 768, 128, 128 });
walk_down.frames.push_back({ 1024, 896, 128, 128 });
walk_down.frames.push_back({ 1024, 1024, 128, 128 });
walk_down.frames.push_back({ 1024, 1152, 128, 128 });
walk_down.frames.push_back({ 1024, 1280, 128, 128 });
walk_down.frames.push_back({ 1024, 1408, 128, 128 });
walk_down.speed = 0.02f;
walk_down.loop = true;

walk_left_down.frames.push_back({ 1152, 512, 128, 128 });
walk_left_down.frames.push_back({ 1152, 640, 128, 128 });
walk_left_down.frames.push_back({ 1152, 768, 128, 128 });
walk_left_down.frames.push_back({ 1152, 896, 128, 128 });
walk_left_down.frames.push_back({ 1152, 1024, 128, 128 });
walk_left_down.frames.push_back({ 1152, 1152, 128, 128 });
walk_left_down.frames.push_back({ 1152, 1280, 128, 128 });
walk_left_down.frames.push_back({ 1152, 1408, 128, 128 });
walk_left_down.speed = 0.02f;
walk_left_down.loop = true;

walk_left.frames.push_back({ 1536, 512, 128, 128 });
walk_left.frames.push_back({ 1536, 640, 128, 128 });
walk_left.frames.push_back({ 1536, 768, 128, 128 });
walk_left.frames.push_back({ 1536, 896, 128, 128 });
walk_left.frames.push_back({ 1536, 1024, 128, 128 });
walk_left.frames.push_back({ 1536, 1152, 128, 128 });
walk_left.frames.push_back({ 1536, 1280, 128, 128 });
walk_left.frames.push_back({ 1536, 1408, 128, 128 });
walk_left.speed = 0.02f;
walk_left.loop = true;

walk_left_up.frames.push_back({ 1792, 512, 128, 128 });
walk_left_up.frames.push_back({ 1792, 640, 128, 128 });
walk_left_up.frames.push_back({ 1792, 768, 128, 128 });
walk_left_up.frames.push_back({ 1792, 896, 128, 128 });
walk_left_up.frames.push_back({ 1792, 1024, 128, 128 });
walk_left_up.frames.push_back({ 1792, 1152, 128, 128 });
walk_left_up.frames.push_back({ 1792, 1280, 128, 128 });
walk_left_up.frames.push_back({ 1792, 1408, 128, 128 });
walk_left_up.speed = 0.02f;
walk_left_up.loop = true;

//-----------------Attack Animation---------------
attack_up.frames.push_back({ 0, 128, 128, 128 });
attack_up.frames.push_back({ 0, 256, 128, 128 });
attack_up.frames.push_back({ 0, 384, 128, 128 });
attack_up.speed = 0.008f;
attack_up.loop = true;

attack_right_up.frames.push_back({ 384, 128, 128, 128 });
attack_right_up.frames.push_back({ 384, 256, 128, 128 });
attack_right_up.frames.push_back({ 384, 384, 128, 128 });
attack_right_up.speed = 0.008f;
attack_right_up.loop = true;

attack_right.frames.push_back({ 512, 128, 128, 128 });
attack_right.frames.push_back({ 512, 256, 128, 128 });
attack_right.frames.push_back({ 512, 384, 128, 128 });
attack_right.speed = 0.008f;
attack_right.loop = true;

attack_right_down.frames.push_back({ 768, 128, 128, 128 });
attack_right_down.frames.push_back({ 768, 256, 128, 128 });
attack_right_down.frames.push_back({ 768, 384, 128, 128 });
attack_right_down.speed = 0.008f;
attack_right_down.loop = true;

attack_down.frames.push_back({ 1024, 128, 128, 128 });
attack_down.frames.push_back({ 1024, 256, 128, 128 });
attack_down.frames.push_back({ 1024, 384, 128, 128 });
attack_down.speed = 0.008f;
attack_down.loop = true;

attack_left_down.frames.push_back({ 1152, 128, 128, 128 });
attack_left_down.frames.push_back({ 1152, 256, 128, 128 });
attack_left_down.frames.push_back({ 1152, 384, 128, 128 });
attack_left_down.speed = 0.008f;
attack_left_down.loop = true;

attack_left.frames.push_back({ 1536, 128, 128, 128 });
attack_left.frames.push_back({ 1536, 256, 128, 128 });
attack_left.frames.push_back({ 1536, 384, 128, 128 });
attack_left.speed = 0.008f;
attack_left.loop = true;

attack_left_up.frames.push_back({ 1792, 128, 128, 128 });
attack_left_up.frames.push_back({ 1792, 256, 128, 128 });
attack_left_up.frames.push_back({ 1792, 384, 128, 128 });
attack_left_up.speed = 0.008f;
attack_left_up.loop = true;

//-----------------Death Animation---------------
dead.frames.push_back({ 0, 2176, 128, 128 });
dead.frames.push_back({ 128, 2176, 128, 128 });
dead.frames.push_back({ 256, 2176, 128, 128 });
dead.frames.push_back({ 384, 2176, 128, 128 });
dead.frames.push_back({ 512, 2176, 128, 128 });
dead.frames.push_back({ 640, 2176, 128, 128 });
dead.frames.push_back({ 768, 2176, 128, 128 });
dead.speed = 0.01f;
#endif