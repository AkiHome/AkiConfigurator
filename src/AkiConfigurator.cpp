#include "AkiConfigurator.h"
AkiConfigurator AkiCfg=AkiConfigurator();

void AkiConfigurator::begin(bool clear){
    Serial.println("Begining AkiConfigurator");
    
    AkiConfiguratorCfg.CfgStructs[0] = (void*)&AkiConfiguratorCfg;
    AkiConfiguratorCfg.CfgStructsIsEdited[0] = &AkiConfiguratorCfg.IsEdited;
    AkiConfiguratorCfg.CfgStructsSize[0] = sizeof(AkiConfiguratorCfg);
    AkiConfiguratorCfg.CfgStructsNames[0] = (char*)"AkiHomeConfigurator";
    AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[0] = AConfEEPRomStartByte;
    AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[1] = AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[0] + AkiConfiguratorCfg.CfgStructsSize[0];
    if(clear==false){
        *AkiConfiguratorCfg.CfgStructsIsEdited[0] = false;
        eeprom_read_block((void*)AkiConfiguratorCfg.CfgStructs[0],(void*)AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[0],AkiConfiguratorCfg.CfgStructsSize[0]);
        for(uint8_t i=1;i<=AkiConfiguratorCfg.CfgStructsCount;i++){
            Serial.print("Reading config at adress: ");
            Serial.print(AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[i]);
            Serial.print(", size: ");
            Serial.print(AkiConfiguratorCfg.CfgStructsSize[i]);
            eeprom_read_block(AkiConfiguratorCfg.CfgStructs[i],(void*)AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[i],AkiConfiguratorCfg.CfgStructsSize[i]);
            Serial.print(", name: ");
            Serial.println(AkiConfiguratorCfg.CfgStructsNames[i]);
            *AkiConfiguratorCfg.CfgStructsIsEdited[i]=false;
            delay(100);
        }
        *AkiConfiguratorCfg.CfgStructsIsEdited[0] = false;
        Serial.print("Total loaded: ");
        Serial.print(AkiConfiguratorCfg.CfgStructsCount);
        Serial.println(" config's loaded");
    }else{
        *AkiConfiguratorCfg.CfgStructsIsEdited[0] = true;
    }
    
}
void AkiConfigurator::addCfg(void *cfgStruckt, bool *cfgIsUpdated, char *cfgName, size_t cfgSize){
    AkiConfiguratorCfg.CfgStructsCount ++;
    AkiConfiguratorCfg.CfgStructs[AkiConfiguratorCfg.CfgStructsCount] = cfgStruckt;
    AkiConfiguratorCfg.CfgStructsNames[AkiConfiguratorCfg.CfgStructsCount] = cfgName; 
    AkiConfiguratorCfg.CfgStructsIsEdited[AkiConfiguratorCfg.CfgStructsCount] = cfgIsUpdated;
    *AkiConfiguratorCfg.CfgStructsIsEdited[AkiConfiguratorCfg.CfgStructsCount] = true;
    AkiConfiguratorCfg.CfgStructsSize[AkiConfiguratorCfg.CfgStructsCount] = cfgSize;
    AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[AkiConfiguratorCfg.CfgStructsCount +1]=AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[AkiConfiguratorCfg.CfgStructsCount]+cfgSize;
    Serial.print("Adding configuration with number: ");
    Serial.print(AkiConfiguratorCfg.CfgStructsCount);
    Serial.print(", name: ");
    Serial.print(cfgName);
    Serial.print(" to: ");
    Serial.print(AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[AkiConfiguratorCfg.CfgStructsCount]);
    Serial.print("bit in EEPRom. It is: ");
    Serial.print(AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[AkiConfiguratorCfg.CfgStructsCount + 1]/(AconfEEPromSize/100));
    Serial.println("% of all EEPRom");
    *AkiConfiguratorCfg.CfgStructsIsEdited[0]=true;
}
void AkiConfigurator::loop(){
    for(uint8_t i=0;i<=AkiConfiguratorCfg.CfgStructsCount;i++){
        if(*AkiConfiguratorCfg.CfgStructsIsEdited[i]==true){
            Serial.print("Config: ");
            Serial.print(AkiConfiguratorCfg.CfgStructsNames[i]);
            Serial.print(" updated. Updating it in eeprom: ");
            Serial.print(AkiConfiguratorCfg.CfgStructsSize[i]);
            Serial.print(" bytes at adress: ");
            Serial.println(AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[i]);
            eeprom_update_block(AkiConfiguratorCfg.CfgStructs[i],(void*)AkiConfiguratorCfg.CfgStructsInEEPRomAddreses[i],AkiConfiguratorCfg.CfgStructsSize[i]);
            *AkiConfiguratorCfg.CfgStructsIsEdited[i]=false;
        }
    }
}
void ParceSerial(char *str, byte maxStrLength)
{
    for (uint8_t i = 0; i < maxStrLength;)
    {
        if (Serial.available() > 0)
        {
            str[i] = Serial.read();
            if (str[i] == 10)
            {
                if (str[i - 1] == 13)
                {
                    i--;
                }
                str[i] = '\0';
                break;
            }
            i++;
        }
    }
}