#pragma once

#include <vector>

class Core
{
public:
	Core(const std::vector<float>& m_resistance, const float m_u01, const float m_i03, const float m_i04);
private:
	std::vector<float> resistance;
	float u01;
	float i03;
	float i04;

	std::vector<float> amperage;
	std::vector<float> voltage;

	std::vector<float> getAnsVector();
	std::vector<float> solveSystem();

	std::vector<std::vector<float>> getDefaultMatrix();

	float getVoltage(int idResistance);
	std::vector<float> getVectorVoltage();


	float getAbsoluteError();
	float getRelativeError(float absoluteError);


};

