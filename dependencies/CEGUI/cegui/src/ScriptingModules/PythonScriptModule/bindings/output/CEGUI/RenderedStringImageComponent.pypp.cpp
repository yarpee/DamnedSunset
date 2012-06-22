// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "RenderedStringImageComponent.pypp.hpp"

namespace bp = boost::python;

struct RenderedStringImageComponent_wrapper : CEGUI::RenderedStringImageComponent, bp::wrapper< CEGUI::RenderedStringImageComponent > {

    RenderedStringImageComponent_wrapper(CEGUI::RenderedStringImageComponent const & arg )
    : CEGUI::RenderedStringImageComponent( arg )
      , bp::wrapper< CEGUI::RenderedStringImageComponent >(){
        // copy constructor
        
    }

    RenderedStringImageComponent_wrapper( )
    : CEGUI::RenderedStringImageComponent( )
      , bp::wrapper< CEGUI::RenderedStringImageComponent >(){
        // null constructor
    
    }

    RenderedStringImageComponent_wrapper(::CEGUI::String const & imageset, ::CEGUI::String const & image )
    : CEGUI::RenderedStringImageComponent( boost::ref(imageset), boost::ref(image) )
      , bp::wrapper< CEGUI::RenderedStringImageComponent >(){
        // constructor
    
    }

    RenderedStringImageComponent_wrapper(::CEGUI::Image const * image )
    : CEGUI::RenderedStringImageComponent( boost::python::ptr(image) )
      , bp::wrapper< CEGUI::RenderedStringImageComponent >(){
        // constructor
    
    }

    virtual bool canSplit(  ) const  {
        if( bp::override func_canSplit = this->get_override( "canSplit" ) )
            return func_canSplit(  );
        else{
            return this->CEGUI::RenderedStringImageComponent::canSplit(  );
        }
    }
    
    bool default_canSplit(  ) const  {
        return CEGUI::RenderedStringImageComponent::canSplit( );
    }

    virtual ::CEGUI::RenderedStringImageComponent * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->CEGUI::RenderedStringImageComponent::clone(  );
        }
    }
    
    ::CEGUI::RenderedStringImageComponent * default_clone(  ) const  {
        return CEGUI::RenderedStringImageComponent::clone( );
    }

    virtual void draw( ::CEGUI::GeometryBuffer & buffer, ::CEGUI::Vector2 const & position, ::CEGUI::ColourRect const * mod_colours, ::CEGUI::Rect const * clip_rect, float const vertical_space, float const space_extra ) const  {
        if( bp::override func_draw = this->get_override( "draw" ) )
            func_draw( boost::ref(buffer), boost::ref(position), boost::python::ptr(mod_colours), boost::python::ptr(clip_rect), vertical_space, space_extra );
        else{
            this->CEGUI::RenderedStringImageComponent::draw( boost::ref(buffer), boost::ref(position), boost::python::ptr(mod_colours), boost::python::ptr(clip_rect), vertical_space, space_extra );
        }
    }
    
    void default_draw( ::CEGUI::GeometryBuffer & buffer, ::CEGUI::Vector2 const & position, ::CEGUI::ColourRect const * mod_colours, ::CEGUI::Rect const * clip_rect, float const vertical_space, float const space_extra ) const  {
        CEGUI::RenderedStringImageComponent::draw( boost::ref(buffer), boost::ref(position), boost::python::ptr(mod_colours), boost::python::ptr(clip_rect), vertical_space, space_extra );
    }

    virtual ::CEGUI::Size getPixelSize(  ) const  {
        if( bp::override func_getPixelSize = this->get_override( "getPixelSize" ) )
            return func_getPixelSize(  );
        else{
            return this->CEGUI::RenderedStringImageComponent::getPixelSize(  );
        }
    }
    
    ::CEGUI::Size default_getPixelSize(  ) const  {
        return CEGUI::RenderedStringImageComponent::getPixelSize( );
    }

    virtual ::size_t getSpaceCount(  ) const  {
        if( bp::override func_getSpaceCount = this->get_override( "getSpaceCount" ) )
            return func_getSpaceCount(  );
        else{
            return this->CEGUI::RenderedStringImageComponent::getSpaceCount(  );
        }
    }
    
    ::size_t default_getSpaceCount(  ) const  {
        return CEGUI::RenderedStringImageComponent::getSpaceCount( );
    }

    virtual ::CEGUI::RenderedStringImageComponent * split( float split_point, bool first_component ) {
        if( bp::override func_split = this->get_override( "split" ) )
            return func_split( split_point, first_component );
        else{
            return this->CEGUI::RenderedStringImageComponent::split( split_point, first_component );
        }
    }
    
    ::CEGUI::RenderedStringImageComponent * default_split( float split_point, bool first_component ) {
        return CEGUI::RenderedStringImageComponent::split( split_point, first_component );
    }

};

void register_RenderedStringImageComponent_class(){

    { //::CEGUI::RenderedStringImageComponent
        typedef bp::class_< RenderedStringImageComponent_wrapper, bp::bases< CEGUI::RenderedStringComponent > > RenderedStringImageComponent_exposer_t;
        RenderedStringImageComponent_exposer_t RenderedStringImageComponent_exposer = RenderedStringImageComponent_exposer_t( "RenderedStringImageComponent", "! String component that draws an image.\n", bp::init< >("! Constructor\n") );
        bp::scope RenderedStringImageComponent_scope( RenderedStringImageComponent_exposer );
        RenderedStringImageComponent_exposer.def( bp::init< CEGUI::String const &, CEGUI::String const & >(( bp::arg("imageset"), bp::arg("image") ), "! Constructor\n") );
        RenderedStringImageComponent_exposer.def( bp::init< CEGUI::Image const * >(( bp::arg("image") )) );
        bp::implicitly_convertible< CEGUI::Image const *, CEGUI::RenderedStringImageComponent >();
        { //::CEGUI::RenderedStringImageComponent::canSplit
        
            typedef bool ( ::CEGUI::RenderedStringImageComponent::*canSplit_function_type )(  ) const;
            typedef bool ( RenderedStringImageComponent_wrapper::*default_canSplit_function_type )(  ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "canSplit"
                , canSplit_function_type(&::CEGUI::RenderedStringImageComponent::canSplit)
                , default_canSplit_function_type(&RenderedStringImageComponent_wrapper::default_canSplit) );
        
        }
        { //::CEGUI::RenderedStringImageComponent::clone
        
            typedef ::CEGUI::RenderedStringImageComponent * ( ::CEGUI::RenderedStringImageComponent::*clone_function_type )(  ) const;
            typedef ::CEGUI::RenderedStringImageComponent * ( RenderedStringImageComponent_wrapper::*default_clone_function_type )(  ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "clone"
                , clone_function_type(&::CEGUI::RenderedStringImageComponent::clone)
                , default_clone_function_type(&RenderedStringImageComponent_wrapper::default_clone)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::CEGUI::RenderedStringImageComponent::draw
        
            typedef void ( ::CEGUI::RenderedStringImageComponent::*draw_function_type )( ::CEGUI::GeometryBuffer &,::CEGUI::Vector2 const &,::CEGUI::ColourRect const *,::CEGUI::Rect const *,float const,float const ) const;
            typedef void ( RenderedStringImageComponent_wrapper::*default_draw_function_type )( ::CEGUI::GeometryBuffer &,::CEGUI::Vector2 const &,::CEGUI::ColourRect const *,::CEGUI::Rect const *,float const,float const ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "draw"
                , draw_function_type(&::CEGUI::RenderedStringImageComponent::draw)
                , default_draw_function_type(&RenderedStringImageComponent_wrapper::default_draw)
                , ( bp::arg("buffer"), bp::arg("position"), bp::arg("mod_colours"), bp::arg("clip_rect"), bp::arg("vertical_space"), bp::arg("space_extra") ) );
        
        }
        { //::CEGUI::RenderedStringImageComponent::getColours
        
            typedef ::CEGUI::ColourRect const & ( ::CEGUI::RenderedStringImageComponent::*getColours_function_type )(  ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "getColours"
                , getColours_function_type( &::CEGUI::RenderedStringImageComponent::getColours )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "! Set the colour values used when rendering this component.\n\
            ! return the ColourRect object used when drawing this component.\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::getImage
        
            typedef ::CEGUI::Image const * ( ::CEGUI::RenderedStringImageComponent::*getImage_function_type )(  ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "getImage"
                , getImage_function_type( &::CEGUI::RenderedStringImageComponent::getImage )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "! Set the image to be drawn by this component.\n\
            ! return the current set image that will be drawn by this component\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::getPixelSize
        
            typedef ::CEGUI::Size ( ::CEGUI::RenderedStringImageComponent::*getPixelSize_function_type )(  ) const;
            typedef ::CEGUI::Size ( RenderedStringImageComponent_wrapper::*default_getPixelSize_function_type )(  ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "getPixelSize"
                , getPixelSize_function_type(&::CEGUI::RenderedStringImageComponent::getPixelSize)
                , default_getPixelSize_function_type(&RenderedStringImageComponent_wrapper::default_getPixelSize) );
        
        }
        { //::CEGUI::RenderedStringImageComponent::getSize
        
            typedef ::CEGUI::Size const & ( ::CEGUI::RenderedStringImageComponent::*getSize_function_type )(  ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "getSize"
                , getSize_function_type( &::CEGUI::RenderedStringImageComponent::getSize )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "! set the size for rendering the image (0s mean 'normal' size)\n\
            ! return the size for rendering the image (0s mean 'normal' size)\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::getSpaceCount
        
            typedef ::size_t ( ::CEGUI::RenderedStringImageComponent::*getSpaceCount_function_type )(  ) const;
            typedef ::size_t ( RenderedStringImageComponent_wrapper::*default_getSpaceCount_function_type )(  ) const;
            
            RenderedStringImageComponent_exposer.def( 
                "getSpaceCount"
                , getSpaceCount_function_type(&::CEGUI::RenderedStringImageComponent::getSpaceCount)
                , default_getSpaceCount_function_type(&RenderedStringImageComponent_wrapper::default_getSpaceCount) );
        
        }
        { //::CEGUI::RenderedStringImageComponent::setColours
        
            typedef void ( ::CEGUI::RenderedStringImageComponent::*setColours_function_type )( ::CEGUI::ColourRect const & ) ;
            
            RenderedStringImageComponent_exposer.def( 
                "setColours"
                , setColours_function_type( &::CEGUI::RenderedStringImageComponent::setColours )
                , ( bp::arg("cr") )
                , "! return the current set image that will be drawn by this component\n\
            ! Set the colour values used when rendering this component.\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::setColours
        
            typedef void ( ::CEGUI::RenderedStringImageComponent::*setColours_function_type )( ::CEGUI::colour const & ) ;
            
            RenderedStringImageComponent_exposer.def( 
                "setColours"
                , setColours_function_type( &::CEGUI::RenderedStringImageComponent::setColours )
                , ( bp::arg("c") )
                , "! Set the colour values used when rendering this component.\n\
            ! Set the colour values used when rendering this component.\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::setImage
        
            typedef void ( ::CEGUI::RenderedStringImageComponent::*setImage_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            
            RenderedStringImageComponent_exposer.def( 
                "setImage"
                , setImage_function_type( &::CEGUI::RenderedStringImageComponent::setImage )
                , ( bp::arg("imageset"), bp::arg("image") )
                , "! Set the image to be drawn by this component.\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::setImage
        
            typedef void ( ::CEGUI::RenderedStringImageComponent::*setImage_function_type )( ::CEGUI::Image const * ) ;
            
            RenderedStringImageComponent_exposer.def( 
                "setImage"
                , setImage_function_type( &::CEGUI::RenderedStringImageComponent::setImage )
                , ( bp::arg("image") )
                , "! Set the image to be drawn by this component.\n\
            ! Set the image to be drawn by this component.\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::setSize
        
            typedef void ( ::CEGUI::RenderedStringImageComponent::*setSize_function_type )( ::CEGUI::Size const & ) ;
            
            RenderedStringImageComponent_exposer.def( 
                "setSize"
                , setSize_function_type( &::CEGUI::RenderedStringImageComponent::setSize )
                , ( bp::arg("sz") )
                , "! return the ColourRect object used when drawing this component.\n\
            ! set the size for rendering the image (0s mean 'normal' size)\n" );
        
        }
        { //::CEGUI::RenderedStringImageComponent::split
        
            typedef ::CEGUI::RenderedStringImageComponent * ( ::CEGUI::RenderedStringImageComponent::*split_function_type )( float,bool ) ;
            typedef ::CEGUI::RenderedStringImageComponent * ( RenderedStringImageComponent_wrapper::*default_split_function_type )( float,bool ) ;
            
            RenderedStringImageComponent_exposer.def( 
                "split"
                , split_function_type(&::CEGUI::RenderedStringImageComponent::split)
                , default_split_function_type(&RenderedStringImageComponent_wrapper::default_split)
                , ( bp::arg("split_point"), bp::arg("first_component") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
    }

}
