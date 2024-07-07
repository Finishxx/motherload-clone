#ifndef CONFIG_H
#define CONFIG_H

#include "Pos.h"
#include <array>

/**
 * @brief A place to store constants to debug and tune the game systems.
 * 
 */
class Config {

  public:
  static constexpr int g_FPS = 30;
  static constexpr int g_TicksInAFrame = 1000.0f / g_FPS;
  static constexpr int g_WindowWidth = 1024;
  static constexpr int g_WindowHeight = 768;

  static constexpr int g_TileSize = 100;
  static constexpr int g_MapHeight = 150;
  static constexpr int g_MapWidth = 50;

  static constexpr const char * g_Font = "assets/DejaVuSansMono.ttf";
  static constexpr int g_FontSize = g_TileSize / 5;
  static constexpr int g_MaxFontCacheSize = 25;

  static constexpr int g_MaxSpeedX = 13;
  static constexpr int g_MaxSpeedY = 50;
  static constexpr double g_Gravity = 1;
  static constexpr int g_Acceleration = 3; 

  static constexpr int g_DirtDurability = 25;
  static constexpr int g_CoalDurability = 30;
  static constexpr int g_IronDurability = 50;
  static constexpr int g_GoldDurability = 70;
  static constexpr int g_TitaniumDurability = 100;

  static constexpr int g_DirtPrice = 1;
  static constexpr int g_CoalPrice = 50;
  static constexpr int g_IronPrice = 100;
  static constexpr int g_GoldPrice = 300;
  static constexpr int g_TitaniumPrice = 500;

  static constexpr int g_FreeSpace = 20; // how many blocks to leave free in the overworld

  static constexpr int g_UndergroundEmptySpawnChance = 20;
  static constexpr int g_UnderGroundEmptySpawnDepth = 2;

  static constexpr int g_CoalSpawnChance = 10;
  static constexpr int g_CoalSpawnDepth = 1;

  static constexpr int g_IronSpawnChance = 6;
  static constexpr int g_IronSpawnChanceMax = 14;
  static constexpr int g_IronSpawnDepth = 2;

  static constexpr int g_GoldSpawnChance = 2;
  static constexpr int g_GoldSpawnChanceMax = 10;
  static constexpr int g_GoldSpawnDepth = 10;

  static constexpr int g_TitaniumSpawnChance = 0;
  static constexpr int g_TitaniumSpawnChanceMax = 6;
  static constexpr int g_TitaniumSpawnDepth = 10;

  static constexpr int g_TitaniumDamage = 5;

  static constexpr double g_FuelDepletion = 0.1;

  static const std::string g_MapGeneratorHeader;
  static const std::string g_LoadHeader;

  static constexpr char g_CategoryDelimeter = ':';
  static constexpr char g_EndOfLineDelimeter = '|';
  static constexpr char g_PosDelimeter = ';';
  static constexpr char g_True = 'T';
  static constexpr char g_False = 'F';
  static constexpr char g_MapStartDelimeter = '[';
  static constexpr char g_MapEndDelimeter = ']';
  static constexpr char g_SaveFileDelimeter = '_'; // '_'


  //Shops:
  static constexpr int g_ShopMessageLingerTime = 150;
  static constexpr int g_ShopMessageOffset = 2 * g_TileSize;

  static constexpr int g_ShopRightOffset = g_FontSize / 2;
  
  static constexpr int g_FuelHealthNameYPos = g_FontSize;
  static constexpr int g_FuelHealthPriceYPos = g_FuelHealthNameYPos + g_FontSize * 2;
  
  static constexpr int g_UpgradeNameYPos = g_FuelHealthPriceYPos + g_FontSize * 3;
  static constexpr int g_UpgradePriceYPos = g_UpgradeNameYPos + g_FontSize * 2;

  static constexpr int g_FuelHealthPrice = 25;

  static constexpr int g_MaxUpgrade = 5;
  static constexpr int g_UpgradeCategories = 3;

  static std::array<int, g_MaxUpgrade> const g_UpgradeCosts;

  static std::string const g_OutOfStockString;

  // FuelTank:
  static std::array<int, g_MaxUpgrade> const g_FuelCapacity; //{ 100, 125, 150, 200, 250 };
  static std::array<std::string, g_MaxUpgrade> const g_FuelNames; //{ "Basic tank", "Advanced tank", Quality tank, Huge tank, Enormous tank };
  
  // Armor:
  static std::array<int, g_MaxUpgrade> const g_MaxArmor; //{ 20, 35, 50, 75, 100 };
  static std::array<std::string, g_MaxUpgrade> const g_ArmorNames; //{ "Basic Armor", "Advanced Armor", Quality Armor, Durable Armor, Titanium Armor };

  // Drill:
  static std::array<double, g_MaxUpgrade> const g_DrillSpeeds; //{ 1, 1.25, 1.5, 2, 2.5 };
  static std::array<std::string, g_MaxUpgrade> const g_DrillNames; //{ "Basic Drill", "Advanced Drill", Quality Drill, Hardened Drill, Titanium Armor };

  static std::string const g_SaveGamePrefix;
  static std::string const g_SaveLocation;

};

#endif /* CONFIG_H */