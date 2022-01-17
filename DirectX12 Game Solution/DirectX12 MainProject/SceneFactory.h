//
// SceneFactory.h
//

#include "TitleScene.h"
#include "MainScene.h"
#include "ResultScene.h"
#include "EndingScene.h"

class SceneFactory final {
public:
	static std::unique_ptr<Scene> CreateScene(const NextScene nextScene)
	{
		std::unique_ptr<Scene> scene;
		switch (nextScene) {
		case NextScene::TitleScene:	scene = std::make_unique<TitleScene>();	break;
		case NextScene::MainScene:	scene = std::make_unique<MainScene>();	break;
		case NextScene::ResultScene:scene = std::make_unique<ResultScene>();break;
		case NextScene::EndScene:scene = std::make_unique<EndScene>(); break;

		}
		return scene;
	}
};