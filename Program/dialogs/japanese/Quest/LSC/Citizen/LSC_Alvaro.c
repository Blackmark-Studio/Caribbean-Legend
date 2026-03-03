// Альваро Гомец - капитан
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
				dialog.text = "旦那、俺はあんたに何も言わねえ！あんたは理由もなく平和な人々を襲うんだ。くたばっちまえ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ああ、新顔だな！ようこそ！それで、いつここに来たんだ？最近の難破船は覚えがないが。";
				link.l1 = TimeGreeting()+"。私の名は "+GetFullName(pchar)+"。そして俺の船は夜の闇に、静かに、あっという間に沈んじまった。乗組員の中で、 この島まで泳ぎ着いたのは俺だけだったんだ…";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用か？";
				link.l1 = LinkRandPhrase("俺に何か面白い話でもあるか？", "島で何か新しいことがあったかい？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ちょっと様子を見に来ただけだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "なるほど。ああ、自己紹介を忘れていたな。すまない、旦那。俺の名はアルバロ・ゴメス、 かつてはブリッグの船長だったんだ。ええ、今じゃ俺の自慢の船は外輪の向こう、海の底さ……あれからいろいろあったよ。ああ、これが人生ってやつだな。会えて嬉しいぜ！\n";
			link.l1 = "こちらこそお会いできて嬉しいです、ゴメス旦那。";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("俺に何か面白い話でもあるのか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞いてるぜ、旦那。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "かつて船長だったと言っていましたね。どうやってこの正義の島に来たのですか？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "この島での暮らしについて何か教えてくれないか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "教えてくれ、ここの住民たちは互いに平和に暮らしているのか？もちろん、クラン同士は別としてな。";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "現地の住民たちはどこから食料を手に入れているんだ？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "他の連中と同じさ。嵐に巻き込まれたんだ。マストも舵も失って、潮に流されて礁に打ち上げられた。 俺の船は外輪にすら届かずに壊れちまったよ。生き残ったのは、俺を含めてほんの数人だけだった。";
			link.l1 = "悲しい話だな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "何と言えばいいかな？生活に必要なものはすべて揃っているよ。ただ、時々ここは本当に退屈になるし、あの憂鬱さが……最初の一年は本当に辛かった。でも正義の島には慣れたよ。可哀想なのは妻のサブリナだ――きっと俺が死んだと思っているだろう。どうか彼女が再婚して、幸せに暮らしていることを願っているんだ。\n自分の境遇をあまり気に病むなよ、旦那。すぐに慣れるさ。酒場や店、教会に行って、みんなと顔を合わせてみるといい――でも、ナーワルやリバドスの連中のところには本当に必要な時以外は近づくな！ あいつらは一筋縄じゃいかない連中だからな。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "まあ、穏やかなもんさ。ここには書かれた法律なんてないが、理由もなく誰かを殴ったり、 ましてや殺しなんてしちまったら、隔離されるぜ。夜中に海に放り出されることだってあるんだ。\n昔、この島にはどこのクランにも属さない乱暴者が何人かいた――本当に悪党だったよ。最初の奴は姿を消し、二人目はタルタロスの牢屋で数ヶ月腐った後に死んだ。\nもちろん、暴力的な攻撃から身を守るのは構わねえが、基本的に島民はみんな穏やかだ。 アボットは威張ってるが攻撃的じゃねえし、カッセルはろくでなしだが手は汚さねえ。プラットは元囚人だが、 無害なもんさ。\nここには元海軍士官が二人いる――ローダーデールとソルデッラだ。二人ともこの島の近くで海戦をやってて流れ着いたんだ。どっちも生き延びて、 今でも互いに血なまぐさい計画を立ててやがる。";
			link.l1 = "興味深いな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "難破船の船倉からだよ、実際のところ。昔はサン・アウグスティン号にすべての食糧が保管されていて、 みんなで平等に分け合ってたんだ。だが、海賊どもがやってきてサン・アウグスティン号を奪いやがった――今じゃ、俺たちが元々持ってた食糧を買うために、島中から金を巻き上げてやがる！\n俺たちにも隠し場所はあるから、飢え死にまではしないさ。魚を釣ったり、鳥を撃ったりもするが、 一番うまい肉は巨大ガニだ。あいつらの肉は旨くて栄養もある――ただ、めったに外輪の近くまでは来ねえんだよな。\n潜って狩るのは危険すぎる。昔、一人だけ水中でガニ狩りに挑んだ勇者がいたが、結局運が尽きちまった。それ以来、 誰もカニ肉を求めて潜ろうとはしねえよ。";
			link.l1 = "面白いな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("泥棒！Thief！", "欲しいものを勝手に奪えると思ってんのか！？剣を抜け！", "よくも俺の持ち物を盗みやがったな！この剣で思い知らせてやる！");
			link.l1 = "「くそっ！」";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "何だと！？俺の宝箱を荒らすつもりか？ただじゃ済まねえぞ！";
			link.l1 = "忌々しい女め！";
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
			dialog.text = LinkRandPhrase("あいや、カランバ！武器をしまえ、旦那！", "ここでは、剣を抜いたまま走り回る奴は歓迎されねえんだ。", "聞けよ、旦那、剣を抜いたままうろつくのは危ないぜ。しまってくれ…");
			link.l1 = LinkRandPhrase("「いいだろう。」", "ああ、いいぜ。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "この街の市民として、あなたに剣を収めていただきたい。", "この町の市民として、あなたに剣を収めていただきたい。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "それならそれでいいさ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "気をつけろよ、旦那、そんな武器を持ってうろついてると。俺を不安にさせるじゃねえか…", "俺の前でそんなふうに武器を振り回さないでくれ。怖いんだよ……");
				link.l1 = RandPhraseSimple("承知した。", "しまっておく。");
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
