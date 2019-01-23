/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2019 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

/*
 *  @author Javier Sastre
 */

#ifndef GRAPENLP_STATS_H
#define GRAPENLP_STATS_H

#include <limits>
#include <cmath>

#include <grapenlp/array.h>

namespace grapenlp
{
	//sample_type may be an integer type or a low precision float, while stat_type is sup_posed to be a high precision float
	template<typename SampleType, typename StatType = SampleType>
	class stats
	{
		typedef SampleType sample_type;
		typedef StatType stat_type;
		typedef array<sample_type> sample_array;
		typedef typename sample_array::iterator sample_array_iterator;

		sample_array samples;
		sample_array_iterator current_sample;
		sample_type min_, max_;
		stat_type mean_, std_dev_, cv_, up_, down_, p_;

	public:
		stats(std::size_t sample_count): samples(sample_count), current_sample(samples.begin()), min_(std::numeric_limits<sample_type>::max()), max_(std::numeric_limits<sample_type>::min()), mean_(static_cast<stat_type>(0))
		{}

		inline StatType mean() const
		{ return mean_; }

		inline StatType std_dev() const
		{ return std_dev_; }

		inline StatType cv() const
		{ return cv_; }

		inline StatType up() const
		{ return up_; }

		inline StatType down() const
		{ return down_; }

		inline StatType p() const
		{ return p_; }

		inline StatType min() const
		{ return min_; }

		inline StatType max() const
		{ return max_; }

		void add(sample_type sample)
		{
			*current_sample = sample;
			mean_ += static_cast<stat_type>(sample);
			if (sample < min_)
				min_ = sample;
			if (sample > max_)
				max_ = sample;
			++current_sample;
		}

		void compute_stats()
		{
			mean_ /= static_cast<stat_type>(samples.size());
			stat_type diff;
			stat_type sum_diff_sq(0.0L);
			sample_array_iterator i(samples.begin());
			for (; i != samples.end(); ++i)
			{
				diff = mean_ - static_cast<stat_type>(*i);
				sum_diff_sq += diff * diff;
			}
			std_dev_ = std::sqrt(sum_diff_sq / (samples.size() - 1));
			cv_ = (static_cast<stat_type>(100.0)) * (std_dev_ / mean_);
			up_ = mean_ + std_dev_;
			down_ = mean_ - std_dev_;
			std::size_t in_count(0);
			for (i =  samples.begin(); i != samples.end(); ++i)
			{
				if (down_ <= static_cast<stat_type>(*i) && static_cast<stat_type>(*i) <= up_)
					++in_count;
			}
			p_ = (static_cast<stat_type>(100.0)) * (static_cast<stat_type>(in_count) / static_cast<stat_type>(samples.size()));
		}
	};

    template<typename SampleType, typename StatType, typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits> &out, const stats<SampleType, StatType> &s)
    { return out << "(min, mean, max), (mean-SD, SD, mean+SD), CV, P: (" << s.min() << ", " << s.mean() << ", " << s.max() << "), (" << s.down() << ", " << s.std_dev() << ", " << s.up() << "), " << s.cv() << ", " << s.p(); }
} //namespace grapenlp

#endif /*GRAPENLP_STATS_H*/
