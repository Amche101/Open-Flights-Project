/**
 * @file vertex.h
 * Definition and (minimal) implementation of an vertex class.
 */

#pragma once

#include <string>
#include <limits.h>

using std::string;

/**
 * Represents an vertex in a graph; used by the Graph class.
 *
 * @author Haijian Wang
 * @date Fall 2020
 */
class Node
{
  public:
    string name_;// the name of this airport
    double latitude_;
    double longitude_;
    string label_;//label for each vertex

    /**
     * Parameter constructor for unweighted graphs.
     * @param ID - The OpenFlights identifier for this airport(vertex)
     */
    Node(string name)
        : name_(name), latitude_(-1.0), longitude_(-1.0)
    { /* nothing */
    }

    /**
     * Parameter constructor for unweighted graphs.
     * @param latitude - latitude of the airport
     * @param longitude - longitude of the airport
     */
    Node(double latitude, double longitude)
        : name_("No Name"), latitude_(latitude), longitude_(longitude)
    { /* nothing */
    }

    /**
     * Parameter constructor for weighted graphs.
     * @param name - the name of this airport
     * @param latitude - latitude of the airport
     * @param longitude - longitude of the airport
     */
    Node(string name, double latitude, double longitude)
        :name_(name), latitude_(latitude), longitude_(longitude)
    { /* nothing */
    }

    /**
     * Default constructor.
     */
    Node() :name_(""), latitude_(-1.0), longitude_(-1.0)
    { /* nothing */
    }

    /**
     * Compares two vertices.
     * @param other - the vertex to compare with
     */
    bool operator==(Node& other) const
    {
        if (this->name_ != other.name_)
            return false;
        if (this->latitude_ != other.latitude_)
            return false;
        if (this->longitude_ != other.longitude_)
            return false;
        return true;
    }
private:


};
