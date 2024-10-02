#include "Core.h"
#include <vector>
#include <iostream>

Core::Core(const std::vector<float>& m_resistance, const float m_u01, const float m_i03, const float m_i04)
	: resistance(m_resistance), u01(m_u01), i03(m_i03), i04(m_i04) 
{
	solveSystem();
}

std::vector<std::vector<float>> Core::getDefaultMatrix() {

    std::vector<float> row1 = { getVoltage(0), getVoltage(1), 0, 0 };
    std::vector<float> row2 = { 0, -getVoltage(1), getVoltage(2), getVoltage(3) };
    std::vector<float> row3 = { 1, -1, -1, 0 };
    std::vector<float> row4 = { 0, 0, 1, -1 };

    std::vector<std::vector<float>> matrix = { row1, row2, row3, row4 };

    return matrix;
}

std::vector<float> Core::getVectorVoltage()
{
    for (size_t i = 0; i < resistance.size(); i++)
    {
        voltage.push_back(amperage[i] * resistance[i]);;
    }
    return voltage;
}

std::vector<float> Core::getAnsVector() {
    std::vector<float> ans(4, 0);
    ans[0] = u01;
    ans[2] = i03;
    ans[3] = i04 - i03;
    return ans;
}

std::vector<float> gaussElimination(std::vector<std::vector<float>>& A, std::vector<float>& b) {
    int n = A.size();

    for (int i = 0; i < n; ++i) {
        // ����� ������������� �������� ��� �������� �������
        float maxEl = std::abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > maxEl) {
                maxEl = std::abs(A[k][i]);
                maxRow = k;
            }
        }

        // ������������ ����� (���� ����������)
        if (i != maxRow) {
            std::swap(A[i], A[maxRow]);
            std::swap(b[i], b[maxRow]);
        }

        // ��������� ���� ����� ���� �������
        for (int k = i + 1; k < n; ++k) {
            float factor = A[k][i] / A[i][i];
            b[k] -= factor * b[i]; // ��������� ������ b
            for (int j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    // �������� ���
    std::vector<float> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i] / A[i][i];
        for (int k = i - 1; k >= 0; --k) {
            b[k] -= A[k][i] * x[i];
        }
    }

    return x;
}

std::vector<float> Core::solveSystem() {
    std::vector<std::vector<float>> A = getDefaultMatrix();
    std::vector<float> b = getAnsVector();

    amperage = gaussElimination(A, b);
    voltage = getVectorVoltage();

    std::cout << "amperage:" << std::endl;
    for (size_t i = 0; i < amperage.size(); ++i) {
        std::cout << "i[" << i << "] = " << amperage[i] << std::endl;
    }

    std::cout << "voltage:" << std::endl;
    for (size_t i = 0; i < voltage.size(); ++i) {
        std::cout << "u[" << i << "] = " << voltage[i] << std::endl;
    }

    float absoluteError = getAbsoluteError();

    std::cout << "Absolute error: " << absoluteError << std::endl;
    std::cout << "Relative error: " << getRelativeError(absoluteError) << "%" << std::endl;


    return amperage;
}

float Core::getAbsoluteError()
{
    float summ = 0;
    for (size_t i = 0; i < voltage.size(); i++)
    {
        summ += voltage[i] * amperage[i];
    }

    summ += i03 * voltage[2];
    summ += i04 * voltage[3];
    summ -= u01 * amperage[0];
	return summ;
}

float Core::getRelativeError(float absoluteError)
{
    float summ = 0;
    for (size_t i = 0; i < voltage.size(); i++)
    {
        summ += voltage[i] * amperage[i];
    }
    summ += std::abs(i03 * voltage[2]);
    summ += std::abs(i04 * voltage[3]);
    summ += std::abs(u01 * amperage[0]);
	return std::abs(absoluteError) * 100 / (summ*0,5);
}

float Core::getVoltage(int idResistance)
{
	return resistance.at(idResistance);
}