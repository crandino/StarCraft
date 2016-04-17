#ifndef __SCV_ANIMATIONS_H__
#define __SCV_ANIMATIONS_H__

//---------------Idle Animation-----------------
idle_up.frames.push_back({ 0, 0, 72, 64 });
idle_right.frames.push_back({ 288, 0, 72, 64 });
idle_down.frames.push_back({ 576, 0, 72, 64 });
idle_left.frames.push_back({ 864, 0, 72, 64 });
//----------------------------------------------

//--------------Walking Animations--------------
walk_right_up.frames.push_back({ 144, 0, 72, 64 });
walk_right_down.frames.push_back({ 432, 0, 72, 64 });
walk_left_down.frames.push_back({ 720, 0, 72, 64 });
walk_left_up.frames.push_back({ 1008, 0, 72, 64 });
//----------------------------------------------

//--------------Repair Animations---------------		
repair_up.frames.push_back({ 0, 64, 72, 64 });
repair_up.frames.push_back({ 0, 128, 72, 64 });
repair_up.speed = 0.01f;
repair_up.loop = true;

repair_right_up.frames.push_back({ 144, 64, 72, 64 });
repair_right_up.frames.push_back({ 144, 128, 72, 64 });
repair_right_up.speed = 0.01f;
repair_right_up.loop = true;

repair_right.frames.push_back({ 288, 64, 72, 64 });
repair_right.frames.push_back({ 288, 128, 72, 64 });
repair_right.speed = 0.01f;
repair_right.loop = true;

repair_right_down.frames.push_back({ 432, 64, 72, 64 });
repair_right_down.frames.push_back({ 432, 128, 72, 64 });
repair_right_down.speed = 0.01f;
repair_right_down.loop = true;

repair_down.frames.push_back({ 576, 64, 72, 64 });
repair_down.frames.push_back({ 576, 128, 72, 64 });
repair_down.speed = 0.01f;
repair_down.loop = true;

repair_left_down.frames.push_back({ 720, 64, 72, 64 });
repair_left_down.frames.push_back({ 720, 128, 72, 64 });
repair_left_down.speed = 0.01f;
repair_left_down.loop = true;

repair_left.frames.push_back({ 864, 64, 72, 64 });
repair_left.frames.push_back({ 864, 128, 72, 64 });
repair_left.speed = 0.01f;
repair_left.loop = true;

repair_left_up.frames.push_back({ 1008, 64, 72, 64 });
repair_left_up.frames.push_back({ 1008, 128, 72, 64 });
repair_left_up.speed = 0.01f;
repair_left_up.loop = true;
//----------------------------------------------


#endif //!__SCV_ANIMATIONS_H__