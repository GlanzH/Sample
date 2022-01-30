#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CoinManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/EnumManager/EnumManager.h"

/**
 * @detail �R�C�����o�����������������ɂȂ�����A
 * �@�@�@�@�R�C�����o�������閇�������߂�֐������Ƃɋ��߂�����
 * �@�@�@�@Generator�֐��ŃR�C�������B
 */

int CoinManager::Update(const float deltaTime) {
	Iterator();

	Generator();

	if (coin.size() > 0) {
		for (auto coins : coin) {
			coins->Update(deltaTime);
		}
	}

	return 0;
}

/**
 * @fn �����ɂ���ă��[�V������؂�ւ���
 * @return �Ȃ�
 * @detail �G��|������(�R���{��)�ɂ���ăR�C�����o�������閇�������߂�֐������A
 * �@�@�@�@for���ł��̐��R�C�����쐬������
 */
void CoinManager::Generator() {
	std::random_device pos_x_seed;
	random = std::mt19937(pos_x_seed());

	//for(int i = 0; i < ��; ++i){
	distribute = std::uniform_int_distribution<int>(-60, 60);
	 int pos_x = distribute(random);

	//coin.push_back(Create(SimpleMath::Vector3(pos_x, 0,80)));
	//}
}

Coin* CoinManager::Create(SimpleMath::Vector3 position) {
	Coin* create_coin = new Coin;
	create_coin->LoadAssets(position);

	return create_coin;
}

void CoinManager::Iterator() {
	for (auto itr = coin.begin(); itr != coin.end();)
	{
		if ((*itr)->LifeDeathDecision() == LIVE) {
			itr++;
		}
		else {
			if ((*itr)->LifeDeathDecision() == DEAD) {
				StatusManager::Instance().SetAddScore(30);
				itr = coin.erase(itr);
			}
			else {
				itr = coin.erase(itr);
			}
		}
	}
}

void CoinManager::OnCollisionEnter(Coin* this_coin) {
	this_coin->GetCoin();
}

void CoinManager::ComboCoin()
{
	switch (combo)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	default:
		if (combo >= 5) {
			float BonusCoin = (combo * 50.0f) - 100.0f;
		

		}
		break;
	}
}
