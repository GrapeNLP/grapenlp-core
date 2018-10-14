/*
 * GRAPE
 *
 * Copyright (C) 2004-2018 Javier Miguel Sastre Martínez <javier.sastre@telefonica.net>
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

#ifndef GRAPE_MOVISTARBOT_TAG_DICO_H
#define GRAPE_MOVISTARBOT_TAG_DICO_H

#include <array>

#include <grape/u_array.h>
#include <grape/u_out_bound.h>

namespace grape
{
	const std::array<unichar, 8> communicate = { {'c', 'o', 'm', 'u', 'n', 'i', 'c', 'a'} };
	const std::array<unichar, 3> sms = { {'s', 'm', 's'} };
	const std::array<unichar, 5> phone = { {'p', 'h', 'o', 'n', 'e'} };
	const std::array<unichar, 7> message = { {'m', 'e', 's', 's', 'a', 'g', 'e'} };

	const std::array<unichar, 3> mms = { {'m', 'm', 's'} };

	const std::array<unichar, 8> catalog = { {'c', 'a', 't', 'a', 'l', 'o', 'g', 'o'} };
	const std::array<unichar, 3> more = { {'m', 'a', 's'} };
	const std::array<unichar, 8> query = { {'c', 'o', 'n', 's', 'u', 'l', 't', 'a'} };
	const std::array<unichar, 8> download = { {'d', 'e', 's', 'c', 'a', 'r', 'g', 'a'} };
	const std::array<unichar, 4> code = { {'c', 'o', 'd', 'e'} };
	const std::array<unichar, 6> games = { {'j', 'u', 'e', 'g', 'o', 's'} };
	const std::array<unichar, 6> music = { {'m', 'u', 's', 'i', 'c', 'a'} };
	const std::array<unichar, 5> photos = { {'f', 'o', 't', 'o', 's'} };
	const std::array<unichar, 7> pattern = { {'p', 'a', 't', 't', 'e', 'r', 'n'} };
	const std::array<unichar, 4> something = { {'a', 'l', 'g', 'o'} };

	const std::array<unichar, 7> alertas = { {'a', 'l', 'e', 'r', 't', 'a', 's'} };
	const std::array<unichar, 4> alta = { {'a', 'l', 't', 'a'} };

	const std::array<unichar, 4> info = { {'i', 'n', 'f', 'o'} };
	const std::array<unichar, 11> tarifaplana = { {'t', 'a', 'r', 'i', 'f', 'a', 'p', 'l', 'a', 'n', 'a'} };
	const std::array<unichar, 2> tv = { {'t', 'v'} };
	const std::array<unichar, 15> emocionmovistar = { {'e', 'm', 'o', 'c', 'i', 'o', 'n', 'm', 'o', 'v', 'i', 's', 't', 'a', 'r'} };
	const std::array<unichar, 18> escritoriomovistar = { {'e', 's', 'c', 'r', 'i', 't', 'o', 'r', 'i', 'o', 'm', 'o', 'v', 'i', 's', 't', 'a', 'r'} };
	const std::array<unichar, 11> promociones = { {'p', 'r', 'o', 'm', 'o', 'c', 'i', 'o', 'n', 'e', 's'} };
	const std::array<unichar, 5> saldo = { {'s', 'a', 'l', 'd', 'o'} };
	const std::array<unichar, 12> videollamada = { {'v', 'i', 'd', 'e', 'o', 'l', 'l', 'a', 'm', 'a', 'd', 'a'} };

	class movistarbot_tag_dico
	{
	public:
		u_out_bound::trie::string::ref communicate;
		u_out_bound::trie::string::ref sms;
		u_out_bound::trie::string::ref phone;
		u_out_bound::trie::string::ref message;

		u_out_bound::trie::string::ref mms;

		u_out_bound::trie::string::ref catalog;
		u_out_bound::trie::string::ref more;
		u_out_bound::trie::string::ref query;
		u_out_bound::trie::string::ref download;
		u_out_bound::trie::string::ref games;
		u_out_bound::trie::string::ref music;
		u_out_bound::trie::string::ref photos;
		u_out_bound::trie::string::ref pattern;
		u_out_bound::trie::string::ref something;

		u_out_bound::trie::string::ref code;

		u_out_bound::trie::string::ref alertas;
		u_out_bound::trie::string::ref alta;

		u_out_bound::trie::string::ref info;
		u_out_bound::trie::string::ref tarifaplana;
		u_out_bound::trie::string::ref tv;
		u_out_bound::trie::string::ref emocionmovistar;
		u_out_bound::trie::string::ref escritoriomovistar;
		u_out_bound::trie::string::ref promociones;
		u_out_bound::trie::string::ref saldo;
		u_out_bound::trie::string::ref videollamada;

		movistarbot_tag_dico(u_out_bound::trie::string &uobt_root):
			communicate(&(uobt_root.concat(grape::communicate.begin(), grape::communicate.end()))),
			sms(&(uobt_root.concat(grape::sms.begin(), grape::sms.end()))),
			phone(&(uobt_root.concat(grape::phone.begin(), grape::phone.end()))),
			message(&(uobt_root.concat(grape::message.begin(), grape::message.end()))),

			mms(&(uobt_root.concat(grape::mms.begin(), grape::mms.end()))),

			catalog(&(uobt_root.concat(grape::catalog.begin(), grape::catalog.end()))),
			more(&(uobt_root.concat(grape::more.begin(), grape::more.end()))),
			query(&(uobt_root.concat(grape::query.begin(), grape::query.end()))),
			download(&(uobt_root.concat(grape::download.begin(), grape::download.end()))),
			games(&(uobt_root.concat(grape::games.begin(), grape::games.end()))),
			music(&(uobt_root.concat(grape::music.begin(), grape::music.end()))),
			photos(&(uobt_root.concat(grape::photos.begin(), grape::photos.end()))),
			pattern(&(uobt_root.concat(grape::pattern.begin(), grape::pattern.end()))),
			something(&(uobt_root.concat(grape::something.begin(), grape::something.end()))),

			code(&(uobt_root.concat(grape::code.begin(), grape::code.end()))),

			alertas(&(uobt_root.concat(grape::alertas.begin(), grape::alertas.end()))),
			alta(&(uobt_root.concat(grape::alta.begin(), grape::alta.end()))),
			
			info(&(uobt_root.concat(grape::info.begin(), grape::info.end()))),
			tarifaplana(&(uobt_root.concat(grape::tarifaplana.begin(), grape::tarifaplana.end()))),
			tv(&(uobt_root.concat(grape::tv.begin(), grape::tv.end()))),
			emocionmovistar(&(uobt_root.concat(grape::emocionmovistar.begin(), grape::emocionmovistar.end()))),
			escritoriomovistar(&(uobt_root.concat(grape::escritoriomovistar.begin(), grape::escritoriomovistar.end()))),
			promociones(&(uobt_root.concat(grape::promociones.begin(), grape::promociones.end()))),
			saldo(&(uobt_root.concat(grape::saldo.begin(), grape::saldo.end()))),
			videollamada(&(uobt_root.concat(grape::videollamada.begin(), grape::videollamada.end())))
		{}
	};
} //namespace grape

#endif /*GRAPE_TAG_DICO_H*/
