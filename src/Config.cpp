#include "Config.h"


const std::string Config::g_MapGeneratorHeader = "GenerationSetup";
const std::string Config::g_LoadHeader = "GameSave";

std::array<int, Config::g_MaxUpgrade> const Config::g_UpgradeCosts = { 0, 500, 1000, 1500, 2500 };
std::string const Config::g_OutOfStockString = "Ouf Of Stock!";


std::array<int, Config::g_MaxUpgrade> const Config::g_FuelCapacity = { 100, 200, 350, 500, 750 };
std::array<std::string, Config::g_MaxUpgrade> const Config::g_FuelNames = { "Basic Tank", "Advanced Tank", "Quality Tank", "Huge Tank", "Enormous Tank" };

// Armor:
std::array<int, Config::g_MaxUpgrade> const Config::g_MaxArmor = { 20, 40, 70, 110, 150 };
std::array<std::string, Config::g_MaxUpgrade> const Config::g_ArmorNames = { "Basic Armor", "Advanced Armor", "Quality Armor", "Durable Armor", "Titanium Armor" };

// Drill:
std::array<double, Config::g_MaxUpgrade> const Config::g_DrillSpeeds = { 1.5, 2.5, 3.5, 4.5, 5.5 };
std::array<std::string, Config::g_MaxUpgrade> const Config::g_DrillNames = { "Basic Drill", "Advanced Drill", "Quality Drill", "Hardened Drill", "Titanium Drill" };

std::string const Config::g_SaveGamePrefix = "GameSave";
std::string const Config::g_SaveLocation = "saves/";
