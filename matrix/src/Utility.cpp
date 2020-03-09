#include "Utility.h"
#include "Logger.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace MX
{
  int max_window_width = Constants::max_screen_width;
  int max_window_height = Constants::max_screen_height;

  namespace Utility
  {
    bool write_file(const std::string& message, const std::string &path)
    {
      std::ofstream stream(path);

      if (!stream)
      {
        MX_FATAL("MX: Utility: Write to file: Can not open file: " + path);
        return false;
      }

      stream << message;
      stream.close();
      return true;
    }

    bool write_file(const char* message, const std::string &path)
    {
      std::ofstream stream(path);

      if (!stream)
      {
        MX_FATAL("MX: Utility: Write to file: Can not open file: " + path);
        return false;
      }

      stream << message;
      stream.close();
      return true;
    }

    std::string parse_file(const std::string& path)
    {
      std::ifstream stream(path);

      if (!stream)
      {
        MX_FATAL("MX: Utility: Parse file: Can not open file: " + path);
        return "";
      }

      std::string line;
      std::stringstream ss[1];

      while (getline(stream, line))
      {
        ss[0] << line << '\n';
      }

      stream.close();
      return ss[0].str();
    }

    std::string tokenize_line(const std::string &delimiter)
    {
      return "";
    }

    std::string f_str(float num)
    {
      std::ostringstream buff;
      buff << num;
      return buff.str();
    }

    std::string f_str(float num, float num_decimals)
    {
      std::string temp = std::to_string(num);
      size_t found = temp.find('.');
      return temp.substr(0, found + static_cast<size_t>(num_decimals) + 1);
    }

    std::string remove_file_ending(const std::string &name)
    {
      size_t hit = name.find_last_of('.');

      if (hit != std::string::npos)
        return name.substr(0, hit);

      return name;
    }

    std::string get_file_ending(const std::string& file)
    {
      auto found_extension = file.find_last_of('.');

      if (found_extension != std::string::npos)
        return file.substr(found_extension);
      // is a directory
      else
        return ".d";
    }

    std::string get_file_name(const std::string& path)
    {
      auto found_last_slash = path.find_last_of('/');
      
      std::string result = "__UNDEF__";

      if (found_last_slash != std::string::npos)
      {
        result = path.substr(found_last_slash + 1);  
      }
      else
        throw std::runtime_error("MX: Utils: Get File Name: Invalid path: " + path);
    
      return result;
    }

    void find_all_files_of_same_type(const char* path, std::vector<std::string>* results, const std::string& type, bool only_file_name)
    {
      boost::filesystem::path p(path);

      // is a folder
      if (boost::filesystem::is_directory(p))
      {
        boost::filesystem::directory_iterator end_itr;

        for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
        {
          find_all_files_of_same_type(itr->path().string().c_str(), results, type);
        }
      }
      // is a file
      else
      {
        if (get_file_ending(path) == type)
        {
          if (only_file_name)
            results->push_back(get_file_name(path));
          else
            results->push_back(path);
        }
      }
    }

    std::string get_unique_folder_name(const std::string& name, const std::string& path)
    {
      std::string file_name = name;
      std::vector<std::string> existing_names;
      
      // iterate through current
      boost::filesystem::path p(path);
      
      if (boost::filesystem::is_directory(p))
      {
        boost::filesystem::directory_iterator end_itr;

        for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
          existing_names.push_back(get_file_name(itr->path().string()));        
      }

      bool accepted = true;

      for (const auto& it : existing_names)
      {
        if (it == file_name)
          accepted = false;
      }

      // given name is unique, does not need an appendix
      if (accepted)
        return file_name;

      std::string appendix = "_1";
      file_name += appendix;

      uint64_t counter = 0;
      // make sure application does not get caught in an infinite loop
      uint64_t safe_counter = 0;

      while (!accepted)
      {
        ++safe_counter;

        if (safe_counter > Constants::max_amount_of_objects_per_scene)
          throw std::runtime_error("MX: Utils: Get unique file name: Can not find unique file name for " + path);
          
        bool already_exists = false;
        for (const std::string& it : existing_names)
        {
          if (it == file_name)
          {
            ++counter;
            appendix = "_" + std::to_string(counter);
            already_exists = true;
            break;
          }

          // remove old appendix
          auto appendix_pos = file_name.find_last_of("_");

          if (appendix_pos != std::string::npos)
          {
            std::string name_without_file_type = file_name.substr(0, appendix_pos);
            file_name = name_without_file_type + appendix;
          }
          else
            throw std::runtime_error("MX: Utils: Get unique file name: Failed to add appendix for " + path);
        }

        if (!already_exists)
          accepted = true;
      }

      return file_name;
    }

    // only considers MX_RESOURCE path
    std::string get_unique_file_name(const std::string& name)
    {
      std::string file_name = name;
      // add an appendix like _1, _2, ... to create unique names
      bool accepted = true;

      auto point_pos = file_name.find_last_of(".");
      std::string file_type = file_name.substr(point_pos);

      std::vector<std::string> existing_names;
      find_all_files_of_same_type(MX_RESOURCES, &existing_names, file_type);

      for (const auto& it : existing_names)
      {
        if (it == file_name)
          accepted = false;
      }

      // given name is unique, does not need an appendix
      if (accepted)
        return file_name;

      std::string appendix = "_1";
      file_name = file_name.substr(0, point_pos) + appendix + file_type;

      uint64_t counter = 0;
      // make sure application does not get caught in an infinite loop
      uint64_t safe_counter = 0;

      while (!accepted)
      {
        ++safe_counter;

        if (safe_counter > Constants::max_amount_of_objects_per_scene)
          throw std::runtime_error("MX: Utils: Get unique file name: Can not find unique file name for " + name);
          
        bool already_exists = false;
        for (const std::string& it : existing_names)
        {
          if (it == file_name)
          {
            ++counter;
            appendix = "_" + std::to_string(counter);
            already_exists = true;
            break;
          }

          // remove old appendix
          auto appendix_pos = file_name.find_last_of("_");
          auto file_type_pos = file_name.find_last_of(file_type);

          if (appendix_pos != std::string::npos && file_type_pos != std::string::npos)
          {
            std::string name_without_file_type = file_name.substr(0, appendix_pos);
            file_name = name_without_file_type + appendix + file_type;
          }
          else
            throw std::runtime_error("MX: Utils: Get unique file name: Failed to add appendix for " + name);
        }

        if (!already_exists)
          accepted = true;
      }

      return file_name;
    }

    uint64_t generate_id()
    {
      static uint64_t id = 0;
      return ++id;
    }
  }

  namespace Debug
  {
    void assert_condition(bool condition, const char* message)
    {
      if (!condition)
        throw std::runtime_error(message);
    }
  }
}

