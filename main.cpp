// main.cpp (v11 - Formattazione JD)

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

#include "AA+.h"

// --- Dichiarazioni delle Funzioni ---
struct HeliocentricCoords
{
    double Longitude;
    double Latitude;
    double RadiusVector;
};

double CalcolaLongitudinePlutoneSchlyter(double jd, bool bHighPrecision);
double CalcolaLongitudineGeocentrica(const HeliocentricCoords& planetaCoords, const HeliocentricCoords& terraCoords);
void StampaLongitudine(const std::string& nomeCorpo, double longitudine);
void CalcolaEStampaLongitudini(const CAADate& data);

// --- Funzione Principale ---

int main()
{
    std::ifstream inputFile("data.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Errore: Impossibile aprire il file 'data.txt'. Assicurati che esista nella stessa directory dell'eseguibile." << std::endl;
        return 1;
    }

    std::string line;
    if (std::getline(inputFile, line))
    {
        for (char& c : line) 
        {
            if (c == 'T' || c == ':' || c == '-') 
            {
                c = ' ';
            }
        }

        std::stringstream ss(line);
        int anno, mese, giorno, ora, minuti;
        double secondi;

        if (ss >> anno >> mese >> giorno >> ora >> minuti >> secondi)
        {
            CAADate data(anno, mese, giorno, ora, minuti, secondi, true);
            CalcolaEStampaLongitudini(data);
        }
        else
        {
            std::cerr << "Errore: Formato data non valido in 'data.txt'. Usare AAAA-MM-GGTHH:MM:SS" << std::endl;
            return 1;
        }
    }

    return 0;
}

// --- Implementazione delle Funzioni ---

void CalcolaEStampaLongitudini(const CAADate& data)
{
    double jd = data.Julian();
    bool bHighPrecision = false; 

    std::cout << "\nCalcolo per: " 
              << data.Year() << "-" << data.Month() << "-" << data.Day() 
              << " " << data.Hour() << ":" << data.Minute() << ":" << data.Second()
              << " (JD: " << static_cast<long long>(jd) << ")" << std::endl; // Modifica qui
    std::cout << "------------------------------------------------------------" << std::endl;

    double lonSole = CAASun::ApparentEclipticLongitude(jd, bHighPrecision);
    StampaLongitudine("Sole", lonSole);
    double lonLuna = CAAMoon::EclipticLongitude(jd);
    StampaLongitudine("Luna", lonLuna);

    HeliocentricCoords terraCoords;
    terraCoords.Longitude = CAAEarth::EclipticLongitude(jd, bHighPrecision);
    terraCoords.Latitude = CAAEarth::EclipticLatitude(jd, bHighPrecision);
    terraCoords.RadiusVector = CAAEarth::RadiusVector(jd, bHighPrecision);

    HeliocentricCoords planetaCoords;

    planetaCoords.Longitude = CAAMercury::EclipticLongitude(jd, bHighPrecision);
    planetaCoords.Latitude = CAAMercury::EclipticLatitude(jd, bHighPrecision);
    planetaCoords.RadiusVector = CAAMercury::RadiusVector(jd, bHighPrecision);
    StampaLongitudine("Mercurio", CalcolaLongitudineGeocentrica(planetaCoords, terraCoords));

    planetaCoords.Longitude = CAAVenus::EclipticLongitude(jd, bHighPrecision);
    planetaCoords.Latitude = CAAVenus::EclipticLatitude(jd, bHighPrecision);
    planetaCoords.RadiusVector = CAAVenus::RadiusVector(jd, bHighPrecision);
    StampaLongitudine("Venere", CalcolaLongitudineGeocentrica(planetaCoords, terraCoords));

    planetaCoords.Longitude = CAAMars::EclipticLongitude(jd, bHighPrecision);
    planetaCoords.Latitude = CAAMars::EclipticLatitude(jd, bHighPrecision);
    planetaCoords.RadiusVector = CAAMars::RadiusVector(jd, bHighPrecision);
    StampaLongitudine("Marte", CalcolaLongitudineGeocentrica(planetaCoords, terraCoords));

    planetaCoords.Longitude = CAAJupiter::EclipticLongitude(jd, bHighPrecision);
    planetaCoords.Latitude = CAAJupiter::EclipticLatitude(jd, bHighPrecision);
    planetaCoords.RadiusVector = CAAJupiter::RadiusVector(jd, bHighPrecision);
    StampaLongitudine("Giove", CalcolaLongitudineGeocentrica(planetaCoords, terraCoords));

    planetaCoords.Longitude = CAASaturn::EclipticLongitude(jd, bHighPrecision);
    planetaCoords.Latitude = CAASaturn::EclipticLatitude(jd, bHighPrecision);
    planetaCoords.RadiusVector = CAASaturn::RadiusVector(jd, bHighPrecision);
    StampaLongitudine("Saturno", CalcolaLongitudineGeocentrica(planetaCoords, terraCoords));

    planetaCoords.Longitude = CAAUranus::EclipticLongitude(jd, bHighPrecision);
    planetaCoords.Latitude = CAAUranus::EclipticLatitude(jd, bHighPrecision);
    planetaCoords.RadiusVector = CAAUranus::RadiusVector(jd, bHighPrecision);
    StampaLongitudine("Urano", CalcolaLongitudineGeocentrica(planetaCoords, terraCoords));

    planetaCoords.Longitude = CAANeptune::EclipticLongitude(jd, bHighPrecision);
    planetaCoords.Latitude = CAANeptune::EclipticLatitude(jd, bHighPrecision);
    planetaCoords.RadiusVector = CAANeptune::RadiusVector(jd, bHighPrecision);
    StampaLongitudine("Nettuno", CalcolaLongitudineGeocentrica(planetaCoords, terraCoords));

    double lonPlutone = CalcolaLongitudinePlutoneSchlyter(jd, bHighPrecision);
    StampaLongitudine("Plutone", lonPlutone);
}

void StampaLongitudine(const std::string& nomeCorpo, double longitudine)
{
    std::cout << nomeCorpo << ":\t" << longitudine << "°" << std::endl;
}

double CalcolaLongitudineGeocentrica(const HeliocentricCoords& planetaCoords, const HeliocentricCoords& terraCoords)
{
    CAA3DCoordinate planeta_helio_rect;
    planeta_helio_rect.X = planetaCoords.RadiusVector * cos(CAACoordinateTransformation::DegreesToRadians(planetaCoords.Latitude)) * cos(CAACoordinateTransformation::DegreesToRadians(planetaCoords.Longitude));
    planeta_helio_rect.Y = planetaCoords.RadiusVector * cos(CAACoordinateTransformation::DegreesToRadians(planetaCoords.Latitude)) * sin(CAACoordinateTransformation::DegreesToRadians(planetaCoords.Longitude));
    planeta_helio_rect.Z = planetaCoords.RadiusVector * sin(CAACoordinateTransformation::DegreesToRadians(planetaCoords.Latitude));

    CAA3DCoordinate terra_helio_rect;
    terra_helio_rect.X = terraCoords.RadiusVector * cos(CAACoordinateTransformation::DegreesToRadians(terraCoords.Longitude));
    terra_helio_rect.Y = terraCoords.RadiusVector * sin(CAACoordinateTransformation::DegreesToRadians(terraCoords.Longitude));
    terra_helio_rect.Z = 0;

    double x_geo = planeta_helio_rect.X - terra_helio_rect.X;
    double y_geo = planeta_helio_rect.Y - terra_helio_rect.Y;
    double z_geo = planeta_helio_rect.Z;

    double lon_geo = CAACoordinateTransformation::RadiansToDegrees(atan2(y_geo, x_geo));

    return CAACoordinateTransformation::MapTo0To360Range(lon_geo);
}

double CalcolaLongitudinePlutoneSchlyter(double jd, bool bHighPrecision)
{
    double d = jd - 2451543.5;
    double S_rad = CAACoordinateTransformation::DegreesToRadians(50.03 + 0.033459652 * d);
    double P_rad = CAACoordinateTransformation::DegreesToRadians(238.95 + 0.003968789 * d);

    double lon_ecl_helio = 238.9508 + 0.00400703 * d - 19.799 * sin(P_rad) + 19.848 * cos(P_rad) + 0.897 * sin(2*P_rad) - 4.956 * cos(2*P_rad) + 0.610 * sin(3*P_rad) + 1.211 * cos(3*P_rad) - 0.341 * sin(4*P_rad) - 0.190 * cos(4*P_rad) + 0.128 * sin(5*P_rad) - 0.034 * cos(5*P_rad) - 0.038 * sin(6*P_rad) + 0.031 * cos(6*P_rad) + 0.020 * sin(S_rad-P_rad) - 0.010 * cos(S_rad-P_rad);
    double lat_ecl_helio = -3.9082 - 5.453 * sin(P_rad) - 14.975 * cos(P_rad) + 3.527 * sin(2*P_rad) + 1.673 * cos(2*P_rad) - 1.051 * sin(3*P_rad) + 0.328 * cos(3*P_rad) + 0.179 * sin(4*P_rad) - 0.292 * cos(4*P_rad) + 0.019 * sin(5*P_rad) + 0.100 * cos(5*P_rad) - 0.031 * sin(6*P_rad) - 0.026 * cos(6*P_rad) + 0.011 * cos(S_rad-P_rad);
    double r_helio = 40.72 + 6.68 * sin(P_rad) + 6.90 * cos(P_rad) - 1.18 * sin(2*P_rad) - 0.03 * cos(2*P_rad) + 0.15 * sin(3*P_rad) - 0.14 * cos(3*P_rad);

    HeliocentricCoords plutoCoords = {lon_ecl_helio, lat_ecl_helio, r_helio};
    HeliocentricCoords terraCoords = {CAAEarth::EclipticLongitude(jd, bHighPrecision), CAAEarth::EclipticLatitude(jd, bHighPrecision), CAAEarth::RadiusVector(jd, bHighPrecision)};
    
    return CalcolaLongitudineGeocentrica(plutoCoords, terraCoords);
}
