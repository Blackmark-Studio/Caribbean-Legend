// Куранай - индеец
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
				dialog.text = "白い顔の犬は白人の兄弟姉妹を傷つけた。俺はお前とは話さねえ。行け。";
				link.l1 = "「ああ……」";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "白い兄弟は何が欲しいんだ？";
				link.l1 = TimeGreeting()+"「“白い兄弟”だと？なあ、どうしてお前たちインディアンは、俺たちのことを“白い兄弟”とか“色白の犬”なんて呼ぶんだ、ん？」";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+"! "+TimeGreeting()+"「おう、何か用か？」";
				link.l1 = LinkRandPhrase("やあ、クラナイ。最近正義の島で何が起きているんだ？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "見つけたものを見せてくれ、何か買うかもしれねえ…";
					link.l3.go = "trade";
				}
				link.l5 = "元気にしてるか様子を見に来ただけだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "ここではみんな平和に暮らしてるぜ、白い兄弟。俺は白い兄弟を蒼白犬なんて呼ばねえよ。 蒼白いやつがみんな犬ってわけじゃねえ、インディアンのことを「赤肌の犬」って呼ぶことも多いからな。";
			link.l1 = "哲学者みたいな口ぶりだな。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "俺にはお前の言ってることがわからねえ、白い兄弟よ。「哲学者」って何のことだ？";
			link.l1 = "気にすんな、赤肌の兄弟よ。お前の考え方が気に入っただけだ。俺の名は "+GetFullName(pchar)+"。そちらは？";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "クラナイが俺の名だ。白い兄弟の名を知れて嬉しいぜ。";
			link.l1 = "クラナイ……じゃあ、またな！";
			link.l1.go = "exit";
			link.l3 = "この島についていくつか質問したいんだ、Curanai。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞けよ、白い兄弟。俺が答えてやる。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "この島で何をしているんだ？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "「家に帰りたいのか？」";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "この島で平和に暮らしているのか？ここで喧嘩や争いごとは起きるのか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "私と部族の戦士七人は、晴れた日には見えるこの島からそう遠くない小さな島へ航海することを決めた。竹で筏を作り、 出航した。だが、突然嵐に襲われ、我々は一気に外洋へと流された。自分たちの土地や島がどれほど早く消えたか、 気づかなかった。\n何日も何夜も海を漂った。兄弟たちは皆、渇きと飢えで死んでいった。生き残ったのは私一人――精霊が哀れんでくれて、この島へ筏を運んでくれたのだ。";
			link.l1 = "そうか……悲しい話だな。";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "俺は魚を獲る。銛で魚を突くんだ。たまに、たまにだけど大きなカニを突くこともある。そしたら嬉しいぜ。 カニはうまい、すごくうまい。一匹で何日か食えるんだ。\nそれから、カニがいない場所で海底にも潜る。黄色い石、青い石、黒い石、それに真珠を拾う。大きいのも小さいのもな。 \nそれを白い兄弟や白い姉妹に売るんだ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "家に帰りたい。でも、家ってどこなんだ？村がどこにあるのかも、 どうやってそこへ航海すればいいのかも分からないんだ。";
			link.l1 = "うーん、本当にすまないな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "ナーワル族とリバドス族は、しょっちゅう争っている。族長は二人いて、互いに憎み合っている。いつか、 どちらかが相手を殺すだろう。俺にはそう見える。\n残りの俺たちは平和に暮らして、誰も傷つけたりしない。時々、白い兄弟たちが火酒を飲んで悪態をつくことはあるが……殺し合いはないんだ。 ";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("止まれ、色白の犬め！自分のものじゃねえ物を取るんじゃねえ！", "白い顔の犬が俺が見てねえ隙に持っていきやがったのか！？そんなことあるかよ！", "それは俺のものだ、色白の犬め！お前のものじゃねえものを渡すつもりはねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "何だと！？俺の宝箱を荒らすつもりか？ただじゃ済まねえぞ！";
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
			dialog.text = LinkRandPhrase("俺は白い兄弟の裸の刃を見るのは好きじゃねえ。しまってくれ。", "白い兄弟姉妹たちは、お前が刃物を持って走るのを好まない。やめろ、兄弟。", "英雄気取りはやめろ、白い兄弟。刃物をしまえ。");
			link.l1 = LinkRandPhrase("「いいだろう。」", "ああ、いいぜ。", "すまねえ……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "俺はここで静かに暮らしてるんだ。手に刃物を持って行くなんて間違ってるぜ。", "待て、白い兄弟よ。刃物をしまえ、それは俺を怯えさせる。");
				link.l1 = LinkRandPhrase("いいだろう。", "まあ、どうでもいいさ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "白い兄弟よ、刃物をしまってくれ……それがあると落ち着かねえんだよ……", "白人は鋼を持つ時は使うつもりの時だけだ。しまいな…");
				link.l1 = RandPhraseSimple("了解だ。", "俺がそれを持っていく。");
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
