#include "DomainShader.h"

#include "../../api/Application.h"

DomainShader::DomainShader(ID3D10Blob* compiledShader) {
	Application::getInstance()->getAPI()->getDevice()->CreateDomainShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, &m_shader);
}

DomainShader::~DomainShader() {
	Memory::safeRelease(m_shader);
}

void DomainShader::bind() {
	Application::getInstance()->getAPI()->getDeviceContext()->DSSetShader(m_shader, 0, 0);
}