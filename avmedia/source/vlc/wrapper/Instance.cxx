/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <wrapper/Instance.hxx>
#include "SymbolLoader.hxx"

namespace
{
    libvlc_instance_t* ( *libvlc_new ) ( int argc, const char * const *argv );
    void ( *libvlc_release ) ( libvlc_instance_t *p_instance );
    void ( *libvlc_retain ) ( libvlc_instance_t *p_instance );
}

namespace avmedia::vlc::wrapper
{
    bool Instance::LoadSymbols()
    {
        static ApiMap const VLC_INSTANCE_API[] =
        {
            SYM_MAP( libvlc_new ),
            SYM_MAP( libvlc_release ),
            SYM_MAP( libvlc_retain )
        };

        return InitApiMap( VLC_INSTANCE_API );
    }

    Instance::Instance( int argc, const char * const argv[] )
        : mInstance( libvlc_new( argc, argv ) )
    {
        if ( mInstance == nullptr)
        {
            //TODO: error
        }
    }

    Instance::Instance( const Instance& other )
    {
        operator=( other );
    }

    Instance& Instance::operator=( const Instance& other )
    {
        libvlc_release( mInstance );
        mInstance = other.mInstance;
        libvlc_retain( mInstance );
        return *this;
    }

    Instance::~Instance()
    {
        libvlc_release( mInstance );
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
