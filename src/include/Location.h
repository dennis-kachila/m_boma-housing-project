#ifndef LOCATION_H
#define LOCATION_H

#include <string>

/**
 * @brief Location class to represent counties and towns
 */
class Location {
private:
    int id;
    std::string name;
    std::string type; // "county" or "town"
    int parentId;     // For towns, this is the county ID

public:
    /**
     * @brief Constructor with parameters
     * @param id Location identifier
     * @param name Location name
     * @param type Location type ("county" or "town")
     * @param parentId Parent location ID for towns
     */
    Location(int id, const std::string& name, const std::string& type, int parentId = -1);
    
    /**
     * @brief Get location ID
     * @return Location ID
     */
    int getId() const;
    
    /**
     * @brief Get location name
     * @return Location name
     */
    std::string getName() const;
    
    /**
     * @brief Get location type
     * @return Location type ("county" or "town")
     */
    std::string getType() const;
    
    /**
     * @brief Get parent location ID
     * @return Parent location ID
     */
    int getParentId() const;
};

#endif // LOCATION_H
