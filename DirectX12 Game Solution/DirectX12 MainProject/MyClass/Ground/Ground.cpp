#include "Ground.h"

void Ground::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\Forest\\bg_remains.X");	
	model->SetPosition(0.0f, pos_y, 10.0f);
}

void Ground::Render() {
	model->Draw();
}
