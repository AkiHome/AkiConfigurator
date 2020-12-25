#pragma once
#include <Arduino.h>
#include <avr/eeprom.h>
#ifndef AConfStructsCount
    #define AConfStructsCount 20
#endif
#ifndef AconfEEPromSize
    #define AconfEEPromSize 1024 //bytes
#endif
#ifndef AConfEEPRomStartByte
    #define AConfEEPRomStartByte 0
#endif

struct{
    bool IsEdited;
    uint8_t  CfgStructsCount=0;
    uint16_t CfgStructsInEEPRomAddreses[AConfStructsCount+1];
    bool    *CfgStructsIsEdited[AConfStructsCount+1];
    size_t   CfgStructsSize[AConfStructsCount+1];
    void    *CfgStructs[AConfStructsCount+1];
    void    (*CfgStructWipeFunc)(void);
    char    *CfgStructsNames[AConfStructsCount+1];
}AkiConfiguratorCfg;

class AkiConfigurator{
    private:
        
    public:
        void begin(bool Clear);
        void addCfg(void *cfgStruckt, bool *cfgIsUpdated, char *cfgName, size_t cfgSize);
        void loop();
};

extern AkiConfigurator AkiCfg;
