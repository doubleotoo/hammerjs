/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SourceCode_h
#define SourceCode_h

#include "SourceProvider.h"

namespace JSC {

    class SourceCode {
    public:
        SourceCode(SourceProvider* provider)
            : m_provider(provider)
            , m_startChar(0)
            , m_endChar(m_provider->length())
            , m_firstLine(1)
        {
        }

        SourceCode(SourceProvider*, int, int, int)
        {
            // Not supported!
            CRASH();
        }

        ~SourceCode()
        {
            delete m_provider;
        }

        bool isNull() const { return !m_provider; }
        int firstLine() const { return m_firstLine; }
        SourceProvider* provider() const { return m_provider; }
        int startOffset() const { return m_startChar; }
        int endOffset() const { return m_endChar; }
        const UChar* data() const { return m_provider->data() + m_startChar; }
        int length() const { return m_endChar - m_startChar; }

    private:
        SourceProvider* m_provider;
        int m_startChar;
        int m_endChar;
        int m_firstLine;
    };

    inline SourceCode makeSource(const UString& source, const UString& url = UString())
    {
        return SourceCode(new UStringSourceProvider(source, url));
    }

} // namespace JSC

#endif // SourceCode_h
