/*
MIT License

Copyright (c) 2016-2017

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "amf-encoder-h265.h"
#include "misc-util.cpp"

using namespace Plugin::AMD;

Plugin::AMD::EncoderH265::EncoderH265(std::shared_ptr<API::IAPI> videoAPI, API::Adapter videoAdapter, bool useOpenCL, ColorFormat colorFormat, ColorSpace colorSpace, bool fullRangeColor)
	: Encoder(Codec::HEVC, videoAPI, videoAdapter, useOpenCL, colorFormat, colorSpace, fullRangeColor) {
	AMFTRACECALL;
}


Plugin::AMD::EncoderH265::~EncoderH265() {
	AMFTRACECALL;
}


// Properties - Initialization
std::vector<Usage> Plugin::AMD::EncoderH265::CapsUsage() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_USAGE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<Usage> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back(Utility::UsageFromAMFH265((AMF_VIDEO_ENCODER_HEVC_USAGE_ENUM)enm->value));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetUsage(Usage v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_USAGE, Utility::UsageToAMFH265(v));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, Utility::UsageToString(v), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::Usage Plugin::AMD::EncoderH265::GetUsage() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_USAGE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return Utility::UsageFromAMFH265((AMF_VIDEO_ENCODER_HEVC_USAGE_ENUM)e);
}

// Properties - Static
std::vector<QualityPreset> Plugin::AMD::EncoderH265::CapsQualityPreset() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_QUALITY_PRESET, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<QualityPreset> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back(Utility::QualityPresetFromAMFH265((AMF_VIDEO_ENCODER_HEVC_QUALITY_PRESET_ENUM)enm->value));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetQualityPreset(QualityPreset v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_QUALITY_PRESET, Utility::QualityPresetToAMFH265(v));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, Utility::QualityPresetToString(v), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::QualityPreset Plugin::AMD::EncoderH265::GetQualityPreset() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_QUALITY_PRESET, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return Utility::QualityPresetFromAMFH265((AMF_VIDEO_ENCODER_HEVC_QUALITY_PRESET_ENUM)e);
}

std::pair<std::pair<uint32_t, uint32_t>, std::pair<uint32_t, uint32_t>> Plugin::AMD::EncoderH265::CapsResolution() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_FRAMESIZE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	return std::make_pair(
		std::make_pair(var->minValue.sizeValue.width, var->maxValue.sizeValue.width),
		std::make_pair(var->minValue.sizeValue.height, var->maxValue.sizeValue.height)
	);
}

void Plugin::AMD::EncoderH265::SetResolution(std::pair<uint32_t, uint32_t> v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_FRAMESIZE, ::AMFConstructSize(v.first, v.second));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %ldx%ld, error %ls (code %d)",
			m_UniqueId, v.first, v.second, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	m_Resolution.first = v.first;
	m_Resolution.second = v.second;
}

std::pair<uint32_t, uint32_t> Plugin::AMD::EncoderH265::GetResolution() {
	AMFTRACECALL;

	AMFSize e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_FRAMESIZE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	m_Resolution.first = e.width;
	m_Resolution.second = e.height;
	return std::make_pair(e.width, e.height);
}

void Plugin::AMD::EncoderH265::SetAspectRatio(std::pair<uint32_t, uint32_t> v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_ASPECT_RATIO, ::AMFConstructRatio(v.first, v.second));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %ld:%ld, error %ls (code %d)",
			m_UniqueId, v.first, v.second, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

std::pair<uint32_t, uint32_t> Plugin::AMD::EncoderH265::GetAspectRatio() {
	AMFTRACECALL;

	AMFRatio e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_ASPECT_RATIO, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return std::make_pair(e.num, e.den);
}

void Plugin::AMD::EncoderH265::SetFrameRate(std::pair<uint32_t, uint32_t> v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_FRAMERATE, ::AMFConstructRate(v.first, v.second));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %ld/%ld, error %ls (code %d)",
			m_UniqueId, v.first, v.second, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	m_FrameRate = std::make_pair(v.first, v.second);
	UpdateFrameRateValues();
}

std::pair<uint32_t, uint32_t> Plugin::AMD::EncoderH265::GetFrameRate() {
	AMFTRACECALL;

	AMFRate e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_FRAMERATE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> Unable to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	m_FrameRate = std::make_pair(e.num, e.den);
	UpdateFrameRateValues();
	return m_FrameRate;
}

std::vector<Profile> Plugin::AMD::EncoderH265::CapsProfile() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_PROFILE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<Profile> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back(Utility::ProfileFromAMFH265((AMF_VIDEO_ENCODER_HEVC_PROFILE_ENUM)enm->value));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetProfile(Profile v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_PROFILE, Utility::ProfileToAMFH265(v));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, Utility::ProfileToString(v), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::Profile Plugin::AMD::EncoderH265::GetProfile() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_PROFILE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return Utility::ProfileFromAMFH265((AMF_VIDEO_ENCODER_HEVC_PROFILE_ENUM)e);
}

std::vector<ProfileLevel> Plugin::AMD::EncoderH265::CapsProfileLevel() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_PROFILE_LEVEL, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<ProfileLevel> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back((ProfileLevel)(enm->value / 3));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetProfileLevel(ProfileLevel v) {
	AMFTRACECALL;;

	if (v == ProfileLevel::Automatic)
		v = Utility::H265ProfileLevel(m_Resolution, m_FrameRate);

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_PROFILE_LEVEL, ((int64_t)v) * 3);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %lld, error %ls (code %d)",
			m_UniqueId, (int64_t)v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::ProfileLevel Plugin::AMD::EncoderH265::GetProfileLevel() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_PROFILE_LEVEL, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (ProfileLevel)(e / 3);
}

std::vector<HEVC::Tier> Plugin::AMD::EncoderH265::CapsTier() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_TIER, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<HEVC::Tier> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back(Utility::TierFromAMFH265((AMF_VIDEO_ENCODER_HEVC_TIER_ENUM)enm->value));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetTier(HEVC::Tier v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_TIER, Utility::TierToAMFH265(v));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, Utility::TierToString(v), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::HEVC::Tier Plugin::AMD::EncoderH265::GetTier() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_TIER, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (HEVC::Tier)e;
}

std::pair<uint64_t, uint64_t> Plugin::AMD::EncoderH265::CapsMaximumReferenceFrames() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_MAX_NUM_REFRAMES, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	return std::make_pair(var->minValue.int64Value, var->maxValue.int64Value);
}

void Plugin::AMD::EncoderH265::SetMaximumReferenceFrames(uint64_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_MAX_NUM_REFRAMES, v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %lld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint64_t Plugin::AMD::EncoderH265::GetMaximumReferenceFrames() {
	AMFTRACECALL;

	uint64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_MAX_NUM_REFRAMES, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, __FUNCTION_NAME__ "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

std::vector<CodingType> Plugin::AMD::EncoderH265::CapsCodingType() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_CABAC_ENABLE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<CodingType> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back(Utility::CodingTypeFromAMFH265((AMF_VIDEO_ENCODER_CODING_ENUM)enm->value));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetCodingType(CodingType v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_CABAC_ENABLE, Utility::CodingTypeToAMFH265(v));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, Utility::CodingTypeToString(v), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::CodingType Plugin::AMD::EncoderH265::GetCodingType() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_CABAC_ENABLE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> Unable to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return Utility::CodingTypeFromAMFH265((AMF_VIDEO_ENCODER_CODING_ENUM)e);
}

std::pair<uint32_t, uint32_t> Plugin::AMD::EncoderH265::CapsMaximumLongTermReferenceFrames() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetMaximumLongTermReferenceFrames(uint32_t v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

uint32_t Plugin::AMD::EncoderH265::GetMaximumLongTermReferenceFrames() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

// Properties - Dynamic
std::vector<RateControlMethod> Plugin::AMD::EncoderH265::CapsRateControlMethod() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_METHOD, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<RateControlMethod> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back(Utility::RateControlMethodFromAMFH265((AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_METHOD_ENUM)enm->value));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetRateControlMethod(RateControlMethod v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_METHOD, Utility::RateControlMethodToAMFH265(v));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, Utility::RateControlMethodToString(v), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::RateControlMethod Plugin::AMD::EncoderH265::GetRateControlMethod() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_METHOD, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return Utility::RateControlMethodFromAMFH265((AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_METHOD_ENUM)e);
}

std::vector<PrePassMode> Plugin::AMD::EncoderH265::CapsPrePassMode() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_PREANALYSIS_ENABLE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	if (var->type == amf::AMF_VARIANT_BOOL) {
		return std::vector<PrePassMode>({ PrePassMode::Disabled, PrePassMode::Enabled });
	} else {
		std::vector<PrePassMode> ret;
		for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
			AMF_LOG_ERROR("Unknown Pre-Pass Mode: %ls %lld", enm->name, enm->value);
			//ret.push_back(Utility::PrePassModeFromAMFH265((AMF_VIDEO_ENCODER_PREENCODE_MODE_ENUM)enm->value));
		}
		return ret;
	}
}

void Plugin::AMD::EncoderH265::SetPrePassMode(PrePassMode v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_PREANALYSIS_ENABLE, v != PrePassMode::Disabled);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, (v != PrePassMode::Disabled) ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::PrePassMode Plugin::AMD::EncoderH265::GetPrePassMode() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_PREANALYSIS_ENABLE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> Unable to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	if (e) {
		return PrePassMode::Enabled;
	} else {
		return PrePassMode::Disabled;
	}
}

void Plugin::AMD::EncoderH265::SetVariableBitrateAverageQualityEnabled(bool v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_ENABLE_VBAQ, v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, v ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

bool Plugin::AMD::EncoderH265::IsVariableBitrateAverageQualityEnabled() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_ENABLE_VBAQ, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetFrameSkippingEnabled(bool v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_SKIP_FRAME_ENABLE, v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, v ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

bool Plugin::AMD::EncoderH265::IsFrameSkippingEnabled() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_RATE_CONTROL_SKIP_FRAME_ENABLE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetEnforceHRDEnabled(bool v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_ENFORCE_HRD, v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, v ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

bool Plugin::AMD::EncoderH265::IsEnforceHRDEnabled() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_ENFORCE_HRD, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetFillerDataEnabled(bool v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_FILLER_DATA_ENABLE, v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, v ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

bool Plugin::AMD::EncoderH265::IsFillerDataEnabled() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_FILLER_DATA_ENABLE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetIFrameQPMinimum(uint8_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_MIN_QP_I, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %d, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint8_t Plugin::AMD::EncoderH265::GetIFrameQPMinimum() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_MIN_QP_I, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint8_t)e;
}

void Plugin::AMD::EncoderH265::SetIFrameQPMaximum(uint8_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_MAX_QP_I, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %d, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint8_t Plugin::AMD::EncoderH265::GetIFrameQPMaximum() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_MAX_QP_I, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint8_t)e;
}

void Plugin::AMD::EncoderH265::SetPFrameQPMinimum(uint8_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_MIN_QP_P, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %d, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint8_t Plugin::AMD::EncoderH265::GetPFrameQPMinimum() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_MIN_QP_P, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint8_t)e;
}

void Plugin::AMD::EncoderH265::SetPFrameQPMaximum(uint8_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_MAX_QP_P, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %d, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint8_t Plugin::AMD::EncoderH265::GetPFrameQPMaximum() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_MAX_QP_P, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint8_t)e;
}

std::pair<uint64_t, uint64_t> Plugin::AMD::EncoderH265::CapsTargetBitrate() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_TARGET_BITRATE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	return std::make_pair(var->minValue.int64Value, var->maxValue.int64Value);
}

void Plugin::AMD::EncoderH265::SetTargetBitrate(uint64_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_TARGET_BITRATE, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %lld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint64_t Plugin::AMD::EncoderH265::GetTargetBitrate() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_TARGET_BITRATE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

std::pair<uint64_t, uint64_t> Plugin::AMD::EncoderH265::CapsPeakBitrate() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_PEAK_BITRATE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	return std::make_pair(var->minValue.int64Value, var->maxValue.int64Value);
}

void Plugin::AMD::EncoderH265::SetPeakBitrate(uint64_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_PEAK_BITRATE, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %lld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint64_t Plugin::AMD::EncoderH265::GetPeakBitrate() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_PEAK_BITRATE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetIFrameQP(uint8_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_QP_I, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %d, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint8_t Plugin::AMD::EncoderH265::GetIFrameQP() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_QP_I, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint8_t)e;
}

void Plugin::AMD::EncoderH265::SetPFrameQP(uint8_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_QP_P, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %d, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint8_t Plugin::AMD::EncoderH265::GetPFrameQP() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_QP_P, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint8_t)e;
}

std::pair<uint64_t, uint64_t> Plugin::AMD::EncoderH265::CapsVBVBufferSize() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(AMF_VIDEO_ENCODER_HEVC_VBV_BUFFER_SIZE, &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	return std::make_pair(var->minValue.int64Value, var->maxValue.int64Value);
}

void Plugin::AMD::EncoderH265::SetVBVBufferSize(uint64_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_VBV_BUFFER_SIZE, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %lld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

void Plugin::AMD::EncoderH265::SetVBVBufferStrictness(double_t strictness) {
	AMFTRACECALL;

	uint64_t looseBitrate, targetBitrate, strictBitrate;

	Usage usage = GetUsage();
	if (usage == Usage::UltraLowLatency) {
		targetBitrate = GetTargetBitrate();
	} else {
		switch (this->GetRateControlMethod()) {
			case RateControlMethod::ConstantBitrate:
				targetBitrate = this->GetTargetBitrate();
				break;
			case RateControlMethod::LatencyConstrainedVariableBitrate:
			case RateControlMethod::PeakConstrainedVariableBitrate:
				targetBitrate = max(this->GetTargetBitrate(), this->GetPeakBitrate());
				break;
			case RateControlMethod::ConstantQP:
				// When using Constant QP, one will have to pick a QP that is decent
				//  in both quality and bitrate. We can easily calculate both the QP
				//  required for an average bitrate and the average bitrate itself 
				//  with these formulas:
				// BITRATE = ((1 - (QP / 51)) ^ 2) * ((Width * Height) * 1.5 * (FPSNumerator / FPSDenumerator))
				// QP = (1 - sqrt(BITRATE / ((Width * Height) * 1.5 * (FPSNumerator / FPSDenumerator)))) * 51

				auto frameSize = this->GetResolution();
				auto frameRate = this->GetFrameRate();

				double_t bitrate = frameSize.first * frameSize.second;
				switch (this->m_ColorFormat) {
					case ColorFormat::NV12:
					case ColorFormat::I420:
						bitrate *= 1.5;
						break;
					case ColorFormat::YUY2:
						bitrate *= 4;
						break;
					case ColorFormat::BGRA:
					case ColorFormat::RGBA:
						bitrate *= 3;
						break;
					case ColorFormat::GRAY:
						bitrate *= 1;
						break;
				}
				bitrate *= frameRate.first / frameRate.second;

				uint8_t qp_i = this->GetIFrameQP(),
					qp_p = this->GetPFrameQP();
				double_t qp = 1 - ((double_t)(min(qp_i, qp_p)) / 51.0);
				qp = max(qp * qp, 0.001); // Needs to be at least 0.001.

				targetBitrate = static_cast<uint32_t>(bitrate * qp);
				break;
		}
	}
	strictBitrate = static_cast<uint32_t>(targetBitrate * (m_FrameRate.second / m_FrameRate.first));
	looseBitrate = CapsTargetBitrate().second;

	// Three-Point Linear Lerp
	// 0% = looseBitrate, 50% = targetBitrate, 100% = strictBitrate
	strictness = min(max(strictness, 0.0), 1.0);
	double_t aFadeVal = min(strictness * 2.0, 1.0); // 0 - 0.5
	double_t bFadeVal = max(strictness * 2.0 - 1.0, 0.0); // 0.5 - 1.0

	double_t aFade = (looseBitrate * (1.0 - aFadeVal)) + (targetBitrate * aFadeVal);
	double_t bFade = (aFade * (1.0 - bFadeVal)) + (strictBitrate * bFadeVal);

	uint32_t vbvBufferSize = static_cast<uint32_t>(round(bFade));
	this->SetVBVBufferSize(vbvBufferSize);
}

uint64_t Plugin::AMD::EncoderH265::GetVBVBufferSize() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_VBV_BUFFER_SIZE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetVBVBufferInitialFullness(double v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_INITIAL_VBV_BUFFER_FULLNESS, (int64_t)(v * 64));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %lf (%d), error %ls (code %d)",
			m_UniqueId, v, (uint8_t)(v * 64), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

float Plugin::AMD::EncoderH265::GetInitialVBVBufferFullness() {
	AMFTRACECALL;

	int64_t e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_INITIAL_VBV_BUFFER_FULLNESS, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (e / 64.0f);
}

// Properties - Picture Control
std::vector<HEVC::GOPType> Plugin::AMD::EncoderH265::CapsGOPType() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(L"GOPType", &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	std::vector<HEVC::GOPType> ret;
	for (const amf::AMFEnumDescriptionEntry* enm = var->pEnumDescription; enm->name != nullptr; enm++) {
		ret.push_back(Utility::GOPTypeFromAMFH265(enm->value));
	}
	return ret;
}

void Plugin::AMD::EncoderH265::SetGOPType(HEVC::GOPType v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(L"GOPType", Utility::GOPTypeToAMFH265(v));
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set mode to %s, error %ls (code %d)",
			m_UniqueId, Utility::GOPTypeToString(v), m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

Plugin::AMD::HEVC::GOPType Plugin::AMD::EncoderH265::GetGOPType() {
	AMFTRACECALL;

	int64_t e;
	AMF_RESULT res = m_AMFEncoder->GetProperty(L"GOPType", &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return Utility::GOPTypeFromAMFH265(e);
}

void Plugin::AMD::EncoderH265::SetGOPSize(uint32_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_GOP_SIZE, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %ld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint32_t Plugin::AMD::EncoderH265::GetGOPSize() {
	AMFTRACECALL;

	int64_t e;
	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_GOP_SIZE, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint32_t)e;
}

void Plugin::AMD::EncoderH265::SetGOPSizeMin(uint32_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(L"GOPSizeMin", (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %ld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint32_t Plugin::AMD::EncoderH265::GetGOPSizeMin() {
	AMFTRACECALL;

	int64_t e;
	AMF_RESULT res = m_AMFEncoder->GetProperty(L"GOPSizeMin", &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint32_t)e;
}

void Plugin::AMD::EncoderH265::SetGOPSizeMax(uint32_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(L"GOPSizeMax", (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %ld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint32_t Plugin::AMD::EncoderH265::GetGOPSizeMax() {
	AMFTRACECALL;

	int64_t e;
	AMF_RESULT res = m_AMFEncoder->GetProperty(L"GOPSizeMax", &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint32_t)e;
}

void Plugin::AMD::EncoderH265::SetGOPAlignmentEnabled(bool v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

bool Plugin::AMD::EncoderH265::GetGOPAlignmentEnabled() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetIDRPeriod(uint32_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_NUM_GOPS_PER_IDR, (int64_t)v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %ld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint32_t Plugin::AMD::EncoderH265::GetIDRPeriod() {
	AMFTRACECALL;

	int64_t e;
	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_NUM_GOPS_PER_IDR, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint32_t)e;
}

void Plugin::AMD::EncoderH265::SetHeaderInsertionMode(HEVC::HeaderInsertionMode v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

Plugin::AMD::HEVC::HeaderInsertionMode Plugin::AMD::EncoderH265::GetHeaderInsertionMode() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetMaximumAccessUnitSize(uint32_t v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

uint32_t Plugin::AMD::EncoderH265::GetMaximumAccessUnitSize() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetDeblockingFilterEnabled(bool v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_DE_BLOCKING_FILTER_DISABLE, !v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set to %s, error %ls (code %d)",
			m_UniqueId, v ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

bool Plugin::AMD::EncoderH265::IsDeblockingFilterEnabled() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(L"HevcDeBlockingFilter", &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetMotionEstimationQuarterPixelEnabled(bool v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_MOTION_QUARTERPIXEL, v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set mode to %s, error %ls (code %d)",
			m_UniqueId, v ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

bool Plugin::AMD::EncoderH265::IsMotionEstimationQuarterPixelEnabled() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_MOTION_QUARTERPIXEL, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

void Plugin::AMD::EncoderH265::SetMotionEstimationHalfPixelEnabled(bool v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(AMF_VIDEO_ENCODER_HEVC_MOTION_HALF_PIXEL, v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set mode to %s, error %ls (code %d)",
			m_UniqueId, v ? "Enabled" : "Disabled", m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

bool Plugin::AMD::EncoderH265::IsMotionEstimationHalfPixelEnabled() {
	AMFTRACECALL;

	bool e;

	AMF_RESULT res = m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_MOTION_HALF_PIXEL, &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return e;
}

// Properties - Slicing
void Plugin::AMD::EncoderH265::SetSlicesPerFrame(uint32_t v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

uint32_t Plugin::AMD::EncoderH265::GetSlicesPerFrame() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetSliceControlMode(uint32_t v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

uint32_t Plugin::AMD::EncoderH265::GetSliceControlMode() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetSliceControlSize(uint32_t v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

uint32_t Plugin::AMD::EncoderH265::GetSliceControlSize() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

// Properties - Experimental
void Plugin::AMD::EncoderH265::SetQPCBOffset(uint8_t v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

uint8_t Plugin::AMD::EncoderH265::GetQPCBOffset() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetQPCROffset(uint8_t v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

uint8_t Plugin::AMD::EncoderH265::GetQPCROffset() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

std::pair<uint32_t, uint32_t> Plugin::AMD::EncoderH265::CapsInputQueueSize() {
	AMFTRACECALL;

	const amf::AMFPropertyInfo* var;
	AMF_RESULT res = m_AMFEncoder->GetPropertyInfo(L"HevcInputQueueSize", &var);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Querying capabilities failed, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}

	return std::make_pair((uint32_t)var->minValue.int64Value, (uint32_t)var->maxValue.int64Value);
}

void Plugin::AMD::EncoderH265::SetInputQueueSize(uint32_t v) {
	AMFTRACECALL;

	AMF_RESULT res = m_AMFEncoder->SetProperty(L"HevcInputQueueSize", v);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to set mode to %ld, error %ls (code %d)",
			m_UniqueId, v, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
}

uint32_t Plugin::AMD::EncoderH265::GetInputQueueSize() {
	AMFTRACECALL;
	
	int64_t e;
	AMF_RESULT res = m_AMFEncoder->GetProperty(L"HevcInputQueueSize", &e);
	if (res != AMF_OK) {
		QUICK_FORMAT_MESSAGE(errMsg, "<Id: %lld> <" __FUNCTION_NAME__ "> Failed to retrieve value, error %ls (code %d)",
			m_UniqueId, m_AMF->GetTrace()->GetResultText(res), res);
		throw std::exception(errMsg.data());
	}
	return (uint32_t)e;
}

void Plugin::AMD::EncoderH265::SetLowLatencyInternal(bool v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

bool Plugin::AMD::EncoderH265::GetLowLatencyInternal() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

void Plugin::AMD::EncoderH265::SetCommonLowLatencyInternal(bool v) {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

bool Plugin::AMD::EncoderH265::GetCommonLowLatencyInternal() {
	AMFTRACECALL;

	throw std::logic_error("The method or operation is not implemented.");
}

// Internal
void Plugin::AMD::EncoderH265::PacketPriorityAndKeyframe(amf::AMFDataPtr pData, struct encoder_packet* packet) {
	uint64_t pktType;
	pData->GetProperty(AMF_VIDEO_ENCODER_HEVC_OUTPUT_DATA_TYPE, &pktType);
	switch ((AMF_VIDEO_ENCODER_HEVC_OUTPUT_DATA_TYPE_ENUM)pktType) {
		case AMF_VIDEO_ENCODER_HEVC_OUTPUT_DATA_TYPE_I:
			packet->keyframe = true;
			packet->priority = 3;
			break;
		case AMF_VIDEO_ENCODER_HEVC_OUTPUT_DATA_TYPE_P:
			packet->priority = 1;
			break;
	}
}

AMF_RESULT Plugin::AMD::EncoderH265::GetExtraDataInternal(amf::AMFVariant* p) {
	return m_AMFEncoder->GetProperty(AMF_VIDEO_ENCODER_HEVC_EXTRADATA, p);
}
