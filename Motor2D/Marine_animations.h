#ifndef __MARINE_ANIMATIONS_H__
#define __MARINE_ANIMATIONS_H__

//---------------Idle Animation-----------------
idle_up.frames.push_back({ 0, 0, 64, 64 });
idle_up.frames.push_back({ 0, 64, 64, 64 });
idle_up.frames.push_back({ 0, 128, 64, 64 });
idle_up.frames.push_back({ 0, 64, 64, 64 });
idle_up.frames.push_back({ 0, 0, 64, 64 });
idle_up.speed = 0.005f;
idle_up.loop = true;

idle_right_up.frames.push_back({ 128, 0, 64, 64 });
idle_right_up.frames.push_back({ 128, 64, 64, 64 });
idle_right_up.frames.push_back({ 128, 128, 64, 64 });
idle_right_up.frames.push_back({ 128, 64, 64, 64 });
idle_right_up.frames.push_back({ 128, 0, 64, 64 });
idle_right_up.speed = 0.005f;
idle_right_up.loop = true;

idle_right.frames.push_back({ 256, 0, 64, 64 });
idle_right.frames.push_back({ 256, 64, 64, 64 });
idle_right.frames.push_back({ 256, 128, 64, 64 });
idle_right.frames.push_back({ 256, 64, 64, 64 });
idle_right.frames.push_back({ 256, 0, 64, 64 });
idle_right.speed = 0.005f;
idle_right.loop = true;

idle_right_down.frames.push_back({ 384, 0, 64, 64 });
idle_right_down.frames.push_back({ 384, 64, 64, 64 });
idle_right_down.frames.push_back({ 384, 128, 64, 64 });
idle_right_down.frames.push_back({ 384, 64, 64, 64 });
idle_right_down.frames.push_back({ 384, 0, 64, 64 });
idle_right_down.speed = 0.005f;
idle_right_down.loop = true;

idle_down.frames.push_back({ 448, 0, 64, 64 });
idle_down.frames.push_back({ 448, 64, 64, 64 });
idle_down.frames.push_back({ 448, 128, 64, 64 });
idle_down.frames.push_back({ 448, 64, 64, 64 });
idle_down.frames.push_back({ 448, 0, 64, 64 });
idle_down.speed = 0.005f;
idle_down.loop = true;

idle_left_down.frames.push_back({ 640, 0, 64, 64 });
idle_left_down.frames.push_back({ 640, 64, 64, 64 });
idle_left_down.frames.push_back({ 640, 128, 64, 64 });
idle_left_down.frames.push_back({ 640, 64, 64, 64 });
idle_left_down.frames.push_back({ 640, 0, 64, 64 });
idle_left_down.speed = 0.005f;
idle_left_down.loop = true;

idle_left.frames.push_back({ 768, 0, 64, 64 });
idle_left.frames.push_back({ 768, 64, 64, 64 });
idle_left.frames.push_back({ 768, 128, 64, 64 });
idle_left.frames.push_back({ 768, 64, 64, 64 });
idle_left.frames.push_back({ 768, 0, 64, 64 });
idle_left.speed = 0.005f;
idle_left.loop = true;

idle_left_up.frames.push_back({ 960, 0, 64, 64 });
idle_left_up.frames.push_back({ 960, 64, 64, 64 });
idle_left_up.frames.push_back({ 960, 128, 64, 64 });
idle_left_up.frames.push_back({ 960, 64, 64, 64 });
idle_left_up.frames.push_back({ 960, 0, 64, 64 });
idle_left_up.speed = 0.005f;
idle_left_up.loop = true;
//----------------------------------------------

//--------------Walking Animations--------------
walk_up.frames.push_back({ 0, 0, 64, 64 });
walk_up.frames.push_back({ 0, 256, 64, 64 });
walk_up.frames.push_back({ 0, 320, 64, 64 });
walk_up.frames.push_back({ 0, 384, 64, 64 });
walk_up.frames.push_back({ 0, 448, 64, 64 });
walk_up.frames.push_back({ 0, 512, 64, 64 });
walk_up.frames.push_back({ 0, 576, 64, 64 });
walk_up.frames.push_back({ 0, 640, 64, 64 });
walk_up.frames.push_back({ 0, 704, 64, 64 });
walk_up.frames.push_back({ 0, 768, 64, 64 });
walk_up.speed = 0.02f;

one.frames.push_back({ 64, 0, 64, 64 });

walk_right_up.frames.push_back({ 128, 0, 64, 64 });
walk_right_up.frames.push_back({ 128, 256, 64, 64 });
walk_right_up.frames.push_back({ 128, 320, 64, 64 });
walk_right_up.frames.push_back({ 128, 384, 64, 64 });
walk_right_up.frames.push_back({ 128, 448, 64, 64 });
walk_right_up.frames.push_back({ 128, 512, 64, 64 });
walk_right_up.frames.push_back({ 128, 576, 64, 64 });
walk_right_up.frames.push_back({ 128, 640, 64, 64 });
walk_right_up.frames.push_back({ 128, 704, 64, 64 });
walk_right_up.frames.push_back({ 128, 768, 64, 64 });
walk_right_up.speed = 0.02f;

three.frames.push_back({ 192, 0, 64, 64 });

walk_right.frames.push_back({ 256, 0, 64, 64 });
walk_right.frames.push_back({ 256, 256, 64, 64 });
walk_right.frames.push_back({ 256, 320, 64, 64 });
walk_right.frames.push_back({ 256, 384, 64, 64 });
walk_right.frames.push_back({ 256, 448, 64, 64 });
walk_right.frames.push_back({ 256, 512, 64, 64 });
walk_right.frames.push_back({ 256, 576, 64, 64 });
walk_right.frames.push_back({ 256, 640, 64, 64 });
walk_right.frames.push_back({ 256, 704, 64, 64 });
walk_right.frames.push_back({ 256, 768, 64, 64 });
walk_right.speed = 0.02f;

five.frames.push_back({ 320, 0, 64, 64 });

walk_right_down.frames.push_back({ 384, 0, 64, 64 });
walk_right_down.frames.push_back({ 384, 256, 64, 64 });
walk_right_down.frames.push_back({ 384, 320, 64, 64 });
walk_right_down.frames.push_back({ 384, 384, 64, 64 });
walk_right_down.frames.push_back({ 384, 448, 64, 64 });
walk_right_down.frames.push_back({ 384, 512, 64, 64 });
walk_right_down.frames.push_back({ 384, 576, 64, 64 });
walk_right_down.frames.push_back({ 384, 640, 64, 64 });
walk_right_down.frames.push_back({ 384, 704, 64, 64 });
walk_right_down.frames.push_back({ 384, 768, 64, 64 });
walk_right_down.speed = 0.02f;

seven.frames.push_back({ 448, 0, 64, 64 });
walk_down.frames.push_back({ 512, 0, 64, 64 });
walk_down.frames.push_back({ 512, 256, 64, 64 });
walk_down.frames.push_back({ 512, 320, 64, 64 });
walk_down.frames.push_back({ 512, 384, 64, 64 });
walk_down.frames.push_back({ 512, 448, 64, 64 });
walk_down.frames.push_back({ 512, 512, 64, 64 });
walk_down.frames.push_back({ 512, 576, 64, 64 });
walk_down.frames.push_back({ 512, 640, 64, 64 });
walk_down.frames.push_back({ 512, 704, 64, 64 });
walk_down.frames.push_back({ 512, 768, 64, 64 });
walk_down.speed = 0.02f;

nine.frames.push_back({ 576, 0, 64, 64 });

walk_left_down.frames.push_back({ 640, 0, 64, 64 });
walk_left_down.frames.push_back({ 640, 256, 64, 64 });
walk_left_down.frames.push_back({ 640, 320, 64, 64 });
walk_left_down.frames.push_back({ 640, 384, 64, 64 });
walk_left_down.frames.push_back({ 640, 448, 64, 64 });
walk_left_down.frames.push_back({ 640, 512, 64, 64 });
walk_left_down.frames.push_back({ 640, 576, 64, 64 });
walk_left_down.frames.push_back({ 640, 640, 64, 64 });
walk_left_down.frames.push_back({ 640, 704, 64, 64 });
walk_left_down.frames.push_back({ 640, 768, 64, 64 });
walk_left_down.speed = 0.02f;

eleven.frames.push_back({ 704, 0, 64, 64 });

walk_left.frames.push_back({ 768, 0, 64, 64 });
walk_left.frames.push_back({ 768, 256, 64, 64 });
walk_left.frames.push_back({ 768, 320, 64, 64 });
walk_left.frames.push_back({ 768, 384, 64, 64 });
walk_left.frames.push_back({ 768, 448, 64, 64 });
walk_left.frames.push_back({ 768, 512, 64, 64 });
walk_left.frames.push_back({ 768, 576, 64, 64 });
walk_left.frames.push_back({ 768, 640, 64, 64 });
walk_left.frames.push_back({ 768, 704, 64, 64 });
walk_left.frames.push_back({ 768, 768, 64, 64 });
walk_left.speed = 0.02f;

thirdteen.frames.push_back({ 832, 0, 64, 64 });

walk_left_up.frames.push_back({ 896, 0, 64, 64 });
walk_left_up.frames.push_back({ 896, 256, 64, 64 });
walk_left_up.frames.push_back({ 896, 320, 64, 64 });
walk_left_up.frames.push_back({ 896, 384, 64, 64 });
walk_left_up.frames.push_back({ 896, 448, 64, 64 });
walk_left_up.frames.push_back({ 896, 512, 64, 64 });
walk_left_up.frames.push_back({ 896, 576, 64, 64 });
walk_left_up.frames.push_back({ 896, 640, 64, 64 });
walk_left_up.frames.push_back({ 896, 704, 64, 64 });
walk_left_up.frames.push_back({ 896, 768, 64, 64 });
walk_left_up.speed = 0.02f;

fifteen.frames.push_back({ 960, 0, 64, 64 });
//----------------------------------------------

//-----------MARINE ATTACK----------------------
attack_up.frames.push_back({ 0, 128, 64, 64 });
attack_up.frames.push_back({ 0, 192, 64, 64 });
attack_up.speed = 0.01f;
attack_up.loop = true;


attack_right_up.frames.push_back({ 128, 128, 64, 64 });
attack_right_up.frames.push_back({ 128, 192, 64, 64 });
attack_right_up.speed = 0.01f;
attack_right_up.loop = true;


attack_right.frames.push_back({ 256, 128, 64, 64 });
attack_right.frames.push_back({ 256, 192, 64, 64 });
attack_right.speed = 0.01f;
attack_right.loop = true;

attack_right_down.frames.push_back({ 384, 128, 64, 64 });
attack_right_down.frames.push_back({ 384, 192, 64, 64 });
attack_right_down.speed = 0.01f;
attack_right_down.loop = true;

attack_down.frames.push_back({ 512, 128, 64, 64 });
attack_down.frames.push_back({ 512, 192, 64, 64 });
attack_down.speed = 0.01f;
attack_down.loop = true;

attack_left_down.frames.push_back({ 640, 128, 64, 64 });
attack_left_down.frames.push_back({ 640, 192, 64, 64 });
attack_left_down.speed = 0.01f;
attack_left_down.loop = true;

attack_left.frames.push_back({ 768, 128, 64, 64 });
attack_left.frames.push_back({ 768, 192, 64, 64 });
attack_left.speed = 0.01f;
attack_left.loop = true;

attack_left_up.frames.push_back({ 896, 128, 64, 64 });
attack_left_up.frames.push_back({ 896, 192, 64, 64 });
attack_left_up.speed = 0.01f;
attack_left_up.loop = true;
//----------------------------------------------

#endif // !__MARINE_ANIMATIONS_H__
