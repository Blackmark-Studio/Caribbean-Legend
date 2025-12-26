//Jason диалог индейцев в джунглях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","「白い女インディアン」")+" 話がしたいのか？","またお前か、 "+GetSexPhrase("青白い顔","「白い女インディアン」")+".",""+GetSexPhrase("顔の白い奴はよくしゃべるな。まるで女みたいだぜ。","白人女はおしゃべりが好きだな。")+"","精霊が俺をここに連れてきたんだ、色白野郎 "+GetSexPhrase("兄弟。","姉妹")+".","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「ああ。」","ああ、また俺だ。","とても詩的だな。","私もあなたに会えて嬉しいです。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "やあ、白い兄弟よ。インディアンと話したいのか？";
				link.l1 = "ようこそ、ジャングルの息子よ。お会いできて嬉しいが、私は旅を続けねばならぬ。";
				link.l1.go = "exit";
				link.l2 = "ああ、面白い品を売っていると聞いたぜ。何か売り物はあるか？";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "「運がいいな、白い兄弟。」 "+npchar.name+" いくつか商品を売っている。見ていってくれ。";
					link.l1 = "品物を見せてくれ……";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "待てよ。売り物があるんだ。マンガローザっていう植物さ。あんたがこれを好むって聞いたんだが……";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "いいや、白い兄弟よ。 "+npchar.name+" 取引しない。 "+npchar.name+"  は戦士だ。";
					link.l1 = "なるほど。よし、それじゃあな、赤い肌の兄弟よ。";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" 神々の涙を持っている。でかいぞ、白い兄弟よ。その量は "+FindRussianQtyString(sti(npchar.quest.item.qty))+"。欲しいのか？俺は で売ってるぜ "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 一つには。";
					link.l1 = "いや、興味はない。";
					link.l1.go = "exit";
					link.l2 = "もちろんだ！そんな値段なら喜んで買わせてもらうぜ。";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "待てよ。売りたい物があるんだ。マンガ・ローザっていう植物さ。あんたがこういうものが好きだって聞いたぜ…";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" 神々の涙を持っている。小さいやつだ、白い兄弟よ。その量は "+FindRussianQtyString(sti(npchar.quest.item.qty))+"。欲しいのか？俺は で売ってるぜ "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 一つには。";
					link.l1 = "いや、興味はない。";
					link.l1.go = "exit";
					link.l2 = "もちろんだ！そんな値段なら喜んで買わせてもらうぜ。";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "待てよ。売りたいものがあるんだ。マンガローザっていう植物さ。あんたがこういうものが好きだって聞いたぜ……";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" お前ら白い顔が大好きな黄色い金属がある。量は "+FindRussianQtyString(sti(npchar.quest.item.qty))+"。私は～だけで売っている "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 一つには。";
					link.l1 = "いや、興味はない。";
					link.l1.go = "exit";
					link.l2 = "もちろんだ！そんな値段なら喜んで買わせてもらうぜ。";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "待てよ。売り物があるんだ。マンガローザっていう植物さ。あんたがこういうものが好きだって聞いたぜ…";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" お前ら白人がそんなに好きな白い金属があるんだ。その量は "+FindRussianQtyString(sti(npchar.quest.item.qty))+"。私は～だけで売る "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 一つには。";
					link.l1 = "いや、興味はない。";
					link.l1.go = "exit";
					link.l2 = "もちろんだ！そんな値段なら喜んで買わせてもらうぜ。";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "待てよ。売り物があるんだ。マンガローザっていう植物さ。あんたがこういうものが好きだって聞いたぜ…";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "「運がいいな、白い兄弟。」 "+npchar.name+" いくつか商品を売っている。見ていきな。";
					link.l1 = "品物を見せてくれ…";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "待てよ。売り物があるんだ。マンガローザっていう植物さ。あんたがこういうものが好きだって聞いたぜ…";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "いや、白人の兄弟よ。 "+npchar.name+"  取引しない。 "+npchar.name+" - は戦士だ。";
					link.l1 = "なるほど。よし、それじゃあな、赤い肌の兄弟よ。";
					link.l1.go = "exit";
				break;
			}
		break;
		
		case "torg":
			DialogExit();
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = "First time";
			LaunchItemsTrade(NPChar, 0);
			ChangeIndianRelation(1.00);
		break;
		
		// большой жемчуг
		case "big_pearl":
			dialog.text = "「いくつ涙を買いたいんだ？」";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "冗談か、色白野郎？神々の涙なんていらねえのか？じゃあ、さらばだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "俺がどれだけ涙を流したか話しただろう。\nインディアンをからかうつもりか、白顔野郎？\nなら、さらばだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 涙か？よし。お前が俺に "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+"、白い兄弟よ。";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "「ほら、お前の金だ、赤い肌の兄弟よ。」";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "今は十分なお金がないんだ。すまないが、君の真珠は買えない。";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "持っていけ、白い兄弟。今はお前のものだ。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "「いくつ涙を買いたいんだ？」";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "冗談か、色白野郎？神々の涙なんぞいらねえってのか？じゃあな。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "俺がどれだけ涙を流したか話しただろう。インディアンをからかうのか、白顔野郎？じゃあ、さらばだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 涙か？よし。お前が俺に "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+"、白い兄弟よ。";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "「ほら、金だぜ、赤い肌の兄弟。」";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "今は十分なお金がないんだ。すまないが、君の真珠は買えない。";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "持っていけ、白い兄弟。今はお前のものだ。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "いくつ買いたいんだ？";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "冗談かよ、色白野郎？鉄なんていらねえのか？じゃあ、さよならだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "俺は自分が何人いるか言っただろう。インディアンをバカにしてるのか、白顔野郎？じゃあ、さよならだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 「塊か？あんたからか」 "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+"、白い兄弟よ。";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "「ほらよ、お前の金だ、赤い肌の兄弟。」";
				link.l1.go = "gold_1";
			}
			link.l2 = "今は十分なお金がないんだ。すまないが、君の金は買えない。";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "持っていけ、白い兄弟。今はお前のものだ。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "いくつ買いたいんだ？";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "冗談かよ、色白野郎？鉄はいらねえのか？じゃあ、さよならだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "俺は何人いるか言っただろう。インディアンをからかってるのか、白顔野郎？じゃあな。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 「かけら？あんたからか」 "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+"、白い兄弟よ。";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "「ほら、金だぜ、赤い肌の兄弟。」";
				link.l1.go = "silver_1";
			}
			link.l2 = "今は十分なお金がないんだ。すまないが、君の銀は買えない。";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "持っていけ、白い兄弟。今はお前のものだ。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "マンガローザ？見てみたいな。";
			link.l1 = "ほら、見てみろ…";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "はい。これがその名の一つだ――マンガ・ローザ。これのためにお守りをやろう。とても良いお守りで、名前もある―― "+XI_ConvertString(npchar.quest.mangarosa)+"。取引か？";
			link.l1 = "聞いてくれ、赤い肌の兄弟よ、この植物についてもっと知りたいんだ。なぜそんなに必要なのか教えてくれないか？";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" わからないな。取引したいなら、マンガ・ロッサと引き換えにこのお守りを渡すぜ。そうじゃなきゃ、俺は行くぞ。";
			link.l1 = "ああ、まあいいさ。取引しよう。";
			link.l1.go = "mangarosa_3";
			link.l2 = "いやだ。この植物をお守りなんかと交換するつもりはない。";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "持っていけ "+XI_ConvertString(npchar.quest.mangarosa)+"。役に立つ。";
			link.l1 = "間違いないな。幸運を祈るぜ、赤い肌の友よ。";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"運命を試すんじゃねえぞ、色白野郎！剣をしまえ！","聞けよ、色白野郎、武器をしまって話そうぜ。俺は揉め事なんざごめんだ。");
			link.l1 = LinkRandPhrase("「いいだろう。」","「いいだろう。」","おっしゃる通りだな……");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
