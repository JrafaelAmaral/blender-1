/*
 * $Id$
 *
 * ***** BEGIN LGPL LICENSE BLOCK *****
 *
 * Copyright 2009 Jörg Hermann Müller
 *
 * This file is part of AudaSpace.
 *
 * AudaSpace is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AudaSpace is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with AudaSpace.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ***** END LGPL LICENSE BLOCK *****
 */

#include "AUD_AccumulatorReader.h"

#include <cstring>

#define CC specs.channels + channel

AUD_AccumulatorReader::AUD_AccumulatorReader(AUD_IReader* reader,
											 bool additive) :
		AUD_EffectReader(reader),
		m_additive(additive),
		m_sums(AUD_SAMPLE_SIZE(reader->getSpecs())),
		m_prevs(AUD_SAMPLE_SIZE(reader->getSpecs()))
{
	memset(m_sums.getBuffer(), 0, m_sums.getSize());
	memset(m_prevs.getBuffer(), 0, m_prevs.getSize());
}

void AUD_AccumulatorReader::read(int & length, sample_t* & buffer)
{
	sample_t* buf;
	sample_t* sums;
	sample_t* prevs;
	sums = m_sums.getBuffer();
	prevs = m_prevs.getBuffer();

	AUD_Specs specs = m_reader->getSpecs();

	m_reader->read(length, buf);
	if(m_buffer.getSize() < length * AUD_SAMPLE_SIZE(specs))
		m_buffer.resize(length * AUD_SAMPLE_SIZE(specs));

	buffer = m_buffer.getBuffer();

	if(m_additive)
	{
		for(int channel = 0; channel < specs.channels; channel++)
		{
			for(int i = 0; i < length; i++)
			{
				if(buf[i * CC] > prevs[channel])
					sums[channel] += buf[i * CC] - prevs[channel];
				buffer[i * CC] = sums[channel] + buf[i * CC];
				prevs[channel] = buf[i * CC];
			}
		}
	}
	else
	{
		for(int channel = 0; channel < specs.channels; channel++)
		{
			for(int i = 0; i < length; i++)
			{
				if(buf[i * CC] > prevs[channel])
					sums[channel] += buf[i * CC] - prevs[channel];
				buffer[i * CC] = sums[channel];
				prevs[channel] = buf[i * CC];
			}
		}
	}
}
