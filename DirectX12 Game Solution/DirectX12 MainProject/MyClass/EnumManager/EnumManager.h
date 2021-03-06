#pragma once

/**
 * @enum EnemyState
 * 敵の状態
 */
enum EnemyState {
	LIVE,
	DEAD,
	AUTO,
};

/**
 * @enum Direct
 * 敵の向き
 */
enum Direct {
	RIGHT,
	LEFT
};


/**
 * @enum Postune
 * 敵の構え
 */
enum Postune {
	UPPER = 1,
	LOWER = 2
};