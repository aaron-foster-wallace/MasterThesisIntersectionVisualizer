#include "Material.h"
#include "../shader/ShaderSet.h"

using namespace DirectX;
using namespace SimpleMath;

Material::Material(ShaderSet* shaderSet)
	: m_customSRVs(nullptr)
	, m_numTextures(3)
	, m_shader(shaderSet)
{
	m_phongSettings.ka = 1.f;
	m_phongSettings.kd = 1.f;
	m_phongSettings.ks = 1.f;
	m_phongSettings.shininess = 10.f;
	m_phongSettings.modelColor = Vector4::One;
	m_phongSettings.hasDiffuseTexture = 0;
	m_phongSettings.hasNormalTexture = 0;
	m_phongSettings.hasSpecularTexture = 0;

}
Material::~Material() { }

void Material::bind() {
	m_shader->setCBufferVar("sys_material", (void*)&getPhongSettings(), sizeof(PhongSettings));
	m_shader->setTexture2D("sys_texDiffuse", m_srvs[0]);
	m_shader->setTexture2D("sys_texNormal", m_srvs[1]);
	m_shader->setTexture2D("sys_texSpecular", m_srvs[2]);
	m_shader->bind();
}

void Material::setKa(float ka) {
	m_phongSettings.ka = ka;
}
void Material::setKd(float kd) {
	m_phongSettings.kd = kd;
}
void Material::setKs(float ks) {
	m_phongSettings.ks = ks;
}
void Material::setShininess(float shininess) {
	m_phongSettings.shininess = shininess;
}
void Material::setColor(const DirectX::SimpleMath::Vector4& color) {
	m_phongSettings.modelColor = color;
}


void Material::setDiffuseTexture(const std::string& filename) {
	getAndInsertTexture(filename, 0);
	m_phongSettings.hasDiffuseTexture = 1;
}
void Material::setDiffuseTexture(ID3D11ShaderResourceView* srv) {
	m_srvs[0] = srv;
	m_phongSettings.hasDiffuseTexture = 1;
}


void Material::setNormalTexture(const std::string& filename) {
	getAndInsertTexture(filename, 1);
	m_phongSettings.hasNormalTexture = 1;
}
void Material::setNormalTexture(ID3D11ShaderResourceView* srv) {
	m_srvs[1] = srv;
	m_phongSettings.hasNormalTexture = 1;
}


void Material::setSpecularTexture(const std::string& filename) {
	getAndInsertTexture(filename, 2);
	m_phongSettings.hasSpecularTexture = 1;
}
void Material::setSpecularTexture(ID3D11ShaderResourceView* srv) {
	m_srvs[2] = srv;
	m_phongSettings.hasSpecularTexture = 1;
}


void Material::setTextures(ID3D11ShaderResourceView** srvs, UINT numTextures) {
	m_numTextures = numTextures;
	m_customSRVs = srvs;
}


void Material::getAndInsertTexture(const std::string& filename, int arraySlot) {

	DXTexture* t = &Application::getInstance()->getResourceManager().getDXTexture(filename);
	m_srvs[arraySlot] = *t->getResourceView();

}

ID3D11ShaderResourceView* const* Material::getTextures(UINT& numTextures) {
	numTextures = m_numTextures;
	if (m_customSRVs)
		return m_customSRVs;
	else
		return m_srvs;
}

const Material::PhongSettings& Material::getPhongSettings() const {
	return m_phongSettings;
}

ShaderSet* Material::getShader() const {
	return m_shader;
}

// TODO: remove
//float Material::getKa() const {
//	return m_phongSettings.ka;
//}
//float Material::getKd() const {
//	return m_phongSettings.kd;
//}
//float Material::getKs() const {
//	return m_phongSettings.ks;
//}
//float Material::getShininess() const {
//	return m_phongSettings.shininess;
//}
//const DirectX::SimpleMath::Vector4& Material::getColor() const {
//	return m_phongSettings.modelColor;
//}
//const bool* Material::getTextureFlags() const {
//	return m_phongSettings.textureFlags;
//}