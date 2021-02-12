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

#ifndef GRAPENLP_MOVISTARBOT_OUT_SERIALIZER_H
#define GRAPENLP_MOVISTARBOT_OUT_SERIALIZER_H

#include <grapenlp/u_array.h>
#include <grapenlp/token.h>
#include <grapenlp/u_set_trie.h>
#include <grapenlp/segment.h>
#include <grapenlp/movistarbot_tag_dico.h>
#include <grapenlp/movistarbot_phone_digit_separator_set.h>

namespace grapenlp
{
	const movistarbot_phone_digit_separator_set the_movistarbot_phone_digit_separator_set = movistarbot_phone_digit_separator_set();

	template<typename InputIterator, assoc_container_impl_choice acic>
	struct movistarbot_out_serializer
	{
		//Dictionary of grammar output tags: XML tags represented as unicode arrays
		typedef trie_with_ptr_data<unichar, u_array> ua_trie;
		//Unicode token
		typedef token<InputIterator> u_token;
		//Iterator over lists of unicode tokens
		typedef typename u_token::ref_list::const_iterator u_token_iterator;
		typedef segment<u_token_iterator> u_token_segment;
		typedef segment_map<u_token_iterator, unichar, acic> u_token_segment_map;
		typedef typename u_token_segment_map::const_iterator u_token_segment_map_const_iterator;
		typedef typename set_impl_selector<acic, u_token_segment_map>::type u_token_segment_map_set;
		typedef typename u_token_segment_map_set::const_iterator u_token_segment_map_set_const_iterator;

		//Returns the input iterator of the first character of the specified token (iterator)
		InputIterator get_input_begin(u_token_iterator i, u_token_iterator token_list_end)
		{
			//If the token iterator points to the end of the token list, return the end of the input sequence
			if (i == token_list_end)
			{
				--i;
				return (*i)->end;
			}
			//Else return the beginning of the token
			return (*i)->begin;
		}

		//Returns the input iterator of the character after the token before the specified token (iterator)
		//This avoids to include whites between the last token to be taken into account and the specified token iterator
		InputIterator get_input_end(u_token_iterator i, u_token_iterator token_list_begin)
		{
			//If the token iterator points to the first token, return the beginning of the input sequence
			if (i == token_list_begin)
				return (*i)->begin;
			//Else return the iterator to the character right after the token to be taken into account
			--i;
			return (*i)->end;
		}

		//Returns the absolute input index of the first character the specified token (iterator)
		std::size_t get_absolute_input_begin_index(u_token_iterator i, u_token_iterator token_list_end, InputIterator input_begin)
		{ return std::distance(input_begin, get_input_begin(i, token_list_end)); }

		//Returns the absolute input index of the first character just after the specified token (iterator)
		std::size_t get_absolute_input_end_index(u_token_iterator i, u_token_iterator token_list_begin, InputIterator input_begin)
		{
			if (i == token_list_begin)
				return 0;
			--i;
			return std::distance(input_begin, (*i)->end);
		}

		std::size_t get_serialized_index_size(std::size_t i)
		{
			std::size_t result = 1;
			while (i > 10)
			{
				i /= 10;
				result++;
			}
			return result;
		}

		/*std::size_t get_serialized_segment_size(const u_token_segment &s, u_token_iterator token_list_begin, u_token_iterator token_list_end, InputIterator input_begin)
		{
			//Number of digits of begin index + number of digits of end index + 1 for the ','
			if (s.get_begin() == s.get_end())
				return (get_serialized_index_size(get_absolute_input_begin_index(s.get_begin(), token_list_end, input_begin)) << 1) + 1;
			return get_serialized_index_size(get_absolute_input_begin_index(s.get_begin(), token_list_end, input_begin)) +
				get_serialized_index_size(get_absolute_input_end_index(s.get_end(), token_list_begin, input_begin)) +
				1;
		}

		std::size_t get_serialized_segment_map_size(const u_token_segment_map &sm, u_token_iterator token_list_begin, u_token_iterator token_list_end, InputIterator input_begin, InputIterator input_end)
		{
			//Segment separators (EOL) + segment name delimiter (:)
			std::size_t result(sm.size() << 1);
			typename u_token_segment_map::const_iterator i(sm.begin());
			for (; i != sm.end(); ++i)
				//Segment name length + segment size
				result += i->first->size() + get_serialized_segment_size(*i->second, token_list_begin, token_list_end, input_begin);
			return result;
		}

		std::size_t get_serialized_segment_map_set_size(const u_token_segment_map_set &sms, u_token_iterator token_list_begin, u_token_iterator token_list_end, InputIterator input_begin)
		{
			//Number of digits of interpretations + EOL + segment_map separator + EOL * segment_map count
			std::size_t result(get_serialized_index_size(sms.size()) + 1 + sms.size());
			u_token_segment_map_set_const_iterator i(sms.begin());
			for (; i != sms.end(); ++i)
				//Segment name length + segment size + EOL
				result += get_serialized_segment_map_size(*i, token_list_begin, token_list_end, input_begin);
			return result;
		}*/

		template<typename UnicharIterator>
		UnicharIterator serialize_absolute_input_begin_index(u_token_iterator i, u_token_iterator token_list_end, InputIterator input_begin, InputIterator input_end, UnicharIterator uit)
		{
			if (i == token_list_end)
				return itoui(input_end - input_begin, uit);
			return itoui((*i)->begin - input_begin, uit);
		}

		template<typename UnicharIterator>
		UnicharIterator serialize_absolute_input_end_index(u_token_iterator i, u_token_iterator token_list_end, InputIterator input_begin, InputIterator input_end, UnicharIterator uit)
		{
			--i;
			return itoui((*i)->end - input_begin, uit);
		}

		template<typename UnicharIterator>
		UnicharIterator serialize_segment(const u_token_segment &s, u_token_iterator token_list_end, InputIterator input_begin, InputIterator input_end, UnicharIterator uit)
		{
			//Add begin index
			uit = serialize_absolute_input_begin_index(s.get_begin(), token_list_end, input_begin, input_end, uit);
			*uit = ',';
			++uit;
			if (s.get_begin() == s.get_end())
				return serialize_absolute_input_begin_index(s.get_begin(), token_list_end, input_begin, input_end, uit);
			return serialize_absolute_input_end_index(s.get_end(), token_list_end, input_begin, input_end, uit);
		}

		template<typename UnicharIterator>
		UnicharIterator serialize_segment_map(const u_token_segment_map &sm, u_token_iterator token_list_end, InputIterator input_begin, InputIterator input_end, UnicharIterator uit)
		{
			typename u_token_segment_map::const_iterator i(sm.begin());
			for (; i != sm.end(); ++i)
			{
				//Add segment name
				uit = i->first->copy(uit);
				*uit = ':';
				++uit;
				//Add segment
				uit = serialize_segment((*i->second), token_list_end, input_begin, input_end, uit);
				*uit = '\n';
				++uit;
			}
			return uit;
		}

		//Appends a sequence up from the specified unicode character iterator
		template<typename UnicharSequence, typename UnicharIterator>
		UnicharIterator append(const UnicharSequence &us, UnicharIterator uit)
		{ return std::copy(us.begin(), us.end(), uit); }

		//Appends a token up from the specified unicode character iterator
		template<typename UnicharIterator>
		UnicharIterator append(const u_token &t, UnicharIterator uit)
		{ return std::copy(t.begin, t.end, uit); }

		//Appends a segment of tokens up from the specified unicode character iterator
		template<typename UnicharIterator>
		UnicharIterator append(const u_token_segment &s, UnicharIterator uit)
		{
			if (s.get_begin() == s.get_end())
				return uit;
			u_token_iterator before_end(s.get_end());
			--before_end;
			return std::copy((*s.get_begin())->begin, (*before_end)->end, uit);
		}

		//Appends a segment of tokens up from the specified unicode character iterator but omitting white characters that may separate the tokens
		template<typename UnicharIterator>
		UnicharIterator append_without_whites(const u_token_segment &s, UnicharIterator uit)
		{
			u_token_iterator i(s.get_begin());
			for (; i != s.get_end(); ++i)
//Whites are omitted from the token list, so we do not need to check for white tokens
//				if (!i->is_white)
					uit = append(**i, uit);
			return uit;
		}

		//Appends a segment of tokens up from the specified unicode character iterator but omitting white characters and other specified substrings that may separate the tokens
		template<typename UnicharIterator>
		UnicharIterator filtered_append_without_whites(const u_token_segment &s, const u_set_trie &tokens_to_ommit, UnicharIterator uit)
		{
			u_token_iterator i(s.get_begin());
			for (; i != s.get_end(); ++i)
//Whites are omitted from the token list, so we do not need to check for white tokens
//				if (!i->is_white)
				if (!the_movistarbot_phone_digit_separator_set.includes((*i)->begin, (*i)->end))
					uit = append(**i, uit);
			return uit;
		}

		std::size_t get_serialized_segment_size(const u_token_segment &s)
		{
			//Empty segment test
			if (s.get_begin() == s.get_end())
				return 0;
			u_token_iterator i(s.get_end());
			--i;
			return std::distance((*s.get_begin())->begin, (*i)->end);
		}

		std::size_t get_serialized_segment_without_whites_size(const u_token_segment &s)
		{
			std::size_t result = 0;
			u_token_iterator i(s.get_begin());
			for (; i != s.get_end(); ++i)
//Whites are omitted from the token list, so we do not need to check for white tokens
//				if (!i->is_white)
					result += (*i)->size();
			return result;
		}

		std::size_t get_serialized_filtered_segment_without_whites_size(const u_token_segment &s, const u_set_trie &tokens_to_ommit)
		{
			std::size_t result(0);
			u_token_iterator i(s.get_begin());
			for (; i != s.get_end(); ++i)
//Whites are omitted from the token list, so we do not need to check for white tokens
//				if (!i->is_white)
				if (!tokens_to_ommit.includes((*i)->begin, (*i)->end))
					result += (*i)->size();
			return result;
		}

		std::size_t get_serialized_sms_segment_map_set_size(const u_token_segment_map &sms_sm, u_token_segment_map_const_iterator phone_segment_it, u_token_segment_map_const_iterator message_segment_it, const movistarbot_tag_dico &td)
		{
			//Add "sms" chain length
			std::size_t result(sms.size());
			if (phone_segment_it != sms_sm.end())
					//If phone argument present, add "_phone" chain length + length of 1 space + length of phone number without whites
				result += 2 + phone.size() + get_serialized_filtered_segment_without_whites_size(phone_segment_it->second, the_movistarbot_phone_digit_separator_set);
			if (message_segment_it != sms_sm.end())
				//If message argument present, add "_message" chain length + length of 1 space + length of message as is
				result += 2 + message.size() + get_serialized_segment_size(message_segment_it->second);
			return result;
		}

		void serialize_sms_segment_map_set(const u_token_segment_map &sms_sm, const movistarbot_tag_dico &td, u_array &result)
		{
#ifdef TRACE
			std::wcout << L"Serializing SMS service command (";
#endif
			//Find phone segment within the sms segment map
			u_token_segment_map_const_iterator phone_segment_it(sms_sm.find(td.phone));
			//Find message segment within the sms segment map
			u_token_segment_map_const_iterator message_segment_it(sms_sm.find(td.message));

			result.reset(get_serialized_sms_segment_map_set_size(sms_sm, phone_segment_it, message_segment_it, td));
			u_array::iterator uit(result.begin());

			//Append "sms"
			uit = append(sms, uit);

			if (phone_segment_it != sms_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "phone"
				uit = append(phone, uit);
			}

			if (message_segment_it != sms_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "message"
				uit = append(message, uit);
			}

			if (phone_segment_it != sms_sm.end())
			{
				//Append space
				*uit = ' ';
				++uit;
				//Append phone without whites between the digits nor digit separators ('.', '-', etc)
				uit = filtered_append_without_whites(phone_segment_it->second, the_movistarbot_phone_digit_separator_set, uit);
			}

			if (message_segment_it != sms_sm.end())
			{
				//Append space
				*uit = ' ';
				++uit;
				//Append message as is
				uit = append(message_segment_it->second, uit);
			}

#ifdef TRACE
			std::wcout << result.size() << L" chars): " << result << std::endl;
#endif
		}

		std::size_t get_serialized_catalog_segment_map_set_size(const u_token_segment_map &catalog_sm, u_token_segment_map_const_iterator download_segment_it, u_token_segment_map_const_iterator more_segment_it, u_token_segment_map_const_iterator games_segment_it, u_token_segment_map_const_iterator music_segment_it, u_token_segment_map_const_iterator photos_segment_it, u_token_segment_map_const_iterator code_segment_it, u_token_segment_map_const_iterator pattern_segment_it, const movistarbot_tag_dico &td)
		{
			//Add "catalog" chain length
			std::size_t result(catalog.size());
			//If download argument present, add "_download" chain length
			if (download_segment_it != catalog_sm.end())
				result += 1 + download.size();
			//If more argument present, add "_more" chain length
			if (more_segment_it != catalog_sm.end())
				result += 1 + more.size();
			//If games argument present, add "_games" chain length
			if (games_segment_it != catalog_sm.end())
				result += 1 + games.size();
			//If music argument present, add "_music" chain length
			else if (music_segment_it != catalog_sm.end())
				result += 1 + music.size();
			//If photos argument present, add "_photos" chain length
			else if (photos_segment_it != catalog_sm.end())
				result += 1 + photos.size();
			//If pattern argument present, add "_pattern" chain length + length of 1 space + length of pattern as is
			if (pattern_segment_it != catalog_sm.end())
				result += 2 + pattern.size() + get_serialized_segment_size(pattern_segment_it->second);
			//If code argument present, add "_code" chain length + length of 1 space + length of code as is
			if (code_segment_it != catalog_sm.end())
				result += 2 + code.size() + get_serialized_segment_size(code_segment_it->second);
			return result;
		}

		void serialize_catalog_segment_map_set(const u_token_segment_map &catalog_sm, const movistarbot_tag_dico &td, u_array &result)
		{
#ifdef TRACE
			std::wcout << L"Serializing catalog service command (";
#endif
			//Find "download" segment within the catalog segment map
			u_token_segment_map_const_iterator download_segment_it(catalog_sm.find(td.download));
			//Find "more" segment within the catalog segment map
			u_token_segment_map_const_iterator more_segment_it(catalog_sm.find(td.more));
			//Find "games" segment within the catalog segment map
			u_token_segment_map_const_iterator games_segment_it(catalog_sm.find(td.games));
			//Find "music" segment within the catalog segment map
			u_token_segment_map_const_iterator music_segment_it(catalog_sm.find(td.music));
			//Find "photos" segment within the catalog segment map
			u_token_segment_map_const_iterator photos_segment_it(catalog_sm.find(td.photos));
			//Find "code" segment within the catalog segment map
			u_token_segment_map_const_iterator code_segment_it(catalog_sm.find(td.code));
			//Find "pattern" segment within the catalog segment map
			u_token_segment_map_const_iterator pattern_segment_it(catalog_sm.find(td.pattern));

			result.reset(get_serialized_catalog_segment_map_set_size(catalog_sm, download_segment_it, more_segment_it, games_segment_it, music_segment_it, photos_segment_it, code_segment_it, pattern_segment_it, td));

			u_array::iterator uit(result.begin());

			//Append "catalog"
			uit = append(catalog, uit);

			if (download_segment_it != catalog_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "download"
				uit = append(download, uit);
			}

			if (more_segment_it != catalog_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "more"
				uit = append(more, uit);
			}

			if (games_segment_it != catalog_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "games"
				uit = append(games, uit);
			}

			else if (music_segment_it != catalog_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "music"
				uit = append(music, uit);
			}

			else if (photos_segment_it != catalog_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "photos"
				uit = append(photos, uit);
			}

			if (pattern_segment_it != catalog_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "pattern"
				uit = append(pattern, uit);

				//Append space
				*uit = ' ';
				++uit;
				//Append pattern as is
				uit = append(pattern_segment_it->second, uit);
			}

			if (code_segment_it != catalog_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "code"
				uit = append(code, uit);

				//Append space
				*uit = ' ';
				++uit;
				//Append code as is
				uit = append(code_segment_it->second, uit);
			}

#ifdef TRACE
			std::wcout << result.size() << L" chars): " << result << std::endl;
#endif
		}

		std::size_t get_serialized_alertas_segment_map_set_size(const u_token_segment_map &alertas_sm, u_token_segment_map_const_iterator more_segment_it, u_token_segment_map_const_iterator pattern_segment_it, u_token_segment_map_const_iterator code_segment_it, u_token_segment_map_const_iterator alta_segment_it, const movistarbot_tag_dico &td)
		{
			//Add "alertas" chain length
			std::size_t result(alertas.size());
			//If code argument present, add "_code" chain length + length of 1 space + length of code as is
			if (code_segment_it != alertas_sm.end())
			{
				result += 2 + code.size() + get_serialized_segment_size(code_segment_it->second);
				//If alta argument present, add "_alta" chain length
				if (alta_segment_it != alertas_sm.end())
					result += 1 + alta.size();
			}
			//If alta argument present, add "_alta" chain length
			else if (alta_segment_it != alertas_sm.end())
			{
				result += 1 + alta.size();
				//If pattern argument present, add "_pattern" chain length + length of 1 space + length of pattern as is
				if (pattern_segment_it != alertas_sm.end())
					result += 2 + pattern.size() + get_serialized_segment_size(pattern_segment_it->second);
			}
			else
			{
				//If more argument present, add "_more" chain length
				if (more_segment_it != alertas_sm.end())
					result += 1 + more.size();
				//If pattern argument present, add "_pattern" chain length + length of 1 space + length of pattern as is
				if (pattern_segment_it != alertas_sm.end())
					result += 2 + pattern.size() + get_serialized_segment_size(pattern_segment_it->second);
			}
			return result;
		}

		void serialize_alertas_segment_map_set(const u_token_segment_map &alertas_sm, const movistarbot_tag_dico &td, u_array &result)
		{
#ifdef TRACE
			std::wcout << L"Serializing alertas service command (";
#endif
			//Find "more" segment within the alertas segment map
			u_token_segment_map_const_iterator more_segment_it(alertas_sm.find(td.more));
			//Find "pattern" segment within the alertas segment map
			u_token_segment_map_const_iterator pattern_segment_it(alertas_sm.find(td.pattern));
			//Find "code" segment within the alertas segment map
			u_token_segment_map_const_iterator code_segment_it(alertas_sm.find(td.code));
			//Find "alta" segment within the alertas segment map
			u_token_segment_map_const_iterator alta_segment_it(alertas_sm.find(td.alta));

			result.reset(get_serialized_alertas_segment_map_set_size(alertas_sm, more_segment_it, pattern_segment_it, code_segment_it, alta_segment_it, td));
			u_array::iterator uit(result.begin());

			//Append "alertas"
			uit = append(alertas, uit);

			if (code_segment_it != alertas_sm.end())
			{
				if (alta_segment_it != alertas_sm.end())
				{
					//Append "_"
					*uit = '_';
					++uit;
					//Append "alta"
					uit = append(alta, uit);
				}

				//Append "_"
				*uit = '_';
				++uit;
				//Append "code"
				uit = append(code, uit);

				//Append code number
				*uit = ' ';
				++uit;
				//Append code number as is
				uit = append(code_segment_it->second, uit);
			}
			else if (alta_segment_it != alertas_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "alta"
				uit = append(alta, uit);

				if (pattern_segment_it != alertas_sm.end())
				{
					//Append "_"
					*uit = '_';
					++uit;
					//Append "pattern"
					uit = append(pattern, uit);

					//Append space
					*uit = ' ';
					++uit;
					//Append pattern as is
					uit = append(pattern_segment_it->second, uit);
				}
			}
			else
			{
				if (more_segment_it != alertas_sm.end())
				{
					//Append "_"
					*uit = '_';
					++uit;
					//Append "more"
					uit = append(more, uit);
				}

				if (pattern_segment_it != alertas_sm.end())
				{
					//Append "_"
					*uit = '_';
					++uit;
					//Append "pattern"
					uit = append(pattern, uit);

					//Append space
					*uit = ' ';
					++uit;
					//Append pattern as is
					uit = append(pattern_segment_it->second, uit);
				}
			}

#ifdef TRACE
			std::wcout << result.size() << L" chars): " << result << std::endl;
#endif
		}

		std::size_t get_serialized_info_segment_map_set_size(const u_token_segment_map &info_sm, u_token_segment_map_const_iterator tarifaplana_segment_it, u_token_segment_map_const_iterator tv_segment_it, u_token_segment_map_const_iterator music_segment_it, u_token_segment_map_const_iterator emocionmovistar_segment_it, u_token_segment_map_const_iterator escritoriomovistar_segment_it, u_token_segment_map_const_iterator promociones_segment_it, u_token_segment_map_const_iterator saldo_segment_it, u_token_segment_map_const_iterator videollamada_segment_it, const movistarbot_tag_dico &td)
		{
			//Add "info" chain length
			std::size_t result(info.size());
			//If tarifaplana argument present, add "_tarifaplana" chain length
			if (tarifaplana_segment_it != info_sm.end())
			{
				result += 1 + tarifaplana.size();
				//If tv argument present, add "_tv" chain length
				if (tv_segment_it != info_sm.end())
					result += 1 + tv.size();
				//If music argument present, add "_music" chain length
				else if (music_segment_it != info_sm.end())
					result += 1 + music.size();
			}
			//If emocionmovistar argument present, add "_emocionmovistar" chain length
			else if (emocionmovistar_segment_it != info_sm.end())
			{
				result += 1 + emocionmovistar.size();
				//If tv argument present, add "_tv" chain length
			}
			//If escritoriomovistar argument present, add "_escritoriomovistar" chain length
			else if (escritoriomovistar_segment_it != info_sm.end())
			{
				result += 1 + escritoriomovistar.size();
				//If tv argument present, add "_tv" chain length
			}
			//If promociones argument present, add "_promociones" chain length
			else if (promociones_segment_it != info_sm.end())
			{
				result += 1 + promociones.size();
				//If tv argument present, add "_tv" chain length
			}
			//If saldo argument present, add "_saldo" chain length
			else if (saldo_segment_it != info_sm.end())
			{
				result += 1 + saldo.size();
				//If tv argument present, add "_tv" chain length
			}
			//If videollamada argument present, add "_videollamada" chain length
			else if (videollamada_segment_it != info_sm.end())
			{
				result += 1 + videollamada.size();
				//If tv argument present, add "_tv" chain length
			}
			return result;
		}

		void serialize_info_segment_map_set(const u_token_segment_map &info_sm, const movistarbot_tag_dico &td, u_array &result)
		{
#ifdef TRACE
			std::wcout << L"Serializing info service command (";
#endif
			//Find "tarifaplana" segment within the info segment map
			u_token_segment_map_const_iterator tarifaplana_segment_it(info_sm.find(td.tarifaplana));
			//Find "tv" segment within the info segment map
			u_token_segment_map_const_iterator tv_segment_it(info_sm.find(td.tv));
			//Find "music" segment within the info segment map
			u_token_segment_map_const_iterator music_segment_it(info_sm.find(td.music));
			//Find "emocionmovistar" segment within the info segment map
			u_token_segment_map_const_iterator emocionmovistar_segment_it(info_sm.find(td.emocionmovistar));
			//Find "escritoriomovistar" segment within the info segment map
			u_token_segment_map_const_iterator escritoriomovistar_segment_it(info_sm.find(td.escritoriomovistar));
			//Find "promociones" segment within the info segment map
			u_token_segment_map_const_iterator promociones_segment_it(info_sm.find(td.promociones));
			//Find "saldo" segment within the info segment map
			u_token_segment_map_const_iterator saldo_segment_it(info_sm.find(td.saldo));
			//Find "videollamada" segment within the info segment map
			u_token_segment_map_const_iterator videollamada_segment_it(info_sm.find(td.videollamada));

			result.reset(get_serialized_info_segment_map_set_size(info_sm, tarifaplana_segment_it, tv_segment_it, music_segment_it, emocionmovistar_segment_it, escritoriomovistar_segment_it, promociones_segment_it, saldo_segment_it, videollamada_segment_it, td));
			u_array::iterator uit(result.begin());

			//Append "info"
			uit = append(info, uit);

			if (tarifaplana_segment_it != info_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "tarifaplana"
				uit = append(tarifaplana, uit);

				if (tv_segment_it != info_sm.end())
				{
					//Append "_"
					*uit = '_';
					++uit;
					//Append "tv"
					uit = append(tv, uit);
				}

				else if (music_segment_it != info_sm.end())
				{
					//Append "_"
					*uit = '_';
					++uit;
					//Append "music"
					uit = append(music, uit);
				}
			}
			else if (emocionmovistar_segment_it != info_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "emocionmovistar"
				uit = append(emocionmovistar, uit);
			}
			else if (escritoriomovistar_segment_it != info_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "escritoriomovistar"
				uit = append(escritoriomovistar, uit);
			}
			else if (promociones_segment_it != info_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "promociones"
				uit = append(promociones, uit);
			}
			else if (saldo_segment_it != info_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "saldo"
				uit = append(saldo, uit);
			}
			else if (videollamada_segment_it != info_sm.end())
			{
				//Append "_"
				*uit = '_';
				++uit;
				//Append "videollamada"
				uit = append(videollamada, uit);
			}

#ifdef TRACE
			std::wcout << result.size() << L" chars): " << result << std::endl;
#endif
		}

		//Checks if the specified segment map corresponds to a sms sending request:
		//it mentions the sms or asks to communicate a message or asks to communicate to a phone number
		bool is_sms_segment_map(const u_token_segment_map &sm, const movistarbot_tag_dico &td)
		{
			return sm.has_key(td.sms) ||
			      (sm.has_key(td.communicate) && (sm.has_key(td.message) || sm.has_key(td.phone)));
		}

		//Checks if the specified segment map corresponds to a catalog query or download request:
		//it mentions the catalog, or it demands access to catalog contents or to download catalog contents (games, music, photos, whatever)
		bool is_catalog_segment_map(const u_token_segment_map &sm, const movistarbot_tag_dico &td)
		{
			return sm.has_key(td.catalog) ||
			      sm.has_key(td.games) ||
			      (sm.has_key(td.music) && !sm.has_key(td.tarifaplana)) ||
			      sm.has_key(td.photos) ||
			      (sm.has_key(td.download) && sm.has_key(td.code)) ||
			      //Quiero algo de torrente | Descárgame algo de torrente
			      (sm.has_key(td.something) && (sm.has_key(td.query) || sm.has_key(td.download)) && sm.has_key(td.pattern));
//			      sm.has_key(td.query) && sm.has_key(td.more);
		}

		//Checks if the specified segment map corresponds to a catalog query or download request:
		//it mentions "alertas"
		bool is_alertas_segment_map(const u_token_segment_map &sm, const movistarbot_tag_dico &td)
		{
			return sm.has_key(td.alertas) ||
			      (sm.has_key(td.alta) && sm.has_key(td.code));
		}

		//Checks if the specified segment map corresponds to a catalog query or download request:
		//it mentions any information topic
		bool is_info_segment_map(const u_token_segment_map &sm, const movistarbot_tag_dico &td)
		{
			return (sm.has_key(td.tarifaplana) && (sm.has_key(td.tv) || sm.has_key(td.music))) ||
			       sm.has_key(td.emocionmovistar) ||
			       sm.has_key(td.escritoriomovistar) ||
			       sm.has_key(td.promociones) ||
			       sm.has_key(td.saldo) ||
			       sm.has_key(td.videollamada);
		}

		bool serialize_segment_map(const u_token_segment_map &sm, const movistarbot_tag_dico &td, u_array &result)
		{
#ifdef TRACE
			std::wcout << "Trying to serialize: " << sm << std::endl;
#endif
			if (is_sms_segment_map(sm, td))
			{
#ifdef TRACE
				std::wcout << "Serializing sms request" << std::endl;
#endif
				serialize_sms_segment_map_set(sm, td, result);
				return true;
			}
			if (is_catalog_segment_map(sm, td))
			{
#ifdef TRACE
				std::wcout << "Serializing catalog request" << std::endl;
#endif
				serialize_catalog_segment_map_set(sm, td, result);
				return true;
			}
			if (is_alertas_segment_map(sm, td))
			{
#ifdef TRACE
				std::wcout << "Serializing alertas request" << std::endl;
#endif
				serialize_alertas_segment_map_set(sm, td, result);
				return true;
			}
			if (is_info_segment_map(sm, td))
			{
#ifdef TRACE
				std::wcout << "Serializing info request" << std::endl;
#endif
				serialize_info_segment_map_set(sm, td, result);
				return true;
			}
			//No interpretation found corresponding to any known service
#ifdef TRACE
			std::wcout << "Not a valid request: discarding" << std::endl;
#endif
			return false;
		}

		bool operator() (const u_token_segment_map_set &sms, const movistarbot_tag_dico &td, u_array &result)
		{
			//No interpretations found: return
			if (sms.size() == 0)
				return false;
			u_token_segment_map_set_const_iterator i(sms.begin());
			//Serialize the first interpretation corresponding to a known service and serialize it
			for (; i != sms.end(); ++i)
			{
				if (serialize_segment_map(*i, td, result))
					return true;
			}
			return false;
		}

/*		template<typename UnicharIterator>
		UnicharIterator serialize_segment_map_set(const u_token_segment_map_set &sms, u_token_iterator token_list_end, InputIterator input_begin, InputIterator input_end, UnicharIterator uit)
		{
			//Add number of interpretations
			uit = itoui(sms.size(), uit);
			*uit = '\n';
			++uit;
			u_token_segment_map_set_const_iterator i(sms.begin());
			for (; i != sms.end(); ++i)
			{
				uit = serialize_segment_map(*i, token_list_end, input_begin, input_end, uit);
				*uit = '\n';
				++uit;
			}
			return uit;
		}*/
	};
} //namespace grapenlp

#endif /*GRAPENLP_OUT_SERIALIZER_H*/
