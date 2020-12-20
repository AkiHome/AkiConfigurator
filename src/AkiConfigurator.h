#include <Arduino.h>
#include <avr/eeprom.h>
#pragma once

struct AkiConfiguratorConf{
    int CfgStrucktsCount;
    int CfgStrucktsSize[20];
    void *CfgStruckts[20];
} AkiConfiguratorCfg;

class AkiConfigurator{
    private:
        
    public:
        bool begin();
        void readConf();
        void writeConf();
};
extern AkiConfigurator AkiCfg;
