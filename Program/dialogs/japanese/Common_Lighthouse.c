#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("町で警報が鳴ったようだ。どうやら俺も武器を取る時が来たらしいな……","もしかして、町の衛兵たちに追われてるんじゃねえか？","ここには隠れ家なんてねえが、肋骨の下に冷たい鋼を何インチか突き立てられるかもな！"),LinkRandPhrase("何の用だ、 "+GetSexPhrase("悪党","悪党")+"？！衛兵たちがお前を追っている、そう遠くへは行けねえぞ。 "+GetSexPhrase("汚ねえ海賊","くさい野郎")+"!",""+GetSexPhrase("Filthy","Filthy")+" 「殺人者だ！衛兵！衛兵！！」","「俺はお前なんか怖くねえ」 "+GetSexPhrase("這い寄る","くさい野郎")+"！すぐにお前は俺たちの砦で絞首刑だ、逃げられやしねえぞ……"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("生きるのに飽きたようだな……","そうみたいだな、この場所には平和な人間はいないようだ "+XI_ConvertString("Colony"+npchar.city+"Gen")+"「みんな英雄になりたがるんだ！」"),RandPhraseSimple("地獄へ落ちろ！","へっ、これがお前の人生の最後の数秒だぜ……"));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "今度は何の用で俺のところに来たんだ？";
				link.l1 = "ジェラール・ルクロワという紳士をご存知だと思いますが？私への報酬を預けているはずなんですが…";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("「こんにちは、水夫さん！私の名前は」 "+GetFullName(npchar)+"、そして私はこの灯台の番人だ。どんな風に吹かれてここへ来たんだ？","やあ、いらっしゃい！灯台で新しい顔を見るのは本当に久しぶりだよ……自己紹介させてもらおう―― "+GetFullName(npchar)+"、そしてこの灯台は俺の家であり仕事場でもあるんだ。何か用かい？");
				link.l1 = "「やあ、」 "+npchar.name+"！俺の名前は "+GetFullName(pchar)+"、俺は船長だ。この素晴らしい入り江を散歩していて、ここに誰が住んでいるのか見に立ち寄ることにしたんだ。";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、古き友よ、船長」 "+GetFullName(pchar)+"！さあ、入ってくれ、入ってくれ！今回は何の用だ？";
				link.l1 = "やあ、古い船乗りよ！この灯台でひとりぼっちで泣き言でも言ってるんじゃねえのか？";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "これで分かっただろう。俺も昔はお前みたいな船乗りだったんだが、もう長いこと船の甲板には立ってねえ。 今じゃこの灯台を任されてて、ついでにちょっとした物も売ってるんだ…";
			link.l1 = "「で、あんたはいったい何を売ってるんだ？」";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " 今回は何の用で来たんだ？";
			link.l1 = RandPhraseSimple("最近あなたの植民地で何か面白いことが起きたか教えてくれないか？","しばらく陸に上がってなかったんだが……ここで何が起きてるんだ？");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "何を売っているか見せてくれ。";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "それで、 "+npchar.name+"、俺の護符はもう届いたか？";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+"、あなたにお守りを注文したいんだ。";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "「聞け、」 "+npchar.name+"、あんたが注文でお守りを届けているって知ってるぜ。だから、お守りについて詳しいはずだ。頼む、 この小さな品を見てくれ――何かわかることはあるか？";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "旦那、また来たぜ、あの奇妙なお守りについて聞きに来たんだ";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "「あなたに聞きたいことがあったんだが……」";
			link.l4.go = "quests";
			link.l9 = "ちょっと覗いてみただけだ……";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "時々、浜辺に行って貝殻を集めているんだ。ここからそう遠くないところに綺麗な場所があって、 だから俺からいつでも真珠を買えるぜ。嵐のたびに琥珀も流れ着く、それも売ってるが、かなり高くつくぞ。\n時には波が沈没船からいろんな面白いガラクタを運んでくるし、昔の仲間たちが特別な品を持ってきてくれることもある。 俺は魔法の護符に興味があってな、賢者どもはそれにいい金を払うんだ。\n特別な時には武器も出すが、どこで手に入れたかは聞くなよ。町の商人がガラクタは全部買い取ってくれるが、 いい品は自分で直して磨いてから自分で売るのさ。\n俺が興味あるのはラム酒だ。あの地元の酒場で二ペソで出してるションベンみたいなやつじゃねえぞ。 本物の瓶詰めジャマイカン・ラムだ。あれは人を癒し、蘇らせる。一本持ってきてくれたら十倍払うぜ。考えてみな。";
			link.l1 = "「聞け、」 "+npchar.name+"「お前、古い船乗り仲間が魔法のアミュレットを持ってきてくれるって言ってたな。 特定のアミュレットを注文することはできるのか？たっぷり金は払うぜ。」";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "船長、最近いくらかの積荷が浜に打ち上げられました―― "+GetGoodsNameAlt(sti(npchar.quest.goods))+"。一部は海水でダメになったが、 "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" 素晴らしい状態で救い出せたんだ。いくつか買わないか？あんたのためだけに安くしてやるぜ、ただし "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" 1単位あたり。";
				link.l1 = "いや。最近の収穫を見せてくれ。";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "ふむ……正直な申し出だな、同意しよう。多少は転売して儲けも出せそうだ。さて……それで合計は "+FindRussianMoneyString(sti(npchar.quest.goodscost))+"。そういうことか？";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "その通りだぜ、船長。いい取引だったな！お互いしっかり儲けたってわけさ……";
			link.l1 = "よし、それじゃあ。船乗りたちに荷物を俺の船まで運ばせるぜ。さて、売り物を見せてくれ。";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "まあ、全部ってわけじゃねえが、よく持ち込まれる小物もあるから、手伝えると思うぜ。だが警告しとくぞ： こういう注文の護符は全部で100ドゥブロンかかるんだ。分かってくれよ……";
				link.l1 = "値段は問題じゃねえ。どんなお守りがあるんだ？";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "ふん！そんな大金があれば船一隻買えるぜ。高すぎるな。俺は自分でなんとかするさ…";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "いいえ、船長。そういうものは偶然にしか見つからないので、前もって注文するのは無理です。それに、 手に入るまでほとんど永遠に待たなきゃならないでしょうね…";
				link.l1 = "そうか、なら仕方ねえな。";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "ご希望通りに。気が変わったらまた会いに来てくれ。";
			else dialog.text = "今日はどんな品を売っているかご覧になりますか、船長？もし気に入る物がなければ、またすぐにお越しください――他の商品が入るかもしれませんよ。";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "もちろん、これらはすべて良いことだが、実は聞きたいことがあるんだ――ジェラール・ルクロワという紳士をご存じだろう？俺のために報酬を預けているはずなんだが…";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "お前の品物を見せてくれ。";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "最近、あなたの植民地で何か面白いことが起きたか教えてくれないか？";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "取引は取引だが、ちょっと聞きたいことがあるんだ。";
			link.l3.go = "quests";
			link.l4 = "良い一日を。 "+npchar.name+"！お会いできて嬉しかったです！また今度立ち寄りますね…";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "お選びください。";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "残念ながら、このリストには今のところ興味を引くものはないな。";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "ブードゥー人形か？火器が好きなのか？いいだろう…";
			link.l1 = "注文品を受け取りにいつ戻ればいいんだ？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "火薬の検査役か？どんな小競り合いでも、射撃の腕が勝敗を分けるんだぜ。いいじゃねえか…";
			link.l1 = "注文品を受け取りにいつ戻ればいい？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "儀式用のナイフか？お前は重いブロードソードで敵を力強く斬りつけるのが好きなんだろ？だったら、これはお前向きだ。 いいだろう… ";
			link.l1 = "注文品を受け取りにいつ戻ればいいんだ？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "ポールアックスか？でかい斧での振り下ろしなら、どんな敵でも叩き潰せるぜ！いいな……";
			link.l1 = "「注文品を受け取りにいつ戻ればいい？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "ツァンツァか？あんなものは、どんな向こう見ずな海賊でもビビらせるぜ。いいぞ……";
			link.l1 = "注文を受け取りに戻るのはいつにすればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "サンゴ礁か？お前の大砲のブドウ弾なら、まっすぐ標的に飛んでいくぜ！いいぞ…";
			link.l1 = "注文品を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "コブハクジラ？戦士にとって不屈こそが最高の味方だ。よし…";
			link.l1 = "「注文品を受け取りに戻るのはいつがよいですか？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "「シウテクウトリよ？敵船の船体を塵にしてやれ！よし…」";
			link.l1 = "「注文品を受け取りに戻るのはいつがよいですか？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "バルド？バルドを配置しろ――そうすりゃ、どの砲弾も的にまっすぐ飛んでいくぜ！よし…";
			link.l1 = "注文品を受け取りにいつ戻ればいい？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "カスカヴェラか？蛇の毒は一番危険なもんだ。いいだろう…";
			link.l1 = "注文を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "ンゴンボの仮面か？敵の警戒心を下げるってな、ははっ！いいじゃねえか…";
			link.l1 = "注文品を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "ンゴンボの盾か？弾を避けられなかった時でも、このお守りが命を救ってくれるぜ。いいだろう…";
			link.l1 = "注文品を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "エウコロギオンか？良い祈りは弾丸さえも逸らすことができる。いいだろう…";
			link.l1 = "注文品を受け取りに戻るのはいつがよいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "十字架か？これはキリスト教徒の白兵戦に大いに役立つだろう。よし…";
			link.l1 = "注文品を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "エル・トロソか？これは致命傷をただのかすり傷に変えてくれるぜ。いいな…";
			link.l1 = "注文を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "ソグボ？そして、大砲はいつでも戦闘準備万端であるように！よし…";
			link.l1 = "「注文品を受け取りに戻るのはいつがよいですか？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "マドンナ？聖母マリアの御姿には強力な癒しの力があるのだ。よろしい…";
			link.l1 = "注文品を受け取りにいつ戻ればいい？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "聖水だと？どんな弱虫でも聖水を浴びれば伝説の英雄になれるってわけだ！よし…";
			link.l1 = "注文品を受け取りにいつ戻ればいい？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "錨か？お前の船が砲弾の雨の中でも沈まねえよう祈ってやるぜ、ははっ！よし…";
			link.l1 = "「注文品を受け取りに戻るのはいつがよいですか？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "エンコルピオンか？この護符を持っていれば、お前の帆はどんな風も恐れぬだろう。よし…";
			link.l1 = "注文を受け取りに戻るのはいつにすればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "奇跡を起こす者か？主が陸でも海でもお前さんの乗組員を見守ってくださるように！良い…";
			link.l1 = "注文品を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "チマルタか？お前の頭上をマスケット弾が飛び交うが、傷一つ負わねえぜ！よし…";
			link.l1 = "「注文品を受け取りにいつ戻ればいい？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "テレド？どの船大工も一度は夢見るやつだ。いいだろう…";
			link.l1 = "注文品を受け取りにいつ戻ればいい？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "ソチピリ？それなら帆の繕いにかかる時間が省けるな。よし…";
			link.l1 = "「注文品を受け取りに戻るのはいつがよいですか？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "猿だと？俺から見りゃ荷運びのロバだぜ！よし…";
			link.l1 = "注文を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "ジプシーのファンか？見回りの目をごまかすとはな！いいだろう…";
			link.l1 = "俺の注文を受け取りにいつ戻ればいいんだ？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "翡翠の亀か？それがあんたの切り札ってわけだな！いいだろう…";
			link.l1 = "注文を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "猿拳か？よく言うだろう――相手に一目置かせろってな！よし…";
			link.l1 = "「注文品を受け取りにいつ戻ればいい？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "漁師か？それはどの航海士にとっても夢だぜ。よし…";
			link.l1 = "注文品を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "商人の数珠か？金は数えられるのが好きだろう、そうじゃねえか？……いいだろう…";
			link.l1 = "「注文品を受け取りにいつ戻ればいい？」";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "エエカトルだと？どんな鈍くさい古い船でも風より速く走るぜ！よし…";
			link.l1 = "注文品を受け取りにいつ戻ればいい？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "水夫のイヤリングだと？それは操舵手にやっとけ！よし…";
			link.l1 = "注文品を受け取りにいつ戻ればいい？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "巡礼者か？向かい風が追い風になるってわけだ。いいだろう…";
			link.l1 = "注文品を受け取りにいつ戻ればいいですか？";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "二ヶ月後だ、それより早くは無理だと思う。その頃には奴らがそれを俺のところに持ってくるはずだ。 だから二ヶ月後に金を用意して待ってるぜ。";
			link.l1 = "素晴らしい！必ず行くよ！ありがとう、 "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "ああ、持ってるぜ。100ドゥブロン用意したか、船長？"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "もちろん！はい、約束通りだ。";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "あっ、金は船に置いてきちまった！すぐに持ってくるぜ。";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "まだだ。後でまた来てくれ。心配すんな――お前の護符はきっと届くぜ。";
			link.l1 = "「よし。」";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveDublonsFromPCharTotal(100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "すべて問題なさそうだ。これがあんたの護符だ。幸運を祈るぜ！";
			link.l1 = "ありがとうございます。 "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "そこにあるものを見せてくれ。";
			link.l1 = "ここにあるのは、どうやら古代インディアンの護符らしいな。だが、使い方も隠された力も俺にはさっぱりわからねえ。";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "ほうほう。こんなものを見せてくれたのは、お前で三人目だぜ、相棒。 このお守りは南方の原生林から持ち込まれたもんだ。パナマの近くには、 こういう飾りを身につけてるインディアンがいるんだよ。あいつら赤肌は、これが『偉大なる祖先』 の遺産だって言ってるぜ。\nその祖先が誰なのか、どんな遺産を残したのかは俺にはさっぱり分からねえが、 どこで聞き込みすりゃいいかは教えてやれるぜ。興味あるか？";
				link.l1 = "もちろんだ！";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "ふむ……俺はいろんなお守りを手にしてきたが、こんなのはカリブで初めて見るぜ。悪いな、相棒、俺にはわからねえ。 こういうのは専門外だ。でも、ただの物じゃねえことは確かだ。他の誰かに聞いてみな。 俺みたいにお守りに詳しい灯台守が他にもいるはずだぜ。";
				link.l1 = "失礼しました……それでは引き続きお尋ねします。";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "ドミニカにはカリブ族の村があって、そこの酋長はモクニテクヴリという名だ。 彼らにはトゥットゥアタパクというシャーマンがいて、インディアンの中でもとても尊敬されている人物だ。 彼はカリブ族じゃなくて、前に話したあの土地の出身なんだ。この護符については、俺よりも彼の方が詳しいだろう。 だが気をつけろ――トゥットゥアタパクは白人を憎んでいる。本当に心の底からな。昔、 奴らに奴隷にされて故郷から連れ去られたことがあるからだ……";
			link.l1 = "奴もそうやってカリブに来たってことか？";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "ああ。これはなかなか興味深い話だ。インディアンの奴隷を乗せた船がマリー・ガラント付近で無風に捕まり、 乗組員の半分が急な熱病で死んだんだ。だが、インディアンは一人も病気にならなかった！\nその後、船長が発狂して自分の船に火を放った。その結果、囚われていたインディアンたちが暴動を起こし、 乗組員を皆殺しにしたんだ。さて、誰が彼らのリーダーだったか分かるか？";
			link.l1 = "「私は……」";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "それだけだ。きっとシャーマンの呪いで海が死人のように静まり返り、乗組員に死の病が広まったんだ。 このインディアンはとても賢くて、非常に危険な奴だ。もしあいつのところへ行くなら、 礼儀正しくして言葉に気をつけろ――さもないと大変な目に遭うぜ。それに、供え物がなければ話すことさえしてくれねえぞ。";
			link.l1 = "「それで、どんな供物を要求するんだ？」";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "くだらない物じゃ彼を買収できねえよ。俺の知る限り、 あいつはカリブ兵を白人の居住地に送り込んで火器を買わせてるんだ。贈り物としてマスケット銃を持っていけば、 きっと喜んで少しはお前に関心を示してくれるだろうさ。";
			link.l1 = "ありがとう！言われた通りにするよ…教えてくれ、どうしてそんなことまで知っているんだ？";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "俺の友人はあの不運な船の水夫だったんだ。幸いにも、あの地獄から生き延びることができた……あんたと同じような護符を彼が身につけているのを見たから、 亡くなった船長もインディアンの持ち物をいくつか持ち出したんだろうな。 あんたの護符もきっとそのコレクションの一つさ――船長が正気を失って自分の船に火を放ったとき、水夫たちは船長を殺してから船室の箱をあさったんだ。";
			link.l1 = "了解だ。じゃあ、あとはドミニカに贈り物を持っていくだけだな。手助けと面白い話をありがとう！";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "幸運を祈るぜ、相棒。あの赤い肌の悪魔には気をつけろよ……";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "はい？トゥトゥアタパクと話したんだろう？";
			link.l1 = "その通りだ。今度はあと二つのお守りを見つけたいんだ。俺がこの遺物を見せた三人目だと言ってたな。じゃあ、 他の二人は誰だったんだ？";
			link.l1.go = "caleuche_10";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_10":
			dialog.text = "一人は俺の友人で、トゥットゥアタパクをカリブの島々に連れてきたあの船の水夫だ。あの事件以来、 奴はどの船の甲板にも足を踏み入れていない。しばらく会っていないが、どこに住んでいるかは知ってるぜ。 ウェストメインのベリーズで探してみな。今は猟師になって、ジャングルを歩き回ってる。 名前はファーガス・フーパーだ。";
			link.l1 = "いいだろう。で、二つ目は？";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "二人目については、ほんの少ししか知らねえ。名前がジャックなのかジャクソンなのか、私掠船乗りなのか、 小さな商売人なのか、ただの冒険者なのかも分からねえ。奴は変わった名前のシーベックを持ってる……うーん……その名は……くそっ、忘れちまった！だが、その名は何か悪魔的なものだった。意味を聞いたら、奴は「海の神々から生まれた鳥女だ」 と言いやがった。ふん！神も信じねえ奴め……\n";
			link.l1 = "オタクかよ……で、彼女の名前は覚えてないのか？";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "いや、雷に打たれてもいいが、覚えてねえな。ああ、そうだ、自己紹介したときにバルバドスから来たって言ってたぜ。";
			link.l1 = "そりゃすげえな！よし、羽根女好きの野郎を他の奴らより先に見つけてやるぜ……ありがとな、相棒、助かったぜ！";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "どういたしまして、船長、たまには寄ってくれよ。";
			link.l1 = "もちろんだ！";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
			AddLandQuestMark(characterFromId("Bridgetown_Portman"), "questmarkmain");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("お前は "+GetSexPhrase(" 泥棒だよ、旦那！衛兵ども、そいつを捕まえろ"," 泥棒だ！衛兵たち、あの女を捕まえろ")+"!!!","おったまげたぜ！ちょっと目を離した隙に、もうお前は宝箱に頭を突っ込んでやがる！止まれ、泥棒め！","衛兵！強盗だ！泥棒を止めろ！");
			link.l1 = "ちくしょう、くそっ！";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "ああ、あんたがあの船長か！そうさ、ずっと待ってたんだ。ジェラールも待ってたけど、 急な遠征で出かけなきゃならなくなってな、代わりに俺が支払いを渡すよう頼まれたんだ。 あんたが必ず来るって言ってたぜ。ここにドゥブロン金貨が90枚ある、どうぞ。");
			link.l1 = "ありがとうございます！正直者と取引できて嬉しいです。";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 90);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
