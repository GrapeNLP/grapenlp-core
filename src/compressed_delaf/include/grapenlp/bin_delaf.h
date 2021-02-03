/*
 * GRAPENLP
 *
 * Copyright (C) 2004-2021 Javier Miguel Sastre Martínez <javier.sastre@gmail.com>
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

#ifndef GRAPENLP_BIN_DELAF_H
#define GRAPENLP_BIN_DELAF_H

#include <limits>
#include <deque>
#include <stack>
#include <memory>

#include <grapenlp/unicode.h>

namespace grapenlp
{
	class bin_delaf
	{
	public:
		class state;

		class outgoing_transition
		{
		private:
			const unsigned char byte0, byte1, byte2, byte3, byte4;

			outgoing_transition(): byte0(), byte1(), byte2(), byte3(), byte4()
			{}

		public:
			unichar get_label() const
			{
				return ((unichar)byte0) * 0x0100 +
				       ((unichar)byte1);
			}

			std::size_t get_target_state_offset() const
			{
				return ((std::size_t)byte2) * ((std::size_t)0x00010000) +
				       ((std::size_t)byte3) * ((std::size_t)0x00000100) +
				       ((std::size_t)byte4);
			}
		};

		typedef const outgoing_transition* const_outgoing_transition_iterator;

		//State class just helps to interpretate a sequence of bytes as a FST state
		//Byte 0: negation of first bit = final flag; Remaining bits are the most significant of the state transition count
		//Byte 1: less significant bits of transition count
		//Byte 2-4: if final, these 3 bytes are the word properties index (begining with de most significant byte); otherwise transitions start here
		class state
		{
		private:
			const unsigned char byte0, byte1, byte2, byte3, byte4;

			//Packed states are not built; we only interpretate a byte sequence as a packed state
			//Thus, call to state constructor is forbidden by declaring it as private
			state(): byte0(0), byte1(0), byte2(0), byte3(0), byte4(0)
			{}

		public:
			bool is_final() const
			{ return !(byte0 & 0x80); }

			std::size_t get_outgoing_transition_count() const
			{
				return ((std::size_t)(byte0 & 0x7F)) * ((std::size_t)0x0100) +
				       ((std::size_t)byte1);
			}

			//Returns the word properties index associated to this state
			//Notice that only final states have an associated word properties index
			//This function does not check if the state is final
			std::size_t get_word_properties_index() const
			{
				return ((std::size_t)byte2) * ((std::size_t)0x00010000) +
				       ((std::size_t)byte3) * ((std::size_t)0x00000100) +
				       ((std::size_t)byte4);
			}

			//Returns the first transition handler
			const_outgoing_transition_iterator outgoing_transition_begin() const
			{
				if (is_final())
					return reinterpret_cast<const_outgoing_transition_iterator>(((std::size_t)this) + ((std::size_t)5));
				else return reinterpret_cast<const_outgoing_transition_iterator>(((std::size_t)this) + ((std::size_t)2));
			}

			//Returns the position after the last transition
			const_outgoing_transition_iterator outgoing_transition_end() const
			{
				if (is_final())
					return reinterpret_cast<const_outgoing_transition_iterator>(((std::size_t)this) + ((std::size_t)5) + get_outgoing_transition_count() * sizeof(outgoing_transition));
				else return reinterpret_cast<const_outgoing_transition_iterator>(((std::size_t)this) + ((std::size_t)2) + get_outgoing_transition_count() * sizeof(outgoing_transition));
			}

			//Returns the outgoing transition at the specified index
			//Notice that we do not check if the index is out of bounds
			const outgoing_transition& get_outgoing_transition(std::size_t index) const
			{ return outgoing_transition_begin()[index]; }

			//Binary searches the outgoing transition corresponding to the specified character
			//and returns the reference of its target state, or a NULL reference if the transition
			//does not exist
			std::size_t get_target_state_offset(const unichar c) const
			{
				const outgoing_transition* current_transition_ref;
				std::size_t middle_transition_index;
				std::size_t lower_transition_index(0);
				std::size_t upper_transition_index(get_outgoing_transition_count());
				unichar current_unichar;

				//While there are transitions to be searched
				while (lower_transition_index != upper_transition_index)
				{
					//Get current middle transition index
					middle_transition_index = (lower_transition_index + upper_transition_index) / 2;
					current_transition_ref = &get_outgoing_transition(middle_transition_index);
					current_unichar = current_transition_ref->get_label();
//					std::wcout << L"Transition char, lbound, cbound, ubound, offset: " << current_unichar << L" " << lower_transition_index << L" " << middle_transition_index << L" " << upper_transition_index << L" " << ((std::size_t)current_transition_ref) - ((std::size_t)this) << std::endl;
					//If the current transition has a less unichar, increase the lower transition bound
					if (current_unichar < c)
						lower_transition_index = middle_transition_index + 1;
					//Else if the current transition has a greater unichar, decrease the upper transition bound
					else if (c < current_unichar)
						upper_transition_index = middle_transition_index;
					//Else the matching transition has been found; return the corresponding target state
					else return current_transition_ref->get_target_state_offset();
				}
				//No matching transition found; return NULL state reference
				return std::numeric_limits<std::size_t>::max();
			}
		};

		class const_depth_first_iterator
		{
			friend class bin_delaf;
		public:
			typedef std::pair<const_outgoing_transition_iterator, const_outgoing_transition_iterator> const_outgoing_transition_iterator_pair;
			typedef std::deque<const_outgoing_transition_iterator_pair> backtracking_stack;
		protected:
			const bin_delaf &dico;
			backtracking_stack bs;

			//End iterator constructor
			const_depth_first_iterator(const bin_delaf &dico_): dico(dico_), bs()
			{}

			//Begin iterator constructor
			const_depth_first_iterator(const bin_delaf &dico_, const state &initial_state): dico(dico_), bs()
			{
				if (initial_state.get_outgoing_transition_count())
					bs.push_back(const_outgoing_transition_iterator_pair(initial_state.outgoing_transition_begin(), initial_state.outgoing_transition_end()));
			}

		public:
			//This is the end iterator once the backtracking stack is empty
			bool is_end()
			{ return bs.empty(); }

			//Increment iterator
			const_depth_first_iterator& operator++()
			{
				if (is_end())
					return *this;
				//Get next inner state (the state pointed by the transition at the top of the backtracking stack)
				const state& in_state = dico.offset_to_state(bs.back().first->get_target_state_offset());
				//If inner state has transitions, push its first transition and we are done
				if (in_state.get_outgoing_transition_count())
				{
//					std::wcout << L"Goin" << std::endl;
					bs.push_back(const_outgoing_transition_iterator_pair(in_state.outgoing_transition_begin(), in_state.outgoing_transition_end()));
					return *this;
				}
				//Else we have to recursively pop transition iterators up to the first one that is not an end iterator, and increment it
				//or if we run out of transition iterators, return the end iterator
				do
				{
					//Increment top transition iterator
					++bs.back().first;
//					std::wcout << L"Inctop" << std::endl;
					//If it is not an end iterator, we are done
					if (bs.back().first != bs.back().second)
						return *this;
					//Otherwise pop it and go for the next one in the top of the backtracking stack,
					//or if there are no more return the end iterator
					bs.pop_back();
//					std::wcout << L"Poptop" << std::endl;
				} while (!is_end());
				return *this;
			}

			bool operator==(const const_depth_first_iterator &cdfi) const
			{ return bs == cdfi.bs; }

			bool operator!=(const const_depth_first_iterator &cdfi) const
			{ return !(*this == cdfi); }

			class const_last_path_char_iterator
			{
				friend class const_depth_first_iterator;
			public:
				typedef const_depth_first_iterator::backtracking_stack::const_iterator base_iterator;
			protected:
				base_iterator i;

				const_last_path_char_iterator(base_iterator i_): i(i_)
				{}

			public:
				unichar operator* () const
				{ return i->first->get_label(); }
				//Member access operator "->" is not defined since we are to return chars and not structs

				const_last_path_char_iterator& operator++ ()
				{
					++i;
					return *this;
				}

				const_last_path_char_iterator& operator-- ()
				{
					--i;
					return *this;
				}

				bool operator== (const_last_path_char_iterator &clpci) const
				{ return i == clpci.i; }

				bool operator!= (const_last_path_char_iterator &clpci) const
				{ return !(*this == clpci); }
			}; //class const_last_path_char_iterator

			const_last_path_char_iterator const_last_path_char_iterator_begin() const
			{ return const_last_path_char_iterator(bs.begin()); }

			const_last_path_char_iterator const_last_path_char_iterator_end() const
			{ return const_last_path_char_iterator(bs.end()); }
		}; //class const_depth_first_iterator

		class const_depth_first_final_state_iterator: protected const_depth_first_iterator
		{
		public:
			typedef const_depth_first_iterator base_type;

		protected:
			//End iterator constructor
			const_depth_first_final_state_iterator(const bin_delaf &dico_): base_type(dico_)
			{}

			//Begin iterator constructor
			const_depth_first_final_state_iterator(const bin_delaf &dico_, const state &initial_state): base_type(dico_, initial_state)
			{
				//Increment iterator until first final state is reached,
				//or up to becoming the end iterator if no final states are present
				while (!is_end() && !dico.offset_to_state(bs.back().first->get_target_state_offset()).is_final())
					base_type::operator++ ();
			}

		public:
			//Increment iterator
			const_depth_first_final_state_iterator& operator++()
			{
				//Go to next state, final or not
				base_type::operator++ ();
				//Skip states until a final one is reached
				while (!is_end() && !dico.offset_to_state(bs.back().first->get_target_state_offset()).is_final())
					base_type::operator++ ();
				return *this;
			}

			bool operator==(const const_depth_first_final_state_iterator &ci) const
			{ return base_type::operator== (ci); }

			bool operator!=(const const_depth_first_final_state_iterator &ci) const
			{ return !(*this == ci); }

			const state& operator*() const
			{ return dico.offset_to_state(bs.back().first->get_target_state_offset()); }
		};

	protected:
		unsigned char *buffer;

	public:
		bin_delaf(): buffer(NULL)
		{}

		~bin_delaf()
		{
			if (buffer)
				delete[] buffer;
		}

		void reset_buffer(unsigned char *buffer_)
		{ buffer = buffer_; }

		const_depth_first_iterator depth_first_begin() const
		{ return const_depth_first_iterator(*this, get_initial_state()); }

		const_depth_first_iterator depth_first_end() const
		{ return const_depth_first_iterator(*this); }

		const state& offset_to_state(std::size_t offset) const
		{ return *reinterpret_cast<const state*>((std::size_t)buffer + offset); }

		//First state byte is the fifth one (the first 4 bytes are the size in bytes of the whole bin_delaf structure)
		std::size_t get_initial_state_offset() const
		{ return 4; }

		const state& get_initial_state() const
		{ return offset_to_state(get_initial_state_offset()); }

		//Returns the offset of the last state reached by consuming the specified word;
		//If there is no such state (the word is unknown), the maximum offset is returned
		template<typename UCharIterator>
		std::size_t get_state_offset(UCharIterator begin, UCharIterator end) const
		{
			std::size_t current_state_offset(get_initial_state_offset());
			//For each char of the word to recognize
			for (; begin != end; ++begin)
			{
				//Consume the next char and retrieve the next state offset
				current_state_offset = offset_to_state(current_state_offset).get_target_state_offset(*begin);
				//If there is no next state, the word is unknown: return maximum state offset
				if (current_state_offset == std::numeric_limits<std::size_t>::max())
					break;
			}
			//All word chars have been consumed, return current state offset
			//Notice that if the last consumed character did not lead to any state,
			//we are returning here the maximum state offset
			return current_state_offset;
		}

		//Indicates if the specified word is included in this dictionary or not
		template<typename UCharIterator>
		bool includes(UCharIterator word_begin, UCharIterator word_end) const
		{ return get_state_offset(word_begin, word_end) != std::numeric_limits<std::size_t>::max(); }
	};
} //namespace grapenlp

#endif /*GRAPENLP_BIN_DELAF_H*/
