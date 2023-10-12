# include <Siv3D.hpp>

/// @brief アイテムのボタン
/// @param rect ボタンの領域
/// @param texture ボタンの絵文字
/// @param font 文字描画に使うフォント
/// @param name アイテムの名前
/// @param desc アイテムの説明
/// @param count アイテムの所持数
/// @param enabled ボタンを押せるか
/// @return ボタンが押された場合 true, それ以外の場合は false
bool Button(const Rect& rect, const Texture& texture, const Font& font, const String& name,const String& desc, int32 count, bool enabled)
{
	if (enabled)
	{
		rect.draw(ColorF{ 0.3, 0.5, 0.9, 0.8 });

		rect.drawFrame(2, 2, ColorF{ 0.5, 0.7, 1.0 });

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
	else
	{
		rect.draw(ColorF{ 0.0, 0.4 });

		rect.drawFrame(2, 2, ColorF{ 0.5 });
	}

	texture.scaled(0.5).drawAt(rect.x + 50, rect.y + 50);

	font(name).draw(30, rect.x + 100, rect.y + 15, Palette::White);

	font(desc).draw(18, rect.x + 102, rect.y + 60, Palette::White);

	font(count).draw(50, Arg::rightCenter((rect.x + rect.w - 20), (rect.y + 50)), Palette::White);

	return (enabled && rect.leftClicked());
}

void Main()
{
	
	// フォント
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// 自動生産
	const Array<Texture> Emoji{ Texture{U"🌾"_emoji}, Texture{ U"🏭"_emoji }, Texture{ U"🗺️"_emoji }, Texture{ U"🪐"_emoji }};

	// 絵文字
	const Array<Texture> texture { Texture{U"🍎"_emoji}, Texture{ U"🍌"_emoji }, Texture{ U"🍈"_emoji }, Texture{ U"🧊"_emoji }, Texture{ U"🍇"_emoji }, Texture{ U"🍑"_emoji }};

	// クリック円
	Array<Circle> circle{ Circle{170, 300, 100 }, Circle{ 970, 300, 100 }, Circle{ 1770, 300, 100 }, Circle{ 2570, 300, 100 }, Circle{ 3370, 300, 100 }, Circle{ 4170, 300, 100 }};

	//背景
	Array<Rect> back{ Rect{0, 0, 800, 600}, Rect{ 800, 0, 800, 600 }, Rect{ 1600, 0, 800, 600 }, Rect{ 2400, 0, 800, 600 }, Rect{ 3200, 0, 800, 600 }, Rect{ 4000, 0, 800, 600 }};

	// 表示サイズ（倍率）
	Array<double> size {1.5, 1.5, 1.5, 1.5, 1.5, 1.5 };

	// 個数
	Array<double> num {0, 0, 0, 0, 0, 0};

	//毎秒の生産量
	Array<int32> cps {0, 0, 0, 0, 0, 0};

	// 農場の所有数
	Array<int32> farmCount {0, 0, 0, 0, 0, 0};

	// 工場の所有数
	Array<int32> factoryCount {0, 0, 0, 0, 0, 0};

	// 国家の所有数
	Array<int32> countryCount {0, 0, 0, 0, 0, 0};

	// 惑星の所有数
	Array<int32> planetCount {0, 0, 0, 0, 0, 0};

	// 農場の価格
	Array<int32> farmCost {10, 10, 10, 10, 10, 10};

	// 工場の価格
	Array<int32> factoryCost {100, 100, 100, 100, 100, 100};

	// 国家の価格
	Array<int32> countryCost {1000, 1000, 1000, 1000, 1000, 1000};

	// 惑星の価格
	Array<int32> planetCost {10000, 10000, 10000, 10000, 10000 ,10000};

	// ゲームの経過時間の蓄積10000
	double accumulatedTime = 0.0;

	int n = 0;

	while (System::Update())
	{

		ClearPrint();
		Print << n;


		if (n > -4000 && KeyRight.down())
		{
			n -= 800; for (int i = 0; i < 6; i++)
			{
				back[i].x -= 800;
				circle[i].x -= 800;
			}
		}
		if (n < 0 && KeyLeft.down())
		{
			n += 800; for (int i = 0; i < 6; i++)
			{
				back[i].x += 800;
				circle[i].x += 800;
			}
		}
	
		// ゲームの経過時間を加算する
		accumulatedTime += Scene::DeltaTime();

		for (int i = 0; i < 6; i++)
		{
			// 毎秒の生産量 (cookies per second) を計算する
			cps[i] = (farmCount[i] + factoryCount[i] * 10 + countryCount[i] * 100 + planetCount[i] * 1000);

			// 0.1 秒以上蓄積していたら
			if (0.1 <= accumulatedTime)
			{
				accumulatedTime -= 0.1;

				// 0.1 秒分の生産を加算する
				num[i] += (cps[i] * 0.1);
			}
		}

		// 背景を描く
		back[0].draw(Arg::left = HSV{ 0 }, Arg::right = HSV{ 35 });
		back[1].draw(Arg::left = HSV{ 35 }, Arg::right = HSV{ 65 });
		back[2].draw(Arg::left = HSV{ 65 }, Arg::right = HSV{ 150 });
		back[3].draw(Arg::left = HSV{ 150 }, Arg::right = HSV{ 280 });
		back[4].draw(Arg::left = HSV{ 280 }, Arg::right = HSV{ 300 });
		back[5].draw(Arg::left = HSV{ 310 }, Arg::right = HSV{ 340 });

		for (int i = 0; i < 6; i++)
		{

			// 農場の価格を計算する
			farmCost[i] = 10 + (farmCount[i] * 10);

			// 工場の価格を計算する
			factoryCost[i] = 100 + (factoryCount[i] * 100);

			// 国家の価格を計算する
			countryCost[i] = 1000 + (countryCount[i] * 1000);

			// 惑星の価格を計算する
			planetCost[i] = 10000 + (planetCount[i] * 10000);

			// 円上にマウスカーソルがあれば
			if (circle[i].mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			// 円が左クリックされたら
			if (circle[i].leftClicked())
			{
				size[i] = 1.3;
				num[i] += 10000;
			}

			// 表示サイズを回復する
			size[i] += Scene::DeltaTime();

			if (1.5 < size[i])
			{
				size[i] = 1.5;
			}

			// 数を整数で表示する
			font(U"{:.0f}"_fmt(num[i])).drawAt(60, (170 + 800 * i) + n, 100);

			// 生産量を表示する
			font(U"毎秒: {}"_fmt(cps[i])).drawAt(24, (170 + 800 * i) + n, 160);

			// 描画する
			texture[i].scaled(size[i]).drawAt(circle[i].center);
		}

		// 農場ボタン
		if (Button(Rect{ 340 + n, 40, 420, 100 }, Emoji[0], font, U"りんご農場", U"C{} / 1 CPS"_fmt(farmCost[0]), farmCount[0], (farmCost[0] <= num[0])))
		{
			num[0] -= farmCost[0];
			++farmCount[0];
		}
		if (Button(Rect{ 1140 + n, 40, 420, 100 }, Emoji[0], font, U"ばなな農場", U"C{} / 1 CPS"_fmt(farmCost[1]), farmCount[1], (farmCost[1] <= num[1])))
		{
			num[1] -= farmCost[1];
			++farmCount[1];
		}
		if (Button(Rect{ 1940 + n, 40, 420, 100 }, Emoji[0], font, U"めろん農場", U"C{} / 1 CPS"_fmt(farmCost[2]), farmCount[2], (farmCost[2] <= num[2])))
		{
			num[2] -= farmCost[2];
			++farmCount[2];
		}
		if (Button(Rect{ 2740 + n, 40, 420, 100 }, Emoji[0], font, U"あいす農場(製氷機)", U"C{} / 1 CPS"_fmt(farmCost[3]), farmCount[3], (farmCost[3] <= num[3])))
		{
			num[3] -= farmCost[3];
			++farmCount[3];
		}
		if (Button(Rect{ 3540 + n, 40, 420, 100 }, Emoji[0], font, U"ぶどう農場", U"C{} / 1 CPS"_fmt(farmCost[4]), farmCount[4], (farmCost[4] <= num[4])))
		{
			num[4] -= farmCost[4];
			++farmCount[4];
		}
		if (Button(Rect{ 4340 + n, 40, 420, 100 }, Emoji[0], font, U"もも農場", U"C{} / 1 CPS"_fmt(farmCost[5]), farmCount[5], (farmCost[5] <= num[5])))
		{
			num[5] -= farmCost[5];
			++farmCount[5];
		}

		// 工場ボタン
		if (farmCount[0] >= 1)
		{
			if (Button(Rect{ 340 + n, 160, 420, 100 }, Emoji[1], font, U"ﾘﾝｺﾞｼﾞｭｰｽ工場", U"C{} / 10 CPS"_fmt(factoryCost[0]), factoryCount[0], (factoryCost[0] <= num[0])))
			{
				num[0] -= factoryCost[0];
				++factoryCount[0];
			}
		}
		if (farmCount[1] >= 1)
		{
			if (Button(Rect{ 1140 + n, 160, 420, 100 }, Emoji[1], font, U"ﾊﾞﾅﾅｽﾑｰｼﾞｰ工場", U"C{} / 10 CPS"_fmt(factoryCost[1]), factoryCount[1], (factoryCost[1] <= num[1])))
			{
				num[1] -= factoryCost[1];
				++factoryCount[1];
			}
		}
		if (farmCount[2] >= 1)
		{
			if (Button(Rect{ 1940 + n, 160, 420, 100 }, Emoji[1], font, U"ﾒﾛﾝｿｰﾀﾞ工場", U"C{} / 10 CPS"_fmt(factoryCost[2]), factoryCount[2], (factoryCost[2] <= num[2])))
			{
				num[2] -= factoryCost[2];
				++factoryCount[2];
			}
		}
		if (farmCount[3] >= 1)
		{
			if (Button(Rect{ 2740 + n, 160, 420, 100 }, Emoji[1], font, U"氷水工場(冷凍庫)", U"C{} / 10 CPS"_fmt(factoryCost[3]), factoryCount[3], (factoryCost[3] <= num[3])))
			{
				num[3] -= factoryCost[3];
				++factoryCount[3];
			}
		}
		if (farmCount[4] >= 1)
		{
			if (Button(Rect{ 3540 + n, 160, 420, 100 }, Emoji[1], font, U"ﾜｲﾝ工場", U"C{} / 10 CPS"_fmt(factoryCost[4]), factoryCount[4], (factoryCost[4] <= num[4])))
			{
				num[4] -= factoryCost[4];
				++factoryCount[4];
			}
		}
		if (farmCount[5] >= 1)
		{
			if (Button(Rect{ 4340 + n, 160, 420, 100 }, Emoji[1], font, U"桃缶工場", U"C{} / 10 CPS"_fmt(factoryCost[5]), factoryCount[5], (factoryCost[5] <= num[5])))
			{
				num[5] -= factoryCost[5];
				++factoryCount[5];
			}
		}

		// 国家ボタン
		if (factoryCount[0] >= 1)
		{
			if (Button(Rect{ 340 + n, 280, 420, 100 }, Emoji[2], font, U"林檎王国", U"C{} / 100 CPS"_fmt(countryCost[0]), countryCount[0], (countryCost[0] <= num[0])))
			{
				num[0] -= countryCost[0];
				++countryCount[0];
			}
		}
		if (factoryCount[1] >= 1)
		{
			if (Button(Rect{ 1140 + n, 280, 420, 100 }, Emoji[2], font, U"甘蕉帝国", U"C{} / 100 CPS"_fmt(countryCost[1]), countryCount[1], (countryCost[1] <= num[1])))
			{
				num[1] -= countryCost[1];
				++countryCount[1];
			}
		}
		if (factoryCount[2] >= 1)
		{
			if (Button(Rect{ 1940 + n, 280, 420, 100 }, Emoji[2], font, U"舐瓜協和国", U"C{} / 100 CPS"_fmt(countryCost[2]), countryCount[2], (countryCost[2] <= num[2])))
			{
				num[2] -= countryCost[2];
				++countryCount[2];
			}
		}
		if (factoryCount[3] >= 1)
		{
			if (Button(Rect{ 2740 + n, 280, 420, 100 }, Emoji[2], font, U"海", U"C{} / 100 CPS"_fmt(countryCost[3]), countryCount[3], (countryCost[3] <= num[3])))
			{
				num[3] -= countryCost[3];
				++countryCount[3];
			}
		}
		if (factoryCount[4] >= 1)
		{
			if (Button(Rect{ 3540 + n, 280, 420, 100 }, Emoji[2], font, U"葡萄国", U"C{} / 100 CPS"_fmt(countryCost[4]), countryCount[4], (countryCost[4] <= num[4])))
			{
				num[4] -= countryCost[4];
				++countryCount[4];
			}
		}
		if (factoryCount[5] >= 1)
		{
			if (Button(Rect{ 4340 + n, 280, 420, 100 }, Emoji[2], font, U"桃諸島", U"C{} / 100 CPS"_fmt(countryCost[5]), countryCount[5], (countryCost[5] <= num[5])))
			{
				num[5] -= countryCost[5];
				++countryCount[5];
			}
		}

		// 惑星ボタン
		if (countryCount[0] >= 1)
		{
			if (Button(Rect{ 340 + n, 400, 420, 100 }, Emoji[3], font, U"ﾏﾙｽ･ﾄﾞﾒｽﾃｨｶ星", U"C{} / 1000 CPS"_fmt(planetCost[0]), planetCount[0], (planetCost[0] <= num[0])))
			{
				num[0] -= planetCost[0];
				++planetCount[0];
			}
		}
		if (countryCount[1] >= 1)
		{
			if (Button(Rect{ 1140 + n, 400, 420, 100 }, Emoji[3], font, U"ﾑｻ･ﾊﾟﾗﾃﾞｨｼｱｶ星", U"C{} / 1000 CPS"_fmt(planetCost[1]), planetCount[1], (planetCost[1] <= num[1])))
			{
				num[1] -= planetCost[1];
				++planetCount[1];
			}
		}
		if (countryCount[2] >= 1)
		{
			if (Button(Rect{ 1940 + n, 400, 420, 100 }, Emoji[3], font, U"ｸｸﾐｽ･ﾒﾛ星", U"C{} / 1000 CPS"_fmt(planetCost[2]), planetCount[2], (planetCost[2] <= num[2])))
			{
				num[2] -= planetCost[2];
				++planetCount[2];
			}
		}
		if (countryCount[3] >= 1)
		{
			if (Button(Rect{ 2740 + n, 400, 420, 100 }, Emoji[3], font, U"h2-o1星", U"C{} / 1000 CPS"_fmt(planetCost[3]), planetCount[3], (planetCost[3] <= num[3])))
			{
				num[3] -= planetCost[3];
				++planetCount[3];
			}
		}
		if (countryCount[4] >= 1)
		{
			if (Button(Rect{ 3540 + n, 400, 420, 100 }, Emoji[3], font, U"ｳﾞｨﾃｨｽ星", U"C{} / 1000 CPS"_fmt(planetCost[4]), planetCount[4], (planetCost[4] <= num[4])))
			{
				num[4] -= planetCost[4];
				++planetCount[4];
			}
		}
		if (countryCount[5] >= 1)
		{
			if (Button(Rect{ 4340 + n, 400, 420, 100 }, Emoji[3], font, U"ﾌﾟﾗﾅｽ・ﾍﾟﾙｼｶ星", U"C{} / 1000 CPS"_fmt(planetCost[5]), planetCount[5], (planetCost[5] <= num[5])))
			{
				num[5] -= planetCost[5];
				++planetCount[5];
			}
		}
	}
}
