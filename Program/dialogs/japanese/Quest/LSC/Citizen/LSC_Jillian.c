// Джиллиан Стайнер - просто девушка
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "俺に近寄るな！路上で喧嘩を始めるような奴とは話さねえ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "あっ……こんにちは！びっくりしたよ。君が来たのに気づかなかった……何か手伝おうか？";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"。俺はこの島に来たばかりなんだ。島の住人たちと知り合おうとしてて、 こんな綺麗な女の人に会わずにはいられなかったんだ。名前を教えてくれないか？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か手伝おうか？";
				link.l1 = LinkRandPhrase("ジリアン！元気か？何か新しいことはあるか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ご機嫌いかがかと思いまして、奥様。では、ごきげんよう！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "照れちゃいますよ、旦那。でも、こちらこそ光栄です。お褒めいただきありがとうございます。私の名前はジリアン、 ジリアン・シュタイナーです。";
			link.l1 = "本当に嬉しいよ、ジリアン。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "ここは初めてだと言うのか？どうやってここに来たんだ？難破を生き延びたのか？";
			link.l1 = "まあ……そんなところだ。俺はバーク船でここへ航海してきて、もう少しで暗礁を抜けられるところだったが、 運悪く外側の環礁にぶつかって船が沈んじまった。乗組員の中でここまで泳ぎ着いたのは、俺一人だけだったんだ。";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "おお！それで島を探しに来たのか？信じられねえな！";
			link.l1 = "ああ、ちょっと正気じゃなかったんだ。伝説の正義の島を探すと決めて、ついに見つけた。\nでも…どうやってここを出るかは、まだ分からないんだ。";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "お前は相当勇敢か、あるいは無謀だな。自分の意思でここまで航海してくるとは……これでお前も俺たちと同じく、この島に閉じ込められたわけだ。何年も誰一人としてここから出ていないんだぜ。";
			link.l1 = "俺はまだ希望を捨てちゃいねえ。\nよし、ジリアン、ありがとう、もう行っていいぜ。じゃあな、奥さん！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "「ああ、もちろん」 "+pchar.name+"……聞いているぞ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "島を出たいのか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "「それで、どうやって日々を過ごしているんだ？」";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "結婚していないって言うけど……こんなに可愛い娘に言い寄る男はいないのかい？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "俺は両親と一緒にイングランドから航海してきたんだ。貧しかったから、新世界で新しい人生を始めたくてさ……でも、嵐に船が巻き込まれて、両親は死んじまった。俺だけがなんとか生き延びたんだ。外輪の難破船にたどり着いて、 一日中気を失っていたところを誰かに見つけられたんだよ。\n新しい人生は始めたけど、それはたぶん両親が夢見ていたものとは違うな。";
			link.l1 = "すまない……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "それで、どこへ行けっていうの？誰が私を受け入れてくれるの？家も、夫も、お金もないのよ。ロンドンのスラムと……この正義の島しか知らないんだから。ここで生きるのが私の運命なら、仕方ないわ――女にとっては、もっとひどいことだってあったはずだもの。";
			link.l1 = "まあ、納得するしかないか。";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "私は主に教会でジュリアン兄弟の手伝いをしています。\nそれから、アクセルの店で雑用もやってます――それで小銭を稼いでるんです。外輪の難破船をよじ登るなんて、私には無理ですから。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "うふふ……言い寄ってくる男はいるけど、ろくな奴はいないのよ。誰も好きじゃないし、 好きでもない男と一緒に暮らしたくなんてないわ。あたしが本当に好きな男たちは、 全然あたしのことなんて見てくれないし……。あたしなんて、ただの貧乏な普通の娘よ……";
			link.l1 = "きっと誰かを見つけられるさ、そして君にはまだこれからの人生がたくさん残っているんだ…";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("「ああ、泥棒め！」", "それに汚え手を出すな、それは俺のもんだ！", "俺はお前に俺の箱を開ける許可なんて出してねえぞ！");
			link.l1 = "「くそっ！」";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の胸から手を離せ、この泥棒め！";
			link.l1 = "「愚かな娘め！」";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("旦那、お願いです、武器をしまってください。怖いですよ。", "この島の連中は、剣を振り回して走り回るのを嫌うんだ。", "剣を振り回して走り回る男なんて、俺は感心しねえ。しまっとけ。");
			link.l1 = LinkRandPhrase("いいだろう。", "いいだろう。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "この島の連中は、剣を振り回して走り回るのを嫌うんだ。", "剣をしまってください、旦那。武装した男がうろついていると、私たちは不安になるんです。");
				link.l1 = LinkRandPhrase("いいだろう。", "申し訳ありませんが……", "申し訳ありません、奥様……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、お願いです、武器をしまってください。怖いですよ。", "剣を振り回してる男なんて、俺は感心しねえよ。しまっとけ。");
				link.l1 = RandPhraseSimple("すまねえ……", "俺はそれを片付けてるところだ。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
