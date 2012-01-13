// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "ResourceProvider.pypp.hpp"

namespace bp = boost::python;

struct ResourceProvider_wrapper : CEGUI::ResourceProvider, bp::wrapper< CEGUI::ResourceProvider > {

    ResourceProvider_wrapper( )
    : CEGUI::ResourceProvider( )
      , bp::wrapper< CEGUI::ResourceProvider >(){
        // null constructor
    
    }

    virtual ::size_t getResourceGroupFileNames( ::std::vector< CEGUI::String > & out_vec, ::CEGUI::String const & file_pattern, ::CEGUI::String const & resource_group ){
        bp::override func_getResourceGroupFileNames = this->get_override( "getResourceGroupFileNames" );
        return func_getResourceGroupFileNames( boost::ref(out_vec), boost::ref(file_pattern), boost::ref(resource_group) );
    }

    virtual void loadRawDataContainer( ::CEGUI::String const & filename, ::CEGUI::RawDataContainer & output, ::CEGUI::String const & resourceGroup ){
        bp::override func_loadRawDataContainer = this->get_override( "loadRawDataContainer" );
        func_loadRawDataContainer( boost::ref(filename), boost::ref(output), boost::ref(resourceGroup) );
    }

    virtual void unloadRawDataContainer( ::CEGUI::RawDataContainer & arg0 ) {
        if( bp::override func_unloadRawDataContainer = this->get_override( "unloadRawDataContainer" ) )
            func_unloadRawDataContainer( boost::ref(arg0) );
        else{
            this->CEGUI::ResourceProvider::unloadRawDataContainer( boost::ref(arg0) );
        }
    }
    
    void default_unloadRawDataContainer( ::CEGUI::RawDataContainer & arg0 ) {
        CEGUI::ResourceProvider::unloadRawDataContainer( boost::ref(arg0) );
    }

};

void register_ResourceProvider_class(){

    { //::CEGUI::ResourceProvider
        typedef bp::class_< ResourceProvider_wrapper, boost::noncopyable > ResourceProvider_exposer_t;
        ResourceProvider_exposer_t ResourceProvider_exposer = ResourceProvider_exposer_t( "ResourceProvider", "*!\n\
        \n\
           Abstract class that defines the required interface for all resource provider sub-classes.\n\
        \n\
           A ResourceProvider is used to load both XML and binary data from an external source.  This could\
           be from a filesystem or the resource manager of a specific renderer.\n\
        *\n", bp::init< >("*************************************************************************\n\
           Construction and Destruction\n\
        *************************************************************************\n\
         *!\n\
         \n\
             Constructor for the ResourceProvider class\n\
         *\n") );
        bp::scope ResourceProvider_scope( ResourceProvider_exposer );
        { //::CEGUI::ResourceProvider::getDefaultResourceGroup
        
            typedef ::CEGUI::String const & ( ::CEGUI::ResourceProvider::*getDefaultResourceGroup_function_type )(  ) const;
            
            ResourceProvider_exposer.def( 
                "getDefaultResourceGroup"
                , getDefaultResourceGroup_function_type( &::CEGUI::ResourceProvider::getDefaultResourceGroup )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
                \n\
                    Return the current default resource group identifier.\n\
            \n\
                @return\n\
                    String object containing the currently set default resource group identifier.\n\
                *\n" );
        
        }
        { //::CEGUI::ResourceProvider::getResourceGroupFileNames
        
            typedef ::size_t ( ::CEGUI::ResourceProvider::*getResourceGroupFileNames_function_type )( ::std::vector<CEGUI::String, std::allocator<CEGUI::String> > &,::CEGUI::String const &,::CEGUI::String const & ) ;
            
            ResourceProvider_exposer.def( 
                "getResourceGroupFileNames"
                , bp::pure_virtual( getResourceGroupFileNames_function_type(&::CEGUI::ResourceProvider::getResourceGroupFileNames) )
                , ( bp::arg("out_vec"), bp::arg("file_pattern"), bp::arg("resource_group") ) );
        
        }
        { //::CEGUI::ResourceProvider::loadRawDataContainer
        
            typedef void ( ::CEGUI::ResourceProvider::*loadRawDataContainer_function_type )( ::CEGUI::String const &,::CEGUI::RawDataContainer &,::CEGUI::String const & ) ;
            
            ResourceProvider_exposer.def( 
                "loadRawDataContainer"
                , bp::pure_virtual( loadRawDataContainer_function_type(&::CEGUI::ResourceProvider::loadRawDataContainer) )
                , ( bp::arg("filename"), bp::arg("output"), bp::arg("resourceGroup") )
                , "*************************************************************************\n\
                    Accessor functions\n\
                *************************************************************************\n\
            \n\
                *!\n\
                \n\
                    Load XML data using InputSource objects.\n\
            \n\
                @param filename\n\
                    String containing a filename of the resource to be loaded.\n\
            \n\
               @param output\n\
                  Reference to a InputSourceContainer object to load the data into.\n\
               *\n\
                virtual void loadInputSourceContainer(const String& filename, InputSourceContainer& output) =\
                0;\n\
                *!\n\
                \n\
                    Load raw binary data.\n\
            \n\
                @param filename\n\
                    String containing a filename of the resource to be loaded.\n\
            \n\
               @param output\n\
                    Reference to a RawDataContainer object to load the data into.\n\
            \n\
                @param resourceGroup\n\
                    Optional String that may be used by implementations to identify the group from\n\
                    which the resource should be loaded.\n\
                *\n" );
        
        }
        { //::CEGUI::ResourceProvider::setDefaultResourceGroup
        
            typedef void ( ::CEGUI::ResourceProvider::*setDefaultResourceGroup_function_type )( ::CEGUI::String const & ) ;
            
            ResourceProvider_exposer.def( 
                "setDefaultResourceGroup"
                , setDefaultResourceGroup_function_type( &::CEGUI::ResourceProvider::setDefaultResourceGroup )
                , ( bp::arg("resourceGroup") )
                , "*!\n\
                \n\
                    Set the default resource group identifier.\n\
            \n\
                @param resourceGroup\n\
                    String object containing the default resource group identifier to be used.\n\
            \n\
                @return\n\
                    Nothing.\n\
                *\n" );
        
        }
        { //::CEGUI::ResourceProvider::unloadRawDataContainer
        
            typedef void ( ::CEGUI::ResourceProvider::*unloadRawDataContainer_function_type )( ::CEGUI::RawDataContainer & ) ;
            typedef void ( ResourceProvider_wrapper::*default_unloadRawDataContainer_function_type )( ::CEGUI::RawDataContainer & ) ;
            
            ResourceProvider_exposer.def( 
                "unloadRawDataContainer"
                , unloadRawDataContainer_function_type(&::CEGUI::ResourceProvider::unloadRawDataContainer)
                , default_unloadRawDataContainer_function_type(&ResourceProvider_wrapper::default_unloadRawDataContainer)
                , ( bp::arg("arg0") ) );
        
        }
    }

}
