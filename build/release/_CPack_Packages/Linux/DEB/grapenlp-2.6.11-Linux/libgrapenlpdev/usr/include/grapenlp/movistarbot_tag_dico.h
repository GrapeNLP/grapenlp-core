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

#ifndef GRAPENLP_MOVISTARBOT_TAG_DICO_H
#define GRAPENLP_MOVISTARBOT_TAG_DICO_H

#include <array>

#include <grapenlp/u_array.h>
#include <grapenlp/u_out_bound.h>

namespace grapenlp
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
			communicate(&(uobt_root.concat(grapenlp::communicate.begin(), grapenlp::communicate.end()))),
			sms(&(uobt_root.concat(grapenlp::sms.begin(), grapenlp::sms.end()))),
			phone(&(uobt_root.concat(grapenlp::phone.begin(), grapenlp::phone.end()))),
			message(&(uobt_root.concat(grapenlp::message.begin(), grapenlp::message.end()))),

			mms(&(uobt_root.concat(grapenlp::mms.begin(), grapenlp::mms.end()))),

			catalog(&(uobt_root.concat(grapenlp::catalog.begin(), grapenlp::catalog.end()))),
			more(&(uobt_root.concat(grapenlp::more.begin(), grapenlp::more.end()))),
			query(&(uobt_root.concat(grapenlp::query.begin(), grapenlp::query.end()))),
			download(&(uobt_root.concat(grapenlp::download.begin(), grapenlp::download.end()))),
			games(&(uobt_root.concat(grapenlp::games.begin(), grapenlp::games.end()))),
			music(&(uobt_root.concat(grapenlp::music.begin(), grapenlp::music.end()))),
			photos(&(uobt_root.concat(grapenlp::photos.begin(), grapenlp::photos.end()))),
			pattern(&(uobt_root.concat(grapenlp::pattern.begin(), grapenlp::pattern.end()))),
			something(&(uobt_root.concat(grapenlp::something.begin(), grapenlp::something.end()))),

			code(&(uobt_root.concat(grapenlp::code.begin(), grapenlp::code.end()))),

			alertas(&(uobt_root.concat(grapenlp::alertas.begin(), grapenlp::alertas.end()))),
			alta(&(uobt_root.concat(grapenlp::alta.begin(), grapenlp::alta.end()))),
			
			info(&(uobt_root.concat(grapenlp::info.begin(), grapenlp::info.end()))),
			tarifaplana(&(uobt_root.concat(grapenlp::tarifaplana.begin(), grapenlp::tarifaplana.end()))),
			tv(&(uobt_root.concat(grapenlp::tv.begin(), grapenlp::tv.end()))),
			emocionmovistar(&(uobt_root.concat(grapenlp::emocionmovistar.begin(), grapenlp::emocionmovistar.end()))),
			escritoriomovistar(&(uobt_root.concat(grapenlp::escritoriomovistar.begin(), grapenlp::escritoriomovistar.end()))),
			promociones(&(uobt_root.concat(grapenlp::promociones.begin(), grapenlp::promociones.end()))),
			saldo(&(uobt_root.concat(grapenlp::saldo.begin(), grapenlp::saldo.end()))),
			videollamada(&(uobt_root.concat(grapenlp::videollamada.begin(), grapenlp::videollamada.end())))
		{}
	};
} //namespace grapenlp

#endif /*GRAPENLP_TAG_DICO_H*/
