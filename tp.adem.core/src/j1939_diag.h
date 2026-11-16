// Standalone emulator compatibility implementation; simulation only.
#pragma once
#include <cstdint>
#include <vector>
namespace j1939diag {
constexpr uint32_t PGN_DM1=0xFECA,PGN_DM2=0xFECB,PGN_DM3=0xFECC,PGN_DM4=0xFECD,PGN_DM5=0xFECE,PGN_DM7=0xE400,PGN_DM11=0xFED3,PGN_DM30=0xA300,PGN_ACKM=0xE800;
struct Dtc {uint32_t spn; uint8_t fmi,cm,oc;};
struct TestResult {uint8_t id;uint32_t spn;uint8_t fmi;int32_t value,low,high;};
struct DiagState {
 std::vector<Dtc> active,stored;std::vector<TestResult> tests;
 uint8_t lamp=0,flash=0;uint16_t readinessSupported=0,readinessComplete=0;
 void recomputeLamps(){lamp=active.empty()?0:0x10;flash=0;}
 void clearActive(){active.clear();recomputeLamps();}
 void clearStored(){stored.clear();}
};
inline std::vector<uint8_t> buildDmList(uint8_t lamp,uint8_t flash,const std::vector<Dtc>& dtcs){
 std::vector<uint8_t> out={lamp,flash};
 if(dtcs.empty()){out.insert(out.end(),{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF});return out;}
 for(const auto& d:dtcs){uint32_t spn=d.spn&0x7FFFF;out.push_back(uint8_t(spn));out.push_back(uint8_t(spn>>8));out.push_back(uint8_t(((spn>>16)&7)<<5 | (d.fmi&31)));out.push_back(uint8_t((d.oc&127)|(d.cm?128:0)));}
 return out;
}
inline std::vector<uint8_t> buildDm5(const DiagState& d){
 return {uint8_t(d.active.size()),uint8_t(d.stored.size()),0xFF,0xFF,uint8_t(d.readinessSupported),uint8_t(d.readinessSupported>>8),uint8_t(d.readinessComplete),uint8_t(d.readinessComplete>>8)};
}
inline std::vector<uint8_t> buildDm30(const std::vector<TestResult>& tests){
 std::vector<uint8_t> out;for(const auto& t:tests){out.push_back(t.id);out.push_back(uint8_t(t.spn));out.push_back(uint8_t(t.spn>>8));out.push_back(uint8_t(t.spn>>16));out.push_back(t.fmi);for(auto v:{t.value,t.low,t.high}){out.push_back(uint8_t(v));out.push_back(uint8_t(v>>8));}}if(out.empty())out.assign(8,0xFF);return out;
}
}
