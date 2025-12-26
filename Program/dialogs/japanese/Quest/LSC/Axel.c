// торговец Аксель Йост
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "ほう、見てみろよ……"+GetFullName(pchar)+"「おい！死んだはずじゃねえのか？どうやって戻ってきたんだ？」";
				link.l1 = "簡単さ。俺は一度も死んだことがねえんだ、ははっ！";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "へっ、相棒、ナーワル族と和解するまでは取引しねえぜ。あいつらに面倒ごとを起こされたくねえんだ。 ファジオに話してみな、あいつなら力になれるぞ。";
				link.l1 = "よし、すぐに彼に会いに行くぜ。";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "俺はお前と話したくねえんだ、相棒。お前は何の理由もなく無実の人々を襲って、喧嘩をふっかけるじゃねえか。 消え失せろ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ああ、新顔だな！何の用でここに来たんだ？いや、俺が聞くことじゃねえかもな……自己紹介させてもらうぜ。俺の名はアクセル・ヨースト、この店の主だ。何か気に入った物はあるか？";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"。どんな品物を売っているんだ？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+pchar.name+"！会えて嬉しいぜ。買いに来たのか、それとも売りに来たのか？";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "聞いてくれ、アクセル、いいライフルは売ってないか？普通の兵隊が持つマスケットじゃなくて、 もっと精度と射程の高いやつだ。";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "聞けよ、アクセル、チャド・キャッパーがウイスキーの樽を手に入れてくれって頼んできたか？ ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "聞いてくれ、アクセル。お前はあの間抜けとの会話を聞いていただろう。奴はどんなビーズを求めていたんだ？ 俺にはさっぱり分からねえ。";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "ああ。取引しようぜ、Axel！";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("「島の周りで何か噂を聞いたか、アクセル？」", "最近、この正義の島で何が起きているんだ？", "最近どんな噂を聞いたんだ？");
				link.l2.go = "rumours_LSC";
				link.l3 = "まだだ。ちょっと挨拶したかっただけさ。";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "いろんなものがあるぜ：薬、刃物、火器、弾薬、胸当て、宝石、鉱石、魔法のアミュレットや護符、ガラクタ、 クラフト用の素材……\nみんな沈没船で見つけた自分に要らねえ物を俺に持ってくるんだ。あんたも遠慮なく持ってきてくれていいぜ。ただし、 食料や船用品は扱ってねえからな。";
			link.l1 = "いいだろう、アクセル。何を持っているか見せてくれ。";
			link.l1.go = "Trade_items";
			link.l2 = "ありがとう、Axel。覚えておくよ。必要な時はまた会おう。";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "冗談だろう。お前で三人目だぞ、同じことを聞かれたのは！\n俺はそんな武器は持ってねえが、 数か月前にアドルフ・バルビエがスコープ付きの狩猟用シュトゥッツェンを売ろうとしてきたんだ。 素晴らしい銃だったぜ、まさにお前が探してるものだ。\nだがバルビエのやつ、とんでもない値をふっかけてきやがったから、断ったのさ。";
			link.l1 = "本当か！それで、バルビエはどこにいるんだ？";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "さあな。たぶん街をうろついてるんじゃねえか。サンチョの酒場によく行くし、毎晩のように一杯やるのが好きなんだ。";
			link.l1 = "ありがとう！そこで探してみるよ。ところで、アクセル、他に誰がそのライフルについて君に聞いてきたんだ？ 他にも興味を持っていた者がいると言っていたけど、それは誰なんだ？";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "メアリー・キャスパーとマルチェロ――通称サイクロプスだ。\nあの娘が何でライフルを欲しがるのかさっぱり分からねえが、まあ、俺たちの赤毛のメアリーは有名な変わり者だからな。 一年前には地雷を作るために火薬を山ほど買い込んだ――「カニを気絶させるため」だとさ。ドナルドが止めてくれて本当に助かったぜ。\nそれからマルチェロは鳥撃ち用にライフルが欲しいと言ってた。塩漬け牛肉にはもう飽きたらしい。 二人ともアドルフを紹介しておいた。どっちかにライフルを売ったかどうかは知らねえ。\nそれと……あのずる賢い野郎ジュゼッペ・ファツィオも最近アドルフのことを聞きに来てた。 あいつもシュトゥッツェンを買うつもりかもしれねえな。";
			link.l1 = "どうやら競争相手が多いみたいだな。まあいい、アドルフを探しに行くぜ――まだシュトゥッツェンを売ってなきゃいいが。";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "へっ、それがあいつの言う「大きな真珠」さ！誰にでもそれをせがむんだ。ひとつ渡せば、 あんたはあいつの親友になれるぜ。";
			link.l1 = "ああ、なるほど。大きな真珠か……ありがとう、アクセル。普通のビーズを探していたら、俺はくたくたになってたぜ！";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "ああ、相棒、そうだよ。でもな、もしお前さんもブッシュミルズの樽を買いたいってんなら、残念だが無理だぜ。 俺が持ってたのは一本だけで、チャドが買っちまったんだ。代わりにスコッチウイスキーならあるぜ――アイリッシュにも負けてねえし、実を言うと俺はこっちの味の方が好きなんだ。";
			link.l1 = "また今度だ。チャドが他に何か買っていったか？";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "いいや。ああ！彼はヒ素に興味があったよ、タルタロス号にはネズミが多すぎるから退治したいって言ってたんだ。\n俺はもうヒ素は扱ってないんだ、オーレを雇って店を掃除してもらうようになってから必要なくなったからな。 手元にあった分は可哀想なサンチョにやったよ、どうやらネズミどもが彼の酒場に引っ越したみたいでな。 なぜネズミがあんなにオーレを怖がるのかは分からねえが……";
			link.l1 = "もしかして、あいつの父親は猫だったのかもな。";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "ははは！まあな……とにかく、サンチョがヒ素を持ってるぜ、もし瓶が欲しいならな。";
			link.l1 = "わかった、ありがとう。すぐに彼に会いに行くよ。";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
