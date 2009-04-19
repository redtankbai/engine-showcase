#include "RendererSystemCameraComponent.h"

#include "../Input/InputSystemComponent.h"


void RendererSystemCameraComponent::Observe( ISubject* subject, unsigned int systemChanges )
{
	RendererSystemComponent::Observe( subject, systemChanges );

	ISystemComponent* component = static_cast< ISystemComponent* >( subject );

	if ( component->GetType( ) == InputSystemType )
	{
		InputSystemComponent* inputComponent = static_cast< InputSystemComponent* >( component );

		if ( System::Changes::Input::Mouse_Moved & systemChanges )
		{
			float mouseXDelta = inputComponent->GetProperties( )[ "mouseXDelta" ].GetValue< int >( );
			_xHistory.pop_back( );
			_xHistory.push_front( mouseXDelta );

			float mouseYDelta = inputComponent->GetProperties( )[ "mouseYDelta" ].GetValue< int >( );
			_yHistory.pop_back( );
			_yHistory.push_front( mouseYDelta );
		}
	}
}

void RendererSystemCameraComponent::PushChanges( unsigned int systemChanges )
{
	if ( _observer != 0 )
	{
		_observer->Observe( this, systemChanges );
	}
}

void RendererSystemCameraComponent::Update( float deltaMilliseconds )
{
	RendererSystemComponent::Update( deltaMilliseconds );

	SceneNode::ObjectIterator objects = _sceneNode->getAttachedObjectIterator( );

	float xResult = this->AverageInputHistory( _xHistory, _weightModifier );
	float yResult = this->AverageInputHistory( _yHistory, _weightModifier );

	while( objects.hasMoreElements( ) )
	{
		MovableObject* object = objects.getNext( );

		if( object->getMovableType( ) == "Camera" )
		{
			Camera* camera = _scene->GetSceneManager( )->getCamera( object->getName( ) );

			_sceneNode->yaw( Degree( -xResult ) );
			camera->pitch( Degree( yResult ) );
		}
	}

	_xHistory.pop_back( );
	_xHistory.push_front( 0.0f );

	_yHistory.pop_back( );
	_yHistory.push_front( 0.0f );

	this->PushChanges( System::Changes::Geometry::Orientation );
}

void RendererSystemCameraComponent::Initialize( AnyValueMap properties )
{
	RendererSystemComponent::Initialize( properties );

	for( int i = 0; i < _historySize; i++ )
	{
		_xHistory.push_front( 0.0f );
		_yHistory.push_front( 0.0f );
	}
}

float RendererSystemCameraComponent::AverageInputHistory( const History& inputHistory, const float& weightModifier )
{
	int index = 0;
	float sum = 0.0f;

	for ( History::const_iterator i = inputHistory.begin( ); i != inputHistory.end( ); ++i )
	{
		sum += ( *i ) * pow( weightModifier, index++ );
	}

	return sum / _historySize;
}