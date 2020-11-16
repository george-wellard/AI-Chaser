#ifndef position_H
#define position_H

#define PI 3.1415927f
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0f)))
#define RAD2DEG(RAD) ((RAD)*((180.0f)/(PI)))

class EnemyPos
{
public:

	EnemyPos() {};
	EnemyPos(float newX, float newY) { x = newX; y = newY; }

	void set(float newX, float newY, float newRo) { x = newX; y = newY; Ro = newRo; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getRo() const { return Ro; }

private:

	float x, y, Ro;
};
#endif
